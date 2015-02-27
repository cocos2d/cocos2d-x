
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

#include "renderer/abstraction/opengles2.0/CCGraphicsOpenGLES2.0.h"
#include "cocos2d.h"

NS_CC_BEGIN

GraphicsInterface* GraphicsOpenGLES20::create(const char* name)
{
    auto obj = new GraphicsOpenGLES20;
    if (obj && obj->init(name))
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}

void GraphicsOpenGLES20::shutdown()
{
    CC_SAFE_RELEASE_NULL(_view);
}

// @brief create a uninitialized view.
ViewInterface* GraphicsOpenGLES20::getView() const
{
    return nullptr;//_view;
}

//
// Protected Methods
//

bool GraphicsOpenGLES20::init(const char* name)
{
    bool result = true;
    
    // for now, to support easy backwards compatibility we just steal the default GL view.
    _view = Director::getInstance()->getOpenGLView();
    if (_view)
        _view->retain();

    result = _view ? result : false;
    
    return result;
}

NS_CC_END
