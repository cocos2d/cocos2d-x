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

#include "EGL/egl.h"
#include "gles/gl.h"

#include "CCCocos2dDefine.h"
#include "CCSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

namespace cocos2d {

//////////////////////////////////////////////////////////////////////////
// impliment CCXEGL
//////////////////////////////////////////////////////////////////////////

class CCXEGL
{
public:
	~CCXEGL() 
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

	static CCXEGL * create(CCEGLView * pWindow)
	{
		CCXEGL * pEGL = new CCXEGL;
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
				EGL_LEVEL,				0,
				EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
				EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
				EGL_NATIVE_RENDERABLE,	EGL_FALSE,
				EGL_DEPTH_SIZE,			16,
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
//  		if (! m_eglNativeWindow || EGL_NO_DISPLAY == m_eglDisplay)
//  		{
//  			return;
//  		}
//  
//  		// release old surface
//  		if (EGL_NO_SURFACE != m_eglSurface)
//  		{
//  			eglDestroySurface(m_eglDisplay, m_eglSurface);
//  			m_eglSurface = EGL_NO_SURFACE;
//  		}
//  
//  		// create new surface and make current
//  		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_eglNativeWindow, NULL);
//  		eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
	}

	void swapBuffers()
	{
		if (EGL_NO_DISPLAY != m_eglDisplay)
		{
			eglSwapBuffers(m_eglDisplay, m_eglSurface);
		}
	}
private:
	CCXEGL() 
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
static CCEGLView * pMainWindow;
static const WCHAR * kWindowClassName = L"Cocos2dxWin32";

static LRESULT CALLBACK _WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (pMainWindow && pMainWindow->getHWnd() == hWnd)
	{
		return pMainWindow->WindowProc(uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

CCEGLView::CCEGLView()
: m_bCaptured(false)
, m_bOrientationReverted(false)
, m_pDelegate(NULL)
, m_pEGL(NULL)
, m_hWnd(NULL)
{
    m_pTouch    = new CCTouch;
    m_pSet      = new CCSet;
	m_eInitOrientation = CCDirector::sharedDirector()->getDeviceOrientation();
	m_bOrientationInitVertical = (CCDeviceOrientationPortrait == m_eInitOrientation
		|| kCCDeviceOrientationPortraitUpsideDown == m_eInitOrientation) ? true : false;
}

CCEGLView::~CCEGLView()
{
	release();
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);
	CC_SAFE_DELETE(m_pEGL);
}

bool CCEGLView::Create(LPCTSTR pTitle, int w, int h)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(m_hWnd);

		HINSTANCE hInstance = GetModuleHandle( NULL );
		WNDCLASS  wc;		// Windows Class Structure

		// Redraw On Size, And Own DC For Window.
		wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  
		wc.lpfnWndProc    = _WindowProc;					// WndProc Handles Messages
		wc.cbClsExtra     = 0;                              // No Extra Window Data
		wc.cbWndExtra     = 0;								// No Extra Window Data
		wc.hInstance      = hInstance;						// Set The Instance
		wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );	// Load The Default Icon
		wc.hCursor        = LoadCursor( NULL, IDC_ARROW );	// Load The Arrow Pointer
		wc.hbrBackground  = NULL;                           // No Background Required For GL
		wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
		wc.lpszClassName  = kWindowClassName;               // Set The Class Name

		CC_BREAK_IF(! RegisterClass(&wc) && 1410 != GetLastError());		

		// center window position
		RECT rcDesktop;
		GetWindowRect(GetDesktopWindow(), &rcDesktop);
		RECT rect = {(rcDesktop.right + rcDesktop.left - w) / 2, (rcDesktop.bottom + rcDesktop.top - h) / 2, 0, 0};
		rect.right = rect.left + w;
		rect.bottom = rect.top + h;
		AdjustWindowRectEx(&rect, WS_CAPTION | WS_POPUPWINDOW, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		// create window
		m_hWnd = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	// Extended Style For The Window
			kWindowClassName,									// Class Name
			pTitle,												// Window Title
			WS_CAPTION | WS_POPUPWINDOW,	// Defined Window Style
			rect.left, rect.top,								// Window Position
			rect.right - rect.left,                             // Window Width
			rect.bottom - rect.top,                             // Window Height
			NULL,												// No Parent Window
			NULL,												// No Menu
			hInstance,											// Instance
			NULL );

