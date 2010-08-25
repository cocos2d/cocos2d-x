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

// #define USE_EGL_UMU

#ifndef USE_EGL_UMU
// #define _EGL_SHOW_
#include <windows.h>
#endif
#include "CCXEGLView_uphone.h"

#include "TDC.h"
#undef GetNextWindow        // this micro defined in winuser.h
#include "TApplication.h"

#include "EGL/egl.h"
#include "gles/gl.h"

#include "Cocos2dDefine.h"
#include "NSSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

#ifndef USE_EGL_UMU
#define WIN_CLASS_NAME      "OpenGL"

static bool  s_keys[256];               // Array Used For The Keyboard Routine
static bool  s_active=TRUE;             // Window Active Flag Set To TRUE By Default

EGLNativeWindowType _CreateWnd(int width, int height);
LRESULT  CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);
#endif


namespace cocos2d {

class CCXEGL
{
public:
    ~CCXEGL() 
    {
        if (EGL_NO_DISPLAY != m_eglDisplay)
        {
            eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            eglTerminate(m_eglDisplay);
        }
#ifndef USE_EGL_UMU
        if (m_eglDC)
        {
            ReleaseDC(m_eglWnd, m_eglDC);
        }
        if (m_eglWnd)
        {
            DestroyWindow(m_eglWnd);
        }
        UnregisterClass(WIN_CLASS_NAME, GetModuleHandle(NULL));
#endif
        if (m_pBmp)
        {
            m_pBmp->Destroy();
        }
    }

    static CCXEGL * create(TWindow * pWindow)
    {
        CCXEGL * pEGL = new CCXEGL;
        Boolean bSuccess = FALSE;
        do 
        {
            CCX_BREAK_IF(! pEGL);

            TRectangle rc;
            pWindow->GetClientBounds(&rc);
            CCX_BREAK_IF(! (pEGL->m_pBmp = TBitmap::Create(rc.Width(), rc.Height(), 32)));
#ifdef USE_EGL_UMU
            pEGL->m_eglWnd = pWindow;
            TDC dc(pWindow);
            pEGL->m_eglDC = &dc;
#else
            CCX_BREAK_IF(! (pEGL->m_eglWnd = _CreateWnd(rc.Width(), rc.Height())));

            pEGL->m_eglDC = GetDC(pEGL->m_eglWnd);
            CCX_BREAK_IF(! pEGL->m_eglDC);
#endif
            EGLDisplay eglDisplay;
            CCX_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglDC)));

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
            eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, pEGL->m_eglWnd, NULL);
            CCX_BREAK_IF(EGL_NO_SURFACE == eglSurface);

            EGLContext eglContext;
            eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL);
            CCX_BREAK_IF(EGL_NO_CONTEXT == eglContext);

            CCX_BREAK_IF(EGL_FALSE == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext));

            pEGL->m_pWnd       = pWindow;
            pEGL->m_eglDisplay = eglDisplay;
            pEGL->m_eglSurface = eglSurface;
            pEGL->m_eglConfig  = eglConfig;
            pEGL->m_eglContext = eglContext;
            bSuccess = TRUE;
        } while (0);

        if (! bSuccess)
        {
            CCX_SAFE_DELETE(pEGL);   
        }

        return pEGL;
    }

    void resizeSurface()
    {
        if (! m_pWnd || EGL_NO_DISPLAY == m_eglDisplay)
        {
            return;
        }

        // release old surface
        if (EGL_NO_SURFACE != m_eglSurface)
        {
            eglDestroySurface(m_eglDisplay, m_eglSurface);
            m_eglSurface = EGL_NO_SURFACE;
        }

        // resize eglWnd;
        TRectangle rc;
        m_pWnd->GetClientBounds(&rc);
        RECT rcNew = {0, 0, rc.Width(), rc.Height(),};
        AdjustWindowRectEx(&rcNew, WS_POPUPWINDOW, false, WS_EX_TOPMOST | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
        MoveWindow(m_eglWnd, rcNew.left, rcNew.top, rcNew.right - rcNew.left, rcNew.bottom - rcNew.top, FALSE);

        // create new surface and make current
        m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_eglWnd, NULL);
        eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
    }

    void swapBuffers()
    {
        if (EGL_NO_DISPLAY != m_eglDisplay)
        {
            TRectangle rc;
            m_pWnd->GetClientBounds(&rc);

            int nWidth = rc.Width();
            int nHeight = rc.Height();

            char *pData = new char[4 * nWidth * nHeight];
            if (pData == NULL)
            {
                return;
            }
            glReadPixels(0, 0, nWidth, nHeight, GL_RGBA, GL_UNSIGNED_BYTE, pData);

            char * pDst     = (char *)m_pBmp->GetDataPtr();
            int    nPitch   = m_pBmp->GetRowBytes();
            char * pDstRow  = NULL;
            char * pSrc     = pData;

            for (int i = 0; i < nHeight; i++)
            {
                pDstRow = pDst + (nHeight - i - 1) * nPitch;
                for (int j = 0; j < nWidth; j++)
                {
                    *(int *)pDstRow = RGBA(pSrc[0], pSrc[1], pSrc[2], pSrc[3]);
                    pSrc += 4;
                    pDstRow += 4;
                }
            }
            TDC dc(m_pWnd);
            dc.DrawBitmap(m_pBmp, 0, 0);
#ifdef _EGL_SHOW_
            eglSwapBuffers(m_eglDisplay, m_eglSurface);
#endif
            delete pData;
        }
    }
