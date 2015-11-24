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

#include "renderer/CCTrianglesCommand.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCBatchCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/CCPrimitiveCommand.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCRenderState.h"
#include "renderer/ccGLStateCache.h"

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
        RenderState::StateBlock::_defaultState->setCullFace(true);
    }
    else
    {
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
    }
    
    
    if (_isDepthEnabled)
    {
        glEnable(GL_DEPTH_TEST);
        RenderState::StateBlock::_defaultState->setDepthTest(true);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        RenderState::StateBlock::_defaultState->setDepthTest(false);
    }
    
    glDepthMask(_isDepthWrite);
    RenderState::StateBlock::_defaultState->setDepthWrite(_isDepthEnabled);

    CHECK_GL_ERROR_DEBUG();
}

//
//
//
static const int DEFAULT_RENDER_QUEUE = 0;

//
// constructors, destructor, init
//
Renderer::Renderer()
:_lastMaterialID(0)
,_lastBatchedMeshCommand(nullptr)
,_filledVertex(0)
,_filledIndex(0)
,_numberQuads(0)
,_glViewAssigned(false)
,_isRendering(false)
,_isDepthTestFor2D(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
,_cacheTextureListener(nullptr)
#endif
{
    _groupCommandManager = new (std::nothrow) GroupCommandManager();
    
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _batchedCommands.reserve(BATCH_QUADCOMMAND_RESEVER_SIZE);

    // default clear color
    _clearColor = Color4F::BLACK;
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
    
    glDeleteBuffers(2, _buffersVBO);
    glDeleteBuffers(2, _quadbuffersVBO);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_buffersVAO);
        glDeleteVertexArrays(1, &_quadVAO);
        GL::bindVAO(0);
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_cacheTextureListener);
#endif
}

void Renderer::initGLView()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _cacheTextureListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        this->setupBuffer();
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_cacheTextureListener, -1);
#endif
    
    //setup index data for quads
    
    for( int i=0; i < VBO_SIZE/4; i++)
    {
        _quadIndices[i*6+0] = (GLushort) (i*4+0);
        _quadIndices[i*6+1] = (GLushort) (i*4+1);
        _quadIndices[i*6+2] = (GLushort) (i*4+2);
        _quadIndices[i*6+3] = (GLushort) (i*4+3);
        _quadIndices[i*6+4] = (GLushort) (i*4+2);
        _quadIndices[i*6+5] = (GLushort) (i*4+1);
    }
    
    setupBuffer();
    
    _glViewAssigned = true;
}

void Renderer::setupBuffer()
{
    if(Configuration::getInstance()->supportsShareableVAO())
    {
        setupVBOAndVAO();
    }
    else
    {
        setupVBO();
    }
}

void Renderer::setupVBOAndVAO()
{
    //generate vbo and vao for trianglesCommand
    glGenVertexArrays(1, &_buffersVAO);
    GL::bindVAO(_buffersVAO);

    glGenBuffers(2, &_buffersVBO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);

    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //generate vbo and vao for quadCommand
    glGenVertexArrays(1, &_quadVAO);
    GL::bindVAO(_quadVAO);
    
    glGenBuffers(2, &_quadbuffersVBO[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, _quadbuffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVerts[0]) * VBO_SIZE, _quadVerts, GL_DYNAMIC_DRAW);
    
    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, vertices));
    
    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, colors));
    
    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadbuffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_quadIndices[0]) * INDEX_VBO_SIZE, _quadIndices, GL_STATIC_DRAW);
    
    // Must unbind the VAO before changing the element buffer.
    GL::bindVAO(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CHECK_GL_ERROR_DEBUG();
}

void Renderer::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);
    glGenBuffers(2, &_quadbuffersVBO[0]);
    mapBuffers();
}

