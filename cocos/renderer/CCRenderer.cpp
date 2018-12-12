/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "renderer/CCRenderer.h"

#include <algorithm>

#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCBatchCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCPrimitiveCommand.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"

#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "2d/CCCamera.h"
#include "2d/CCScene.h"

#include "renderer/backend/Backend.h"

NS_CC_BEGIN

// helper
static bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getGlobalOrder() < b->getGlobalOrder();
}

static bool compare3DCommand(RenderCommand* a, RenderCommand* b)
{
    return  a->getDepth() > b->getDepth();
}

// queue
RenderQueue::RenderQueue()
{
}

void RenderQueue::push_back(RenderCommand* command)
{
    float z = command->getGlobalOrder();
    if(z < 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_NEG].push_back(command);
    }
    else if(z > 0)
    {
        _commands[QUEUE_GROUP::GLOBALZ_POS].push_back(command);
    }
    else
    {
        if(command->is3D())
        {
            if(command->isTransparent())
            {
                _commands[QUEUE_GROUP::TRANSPARENT_3D].push_back(command);
            }
            else
            {
                _commands[QUEUE_GROUP::OPAQUE_3D].push_back(command);
            }
        }
        else
        {
            _commands[QUEUE_GROUP::GLOBALZ_ZERO].push_back(command);
        }
    }
}

ssize_t RenderQueue::size() const
{
    ssize_t result(0);
    for(int index = 0; index < QUEUE_GROUP::QUEUE_COUNT; ++index)
    {
        result += _commands[index].size();
    }
    
    return result;
}

void RenderQueue::sort()
{
    // Don't sort _queue0, it already comes sorted
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::TRANSPARENT_3D]), std::end(_commands[QUEUE_GROUP::TRANSPARENT_3D]), compare3DCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_NEG]), std::end(_commands[QUEUE_GROUP::GLOBALZ_NEG]), compareRenderCommand);
    std::stable_sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_POS]), std::end(_commands[QUEUE_GROUP::GLOBALZ_POS]), compareRenderCommand);
}

RenderCommand* RenderQueue::operator[](ssize_t index) const
{
    for(int queIndex = 0; queIndex < QUEUE_GROUP::QUEUE_COUNT; ++queIndex)
    {
        if(index < static_cast<ssize_t>(_commands[queIndex].size()))
            return _commands[queIndex][index];
        else
        {
            index -= _commands[queIndex].size();
        }
    }
    
    CCASSERT(false, "invalid index");
    return nullptr;
}

void RenderQueue::clear()
{
    for(int i = 0; i < QUEUE_COUNT; ++i)
    {
        _commands[i].clear();
    }
}

void RenderQueue::realloc(size_t reserveSize)
{
    for(int i = 0; i < QUEUE_COUNT; ++i)
    {
        _commands[i] = std::vector<RenderCommand*>();
        _commands[i].reserve(reserveSize);
    }
}

//
//
//
static const int DEFAULT_RENDER_QUEUE = 0;

//
// constructors, destructor, init
//
Renderer::Renderer()
{
    _groupCommandManager = new (std::nothrow) GroupCommandManager();
    
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _queuedTriangleCommands.reserve(BATCH_TRIAGCOMMAND_RESERVED_SIZE);

    // for the batched TriangleCommand
    _triBatchesToDraw = (TriBatchToDraw*) malloc(sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
    
    _renderPassDescriptor.clearColorValue = {0, 0, 0, 1};
    _renderPassDescriptor.needClearColor = true;
    _renderPassDescriptor.needColorAttachment = true;
    _renderPassDescriptor.clearDepthValue = 0;
    _renderPassDescriptor.needClearDepth = true;
    _renderPassDescriptor.needDepthAttachment = true;
    _renderPassDescriptor.clearStencilValue = 0;
    _renderPassDescriptor.needClearStencil = true;
    _renderPassDescriptor.needStencilAttachment = true;
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
    
    free(_triBatchesToDraw);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_cacheTextureListener);
#endif
    
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
    CC_SAFE_RELEASE(_commandBuffer);
}

void Renderer::init()
{
    auto device = backend::Device::getInstance();
    _vertexBuffer = device->newBuffer(Renderer::VBO_SIZE, backend::BufferType::VERTEX, backend::BufferUsage::READ);
    _indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE, backend::BufferType::INDEX, backend::BufferUsage::READ);
    _commandBuffer = device->newCommandBuffer();
}

