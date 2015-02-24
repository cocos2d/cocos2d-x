
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

#ifndef _CC_GRAPHICS_OPEN_GL_ES_20_H_
#define _CC_GRAPHICS_OPEN_GL_ES_20_H_

#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "renderer/abstraction/interface/GraphicsInterface.h"

NS_CC_BEGIN

class GraphicsOpenGLES20
    : public Ref
    , public GraphicsInterface
{
public:
    
    static auto create() -> std::unique_ptr<GraphicsInterface>;
    
    //
    // View Interface Commands
    //
    
    // @brief create a uninitialized view.
    handle viewCreate();
    
    // @brief create a view with coordinates.
    handle viewCreateWithRect(const Rect& rect);
    
    // @brief create a full screen view.
    handle viewCreateFullscreen();
    
    // @brief create a view from a native object.
    handle viewCreateWithNative(handle native);

protected:
    
    // @brief initialize the API
    auto init() -> bool;
};

NS_CC_END

#endif // _CC_GRAPHICS_OPEN_GL_ES_20_H_