/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "renderer/CCQuadCommand.h"
#include "renderer/CCBatchCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCScissorCommand.h"
#include "renderer/CCStencilCommand.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "2d/CCCamera.h"
#include "2d/CCScene.h"

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
    std::sort(std::begin(_commands[QUEUE_GROUP::TRANSPARENT_3D]), std::end(_commands[QUEUE_GROUP::TRANSPARENT_3D]), compare3DCommand);
    std::sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_NEG]), std::end(_commands[QUEUE_GROUP::GLOBALZ_NEG]), compareRenderCommand);
    std::sort(std::begin(_commands[QUEUE_GROUP::GLOBALZ_POS]), std::end(_commands[QUEUE_GROUP::GLOBALZ_POS]), compareRenderCommand);
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
    _commands.clear();
    for(int index = 0; index < QUEUE_COUNT; ++index)
        _commands.emplace_back(std::vector<RenderCommand*>());
}

void RenderQueue::saveRenderState()
{
    _isDepthEnabled = glIsEnabled(GL_DEPTH_TEST) != GL_FALSE;
    _isCullEnabled = glIsEnabled(GL_CULL_FACE) != GL_FALSE;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &_isDepthWrite);
    
    CHECK_GL_ERROR_DEBUG();
}

void RenderQueue::restoreRenderState()
{
    if (_isCullEnabled)
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
    
    
    if (_isDepthEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    
    glDepthMask(_isDepthWrite);
    
    CHECK_GL_ERROR_DEBUG();
}

//
//
//
static const int DEFAULT_RENDER_QUEUE = 0;

//
// constructors, destructors, init
//
Renderer::Renderer()
    :_lastMaterialID(0)
    ,_lastBatchedMeshCommand(nullptr)
    ,_glViewAssigned(false)
    ,_isRendering(false)
    ,_isDepthTestFor2D(false)
{
    _groupCommandManager = new (std::nothrow) GroupCommandManager();
    
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _batchQuadCommands.reserve(BATCH_QUADCOMMAND_RESERVE_SIZE);

    // default clear color
    _clearColor = Color4F::BLACK;
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
  
    CC_SAFE_RELEASE(_vao);
    CC_SAFE_RELEASE(_vbo);
    CC_SAFE_RELEASE(_ibo);
}

void Renderer::initGLView()
{
    initBuffers();
}

void Renderer::initBuffers()
{
    _vao = VertexData::create(VertexData::Primitive::Triangles);
    _vbo = VertexBuffer::create(sizeof(V3F_C4B_T2F), VBO_SIZE, VertexBuffer::ArrayType::All, VertexBuffer::ArrayMode::Dynamic);
    _ibo = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, INDEX_VBO_SIZE, IndexBuffer::ArrayType::All);
    _vao->setIndexBuffer(_ibo);
    
    _vao->addStream(_vbo, VertexAttribute(offsetof(V3F_C4B_T2F, vertices),  GLProgram::VERTEX_ATTRIB_POSITION,  DataType::Float, 3));
    _vao->addStream(_vbo, VertexAttribute(offsetof(V3F_C4B_T2F, colors),    GLProgram::VERTEX_ATTRIB_COLOR,     DataType::UByte, 4, true));
    _vao->addStream(_vbo, VertexAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, DataType::Float, 2));
    
    CC_SAFE_RETAIN(_vao);
    CC_SAFE_RETAIN(_vbo);
    CC_SAFE_RETAIN(_ibo);

    // pre setup index data for quads
    auto indices = _ibo->getElementsOfType<uint16_t>();
    for( int i=0; i < VBO_SIZE/4; i++)
    {
        indices[i*6+0] = (GLushort) (i*4+0);
        indices[i*6+1] = (GLushort) (i*4+1);
        indices[i*6+2] = (GLushort) (i*4+2);
        indices[i*6+3] = (GLushort) (i*4+3);
        indices[i*6+4] = (GLushort) (i*4+2);
        indices[i*6+5] = (GLushort) (i*4+1);
    }
    
    _glViewAssigned = true;
}

void Renderer::addCommand(RenderCommand* command)
{
    int renderQueue =_commandGroupStack.top();
    addCommand(command, renderQueue);
}