void Renderer::addCommand(RenderCommand* command)
{
    int renderQueueID =_commandGroupStack.top();
    addCommand(command, renderQueueID);
}

void Renderer::addCommand(RenderCommand* command, int renderQueueID)
{
    CCASSERT(!_isRendering, "Cannot add command while rendering");
    CCASSERT(renderQueueID >=0, "Invalid render queue");
    CCASSERT(command->getType() != RenderCommand::Type::UNKNOWN_COMMAND, "Invalid Command Type");

    _renderGroups[renderQueueID].push_back(command);
}

void Renderer::pushGroup(int renderQueueID)
{
    CCASSERT(!_isRendering, "Cannot change render queue while rendering");
    _commandGroupStack.push(renderQueueID);
}

void Renderer::popGroup()
{
    CCASSERT(!_isRendering, "Cannot change render queue while rendering");
    _commandGroupStack.pop();
}

int Renderer::createRenderQueue()
{
    RenderQueue newRenderQueue;
    _renderGroups.push_back(newRenderQueue);
    return (int)_renderGroups.size() - 1;
}

void Renderer::processRenderCommand(RenderCommand* command)
{
    auto commandType = command->getType();
    switch(commandType)
    {
        case RenderCommand::Type::TRIANGLES_COMMAND:
        {
            // flush other queues
            flush3D();
            
            auto cmd = static_cast<TrianglesCommand*>(command);
            
            // flush own queue when buffer is full
            if(_filledVertex + cmd->getVertexCount() > VBO_SIZE || _filledIndex + cmd->getIndexCount() > INDEX_VBO_SIZE)
            {
                CCASSERT(cmd->getVertexCount()>= 0 && cmd->getVertexCount() < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
                CCASSERT(cmd->getIndexCount()>= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE, "VBO for index is not big enough, please break the data down or use customized render command");
                drawBatchedTriangles();
            }
            
            // queue it
            _queuedTriangleCommands.push_back(cmd);
//             _filledIndex += cmd->getIndexCount();
//             _filledVertex += cmd->getVertexCount();
        }
            break;
        case RenderCommand::Type::MESH_COMMAND:
        {
            flush2D();
            auto cmd = static_cast<MeshCommand*>(command);
            
            if (cmd->isSkipBatching() || _lastBatchedMeshCommand == nullptr || _lastBatchedMeshCommand->getMaterialID() != cmd->getMaterialID())
            {
                flush3D();
                
                //            CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_MESH_COMMAND");
                
                if(cmd->isSkipBatching())
                {
                    // XXX: execute() will call bind() and unbind()
                    // but unbind() shouldn't be call if the next command is a MESH_COMMAND with Material.
                    // Once most of cocos2d-x moves to Pass/StateBlock, only bind() should be used.
                    cmd->execute();
                }
                else
                {
                    cmd->preBatchDraw();
                    cmd->batchDraw();
                    _lastBatchedMeshCommand = cmd;
                }
            }
            else
            {
                //            CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_MESH_COMMAND");
                cmd->batchDraw();
            }
        }
            break;
        case RenderCommand::Type::GROUP_COMMAND:
        {
            flush();
            
            RenderInfo renderInfo;
            renderInfo.viewPort = command->getViewPort();
            _renderInfoStack.push(renderInfo);
            clear(command->getPipelineDescriptor().renderPassDescriptor);
            
            int renderQueueID = ((GroupCommand*) command)->getRenderQueueID();
            visitRenderQueue(_renderGroups[renderQueueID]);
            _renderInfoStack.pop();
        }
            break;
        case RenderCommand::Type::CUSTOM_COMMAND:
            flush();
            drawCustomCommand(command);
            break;
        case RenderCommand::Type::BATCH_COMMAND:
            flush();
            drawBatchedCommand(command);
            break;
        case RenderCommand::Type::PRIMITIVE_COMMAND:
        {
            flush();
            auto cmd = static_cast<PrimitiveCommand*>(command);
            //        CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_PRIMITIVE_COMMAND");
            cmd->execute();
        }
            break;
        default:
            assert(false);
            break;
    }
}

void Renderer::visitRenderQueue(RenderQueue& queue)
{
    //
    //Process Global-Z < 0 Objects
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_NEG));
    
    //
    //Process Opaque Object
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::OPAQUE_3D));
    
    //
    //Process 3D Transparent object
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::TRANSPARENT_3D));
    
    //
    //Process Global-Z = 0 Queue
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO));
        
    //
    //Process Global-Z > 0 Queue
    //
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_POS));
}

