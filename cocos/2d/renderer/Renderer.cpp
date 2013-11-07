//
// Created by NiTe Luo on 10/31/13.
//


#include "Renderer.h"

#include "CCGL.h"
#include "ccMacros.h"
#include "CCShaderCache.h"
#include "ccGLStateCache.h"
#include "CCGLProgram.h"
#include "QuadCommand.h"

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
{
    _shaderProgram = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
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

                //Set Shader
                _shaderProgram->use();
                _shaderProgram->setUniformsForBuiltins();

                //Set Blend Mode
                //Set texture
                GL::bindTexture2D(cmd->getTextureID());
                GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);

#define kQuadSize sizeof(cmd->getQuad()->bl)
                long offset = (long)cmd->getQuad();

                // vertex
                int diff = offsetof( V3F_C4B_T2F, vertices);
                glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

                // texCoods
                diff = offsetof( V3F_C4B_T2F, texCoords);
                glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

                // color
                diff = offsetof( V3F_C4B_T2F, colors);
                glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                CHECK_GL_ERROR_DEBUG();
                CC_INCREMENT_GL_DRAWS(1);

                break;
            }
            default:
                break;
        }

        delete command;
    }

    _renderQueue.clear();
}

NS_CC_END