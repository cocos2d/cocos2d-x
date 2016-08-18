/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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

#include "renderer/CCTrianglesCommand.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "xxhash.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTexture2D.h"

NS_CC_BEGIN

TrianglesCommand::TrianglesCommand()
:_materialID(0)
,_textureID(0)
,_glProgramState(nullptr)
,_blendType(BlendFunc::DISABLE)
,_alphaTextureID(0)
{
    _type = RenderCommand::Type::TRIANGLES_COMMAND;
}

void TrianglesCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv, uint32_t flags)
{
    CCASSERT(glProgramState, "Invalid GLProgramState");
    CCASSERT(glProgramState->getVertexAttribsFlags() == 0, "No custom attributes are supported in QuadCommand");

    RenderCommand::init(globalOrder, mv, flags);

    _triangles = triangles;
    if(_triangles.indexCount % 3 != 0)
    {
        int count = _triangles.indexCount;
        _triangles.indexCount = count / 3 * 3;
        CCLOGERROR("Resize indexCount from %zd to %zd, size must be multiple times of 3", count, _triangles.indexCount);
    }
    _mv = mv;
    
    if( _textureID != textureID || _blendType.src != blendType.src || _blendType.dst != blendType.dst ||
       _glProgramState != glProgramState)
    {
        _textureID = textureID;
        _blendType = blendType;
        _glProgramState = glProgramState;

        generateMaterialID();
    }
}

void TrianglesCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles,const Mat4& mv)
{
    init(globalOrder, textureID, glProgramState, blendType, triangles, mv, 0);
}

void TrianglesCommand::init(float globalOrder, Texture2D* texture, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags)
{
    init(globalOrder, texture->getName(), glProgramState, blendType, triangles, mv, flags);
    _alphaTextureID = texture->getAlphaTextureName();
}

TrianglesCommand::~TrianglesCommand()
{
}

void TrianglesCommand::generateMaterialID()
{
    // glProgramState is hashed because it contains:
    //  *  uniforms/values
    //  *  glProgram
    //
    // we safely can when the same glProgramState is being used then they share those states
    // if they don't have the same glProgramState, they might still have the same
    // uniforms/values and glProgram, but it would be too expensive to check the uniforms.
    struct {
        GLuint textureId;
        GLenum blendSrc;
        GLenum blendDst;
        void* glProgramState;
    } hashMe;

    hashMe.textureId = _textureID;
    hashMe.blendSrc = _blendType.src;
    hashMe.blendDst = _blendType.dst;
    hashMe.glProgramState = _glProgramState;
    _materialID = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
}

void TrianglesCommand::useMaterial() const
{
    //Set texture
    GL::bindTexture2D(_textureID);
    
    if (_alphaTextureID > 0)
    { // ANDROID ETC1 ALPHA supports.
        GL::bindTexture2DN(1, _alphaTextureID);
    }
    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
    
    _glProgramState->apply(_mv);
}

NS_CC_END