void Renderer::doVisitRenderQueue(const std::vector<RenderCommand*>& renderCommands)
{
    for (const auto& command : renderCommands)
        {
        processRenderCommand(command);
        }
        flush();
}

void Renderer::render()
{
    //TODO: setup camera or MVP
    _isRendering = true;
//    if (_glViewAssigned)
    {
        //Process render commands
        //1. Sort render commands based on ID
        for (auto &renderqueue : _renderGroups)
        {
            renderqueue.sort();
        }
        visitRenderQueue(_renderGroups[0]);
    }
    clean();
    _isRendering = false;
}

void Renderer::beginFrame()
{
    _commandBuffer->beginFrame();
    clear(_renderPassDescriptor);
}

void Renderer::endFrame()
{
    _commandBuffer->endFrame();
}

void Renderer::clean()
{
    // Clear render group
    for (size_t j = 0, size = _renderGroups.size() ; j < size; j++)
    {
        //commands are owned by nodes
        // for (const auto &cmd : _renderGroups[j])
        // {
        //     cmd->releaseToCommandPool();
        // }
        _renderGroups[j].clear();
    }

    // Clear batch commands
    _queuedTriangleCommands.clear();
    _lastBatchedMeshCommand = nullptr;
}

void Renderer::setDepthTest(bool enable)
{
//    if (enable)
//    {
//        glClearDepth(1.0f);
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LEQUAL);
//
//        RenderState::StateBlock::_defaultState->setDepthTest(true);
//        RenderState::StateBlock::_defaultState->setDepthFunction(RenderState::DEPTH_LEQUAL);
//
////        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    }
//    else
//    {
//        glDisable(GL_DEPTH_TEST);
//
//        RenderState::StateBlock::_defaultState->setDepthTest(false);
//    }
//
//    _isDepthTestFor2D = enable;
//    CHECK_GL_ERROR_DEBUG();
    //todo: minggo
}

void Renderer::fillVerticesAndIndices(const TrianglesCommand* cmd)
{
    memcpy(&_verts[_filledVertex], cmd->getVertices(), sizeof(V3F_C4B_T2F) * cmd->getVertexCount());
    
    // fill vertex, and convert them to world coordinates
    const Mat4& modelView = cmd->getModelView();
    for(ssize_t i=0; i < cmd->getVertexCount(); ++i)
    {
        modelView.transformPoint(&(_verts[i + _filledVertex].vertices));
    }
    
    // fill index
    const unsigned short* indices = cmd->getIndices();
    for(ssize_t i=0; i< cmd->getIndexCount(); ++i)
    {
        _indices[_filledIndex + i] = _filledVertex + indices[i];
    }
    
    _filledVertex += cmd->getVertexCount();
    _filledIndex += cmd->getIndexCount();
}

void Renderer::cleanVerticesAndIncices()
{
    _filledIndex = 0;
    _filledVertex = 0;
}

