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

#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "renderer/CCMeshCommand.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "xxhash.h"

NS_CC_BEGIN

MeshCommand::MeshCommand()
: _textureID(0)
, _blendType(BlendFunc::DISABLE)
, _glProgramState(nullptr)
, _cullFaceEnabled(false)
, _cullFace(GL_BACK)
, _depthTestEnabled(false)
, _depthWriteEnabled(false)
, _displayColor(1.0f, 1.0f, 1.0f, 1.0f)
, _matrixPalette(nullptr)
, _matrixPaletteSize(0)
, _materialID(0)
, _vao(0)
{
    _type = RenderCommand::Type::MESH_COMMAND;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // listen the event when app go to foreground
    _backToForegroundlistener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, CC_CALLBACK_1(MeshCommand::listenBackToForeground, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundlistener, -1);
#endif
}

void MeshCommand::init(float globalOrder,
                       GLuint textureID,
                       GLProgramState* glProgramState,
                       BlendFunc blendType,
                       GLuint vertexBuffer,
                       GLuint indexBuffer,
                       GLenum primitive,
                       GLenum indexFormat,
                       ssize_t indexCount,
                       const Mat4 &mv)
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

void MeshCommand::setDisplayColor(const Vec4& color)
{
    _displayColor = color;
}

MeshCommand::~MeshCommand()
{
    releaseVAO();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundlistener);
#endif
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

void MeshCommand::genMaterialID(GLuint texID, void* glProgramState, void* mesh, const BlendFunc& blend)
{
    int* intstate = static_cast<int*>(glProgramState);
    int* intmesh = static_cast<int*>(mesh);
    
    int statekey[] = {intstate[0], 0}, meshkey[] = {intmesh[0], 0};
    if (sizeof(void*) > sizeof(int))
    {
        statekey[1] = intstate[1];
        meshkey[1] = intmesh[1];
    }
    int intArray[] = {(int)texID, statekey[0], statekey[1], meshkey[0], meshkey[1], (int)blend.src, (int)blend.dst};
    _materialID = XXH32((const void*)intArray, sizeof(intArray), 0);
}

void MeshCommand::MatrixPalleteCallBack( GLProgram* glProgram, Uniform* uniform)
{
    glProgram->setUniformLocationWith4fv(uniform->location, (const float*)_matrixPalette, _matrixPaletteSize);
}

void MeshCommand::preBatchDraw()
{
    // set render state
    applyRenderState();
    // Set material
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    if (_vao == 0)
        buildVAO();
    if (_vao)
    {
        GL::bindVAO(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        _glProgramState->applyAttributes();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
}
void MeshCommand::batchDraw()
{
    _glProgramState->setUniformVec4("u_color", _displayColor);
    
    if (_matrixPaletteSize && _matrixPalette)
    {
        _glProgramState->setUniformCallback("u_matrixPalette", CC_CALLBACK_2(MeshCommand::MatrixPalleteCallBack, this));
        
    }
    
    _glProgramState->applyGLProgram(_mv);
    _glProgramState->applyUniforms();
    
    // Draw
    glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);
}
void MeshCommand::postBatchDraw()
{
    //restore render state
    restoreRenderState();
    if (_vao)
    {
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    _glProgramState->setUniformVec4("u_color", _displayColor);
    
    if (_matrixPaletteSize && _matrixPalette)
    {
        _glProgramState->setUniformCallback("u_matrixPalette", CC_CALLBACK_2(MeshCommand::MatrixPalleteCallBack, this));
        
    }
    
    _glProgramState->apply(_mv);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    // Draw
    glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);
    
    //restore render state
    restoreRenderState();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshCommand::buildVAO()
{
    releaseVAO();
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        auto flags = _glProgramState->getVertexAttribsFlags();
        for (int i = 0; flags > 0; i++) {
            int flag = 1 << i;
            if (flag & flags)
                glEnableVertexAttribArray(i);
            flags &= ~flag;
        }
        _glProgramState->applyAttributes(false);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
        
        GL::bindVAO(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
void MeshCommand::releaseVAO()
{
    if (Configuration::getInstance()->supportsShareableVAO() && _vao)
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
        GL::bindVAO(0);
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MeshCommand::listenBackToForeground(EventCustom* event)
{
    releaseVAO();
}
#endif

NS_CC_END
