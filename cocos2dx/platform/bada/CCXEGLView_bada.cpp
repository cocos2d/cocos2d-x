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

#include "CCXEGLView.h"


#include "CCXCocos2dDefine_bada.h"
#include "NSSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCXUIAccelerometer_bada.h"
#include <GLES/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>


using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


#define TIME_OUT 10

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
	}

	static CCXEGL * create(CCXEGLView * pWindow)
	{
		CCXEGL * pEGL = new CCXEGL;
		bool bSuccess = false;
		do 
		{
			CCX_BREAK_IF(! pEGL);

			pEGL->m_eglNativeWindow = pWindow;

			//cjh pEGL->m_eglNativeDisplay = GetDC(pEGL->m_eglNativeWindow);

			EGLDisplay eglDisplay;
			CCX_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglNativeDisplay)));

			EGLint nMajor, nMinor;
			CCX_BREAK_IF(EGL_FALSE == eglInitialize(eglDisplay, &nMajor, &nMinor) || 1 != nMajor);

//			const EGLint aConfigAttribs[] =
//			{
//				EGL_LEVEL,				0,
//				EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
//				EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
//				EGL_NATIVE_RENDERABLE,	EGL_FALSE,
//				EGL_DEPTH_SIZE,			16,
//				EGL_NONE,
//			};

			//cjh bada
			EGLint aConfigAttribs[] = {
				EGL_RED_SIZE,	5,
				EGL_GREEN_SIZE,	6,
				EGL_BLUE_SIZE,	5,
				EGL_ALPHA_SIZE,	0,
				EGL_DEPTH_SIZE, 8,
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
				EGL_NONE
			};
			eglBindAPI(EGL_OPENGL_ES_API);
			///

			EGLint iConfigs;
			EGLConfig eglConfig;
			CCX_BREAK_IF(EGL_FALSE == eglChooseConfig(eglDisplay, aConfigAttribs, &eglConfig, 1, &iConfigs) 
				|| (iConfigs != 1));

			EGLContext eglContext;
			eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL);
			CCX_BREAK_IF(EGL_NO_CONTEXT == eglContext);

			EGLSurface eglSurface;
			eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, pEGL->m_eglNativeWindow, NULL);
			CCX_BREAK_IF(EGL_NO_SURFACE == eglSurface);

			CCX_BREAK_IF(EGL_FALSE == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext));

			pEGL->m_eglDisplay = eglDisplay;
			pEGL->m_eglConfig  = eglConfig;
			pEGL->m_eglContext = eglContext;
			pEGL->m_eglSurface = eglSurface;
			bSuccess = true;
		} while (0);

		if (! bSuccess)
		{
			CCX_SAFE_DELETE(pEGL);  
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
// impliment CCXEGLView
//////////////////////////////////////////////////////////////////////////
static CCXEGLView * pMainWindow;


CCXEGLView::CCXEGLView()
: m_bCaptured(false)
, m_bOrientationReverted(false)
, m_pDelegate(NULL)
, m_pEGL(NULL)
, m_pTimer(null)
{
    m_pTouch    = new CCTouch;
    m_pSet      = new NSSet;
	m_eInitOrientation = CCDirector::sharedDirector()->getDeviceOrientation();
	m_bOrientationInitVertical = (CCDeviceOrientationPortrait == m_eInitOrientation
		|| kCCDeviceOrientationPortraitUpsideDown == m_eInitOrientation) ? true : false;
	m_nowOrientation = ORIENTATION_PORTRAIT;
}

CCXEGLView::~CCXEGLView()
{
	release();
    CCX_SAFE_DELETE(m_pSet);
    CCX_SAFE_DELETE(m_pTouch);
    CCX_SAFE_DELETE(m_pDelegate);
	CCX_SAFE_DELETE(m_pEGL);
}

CGSize CCXEGLView::getSize()
{
//	CGSize size(GetBounds().width, GetBounds().height);
	if (m_nowOrientation == ORIENTATION_PORTRAIT || m_nowOrientation == ORIENTATION_PORTRAIT_REVERSE)
	{
		return CGSize(480, 800);
	}
	else
	{
		return CGSize(800, 480);
	}
//	return size;
}

CGRect CCXEGLView::getFrame()
{
	CGRect rc(GetBounds().x, GetBounds().y, GetBounds().width, GetBounds().height);
	return rc;
}

bool CCXEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCXEGLView::release()
{
	if (m_pTimer)
	{
		m_pTimer->Cancel();
		delete m_pTimer;
		m_pTimer = null;
	}
	Application::GetInstance()->Terminate();
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
//typedef enum {
//	/// Device oriented vertically, home button on the bottom
//	kCCDeviceOrientationPortrait = 0, // UIDeviceOrientationPortrait,
//	/// Device oriented vertically, home button on the top
//    kCCDeviceOrientationPortraitUpsideDown = 1, // UIDeviceOrientationPortraitUpsideDown,
//	/// Device oriented horizontally, home button on the right
//    kCCDeviceOrientationLandscapeLeft = 2, // UIDeviceOrientationLandscapeLeft,
//	/// Device oriented horizontally, home button on the left
//    kCCDeviceOrientationLandscapeRight = 3, // UIDeviceOrientationLandscapeRight,
//
//	// Backward compatibility stuff
//	CCDeviceOrientationPortrait = kCCDeviceOrientationPortrait,
//	CCDeviceOrientationPortraitUpsideDown = kCCDeviceOrientationPortraitUpsideDown,
//	CCDeviceOrientationLandscapeLeft = kCCDeviceOrientationLandscapeLeft,
//	CCDeviceOrientationLandscapeRight = kCCDeviceOrientationLandscapeRight,
//} ccDeviceOrientation;
//
//enum Orientation
//{
//	ORIENTATION_NONE,						/**< The control has no orientation style */
//	ORIENTATION_PORTRAIT,					/**< The control has vertical orientation style */
//	ORIENTATION_LANDSCAPE,					/**< The control has horizontal orientation style */
//	ORIENTATION_PORTRAIT_REVERSE,		/**< The control has vertical upside-down orientation style */
//	ORIENTATION_LANDSCAPE_REVERSE,			/**< The control has horizontal reverse orientation style */
//	ORIENTATION_AUTOMATIC = 6,					/**< The control has vertical, horizontal, and horizontal reverse orientation styles*/
//	ORIENTATION_AUTOMATIC_FOUR_DIRECTION = 8,	/**< The control has four-directional orientation style */
//};

static int badaOrientation[4] = {
		ORIENTATION_PORTRAIT,
		ORIENTATION_PORTRAIT_REVERSE,
		ORIENTATION_LANDSCAPE,
		ORIENTATION_LANDSCAPE_REVERSE
};

int CCXEGLView::setDeviceOrientation(int eOritation)
{
	m_nowOrientation = (Orientation)badaOrientation[eOritation];
	AppLog("111width = %d, height = %d", GetBounds().width, GetBounds().height);
	SetOrientation(m_nowOrientation);
	AppLog("222width = %d, height = %d", GetBounds().width, GetBounds().height);
	return m_eInitOrientation;
}

//bada
bool
CCXEGLView::Create(Osp::App::Application* pApp)
{
	// Construct an XML form
	Construct(FORM_STYLE_NORMAL);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pFrame->AddControl(*this);
	pFrame->SetCurrentForm(*this);

	m_pEGL = CCXEGL::create(this);
	if (m_pEGL == null)
		return false;
	Draw();
	Show();
	return true;
}

result
CCXEGLView::OnInitializing(void)
{
	result r = E_SUCCESS;

	AddTouchEventListener(*this);
//	Touch touch;
//	touch.SetMultipointEnabled(*this, true);
	m_pTimer = new Timer;
	if (null == m_pTimer)
	{
		return E_FAILURE;
	}

	r = m_pTimer->Construct(*this);
	if (IsFailed(r))
	{
		delete m_pTimer;
		m_pTimer = null;
		return E_FAILURE;
	}
	m_pTimer->Start(TIME_OUT);

	return r;
}

result
CCXEGLView::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
CCXEGLView::OnTimerExpired(Timer& timer)
{
	if (!m_pTimer)
	{
		return;
	}

	m_pTimer->Start(TIME_OUT);
	CCDirector::sharedDirector()->preMainLoop();
}

// touch event
void CCXEGLView::OnTouchIndicated(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& startPosition, const Osp::Graphics::Point& currentPoint)
{

}

void CCXEGLView::OnTouchPressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchPressed...");
	if (m_pDelegate && m_pTouch)
	{
		m_bCaptured = true;

		m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
		m_pSet->addObject(m_pTouch);
		m_pDelegate->touchesBegan(m_pSet, NULL);
	}



}

void CCXEGLView::OnTouchLongPressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCXEGLView::OnTouchReleased(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchReleased...");
	if (m_bCaptured)
	{
		m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
		m_pDelegate->touchesEnded(m_pSet, NULL);
		m_pSet->removeObject(m_pTouch);
		m_bCaptured = false;
	}
}


void CCXEGLView::OnTouchMoved(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchMoved...");
	if (m_bCaptured)
	{
        m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
        m_pDelegate->touchesMoved(m_pSet, NULL);
	}
}


void CCXEGLView::OnTouchDoublePressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCXEGLView::OnTouchFocusIn(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCXEGLView::OnTouchFocusOut(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}

result CCXEGLView::OnDraw(void)
{
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->drawScene();
}

}       // end of namespace cocos2d
