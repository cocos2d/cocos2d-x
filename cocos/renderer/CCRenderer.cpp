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
#include "renderer/CCCustomCommand.h"
#include "renderer/CCCallbackCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCTexture2D.h"

#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "2d/CCCamera.h"
#include "2d/CCScene.h"
#include "xxhash.h"

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
    for(int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
    {
        _commands[i].clear();
    }
}

void RenderQueue::realloc(size_t reserveSize)
{
    for(int i = 0; i < QUEUE_GROUP::QUEUE_COUNT; ++i)
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
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
    
    free(_triBatchesToDraw);
    
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPipeline);
}

void Renderer::init()
{
    // Should invoke _triangleCommandBufferManager.init() first.
    _triangleCommandBufferManager.init();
    _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
    _indexBuffer = _triangleCommandBufferManager.getIndexBuffer();

    auto device = backend::Device::getInstance();
    _commandBuffer = device->newCommandBuffer();
    _renderPipeline = device->newRenderPipeline();
    _commandBuffer->setRenderPipeline(_renderPipeline);
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

void Renderer::processGroupCommand(GroupCommand* command)
{
    flush();

    int renderQueueID = ((GroupCommand*) command)->getRenderQueueID();

    pushStateBlock();
    //apply default state for all render queues
    setDepthTest(false);
    setDepthWrite(false);
    setCullMode(backend::CullMode::NONE);
    visitRenderQueue(_renderGroups[renderQueueID]);
    popStateBlock();
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
            if(_queuedTotalVertexCount + cmd->getVertexCount() > VBO_SIZE || _queuedTotalIndexCount + cmd->getIndexCount() > INDEX_VBO_SIZE)
            {
                CCASSERT(cmd->getVertexCount()>= 0 && cmd->getVertexCount() < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
                CCASSERT(cmd->getIndexCount()>= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE, "VBO for index is not big enough, please break the data down or use customized render command");
                drawBatchedTriangles();

                _queuedTotalIndexCount = _queuedTotalVertexCount = 0;
#ifdef CC_USE_METAL
                _queuedIndexCount = _queuedVertexCount = 0;
                _triangleCommandBufferManager.prepareNextBuffer();
                _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
                _indexBuffer = _triangleCommandBufferManager.getIndexBuffer();
#endif
            }
            
            // queue it
            _queuedTriangleCommands.push_back(cmd);
#ifdef CC_USE_METAL
            _queuedIndexCount += cmd->getIndexCount();
            _queuedVertexCount += cmd->getVertexCount();
#endif
            _queuedTotalVertexCount += cmd->getVertexCount();
            _queuedTotalIndexCount += cmd->getIndexCount();

        }
            break;
        case RenderCommand::Type::MESH_COMMAND:
            flush2D();
            drawMeshCommand(command);
            break;
        case RenderCommand::Type::GROUP_COMMAND:
            processGroupCommand(static_cast<GroupCommand*>(command));
            break;
        case RenderCommand::Type::CUSTOM_COMMAND:
            flush();
            drawCustomCommand(command);
            break;
        case RenderCommand::Type::CALLBACK_COMMAND:
            flush();
           static_cast<CallbackCommand*>(command)->execute();
            break;
        case RenderCommand::Type::CAPTURE_SCREEN_COMMAND:
            flush();
            captureScreen(command);
            break;
        default:
            assert(false);
            break;
    }
}

void Renderer::captureScreen(RenderCommand *command)
{
    _commandBuffer->captureScreen(static_cast<CaptureScreenCallbackCommand*>(command)->func);
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
    pushStateBlock();
    setDepthTest(true); //enable depth test in 3D queue by default
    setDepthWrite(true);
    setCullMode(backend::CullMode::BACK);
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::OPAQUE_3D));
    
    //
    //Process 3D Transparent object
    //
    setDepthWrite(false);
    doVisitRenderQueue(queue.getSubQueue(RenderQueue::QUEUE_GROUP::TRANSPARENT_3D));
    popStateBlock();

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
}

