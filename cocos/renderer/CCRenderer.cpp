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
//#include "renderer/CCRenderState.h"

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

//void RenderQueue::saveRenderState()
//{
//    _isDepthEnabled = glIsEnabled(GL_DEPTH_TEST) != GL_FALSE;
//    _isCullEnabled = glIsEnabled(GL_CULL_FACE) != GL_FALSE;
//    glGetBooleanv(GL_DEPTH_WRITEMASK, &_isDepthWrite);
//
//    CHECK_GL_ERROR_DEBUG();
//}
//
//void RenderQueue::restoreRenderState()
//{
//    if (_isCullEnabled)
//    {
//        glEnable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setCullFace(true);
//    }
//    else
//    {
//        glDisable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setCullFace(false);
//    }
//
//    if (_isDepthEnabled)
//    {
//        glEnable(GL_DEPTH_TEST);
//        RenderState::StateBlock::_defaultState->setDepthTest(true);
//    }
//    else
//    {
//        glDisable(GL_DEPTH_TEST);
//        RenderState::StateBlock::_defaultState->setDepthTest(false);
//    }
//
//    glDepthMask(_isDepthWrite);
//    RenderState::StateBlock::_defaultState->setDepthWrite(_isDepthEnabled);
//
//    CHECK_GL_ERROR_DEBUG();
//}

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

    _verts = malloc(Renderer::VBO_SIZE);
    _indices = malloc(Renderer::INDEX_VBO_SIZE);
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
    
    free(_triBatchesToDraw);
    free(_verts);
    free(_indices);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_cacheTextureListener);
#endif
    
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_defaultRenderPass);
}

void Renderer::init()
{
    auto device = backend::Device::getInstance();
    _vertexBuffer = device->newBuffer(Renderer::VBO_SIZE, backend::BufferType::VERTEX, backend::BufferUsage::READ);
    _indexBuffer = device->newBuffer(Renderer::INDEX_VBO_SIZE, backend::BufferType::INDEX, backend::BufferUsage::READ);
    _commandBuffer = device->newCommandBuffer();
    createDefaultRenderPass();
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
    if( RenderCommand::Type::TRIANGLES_COMMAND == commandType)
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
        _filledIndex += cmd->getIndexCount();
        _filledVertex += cmd->getVertexCount();
    }
    else if (RenderCommand::Type::MESH_COMMAND == commandType)
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
    else if(RenderCommand::Type::GROUP_COMMAND == commandType)
    {
        flush();
        auto tmpRenderPass = _currentRenderPass;
        _currentRenderPass = createRenderPass(command);
        _viewPortStack.push({command->getViewPort()});
        int renderQueueID = ((GroupCommand*) command)->getRenderQueueID();
//        CCGL_DEBUG_PUSH_GROUP_MARKER("RENDERER_GROUP_COMMAND");
        visitRenderQueue(_renderGroups[renderQueueID]);
        _viewPortStack.pop();
        _currentRenderPass->release();
        _currentRenderPass = tmpRenderPass;
//        CCGL_DEBUG_POP_GROUP_MARKER();
    }
    else if(RenderCommand::Type::CUSTOM_COMMAND == commandType)
    {
        flush();
        drawCustomCommand(command);
//        auto cmd = static_cast<CustomCommand*>(command);
////        CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_CUSTOM_COMMAND");
//        cmd->execute();
    }
    else if(RenderCommand::Type::BATCH_COMMAND == commandType)
    {
        flush();
        drawBatchedCommand(command);
//        auto cmd = static_cast<BatchCommand*>(command);
//        CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_BATCH_COMMAND");
//        cmd->execute();
    }
    else if(RenderCommand::Type::PRIMITIVE_COMMAND == commandType)
    {
        flush();
        auto cmd = static_cast<PrimitiveCommand*>(command);
//        CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_PRIMITIVE_COMMAND");
        cmd->execute();
    }
    else
    {
        CCLOGERROR("Unknown commands in renderQueue");
    }
}

