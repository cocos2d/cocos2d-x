/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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

#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

/**
Callback command is used to invoke a callback function when this command is
executed. You can do some logic opertion in the callback, such as invoking
renderer to set depth/stencil test. Don't suggest to invoke backen API in
the callback function.
*/
class CC_DLL CallbackCommand : public RenderCommand
{
public:
    CallbackCommand();

    void init(float globalZOrder);
    void init(float globalZorder, const Mat4 &transform, unsigned int);

    /**
     Execute the render command and call callback functions.
     */
    void execute();
    /**Callback function.*/
    std::function<void()> func;
};

/**
 * CaptureScreenCallbackCommand is used to capture the screen.
 */
class CC_DLL CaptureScreenCallbackCommand : public RenderCommand
{
public:
    CaptureScreenCallbackCommand();
    
    void init(float globalZOrder);
    
    /**
     * A callback function to do with the image after capture from the color buffer.
     */
    std::function<void(const unsigned char*, int, int)> func;
};

NS_CC_END
/**
 end of support group
 @}
 */