void Renderer::endFrame()
{
    _commandBuffer->endFrame();

#ifdef CC_USE_METAL
    _triangleCommandBufferManager.putbackAllBuffers();
    _vertexBuffer = _triangleCommandBufferManager.getVertexBuffer();
    _indexBuffer = _triangleCommandBufferManager.getIndexBuffer();
#endif
    _queuedTotalIndexCount = 0;
    _queuedTotalVertexCount = 0;
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
}

void Renderer::setDepthTest(bool value)
{
    _depthStencilDescriptor.depthTestEnabled = value;
    _renderPassDescriptor.depthTestEnabled = value;
}

void Renderer::setDepthWrite(bool value)
{
    _depthStencilDescriptor.depthWriteEnabled = value;
}

void Renderer::setDepthCompareFunction(backend::CompareFunction func)
{
    _depthStencilDescriptor.depthCompareFunction = func;
}

backend::CompareFunction Renderer::getDepthCompareFunction() const
{
    return _depthStencilDescriptor.depthCompareFunction;
}

bool Renderer::Renderer::getDepthTest() const
{
    return _depthStencilDescriptor.depthTestEnabled;
}

bool Renderer::getDepthWrite() const
{
    return _depthStencilDescriptor.depthWriteEnabled;
}

void Renderer::setStencilTest(bool value)
{
    _depthStencilDescriptor.stencilTestEnabled = value;
    _renderPassDescriptor.stencilTestEnabled = value;
}

void Renderer::setStencilCompareFunction(backend::CompareFunction func, unsigned int ref, unsigned int readMask)
{
    _depthStencilDescriptor.frontFaceStencil.stencilCompareFunction = func;
    _depthStencilDescriptor.backFaceStencil.stencilCompareFunction = func;

    _depthStencilDescriptor.frontFaceStencil.readMask = readMask;
    _depthStencilDescriptor.backFaceStencil.readMask = readMask;

    _stencilRef = ref;
}

void Renderer::setStencilOperation(backend::StencilOperation stencilFailureOp,
                             backend::StencilOperation depthFailureOp,
                             backend::StencilOperation stencilDepthPassOp)
{
    _depthStencilDescriptor.frontFaceStencil.stencilFailureOperation = stencilFailureOp;
    _depthStencilDescriptor.backFaceStencil.stencilFailureOperation = stencilFailureOp;

    _depthStencilDescriptor.frontFaceStencil.depthFailureOperation = depthFailureOp;
    _depthStencilDescriptor.backFaceStencil.depthFailureOperation = depthFailureOp;

    _depthStencilDescriptor.frontFaceStencil.depthStencilPassOperation = stencilDepthPassOp;
    _depthStencilDescriptor.backFaceStencil.depthStencilPassOperation = stencilDepthPassOp;
}

void Renderer::setStencilWriteMask(unsigned int mask)
{
    _depthStencilDescriptor.frontFaceStencil.writeMask = mask;
    _depthStencilDescriptor.backFaceStencil.writeMask = mask;
}

bool Renderer::getStencilTest() const
{
    return _depthStencilDescriptor.stencilTestEnabled;
}

backend::StencilOperation Renderer::getStencilFailureOperation() const
{
    return _depthStencilDescriptor.frontFaceStencil.stencilFailureOperation;
}

backend::StencilOperation Renderer::getStencilPassDepthFailureOperation() const
{
    return _depthStencilDescriptor.frontFaceStencil.depthFailureOperation;
}

backend::StencilOperation Renderer::getStencilDepthPassOperation() const
{
    return _depthStencilDescriptor.frontFaceStencil.depthStencilPassOperation;
}

backend::CompareFunction Renderer::getStencilCompareFunction() const
{
    return _depthStencilDescriptor.depthCompareFunction;
}

unsigned int Renderer::getStencilReadMask() const
{
    return _depthStencilDescriptor.frontFaceStencil.readMask;
}

unsigned int Renderer::getStencilWriteMask() const
{
    return _depthStencilDescriptor.frontFaceStencil.writeMask;
}

