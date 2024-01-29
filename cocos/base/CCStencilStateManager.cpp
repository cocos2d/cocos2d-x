/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#include "base/CCStencilStateManager.h"
#include "base/CCDirector.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#define CC_CLIPPING_NODE_OPENGLES 0
#else
#define CC_CLIPPING_NODE_OPENGLES 1
#endif

NS_CC_BEGIN

GLint StencilStateManager::s_layer = -1;

StencilStateManager::StencilStateManager()
: _alphaThreshold(1.0f)
, _inverted(false)
, _currentStencilEnabled(GL_FALSE)
, _currentStencilWriteMask(~0)
, _currentStencilFunc(GL_ALWAYS)
, _currentStencilRef(0)
, _currentStencilValueMask(~0)
, _currentStencilFail(GL_KEEP)
, _currentStencilPassDepthFail(GL_KEEP)
, _currentStencilPassDepthPass(GL_KEEP)
, _currentDepthWriteMask(GL_TRUE)
,  _currentAlphaTestEnabled(GL_FALSE)
, _currentAlphaTestFunc(GL_ALWAYS)
, _currentAlphaTestRef(1)

{
}

void StencilStateManager::drawFullScreenQuadClearStencil()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    Vec2 vertices[] = {
        Vec2(-1.0f, -1.0f),
        Vec2(1.0f, -1.0f),
        Vec2(1.0f, 1.0f),
        Vec2(-1.0f, 1.0f)
    };
    
    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    
    int colorLocation = glProgram->getUniformLocation("u_color");
    CHECK_GL_ERROR_DEBUG();
    
    Color4F color(1, 1, 1, 1);
    
    glProgram->use();
    glProgram->setUniformsForBuiltins();
    glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}


void StencilStateManager::setAlphaThreshold(GLfloat alphaThreshold)
{
    _alphaThreshold = alphaThreshold;
}

GLfloat StencilStateManager::getAlphaThreshold()const
{
    return _alphaThreshold;
}

void StencilStateManager::setInverted(bool inverted)
{
    _inverted = inverted;
}

bool StencilStateManager::isInverted()const
{
    return _inverted;
}

void StencilStateManager::onBeforeVisit()
{
    ///////////////////////////////////
    // INIT
    
    // increment the current layer
    s_layer++;
    
    // mask of the current layer (ie: for layer 3: 00000100)
    GLint mask_layer = 0x1 << s_layer;
    // mask of all layers less than the current (ie: for layer 3: 00000011)
    GLint mask_layer_l = mask_layer - 1;
    // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
    _mask_layer_le = mask_layer | mask_layer_l;
    
    // manually save the stencil state
    
    _currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&_currentStencilWriteMask);
    glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&_currentStencilFunc);
    glGetIntegerv(GL_STENCIL_REF, &_currentStencilRef);
    glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&_currentStencilValueMask);
    glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&_currentStencilFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&_currentStencilPassDepthFail);
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&_currentStencilPassDepthPass);
    
    // enable stencil use
    glEnable(GL_STENCIL_TEST);
    //    RenderState::StateBlock::_defaultState->setStencilTest(true);
    
    // check for OpenGL error while enabling stencil test
    CHECK_GL_ERROR_DEBUG();
    
    // all bits on the stencil buffer are readonly, except the current layer bit,
    // this means that operation like glClear or glStencilOp will be masked with this value
    glStencilMask(mask_layer);
    //    RenderState::StateBlock::_defaultState->setStencilWrite(mask_layer);
    
    // manually save the depth test state
    
    glGetBooleanv(GL_DEPTH_WRITEMASK, &_currentDepthWriteMask);
    
    // disable depth test while drawing the stencil
    //glDisable(GL_DEPTH_TEST);
    // disable update to the depth buffer while drawing the stencil,
    // as the stencil is not meant to be rendered in the real scene,
    // it should never prevent something else to be drawn,
    // only disabling depth buffer update should do
    glDepthMask(GL_FALSE);
    RenderState::StateBlock::_defaultState->setDepthWrite(false);
    
    ///////////////////////////////////
    // CLEAR STENCIL BUFFER
    
    // manually clear the stencil buffer by drawing a fullscreen rectangle on it
    // setup the stencil test func like this:
    // for each pixel in the fullscreen rectangle
    //     never draw it into the frame buffer
    //     if not in inverted mode: set the current layer value to 0 in the stencil buffer
    //     if in inverted mode: set the current layer value to 1 in the stencil buffer
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    glStencilOp(!_inverted ? GL_ZERO : GL_REPLACE, GL_KEEP, GL_KEEP);
    
    // draw a fullscreen solid rectangle to clear the stencil buffer
    //ccDrawSolidRect(Vec2::ZERO, ccpFromSize([[Director sharedDirector] winSize]), Color4F(1, 1, 1, 1));
    drawFullScreenQuadClearStencil();
    
    ///////////////////////////////////
    // DRAW CLIPPING STENCIL
    
    // setup the stencil test func like this:
    // for each pixel in the stencil node
    //     never draw it into the frame buffer
    //     if not in inverted mode: set the current layer value to 1 in the stencil buffer
    //     if in inverted mode: set the current layer value to 0 in the stencil buffer
    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    //    RenderState::StateBlock::_defaultState->setStencilFunction(RenderState::STENCIL_NEVER, mask_layer, mask_layer);
    
    glStencilOp(!_inverted ? GL_REPLACE : GL_ZERO, GL_KEEP, GL_KEEP);
    //    RenderState::StateBlock::_defaultState->setStencilOperation(
    //                                                                !_inverted ? RenderState::STENCIL_OP_REPLACE : RenderState::STENCIL_OP_ZERO,
    //                                                                RenderState::STENCIL_OP_KEEP,
    //                                                                RenderState::STENCIL_OP_KEEP);
    
    
    // enable alpha test only if the alpha threshold < 1,
    // indeed if alpha threshold == 1, every pixel will be drawn anyways
    if (_alphaThreshold < 1) {
#if !CC_CLIPPING_NODE_OPENGLES
        // manually save the alpha test state
        _currentAlphaTestEnabled = glIsEnabled(GL_ALPHA_TEST);
        glGetIntegerv(GL_ALPHA_TEST_FUNC, (GLint *)&_currentAlphaTestFunc);
        glGetFloatv(GL_ALPHA_TEST_REF, &_currentAlphaTestRef);
        // enable alpha testing
        glEnable(GL_ALPHA_TEST);
        // check for OpenGL error while enabling alpha test
        CHECK_GL_ERROR_DEBUG();
        // pixel will be drawn only if greater than an alpha threshold
        glAlphaFunc(GL_GREATER, _alphaThreshold);
#endif
    }
    
    //Draw _stencil
}

