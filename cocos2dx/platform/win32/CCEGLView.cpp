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
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "support/CCPointExtension.h"
#include "CCApplication.h"

NS_CC_BEGIN

static void SetupPixelFormat(HDC hDC)
{
    int pixelFormat;

    PIXELFORMATDESCRIPTOR pfd =
    {   
        sizeof(PIXELFORMATDESCRIPTOR),  // size
        1,                          // version
        PFD_SUPPORT_OPENGL |        // OpenGL window
        PFD_DRAW_TO_WINDOW |        // render to window
        PFD_DOUBLEBUFFER,           // support double-buffering
        PFD_TYPE_RGBA,              // color type
        32,                         // prefered color depth
        0, 0, 0, 0, 0, 0,           // color bits (ignored)
        0,                          // no alpha buffer
        0,                          // alpha bits (ignored)
        0,                          // no accumulation buffer
        0, 0, 0, 0,                 // accum bits (ignored)
        16,                         // depth buffer
        0,                          // no stencil buffer
        0,                          // no auxiliary buffers
        PFD_MAIN_PLANE,             // main layer
        0,                          // reserved
        0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////
static CCEGLView* s_pMainWindow = NULL;
static const WCHAR* kWindowClassName = L"Cocos2dxWin32";

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
, m_hWnd(NULL)
, m_hDC(NULL)
, m_hRC(NULL)
, m_lpfnAccelerometerKeyHook(NULL)
, m_menu(NULL)
, m_wndproc(NULL)
, m_windowWidth(0)
, m_windowHeight(0)
, m_windowTouchScaleX(1.0f)
, m_windowTouchScaleY(1.0f)
{
    strcpy(m_szViewName, "Cocos2dxWin32");
}

CCEGLView::~CCEGLView()
{

}

bool CCEGLView::initGL()
{
    m_hDC = GetDC(m_hWnd);
    SetupPixelFormat(m_hDC);
    //SetupPalette();
    m_hRC = wglCreateContext(m_hDC);
    wglMakeCurrent(m_hDC, m_hRC);

    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    CCLOG("OpenGL version = %s", glVersion);

    if ( atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain, 
		"Your OpenGL version is %s, but Cocos2d-x requires OpenGL 1.5 or higher on Windows. Please upgrade the driver of your video card", 
		glVersion);
	CCMessageBox(strComplain, "OpenGL version tooooooooooold");
    }

    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult) 
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(GlewInitResult));
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        CCLog("Ready for GLSL");
    }
    else 
    {
        CCLog("Not totally ready :(");
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        CCLog("Ready for OpenGL 2.0");
    }
    else
    {
        CCLog("OpenGL 2.0 not supported");
    }
    return true;
}

void CCEGLView::destroyGL()
{
    if (m_hDC != NULL && m_hRC != NULL)
    {
        // deselect rendering context and delete it
        wglMakeCurrent(m_hDC, NULL);
        wglDeleteContext(m_hRC);
    }
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
        wc.lpszMenuName   = m_menu;                         // 
        wc.lpszClassName  = kWindowClassName;               // Set The Class Name

        CC_BREAK_IF(! RegisterClass(&wc) && 1410 != GetLastError());        

        // center window position
        RECT rcDesktop;
        GetWindowRect(GetDesktopWindow(), &rcDesktop);

        WCHAR wszBuf[50] = {0};
        MultiByteToWideChar(CP_UTF8, 0, m_szViewName, -1, wszBuf, sizeof(wszBuf));

        // create window
        m_hWnd = CreateWindowEx(
            WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,    // Extended Style For The Window
            kWindowClassName,                                    // Class Name
            wszBuf,                                                // Window Title
            WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX,        // Defined Window Style
            0, 0,                                                // Window Position
            0,                                                  // Window Width
            0,                                                  // Window Height
            NULL,                                                // No Parent Window
            NULL,                                                // No Menu
            hInstance,                                            // Instance
            NULL );

        CC_BREAK_IF(! m_hWnd);

        resize(w, h);

        bRet = initGL();
        CC_BREAK_IF(!bRet);
        
        s_pMainWindow = this;
        bRet = true;
    } while (0);

    return bRet;
}