void Renderer::visitRenderQueue(RenderQueue& queue)
{
    //todo: minggo
//    queue.saveRenderState();
    
    //
    //Process Global-Z < 0 Objects
    //
//    const auto& zNegQueue = queue.getSubQueue(RenderQueueBackend::QUEUE_GROUP::GLOBALZ_NEG);
//    if (zNegQueue.size() > 0)
//    {
//        if(_isDepthTestFor2D)
//        {
//            glEnable(GL_DEPTH_TEST);
//            glDepthMask(true);
//            glEnable(GL_BLEND);
//            RenderState::StateBlock::_defaultState->setDepthTest(true);
//            RenderState::StateBlock::_defaultState->setDepthWrite(true);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        else
//        {
//            glDisable(GL_DEPTH_TEST);
//            glDepthMask(false);
//            glEnable(GL_BLEND);
//            RenderState::StateBlock::_defaultState->setDepthTest(false);
//            RenderState::StateBlock::_defaultState->setDepthWrite(false);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        glDisable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setCullFace(false);
//
//        for (const auto& zNegNext : zNegQueue)
//        {
//            processRenderCommand(zNegNext);
//        }
//        flush();
//    }
    
    //
    //Process Opaque Object
    //
//    const auto& opaqueQueue = queue.getSubQueue(RenderQueueBackend::QUEUE_GROUP::OPAQUE_3D);
//    if (opaqueQueue.size() > 0)
//    {
//        //Clear depth to achieve layered rendering
//        glEnable(GL_DEPTH_TEST);
//        glDepthMask(true);
//        glDisable(GL_BLEND);
//        glEnable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setDepthTest(true);
//        RenderState::StateBlock::_defaultState->setDepthWrite(true);
//        RenderState::StateBlock::_defaultState->setBlend(false);
//        RenderState::StateBlock::_defaultState->setCullFace(true);
//
//        for (const auto& opaqueNext : opaqueQueue)
//        {
//            processRenderCommand(opaqueNext);
//        }
//        flush();
//    }
    
    //
    //Process 3D Transparent object
    //
//    const auto& transQueue = queue.getSubQueue(RenderQueueBackend::QUEUE_GROUP::TRANSPARENT_3D);
//    if (transQueue.size() > 0)
//    {
//        glEnable(GL_DEPTH_TEST);
//        glDepthMask(false);
//        glEnable(GL_BLEND);
//        glEnable(GL_CULL_FACE);
//
//        RenderState::StateBlock::_defaultState->setDepthTest(true);
//        RenderState::StateBlock::_defaultState->setDepthWrite(false);
//        RenderState::StateBlock::_defaultState->setBlend(true);
//        RenderState::StateBlock::_defaultState->setCullFace(true);
//
//
//        for (const auto& transNext : transQueue)
//        {
//            processRenderCommand(transNext);
//        }
//        flush();
//    }
    
    //
    //Process Global-Z = 0 Queue
    //
    const auto& zZeroQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO);
    if (zZeroQueue.size() > 0)
    {
//        if(_isDepthTestFor2D)
//        {
//            glEnable(GL_DEPTH_TEST);
//            glDepthMask(true);
//            glEnable(GL_BLEND);
//
//            RenderState::StateBlock::_defaultState->setDepthTest(true);
//            RenderState::StateBlock::_defaultState->setDepthWrite(true);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        else
//        {
//            glDisable(GL_DEPTH_TEST);
//            glDepthMask(false);
//            glEnable(GL_BLEND);
//
//            RenderState::StateBlock::_defaultState->setDepthTest(false);
//            RenderState::StateBlock::_defaultState->setDepthWrite(false);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        glDisable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setCullFace(false);
        
        for (const auto& zZeroNext : zZeroQueue)
        {
            processRenderCommand(zZeroNext);
        }
        flush();
    }
    
    //
    //Process Global-Z > 0 Queue
    //
//    const auto& zPosQueue = queue.getSubQueue(RenderQueueBackend::QUEUE_GROUP::GLOBALZ_POS);
//    if (zPosQueue.size() > 0)
//    {
//        if(_isDepthTestFor2D)
//        {
//            glEnable(GL_DEPTH_TEST);
//            glDepthMask(true);
//            glEnable(GL_BLEND);
//
//            RenderState::StateBlock::_defaultState->setDepthTest(true);
//            RenderState::StateBlock::_defaultState->setDepthWrite(true);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        else
//        {
//            glDisable(GL_DEPTH_TEST);
//            glDepthMask(false);
//            glEnable(GL_BLEND);
//
//            RenderState::StateBlock::_defaultState->setDepthTest(false);
//            RenderState::StateBlock::_defaultState->setDepthWrite(false);
//            RenderState::StateBlock::_defaultState->setBlend(true);
//        }
//        glDisable(GL_CULL_FACE);
//        RenderState::StateBlock::_defaultState->setCullFace(false);
//
//        for (const auto& zPosNext : zPosQueue)
//        {
//            processRenderCommand(zPosNext);
//        }
//        flush();
//    }
    