unsigned int Renderer::getStencilReferenceValue() const
{
    return _stencilRef;
}

void Renderer::setViewPort(int x, int y, unsigned int w, unsigned int h)
{
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = w;
    _viewport.h = h;
}

void Renderer::fillVerticesAndIndices(const TrianglesCommand* cmd, unsigned int vertexBufferOffset)
{
    size_t vertexCount = cmd->getVertexCount();
    memcpy(&_verts[_filledVertex], cmd->getVertices(), sizeof(V3F_C4B_T2F) * vertexCount);
    
    // fill vertex, and convert them to world coordinates
    const Mat4& modelView = cmd->getModelView();
    for (size_t i=0; i < vertexCount; ++i)
    {
        modelView.transformPoint(&(_verts[i + _filledVertex].vertices));
    }
    
    // fill index
    const unsigned short* indices = cmd->getIndices();
    size_t indexCount = cmd->getIndexCount();
    for (size_t i = 0; i < indexCount; ++i)
    {
        _indices[_filledIndex + i] = vertexBufferOffset + _filledVertex + indices[i];
    }
    
    _filledVertex += vertexCount;
    _filledIndex += indexCount;
}

void Renderer::drawBatchedTriangles()
{
    if(_queuedTriangleCommands.empty())
        return;
    
    /************** 1: Setup up vertices/indices *************/
#ifdef CC_USE_METAL
    unsigned int vertexBufferFillOffset = _queuedTotalVertexCount - _queuedVertexCount;
    unsigned int indexBufferFillOffset = _queuedTotalIndexCount - _queuedIndexCount;
#else
    unsigned int vertexBufferFillOffset = 0;
    unsigned int indexBufferFillOffset = 0;
#endif

    _triBatchesToDraw[0].offset = indexBufferFillOffset;
    _triBatchesToDraw[0].indicesToDraw = 0;
    _triBatchesToDraw[0].cmd = nullptr;
    
    int batchesTotal = 0;
    int prevMaterialID = -1;
    bool firstCommand = true;

    _filledVertex = 0;
    _filledIndex = 0;

    for(const auto& cmd : _queuedTriangleCommands)
    {
        auto currentMaterialID = cmd->getMaterialID();
        const bool batchable = !cmd->isSkipBatching();
        
        fillVerticesAndIndices(cmd, vertexBufferFillOffset);
        
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
#ifdef CC_USE_METAL
    _vertexBuffer->updateSubData(_verts, vertexBufferFillOffset * sizeof(_verts[0]), _filledVertex * sizeof(_verts[0]));
    _indexBuffer->updateSubData(_indices, indexBufferFillOffset * sizeof(_indices[0]), _filledIndex * sizeof(_indices[0]));
#else
    _vertexBuffer->updateData(_verts, _filledVertex * sizeof(_verts[0]));
    _indexBuffer->updateData(_indices,  _filledIndex * sizeof(_indices[0]));
#endif

    /************** 2: Draw *************/
    for (int i = 0; i < batchesTotal; ++i)
    {
        beginRenderPass(_triBatchesToDraw[i].cmd);
        _commandBuffer->setVertexBuffer(_vertexBuffer);
        _commandBuffer->setIndexBuffer(_indexBuffer);
        auto& pipelineDescriptor = _triBatchesToDraw[i].cmd->getPipelineDescriptor();
        _commandBuffer->setProgramState(pipelineDescriptor.programState);
        _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                     backend::IndexFormat::U_SHORT,
                                     _triBatchesToDraw[i].indicesToDraw,
                                     _triBatchesToDraw[i].offset * sizeof(_indices[0]));
        _commandBuffer->endRenderPass();

        _drawnBatches++;
        _drawnVertices += _triBatchesToDraw[i].indicesToDraw;
    }

    /************** 3: Cleanup *************/
    _queuedTriangleCommands.clear();

#ifdef CC_USE_METAL
    _queuedIndexCount = 0;
    _queuedVertexCount = 0;
#endif
}

