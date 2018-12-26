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
#include "renderer/CCRenderer.h"
#include "renderer/CCShaderCache.h"
#include "renderer/ccShaders.h"

NS_CC_BEGIN

int StencilStateManager::s_layer = -1;

StencilStateManager::StencilStateManager()
{
    auto& vertexLayout = _customCommand.getPipelineDescriptor().vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32, 0, false);
    vertexLayout.setLayout(2 * sizeof(float), backend::VertexStepMode::VERTEX);

    auto& pipelineDescriptor = _customCommand.getPipelineDescriptor();
    pipelineDescriptor.vertexShader = ShaderCache::newVertexShaderModule(positionUColor_vert);
    pipelineDescriptor.fragmentShader = ShaderCache::newFragmentShaderModule(positionUColor_frag);

    Vec2 vertices[4] = {
        Vec2(-1.0f, -1.0f),
        Vec2(1.0f, -1.0f),
        Vec2(1.0f, 1.0f),
        Vec2(-1.0f, 1.0f)
    };
    _customCommand.createVertexBuffer(sizeof(Vec2), 4);
    _customCommand.updateVertexBuffer(vertices, sizeof(vertices));

    unsigned short indices[6] = {0, 1, 2, 0, 2, 3};
    _customCommand.createIndexBuffer(sizeof(unsigned short), 6);
    _customCommand.updateIndexBuffer(indices, sizeof(indices));

    Color4F color(1, 1, 1, 1);
    pipelineDescriptor.bindGroup.setUniform("u_color", &color, sizeof(color));
}

void StencilStateManager::drawFullScreenQuadClearStencil(float globalZOrder)
{
//    Director* director = Director::getInstance();
//    CCASSERT(nullptr != director, "Director is null when setting matrix stack");
//
//    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//
//    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    director->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//
//    Vec2 vertices[] = {
//        Vec2(-1.0f, -1.0f),
//        Vec2(1.0f, -1.0f),
//        Vec2(1.0f, 1.0f),
//        Vec2(-1.0f, 1.0f)
//    };
//
//    auto glProgram = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
//
//    int colorLocation = glProgram->getUniformLocation("u_color");
//    CHECK_GL_ERROR_DEBUG();
//
//    Color4F color(1, 1, 1, 1);
//
//    glProgram->use();
//    glProgram->setUniformsForBuiltins();
//    glProgram->setUniformLocationWith4fv(colorLocation, (GLfloat*) &color.r, 1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
//    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
//
    _customCommand.init(globalZOrder);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
    _customCommand.getPipelineDescriptor().bindGroup.setUniform("u_MVPMatrix", Mat4::IDENTITY.m, sizeof(Mat4::IDENTITY.m));

//    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
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

void StencilStateManager::onBeforeVisit(float globalZOrder)
{
    auto renderer = Director::getInstance()->getRenderer();

    // increment the current layer
    s_layer++;

    // mask of the current layer (ie: for layer 3: 00000100)
    GLint mask_layer = 0x1 << s_layer;
    // mask of all layers less than the current (ie: for layer 3: 00000011)
    GLint mask_layer_l = mask_layer - 1;
    // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
    _mask_layer_le = mask_layer | mask_layer_l;

    _beforeDrawQuadCmd.init(globalZOrder);
    _beforeDrawQuadCmd.func = [=]() -> void {

        // manually save the stencil state

    //    _currentStencilEnabled = glIsEnabled(GL_STENCIL_TEST);
    //    glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint *)&_currentStencilWriteMask);
    //    glGetIntegerv(GL_STENCIL_FUNC, (GLint *)&_currentStencilFunc);
    //    glGetIntegerv(GL_STENCIL_REF, &_currentStencilRef);
    //    glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint *)&_currentStencilValueMask);
    //    glGetIntegerv(GL_STENCIL_FAIL, (GLint *)&_currentStencilFail);
    //    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint *)&_currentStencilPassDepthFail);
    //    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint *)&_currentStencilPassDepthPass);

        _currentStencilEnabled = renderer->getStencilTest();
        _currentStencilWriteMask = renderer->getStencilWriteMask();
        _currentStencilFunc = renderer->getStencilCompareFunction();
        _currentStencilRef = renderer->getStencilReferenceValue();
        _currentStencilReadMask = renderer->getStencilReadMask();
        _currentStencilFail = renderer->getStencilFailureOperation();
        _currentStencilPassDepthFail = renderer->getStencilPassDepthFailureOperation();
        _currentStencilPassDepthPass = renderer->getStencilDepthPassOperation();

        // enable stencil use
    //    glEnable(GL_STENCIL_TEST);
        renderer->setStencilTest(true);
        // check for OpenGL error while enabling stencil test
    //    CHECK_GL_ERROR_DEBUG();

        // all bits on the stencil buffer are readonly, except the current layer bit,
        // this means that operation like glClear or glStencilOp will be masked with this value
    //    glStencilMask(mask_layer);
        renderer->setStencilWriteMask(mask_layer);
        //    RenderState::StateBlock::_defaultState->setStencilWrite(mask_layer);

        // manually save the depth test state

    //    glGetBooleanv(GL_DEPTH_WRITEMASK, &_currentDepthWriteMask);
        _currentDepthWriteMask = renderer->getDepthWrite();

        // disable depth test while drawing the stencil
        //glDisable(GL_DEPTH_TEST);
        // disable update to the depth buffer while drawing the stencil,
        // as the stencil is not meant to be rendered in the real scene,
        // it should never prevent something else to be drawn,
        // only disabling depth buffer update should do
    //    glDepthMask(GL_FALSE);
        renderer->setDepthWrite(false);

        ///////////////////////////////////
        // CLEAR STENCIL BUFFER

        // manually clear the stencil buffer by drawing a fullscreen rectangle on it
        // setup the stencil test func like this:
        // for each pixel in the fullscreen rectangle
        //     never draw it into the frame buffer
        //     if not in inverted mode: set the current layer value to 0 in the stencil buffer
        //     if in inverted mode: set the current layer value to 1 in the stencil buffer
    //    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
    //    glStencilOp(!_inverted ? GL_ZERO : GL_REPLACE, GL_KEEP, GL_KEEP);
        renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, mask_layer, mask_layer);
        renderer->setStencilOperation(!_inverted ? backend::StencilOperation::ZERO : backend::StencilOperation::REPLACE,
                                      backend::StencilOperation::KEEP,
                                      backend::StencilOperation::KEEP);
    };
    renderer->addCommand(&_beforeDrawQuadCmd);

    // draw a fullscreen solid rectangle to clear the stencil buffer
    //ccDrawSolidRect(Vec2::ZERO, ccpFromSize([[Director sharedDirector] winSize]), Color4F(1, 1, 1, 1));
    drawFullScreenQuadClearStencil(globalZOrder);

    _afterDrawQuadCmd.init(globalZOrder);
    _afterDrawQuadCmd.func = [=]() -> void {
        // setup the stencil test func like this:
        // for each pixel in the stencil node
        //     never draw it into the frame buffer
        //     if not in inverted mode: set the current layer value to 1 in the stencil buffer
        //     if in inverted mode: set the current layer value to 0 in the stencil buffer
    //    glStencilFunc(GL_NEVER, mask_layer, mask_layer);
        auto renderer = Director::getInstance()->getRenderer();
        renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, mask_layer, mask_layer);
        //    RenderState::StateBlock::_defaultState->setStencilFunction(RenderState::STENCIL_NEVER, mask_layer, mask_layer);

    //    glStencilOp(!_inverted ? GL_REPLACE : GL_ZERO, GL_KEEP, GL_KEEP);
        renderer->setStencilOperation(!_inverted ? backend::StencilOperation::REPLACE : backend::StencilOperation::ZERO,
                                      backend::StencilOperation::KEEP,
                                      backend::StencilOperation::KEEP);
    };
    renderer->addCommand(&_afterDrawQuadCmd);
}

