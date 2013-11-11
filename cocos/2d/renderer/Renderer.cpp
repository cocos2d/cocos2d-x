//
// Created by NiTe Luo on 10/31/13.
//


#include "Renderer.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CustomCommand.h"
#include "CCGL.h"


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

}

Renderer::~Renderer()
{
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

void Renderer::addRenderCommand(RenderCommand *command)
{
    command->generateID();
    _renderQueue.push_back(command);
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
    stable_sort(_renderQueue.begin(), _renderQueue.end(), compareRenderCommand);

    size_t len = _renderQueue.size();

    for (size_t i = 0; i < len; i++)
    {
        auto command = _renderQueue[i];

        if( command->getType() == QUAD_COMMAND )
        {
            QuadCommand* cmd = static_cast<QuadCommand*>(command);

            //
            if(_numQuads + cmd->getQuadCount() < VBO_SIZE)
            {
                memcpy(_quads + _numQuads - 1, cmd->getQuad(), sizeof(V3F_C4B_T2F_Quad) * cmd->getQuadCount());
                _numQuads += cmd->getQuadCount();
                _lastCommand = i;
            }
            else
            {
                //Draw batched quads if VBO is full
                drawBatchedQuads();
            }

        }
        else
        {
            //Draw batched quads if we encountered a different command
            drawBatchedQuads();
        }
    }

    //Draw the batched quads
    drawBatchedQuads();

    _firstCommand = _lastCommand = 0;
    _lastMaterialID = 0;
    _renderQueue.clear();

//    //2. Process commands
//    for(auto it = _renderQueue.begin(); it != _renderQueue.end(); ++it)
//    {
//        //TODO: Perform Sprite batching here
//        auto command = *it;
//
//        switch(command->getType())
//        {
//            case QUAD_COMMAND:
//            {
//                QuadCommand* cmd = static_cast<QuadCommand*>(command);
//
//                if(_lastMaterialID != cmd->getMaterialID() || _numQuads >= VBO_SIZE)
//                {
//                    //Draw batched data
//                    drawQuads();
//                }
//
//                //Reset material if needed.
//                if(_lastMaterialID != cmd->getMaterialID())
//                {
//                    //Set new material
//                    _lastMaterialID = cmd->getMaterialID();
//
//                    //Set Shader
//                    cmd->useMaterial();
//                }
//
//                batchQuads(cmd);
//
//                break;
//            }
//            case CUSTOM_COMMAND:
//            {
//                flush();
//                CustomCommand* cmd = static_cast<CustomCommand*>(command);
//                cmd->execute();
//
//                break;
//            }
//            default:
//                break;
//        }
//
//        delete command;
//    }
//
//    drawQuads();
//
//    _renderQueue.clear();
}

void Renderer::drawBatchedQuads()
{
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

    for(size_t i = _firstCommand; i <= _lastCommand; i++)
    {
        RenderCommand* command = _renderQueue[i];
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

    _firstCommand = _lastCommand;
    _numQuads = 0;
}

void Renderer::drawQuads()
{
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

    glDrawElements(GL_TRIANGLES, (GLsizei) _numQuads*6, GL_UNSIGNED_SHORT, 0 );

    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWS(1);

    _numQuads = 0;
}

void Renderer::batchQuads(QuadCommand* cmd)
{
    //Batch data
    _numQuads++; //Every quad command only contains one quad
    _quads[_numQuads - 1] = *cmd->getQuad();
}

void Renderer::flush()
{
    drawQuads();
    _lastMaterialID = 0;
}

NS_CC_END