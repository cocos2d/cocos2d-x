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
#include "CCApplication.h"
#ifdef CC_KEYBOARD_SUPPORT
#include "keyboard_dispatcher/CCKeyboardDispatcher.h"
#endif

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
		log("OpenGL: glGenFramebuffers is NULL, try to detect an extension");
		if (strstr(gl_extensions, "ARB_framebuffer_object"))
		{
			log("OpenGL: ARB_framebuffer_object is supported");

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
			log("OpenGL: EXT_framebuffer_object is supported");
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
			log("OpenGL: No framebuffers extension is supported");
			log("OpenGL: Any call to Fbo will crash!");
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
// impliment EGLView
//////////////////////////////////////////////////////////////////////////
static EGLView* s_pMainWindow = NULL;
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

EGLView::EGLView()
: _captured(false)
, _wnd(NULL)
, _DC(NULL)
, _RC(NULL)
, _lpfnAccelerometerKeyHook(NULL)
, _menu(NULL)
, _wndproc(NULL)
, _frameZoomFactor(1.0f)
, _supportTouch(false)
{
    strcpy(_viewName, "Cocos2dxWin32");
}

EGLView::~EGLView()
{

}

bool EGLView::initGL()
{
    _DC = GetDC(_wnd);
    SetupPixelFormat(_DC);
    //SetupPalette();
    _RC = wglCreateContext(_DC);
    wglMakeCurrent(_DC, _RC);

    // check OpenGL version at first
    const GLubyte* glVersion = glGetString(GL_VERSION);
    CCLOG("OpenGL version = %s", glVersion);

    if ( atof((const char*)glVersion) < 1.5 )
    {
        char strComplain[256] = {0};
        sprintf(strComplain,
		"OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.",
		glVersion);
		MessageBox(strComplain, "OpenGL version too old");
		return false;
    }

    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult)
    {
		MessageBox((char *)glewGetErrorString(GlewInitResult), "OpenGL error");
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        log("Ready for GLSL");
    }
    else
    {
        log("Not totally ready :(");
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        log("Ready for OpenGL 2.0");
    }
    else
    {
        log("OpenGL 2.0 not supported");
    }

    if(glew_dynamic_binding() == false)
	{
		MessageBox("No OpenGL framebuffer support. Please upgrade the driver of your video card.", "OpenGL error");
		return false;
	}

    // Enable point size by default on windows.
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    return true;
}

void EGLView::destroyGL()
{
    if (_DC != NULL && _RC != NULL)
    {
        // deselect rendering context and delete it
        wglMakeCurrent(_DC, NULL);
        wglDeleteContext(_RC);
    }
}

bool EGLView::Create()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(_wnd);

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
        wc.lpszMenuName   = _menu;                         //
        wc.lpszClassName  = kWindowClassName;               // Set The Class Name

        CC_BREAK_IF(! RegisterClass(&wc) && 1410 != GetLastError());

        // center window position
        RECT rcDesktop;
        GetWindowRect(GetDesktopWindow(), &rcDesktop);

        WCHAR wszBuf[50] = {0};
        MultiByteToWideChar(CP_UTF8, 0, _viewName, -1, wszBuf, sizeof(wszBuf));

        // create window
        _wnd = CreateWindowEx(
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

        CC_BREAK_IF(! _wnd);

        bRet = initGL();
		if(!bRet) destroyGL();
        CC_BREAK_IF(!bRet);

        s_pMainWindow = this;
        bRet = true;
    } while (0);

#if(_MSC_VER >= 1600)
    _supportTouch = CheckTouchSupport();
    if(_supportTouch)
	{
	    _supportTouch = (s_pfRegisterTouchWindowFunction(_wnd, 0) != 0);
    }
#endif /* #if(_MSC_VER >= 1600) */

    return bRet;
}

