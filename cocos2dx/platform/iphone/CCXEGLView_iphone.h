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

#ifndef __CCX_EGLVIEW_IPHONE_H__
#define __CCX_EGLVIEW_IPHONE_H__

//#include "CGGeometry.h"
#include "ccxCommon_iphone.h"

namespace   cocos2d {
class NSSet;
class CCTouch;
class EGLTouchDelegate;
class CGSize;

class CCX_DLL CCXEGLView
{
public:
    CCXEGLView();
   ~CCXEGLView();

    CGSize  getSize();
    bool    isOpenGLReady();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor);
    
    // keep compatible
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    
    void touchesBegan(NSSet *set);
    void touchesMoved(NSSet *set);
    void touchesEnded(NSSet *set);
    void touchesCancelled(NSSet *set);
    
private:
    EGLTouchDelegate *m_pDelegate;
};

}   // end of namespace   cocos2d

#endif	// end of __CCX_EGLVIEW_IPHONE_H__
