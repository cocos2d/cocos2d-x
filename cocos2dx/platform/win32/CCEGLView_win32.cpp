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
#include "CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCIMEDispatcher.h"
#include "CCKeypadDispatcher.h"
#include "CCApplication.h"

#include "EGL/egl.h"

NS_CC_BEGIN

//////////////////////////////////////////////////////////////////////////
// impliment CCEGL
//////////////////////////////////////////////////////////////////////////

class CCEGL
{
public:
    ~CCEGL() 
    {
        if (EGL_NO_SURFACE != m_eglSurface)
        {
            eglDestroySurface(m_eglDisplay, m_eglSurface);
        }
        if (EGL_NO_CONTEXT != m_eglContext)
        {
            eglDestroyContext(m_eglDisplay, m_eglContext);
        }
        eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglTerminate(m_eglDisplay);
        if (m_eglNativeDisplay)
        {
            ReleaseDC(m_eglNativeWindow, m_eglNativeDisplay);
        }
    }

    static CCEGL * create(CCEGLView * pWindow)
    {
        CCEGL * pEGL = new CCEGL;
        BOOL bSuccess = FALSE;
        do 
        {
            CC_BREAK_IF(! pEGL);

            pEGL->m_eglNativeWindow = pWindow->getHWnd();

            pEGL->m_eglNativeDisplay = GetDC(pEGL->m_eglNativeWindow);

            EGLDisplay eglDisplay;
            CC_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglNativeDisplay)));

            EGLint nMajor, nMinor;
            CC_BREAK_IF(EGL_FALSE == eglInitialize(eglDisplay, &nMajor, &nMinor) || 1 != nMajor);

            const EGLint aConfigAttribs[] =
            {
                EGL_LEVEL,                0,
                EGL_SURFACE_TYPE,        EGL_WINDOW_BIT,
                EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
                EGL_NATIVE_RENDERABLE,    EGL_FALSE,
                EGL_DEPTH_SIZE,            16,
                EGL_NONE,
            };
            EGLint iConfigs;
            EGLConfig eglConfig;
            CC_BREAK_IF(EGL_FALSE == eglChooseConfig(eglDisplay, aConfigAttribs, &eglConfig, 1, &iConfigs) 
                || (iConfigs != 1));

            EGLContext eglContext;
            eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL);
            CC_BREAK_IF(EGL_NO_CONTEXT == eglContext);

            EGLSurface eglSurface;
            eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, pEGL->m_eglNativeWindow, NULL);
            CC_BREAK_IF(EGL_NO_SURFACE == eglSurface);

            CC_BREAK_IF(EGL_FALSE == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext));

            pEGL->m_eglDisplay = eglDisplay;
            pEGL->m_eglConfig  = eglConfig;
            pEGL->m_eglContext = eglContext;
            pEGL->m_eglSurface = eglSurface;
            bSuccess = TRUE;
        } while (0);

        if (! bSuccess)
        {
            CC_SAFE_DELETE(pEGL);  
        }

        return pEGL;
    }

    void resizeSurface()
    {
//          if (! m_eglNativeWindow || EGL_NO_DISPLAY == m_eglDisplay)
//          {
//              return;
//          }
//  
//          // release old surface
//          if (EGL_NO_SURFACE != m_eglSurface)
//          {
//              eglDestroySurface(m_eglDisplay, m_eglSurface);
//              m_eglSurface = EGL_NO_SURFACE;
//          }
//  
//          // create new surface and make current
//          m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_eglNativeWindow, NULL);
//          eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
    }

    void swapBuffers()
    {
        if (EGL_NO_DISPLAY != m_eglDisplay)
        {
            eglSwapBuffers(m_eglDisplay, m_eglSurface);
        }
    }
private:
    CCEGL() 
        : m_eglNativeWindow(NULL)
        , m_eglNativeDisplay(EGL_DEFAULT_DISPLAY)
        , m_eglDisplay(EGL_NO_DISPLAY)
        , m_eglConfig(0)
        , m_eglSurface(EGL_NO_SURFACE)
        , m_eglContext(EGL_NO_CONTEXT)
    {}

    EGLNativeWindowType     m_eglNativeWindow;
    EGLNativeDisplayType    m_eglNativeDisplay;
    EGLDisplay              m_eglDisplay;
    EGLConfig               m_eglConfig;
    EGLSurface              m_eglSurface;
    EGLContext              m_eglContext;
};