LRESULT EGLView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL bProcessed = FALSE;

    switch (message)
    {
    case WM_LBUTTONDOWN:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (_supportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */

        if (_delegate && MK_LBUTTON == wParam)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            Point pt(point.x, point.y);
            pt.x /= _frameZoomFactor;
            pt.y /= _frameZoomFactor;
            Point tmp = Point(pt.x, _screenSize.height - pt.y);
            if (_viewPortRect.equals(Rect::ZERO) || _viewPortRect.containsPoint(tmp))
            {
                _captured = true;
                SetCapture(_wnd);
                int id = 0;
                handleTouchesBegin(1, &id, &pt.x, &pt.y);
            }
        }
        break;

    case WM_MOUSEMOVE:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (_supportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */
        if (MK_LBUTTON == wParam && _captured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            Point pt(point.x, point.y);
            int id = 0;
            pt.x /= _frameZoomFactor;
            pt.y /= _frameZoomFactor;
            handleTouchesMove(1, &id, &pt.x, &pt.y);
        }
        break;

    case WM_LBUTTONUP:
#if(_MSC_VER >= 1600)
        // Don't process message generated by Windows Touch
        if (_supportTouch && (s_pfGetMessageExtraInfoFunction() & MOUSEEVENTF_FROMTOUCH) == MOUSEEVENTF_FROMTOUCH) break;
#endif /* #if(_MSC_VER >= 1600) */
        if (_captured)
        {
            POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
            Point pt(point.x, point.y);
            int id = 0;
            pt.x /= _frameZoomFactor;
            pt.y /= _frameZoomFactor;
            handleTouchesEnd(1, &id, &pt.x, &pt.y);

            ReleaseCapture();
            _captured = false;
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
                        ScreenToClient(_wnd, &input);
                        Point pt(input.x, input.y);
                        Point tmp = Point(pt.x, _screenSize.height - pt.y);
                        if (_viewPortRect.equals(Rect::ZERO) || _viewPortRect.containsPoint(tmp))
                        {
                            pt.x /= _frameZoomFactor;
                            pt.y /= _frameZoomFactor;

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
            Application::getInstance()->applicationWillEnterForeground();
            break;
        case SIZE_MINIMIZED:
            Application::getInstance()->applicationDidEnterBackground();
            break;
        }
        break;
    case WM_KEYDOWN:
#ifdef CC_KEYBOARD_SUPPORT
        Director::getInstance()->getKeyboardDispatcher()->dispatchKeyboardEvent(wParam, true);
#endif
        if (wParam == VK_F1 || wParam == VK_F2)
        {
            Director* pDirector = Director::getInstance();
            if (GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
                pDirector->getKeypadDispatcher()->dispatchKeypadMSG(wParam == VK_F1 ? kTypeBackClicked : kTypeMenuClicked);
        }
        else if (wParam == VK_ESCAPE)
        {
            Director::getInstance()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
        }

        if ( _lpfnAccelerometerKeyHook!=NULL )
        {
            (*_lpfnAccelerometerKeyHook)( message,wParam,lParam );
        }
        break;
    case WM_KEYUP:
#ifdef CC_KEYBOARD_SUPPORT
        Director::getInstance()->getKeyboardDispatcher()->dispatchKeyboardEvent(wParam, false);
#endif
        if ( _lpfnAccelerometerKeyHook!=NULL )
        {
            (*_lpfnAccelerometerKeyHook)( message,wParam,lParam );
        }
        break;
    case WM_CHAR:
        {
            if (wParam < 0x20)
            {
                if (VK_BACK == wParam)
                {
                    IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
                }
                else if (VK_RETURN == wParam)
                {
                    IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
                }
                else if (VK_TAB == wParam)
                {
                    // tab input
                }
                else if (VK_ESCAPE == wParam)
                {
                    // ESC input
                    //CCDirector::getInstance()->end();
                }
            }
            else if (wParam < 128)
            {
                // ascii char
                IMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&wParam, 1);
            }
            else
            {
                char szUtf8[8] = {0};
                int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&wParam, 1, szUtf8, sizeof(szUtf8), NULL, NULL);
                IMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
            }
            if ( _lpfnAccelerometerKeyHook!=NULL )
            {
                (*_lpfnAccelerometerKeyHook)( message,wParam,lParam );
            }
        }
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(_wnd, &ps);
        EndPaint(_wnd, &ps);
        break;

    case WM_CLOSE:
        Director::getInstance()->end();
        break;

    case WM_DESTROY:
        destroyGL();
        PostQuitMessage(0);
        break;

    default:
        if (_wndproc)
        {

            _wndproc(message, wParam, lParam, &bProcessed);
            if (bProcessed) break;
        }
        return DefWindowProc(_wnd, message, wParam, lParam);
    }

    if (_wndproc && !bProcessed)
    {
        _wndproc(message, wParam, lParam, &bProcessed);
    }
    return 0;
}

