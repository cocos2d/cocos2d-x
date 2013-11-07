//
// Created by NiTe Luo on 11/6/13.
//


#include "QuadCommand.h"

NS_CC_BEGIN

QuadCommand::QuadCommand(int viewport, int32_t depth, GLuint textureID, GLuint shaderID, BlendFunc blendType, V3F_C4B_T2F_Quad quad)
:RenderCommand()
,_viewport(viewport)
,_depth(depth)
,_textureID(textureID)
,_shaderID(shaderID)
,_blendType(blendType)
,_quad(quad)
{
    _type = QUAD_COMMAND;
}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shaderID < 64, "ShaderID is greater than 64");
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

    _materialID = (int32_t)_shaderID << 28
            | (int32_t)blendID << 24
            | (int32_t)_textureID << 14;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)0 << 59 //is command
            | (int64_t)_depth << 35;

    return _id;
}

NS_CC_END