void Renderer::drawCustomCommand(RenderCommand *command)
{
    auto cmd = static_cast<CustomCommand*>(command);

    if (cmd->getBeforeCallback()) cmd->getBeforeCallback()();

    beginRenderPass(command);
    _commandBuffer->setVertexBuffer(cmd->getVertexBuffer());
    _commandBuffer->setProgramState(cmd->getPipelineDescriptor().programState);
    
    auto drawType = cmd->getDrawType();
    _commandBuffer->setLineWidth(cmd->getLineWidth());
    if (CustomCommand::DrawType::ELEMENT == drawType)
    {
        _commandBuffer->setIndexBuffer(cmd->getIndexBuffer());
        _commandBuffer->drawElements(cmd->getPrimitiveType(),
                                     cmd->getIndexFormat(),
                                     cmd->getIndexDrawCount(),
                                     cmd->getIndexDrawOffset());
        _drawnVertices += cmd->getIndexDrawCount();
    }
    else
    {
        _commandBuffer->drawArrays(cmd->getPrimitiveType(),
                                   cmd->getVertexDrawStart(),
                                   cmd->getVertexDrawCount());
        _drawnVertices += cmd->getVertexDrawCount();
    }
    _drawnBatches++;
    _commandBuffer->endRenderPass();

    if (cmd->getAfterCallback()) cmd->getAfterCallback()();
}

void Renderer::drawMeshCommand(RenderCommand *command)
{
    //MeshCommand and CustomCommand are identical while rendering.
    drawCustomCommand(command);
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
    //TODO 3d batch rendering
}

void Renderer::flushTriangles()
{
    drawBatchedTriangles();
}

// helpers
bool Renderer::checkVisibility(const Mat4 &transform, const Size &size)
{
    auto director = Director::getInstance();
    auto scene = director->getRunningScene();

    //If draw to Rendertexture, return true directly.
    // only cull the default camera. The culling algorithm is valid for default camera.
    if (!scene || (scene && scene->_defaultCamera != Camera::getVisitingCamera()))
        return true;

    Rect visibleRect(director->getVisibleOrigin(), director->getVisibleSize());

    // transform center point to screen space
    float hSizeX = size.width/2;
    float hSizeY = size.height/2;
    Vec3 v3p(hSizeX, hSizeY, 0);
    transform.transformPoint(&v3p);
    Vec2 v2p = Camera::getVisitingCamera()->projectGL(v3p);

    // convert content size to world coordinates
    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]), fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]), fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));

    // enlarge visible rect half size in screen coord
    visibleRect.origin.x -= wshw;
    visibleRect.origin.y -= wshh;
    visibleRect.size.width += wshw * 2;
    visibleRect.size.height += wshh * 2;
    bool ret = visibleRect.containsPoint(v2p);
    return ret;
}

void Renderer::setRenderPipeline(const PipelineDescriptor& pipelineDescriptor, const backend::RenderPassDescriptor& renderPassDescriptor)
{
    auto device = backend::Device::getInstance();
    _renderPipeline->update(pipelineDescriptor, renderPassDescriptor);
    backend::DepthStencilState* depthStencilState = nullptr;
    auto needDepthStencilAttachment = renderPassDescriptor.depthTestEnabled || renderPassDescriptor.stencilTestEnabled;
    if (needDepthStencilAttachment)
    {
        depthStencilState = device->createDepthStencilState(_depthStencilDescriptor);
    }
    _commandBuffer->setDepthStencilState(depthStencilState);
#ifdef CC_USE_METAL
    _commandBuffer->setRenderPipeline(_renderPipeline);
#endif
}

void Renderer::beginRenderPass(RenderCommand* cmd)
{
     _commandBuffer->beginRenderPass(_renderPassDescriptor);
     _commandBuffer->setViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
     _commandBuffer->setCullMode(_cullMode);
     _commandBuffer->setWinding(_winding);
     _commandBuffer->setScissorRect(_scissorState.isEnabled, _scissorState.rect.x, _scissorState.rect.y, _scissorState.rect.width, _scissorState.rect.height);
     setRenderPipeline(cmd->getPipelineDescriptor(), _renderPassDescriptor);

    _commandBuffer->setStencilReferenceValue(_stencilRef);
}