void Renderer::mapBuffers()
{
    // Avoid changing the element buffer for whatever VAO might be bound.
    GL::bindVAO(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, _quadbuffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVerts[0]) * VBO_SIZE, _quadVerts, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadbuffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_quadIndices[0]) * INDEX_VBO_SIZE, _quadIndices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
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
    if( RenderCommand::Type::TRIANGLES_COMMAND == commandType)
    {
        //Draw if we have batched other commands which are not triangle command
        flush3D();
        flushQuads();
        
        //Process triangle command
        auto cmd = static_cast<TrianglesCommand*>(command);
        
        //Draw batched Triangles if necessary
        if(cmd->isSkipBatching() || _filledVertex + cmd->getVertexCount() > VBO_SIZE || _filledIndex + cmd->getIndexCount() > INDEX_VBO_SIZE)
        {
            CCASSERT(cmd->getVertexCount()>= 0 && cmd->getVertexCount() < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
            CCASSERT(cmd->getIndexCount()>= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE, "VBO for index is not big enough, please break the data down or use customized render command");
            //Draw batched Triangles if VBO is full
            drawBatchedTriangles();
        }
        
        //Batch Triangles
        _batchedCommands.push_back(cmd);
        
        fillVerticesAndIndices(cmd);
        
        if(cmd->isSkipBatching())
        {
            drawBatchedTriangles();
        }
        
    }
    else if ( RenderCommand::Type::QUAD_COMMAND == commandType )
    {
        //Draw if we have batched other commands which are not quad command
        flush3D();
        flushTriangles();
        
        //Process quad command
        auto cmd = static_cast<QuadCommand*>(command);
        
        //Draw batched quads if necessary
        if(cmd->isSkipBatching()|| (_numberQuads + cmd->getQuadCount()) * 4 > VBO_SIZE )
        {
            CCASSERT(cmd->getQuadCount()>= 0 && cmd->getQuadCount() * 4 < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
            //Draw batched quads if VBO is full
            drawBatchedQuads();
        }
        
        //Batch Quads
        _batchQuadCommands.push_back(cmd);
        
        fillQuads(cmd);
        
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
    else if(RenderCommand::Type::PRIMITIVE_COMMAND == commandType)
    {
        flush();
        auto cmd = static_cast<PrimitiveCommand*>(command);
        cmd->execute();
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
            glEnable(GL_BLEND);
            RenderState::StateBlock::_defaultState->setDepthTest(true);
            RenderState::StateBlock::_defaultState->setDepthWrite(true);
            RenderState::StateBlock::_defaultState->setBlend(true);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
            glEnable(GL_BLEND);
            RenderState::StateBlock::_defaultState->setDepthTest(false);
            RenderState::StateBlock::_defaultState->setDepthWrite(false);
            RenderState::StateBlock::_defaultState->setBlend(true);
        }
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
        
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
        glEnable(GL_DEPTH_TEST);
        glDepthMask(true);
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setDepthTest(true);
        RenderState::StateBlock::_defaultState->setDepthWrite(true);
        RenderState::StateBlock::_defaultState->setBlend(false);
        RenderState::StateBlock::_defaultState->setCullFace(true);


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
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);

        RenderState::StateBlock::_defaultState->setDepthTest(true);
        RenderState::StateBlock::_defaultState->setDepthWrite(false);
        RenderState::StateBlock::_defaultState->setBlend(true);
        RenderState::StateBlock::_defaultState->setCullFace(true);


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
            glEnable(GL_BLEND);

            RenderState::StateBlock::_defaultState->setDepthTest(true);
            RenderState::StateBlock::_defaultState->setDepthWrite(true);
            RenderState::StateBlock::_defaultState->setBlend(true);

        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
            glEnable(GL_BLEND);

            RenderState::StateBlock::_defaultState->setDepthTest(false);
            RenderState::StateBlock::_defaultState->setDepthWrite(false);
            RenderState::StateBlock::_defaultState->setBlend(true);

        }
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
        
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
        if(_isDepthTestFor2D)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthMask(true);
            glEnable(GL_BLEND);
            
            RenderState::StateBlock::_defaultState->setDepthTest(true);
            RenderState::StateBlock::_defaultState->setDepthWrite(true);
            RenderState::StateBlock::_defaultState->setBlend(true);
            
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
            glDepthMask(false);
            glEnable(GL_BLEND);
            
            RenderState::StateBlock::_defaultState->setDepthTest(false);
            RenderState::StateBlock::_defaultState->setDepthWrite(false);
            RenderState::StateBlock::_defaultState->setBlend(true);
            
        }
        glDisable(GL_CULL_FACE);
        RenderState::StateBlock::_defaultState->setCullFace(false);
        
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
    {
        //commands are owned by nodes
        // for (const auto &cmd : _renderGroups[j])
        // {
        //     cmd->releaseToCommandPool();
        // }
        _renderGroups[j].clear();
    }

    // Clear batch commands
    _batchedCommands.clear();
    _batchQuadCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
    _numberQuads = 0;
    _lastMaterialID = 0;
    _lastBatchedMeshCommand = nullptr;
}