void Renderer::addCommand(RenderCommand* command, int renderQueue)
{
    CCASSERT(!_isRendering, "Cannot add command while rendering");
    CCASSERT(renderQueue >=0, "Invalid render queue");
    CCASSERT(command->getType() != RenderCommand::Type::UNKNOWN_COMMAND, "Invalid Command Type");

    _renderGroups[renderQueue].push_back(command);
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
    if ( RenderCommand::Type::QUAD_COMMAND == commandType )
    {
        //Draw if we have batched other commands which are not quad command
        flush3D();
        
        //Process quad command
        auto cmd = static_cast<QuadCommand*>(command);
        const auto numberQuads = 2 * _vbo->getElementCount();
        
        //Draw batched quads if necessary
        if(cmd->isSkipBatching()|| (numberQuads + cmd->getQuadCount()) * 4 > VBO_SIZE )
        {
            CCASSERT(cmd->getQuadCount()>= 0 && cmd->getQuadCount() * 4 < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
            //Draw batched quads if VBO is full
            drawBatchedQuads();
        }
        
        //Batch Quads
        _batchQuadCommands.push_back(cmd);
        
        insertQuads(cmd);
        
        if(cmd->isSkipBatching())
        {
            drawBatchedQuads();
        }
    }
    else if (RenderCommand::Type::MESH_COMMAND == commandType)
    {
        flush2D();
        auto cmd = static_cast<MeshCommand*>(command);
        
        if (cmd->isSkipBatching() || _lastBatchedMeshCommand == nullptr || _lastBatchedMeshCommand->getMaterialID() != cmd->getMaterialID())
        {
            flush3D();
            
            if(cmd->isSkipBatching())
            {
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
            cmd->batchDraw();
        }
    }
    else if(RenderCommand::Type::GROUP_COMMAND == commandType)
    {
        flush();
        int renderQueueID = ((GroupCommand*) command)->getRenderQueueID();
        visitRenderQueue(_renderGroups[renderQueueID]);
    }
    else if(RenderCommand::Type::CUSTOM_COMMAND == commandType)
    {
        flush();
        auto cmd = static_cast<CustomCommand*>(command);
        cmd->execute();
    }
    else if(RenderCommand::Type::BATCH_COMMAND == commandType)
    {
        flush();
        auto cmd = static_cast<BatchCommand*>(command);
        cmd->execute();
    }
    else if(RenderCommand::Type::BEGIN_SCISSOR_COMMAND == commandType)
    {
        flush();
        command->execute<BeginScissorCommand>();
    }
    else if(RenderCommand::Type::END_SCISSOR_COMMAND == commandType)
    {
        flush();
        command->execute<EndScissorCommand>();
    }
    else if(RenderCommand::Type::BEGIN_STENCIL_COMMAND == commandType)
    {
        flush();
        command->execute<BeginStencilCommand>();
    }
    else if(RenderCommand::Type::AFTER_STENCIL_COMMAND == commandType)
    {
        flush();
        command->execute<AfterStencilCommand>();
    }
    else if(RenderCommand::Type::END_STENCIL_COMMAND == commandType)
    {
        flush();
        command->execute<EndStencilCommand>();
    }
    else
    {
        CCLOGERROR("Unknown commands in renderQueue");
    }
}

void Renderer::visitRenderQueue(RenderQueue& queue)
{
    queue.saveRenderState();
    
    //
    //Process Global-Z < 0 Objects
    //
    const auto& zNegQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_NEG);
    if (zNegQueue.size() > 0)
    {
        if(_isDepthTestFor2D)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthMask(true);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
        }
        for (auto it = zNegQueue.cbegin(); it != zNegQueue.cend(); ++it)
        {
            processRenderCommand(*it);
        }
        flush();
    }
    
    //
    //Process Opaque Object
    //
    const auto& opaqueQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::OPAQUE_3D);
    if (opaqueQueue.size() > 0)
    {
        //Clear depth to achieve layered rendering
        glDepthMask(true);
        glEnable(GL_DEPTH_TEST);
        
        for (auto it = opaqueQueue.cbegin(); it != opaqueQueue.cend(); ++it)
        {
            processRenderCommand(*it);
        }
        flush();
    }
    
    //
    //Process 3D Transparent object
    //
    const auto& transQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::TRANSPARENT_3D);
    if (transQueue.size() > 0)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(false);
        
        for (auto it = transQueue.cbegin(); it != transQueue.cend(); ++it)
        {
            processRenderCommand(*it);
        }
        flush();
    }
    
    //
    //Process Global-Z = 0 Queue
    //
    const auto& zZeroQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_ZERO);
    if (zZeroQueue.size() > 0)
    {
        if(_isDepthTestFor2D)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthMask(true);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
        }
        for (auto it = zZeroQueue.cbegin(); it != zZeroQueue.cend(); ++it)
        {
            processRenderCommand(*it);
        }
        flush();
    }
    
    //
    //Process Global-Z > 0 Queue
    //
    const auto& zPosQueue = queue.getSubQueue(RenderQueue::QUEUE_GROUP::GLOBALZ_POS);
    if (zPosQueue.size() > 0)
    {
        for (auto it = zPosQueue.cbegin(); it != zPosQueue.cend(); ++it)
        {
            processRenderCommand(*it);
        }
        flush();
    }
    
    queue.restoreRenderState();
}