//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////
static CCEGLView * s_pMainWindow;
static const WCHAR * kWindowClassName = L"Cocos2dxWin32";

static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (s_pMainWindow && s_pMainWindow->getHWnd() == hWnd)
    {
        return s_pMainWindow->WindowProc(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

CCEGLView::CCEGLView()
: m_bCaptured(false)
, m_pEGL(NULL)
, m_hWnd(NULL)
, m_lpfnAccelerometerKeyHook(NULL)
{
    
}

CCEGLView::~CCEGLView()
{
}

bool CCEGLView::Create(LPCTSTR pTitle, int w, int h)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(m_hWnd);

        HINSTANCE hInstance = GetModuleHandle( NULL );
        WNDCLASS  wc;        // Windows Class Structure

        // Redraw On Size, And Own DC For Window.
        wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  
        wc.lpfnWndProc    = _WindowProc;                    // WndProc Handles Messages
        wc.cbClsExtra     = 0;                              // No Extra Window Data
        wc.cbWndExtra     = 0;                                // No Extra Window Data
        wc.hInstance      = hInstance;                        // Set The Instance
        wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );    // Load The Default Icon
        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
        wc.hbrBackground  = NULL;                           // No Background Required For GL
        wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
        wc.lpszClassName  = kWindowClassName;               // Set The Class Name

        CC_BREAK_IF(! RegisterClass(&wc) && 1410 != GetLastError());        

        // center window position
        RECT rcDesktop;
        GetWindowRect(GetDesktopWindow(), &rcDesktop);

        // create window
        m_hWnd = CreateWindowEx(
            WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,    // Extended Style For The Window
            kWindowClassName,                                    // Class Name
            pTitle,                                                // Window Title
            WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX,        // Defined Window Style
            0, 0,                                                // Window Position
            0,                                                  // Window Width
            0,                                                  // Window Height
            NULL,                                                // No Parent Window
            NULL,                                                // No Menu
            hInstance,                                            // Instance
            NULL );

        CC_BREAK_IF(! m_hWnd);

        m_sSizeInPoint.width = (float)w;
        m_sSizeInPoint.height = (float)h;

        resize(w, h);

        // init egl
        m_pEGL = CCEGL::create(this);

        if (! m_pEGL)
        {
            DestroyWindow(m_hWnd);
            m_hWnd = NULL;
            break;
        }

        s_pMainWindow = this;
        bRet = true;
    } while (0);

    return bRet;
}

LRESULT CCEGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (m_pDelegate && MK_LBUTTON == wParam)
        {
            CCPoint pt((float)LOWORD(lParam), (float)HIWORD(lParam));
            if (CCRect::CCRectContainsPoint(m_rcViewPort, pt))
            {
                m_bCaptured = true;
                SetCapture(m_hWnd);
                int id = 0;
                handleTouchesBegin(1, &id, &pt.x, &pt.y);
            }
        }
        break;

    case WM_MOUSEMOVE:
        if (MK_LBUTTON == wParam && m_bCaptured)
        {
            CCPoint pt((float)LOWORD(lParam), (float)HIWORD(lParam));
            int id = 0;
            handleTouchesMove(1, &id, &pt.x, &pt.y);
        }
        break;

    case WM_LBUTTONUP:
        if (m_bCaptured)
        {
            CCPoint pt((float)LOWORD(lParam), (float)HIWORD(lParam));
            int id = 0;
            handleTouchesEnd(1, &id, &pt.x, &pt.y);

            ReleaseCapture();
            m_bCaptured = false;
        }
        break;
    case WM_SIZE:
        switch (wParam)
        {
        case SIZE_RESTORED:
            CCApplication::sharedApplication().applicationWillEnterForeground();
            break;
        case SIZE_MINIMIZED:
            CCApplication::sharedApplication().applicationDidEnterBackground();
            break;
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_F1 || wParam == VK_F2)
        {
            CCDirector* pDirector = CCDirector::sharedDirector();
            if (GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
                pDirector->getKeypadDispatcher()->dispatchKeypadMSG(wParam == VK_F1 ? kTypeBackClicked : kTypeMenuClicked);
        }
        if ( m_lpfnAccelerometerKeyHook!=NULL )
        {
            (*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
        }
        break;
    case WM_KEYUP:
        if ( m_lpfnAccelerometerKeyHook!=NULL )
        {
            (*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
        }
        break;
    case WM_CHAR:
        {
            if (wParam < 0x20)
            {
                if (VK_BACK == wParam)
                {
                    CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
                }
                else if (VK_RETURN == wParam)
                {
                    CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
                }
                else if (VK_TAB == wParam)
                {
                    // tab input
                }
                else if (VK_ESCAPE == wParam)
                {
                    // ESC input
                    CCDirector::sharedDirector()->end();
                }
            }
            else if (wParam < 128)
            {
                // ascii char
                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&wParam, 1);
            }
            else
            {
                char szUtf8[8] = {0};
                int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&wParam, 1, szUtf8, sizeof(szUtf8), NULL, NULL);

                CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
            }
            if ( m_lpfnAccelerometerKeyHook!=NULL )
            {
                (*m_lpfnAccelerometerKeyHook)( message,wParam,lParam );
            }
        }
        break;

    case WM_PAINT:
        BeginPaint(m_hWnd, &ps);
        EndPaint(m_hWnd, &ps);
        break;

    case WM_CLOSE:
        CCDirector::sharedDirector()->end();
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(m_hWnd, message, wParam, lParam);
    }
    return 0;
}