private:
    CCXEGL() 
        : m_pWnd(NULL)
        , m_pBmp(NULL)
        , m_eglWnd(NULL)
#ifndef USE_EGL_EMU
        , m_eglDC(NULL)
#endif
        , m_eglDisplay(EGL_NO_DISPLAY)
        , m_eglConfig(0)
        , m_eglSurface(EGL_NO_SURFACE)
        , m_eglContext(EGL_NO_CONTEXT)
    {}

    TWindow *               m_pWnd;
    TBitmap *               m_pBmp;
    EGLNativeWindowType     m_eglWnd;
    EGLNativeDisplayType    m_eglDC;
    EGLDisplay              m_eglDisplay;
    EGLConfig               m_eglConfig;
    EGLSurface              m_eglSurface;
    EGLContext              m_eglContext;
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
    delete m_pEGL;
    delete m_pSet;
    delete m_pTouch;
}

Boolean CCXEGLView::AfterCreate(void)
{
    return (m_pEGL = CCXEGL::create(this)) ? TRUE : FALSE;
}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_WinInit:
        bHandled = TRUE;
        break;

    case EVENT_WinRotationChanged:
        {
            if (m_pEGL)
            {
                m_pEGL->resizeSurface();
                UpdateWindow(0);
            }
        }
//         CCX_SAFE_DELETE(m_pEGL);
//         m_pEGL = CCXEGL::create(this);
        bHandled = TRUE;
        break;

    case EVENT_WinPaint:
        CCDirector::getSharedDirector()->preMainLoop();
        bHandled = TRUE;
        break;

    case EVENT_PenDown:
        if (m_bCaptured)
        {
            bHandled = TRUE;
        }
        else if (m_pDelegate && m_pTouch && m_pSet 
            && ! PointInControl(pEvent->sParam1, pEvent->sParam2, NULL) 
            && SetCaptureEx(-1, TRUE))
        {
            m_bCaptured = true;
            m_nPenEventNum = pEvent->lParam5;
//            SS_printf("PenDown: %4d,    %4d\n", pEvent->sParam1, pEvent->sParam2);
            m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
            m_pSet->addObject(m_pTouch);
            m_pDelegate->touchesBegan(m_pSet, NULL);
        }
        break;

    case EVENT_PenMove:
        if (m_pDelegate && m_pTouch && m_pSet && m_bCaptured && pEvent->lParam5 == m_nPenEventNum)
        {
//                SS_printf("PenMove: %4d,    %4d\n", pEvent->sParam1, pEvent->sParam2);
            m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
            m_pDelegate->touchesMoved(m_pSet, NULL);
        }
        break;

    case EVENT_PenUp:
        if (m_pDelegate && m_pTouch && m_pSet && m_bCaptured && pEvent->lParam5 == m_nPenEventNum)
        {
            ReleaseCapture();
//            SS_printf("PenUp:   %4d,    %4d\n", pEvent->sParam1, pEvent->sParam2);
            m_pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
            m_pDelegate->touchesEnded(m_pSet, NULL);
			 m_pSet->removeObject(m_pTouch);
            m_bCaptured = false;
        }
        break;

    case EVENT_WinClose:
        // Stop the application since the main form has been closed
        pApp->SendStopEvent();
        break;

    }

    if (! bHandled)
    {
        return TWindow::EventHandler(pApp, pEvent);
    }
    return bHandled;
}