void Renderer::setRenderTarget(RenderTargetFlag flags, Texture2D* colorAttachment, Texture2D* depthAttachment, Texture2D* stencilAttachment)
{
    _renderTargetFlag = flags;
    if (flags & RenderTargetFlag::COLOR)
    {
        _renderPassDescriptor.needColorAttachment = true;
        if (colorAttachment)
            _renderPassDescriptor.colorAttachmentsTexture[0] = colorAttachment->getBackendTexture();
        else
            _renderPassDescriptor.colorAttachmentsTexture[0] = nullptr;

        _colorAttachment = colorAttachment;
    }
    else
    {
        _colorAttachment = nullptr;
        _renderPassDescriptor.needColorAttachment = false;
        _renderPassDescriptor.colorAttachmentsTexture[0] = nullptr;
    }

    if (flags & RenderTargetFlag::DEPTH)
    {
        _renderPassDescriptor.depthTestEnabled = true;
        if (depthAttachment)
            _renderPassDescriptor.depthAttachmentTexture = depthAttachment->getBackendTexture();
        else
            _renderPassDescriptor.depthAttachmentTexture = nullptr;

        _depthAttachment = depthAttachment;
    }
    else
    {
        _renderPassDescriptor.depthTestEnabled = false;
        _renderPassDescriptor.depthAttachmentTexture = nullptr;
        _depthAttachment = nullptr;
    }

    if (flags & RenderTargetFlag::STENCIL)
    {
        _stencilAttachment = stencilAttachment;
        _renderPassDescriptor.stencilTestEnabled = true;
        if (_stencilAttachment)
            _renderPassDescriptor.stencilAttachmentTexture = stencilAttachment->getBackendTexture();
        else
            _renderPassDescriptor.stencilAttachmentTexture = nullptr;
    }
    else
    {
        _stencilAttachment = nullptr;
        _renderPassDescriptor.stencilTestEnabled = false;
        _renderPassDescriptor.stencilAttachmentTexture = nullptr;
    }
}

void Renderer::clear(ClearFlag flags, const Color4F& color, float depth, unsigned int stencil, float globalOrder)
{
    _clearFlag = flags;

    CallbackCommand* command = new CallbackCommand();
    command->init(globalOrder);
    command->func = [=]() -> void {
        backend::RenderPassDescriptor descriptor;

        if (flags & ClearFlag::COLOR)
        {
            _clearColor = color;
            descriptor.clearColorValue = {color.r, color.g, color.b, color.a};
            descriptor.needClearColor = true;
            descriptor.needColorAttachment = true;
            descriptor.colorAttachmentsTexture[0] = _renderPassDescriptor.colorAttachmentsTexture[0];
        }
        if (flags & ClearFlag::DEPTH)
        {
            descriptor.clearDepthValue = depth;
            descriptor.needClearDepth = true;
            descriptor.depthTestEnabled = true;
            descriptor.depthAttachmentTexture = _renderPassDescriptor.depthAttachmentTexture;
        }
        if (flags & ClearFlag::STENCIL)
        {
            descriptor.clearStencilValue = stencil;
            descriptor.needClearStencil = true;
            descriptor.stencilTestEnabled = true;
            descriptor.stencilAttachmentTexture = _renderPassDescriptor.stencilAttachmentTexture;
        }

        _commandBuffer->beginRenderPass(descriptor);
        _commandBuffer->endRenderPass();

        delete command;
    };
    addCommand(command);
}

Texture2D* Renderer::getColorAttachment() const
{
    return _colorAttachment;
}

Texture2D* Renderer::getDepthAttachment() const
{
    return _depthAttachment;
}

Texture2D* Renderer::getStencilAttachment() const
{
    return _stencilAttachment;
}

const Color4F& Renderer::getClearColor() const
{
    return _clearColor;
}

float Renderer::getClearDepth() const
{
    return _renderPassDescriptor.clearDepthValue;
}

