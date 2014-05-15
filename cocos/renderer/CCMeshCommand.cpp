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


#include "renderer/CCMeshCommand.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "2d/CCTextureAtlas.h"
#include "2d/CCTexture2D.h"

NS_CC_BEGIN

MeshCommand::MeshCommand()
: _textureID(0)
, _blendType(BlendFunc::DISABLE)
, _glProgramState(nullptr)
, _cullFaceEnabled(false)
, _cullFace(GL_BACK)
, _depthTestEnabled(false)
, _depthWriteEnabled(false)
{
    _type = RenderCommand::Type::MESH_COMMAND;
}

void MeshCommand::init(float globalOrder, GLuint textureID, GLProgramState* glProgramState, BlendFunc blendType, GLuint vertexBuffer, GLuint indexBuffer, GLenum primitive, GLenum indexFormat, GLenum indexCount, const Matrix &mv)
{
    CCASSERT(glProgramState, "GLProgramState cannot be nill");
    
    _globalOrder = globalOrder;
    _textureID = textureID;
    _blendType = blendType;
    _glProgramState = glProgramState;

    _vertexBuffer = vertexBuffer;
    _indexBuffer = indexBuffer;
    _primitive = primitive;
    _indexFormat = indexFormat;
    _indexCount = indexCount;
    _mv = mv;
}

void MeshCommand::setCullFaceEnabled(bool enable)
{
    _cullFaceEnabled = enable;
}

void MeshCommand::setCullFace(GLenum cullFace)
{
    _cullFace = cullFace;
}

void MeshCommand::setDepthTestEnabled(bool enable)
{
    _depthTestEnabled = enable;
}

void MeshCommand::setDepthWriteEnabled(bool enable)
{
    _depthWriteEnabled = enable;
}

MeshCommand::~MeshCommand()
{
}

void MeshCommand::applyRenderState()
{
    if (_cullFaceEnabled)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(_cullFace);
    }
    if (_depthTestEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    if (_depthWriteEnabled)
    {
        glDepthMask(GL_TRUE);
    }
}

void MeshCommand::restoreRenderState()
{
    if (_cullFaceEnabled)
    {
        glDisable(GL_CULL_FACE);
    }
    if (_depthTestEnabled)
    {
        glDisable(GL_DEPTH_TEST);
    }
    if (_depthWriteEnabled)
    {
        glDepthMask(GL_FALSE);
    }
}

void MeshCommand::execute()
{
    // set render state
    applyRenderState();
    
    // Set material
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    _glProgramState->apply(_mv);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    // Draw
    glDrawElements(_primitive, _indexCount, _indexFormat, 0);
    
    //restore render state
    restoreRenderState();
}

NS_CC_END