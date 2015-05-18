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
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "2d/CCLight.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCPass.h"
#include "xxhash.h"

NS_CC_BEGIN


MeshCommand::MeshCommand()
: _textureID(0)
, _glProgramState(nullptr)
, _blendType(BlendFunc::DISABLE)
, _displayColor(1.0f, 1.0f, 1.0f, 1.0f)
, _matrixPalette(nullptr)
, _matrixPaletteSize(0)
, _materialID(0)
, _vao(0)
, _cullFaceEnabled(false)
, _cullFace(GL_BACK)
, _depthTestEnabled(false)
, _depthWriteEnabled(false)
, _forceDepthWrite(false)
, _renderStateCullFaceEnabled(false)
, _renderStateDepthTest(false)
, _renderStateDepthWrite(GL_FALSE)
, _material(nullptr)
{
    _type = RenderCommand::Type::MESH_COMMAND;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // listen the event that renderer was recreated on Android/WP8
    _rendererRecreatedListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, CC_CALLBACK_1(MeshCommand::listenRendererRecreated, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_rendererRecreatedListener, -1);
#endif
}

void MeshCommand::init(float globalZOrder,
                       Material* material,
                       GLuint vertexBuffer,
                       GLuint indexBuffer,
                       GLenum primitive,
                       GLenum indexFormat,
                       ssize_t indexCount,
                       const cocos2d::Mat4 &mv,
                       uint32_t flags)
{
    CCASSERT(material, "material cannot be nill");

    RenderCommand::init(globalZOrder, mv, flags);

    _globalOrder = globalZOrder;
    _material = material;
    
    _vertexBuffer = vertexBuffer;
    _indexBuffer = indexBuffer;
    _primitive = primitive;
    _indexFormat = indexFormat;
    _indexCount = indexCount;
    _mv.set(mv);

    _is3D = true;
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
    init(globalOrder, textureID, glProgramState, blendType, vertexBuffer, indexBuffer, primitive, indexFormat, indexCount, mv, 0);
}

void MeshCommand::init(float globalZOrder,
                       GLuint textureID,
                       cocos2d::GLProgramState *glProgramState,
                       cocos2d::BlendFunc blendType,
                       GLuint vertexBuffer,
                       GLuint indexBuffer,
                       GLenum primitive,
                       GLenum indexFormat,
                       ssize_t indexCount,
                       const cocos2d::Mat4 &mv,
                       uint32_t flags)
{
    CCASSERT(glProgramState, "GLProgramState cannot be nill");
    
    RenderCommand::init(globalZOrder, mv, flags);
    
    _globalOrder = globalZOrder;
    _textureID = textureID;
    _blendType = blendType;
    _glProgramState = glProgramState;
    
    _vertexBuffer = vertexBuffer;
    _indexBuffer = indexBuffer;
    _primitive = primitive;
    _indexFormat = indexFormat;
    _indexCount = indexCount;
    _mv.set(mv);
    
    _is3D = true;
}

void MeshCommand::setCullFaceEnabled(bool enable)
{
    CCASSERT(!_material, "If using material, you should call material->setCullFace()");

    _cullFaceEnabled = enable;
}

void MeshCommand::setCullFace(GLenum cullFace)
{
    CCASSERT(!_material, "If using material, you should call material->setCullFaceSide()");

    _cullFace = cullFace;
}

void MeshCommand::setDepthTestEnabled(bool enable)
{
    CCASSERT(!_material, "If using material, you should call material->setDepthTest()");

    _depthTestEnabled = enable;
}

void MeshCommand::setDepthWriteEnabled(bool enable)
{
    CCASSERT(!_material, "If using material, you should call material->setDepthWrite()");

    _forceDepthWrite = enable;
    _depthWriteEnabled = enable;
}

void MeshCommand::setDisplayColor(const Vec4& color)
{
    CCASSERT(!_material, "If using material, you should set the color as a uniform: use u_color");

    _displayColor = color;
}

void MeshCommand::setMatrixPalette(const Vec4* matrixPalette)
{
    CCASSERT(!_material, "If using material, you should set the color as a uniform: use u_matrixPalette");

    _matrixPalette = matrixPalette;
}

void MeshCommand::setMatrixPaletteSize(int size)
{
    CCASSERT(!_material, "If using material, you should set the color as a uniform: use u_matrixPalette with its size");

    _matrixPaletteSize = size;
}

void MeshCommand::setTransparent(bool value)
{
    CCASSERT(!_material, "If using material, you shouldn't call setTransparent.");

    _isTransparent = value;
    //Skip batching for transparent mesh
    _skipBatching = value;
    
    if (_isTransparent && !_forceDepthWrite)
    {
        _depthWriteEnabled = false;
    }
    else
    {
        _depthWriteEnabled = true;
    }
}

MeshCommand::~MeshCommand()
{
    releaseVAO();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_rendererRecreatedListener);
#endif
}

