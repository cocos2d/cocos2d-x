
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

#include "CCGraphicsOpenGLES2.0.h"
#include "PAL/CCPALMacros.h"
#include "cocos2d.h"

USING_NS_CC;
NS_PRIVATE_BEGIN

GraphicsInterface* GraphicsOpenGLES20::create()
{
    auto obj = new GraphicsOpenGLES20;
    if (obj)
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return nullptr;
}

void GraphicsOpenGLES20::shutdown()
{
    PAL_SAFE_RELEASE_NULL(_view);
}

bool GraphicsOpenGLES20::init()
{
    bool result = true;
    
    // for now, to support easy backwards compatibility we just steal the default GL view.
    _view = Director::getInstance()->getOpenGLView();
    if (_view)
        _view->retain();

    result = _view ? result : false;
    
    return result;
}

bool GraphicsOpenGLES20::supportsGeometryState()
{
    return Configuration::getInstance()->supportsShareableVAO();
}

handle GraphicsOpenGLES20::createGeometryState()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    return (handle)vao;
}

bool GraphicsOpenGLES20::deleteGeometryState(handle object)
{
    auto vao = (GLuint)(intptr_t)object;
    if (!glIsBuffer(vao))
        return false;
    glDeleteVertexArrays(1, (GLuint*)&vao);
    GL::bindVAO(0);
    return true;
}

bool GraphicsOpenGLES20::bindGeometryState(handle object)
{
    auto vao = (GLuint)(intptr_t)object;
    GL::bindVAO(vao);
    CHECK_GL_ERROR_DEBUG();
    return glGetError() ? false : true;
}

NS_PRIVATE_END
