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
#include "renderer/CCQuadCommand.h"
#include "renderer/CCBatchCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCEventDispatcher.h"
#include "CCEventListenerCustom.h"
#include "CCEventType.h"
#include <algorithm>

NS_CC_BEGIN

bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getGlobalOrder() < b->getGlobalOrder();
}

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
    if(index < _queueNegZ.size())
        return _queueNegZ[index];

    index -= _queueNegZ.size();

    if(index < _queue0.size())
        return _queue0[index];

    index -= _queue0.size();

    if(index < _queuePosZ.size())
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
#define DEFAULT_RENDER_QUEUE 0

Renderer::Renderer()
:_lastMaterialID(0)
,_numQuads(0)
,_glViewAssigned(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
,_cacheTextureListener(nullptr)
#endif
{
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    RenderStackElement elelment = {DEFAULT_RENDER_QUEUE, 0};
    _renderStack.push(elelment);
    _batchedQuadCommands.reserve(BATCH_QUADCOMMAND_RESEVER_SIZE);
}

Renderer::~Renderer()
{
    _renderGroups.clear();
    
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
    _cacheTextureListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom* event){
        /** listen the event that coming to foreground on Android */
        this->setupBuffer();
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_cacheTextureListener, -1);
#endif

    setupIndices();
    
    setupBuffer();
    
    _glViewAssigned = true;
}

void Renderer::setupIndices()
{
    for( int i=0; i < VBO_SIZE; i++)
    {
        _indices[i*6+0] = (GLushort) (i*4+0);
        _indices[i*6+1] = (GLushort) (i*4+1);
        _indices[i*6+2] = (GLushort) (i*4+2);
        _indices[i*6+3] = (GLushort) (i*4+3);
        _indices[i*6+4] = (GLushort) (i*4+2);
        _indices[i*6+5] = (GLushort) (i*4+1);
    }
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * VBO_SIZE, _quads, GL_DYNAMIC_DRAW);

    // vertices
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, vertices));

    // colors
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, colors));

    // tex coords
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid*) offsetof( V3F_C4B_T2F, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * VBO_SIZE * 6, _indices, GL_STATIC_DRAW);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * VBO_SIZE, _quads, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * VBO_SIZE * 6, _indices, GL_STATIC_DRAW);
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
    CCASSERT(renderQueue >=0, "Invalid render queue");
    CCASSERT(command->getType() != RenderCommand::Type::UNKNOWN_COMMAND, "Invalid Command Type");
    _renderGroups[renderQueue].push_back(command);
}

void Renderer::pushGroup(int renderQueueID)
{
    _commandGroupStack.push(renderQueueID);
}

void Renderer::popGroup()
{
    _commandGroupStack.pop();
}

int Renderer::createRenderQueue()
{
    RenderQueue newRenderQueue;
    _renderGroups.push_back(newRenderQueue);
    return (int)_renderGroups.size() - 1;
}

void Renderer::render()
{
    //Uncomment this once everything is rendered by new renderer
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //TODO setup camera or MVP

    if (_glViewAssigned)
    {
        //Process render commands
        //1. Sort render commands based on ID
        for (auto &renderqueue : _renderGroups)
        {
            renderqueue.sort();
        }
        
        while(!_renderStack.empty())
        {
            RenderQueue currRenderQueue = _renderGroups[_renderStack.top().renderQueueID];
            size_t len = currRenderQueue.size();
            
            //Process RenderQueue
            for(size_t i = _renderStack.top().currentIndex; i < len; i++)
            {
                _renderStack.top().currentIndex = i;
                auto command = currRenderQueue[i];

                auto commandType = command->getType();
                
                if(commandType == RenderCommand::Type::QUAD_COMMAND)
                {
                    auto cmd = static_cast<QuadCommand*>(command);
                    CCASSERT(nullptr!= cmd, "Illegal command for RenderCommand Taged as QUAD_COMMAND");
                    
                    //Batch quads
                    if(_numQuads + cmd->getQuadCount() > VBO_SIZE)
                    {
                        CCASSERT(cmd->getQuadCount()>= 0 && cmd->getQuadCount() < VBO_SIZE, "VBO is not big enough for quad data, please break the quad data down or use customized render command");

                        //Draw batched quads if VBO is full
                        drawBatchedQuads();
                    }
                    
                    _batchedQuadCommands.push_back(cmd);
                    
                    memcpy(_quads + _numQuads, cmd->getQuads(), sizeof(V3F_C4B_T2F_Quad) * cmd->getQuadCount());
                    convertToWorldCoordinates(_quads + _numQuads, cmd->getQuadCount(), cmd->getModelView());

                    _numQuads += cmd->getQuadCount();
                }
                else if(commandType == RenderCommand::Type::CUSTOM_COMMAND)
                {
                    flush();
                    auto cmd = static_cast<CustomCommand*>(command);
                    cmd->execute();
                }
                else if(commandType == RenderCommand::Type::BATCH_COMMAND)
                {
                    flush();
                    auto cmd = static_cast<BatchCommand*>(command);
                    cmd->execute();
                }
                else if(commandType == RenderCommand::Type::GROUP_COMMAND)
                {
                    flush();
                    auto cmd = static_cast<GroupCommand*>(command);
                    
                    _renderStack.top().currentIndex = i + 1;
                    
                    //push new renderQueue to renderStack
                    RenderStackElement element = {cmd->getRenderQueueID(), 0};
                    _renderStack.push(element);
                    
                    //Exit current loop
                    break;
                }
                else
                {
                    CCASSERT(true, "Invalid command");
                    flush();
                }
            }
            
            //Draw the batched quads
            drawBatchedQuads();
            
            currRenderQueue = _renderGroups[_renderStack.top().renderQueueID];
            len = currRenderQueue.size();
            //If pop the render stack if we already processed all the commands
            if(_renderStack.top().currentIndex + 1 >= len)
            {
                _renderStack.pop();
            }
        }
    }

    for (size_t j = 0 ; j < _renderGroups.size(); j++)
    {
        //commands are owned by nodes
        // for (const auto &cmd : _renderGroups[j])
        // {
        //     cmd->releaseToCommandPool();
        // }
        _renderGroups[j].clear();
    }
    
    //Clear the stack incase gl view hasn't been initialized yet
    while(!_renderStack.empty())
    {
        _renderStack.pop();
    }
    RenderStackElement element = {DEFAULT_RENDER_QUEUE, 0};
    _renderStack.push(element);
    _lastMaterialID = 0;
}

