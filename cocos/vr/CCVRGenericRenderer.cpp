/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

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

#include "platform/CCPlatformMacros.h"
#include "vr/CCVRGenericRenderer.h"
#include "vr/CCVRDistortionMesh.h"
#include "vr/CCVRDistortion.h"
#include "vr/CCVRGenericHeadTracker.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "2d/CCScene.h"
#include "2d/CCCamera.h"
#include "2d/CCSprite.h"
#include "platform/CCGLView.h"


NS_CC_BEGIN

VRGenericRenderer::VRGenericRenderer()
: _vignetteEnabled(true)
, _distortion(nullptr)
, _leftDistortionMesh(nullptr)
, _rightDistortionMesh(nullptr)
, _glProgramState(nullptr)
{
    _headTracker = new VRGenericHeadTracker;
}

VRGenericRenderer::~VRGenericRenderer()
{
    CC_SAFE_DELETE(_headTracker);
    CC_SAFE_RELEASE(_glProgramState);
    CC_SAFE_RELEASE(_fb);
    CC_SAFE_DELETE(_distortion);
    CC_SAFE_DELETE(_leftDistortionMesh);
    CC_SAFE_DELETE(_rightDistortionMesh);
}

void VRGenericRenderer::setup(GLView* glview)
{
//    CC_UNUSED(glview);

    // set origin to 0,0 in case origin is not 0,0
    auto vp = Camera::getDefaultViewport();

    _leftEye.viewport._bottom = vp._bottom/2 + vp._height/4;
    _leftEye.viewport._left = vp._left/4;
    _leftEye.viewport._width = vp._width/2;
    _leftEye.viewport._height = vp._height/2;

    _rightEye.viewport._bottom = vp._bottom/2 + vp._height/4;
    _rightEye.viewport._left = _leftEye.viewport._width + vp._left/2;
    _rightEye.viewport._width = vp._width/2;
    _rightEye.viewport._height = vp._height/2;


    _texSize = Size(vp._width, vp._height);

    _fb = experimental::FrameBuffer::create(1, _texSize.width, _texSize.height);
    _fb->retain();
    auto rt = experimental::RenderTarget::create(_texSize.width, _texSize.height);
    auto ds = experimental::RenderTargetDepthStencil::create(_texSize.width, _texSize.height);
    _fb->attachRenderTarget(rt);
    _fb->attachDepthStencilTarget(ds);
    _fb->setClearColor(Color4F(0,0,0,1));

    _distortion = new Distortion;
    _leftDistortionMesh = createDistortionMesh(VREye::EyeType::LEFT);
    _rightDistortionMesh = createDistortionMesh(VREye::EyeType::RIGHT);

    setupGLProgram();
}

void VRGenericRenderer::cleanup()
{
}

VRIHeadTracker* VRGenericRenderer::getHeadTracker()
{
    return _headTracker;
}

void VRGenericRenderer::render(Scene* scene, Renderer* renderer)
{
    // FIXME: Use correct eye displacement
    const float eyeOffset = 0.5;

    auto headRotation = _headTracker->getLocalRotation();
    Mat4 leftTransform;
    Mat4::createTranslation(eyeOffset, 0, 0, &leftTransform);
    leftTransform *= headRotation;

    Mat4 rightTransform;
    Mat4::createTranslation(-eyeOffset, 0, 0, &rightTransform);
    rightTransform *= headRotation;

    _fb->applyFBO();
    auto defaultVP = Camera::getDefaultViewport();
    Camera::setDefaultViewport(_leftEye.viewport);
    scene->render(renderer, leftTransform, nullptr);
    Camera::setDefaultViewport(_rightEye.viewport);
    scene->render(renderer, rightTransform, nullptr);
    Camera::setDefaultViewport(defaultVP);
    _fb->restoreFBO();

    auto texture = _fb->getRenderTarget()->getTexture();
    GL::bindTexture2D(texture->getName());
    _glProgramState->apply(Mat4::IDENTITY);

    GLint origViewport[4];
    glGetIntegerv(GL_VIEWPORT, origViewport);
    glViewport(0, 0, _texSize.width, _texSize.height);

    renderDistortionMesh(_leftDistortionMesh, texture->getName());
    renderDistortionMesh(_rightDistortionMesh, texture->getName());


    glViewport(origViewport[0], origViewport[1], origViewport[2], origViewport[3]);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

void VRGenericRenderer::renderDistortionMesh(DistortionMesh *mesh, GLint textureID)
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh->_arrayBufferID);

    _glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0 * sizeof(float)));
    _glProgramState->setVertexAttribPointer("a_textureCoord", 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
    _glProgramState->setVertexAttribPointer("a_vignette", 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(4 * sizeof(float)));
    _glProgramState->setUniformTexture("u_textureSampler", textureID);

    _glProgramState->apply(Mat4::IDENTITY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_elementBufferID);
    glDrawElements(GL_TRIANGLE_STRIP, mesh->_indices, GL_UNSIGNED_SHORT, 0);

    CHECK_GL_ERROR_DEBUG();
}

DistortionMesh* VRGenericRenderer::createDistortionMesh(VREye::EyeType eyeType)
{
    auto vp = Camera::getDefaultViewport();

    const float screenWidth = _texSize.width;
    const float screenHeight = _texSize.height;
    const float xEyeOffsetScreen = (eyeType == VREye::EyeType::LEFT) ? screenWidth/4 + vp._left : screenWidth*3/4 + vp._left;
    const float yEyeOffsetScreen = screenHeight/2 + vp._bottom;

    const float textureWidth = _texSize.width;
    const float textureHeight = _texSize.height;
    const float xEyeOffsetTexture = (eyeType == VREye::EyeType::LEFT) ? _texSize.width/4 : _texSize.width*3/4;
    const float yEyeOffsetTexture = _texSize.height/2;

    const float viewportX = (eyeType == VREye::EyeType::LEFT) ? 0 : textureWidth/2;
    const float viewportY = 0;
    const float viewportW = textureWidth/2;
    const float viewportH = textureHeight;

    return new DistortionMesh(_distortion,
                              screenWidth, screenHeight,
                              xEyeOffsetScreen, yEyeOffsetScreen,
                              textureWidth, textureHeight,
                              xEyeOffsetTexture, yEyeOffsetTexture,
                              viewportX, viewportY,
                              viewportW, viewportH,
                              _vignetteEnabled);
}

void VRGenericRenderer::setupGLProgram()
{
    const GLchar *vertexShader =
    "\
    attribute vec2 a_position;\n\
    attribute vec2 a_textureCoord;\n\
    attribute float a_vignette;\n\
    varying vec2 v_textureCoord;\n\
    varying float v_vignette;\n\
    void main() {\n\
    gl_Position = vec4(a_position, 0.0, 1.0);\n\
    v_textureCoord = a_textureCoord.xy;\n\
    v_vignette = a_vignette;\n\
    }\n";

    const GLchar *fragmentShader =
    "\
    #ifdef GL_ES\n\
    precision mediump float;\n\
    #endif\n\
    varying vec2 v_textureCoord;\n\
    varying float v_vignette;\n\
    uniform sampler2D u_textureSampler;\n\
    void main() {\n\
    gl_FragColor = v_vignette * texture2D(u_textureSampler, v_textureCoord);\n\
    }\n";

    auto program = GLProgram::createWithByteArrays(vertexShader, fragmentShader);
    _glProgramState = GLProgramState::getOrCreateWithGLProgram(program);

    _glProgramState->retain();
}

NS_CC_END
