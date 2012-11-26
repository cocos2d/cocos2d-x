/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "CCEGLView.h"
#include "cocoa/CCSet.h"
#include "CCDirector.h"
#include "ccMacros.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "jni/IMEJni.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "CCGL.h"

#include <stdlib.h>
#include <android/log.h>



#if CC_TEXTURE_ATLAS_USE_VAO

// <EGL/egl.h> exists since android 2.3
#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

#endif

void initExtensions() {
#if CC_TEXTURE_ATLAS_USE_VAO
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
#endif
}

NS_CC_BEGIN

CCEGLView::CCEGLView()
{
    initExtensions();
}

CCEGLView::~CCEGLView()
{

}

bool CCEGLView::isOpenGLReady()
{
    return (m_obScreenSize.width != 0 && m_obScreenSize.height != 0);
}

void CCEGLView::end()
{
    terminateProcessJNI();
}

void CCEGLView::swapBuffers()
{
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView instance;
    return &instance;
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    setKeyboardStateJNI((int)bOpen);
}

NS_CC_END

