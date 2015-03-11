
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

#ifndef _CC_GRAPHICS_METAL_H_
#define _CC_GRAPHICS_METAL_H_

#include "cocos2d.h"
#include "PAL/CCPALMacros.h"
#include "PAL/interfaces/CCGraphicsInterface.h"

NS_PRIVATE_BEGIN

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#    import "TargetConditionals.h"
#    if !TARGET_IPHONE_SIMULATOR
#        define CC_METAL_AVAILABLE
#        import "Metal/Metal.h"
#    endif // TARGET_IPHONE_SIMULATOR
#endif // CC_PLATFORM_IOS

#ifdef CC_METAL_AVAILABLE

class ViewInterface;
class GLView;

class GraphicsMetal
    : public GraphicsInterface
{
public:
    
    static GraphicsInterface* create();
    
    // @brief initialize the API
    bool init();

    // @brief shuts down this interface.
    void shutdown();
};

#endif//CC_METAL_AVAILABLE

NS_PRIVATE_END

#endif//_CC_GRAPHICS_METAL_H_