void Renderer::drawBatchedTriangles()
{
    if(_queuedTriangleCommands.empty())
        return;
    
    /************** 1: Setup up vertices/indices *************/
    
    _triBatchesToDraw[0].offset = 0;
    _triBatchesToDraw[0].indicesToDraw = 0;
    _triBatchesToDraw[0].cmd = nullptr;
    
    int batchesTotal = 0;
    int prevMaterialID = -1;
    bool firstCommand = true;
    
    for(const auto& cmd : _queuedTriangleCommands)
    {
        auto currentMaterialID = cmd->getMaterialID();
        const bool batchable = !cmd->isSkipBatching();
        
        fillVerticesAndIndices(cmd);
        
        // in the same batch ?
        if (batchable && (prevMaterialID == currentMaterialID || firstCommand))
        {
            CC_ASSERT((firstCommand || _triBatchesToDraw[batchesTotal].cmd->getMaterialID() == cmd->getMaterialID()) && "argh... error in logic");
            _triBatchesToDraw[batchesTotal].indicesToDraw += cmd->getIndexCount();
            _triBatchesToDraw[batchesTotal].cmd = cmd;
        }
        else
        {
            // is this the first one?
            if (!firstCommand)
            {
                batchesTotal++;
                _triBatchesToDraw[batchesTotal].offset =
                    _triBatchesToDraw[batchesTotal-1].offset + _triBatchesToDraw[batchesTotal-1].indicesToDraw;
            }
            
            _triBatchesToDraw[batchesTotal].cmd = cmd;
            _triBatchesToDraw[batchesTotal].indicesToDraw = (int) cmd->getIndexCount();
            
            // is this a single batch ? Prevent creating a batch group then
            if (!batchable)
                currentMaterialID = -1;
        }
        
        // capacity full ?
        if (batchesTotal + 1 >= _triBatchesToDrawCapacity)
        {
            _triBatchesToDrawCapacity *= 1.4;
            _triBatchesToDraw = (TriBatchToDraw*) realloc(_triBatchesToDraw, sizeof(_triBatchesToDraw[0]) * _triBatchesToDrawCapacity);
        }
        
        prevMaterialID = currentMaterialID;
        firstCommand = false;
    }
    batchesTotal++;
    
     _vertexBuffer->updateData(_verts, 0, sizeof(_verts[0]) * _filledVertex);
     _indexBuffer->updateData(_indices, 0, sizeof(_indices[0]) * _filledIndex);
    
    /************** 2: Draw *************/
    for (int i = 0; i < batchesTotal; ++i)
    {
        beginRenderPass(_triBatchesToDraw[i].cmd);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setIndexBuffer(_indexBuffer);
        auto& pipelineDescriptor = _triBatchesToDraw[i].cmd->getPipelineDescriptor();
        _commandBuffer->setBindGroup(&pipelineDescriptor.bindGroup);
        _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                     backend::IndexFormat::U_SHORT,
                                     _triBatchesToDraw[i].indicesToDraw,
                                     _triBatchesToDraw[i].offset * sizeof(_indices[0]));
        _commandBuffer->endRenderPass();
    }
    
    /************** 3: Cleanup *************/
    _queuedTriangleCommands.clear();
    cleanVerticesAndIncices();
}

void Renderer::drawBatchedCommand(RenderCommand* command)
{
//    fillVerticesAndIndices(command);
//    
//    /************** 2: Draw *************/
//    auto& pipelineDescriptor = command->getPipelineDescriptor();
//    _commandBuffer->beginRenderPass(pipelineDescriptor.renderPassDescriptor);
//    auto renderPipeline = createRenderPipeline(pipelineDescriptor);
//    _commandBuffer->setRenderPipeline(renderPipeline);
//    renderPipeline->release();
//    
//    auto viewPort = command->getViewPort();
//    _commandBuffer->setViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
//    
//    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
//    _commandBuffer->setIndexBuffer(_indexBuffer);
//    _commandBuffer->setBindGroup(&pipelineDescriptor.bindGroup);
//    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
//                                 backend::IndexFormat::U_SHORT,
//                                 command->getIndexCount(),
//                                 0);
//    
//    _commandBuffer->endRenderPass();
}

void Renderer::drawCustomCommand(RenderCommand *command)
{
    auto cmd = static_cast<CustomCommand*>(command);
    
    beginRenderPass(command);
    _commandBuffer->setVertexBuffer(0, cmd->getVertexBuffer());
    _commandBuffer->setBindGroup( &(cmd->getPipelineDescriptor().bindGroup) );
    
    auto drawType = cmd->getDrawType();
    if (CustomCommand::DrawType::ELEMENT == drawType)
    {
        _commandBuffer->setIndexBuffer(cmd->getIndexBuffer());
        _commandBuffer->drawElements(cmd->getPrimitiveType(),
                                     backend::IndexFormat::U_SHORT,
                                     cmd->getIndexDrawCount(),
                                     cmd->getIndexDrawBufferOffset());
    }
    else
        _commandBuffer->drawArrays(cmd->getPrimitiveType(),
                                   cmd->getVertexDrawStart(),
                                   cmd->getVertexDrawCount());
    
    _commandBuffer->endRenderPass();
}

void Renderer::flush()
{
    flush2D();
    flush3D();
}

void Renderer::flush2D()
{
    flushTriangles();
}

void Renderer::flush3D()
{
    if (_lastBatchedMeshCommand)
    {
        _lastBatchedMeshCommand->postBatchDraw();
        _lastBatchedMeshCommand = nullptr;
    }
}

void Renderer::flushTriangles()
{
    drawBatchedTriangles();
}