//    queue.restoreRenderState();
}

void Renderer::render()
{
    //Uncomment this once everything is rendered by new renderer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    _currentRenderPass = nullptr;
    _isRendering = false;
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
    _filledVertex = 0;
    _filledIndex = 0;
    _lastBatchedMeshCommand = nullptr;
}

void Renderer::clear()
{
    _currentRenderPass = _defaultRenderPass;
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
    // memcpy(&_verts[_filledVertex], cmd->getVertices(), sizeof(V3F_C4B_T2F) * cmd->getVertexCount());

    // // fill vertex, and convert them to world coordinates
    // const Mat4& modelView = cmd->getModelView();
    // for(ssize_t i=0; i < cmd->getVertexCount(); ++i)
    // {
    //     modelView.transformPoint(&(_verts[i + _filledVertex].vertices));
    // }

    // // fill index
    // const unsigned short* indices = cmd->getIndices();
    // for(ssize_t i=0; i< cmd->getIndexCount(); ++i)
    // {
    //     _indices[_filledIndex + i] = _filledVertex + indices[i];
    // }

    // _filledVertex += cmd->getVertexCount();
    // _filledIndex += cmd->getIndexCount();

    _filledVertex += cmd->copyVertexData((char*)_verts + _filledVertex);
    _filledIndex += cmd->copyIndexData((char*)_indices + _filledIndex);
}

void Renderer::drawBatchedTriangles()
{
    if(_queuedTriangleCommands.empty())
        return;
    
    _filledVertex = 0;
    _filledIndex = 0;
    
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
                    _triBatchesToDraw[batchesTotal-1].offset + _triBatchesToDraw[batchesTotal-1].indicesToDraw * _triBatchesToDraw[batchesTotal-1].cmd->getIndexSize();
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
    
    // _vertexBuffer->updateData(_verts, sizeof(_verts[0]) * _filledVertex);
    // _indexBuffer->updateData(_indices, sizeof(_indices[0]) * _filledIndex);

    _vertexBuffer->updateData(_verts, _filledVertex);
    _indexBuffer->updateData(_indices, _filledIndex);
    
    /************** 2: Draw *************/
    _commandBuffer->beginRenderPass(_currentRenderPass);
    
    for (int i = 0; i < batchesTotal; ++i)
    {
        auto& pipelineDescriptor = _triBatchesToDraw[i].cmd->getPipelineDescriptor();
        auto renderPipeline = createRenderPipeline(pipelineDescriptor);
        _commandBuffer->setRenderPipeline(renderPipeline);
        renderPipeline->release();
        
        if (_viewPortStack.empty())
        {
            auto& viewPort = _triBatchesToDraw[i].cmd->getViewPort();
            _commandBuffer->setViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
        }
        else
        {
            auto& viewPort = _viewPortStack.top();
            _commandBuffer->setViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
        }
        
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setIndexBuffer(_indexBuffer);
        _commandBuffer->setBindGroup(&pipelineDescriptor.bindGroup);
        _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                     backend::IndexFormat::U_SHORT, _triBatchesToDraw[i].indicesToDraw,
                                     _triBatchesToDraw[i].offset);
    }
    
    _commandBuffer->endRenderPass();
    
    /************** 3: Cleanup *************/
    _queuedTriangleCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
}

