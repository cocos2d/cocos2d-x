//
// Created by NiTe Luo on 10/31/13.
//


#include "Renderer.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CustomCommand.h"
#include "QuadCommand.h"
#include "GroupCommand.h"
#include "CCConfiguration.h"
#include "CCNotificationCenter.h"
#include "CCEventType.h"
#include <algorithm>    // for std::stable_sort

NS_CC_BEGIN
using namespace std;

static Renderer* s_instance = nullptr;

Renderer *Renderer::getInstance()
{
    if(!s_instance)
    {
        s_instance = new Renderer();
        if(!s_instance->init())
        {
            CC_SAFE_DELETE(s_instance);
        }
    }
    return s_instance;
}

void Renderer::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_instance);
}

Renderer::Renderer()
:_lastMaterialID(0)
,_numQuads(0)
,_firstCommand(0)
,_lastCommand(0)
,_glViewAssigned(false)
{
    _commandGroupStack.push(DEFAULT_RENDER_QUEUE);
    
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _renderStack.push({DEFAULT_RENDER_QUEUE, 0});
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
}

bool Renderer::init()
{
    return true;
}

void Renderer::initGLView()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // listen the event when app go to background
    NotificationCenter::getInstance()->addObserver(this,
                                                           callfuncO_selector(Renderer::onBackToForeground),
                                                           EVNET_COME_TO_FOREGROUND,
                                                           NULL);
#endif

    setupIndices();
    
    setupBuffer();
    
    _glViewAssigned = true;
}

void Renderer::onBackToForeground(Object* obj)
{
    CC_UNUSED_PARAM(obj);
    setupBuffer();
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
                
                if(command->getType() == QUAD_COMMAND)
                {
                    QuadCommand* cmd = static_cast<QuadCommand*>(command);

                    //Batch quads
                    if(_numQuads + cmd->getQuadCount() > VBO_SIZE)
                    {
                        CCASSERT(cmd->getQuadCount() < VBO_SIZE, "VBO is not big enough for quad data, please break the quad data down or use customized render command");

                        //Draw batched quads if VBO is full
                        drawBatchedQuads();
                    }

                    memcpy(_quads + _numQuads, cmd->getQuad(), sizeof(V3F_C4B_T2F_Quad) * cmd->getQuadCount());
                    _numQuads += cmd->getQuadCount();
                }
                else if(command->getType() == CUSTOM_COMMAND)
                {
                    flush();
                    CustomCommand* cmd = static_cast<CustomCommand*>(command);
                    cmd->execute();
                }
                else if(command->getType() == GROUP_COMMAND)
                {
                    flush();
                    GroupCommand* cmd = static_cast<GroupCommand*>(command);
                    
                    _renderStack.top().currentIndex = i + 1;
                    
                    //push new renderQueue to renderStack
                    _renderStack.push({cmd->getRenderQueueID(), 0});
                    
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

    //TODO give command back to command pool
    for (size_t j = 0 ; j < _renderGroups.size(); j++)
    {
        for_each(_renderGroups[j].begin(), _renderGroups[j].end(), [](RenderCommand* cmd){ cmd->releaseToCommandPool(); });
        _renderGroups[j].clear();
    }
    
    //Clear the stack incase gl view hasn't been initialized yet
    while(!_renderStack.empty())
    {
        _renderStack.pop();
    }
    _renderStack.push({DEFAULT_RENDER_QUEUE, 0});
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

        glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * (_numQuads), NULL, GL_DYNAMIC_DRAW);
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
        if (command->getType() == QUAD_COMMAND)
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