LRESULT CCEGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL bProcessed = FALSE;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        if (m_pDelegate && MK_LBUTTON == wParam)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x/CC_CONTENT_SCALE_FACTOR(), point.y/CC_CONTENT_SCALE_FACTOR());
            CCPoint tmp = ccp(pt.x, m_obScreenSize.height - pt.y);
            if (m_obViewPortRect.equals(CCRectZero) || m_obViewPortRect.containsPoint(tmp))
            {
                m_bCaptured = true;
                SetCapture(m_hWnd);
                int id = 0;
                pt.x *= m_windowTouchScaleX;
                pt.y *= m_windowTouchScaleY;
                handleTouchesBegin(1, &id, &pt.x, &pt.y);
            }
        }
        break;

    case WM_MOUSEMOVE:
        if (MK_LBUTTON == wParam && m_bCaptured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x/CC_CONTENT_SCALE_FACTOR(), point.y/CC_CONTENT_SCALE_FACTOR());
            int id = 0;
            pt.x *= m_windowTouchScaleX;
            pt.y *= m_windowTouchScaleY;
            handleTouchesMove(1, &id, &pt.x, &pt.y);
        }
        break;

    case WM_LBUTTONUP:
        if (m_bCaptured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x/CC_CONTENT_SCALE_FACTOR(), point.y/CC_CONTENT_SCALE_FACTOR());
            int id = 0;
            pt.x *= m_windowTouchScaleX;
            pt.y *= m_windowTouchScaleY;
            handleTouchesEnd(1, &id, &pt.x, &pt.y);

            ReleaseCapture();
            m_bCaptured = false;
        }
        break;
    case WM_SIZE:
        switch (wParam)
        {
        case SIZE_RESTORED:
            CCApplication::sharedApplication()->applicationWillEnterForeground();
            break;
        case SIZE_MINIMIZED:
            CCApplication::sharedApplication()->applicationDidEnterBackground();
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
                    //CCDirector::sharedDirector()->end();
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
        PAINTSTRUCT ps;
        BeginPaint(m_hWnd, &ps);
        EndPaint(m_hWnd, &ps);
        break;

    case WM_CLOSE:
        CCDirector::sharedDirector()->end();
        break;

    case WM_DESTROY:
        destroyGL();
        PostQuitMessage(0);
        break;

    default:
        if (m_wndproc)
        {
            
            m_wndproc(message, wParam, lParam, &bProcessed);
            if (bProcessed) break;
        }
        return DefWindowProc(m_hWnd, message, wParam, lParam);
    }

    if (m_wndproc && !bProcessed)
    {
        m_wndproc(message, wParam, lParam, &bProcessed);
    }
    return 0;
}

void CCEGLView::setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook )
{
    m_lpfnAccelerometerKeyHook=lpfnAccelerometerKeyHook;
}


bool CCEGLView::isOpenGLReady()
{
    return (m_hDC != NULL && m_hRC != NULL);
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
    if (m_hDC != NULL)
    {
        ::SwapBuffers(m_hDC);
    }
}


void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

bool CCEGLView::enableRetina()
{
    m_bIsRetinaEnabled = true;
    return true;
}

void CCEGLView::setMenuResource(LPCWSTR menu)
{
    m_menu = menu;
}

void CCEGLView::setWndProc(CUSTOM_WND_PROC proc)
{
    m_wndproc = proc;
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

    RECT rcWindow;
    GetWindowRect(m_hWnd, &rcWindow);

    RECT rcClient;
    GetClientRect(m_hWnd, &rcClient);

    // calculate new window width and height
    POINT ptDiff;
    ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
    ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
    rcClient.right = rcClient.left + width;
    rcClient.bottom = rcClient.top + height;

    m_windowWidth = width;
    m_windowHeight = height;
    const CCSize& frameSize = getFrameSize();
    if (frameSize.width > 0)
    {
        m_windowTouchScaleX = frameSize.width / width;
        m_windowTouchScaleY = frameSize.height / height;

        TCHAR buff[MAX_PATH + 1];
        memset(buff, 0, sizeof(buff));
        swprintf_s(buff, MAX_PATH, L"%s - %0.0fx%0.0f - %0.2f",
                   kWindowClassName, frameSize.width, frameSize.height, 1.0f / m_windowTouchScaleX);
        SetWindowText(m_hWnd, buff);
    }
        
    AdjustWindowRectEx(&rcClient, GetWindowLong(m_hWnd, GWL_STYLE), false, GetWindowLong(m_hWnd, GWL_EXSTYLE));

    // change width and height
    SetWindowPos(m_hWnd, 0, 0, 0, width + ptDiff.x, height + ptDiff.y,
                 SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void CCEGLView::setFrameSize(float width, float height)
{
    Create((LPCTSTR)m_szViewName, (int)width, (int)height);
    CCEGLViewProtocol::setFrameSize(width, height);

    resize(width, height); // adjust window size for menubar
    centerWindow();
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

bool CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    CCEGLViewProtocol::setContentScaleFactor(contentScaleFactor);
    resize((int)(m_obScreenSize.width * contentScaleFactor), (int)(m_obScreenSize.height * contentScaleFactor));
    centerWindow();
    
    return true;
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new CCEGLView();
    }
    return s_pEglView;
}

NS_CC_END
