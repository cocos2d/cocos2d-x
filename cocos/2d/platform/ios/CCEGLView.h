/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CC_EGLVIEW_IPHONE_H__
#define __CC_EGLVIEW_IPHONE_H__

#include "platform/CCCommon.h"
#include "platform/CCEGLViewProtocol.h"

NS_CC_BEGIN



class CC_DLL EGLView : public EGLViewProtocol
{
public:
    /**
     * @js NA
     * @lua NA
     */
    EGLView();
    /**
     * @js NA
     * @lua NA
     */
   ~EGLView();
    /**
     * @js NA
     * @lua NA
     */
    virtual bool    isOpenGLReady();
    /**
     * @js NA
     * @lua NA
     */
    virtual bool    setContentScaleFactor(float contentScaleFactor);
    
    // keep compatible
    /**
     * @js NA
     * @lua NA
     */
    virtual void    end();
    /**
     * @js NA
     * @lua NA
     */
    virtual void    swapBuffers();
    /**
     * @js NA
     * @lua NA
     */
    virtual void setIMEKeyboardState(bool bOpen);

    /** returns the singleton
     * @js NA
     */
    static EGLView* getInstance();

    /** @deprecated Use getInstance() instead 
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static EGLView* sharedOpenGLView();

};

NS_CC_END

#endif    // end of __CC_EGLVIEW_IPHONE_H__
