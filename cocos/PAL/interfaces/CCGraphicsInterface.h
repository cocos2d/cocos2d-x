
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

#include "PAL/CCPALMacros.h"
#include "base/CCRef.h"

NS_PAL_BEGIN

class GraphicsInterface
    : public NS_CC::Ref
{
public:
    
    typedef intptr_t handle;
    
    virtual ~GraphicsInterface() {}
    
    // @brief initializes the graphics API
    // Some methods can be called before this to set specific features.
    virtual bool init() = 0;
    
    // @brief shuts down this interface, releasing all resources.
    // All weak references and cached interfaces are invalidated.
    virtual void shutdown() = 0;
    
    // @brief returns true or false depending on whether or not geometry state objects are supported.
    virtual bool supportsGeometryState() = 0;
    
    // @brief creates a geometry state object.
    virtual handle createGeometryState() = 0;
    
    // @brief delete a geometry state object.
    virtual bool deleteGeometryState(handle object) = 0;
    
    // @brief binds a geometry state object.
    virtual bool bindGeometryState(handle object) = 0;
};

NS_PAL_END

#endif//_CC_GRAPHICS_INTERFACE_H_
