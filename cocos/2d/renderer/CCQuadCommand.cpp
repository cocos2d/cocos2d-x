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


#include "renderer/CCQuadCommand.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN

QuadCommand::QuadCommand()
:_viewport(0)
,_depth(0)
,_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadsCount(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
    _shader = nullptr;
    _quads = nullptr;
}

void QuadCommand::init(int viewport, int32_t depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const kmMat4 &mv)
{
    _viewport = viewport;
    _depth = depth;
    _textureID = textureID;
    _blendType = blendType;
    _shader = shader;

    _quadsCount = quadCount;
    _quads = quad;

    _mv = mv;
}

QuadCommand::~QuadCommand()
{
}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shader->getProgram() < pow(2,10), "ShaderID is greater than 2^10");
    //TODO fix texture ID generation
    CCASSERT(_textureID < pow(2,18), "TextureID is greater than 2^18");

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

    //TODO Material ID should be part of the ID
    //
    // Temporal hack (later, these 32-bits should be packed in 24-bits
    //
    // +---------------------+-------------------+----------------------+
    // | Shader ID (10 bits) | Blend ID (4 bits) | Texture ID (18 bits) |
    // +---------------------+-------------------+----------------------+

    _materialID = (int32_t)_shader->getProgram() << 22
            | (int32_t)blendID << 18
            | (int32_t)_textureID << 0;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)_depth << 36;

    return _id;
}

void QuadCommand::useMaterial()
{
    _shader->use();

    _shader->setUniformsForBuiltins();

    //Set texture
    GL::bindTexture2D(_textureID);

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
}

NS_CC_END