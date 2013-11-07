//
// Created by NiTe Luo on 10/31/13.
//


#include "Renderer.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN
using namespace std;

static Renderer* s_renderer;

Renderer *Renderer::getInstance()
{
    if(!s_renderer)
    {
        s_renderer = new Renderer();
    }
    return s_renderer;
}

Renderer::Renderer()
:_lastMaterialID(0)
,_numQuadsAlloc(0)
,_numQuads(0)
{
    _quadBuffer = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * NUM_QUADS_PER_ALLOC);
    _numQuadsAlloc = NUM_QUADS_PER_ALLOC;
}

Renderer::~Renderer()
{
    free(_quadBuffer);
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

    //2. Process commands
    for(vector<RenderCommand*>::iterator it = _renderQueue.begin(); it != _renderQueue.end(); ++it)
    {
        //TODO: Perform Sprite batching here
        auto command = *it;

        switch(command->getType())
        {
            case QUAD_COMMAND:
            {
                QuadCommand* cmd = (QuadCommand*)command;

                if(_lastMaterialID != cmd->getMaterialID())
                {
                    //Draw batched data
                    if(_numQuads > 0)
                    {
                        drawQuads();
                    }

                    //Set new material
                    _lastMaterialID = cmd->getMaterialID();

                    //Set Shader
                    cmd->useMaterial();

                    //TODO: Set Blend Mode

                    //Set texture
                    GL::bindTexture2D(cmd->getTextureID());
                }

                batchQuads(cmd);

                break;
            }
            default:
                break;
        }

        delete command;
    }

    drawQuads();

    _renderQueue.clear();
}

void Renderer::drawQuads()
{
    //Bind VAO
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    long offset = (long)_quadBuffer;

    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (void*) (offset + diff));

    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (void*)(offset + diff));

    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (void*)(offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4 * _numQuads);

    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWS(1);

    _numQuads = 0;
}

void Renderer::batchQuads(QuadCommand* cmd)
{
    //Batch data
    _numQuads++; //Every quad command only contains one quad
    if(_numQuads > _numQuadsAlloc)
    {
        _numQuadsAlloc = _numQuads + NUM_QUADS_PER_ALLOC;
        _quadBuffer = (V3F_C4B_T2F_Quad*)realloc(_quadBuffer, sizeof(V3F_C4B_T2F_Quad) * _numQuadsAlloc);
    }
    _quadBuffer[_numQuads - 1] = *cmd->getQuad();
}

NS_CC_END