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
#include "renderer/ccShaders.h"
#include "renderer/backend/ProgramState.h"

NS_CC_BEGIN

int StencilStateManager::s_layer = -1;

StencilStateManager::StencilStateManager()
{
    auto& pipelineDescriptor = _customCommand.getPipelineDescriptor();
    auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::POSITION_UCOLOR);
    _programState = new (std::nothrow) backend::ProgramState(program);
    pipelineDescriptor.programState = _programState;
    
    auto vertexLayout = _programState->getVertexLayout();
    const auto& attributeInfo = _programState->getProgram()->getActiveAttributes();
    auto iter = attributeInfo.find("a_position");
    if(iter != attributeInfo.end())
    {
        vertexLayout->setAttribute("a_position", iter->second.location, backend::VertexFormat::FLOAT2, 0, false);
    }
    vertexLayout->setLayout(2 * sizeof(float));

    _mvpMatrixLocaiton = pipelineDescriptor.programState->getUniformLocation("u_MVPMatrix");
    _colorUniformLocation = pipelineDescriptor.programState->getUniformLocation("u_color");
    
   
    Vec2 vertices[4] = {
        Vec2(-1.0f, -1.0f),
        Vec2(1.0f, -1.0f),
        Vec2(1.0f, 1.0f),
        Vec2(-1.0f, 1.0f)
    };
    _customCommand.createVertexBuffer(sizeof(Vec2), 4, CustomCommand::BufferUsage::STATIC);
    _customCommand.updateVertexBuffer(vertices, sizeof(vertices));

    unsigned short indices[6] = {0, 1, 2, 0, 2, 3};
    _customCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, 6, CustomCommand::BufferUsage::STATIC);
    _customCommand.updateIndexBuffer(indices, sizeof(indices));

    Color4F color(1, 1, 1, 1);
    pipelineDescriptor.programState->setUniform(_colorUniformLocation, &color, sizeof(color));
}

StencilStateManager::~StencilStateManager()
{
    CC_SAFE_RELEASE(_programState);
}

void StencilStateManager::drawFullScreenQuadClearStencil(float globalZOrder)
{
    _customCommand.init(globalZOrder);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
    _programState->setUniform(_mvpMatrixLocaiton, Mat4::IDENTITY.m, sizeof(Mat4::IDENTITY.m));
}


void StencilStateManager::setAlphaThreshold(float alphaThreshold)
{
    _alphaThreshold = alphaThreshold;
}

float StencilStateManager::getAlphaThreshold()const
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

void StencilStateManager::updateLayerMask()
{
    // increment the current layer
    s_layer++;

    // mask of the current layer (ie: for layer 3: 00000100)
    _currentLayerMask = 0x1 << s_layer;
    // mask of all layers less than the current (ie: for layer 3: 00000011)
    int mask_layer_l = _currentLayerMask - 1;
    // mask of all layers less than or equal to the current (ie: for layer 3: 00000111)
    _mask_layer_le = _currentLayerMask | mask_layer_l;
}

void StencilStateManager::onBeforeVisit(float globalZOrder)
{
    _customCommand.setBeforeCallback(CC_CALLBACK_0(StencilStateManager::onBeforeDrawQuadCmd, this));
    _customCommand.setAfterCallback(CC_CALLBACK_0(StencilStateManager::onAfterDrawQuadCmd, this));

    // draw a fullscreen solid rectangle to clear the stencil buffer
    drawFullScreenQuadClearStencil(globalZOrder);

}

void StencilStateManager::onBeforeDrawQuadCmd()
{
    auto renderer = Director::getInstance()->getRenderer();
    updateLayerMask();
    // manually save the stencil state
    _currentStencilEnabled = renderer->getStencilTest();
    _currentStencilWriteMask = renderer->getStencilWriteMask();
    _currentStencilFunc = renderer->getStencilCompareFunction();
    _currentStencilRef = renderer->getStencilReferenceValue();
    _currentStencilReadMask = renderer->getStencilReadMask();
    _currentStencilFail = renderer->getStencilFailureOperation();
    _currentStencilPassDepthFail = renderer->getStencilPassDepthFailureOperation();
    _currentStencilPassDepthPass = renderer->getStencilDepthPassOperation();

    // enable stencil use
    renderer->setStencilTest(true);

    // all bits on the stencil buffer are readonly, except the current layer bit,
    // this means that operation like glClear or glStencilOp will be masked with this value
    renderer->setStencilWriteMask(_currentLayerMask);

    // manually save the depth test state

    _currentDepthWriteMask = renderer->getDepthWrite();

    // disable update to the depth buffer while drawing the stencil,
    // as the stencil is not meant to be rendered in the real scene,
    // it should never prevent something else to be drawn,
    // only disabling depth buffer update should do
    renderer->setDepthWrite(false);

    ///////////////////////////////////
    // CLEAR STENCIL BUFFER

    // manually clear the stencil buffer by drawing a fullscreen rectangle on it
    // setup the stencil test func like this:
    // for each pixel in the fullscreen rectangle
    //     never draw it into the frame buffer
    //     if not in inverted mode: set the current layer value to 0 in the stencil buffer
    //     if in inverted mode: set the current layer value to 1 in the stencil buffer
    renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, _currentLayerMask, _currentLayerMask);
    renderer->setStencilOperation(!_inverted ? backend::StencilOperation::ZERO : backend::StencilOperation::REPLACE,
        backend::StencilOperation::KEEP,
        backend::StencilOperation::KEEP);
}

void StencilStateManager::onAfterDrawQuadCmd()
{
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setStencilCompareFunction(backend::CompareFunction::NEVER, _currentLayerMask, _currentLayerMask);

    renderer->setStencilOperation(!_inverted ? backend::StencilOperation::REPLACE : backend::StencilOperation::ZERO,
        backend::StencilOperation::KEEP,
        backend::StencilOperation::KEEP);
}

void StencilStateManager::onAfterDrawStencil()
{
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
    renderer->setStencilCompareFunction(backend::CompareFunction::EQUAL, _mask_layer_le, _mask_layer_le);

    renderer->setStencilOperation(backend::StencilOperation::KEEP, backend::StencilOperation::KEEP, backend::StencilOperation::KEEP);

    // draw (according to the stencil test function) this node and its children

}

void StencilStateManager::onAfterVisit()
{
    ///////////////////////////////////
    // CLEANUP
    
    // manually restore the stencil state
    auto renderer = Director::getInstance()->getRenderer();
    renderer->setStencilCompareFunction(_currentStencilFunc, _currentStencilRef, _currentStencilReadMask);

    renderer->setStencilOperation(_currentStencilFail, _currentStencilPassDepthFail, _currentStencilPassDepthPass);

    renderer->setStencilWriteMask(_currentStencilWriteMask);
    if (!_currentStencilEnabled)
    {
        renderer->setStencilTest(false);
    }
    
    // we are done using this layer, decrement
    s_layer--;
}


NS_CC_END
