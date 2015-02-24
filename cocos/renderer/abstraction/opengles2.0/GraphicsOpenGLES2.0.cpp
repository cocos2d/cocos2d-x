
/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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

#include "renderer/abstraction/opengles2.0/GraphicsOpenGLES2.0.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

auto GraphicsOpenGLES20::create() -> std::unique_ptr<GraphicsInterface>
{
    auto obj = new GraphicsOpenGLES20;
    if (obj && obj->init())
        return std::unique_ptr<GraphicsInterface>(obj);
    CC_SAFE_DELETE(obj);
    return nullptr;
}

// @brief create a uninitialized view.
handle GraphicsOpenGLES20::viewCreate()
{
    return nullptr;
}

// @brief create a view with coordinates.
handle GraphicsOpenGLES20::viewCreateWithRect(const Rect& rect)
{
    return nullptr;
}

// @brief create a full screen view.
handle GraphicsOpenGLES20::viewCreateFullscreen()
{
    return nullptr;
}

// @brief create a view from a native object.
handle GraphicsOpenGLES20::viewCreateWithNative(handle native)
{
    return nullptr;
}

//
// Protected Methods
//

auto GraphicsOpenGLES20::init() -> bool
{
    return true;
}

NS_CC_END