unsigned int Renderer::getClearStencil() const
{
    return _renderPassDescriptor.clearStencilValue;
}

ClearFlag Renderer::getClearFlag() const
{
    return _clearFlag;
}

RenderTargetFlag Renderer::getRenderTargetFlag() const
{
    return _renderTargetFlag;
}

void Renderer::setScissorTest(bool enabled)
{
    _scissorState.isEnabled = enabled;
}

bool Renderer::getScissorTest() const
{
    return _scissorState.isEnabled;
}

const ScissorRect& Renderer::getScissorRect() const
{
    return _scissorState.rect;
}

void Renderer::setScissorRect(float x, float y, float width, float height)
{
    _scissorState.rect.x = x;
    _scissorState.rect.y = y;
    _scissorState.rect.width = width;
    _scissorState.rect.height = height;
}

// TriangleCommandBufferManager
Renderer::TriangleCommandBufferManager::~TriangleCommandBufferManager()
{
    for (auto& vertexBuffer : _vertexBufferPool)
        vertexBuffer->release();

    for (auto& indexBuffer : _indexBufferPool)
        indexBuffer->release();
}

void Renderer::TriangleCommandBufferManager::init()
{
    createBuffer();
}

void Renderer::TriangleCommandBufferManager::putbackAllBuffers()
{
    _currentBufferIndex = 0;
}

void Renderer::TriangleCommandBufferManager::prepareNextBuffer()
{
    if (_currentBufferIndex < (int)_vertexBufferPool.size() - 1)
    {
        ++_currentBufferIndex;
        return;
    }

    createBuffer();
    ++_currentBufferIndex;
}

backend::Buffer* Renderer::TriangleCommandBufferManager::getVertexBuffer() const
{
    return _vertexBufferPool[_currentBufferIndex];
}

backend::Buffer* Renderer::TriangleCommandBufferManager::getIndexBuffer() const
{
    return _indexBufferPool[_currentBufferIndex];
}

void Renderer::TriangleCommandBufferManager::createBuffer()
{
    auto device = backend::Device::getInstance();

#ifdef CC_USE_METAL
    // Metal doesn't need to update buffer to make sure it has the correct size.
    auto vertexBuffer = device->newBuffer(Renderer::VBO_SIZE * sizeof(_verts[0]), backend::BufferType::VERTEX, backend::BufferUsage::DYNAMIC);
    if (!vertexBuffer)
        return;

    auto indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE * sizeof(_indices[0]), backend::BufferType::INDEX, backend::BufferUsage::DYNAMIC);
    if (!indexBuffer)
    {
        vertexBuffer->release();
        return;
    }
#else
    auto tmpData = malloc(Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F));
    if (!tmpData)
        return;

    auto vertexBuffer = device->newBuffer(Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F), backend::BufferType::VERTEX, backend::BufferUsage::DYNAMIC);
    if (!vertexBuffer)
    {
        free(tmpData);
        return;
    }
    vertexBuffer->updateData(tmpData, Renderer::VBO_SIZE * sizeof(V3F_C4B_T2F));

    auto indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE * sizeof(unsigned short), backend::BufferType::INDEX, backend::BufferUsage::DYNAMIC);
    if (! indexBuffer)
    {
        free(tmpData);
        vertexBuffer->release();
        return;
    }
    indexBuffer->updateData(tmpData, Renderer::INDEX_VBO_SIZE * sizeof(unsigned short));

    free(tmpData);
#endif

    _vertexBufferPool.push_back(vertexBuffer);
    _indexBufferPool.push_back(indexBuffer);
}

void Renderer::pushStateBlock()
{
    StateBlock block;
    block.depthTest = getDepthTest();
    block.depthWrite = getDepthWrite();
    block.cullMode = getCullMode();
    _stateBlockStack.emplace_back(block);
}

void Renderer::popStateBlock()
{
    auto & block = _stateBlockStack.back();
    setDepthTest(block.depthTest);
    setDepthWrite(block.depthWrite);
    setCullMode(block.cullMode);
    _stateBlockStack.pop_back();
}

NS_CC_END