void Renderer::clear()
{
    //Enable Depth mask to make sure glClear clear the depth buffer correctly
    glDepthMask(true);
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);

    RenderState::StateBlock::_defaultState->setDepthWrite(false);
}

void Renderer::setDepthTest(bool enable)
{
    if (enable)
    {
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        RenderState::StateBlock::_defaultState->setDepthTest(true);
        RenderState::StateBlock::_defaultState->setDepthFunction(RenderState::DEPTH_LEQUAL);

//        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);

        RenderState::StateBlock::_defaultState->setDepthTest(false);
    }

    _isDepthTestFor2D = enable;
    CHECK_GL_ERROR_DEBUG();
}

void Renderer::fillVerticesAndIndices(const TrianglesCommand* cmd)
{
    memcpy(_verts + _filledVertex, cmd->getVertices(), sizeof(V3F_C4B_T2F) * cmd->getVertexCount());
    const Mat4& modelView = cmd->getModelView();
    
    for(ssize_t i=0; i< cmd->getVertexCount(); ++i)
    {
        V3F_C4B_T2F *q = &_verts[i + _filledVertex];
        Vec3 *vec1 = (Vec3*)&q->vertices;
        modelView.transformPoint(vec1);
    }
    
    const unsigned short* indices = cmd->getIndices();
    //fill index
    for(ssize_t i=0; i< cmd->getIndexCount(); ++i)
    {
        _indices[_filledIndex + i] = _filledVertex + indices[i];
    }
    
    _filledVertex += cmd->getVertexCount();
    _filledIndex += cmd->getIndexCount();
}

void Renderer::fillQuads(const QuadCommand *cmd)
{
    const Mat4& modelView = cmd->getModelView();
    const V3F_C4B_T2F* quads =  (V3F_C4B_T2F*)cmd->getQuads();
    for(ssize_t i=0; i< cmd->getQuadCount() * 4; ++i)
    {
        _quadVerts[i + _numberQuads * 4] = quads[i];
        modelView.transformPoint(quads[i].vertices,&(_quadVerts[i + _numberQuads * 4].vertices));
    }
    
    _numberQuads += cmd->getQuadCount();
}

void Renderer::drawBatchedTriangles()
{
    //TODO: we can improve the draw performance by insert material switching command before hand.

    int indexToDraw = 0;
    int startIndex = 0;

    //Upload buffer to VBO
    if(_filledVertex <= 0 || _filledIndex <= 0 || _batchedCommands.empty())
    {
        return;
    }

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Bind VAO
        GL::bindVAO(_buffersVAO);
        //Set VBO data
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        // option 1: subdata
//        glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );

        // option 2: data
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);

        // option 3: orphaning + glMapBuffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex, nullptr, GL_DYNAMIC_DRAW);
        void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        memcpy(buf, _verts, sizeof(_verts[0])* _filledVertex);
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _filledIndex, _indices, GL_STATIC_DRAW);
    }
    else
    {
#define kQuadSize sizeof(_verts[0])
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * _filledVertex , _verts, GL_DYNAMIC_DRAW);

        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));

        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _filledIndex, _indices, GL_STATIC_DRAW);
    }

    //Start drawing verties in batch
    for(const auto& cmd : _batchedCommands)
    {
        auto newMaterialID = cmd->getMaterialID();
        if(_lastMaterialID != newMaterialID || newMaterialID == MATERIAL_ID_DO_NOT_BATCH)
        {
            //Draw quads
            if(indexToDraw > 0)
            {
                glDrawElements(GL_TRIANGLES, (GLsizei) indexToDraw, GL_UNSIGNED_SHORT, (GLvoid*) (startIndex*sizeof(_indices[0])) );
                _drawnBatches++;
                _drawnVertices += indexToDraw;

                startIndex += indexToDraw;
                indexToDraw = 0;
            }

            //Use new material
            cmd->useMaterial();
            _lastMaterialID = newMaterialID;
        }

        indexToDraw += cmd->getIndexCount();
    }

    //Draw any remaining triangles
    if(indexToDraw > 0)
    {
        glDrawElements(GL_TRIANGLES, (GLsizei) indexToDraw, GL_UNSIGNED_SHORT, (GLvoid*) (startIndex*sizeof(_indices[0])) );
        _drawnBatches++;
        _drawnVertices += indexToDraw;
    }

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Unbind VAO
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    _batchedCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
}

