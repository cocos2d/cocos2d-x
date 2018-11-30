/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "xxhash.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTexture2D.h"
#include "base//ccUtils.h"
#include "renderer/backend/opengl/TextureGL.h"

NS_CC_BEGIN

TrianglesCommand::TrianglesCommand()
{
    _type = RenderCommand::Type::TRIANGLES_COMMAND;
}

size_t TrianglesCommand::copyVertexData(void* out) const
{
    auto dataLength = sizeof(V3F_C4B_T2F) * _triangles.vertCount;
    memcpy(out, _triangles.verts, dataLength);
    
    auto tmpVerts = (V3F_C4B_T2F*)out;
    for (int i = 0; i < _triangles.vertCount; ++i)
        _mv.transformPoint(&tmpVerts[i].vertices);
    
    return dataLength;
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
        CCLOGERROR("Resize indexCount from %d to %d, size must be multiple times of 3", count, _triangles.indexCount);
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

void TrianglesCommand::init(float globalOrder, Texture2D* texture, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags)
{
    init(globalOrder, texture->getName(), glProgramState, blendType, triangles, mv, flags);
    _alphaTextureID = texture->getAlphaTextureName();
}

void TrianglesCommand::init(float globalOrder, backend::Texture* textureID, GLProgramState* glProgramState, BlendFunc blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags)
{
    backend::TextureGL* texture = static_cast<backend::TextureGL*>(textureID);
    init(globalOrder, texture->getHandler(), glProgramState, blendType, triangles, mv, flags);
    //    _alphaTextureID = texture->getAlphaTextureName();
}

void TrianglesCommand::init(float globalOrder, const Triangles& triangles, const Mat4& mv, uint32_t flags)
{
    RenderCommand::init(globalOrder, mv, flags);
    
    _triangles = triangles;
    if(_triangles.indexCount % 3 != 0)
    {
        int count = _triangles.indexCount;
        _triangles.indexCount = count / 3 * 3;
        CCLOGERROR("Resize indexCount from %d to %d, size must be multiple times of 3", count, _triangles.indexCount);
    }
    _mv = mv;
    
    // TODO: optimize it only generate material ID needed.
    generateMaterialID();
}

TrianglesCommand::~TrianglesCommand()
{
}

void TrianglesCommand::generateMaterialID()
{
    struct PipelineDescriptor
    {
        // These are helper functions to handle reference count.
        void setVertexShader(backend::ShaderModule* shaderModule);
        void setFragmentShader(backend::ShaderModule* shaderModule);
        
        backend::DepthStencilDescriptor depthStencilDescriptor;
        backend::BlendDescriptor blendDescriptor;
        backend::BindGroup* bindGroup;
        backend::VertexLayout vertexLayout;
        backend::ShaderModule* vertexShader = nullptr;
        backend::ShaderModule* fragmentShader = nullptr;
    }hashMe;
    memset(&hashMe, 0, sizeof(hashMe));

    hashMe.depthStencilDescriptor = _pipelineDescriptor.depthStencilDescriptor;
    hashMe.blendDescriptor = _pipelineDescriptor.blendDescriptor;
    hashMe.bindGroup = &_pipelineDescriptor.bindGroup;
    hashMe.vertexLayout = _pipelineDescriptor.vertexLayout;
    hashMe.vertexShader = _pipelineDescriptor.vertexShader;
    hashMe.fragmentShader = _pipelineDescriptor.fragmentShader;
    _materialID = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
}

void TrianglesCommand::useMaterial() const
{
    //Set texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    
    if (_alphaTextureID > 0)
    { // ANDROID ETC1 ALPHA supports.
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, _alphaTextureID);
    }
    //set blend mode
    utils::setBlending(_blendType.src, _blendType.dst);
    
    _glProgramState->apply(_mv);
}

NS_CC_END
