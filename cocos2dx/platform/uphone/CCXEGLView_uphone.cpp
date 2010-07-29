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

#include "CCXEGLView_uphone.h"

#include "TG3.h"

#include "EGL/egl.h"

#include "Cocos2dDefine.h"
#include "cocoa/NSSet.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

namespace cocos2d {

class CCXEGL
{
public:
    CCXEGL() 
    : m_pDC(NULL)
    , m_eglDisplay(EGL_NO_DISPLAY)
    , m_eglSurface(EGL_NO_SURFACE)
    , m_eglContext(EGL_NO_CONTEXT) {}

    ~CCXEGL() { CCX_SAFE_DELETE(m_pDC); }

    TDC *       m_pDC;
    EGLDisplay  m_eglDisplay;
    EGLSurface  m_eglSurface;
    EGLContext  m_eglContext;
};
CCXEGLView::CCXEGLView(TApplication * pApp)
: TWindow(pApp)
, m_bCaptured(false)
, m_pDelegate(NULL)
, m_pEGL(NULL)
{
    m_pTouch    = new CCTouch;
    m_pSet      = new NSSet;
}

CCXEGLView::~CCXEGLView()
{
    _releaseEGL();
    delete m_pSet;
    delete m_pTouch;
}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_WinInit:
        {
            _initEGL();
            if (! m_pEGL)
            {
                break;
            }
            bHandled = TRUE;
        }
        break;

    case EVENT_WinPaint:
        {
            swapBuffers();
            bHandled = TRUE;
        }
        break;

    case EVENT_PenDown:
        if (m_pDelegate && m_pTouch && m_pSet && SetCaptureEx(-1, TRUE))
        {
            m_bCaptured = true;
//                 SS_printf("Down    %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
            m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
            m_pSet->addObject(m_pTouch);
            m_pDelegate->touchesBegan(m_pSet, NULL);
            bHandled = TRUE;
        }
        break;

    case EVENT_PenMove:
        if (m_pDelegate && m_pTouch && m_pSet && m_bCaptured)
        {
            TRectangle rc;
            GetBounds(&rc);
            if (rc.IsInRect(pEvent->sParam1, pEvent->sParam2))
            {
//                     SS_printf("Move    %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
                m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
                m_pDelegate->touchesMoved(m_pSet, NULL);
                bHandled = TRUE;
            }
        }
        break;

    case EVENT_PenUp:
        if (m_pDelegate && m_pTouch && m_pSet && m_bCaptured)
        {
            ReleaseCapture();
//                 SS_printf("Up      %4d    %4d\n", pEvent->sParam1, pEvent->sParam2);
            m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
            m_pDelegate->touchesEnded(m_pSet, NULL);
            bHandled = TRUE;
        }
        break;

    case EVENT_WinClose:
        {
            // Stop the application since the main form has been closed
            _releaseEGL();
        }
        break;
    }

    if (bHandled)
    {
        return bHandled;
    }
    else
    {
        return TWindow::EventHandler(pApp, pEvent);
    }
}

CGSize CCXEGLView::getSize()
{
    TRectangle rc;
    GetBounds(&rc);
    return CGSize((float)rc.Width(), (float)rc.Height());
}

bool CCXEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCXEGLView::release()
{
    _releaseEGL();
    CloseWindow();
}

void CCXEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCXEGLView::swapBuffers()
{
    // DrawWindow();
    if (m_pEGL)
    {
        eglSwapBuffers(m_pEGL->m_eglDisplay, m_pEGL->m_eglSurface);
    }
}

//////////////////////////////////////////////////////////////////////////
// private member for initialize EGL
//////////////////////////////////////////////////////////////////////////

void CCXEGLView::_initEGL()
{
    TDC * pDC = NULL;
    CCXEGL * pEGL = new CCXEGL;

    do 
    {
        CCX_BREAK_IF(m_pEGL || ! pEGL);

        pDC = new TDC(this);
        CCX_BREAK_IF(! pDC);

        EGLNativeDisplayType displayId = (EGLNativeDisplayType) pDC;
        EGLDisplay eglDisplay;
        CCX_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(displayId)));

        EGLint nMajor, nMinor;
        CCX_BREAK_IF(EGL_FALSE == eglInitialize(eglDisplay, &nMajor, &nMinor) || 1 != nMajor);

        const EGLint aConfigAttribs[] =
        {
            EGL_LEVEL,				0,
            EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
            EGL_NATIVE_RENDERABLE,	EGL_FALSE,
            EGL_DEPTH_SIZE,			EGL_DONT_CARE,
            EGL_NONE,
        };
        EGLint iConfigs;
        EGLConfig eglConfig;
        CCX_BREAK_IF(EGL_FALSE == eglChooseConfig(eglDisplay, aConfigAttribs, &eglConfig, 1, &iConfigs) 
            || (iConfigs != 1));

        EGLSurface eglSurface;
        EGLNativeWindowType eglWnd = (EGLNativeWindowType) this;
        CCX_BREAK_IF(EGL_NO_SURFACE == (eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWnd, NULL)));

        EGLContext eglContext;
        CCX_BREAK_IF(EGL_NO_CONTEXT == (eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL)));

        CCX_BREAK_IF(EGL_FALSE == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext));

        m_pEGL = pEGL;
        pEGL->m_eglDisplay = eglDisplay;
        pEGL->m_eglSurface = eglSurface;
        pEGL->m_eglContext = eglContext;
        pEGL->m_pDC = pDC;
        pDC = NULL;
        pEGL = NULL;
    } while (0);

    CCX_SAFE_DELETE(pDC);
    CCX_SAFE_DELETE(pEGL);
}

void CCXEGLView::_releaseEGL()
{
    if (! m_pEGL)
    {
        return;
    }

    eglMakeCurrent(m_pEGL->m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(m_pEGL->m_eglDisplay);
    CCX_SAFE_DELETE(m_pEGL);
}

}