void Renderer::render()
{
    //Uncomment this once everything is rendered by new renderer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //TODO: setup camera or MVP
    _isRendering = true;
    
    if (_glViewAssigned)
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

void Renderer::clean()
{
    // Clear render group
    for (size_t j = 0 ; j < _renderGroups.size(); j++)
        _renderGroups[j].clear();

    // Clear batch commands
    _batchQuadCommands.clear();
    _vao->clear();
    _lastMaterialID = 0;
    _lastBatchedMeshCommand = nullptr;
}

void Renderer::clear()
{
    //Enable Depth mask to make sure glClear clear the depth buffer correctly
    glDepthMask(true);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);
}

void Renderer::setDepthTest(bool enable)
{
    if (enable)
    {
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    
    _isDepthTestFor2D = enable;
    CHECK_GL_ERROR_DEBUG();
}

void Renderer::insertQuads(const QuadCommand* cmd)
{
    auto verts = _vbo->getElementsOfType<V3F_C4B_T2F>();
    
    const auto currentVertex = _vbo->getElementCount();
    const auto currentIndex  = _ibo->getElementCount();

    const auto count = 4 * cmd->getQuadCount();
    memcpy(verts + currentVertex, (void*)cmd->getQuads(), count * sizeof(V3F_C4B_T2F));
    _vbo->setElementCount(currentVertex + count);
    _ibo->setElementCount(currentIndex + 6 * cmd->getQuadCount());
    
    const Mat4& modelView = cmd->getModelView();
    
    auto p = verts + currentVertex;
    for (auto i = 0; i < count; ++i, ++p)
    {
        modelView.transformPoint(&p->vertices);
    }
}

void Renderer::drawBatchedQuads()
{
    int indexToDraw = 0;
    int startIndex = 0;
    
    //Start drawing verties in batch
    for (const auto& cmd : _batchQuadCommands)
    {
        auto newMaterialID = cmd->getMaterialID();
        if(_lastMaterialID != newMaterialID || newMaterialID == MATERIAL_ID_DO_NOT_BATCH)
        {
            //Draw quads
            if (indexToDraw > 0)
            {
                _vao->draw(startIndex, indexToDraw);
                _drawnBatches++;
                _drawnVertices += indexToDraw;
                
                startIndex += indexToDraw;
                indexToDraw = 0;
            }
            
            //Use new material
            cmd->useMaterial();
            _lastMaterialID = newMaterialID;
        }
        
        indexToDraw += cmd->getQuadCount() * 6;
    }
    
    //Draw any remaining quad
    if (indexToDraw > 0)
    {
        _vao->draw(startIndex, indexToDraw);
        _drawnBatches++;
        _drawnVertices += indexToDraw;
    }

    _vao->clear();
    _batchQuadCommands.clear();
}

void Renderer::flush()
{
    flush2D();
    flush3D();
}

void Renderer::flush2D()
{
    if (!_vao->empty())
    {
        drawBatchedQuads();
        _lastMaterialID = 0;
    }
}

void Renderer::flush3D()
{
    if (_lastBatchedMeshCommand)
    {
        _lastBatchedMeshCommand->postBatchDraw();
        _lastBatchedMeshCommand = nullptr;
    }
}

// helpers
bool Renderer::checkVisibility(const Mat4 &transform, const Size &size)
{
    auto scene = Director::getInstance()->getRunningScene();
    // only cull the default camera. The culling algorithm is valid for default camera.
    if (scene && scene->_defaultCamera != Camera::getVisitingCamera())
        return true;
    
    // half size of the screen
    Size screen_half = Director::getInstance()->getWinSize();
    screen_half.width /= 2;
    screen_half.height /= 2;

    float hSizeX = size.width/2;
    float hSizeY = size.height/2;

    Vec4 v4world, v4local;
    v4local.set(hSizeX, hSizeY, 0, 1);
    transform.transformVector(v4local, &v4world);

    // center of screen is (0,0)
    v4world.x -= screen_half.width;
    v4world.y -= screen_half.height;

    // convert content size to world coordinates
    float wshw = std::max(fabsf(hSizeX * transform.m[0] + hSizeY * transform.m[4]), fabsf(hSizeX * transform.m[0] - hSizeY * transform.m[4]));
    float wshh = std::max(fabsf(hSizeX * transform.m[1] + hSizeY * transform.m[5]), fabsf(hSizeX * transform.m[1] - hSizeY * transform.m[5]));

    // compare if it in the positive quadrant of the screen
    float tmpx = (fabsf(v4world.x)-wshw);
    float tmpy = (fabsf(v4world.y)-wshh);
    bool ret = (tmpx < screen_half.width && tmpy < screen_half.height);

    return ret;
}


void Renderer::setClearColor(const Color4F &clearColor)
{
    _clearColor = clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

NS_CC_END