void EGLView::setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook )
{
    _lpfnAccelerometerKeyHook=lpfnAccelerometerKeyHook;
}


bool EGLView::isOpenGLReady()
{
    return (_DC != NULL && _RC != NULL);
}

void EGLView::end()
{
    if (_wnd)
    {
#if(_MSC_VER >= 1600)
        if(_supportTouch)
		{
		    s_pfUnregisterTouchWindowFunction(_wnd);
		}
#endif /* #if(_MSC_VER >= 1600) */
        DestroyWindow(_wnd);
        _wnd = NULL;
    }
    s_pMainWindow = NULL;
    UnregisterClass(kWindowClassName, GetModuleHandle(NULL));
    delete this;
}

void EGLView::swapBuffers()
{
    if (_DC != NULL)
    {
        ::SwapBuffers(_DC);
    }
}


void EGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

void EGLView::setMenuResource(LPCWSTR menu)
{
    _menu = menu;
    if (_wnd != NULL)
    {
        HMENU hMenu = LoadMenu(GetModuleHandle(NULL), menu);
        SetMenu(_wnd, hMenu);
    }
}

void EGLView::setWndProc(CUSTOM_WND_PROC proc)
{
    _wndproc = proc;
}

HWND EGLView::getHWnd()
{
    return _wnd;
}

void EGLView::resize(int width, int height)
{
    if (! _wnd)
    {
        return;
    }

    RECT rcWindow;
    GetWindowRect(_wnd, &rcWindow);

    RECT rcClient;
    GetClientRect(_wnd, &rcClient);

    // calculate new window width and height
    POINT ptDiff;
    ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
    ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
    rcClient.right = rcClient.left + width;
    rcClient.bottom = rcClient.top + height;

    const Size& frameSize = getFrameSize();
    if (frameSize.width > 0)
    {
        WCHAR wszBuf[MAX_PATH] = {0};
#ifdef _DEBUG
        char szBuf[MAX_PATH + 1];
        memset(szBuf, 0, sizeof(szBuf));
        snprintf(szBuf, MAX_PATH, "%s - %0.0fx%0.0f - %0.2f",
                   _viewName, frameSize.width, frameSize.height, _frameZoomFactor);
        MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
#else
        MultiByteToWideChar(CP_UTF8, 0, _viewName, -1, wszBuf, sizeof(wszBuf));
#endif
        SetWindowText(_wnd, wszBuf);
    }

    AdjustWindowRectEx(&rcClient, GetWindowLong(_wnd, GWL_STYLE), FALSE, GetWindowLong(_wnd, GWL_EXSTYLE));

    // change width and height
    SetWindowPos(_wnd, 0, 0, 0, width + ptDiff.x, height + ptDiff.y,
                 SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void EGLView::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    resize(_screenSize.width * fZoomFactor, _screenSize.height * fZoomFactor);
    centerWindow();
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
}

float EGLView::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void EGLView::setFrameSize(float width, float height)
{
    EGLViewProtocol::setFrameSize(width, height);

    resize(width, height); // adjust window size for menubar
    centerWindow();
}

void EGLView::centerWindow()
{
    if (! _wnd)
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
    GetWindowRect(_wnd, &rcWindow);

    int offsetX = rcDesktop.left + (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
    offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
    int offsetY = rcDesktop.top + (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
    offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;

    SetWindowPos(_wnd, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void EGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
        (GLint)(y * _scaleY  * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
        (GLsizei)(w * _scaleX * _frameZoomFactor),
        (GLsizei)(h * _scaleY * _frameZoomFactor));
}

void EGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint)(x * _scaleX * _frameZoomFactor + _viewPortRect.origin.x * _frameZoomFactor),
              (GLint)(y * _scaleY * _frameZoomFactor + _viewPortRect.origin.y * _frameZoomFactor),
              (GLsizei)(w * _scaleX * _frameZoomFactor),
              (GLsizei)(h * _scaleY * _frameZoomFactor));
}

EGLView* EGLView::getInstance()
{
    static EGLView* s_pEglView = NULL;
    if (s_pEglView == NULL)
    {
        s_pEglView = new EGLView();
		if(!s_pEglView->Create())
		{
			delete s_pEglView;
			s_pEglView = NULL;
		}
    }

    return s_pEglView;
}

// XXX: deprecated
EGLView* EGLView::sharedOpenGLView()
{
    return EGLView::getInstance();
}

NS_CC_END
