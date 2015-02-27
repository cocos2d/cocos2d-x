
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

#ifndef _CC_GRAPHICS_INTERFACE_H_
#define _CC_GRAPHICS_INTERFACE_H_

#include <memory>
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class ViewInterface;

using handle = void*;

class GraphicsInterface
{
public:
    
    virtual ~GraphicsInterface() {}
    
    // @brief shuts down this interface, releasing all resources.
    // All weak references and cached interfaces are invalidated.
    virtual void shutdown() = 0;

    // @brief gets/creates the view for the currently selected api.
    // no need to delete or lifetime manage in any way.
    virtual ViewInterface* getView() const = 0;
    
    // @brief converts the GraphicsInterface into one of its organizational sub interfaces
    // @usage this->as<ViewInterface>()->someMethod. Compile time check is performed.
    template <class T>
    T* as() { return static_cast<T*>(this); }
    
    
    /* texture API
     - create texture from pixels, store pixels to texture buffer
     - set sampling options (interpolation, clamping etc.)
     - mipmaps
     - upload new data
     */
    
};

NS_CC_END

#endif // _CC_GRAPHICS_INTERFACE_H_