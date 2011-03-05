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

#ifndef __CCX_EGLVIEW_WOPHONE_H__
#define __CCX_EGLVIEW_WOPHONE_H__

#include "GuiBase.h"
#include "TWindow.h"

#include "CGGeometry.h"

class TApplication;

namespace   cocos2d {
class NSSet;
class CCTouch;
class EGLTouchDelegate;

class CCXEGL;

class CCX_DLL CCXEGLView : public TWindow
{
public:

    CCXEGLView(TApplication * pApp);
    virtual ~CCXEGLView();

    virtual Boolean AfterCreate(void);
    virtual Boolean EventHandler(TApplication * pApp, EventType * pEvent);

	CGRect  getFrame();
    CGSize  getSize();
    bool    isOpenGLReady();
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
	bool    canSetContentScaleFactor();
	void    setContentScaleFactor(float contentScaleFactor);
	void    setAnimationInterval(double interval) {};

protected:
    Boolean OnPenDown(EventType* pEvent, Int32 nIndex);
    Boolean OnPenUp(EventType* pEvent, Int32 nIndex);
    Boolean OnPenMove(EventType* pEvent);

private:

    MESSAGE_t m_tMsg;
    CCXEGL *            m_pEGL;
    EGLTouchDelegate *  m_pDelegate;
};

}   // end of namespace   cocos2d

#endif	// end of __CCX_EGLVIEW_WOPHONE_H__