// helpers
bool Renderer::checkVisibility(const Mat4 &transform, const Size &size)
{
//    auto director = Director::getInstance();
//    auto scene = director->getRunningScene();
//
//    //If draw to Rendertexture, return true directly.
//    // only cull the default camera. The culling algorithm is valid for default camera.
//    if (!scene || (scene && scene->_defaultCamera != Camera::getVisitingCamera()))
//        return true;
//
//    Rect visibleRect(director->getVisibleOrigin(), director->getVisibleSize());
//
//    // transform center point to screen space
//    float hSizeX = size.width/2;
//    float hSizeY = size.height/2;
//    Vec3 v3p(hSizeX, hSizeY, 0);
//    transform.transformPoint(&v3p);
//    Vec2 v2p = Camera::getVisitingCamera()->projectGL(v3p);
//
//    // convert content size to world coordinates
//    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]), fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
//    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]), fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));
//
//    // enlarge visible rect half size in screen coord
//    visibleRect.origin.x -= wshw;
//    visibleRect.origin.y -= wshh;
//    visibleRect.size.width += wshw * 2;
//    visibleRect.size.height += wshh * 2;
//    bool ret = visibleRect.containsPoint(v2p);
//    return ret;
    // todo: minggo
    return true;
}


void Renderer::setClearColor(const Color4F &clearColor)
{
    _clearColor = clearColor;
    _renderPassDescriptor.clearColorValue = {clearColor.r, clearColor.g, clearColor.b, clearColor.a};
}

void Renderer::setRenderPipeline(const PipelineDescriptor& pipelineDescriptor, const backend::RenderPassDescriptor& renderPassDescriptor)
{
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.vertexShaderModule = pipelineDescriptor.vertexShader;
    renderPipelineDescriptor.fragmentShaderModule = pipelineDescriptor.fragmentShader;
    renderPipelineDescriptor.vertexLayouts.push_back(pipelineDescriptor.vertexLayout);
    
    auto device = backend::Device::getInstance();
    auto blendState = device->createBlendState(pipelineDescriptor.blendDescriptor);
    renderPipelineDescriptor.blendState = blendState;
    
    auto& depthStencilDescritpor = pipelineDescriptor.depthStencilDescriptor;
    if (depthStencilDescritpor.depthTestEnabled || depthStencilDescritpor.stencilTestEnabled)
    {
        auto depthStencilState = device->createDepthStencilState(depthStencilDescritpor);
        renderPipelineDescriptor.depthStencilState = depthStencilState;
    }
    
    if (renderPassDescriptor.needColorAttachment)
    {
        // FIXME: now just handle color attach ment 0.
        if (renderPassDescriptor.colorAttachmentsTexture[0])
            renderPipelineDescriptor.colorAttachmentsFormat[0] = renderPassDescriptor.colorAttachmentsTexture[0]->getTextureFormat();
    }
    
    if (renderPassDescriptor.needDepthAttachment)
    {
        if (renderPassDescriptor.depthAttachmentTexture)
            renderPipelineDescriptor.depthAttachmentFormat = renderPassDescriptor.depthAttachmentTexture->getTextureFormat();
        else
            renderPipelineDescriptor.depthAttachmentFormat = backend::TextureFormat::D24S8;
    }
    if (renderPassDescriptor.needStencilAttachment)
    {
        if (renderPassDescriptor.stencilAttachmentTexture)
            renderPipelineDescriptor.stencilAttachmentFormat = renderPassDescriptor.stencilAttachmentTexture->getTextureFormat();
        else
            renderPipelineDescriptor.stencilAttachmentFormat = backend::TextureFormat::D24S8;
    }

    //FIXME: optimize it, cache the result as possible.
    auto renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
    _commandBuffer->setRenderPipeline(renderPipeline);
    renderPipeline->release();
}

void Renderer::beginRenderPass(RenderCommand* cmd)
{
    const auto& renderPassDescriptor = cmd->getPipelineDescriptor().renderPassDescriptor;
    _commandBuffer->beginRenderPass(renderPassDescriptor);
    
    // Set viewport.
    if (_renderInfoStack.empty())
    {
        const auto& viewport = cmd->getViewPort();
        _commandBuffer->setViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    }
    else
    {
        const auto& viewport = _renderInfoStack.top().viewPort;
        _commandBuffer->setViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    }
    
    // Set render pipeline.
    setRenderPipeline(cmd->getPipelineDescriptor(), renderPassDescriptor);
}

void Renderer::clear(const backend::RenderPassDescriptor& descriptor)
{
    _commandBuffer->beginRenderPass(descriptor);
    _commandBuffer->endRenderPass();
}

NS_CC_END
