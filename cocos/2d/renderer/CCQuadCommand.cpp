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


#include "2d/renderer/CCQuadCommand.h"
#include "2d/ccGLStateCache.h"
#include "xxhash.h"

NS_CC_BEGIN


static  void convertIntToByteArray(int value, int* output)
{
    *output = value;
}

QuadCommand::QuadCommand()
:_materialID(0)
,_textureID(0)
,_shader(nullptr)
,_blendType(BlendFunc::DISABLE)
,_quads(nullptr)
,_quadsCount(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
}

void QuadCommand::init(float globalOrder, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const Matrix &mv)
{
    _globalOrder = globalOrder;

    _quadsCount = quadCount;
    _quads = quad;

    _mv = mv;

    if( _textureID != textureID || _blendType.src != blendType.src || _blendType.dst != blendType.dst || _shader != shader) {
        
        _textureID = textureID;
        _blendType = blendType;
        _shader = shader;
        
        generateMaterialID();
    }
}

QuadCommand::~QuadCommand()
{
}

void QuadCommand::generateMaterialID()
{
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
    int intArray[3];
    convertIntToByteArray(_shader->getProgram(), intArray);
    convertIntToByteArray(blendID, intArray+1);
    convertIntToByteArray(_textureID, intArray+2);
    
    _materialID = XXH32((const void*)intArray, sizeof(intArray), 0);
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