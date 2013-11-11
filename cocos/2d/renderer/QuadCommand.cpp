//
// Created by NiTe Luo on 11/6/13.
//


#include "QuadCommand.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN

QuadCommand::QuadCommand(int viewport, int32_t depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad quad)
:RenderCommand()
,_viewport(viewport)
,_depth(depth)
,_textureID(textureID)
,_blendType(blendType)
,_quad(quad)
{
    _type = QUAD_COMMAND;
    _shader = shader;
    _quadCount = 1;
}

QuadCommand::~QuadCommand()
{

}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shader->getProgram() < 64, "ShaderID is greater than 64");
    //TODO fix texture ID generation
    CCASSERT(_textureID < 1024, "TextureID is greater than 1024");

    //TODO fix blend id generation
    int blendID = 0;
    if(_blendType == BlendFunc::DISABLE)
    {
        blendID = 0;
    }
    else if(_blendType == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        blendID = 1;
    }
    else if(_blendType == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendID = 2;
    }
    else if(_blendType == BlendFunc::ADDITIVE)
    {
        blendID = 3;
    }
    else
    {
        blendID = 4;
    }

    _materialID = (int32_t)_shader->getProgram() << 28
            | (int32_t)blendID << 24
            | (int32_t)_textureID << 14;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)_depth << 36;

    return _id;
}

void QuadCommand::useMaterial()
{
    _shader->use();
    //TODO once everything is using world coordinate, we can reduce the uniforms for shaders
    _shader->setUniformsForBuiltins();

    //TODO set blend mode

    //Set texture
    GL::bindTexture2D(_textureID);
}

NS_CC_END