void StencilStateManager::onAfterDrawStencil()
{
//    // restore alpha test state
//    if (_alphaThreshold < 1)
//    {
//#if CC_CLIPPING_NODE_OPENGLES
//        // FIXME: we need to find a way to restore the shaders of the stencil node and its children
//#else
//        // manually restore the alpha test state
//        glAlphaFunc(_currentAlphaTestFunc, _currentAlphaTestRef);
//        if (!_currentAlphaTestEnabled)
//        {
//            glDisable(GL_ALPHA_TEST);
//        }
//#endif
//    }

    // restore the depth test state
//    glDepthMask(_currentDepthWriteMask);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setDepthWrite(_currentDepthWriteMask);
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
//    glStencilFunc(GL_EQUAL, _mask_layer_le, _mask_layer_le);
    renderer->setStencilCompareFunction(backend::CompareFunction::EQUAL, _mask_layer_le, _mask_layer_le);

//    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    renderer->setStencilOperation(backend::StencilOperation::KEEP, backend::StencilOperation::KEEP, backend::StencilOperation::KEEP);

    // draw (according to the stencil test function) this node and its children

}

void StencilStateManager::onAfterVisit()
{
    ///////////////////////////////////
    // CLEANUP
    
    // manually restore the stencil state
//    glStencilFunc(_currentStencilFunc, _currentStencilRef, _currentStencilValueMask);
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setStencilCompareFunction(_currentStencilFunc, _currentStencilRef, _currentStencilReadMask);

//    glStencilOp(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);
    renderer->setStencilOperation(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);

//    glStencilMask(_currentStencilWriteMask);
    renderer->setStencilWriteMask(_currentStencilWriteMask);
    if (!_currentStencilEnabled)
    {
//        glDisable(GL_STENCIL_TEST);
        renderer->setStencilTest(false);
    }
    
    // we are done using this layer, decrement
    s_layer--;
}


NS_CC_END