void CCEGLView::setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook )
{
    m_lpfnAccelerometerKeyHook=lpfnAccelerometerKeyHook;
}


bool CCEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCEGLView::end()
{
    if (m_hWnd)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = NULL;
    }
    s_pMainWindow = NULL;
    UnregisterClass(kWindowClassName, GetModuleHandle(NULL));

    delete this;
}

void CCEGLView::swapBuffers()
{
    if (m_pEGL)
    {
        m_pEGL->swapBuffers();
    }
}


void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

HWND CCEGLView::getHWnd()
{
    return m_hWnd;
}

void CCEGLView::resize(int width, int height)
{
    if (! m_hWnd)
    {
        return;
    }

    RECT rcClient;
    GetClientRect(m_hWnd, &rcClient);
    if (rcClient.right - rcClient.left == width &&
        rcClient.bottom - rcClient.top == height)
    {
        return;
    }
    // calculate new window width and height
    rcClient.right = rcClient.left + width;
    rcClient.bottom = rcClient.top + height;
    AdjustWindowRectEx(&rcClient, GetWindowLong(m_hWnd, GWL_STYLE), false, GetWindowLong(m_hWnd, GWL_EXSTYLE));

    // change width and height
    SetWindowPos(m_hWnd, 0, 0, 0, rcClient.right - rcClient.left, 
        rcClient.bottom - rcClient.top, SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

    if (m_pEGL)
    {
        m_pEGL->resizeSurface();
    }

    // calculate view port in pixels
    float viewPortW = m_sSizeInPoint.width * m_fScreenScaleFactor;
    float viewPortH = m_sSizeInPoint.height * m_fScreenScaleFactor;

    GetClientRect(m_hWnd, &rcClient);

    // calculate client new width and height
    float newW = rcClient.right - rcClient.left;
    float newH = rcClient.bottom - rcClient.top;

    // calculate new view port
    m_rcViewPort.origin.x   = rcClient.left + (newW - viewPortW) / 2;
    m_rcViewPort.origin.y    = rcClient.top + (newH - viewPortH) / 2;
    m_rcViewPort.size.width  = viewPortW;
    m_rcViewPort.size.height = viewPortH;
}

void CCEGLView::centerWindow()
{
    if (! m_hWnd)
    {
        return;
    }

    RECT rcDesktop, rcWindow;
    GetWindowRect(GetDesktopWindow(), &rcDesktop);

    // substract the task bar
    HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), NULL);
    if (hTaskBar != NULL)
    {
        APPBARDATA abd;

        abd.cbSize = sizeof(APPBARDATA);
        abd.hWnd = hTaskBar;

        SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
        SubtractRect(&rcDesktop, &rcDesktop, &abd.rc);
    }
    GetWindowRect(m_hWnd, &rcWindow);

    int offsetX = (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
    offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
    int offsetY = (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
    offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;

    SetWindowPos(m_hWnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

bool CCEGLView::canSetContentScaleFactor()
{
    return true;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    CCEGLViewProtocol::setContentScaleFactor(contentScaleFactor);

    resize((int)(m_sSizeInPoint.width * contentScaleFactor), (int)(m_sSizeInPoint.height * contentScaleFactor));
    centerWindow();
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    CC_ASSERT(s_pMainWindow);
    return *s_pMainWindow;
}

NS_CC_END