void Renderer::drawBatchedQuads()
{
    //TODO: we can improve the draw performance by insert material switching command before hand.
    
    ssize_t indexToDraw = 0;
    int startIndex = 0;
    
    //Upload buffer to VBO
    if(_numberQuads <= 0 || _batchQuadCommands.empty())
    {
        return;
    }
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Bind VAO
        GL::bindVAO(_quadVAO);
        //Set VBO data
        glBindBuffer(GL_ARRAY_BUFFER, _quadbuffersVBO[0]);
        
        // option 1: subdata
        //  glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );
        
        // option 2: data
        //  glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);
        
        // option 3: orphaning + glMapBuffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVerts[0]) * _numberQuads * 4, nullptr, GL_DYNAMIC_DRAW);
        void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        memcpy(buf, _quadVerts, sizeof(_quadVerts[0])* _numberQuads * 4);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadbuffersVBO[1]);
    }
    else
    {
#define kQuadSize sizeof(_verts[0])
        glBindBuffer(GL_ARRAY_BUFFER, _quadbuffersVBO[0]);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVerts[0]) * _numberQuads * 4 , _quadVerts, GL_DYNAMIC_DRAW);
        
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        
        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));
        
        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));
        
        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadbuffersVBO[1]);
    }


    // FIXME: The logic of this code is confusing, and error prone
    // Needs refactoring

    //Start drawing vertices in batch
    for(const auto& cmd : _batchQuadCommands)
    {
        bool commandQueued = true;
        auto newMaterialID = cmd->getMaterialID();
        if(_lastMaterialID != newMaterialID || newMaterialID == MATERIAL_ID_DO_NOT_BATCH)
        {
            // flush buffer
            if(indexToDraw > 0)
            {
                glDrawElements(GL_TRIANGLES, (GLsizei) indexToDraw, GL_UNSIGNED_SHORT, (GLvoid*) (startIndex*sizeof(_indices[0])) );
                _drawnBatches++;
                _drawnVertices += indexToDraw;
                
                startIndex += indexToDraw;
                indexToDraw = 0;
            }
            
            //Use new material
            _lastMaterialID = newMaterialID;

            cmd->useMaterial();
        }

        if (commandQueued)
        {
            indexToDraw += cmd->getQuadCount() * 6;
        }
    }
    
    //Draw any remaining quad
    if(indexToDraw > 0)
    {
        glDrawElements(GL_TRIANGLES, (GLsizei) indexToDraw, GL_UNSIGNED_SHORT, (GLvoid*) (startIndex*sizeof(_indices[0])) );
        _drawnBatches++;
        _drawnVertices += indexToDraw;
    }
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Unbind VAO
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    _batchQuadCommands.clear();
    _numberQuads = 0;
}

void Renderer::flush()
{
    flush2D();
    flush3D();
}

void Renderer::flush2D()
{
    flushQuads();
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

void Renderer::flushQuads()
{
    if(_numberQuads > 0)
    {
        drawBatchedQuads();
        _lastMaterialID = 0;
    }
}

void Renderer::flushTriangles()
{
    if(_filledIndex > 0)
    {
        drawBatchedTriangles();
        _lastMaterialID = 0;
    }
}

// helpers
bool Renderer::checkVisibility(const Mat4 &transform, const Size &size)
{
    auto scene = Director::getInstance()->getRunningScene();
    
    //If draw to Rendertexture, return true directly.
    // only cull the default camera. The culling algorithm is valid for default camera.
    if (!scene || (scene && scene->_defaultCamera != Camera::getVisitingCamera()))
        return true;

    auto director = Director::getInstance();
    Rect visiableRect(director->getVisibleOrigin(), director->getVisibleSize());
    
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
    visiableRect.origin.x -= wshw;
    visiableRect.origin.y -= wshh;
    visiableRect.size.width += wshw * 2;
    visiableRect.size.height += wshh * 2;
    bool ret = visiableRect.containsPoint(v2p);
    return ret;
}


void Renderer::setClearColor(const Color4F &clearColor)
{
    _clearColor = clearColor;
}

NS_CC_END