CGSize CCXEGLView::getSize()
{
	Coord w, h;
	TWindow::GetWindowExtent(&w, &h);
    return CGSize((float)w, (float)h);
}

CGRect CCXEGLView::getFrame()
{
	TRectangle rc;
	GetClientBounds(&rc);
	return (CGRect((float)rc.X(), (float)rc.Y(), (float)rc.Width(), (float)rc.Height()));
}

bool CCXEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCXEGLView::release()
{
    CCX_SAFE_DELETE(m_pEGL);
    CloseWindow();
}

void CCXEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCXEGLView::swapBuffers()
{
    if (m_pEGL)
    {
        m_pEGL->swapBuffers();
    }
}

}       // end of namespace cocos2d

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////
#ifndef USE_EGL_UMU
static EGLNativeWindowType _CreateWnd(int width, int height)
{
    WNDCLASS  wc;                  // Windows Class Structure
    HINSTANCE hInstance;
    EGLNativeWindowType hWnd = NULL;

    hInstance         = GetModuleHandle( NULL );             // Grab An Instance For Our Window
    wc.style          = CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Size, And Own DC For Window.
    wc.lpfnWndProc    = WNDPROC( _WndProc );                  // WndProc Handles Messages
    wc.cbClsExtra     = 0;                                   // No Extra Window Data
    wc.cbWndExtra     = 0;                                   // No Extra Window Data
    wc.hInstance      = hInstance;                           // Set The Instance
    wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );       // Load The Default Icon
    wc.hCursor        = LoadCursor( NULL, IDC_ARROW );       // Load The Arrow Pointer
    wc.hbrBackground  = NULL;                                // No Background Required For GL
    wc.lpszMenuName   = NULL;                                // We Don't Want A Menu
    wc.lpszClassName  = WIN_CLASS_NAME;                            // Set The Class Name

    RegisterClass(&wc);                            // Attempt To Register The Window Class

    RECT rect = {0, 0, width, height};
    AdjustWindowRectEx(&rect, WS_POPUPWINDOW, false, WS_EX_TOPMOST | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
    hWnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,       // Extended Style For The Window
        "OpenGL",                             // Class Name
        "Effect Test App",                    // Window Title
        WS_POPUPWINDOW/*WS_OVERLAPPEDWINDOW*/ |                     // Defined Window Style
        WS_CLIPSIBLINGS |                         // Required Window Style
        WS_CLIPCHILDREN,                          // Required Window Style
        0, 0,                                     // Window Position
        rect.right - rect.left,                                    // Window Width
        rect.bottom - rect.top,                                   // Window Height
        NULL,                                     // No Parent Window
        NULL,                                     // No Menu
        hInstance,                                // Instance
        NULL );

#ifdef _EGL_SHOW_
    if (hWnd)
    {
        ShowWindow(hWnd, SW_SHOW);
    }
#endif
    return hWnd;
}

static LRESULT CALLBACK _WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )      // Check For Windows Messages
    {
    case WM_ACTIVATE:
        {
            if ( ! HIWORD( wParam ) )     // Check Minimization State
            {
                s_active = TRUE;
            }
            else
            {
                s_active = FALSE;
            }
            return 0;
        }

    case WM_SYSCOMMAND:
        {
            if ( ( wParam == SC_SCREENSAVE ) ||
                ( wParam == SC_MONITORPOWER ) )
            {
                return 0;
            }
            break;
        }

    case WM_CLOSE:
        {
            PostQuitMessage( 0 );
            return 0;
        }

    case WM_KEYDOWN:
        {
            s_keys[wParam] = TRUE;
            return 0;
        }

    case WM_KEYUP:
        {
            s_keys[wParam] = FALSE;
            return 0;
        }

    case WM_SIZE:
        {
            //ResizeScene( LOWORD( lParam ), HIWORD( lParam ) );  // LoWord=Width, HiWord=Height
            return 0;
        }
    }

    // Pass All Unhandled Messages To DefWindowProc
    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
#endif