void MeshCommand::applyRenderState()
{
    CCASSERT(!_material, "Must not be called when using materials");

    // blend and texture
    GL::bindTexture2D(_textureID);
    GL::blendFunc(_blendType.src, _blendType.dst);

    // cull face
    _renderStateCullFaceEnabled = glIsEnabled(GL_CULL_FACE) != GL_FALSE;
    GLint cullface;
    glGetIntegerv(GL_CULL_FACE_MODE, &cullface);
    _renderStateCullFace = (GLenum)cullface;
    
    if (_cullFaceEnabled != _renderStateCullFaceEnabled)
    {
        _cullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    }
    
    if (_cullFace != _renderStateCullFace)
    {
        glCullFace(_cullFace);
    }

    // depth
    _renderStateDepthTest = (glIsEnabled(GL_DEPTH_TEST) != GL_FALSE);
    glGetBooleanv(GL_DEPTH_WRITEMASK, &_renderStateDepthWrite);

    if (_depthTestEnabled != _renderStateDepthTest)
    {
        _depthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    if (_depthWriteEnabled != _renderStateDepthWrite)
    {
        glDepthMask(_depthWriteEnabled);
    }
}

void MeshCommand::restoreRenderState()
{
    CCASSERT(!_material, "Must not be called when using Material");

    // cull
    if (_cullFaceEnabled != _renderStateCullFaceEnabled)
    {
        _renderStateCullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    }

    if (_cullFace != _renderStateCullFace)
    {
        glCullFace(_renderStateCullFace);
    }

    // depth
    if (_depthTestEnabled != _renderStateDepthTest)
    {
        _renderStateDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    if (_depthWriteEnabled != _renderStateDepthWrite)
    {
        glDepthMask(_renderStateDepthWrite);
    }
}

void MeshCommand::genMaterialID(GLuint texID, void* glProgramState, GLuint vertexBuffer, GLuint indexBuffer, BlendFunc blend)
{
    int intArray[7] = {0};
    intArray[0] = (int)texID;
    *(int**)&intArray[1] = (int*) glProgramState;
    intArray[3] = (int) vertexBuffer;
    intArray[4] = (int) indexBuffer;
    intArray[5] = (int) blend.src;
    intArray[6] = (int) blend.dst;
    _materialID = XXH32((const void*)intArray, sizeof(intArray), 0);
}

uint32_t MeshCommand::getMaterialID() const
{
    return _materialID;
}

void MeshCommand::preBatchDraw()
{
    if (Configuration::getInstance()->supportsShareableVAO() && _vao == 0)
        buildVAO();
    if (_vao)
    {
        GL::bindVAO(_vao);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

        // FIXME: Assumes that all the passes in the Material share the same Vertex Attribs
        GLProgramState* programState = _material
                                        ? _material->_currentTechnique->_passes.at(0)->getGLProgramState()
                                        : _glProgramState;
        programState->applyAttributes();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }
}

void MeshCommand::batchDraw()
{
    if (_material)
    {
        for(const auto& pass: _material->_currentTechnique->_passes)
        {
            // don't bind attributes, since they were
            // already bound in preBatchDraw
            pass->bind(_mv, false);

            glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);

            pass->unbind();
        }
    }
    else
    {
        _glProgramState->applyGLProgram(_mv);

        // set render state
        applyRenderState();

        // Draw
        glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);

        //restore render state
        restoreRenderState();
    }
}
void MeshCommand::postBatchDraw()
{
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
    // Draw without VAO
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

    if (_material)
    {
        for(const auto& pass: _material->_currentTechnique->_passes)
        {
            // don't bind attributes, since they were
            // already bound in preBatchDraw
            pass->bind(_mv, true);

            glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
            CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);

            pass->unbind();
        }
    }
    else
    {
        // set render state
        _glProgramState->apply(_mv);

        applyRenderState();

        // Draw
        glDrawElements(_primitive, (GLsizei)_indexCount, _indexFormat, 0);
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _indexCount);

        //restore render state
        restoreRenderState();
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshCommand::buildVAO()
{
    // FIXME: Assumes that all the passes in the Material share the same Vertex Attribs
    GLProgramState* programState = (_material != nullptr)
                                    ? _material->_currentTechnique->_passes.at(0)->getGLProgramState()
                                    : _glProgramState;

    releaseVAO();
    glGenVertexArrays(1, &_vao);
    GL::bindVAO(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    auto flags = programState->getVertexAttribsFlags();
    for (int i = 0; flags > 0; i++) {
        int flag = 1 << i;
        if (flag & flags)
            glEnableVertexAttribArray(i);
        flags &= ~flag;
    }
    programState->applyAttributes(false);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    
    GL::bindVAO(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void MeshCommand::releaseVAO()
{
    if (_vao)
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
        GL::bindVAO(0);
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
void MeshCommand::listenRendererRecreated(EventCustom* event)
{
    _vao = 0;
}

#endif

NS_CC_END
