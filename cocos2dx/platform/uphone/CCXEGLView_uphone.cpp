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

#include <windows.h>
#include "CCXEGLView_uphone.h"

#include "EGL/egl.h"

#include "Cocos2dDefine.h"
#include "cocoa/NSSet.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

#define WIN_CLASS_NAME      "OpenGL"

static bool  g_keys[256];               // Array Used For The Keyboard Routine
static bool  g_active=TRUE;             // Window Active Flag Set To TRUE By Default

EGLNativeWindowType _CreateWnd(int width, int height);
LRESULT  CALLBACK _WndProc(HWND, UINT, WPARAM, LPARAM);

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
        if (m_eglDC)
        {
            ReleaseDC(m_eglWnd, m_eglDC);
        }
        if (m_eglWnd)
        {
            DestroyWindow(m_eglWnd);
        }
        UnregisterClass(WIN_CLASS_NAME, GetModuleHandle(NULL));
    }

    static CCXEGL * Create(TWindow * pWindow)
    {
        CCXEGL * pEGL = new CCXEGL;
        Boolean bSuccess = FALSE;

        do 
        {
            CCX_BREAK_IF(! pEGL);

            TRectangle rc;
            pWindow->GetClientBounds(&rc);

            CCX_BREAK_IF(! (pEGL->m_eglWnd = _CreateWnd(rc.Width(), rc.Height())));

            pEGL->m_eglDC = GetDC(pEGL->m_eglWnd);
            CCX_BREAK_IF(! pEGL->m_eglDC);

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

            pEGL->m_eglDisplay = eglDisplay;
            pEGL->m_eglSurface = eglSurface;
            pEGL->m_eglContext = eglContext;
            bSuccess = TRUE;
        } while (0);

        if (! bSuccess)
        {
            CCX_SAFE_DELETE(pEGL);   
        }

        return pEGL;
    }

    void SwapBuffers()
    {
        if (EGL_NO_DISPLAY != m_eglDisplay)
        {
            eglSwapBuffers(m_eglDisplay, m_eglSurface);
        }
    }
private:
    CCXEGL() 
        : m_eglWnd(NULL)
        , m_eglDC(NULL)
        , m_eglDisplay(EGL_NO_DISPLAY)
        , m_eglSurface(EGL_NO_SURFACE)
        , m_eglContext(EGL_NO_CONTEXT) {}


    EGLNativeWindowType     m_eglWnd;
    EGLNativeDisplayType    m_eglDC;
    EGLDisplay              m_eglDisplay;
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
    return (m_pEGL = CCXEGL::Create(this)) ? TRUE : FALSE;
}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;

    switch(pEvent->eType)
    {
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
    }

    if (! bHandled)
    {
        return TWindow::EventHandler(pApp, pEvent);
    }
    return bHandled;
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
    CCX_SAFE_DELETE(m_pEGL);
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
        m_pEGL->SwapBuffers();
    }
}

}       // end of namespace cocos2d

//////////////////////////////////////////////////////////////////////////
// static function
//////////////////////////////////////////////////////////////////////////

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
                g_active = TRUE;
            }
            else
            {
                g_active = FALSE;
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
            g_keys[wParam] = TRUE;
            return 0;
        }

    case WM_KEYUP:
        {
            g_keys[wParam] = FALSE;
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