void StencilStateManager::onAfterDrawStencil()
{
    // restore alpha test state
    if (_alphaThreshold < 1)
    {
#if CC_CLIPPING_NODE_OPENGLES
        // FIXME: we need to find a way to restore the shaders of the stencil node and its children
#else
        // manually restore the alpha test state
        glAlphaFunc(_currentAlphaTestFunc, _currentAlphaTestRef);
        if (!_currentAlphaTestEnabled)
        {
            glDisable(GL_ALPHA_TEST);
        }
#endif
    }
    
    // restore the depth test state
    glDepthMask(_currentDepthWriteMask);
    RenderState::StateBlock::_defaultState->setDepthWrite(_currentDepthWriteMask != 0);
    
    //if (currentDepthTestEnabled) {
    //    glEnable(GL_DEPTH_TEST);
    //}
    
    ///////////////////////////////////
    // DRAW CONTENT
    
    // setup the stencil test function like this:
    // for each pixel of this node and its children
    //     if all layers less than or equals to the current are set to 1 in the stencil buffer
    //         draw the pixel and keep the current layer in the stencil buffer
    //     else
    //         do not draw the pixel but keep the current layer in the stencil buffer
    glStencilFunc(GL_EQUAL, _mask_layer_le, _mask_layer_le);
    //    RenderState::StateBlock::_defaultState->setStencilFunction(RenderState::STENCIL_EQUAL, _mask_layer_le, _mask_layer_le);
    
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    //    RenderState::StateBlock::_defaultState->setStencilOperation(RenderState::STENCIL_OP_KEEP, RenderState::STENCIL_OP_KEEP, RenderState::STENCIL_OP_KEEP);
    
    // draw (according to the stencil test function) this node and its children

}

void StencilStateManager::onAfterVisit()
{
    ///////////////////////////////////
    // CLEANUP
    
    // manually restore the stencil state
    glStencilFunc(_currentStencilFunc, _currentStencilRef, _currentStencilValueMask);
    //    RenderState::StateBlock::_defaultState->setStencilFunction((RenderState::StencilFunction)_currentStencilFunc, _currentStencilRef, _currentStencilValueMask);
    
    glStencilOp(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);
    //    RenderState::StateBlock::_defaultState->setStencilOperation((RenderState::StencilOperation)_currentStencilFail,
    //                                                                (RenderState::StencilOperation)_currentStencilPassDepthFail,
    //                                                                (RenderState::StencilOperation)_currentStencilPassDepthPass);
    
    glStencilMask(_currentStencilWriteMask);
    if (!_currentStencilEnabled)
    {
        glDisable(GL_STENCIL_TEST);
        //        RenderState::StateBlock::_defaultState->setStencilTest(false);
    }
    
    // we are done using this layer, decrement
    s_layer--;
}


NS_CC_END
