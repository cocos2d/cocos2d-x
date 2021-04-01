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
#pragma once

#include "base/ccConfig.h"
#include "platform/CCPlatformMacros.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCCallbackCommand.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

class CC_DLL StencilStateManager
{
public:
    StencilStateManager();
    ~StencilStateManager();
    void onBeforeVisit(float globalZOrder);
    void onAfterDrawStencil();
    void onAfterVisit();
    void setAlphaThreshold(float alphaThreshold);
    void setInverted(bool inverted);
    bool isInverted()const;
    float getAlphaThreshold()const;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(StencilStateManager);
    static int s_layer;
    /**draw fullscreen quad to clear stencil bits
     */
    void drawFullScreenQuadClearStencil(float globalZOrder);
    
    void updateLayerMask();
    void onBeforeDrawQuadCmd();
    void onAfterDrawQuadCmd();
    
    float _alphaThreshold = 1.f;
    bool _inverted = false;
    
    bool _currentStencilEnabled = false;
    unsigned int _currentStencilWriteMask = ~0;
    backend::CompareFunction _currentStencilFunc = backend::CompareFunction::ALWAYS;
    unsigned int _currentStencilRef = 0;
    unsigned int _currentStencilReadMask = ~0;
    backend::StencilOperation _currentStencilFail = backend::StencilOperation::KEEP;
    backend::StencilOperation _currentStencilPassDepthFail = backend::StencilOperation::KEEP;
    backend::StencilOperation _currentStencilPassDepthPass = backend::StencilOperation::KEEP;
    bool _currentDepthWriteMask = true;

    unsigned int _mask_layer_le = 0;
    int _currentLayerMask = 0;

    CustomCommand _customCommand;
    CallbackCommand _afterDrawStencilCmd;
    CallbackCommand _afterVisitCmd;
    
    backend::UniformLocation _mvpMatrixLocaiton;
    backend::UniformLocation _colorUniformLocation;
    backend::ProgramState* _programState = nullptr;
};

NS_CC_END
// end of base group
/** @} */