		CC_BREAK_IF(! m_hWnd);

		// init egl
		m_pEGL = CCXEGL::create(this);

		if (! m_pEGL)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = NULL;
			break;
		}

		ShowWindow(m_hWnd, SW_SHOW);
		pMainWindow = this;
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
		if (m_pDelegate && m_pTouch && MK_LBUTTON == wParam)
		{
			m_bCaptured = true;
			m_pTouch->SetTouchInfo(0, (float)LOWORD(lParam), (float)HIWORD(lParam));
			m_pSet->addObject(m_pTouch);
			m_pDelegate->touchesBegan(m_pSet, NULL);
		}
		break;

	case WM_MOUSEMOVE:
		if (MK_LBUTTON == wParam && m_bCaptured)
		{
            m_pTouch->SetTouchInfo(0, (float)LOWORD(lParam), (float)HIWORD(lParam));
            m_pDelegate->touchesMoved(m_pSet, NULL);
		}
		break;

	case WM_LBUTTONUP:
		if (m_bCaptured)
		{
			m_pTouch->SetTouchInfo(0, (float)LOWORD(lParam), (float)HIWORD(lParam));
			m_pDelegate->touchesEnded(m_pSet, NULL);
			m_pSet->removeObject(m_pTouch);
			m_bCaptured = false;
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

CCSize CCEGLView::getSize()
{
	RECT rc;
	GetClientRect(m_hWnd, &rc);
    return CCSize((float)(rc.right - rc.left), (float)(rc.bottom - rc.top));
}

CCRect CCEGLView::getFrame()
{
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	return (CCRect((float)rc.left, (float)rc.top, (float)(rc.right - rc.left), (float)(rc.bottom - rc.top)));
}

bool CCEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCEGLView::release()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
	pMainWindow = NULL;
	UnregisterClass(kWindowClassName, GetModuleHandle(NULL));
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
    m_pDelegate = pDelegate;
}

void CCEGLView::swapBuffers()
{
    if (m_pEGL)
    {
        m_pEGL->swapBuffers();
    }
}

HWND CCEGLView::getHWnd()
{
	return m_hWnd;
}

int CCEGLView::setDeviceOrientation(int eOritation)
{
	do 
	{
		bool bVertical = (CCDeviceOrientationPortrait == eOritation
			|| kCCDeviceOrientationPortraitUpsideDown == eOritation) ? true : false;

		CC_BREAK_IF(m_bOrientationReverted && bVertical != m_bOrientationInitVertical);
		CC_BREAK_IF(! m_bOrientationReverted && bVertical == m_bOrientationInitVertical);

		RECT rc;
		GetClientRect(m_hWnd, &rc);

		// swap width and height
		LONG nTmp = rc.right;
		rc.right = rc.bottom;
		rc.bottom = nTmp;

		// calc new window size
		AdjustWindowRectEx(&rc, GetWindowLong(m_hWnd, GWL_STYLE), false, GetWindowLong(m_hWnd, GWL_EXSTYLE));

		// change width and height
		SetWindowPos(m_hWnd, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 
			SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		if (m_pEGL)
		{
			m_pEGL->resizeSurface();
		}
		m_bOrientationReverted = (bVertical == m_bOrientationInitVertical) ? false : true;
	} while (0);

	return m_eInitOrientation;
}

bool CCEGLView::canSetContentScaleFactor()
{
    // can scale content?
    return false;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    // if it supports scaling content, set it
}

}       // end of namespace cocos2d
