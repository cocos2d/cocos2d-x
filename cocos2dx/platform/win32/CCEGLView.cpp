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

#if(_MSC_VER >= 1600) // Visual Studio 2010 or higher version.
// Windows Touch define
#define MOUSEEVENTF_FROMTOUCH 0xFF515700

// Windows Touch functions
// Workaround to be able tu run app on Windows XP
typedef WINUSERAPI BOOL (WINAPI *RegisterTouchWindowFn)(_In_ HWND hwnd, _In_ ULONG ulFlags);
typedef WINUSERAPI BOOL (WINAPI *UnregisterTouchWindowFn)(_In_ HWND hwnd);
typedef WINUSERAPI LPARAM (WINAPI *GetMessageExtraInfoFn)(VOID);
typedef WINUSERAPI BOOL (WINAPI *GetTouchInputInfoFn)(_In_ HTOUCHINPUT hTouchInput, _In_ UINT cInputs, __out_ecount(cInputs) PTOUCHINPUT pInputs, _In_ int cbSize);
typedef WINUSERAPI BOOL (WINAPI *CloseTouchInputHandleFn)(_In_ HTOUCHINPUT hTouchInput);

static RegisterTouchWindowFn s_pfRegisterTouchWindowFunction = NULL;
static UnregisterTouchWindowFn s_pfUnregisterTouchWindowFunction = NULL;
static GetMessageExtraInfoFn s_pfGetMessageExtraInfoFunction = NULL;
static GetTouchInputInfoFn s_pfGetTouchInputInfoFunction = NULL;
static CloseTouchInputHandleFn s_pfCloseTouchInputHandleFunction = NULL;

static bool CheckTouchSupport()
{
	s_pfRegisterTouchWindowFunction = (RegisterTouchWindowFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "RegisterTouchWindow");
	s_pfUnregisterTouchWindowFunction = (UnregisterTouchWindowFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "UnregisterTouchWindow");
	s_pfGetMessageExtraInfoFunction = (GetMessageExtraInfoFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetMessageExtraInfo");
	s_pfGetTouchInputInfoFunction = (GetTouchInputInfoFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "GetTouchInputInfo");
	s_pfCloseTouchInputHandleFunction = (CloseTouchInputHandleFn)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "CloseTouchInputHandle");

	return (s_pfRegisterTouchWindowFunction && s_pfUnregisterTouchWindowFunction && s_pfGetMessageExtraInfoFunction && s_pfGetTouchInputInfoFunction && s_pfCloseTouchInputHandleFunction);
}

#endif /* #if(_MSC_VER >= 1600) */

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
        32,                         // preferred color depth
        0, 0, 0, 0, 0, 0,           // color bits (ignored)
        0,                          // no alpha buffer
        0,                          // alpha bits (ignored)
        0,                          // no accumulation buffer
        0, 0, 0, 0,                 // accum bits (ignored)
        24,                         // depth buffer
        8,                          // no stencil buffer
        0,                          // no auxiliary buffers
        PFD_MAIN_PLANE,             // main layer
        0,                          // reserved
        0, 0, 0,                    // no layer, visible, damage masks
    };

    pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
}

static bool glew_dynamic_binding()
{
	const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

	// If the current opengl driver doesn't have framebuffers methods, check if an extension exists
	if (glGenFramebuffers == NULL)
	{
		CCLog("OpenGL: glGenFramebuffers is NULL, try to detect an extension");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			CCLog("OpenGL: ARB_framebuffer_object is supported");

			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
		}
		else
		if (strstr(gl_extensions, "EXT_framebuffer_object"))
		{
			CCLog("OpenGL: EXT_framebuffer_object is supported");
			glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
			glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
			glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
			glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
			glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
			glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
			glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
			glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
			glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
			glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
			glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
			glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
			glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
			glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
			glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
			glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
			glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
		}
		else
		{
			CCLog("OpenGL: No framebuffers extension is supported");
			CCLog("OpenGL: Any call to Fbo will crash!");
			return false;
		}
	}
	return true;
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
, m_fFrameZoomFactor(1.0f)
, m_bSupportTouch(false)
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
		"OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
		glVersion);
		CCMessageBox(strComplain, "OpenGL version too old");
		return false;
    }

    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
		CCMessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
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

    if(glew_dynamic_binding() == false)
	{
		CCMessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
		return false;
	}

    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

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

bool CCEGLView::Create()
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
            //TODO: Initializing width with a large value to avoid getting a wrong client area by 'GetClientRect' function.
            1000,                                               // Window Width
            1000,                                               // Window Height
            NULL,                                                // No Parent Window
            NULL,                                                // No Menu
            hInstance,                                            // Instance
            NULL );

        CC_BREAK_IF(! m_hWnd);

        bRet = initGL();
		if(!bRet) destroyGL();
        CC_BREAK_IF(!bRet);

        s_pMainWindow = this;
        bRet = true;
    } while (0);

#if(_MSC_VER >= 1600)
    m_bSupportTouch = CheckTouchSupport();
    if(m_bSupportTouch)
	{
	    m_bSupportTouch = (s_pfRegisterTouchWindowFunction(m_hWnd, 0) != 0);
    }
#endif /* #if(_MSC_VER >= 1600) */

    return bRet;
}