void Renderer::drawBatchedCommand(RenderCommand* command)
{
    auto cmd = static_cast<BatchCommand*>(command);
    
//    fillVerticesAndIndices(cmd);
    V3F_C4B_T2F_Quad* quad = cmd->getQuad();
    unsigned short* indices = cmd->getIndices();
    uint32_t quadSize = sizeof(quad[0]) * cmd->getQuadCount();
    uint32_t indexCount = cmd->getQuadCount() * 6;
    uint32_t indexSize = sizeof(indices[0]) * indexCount;
    
    _vertexBuffer->updateData(quad, quadSize);
    _indexBuffer->updateData(indices, indexSize);
    
    /************** 2: Draw *************/
    _commandBuffer->beginRenderPass(_currentRenderPass);
    auto& pipelineDescriptor = cmd->getPipelineDescriptor();
    auto renderPipeline = createRenderPipeline(pipelineDescriptor);
    _commandBuffer->setRenderPipeline(renderPipeline);
    renderPipeline->release();
    
    auto viewPort = cmd->getViewPort();
    _commandBuffer->setViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
    
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _commandBuffer->setIndexBuffer(_indexBuffer);
    _commandBuffer->setBindGroup(&pipelineDescriptor.bindGroup);
    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                 backend::IndexFormat::U_SHORT, indexCount,
                                 0);
    
    _commandBuffer->endRenderPass();
}

void Renderer::drawCustomCommand(RenderCommand *command)
{
    auto cmd = static_cast<CustomCommand*>(command);
    
    //    fillVerticesAndIndices(cmd);
    V3F_C4B_T2F_Quad* quad = cmd->getQuad();
    unsigned short* indices = cmd->getIndices();
    uint32_t quadSize = sizeof(quad[0]) * cmd->getQuadCount();
    uint32_t indexCount = cmd->getQuadCount() * 6;
    uint32_t indexSize = sizeof(indices[0]) * indexCount;
    
    _vertexBuffer->updateData(quad, quadSize);
    _indexBuffer->updateData(indices, indexSize);
    
    /************** 2: Draw *************/
    _commandBuffer->beginRenderPass(_currentRenderPass);
    auto& pipelineDescriptor = cmd->getPipelineDescriptor();
    auto renderPipeline = createRenderPipeline(pipelineDescriptor);
    _commandBuffer->setRenderPipeline(renderPipeline);
    renderPipeline->release();
    
    auto viewPort = cmd->getViewPort();
    _commandBuffer->setViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
    
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _commandBuffer->setIndexBuffer(_indexBuffer);
    _commandBuffer->setBindGroup(&pipelineDescriptor.bindGroup);
    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                 backend::IndexFormat::U_SHORT, indexCount,
                                 0);
    
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
//        CCGL_DEBUG_INSERT_EVENT_MARKER("RENDERER_BATCH_MESH");

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
    createDefaultRenderPass();
}

backend::RenderPipeline* Renderer::createRenderPipeline(const PipelineDescriptor& pipelineDescriptor)
{
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.setVertexShaderModule(pipelineDescriptor.vertexShader);
    renderPipelineDescriptor.setFragmentShaderModule(pipelineDescriptor.fragmentShader);
    renderPipelineDescriptor.setVertexLayout(0, pipelineDescriptor.vertexLayout);
    
    auto device = backend::Device::getInstance();
    auto blendState = device->createBlendState(pipelineDescriptor.blendDescriptor);
    renderPipelineDescriptor.setBlendState(blendState);
    
    auto& depthStencilDescritpor = pipelineDescriptor.depthStencilDescriptor;
    if (depthStencilDescritpor.depthTestEnabled || depthStencilDescritpor.stencilTestEnabled)
    {
        auto depthStencilState = device->createDepthStencilState(pipelineDescriptor.depthStencilDescriptor);
        renderPipelineDescriptor.setDepthStencilState(depthStencilState);
    }
    
    auto renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
    return renderPipeline;
}

backend::RenderPass* Renderer::createRenderPass(RenderCommand* cmd)
{
    auto& renderpassDescriptor = cmd->getPipelineDescriptor().renderPassDescriptor;
    return backend::Device::getInstance()->newRenderPass(renderpassDescriptor);
}

void Renderer::createDefaultRenderPass()
{
    CC_SAFE_RELEASE(_defaultRenderPass);
    backend::RenderPassDescriptor descriptor;
    descriptor.setClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    descriptor.setClearDepth(0);
    _defaultRenderPass = backend::Device::getInstance()->newRenderPass(descriptor);
}

NS_CC_END
