//
// Created by NiTe Luo on 10/31/13.
//


#include <OpenGL/OpenGL.h>
#include "Renderer.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CustomCommand.h"
#include "QuadCommand.h"
#include "CCGL.h"
#include "GroupCommand.h"


NS_CC_BEGIN
using namespace std;

static Renderer*s_instance;

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
{
    RenderQueue defaultRenderQueue;
    _renderGroups.push_back(defaultRenderQueue);
    _renderStack.push({DEFAULT_RENDER_QUEUE, 0});
}

Renderer::~Renderer()
{
    _renderGroups.clear();
}

bool Renderer::init()
{
    setupIndices();

    setupVBOAndVAO();

    return true;
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

void Renderer::setupVBOAndVAO()
{
    glGenVertexArrays(1, &_VAOname);
    GL::bindVAO(_VAOname);

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

void Renderer::addRenderCommand(RenderCommand *command, int renderQueue)
{
    command->generateID();
    _renderGroups[renderQueue].push_back(command);
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

    //Process render commands
    //1. Sort render commands based on ID
    for (auto it = _renderGroups.begin(); it != _renderGroups.end(); ++it)
    {
        stable_sort((*it).begin(), (*it).end(), compareRenderCommand);
    }

    while(!_renderStack.empty())
    {
        size_t len = _renderGroups[_renderStack.top().renderQueueID].size();

        //If pop the render stack if we already processed all the commands
        if(_renderStack.top().currentIndex >= len)
        {
            _renderStack.pop();
            continue;
        }

        for(size_t i = _renderStack.top().currentIndex; i < len; i++)
        {
            auto command = _renderGroups[_renderStack.top().renderQueueID][i];

            if(command->getType() == QUAD_COMMAND)
            {
                QuadCommand* cmd = static_cast<QuadCommand*>(command);

                CCASSERT(cmd->getQuadCount()<VBO_SIZE, "VBO is not big enough for quad data, please break the quad data down or use customized render command");

                //Batch quads
                if(_numQuads + cmd->getQuadCount() < VBO_SIZE)
                {
                    memcpy(_quads + _numQuads, cmd->getQuad(), sizeof(V3F_C4B_T2F_Quad) * cmd->getQuadCount());
                    _numQuads += cmd->getQuadCount();
                    _lastCommand = i;
                }
                else
                {
                    //Draw batched quads if VBO is full
                    drawBatchedQuads();
                }
            }
            else if(command->getType() == CUSTOM_COMMAND)
            {
                flush();
                CustomCommand* cmd = static_cast<CustomCommand*>(command);
                cmd->execute();
            }
            else if(command->getType() == GROUP_COMMAND)
            {
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

    }

    size_t len = _renderGroups[DEFAULT_RENDER_QUEUE].size();

    for (size_t i = 0; i < len; i++)
    {
        auto command = _renderGroups[DEFAULT_RENDER_QUEUE][i];

        switch (command->getType())
        {
            case QUAD_COMMAND:
            {
                QuadCommand* cmd = static_cast<QuadCommand*>(command);

                CCASSERT(cmd->getQuadCount()<VBO_SIZE, "VBO is not big enough for quad data, please break the quad data down or use customized render command");

                //Batch quads
                if(_numQuads + cmd->getQuadCount() < VBO_SIZE)
                {
                    memcpy(_quads + _numQuads, cmd->getQuad(), sizeof(V3F_C4B_T2F_Quad) * cmd->getQuadCount());
                    _numQuads += cmd->getQuadCount();
                    _lastCommand = i;
                }
                else
                {
                    //Draw batched quads if VBO is full
                    drawBatchedQuads();
                }
                break;
            }
            case CUSTOM_COMMAND:
            {
                flush();
                CustomCommand* cmd = static_cast<CustomCommand*>(command);
                cmd->execute();
            }
            default:
                flush();
                break;
        }
    }

    //Draw the batched quads
    drawBatchedQuads();

    //TODO give command back to command pool
    for_each(_renderGroups[DEFAULT_RENDER_QUEUE].begin(), _renderGroups[DEFAULT_RENDER_QUEUE].end(), [](RenderCommand* cmd){delete cmd;});

    _firstCommand = _lastCommand = 0;
    _lastMaterialID = 0;
    _renderGroups[DEFAULT_RENDER_QUEUE].clear();
}

void Renderer::drawBatchedQuads()
{
    //TODO we can improve the draw performance by inseart material switching command before hand.

    int quadsToDraw = 0;
    int startQuad = 0;

    //Upload buffer to VBO
    if(_numQuads <= 0)
        return;

    //Set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(_quads[0]) * (_numQuads), NULL, GL_DYNAMIC_DRAW);
    void *buf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(buf, _quads, sizeof(_quads[0])* (_numQuads));
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Bind VAO
    GL::bindVAO(_VAOname);

    //Start drawing verties in batch
    for(size_t i = _firstCommand; i <= _lastCommand; i++)
    {
        RenderCommand* command = _renderGroups[DEFAULT_RENDER_QUEUE][i];
        if (command->getType() == QUAD_COMMAND)
        {
            QuadCommand* cmd = static_cast<QuadCommand*>(command);
            if(_lastMaterialID != cmd->getMaterialID())
            {
                //Draw quads
                if(quadsToDraw > 0)
                {
                    glDrawElements(GL_TRIANGLES, (GLsizei) quadsToDraw*6, GL_UNSIGNED_SHORT, (GLvoid*) (startQuad*6*sizeof(_indices[0])) );
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