void Renderer::convertToWorldCoordinates(V3F_C4B_T2F_Quad* quads, ssize_t quantity, const kmMat4& modelView)
{
//    kmMat4 matrixP, mvp;
//    kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
//    kmMat4Multiply(&mvp, &matrixP, &modelView);

    for(ssize_t i=0; i<quantity; ++i) {
        V3F_C4B_T2F_Quad *q = &quads[i];

        kmVec3 *vec1 = (kmVec3*)&q->bl.vertices;
        kmVec3Transform(vec1, vec1, &modelView);

        kmVec3 *vec2 = (kmVec3*)&q->br.vertices;
        kmVec3Transform(vec2, vec2, &modelView);

        kmVec3 *vec3 = (kmVec3*)&q->tr.vertices;
        kmVec3Transform(vec3, vec3, &modelView);

        kmVec3 *vec4 = (kmVec3*)&q->tl.vertices;
        kmVec3Transform(vec4, vec4, &modelView);
    }
}

void Renderer::drawBatchedQuads()
{
    //TODO we can improve the draw performance by insert material switching command before hand.

    int quadsToDraw = 0;
    int startQuad = 0;

    //Upload buffer to VBO
    if(_numQuads <= 0 || _batchedQuadCommands.empty())
    {
        return;
    }

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Set VBO data
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        // option 1: subdata
//        glBufferSubData(GL_ARRAY_BUFFER, sizeof(_quads[0])*start, sizeof(_quads[0]) * n , &_quads[start] );

        // option 2: data
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quads_[0]) * (n-start), &quads_[start], GL_DYNAMIC_DRAW);

        // option 3: orphaning + glMapBuffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * (_numQuads), nullptr, GL_DYNAMIC_DRAW);
        void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        memcpy(buf, _quads, sizeof(_quads[0])* (_numQuads));
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Bind VAO
        GL::bindVAO(_quadVAO);
    }
    else
    {
#define kQuadSize sizeof(_quads[0].bl)
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

        glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * _numQuads , _quads, GL_DYNAMIC_DRAW);

        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, vertices));

        // colors
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, colors));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (GLvoid*) offsetof(V3F_C4B_T2F, texCoords));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    }

    //Start drawing verties in batch
    //for(auto i = _batchedQuadCommands.begin(); i != _batchedQuadCommands.end(); ++i)
    for(const auto& cmd : _batchedQuadCommands)
    {
        if(_lastMaterialID != cmd->getMaterialID())
        {
            //Draw quads
            if(quadsToDraw > 0)
            {
                glDrawElements(GL_TRIANGLES, (GLsizei) quadsToDraw*6, GL_UNSIGNED_SHORT, (GLvoid*) (startQuad*6*sizeof(_indices[0])) );
                CC_INCREMENT_GL_DRAWS(1);

                startQuad += quadsToDraw;
                quadsToDraw = 0;
            }

            //Use new material
            cmd->useMaterial();
            _lastMaterialID = cmd->getMaterialID();
        }

        quadsToDraw += cmd->getQuadCount();
    }

    //Draw any remaining quad
    if(quadsToDraw > 0)
    {
        glDrawElements(GL_TRIANGLES, (GLsizei) quadsToDraw*6, GL_UNSIGNED_SHORT, (GLvoid*) (startQuad*6*sizeof(_indices[0])) );
        CC_INCREMENT_GL_DRAWS(1);
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

    _batchedQuadCommands.clear();
    _numQuads = 0;
}

void Renderer::flush()
{
    drawBatchedQuads();
    _lastMaterialID = 0;
}

NS_CC_END
