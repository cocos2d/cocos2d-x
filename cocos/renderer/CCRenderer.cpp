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
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCMeshCommand.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventType.h"
#include "base/CCCamera.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

// helper
static bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getGlobalOrder() < b->getGlobalOrder();
}

// queue

void RenderQueue::push_back(RenderCommand* command)
{
    float z = command->getGlobalOrder();
    if(z < 0)
        _queueNegZ.push_back(command);
    else if(z > 0)
        _queuePosZ.push_back(command);
    else
        _queue0.push_back(command);
}

ssize_t RenderQueue::size() const
{
    return _queueNegZ.size() + _queue0.size() + _queuePosZ.size();
}

void RenderQueue::sort()
{
    // Don't sort _queue0, it already comes sorted
    std::sort(std::begin(_queueNegZ), std::end(_queueNegZ), compareRenderCommand);
    std::sort(std::begin(_queuePosZ), std::end(_queuePosZ), compareRenderCommand);
}

RenderCommand* RenderQueue::operator[](ssize_t index) const
{
    if(index < static_cast<ssize_t>(_queueNegZ.size()))
        return _queueNegZ[index];

    index -= _queueNegZ.size();

    if(index < static_cast<ssize_t>(_queue0.size()))
        return _queue0[index];

    index -= _queue0.size();

    if(index < static_cast<ssize_t>(_queuePosZ.size()))
        return _queuePosZ[index];

    CCASSERT(false, "invalid index");
    return nullptr;
}

void RenderQueue::clear()
{
    _queueNegZ.clear();
    _queue0.clear();
    _queuePosZ.clear();
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
,_filledVertex(0)
,_filledIndex(0)
,_glViewAssigned(false)
,_isRendering(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
,_cacheTextureListener(nullptr)
#endif
{
    _groupCommandManager = new (std::nothrow) GroupCommandManager();
    
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _batchedCommands.reserve(BATCH_QUADCOMMAND_RESEVER_SIZE);
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    _groupCommandManager->release();
    
    glDeleteBuffers(2, _buffersVBO);
    
    if (Configuration::getInstance()->supportsShareableVAO())
    {
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
    glGenVertexArrays(1, &_quadVAO);
    GL::bindVAO(_quadVAO);

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

    CHECK_GL_ERROR_DEBUG();
}

void Renderer::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    mapBuffers();
}

void Renderer::mapBuffers()
{
    // Avoid changing the element buffer for whatever VAO might be bound.
    GL::bindVAO(0);

    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_verts[0]) * VBO_SIZE, _verts, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * INDEX_VBO_SIZE, _indices, GL_STATIC_DRAW);
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

void Renderer::visitRenderQueue(const RenderQueue& queue)
{
    ssize_t size = queue.size();
    
    for (ssize_t index = 0; index < size; ++index)
    {
        auto command = queue[index];
        auto commandType = command->getType();
        if(RenderCommand::Type::QUAD_COMMAND == commandType || RenderCommand::Type::TRIANGLES_COMMAND == commandType)
        {
            flush3D();
            auto cmd = static_cast<TrianglesCommand*>(command);
            //Batch quads
            if( _filledVertex + cmd->getVertexCount() > VBO_SIZE || _filledIndex + cmd->getIndexCount() > INDEX_VBO_SIZE)
            {
                CCASSERT(cmd->getVertexCount()>= 0 && cmd->getVertexCount() < VBO_SIZE, "VBO for vertex is not big enough, please break the data down or use customized render command");
                CCASSERT(cmd->getIndexCount()>= 0 && cmd->getIndexCount() < INDEX_VBO_SIZE, "VBO for index is not big enough, please break the data down or use customized render command");
                //Draw batched quads if VBO is full
                drawBatchedQuads();
            }
            
            _batchedCommands.push_back(cmd);
            
            fillVerticesAndIndices(cmd);

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
        else if (RenderCommand::Type::MESH_COMMAND == commandType)
        {
            flush2D();
            auto cmd = static_cast<MeshCommand*>(command);
            if (_lastBatchedMeshCommand == nullptr || _lastBatchedMeshCommand->getMaterialID() != cmd->getMaterialID())
            {
                flush3D();
                cmd->preBatchDraw();
                cmd->batchDraw();
                _lastBatchedMeshCommand = cmd;
            }
            else
            {
                cmd->batchDraw();
            }
        }
        else
        {
            CCLOGERROR("Unknown commands in renderQueue");
        }
    }
}

void Renderer::render()
{
    //Uncomment this once everything is rendered by new renderer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //TODO: setup camera or MVP
    _isRendering = true;
    
    if (_glViewAssigned)
    {
        // cleanup
        _drawnBatches = _drawnVertices = 0;

        //Process render commands
        //1. Sort render commands based on ID
        for (auto &renderqueue : _renderGroups)
        {
            renderqueue.sort();
        }
        visitRenderQueue(_renderGroups[0]);
        flush();
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

    // Clear batch quad commands
    _batchedCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
    _lastMaterialID = 0;
    _lastBatchedMeshCommand = nullptr;
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

void Renderer::drawBatchedQuads()
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
        GL::bindVAO(_quadVAO);
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
        if(_lastMaterialID != newMaterialID || newMaterialID == TrianglesCommand::MATERIAL_ID_DO_NOT_BATCH)
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

    _batchedCommands.clear();
    _filledVertex = 0;
    _filledIndex = 0;
}

void Renderer::flush()
{
    flush2D();
    flush3D();
}

void Renderer::flush2D()
{
    drawBatchedQuads();
    _lastMaterialID = 0;
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

NS_CC_END
