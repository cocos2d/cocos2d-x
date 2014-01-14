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

#include "CCRenderer.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CCCustomCommand.h"
#include "renderer/CCQuadCommand.h"
#include "CCGroupCommand.h"
#include "CCConfiguration.h"
#include "CCDirector.h"
#include "CCEventDispatcher.h"
#include "CCEventListenerCustom.h"
#include "CCEventType.h"
#include <algorithm>    // for std::stable_sort

NS_CC_BEGIN
using namespace std;


#define DEFAULT_RENDER_QUEUE 0

Renderer::Renderer()
:_lastMaterialID(0)
,_firstCommand(0)
,_lastCommand(0)
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
    command->generateID();
    _renderGroups[_commandGroupStack.top()].push_back(command);
}

void Renderer::addCommand(RenderCommand* command, int renderQueue)
{
    command->generateID();
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

bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
    return a->getID() < b->getID();
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
        for (auto it = _renderGroups.begin(); it != _renderGroups.end(); ++it)
        {
            std::stable_sort((*it).begin(), (*it).end(), compareRenderCommand);
        }
        
        while(!_renderStack.empty())
        {
            RenderQueue currRenderQueue = _renderGroups[_renderStack.top().renderQueueID];
            size_t len = currRenderQueue.size();
            
            //Refresh the batch command index in case the renderStack has changed.
            _firstCommand = _lastCommand = _renderStack.top().currentIndex;
            
            //Process RenderQueue
            for(size_t i = _renderStack.top().currentIndex; i < len; i++)
            {
                _renderStack.top().currentIndex = _lastCommand = i;
                auto command = currRenderQueue[i];

                auto commandType = command->getType();
                
                if(commandType == RenderCommand::Type::QUAD_COMMAND)
                {
                    QuadCommand* cmd = static_cast<QuadCommand*>(command);
                    ssize_t cmdQuadCount = cmd->getQuadCount();
                    
                    //Batch quads
                    if(_numQuads + cmdQuadCount > VBO_SIZE)
                    {
                        CCASSERT(cmdQuadCount < VBO_SIZE, "VBO is not big enough for quad data, please break the quad data down or use customized render command");

                        //Draw batched quads if VBO is full
                        drawBatchedQuads();
                    }

                    memcpy(_quads + _numQuads, cmd->getQuad(), sizeof(V3F_C4B_T2F_Quad) * cmdQuadCount);
                    _numQuads += cmdQuadCount;
                }
                else if(commandType == RenderCommand::Type::CUSTOM_COMMAND)
                {
                    flush();
                    CustomCommand* cmd = static_cast<CustomCommand*>(command);
                    cmd->execute();
                }
                else if(commandType == RenderCommand::Type::GROUP_COMMAND)
                {
                    flush();
                    GroupCommand* cmd = static_cast<GroupCommand*>(command);
                    
                    _renderStack.top().currentIndex = i + 1;
                    
                    //push new renderQueue to renderStack
                    RenderStackElement element = {cmd->getRenderQueueID(), 0};
                    _renderStack.push(element);
                    
                    //Exit current loop
                    break;
                }
                else
                {
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
    _firstCommand = _lastCommand = 0;
    _lastMaterialID = 0;
}

void Renderer::drawBatchedQuads()
{
    //TODO we can improve the draw performance by insert material switching command before hand.

    int quadsToDraw = 0;
    int startQuad = 0;

    //Upload buffer to VBO
    if(_numQuads <= 0)
    {
        _firstCommand = _lastCommand;
        return;
    }

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        //Set VBO data
        glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

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

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(_quads[0]) * _numQuads , _quads);

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
    for(size_t i = _firstCommand; i <= _lastCommand; i++)
    {
        RenderCommand* command = _renderGroups[_renderStack.top().renderQueueID][i];
        if (command->getType() == RenderCommand::Type::QUAD_COMMAND)
        {
            QuadCommand* cmd = static_cast<QuadCommand*>(command);
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

    
    _firstCommand = _lastCommand;
    _numQuads = 0;
}

void Renderer::flush()
{
    drawBatchedQuads();
    _lastMaterialID = 0;
}

NS_CC_END