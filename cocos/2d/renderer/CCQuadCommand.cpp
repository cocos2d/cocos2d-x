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
#include "xxhash.h"

NS_CC_BEGIN

QuadCommand::QuadCommand()
:_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadsCount(0)
,_dirty(false)
,_shader(nullptr)
,_quads(nullptr)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
}

void QuadCommand::init(float globalOrder, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const kmMat4 &mv)
{
    _globalOrder = globalOrder;
    _textureID = textureID;
    _blendType = blendType;
    _shader = shader;

    _quadsCount = quadCount;
    _quads = quad;

    _mv = mv;
    
    _dirty = true;

    generateMaterialID();
}

QuadCommand::~QuadCommand()
{
}

void QuadCommand::generateMaterialID()
{
    if (_dirty)
    {
        //Generate Material ID
        
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
        
        // convert program id, texture id and blend id into byte array
        char byteArray[12];
        convertIntToByteArray(_shader->getProgram(), byteArray);
        convertIntToByteArray(blendID, byteArray + 4);
        convertIntToByteArray(_textureID, byteArray + 8);
        
        _materialID = XXH32(byteArray, 12, 0);
        
        _dirty = false;
    }
}

void QuadCommand::convertIntToByteArray(int value, char* output)
{
    *output++ = value & 0x000000ff;
    *output++ = (value & 0x0000ff00) >> 8;
    *output++ = (value & 0x00ff0000) >> 16;
    *output   = (value & 0xff000000) >> 24;
}

void QuadCommand::useMaterial() const
{
    _shader->use();
    _shader->setUniformsForBuiltins(_mv);

    //Set texture
    GL::bindTexture2D(_textureID);

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
}

NS_CC_END