LRESULT CCEGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL bProcessed = FALSE;

    switch (message)
    {
    case WM_LBUTTONDOWN:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (m_bSupportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */

        if (m_pDelegate && MK_LBUTTON == wParam)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x, point.y);
            pt.x /= m_fFrameZoomFactor;
            pt.y /= m_fFrameZoomFactor;
            CCPoint tmp = ccp(pt.x, m_obScreenSize.height - pt.y);
            if (m_obViewPortRect.equals(CCRectZero) || m_obViewPortRect.containsPoint(tmp))
            {
                m_bCaptured = true;
                SetCapture(m_hWnd);
                int id = 0;
                handleTouchesBegin(1, &id, &pt.x, &pt.y);
            }
        }
        break;

    case WM_MOUSEMOVE:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (m_bSupportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */
        if (MK_LBUTTON == wParam && m_bCaptured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x, point.y);
            int id = 0;
            pt.x /= m_fFrameZoomFactor;
            pt.y /= m_fFrameZoomFactor;
            handleTouchesMove(1, &id, &pt.x, &pt.y);
        }
        break;

    case WM_LBUTTONUP:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (m_bSupportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */
        if (m_bCaptured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            CCPoint pt(point.x, point.y);
            int id = 0;
            pt.x /= m_fFrameZoomFactor;
            pt.y /= m_fFrameZoomFactor;
            handleTouchesEnd(1, &id, &pt.x, &pt.y);

            ReleaseCapture();
            m_bCaptured = false;
        }
        break;
#if(_MSC_VER >= 1600)
    case WM_TOUCH:
		{
            BOOL bHandled = FALSE;
            UINT cInputs = LOWORD(wParam);
            PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
            if (pInputs)
            {
                if (s_pfGetTouchInputInfoFunction((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT)))
                {
                    for (UINT i=0; i < cInputs; i++)
                    {
                        TOUCHINPUT ti = pInputs[i];
                        POINT input;
                        input.x = TOUCH_COORD_TO_PIXEL(ti.x);
                        input.y = TOUCH_COORD_TO_PIXEL(ti.y);
                        ScreenToClient(m_hWnd, &input);
                        CCPoint pt(input.x, input.y);
                        CCPoint tmp = ccp(pt.x, m_obScreenSize.height - pt.y);
                        if (m_obViewPortRect.equals(CCRectZero) || m_obViewPortRect.containsPoint(tmp))
                        {
                            pt.x /= m_fFrameZoomFactor;
                            pt.y /= m_fFrameZoomFactor;

                            if (ti.dwFlags & TOUCHEVENTF_DOWN)
                                handleTouchesBegin(1, reinterpret_cast<int*>(&ti.dwID), &pt.x, &pt.y);
                            else if (ti.dwFlags & TOUCHEVENTF_MOVE)
                                handleTouchesMove(1, reinterpret_cast<int*>(&ti.dwID), &pt.x, &pt.y);
                            else if (ti.dwFlags & TOUCHEVENTF_UP)
                                handleTouchesEnd(1, reinterpret_cast<int*>(&ti.dwID), &pt.x, &pt.y);
                         }
                     }
                     bHandled = TRUE;
                 }
                 delete [] pInputs;
             }
             if (bHandled)
             {
                 s_pfCloseTouchInputHandleFunction((HTOUCHINPUT)lParam);
             }
		}
      break;
#endif /* #if(_MSC_VER >= 1600) */
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
        else if (wParam == VK_ESCAPE)
        {
            CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
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
#if(_MSC_VER >= 1600)
        if(m_bSupportTouch)
		{
		    s_pfUnregisterTouchWindowFunction(m_hWnd);
		}
#endif /* #if(_MSC_VER >= 1600) */
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

void CCEGLView::setMenuResource(LPCWSTR menu)
{
    m_menu = menu;
    if (m_hWnd != NULL)
    {
        HMENU hMenu = LoadMenu(GetModuleHandle(NULL), menu);
        SetMenu(m_hWnd, hMenu);
    }
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

    const CCSize& frameSize = getFrameSize();
    if (frameSize.width > 0)
    {
        WCHAR wszBuf[MAX_PATH] = {0};
#ifdef _DEBUG
        char szBuf[MAX_PATH + 1];
        memset(szBuf, 0, sizeof(szBuf));
        snprintf(szBuf, MAX_PATH, "%s - %0.0fx%0.0f - %0.2f",
                   m_szViewName, frameSize.width, frameSize.height, m_fFrameZoomFactor);
        MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
#else
        MultiByteToWideChar(CP_UTF8, 0, m_szViewName, -1, wszBuf, sizeof(wszBuf));
#endif
        SetWindowText(m_hWnd, wszBuf);
    }

    AdjustWindowRectEx(&rcClient, GetWindowLong(m_hWnd, GWL_STYLE), FALSE, GetWindowLong(m_hWnd, GWL_EXSTYLE));

    // change width and height
    SetWindowPos(m_hWnd, 0, 0, 0, width + ptDiff.x, height + ptDiff.y,
                 SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
    centerWindow();
    CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}

float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void CCEGLView::setFrameSize(float width, float height)
{
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

    int offsetX = rcDesktop.left + (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
    offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
    int offsetY = rcDesktop.top + (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
    offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;

    SetWindowPos(m_hWnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
        (GLint)(y * m_fScaleY  * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
        (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
        (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * m_fScaleX * m_fFrameZoomFactor + m_obViewPortRect.origin.x * m_fFrameZoomFactor),
              (GLint)(y * m_fScaleY * m_fFrameZoomFactor + m_obViewPortRect.origin.y * m_fFrameZoomFactor),
              (GLsizei)(w * m_fScaleX * m_fFrameZoomFactor),
              (GLsizei)(h * m_fScaleY * m_fFrameZoomFactor));
}

CCEGLView* CCEGLView::sharedOpenGLView()
{
    static CCEGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new CCEGLView();
		if(!s_pEglView->Create())
		{
			delete s_pEglView;
			s_pEglView = NULL;
		}
    }

    return s_pEglView;
}

NS_CC_END
