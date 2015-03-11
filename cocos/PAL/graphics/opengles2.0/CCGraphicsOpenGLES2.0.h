
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

#include "base/CCRef.h"
#include "PAL/CCPALMacros.h"
#include "PAL/interfaces/CCGraphicsInterface.h"

NS_CC_BEGIN
class GLView;
NS_CC_END

NS_PRIVATE_BEGIN

class GraphicsGeometryState;

class GraphicsOpenGLES20
    : public GraphicsInterface
{
public:
    
    static GraphicsInterface* create();
    
    // @brief initialize the API
    bool init();

    // @brief shuts down this interface.
    void shutdown();
    
    // @brief returns true or false depending on whether or not geometry state objects are supported.
    bool supportsGeometryState();
    
    // @brief creates a geometry state object
    handle createGeometryState();
    
    // @brief delete a geometry state object.
    bool deleteGeometryState(handle object);
    
    // @brief binds a geometry state object.
    bool bindGeometryState(handle object);
    
protected:
    
    NS_CC::GLView* _view;
};

NS_PRIVATE_END

#endif // _CC_GRAPHICS_OPEN_GL_ES_20_H_
