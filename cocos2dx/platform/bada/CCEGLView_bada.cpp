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
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCAccelerometer_bada.h"
#include <GLES/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>


using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

#define TIME_OUT 10

NS_CC_BEGIN;

//////////////////////////////////////////////////////////////////////////
// impliment CCEGL
//////////////////////////////////////////////////////////////////////////
static CCEGLView * s_pMainWindow;

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
	}

	static CCEGL * create(CCEGLView * pWindow)
	{
		CCEGL * pEGL = new CCEGL;
		bool bSuccess = false;
		do 
		{
			CC_BREAK_IF(! pEGL);

			pEGL->m_eglNativeWindow = pWindow;

			EGLDisplay eglDisplay;
			CC_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglNativeDisplay)));

			EGLint nMajor, nMinor;
			CC_BREAK_IF(EGL_FALSE == eglInitialize(eglDisplay, &nMajor, &nMinor) || 1 != nMajor);

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
			bSuccess = true;

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


CCEGLView::CCEGLView()
: m_bNotHVGA(true)
, m_pDelegate(NULL)
, m_fScreenScaleFactor(1.0)
, m_bCaptured(false)
, m_pEGL(NULL)
, m_pTimer(null)
{
    m_pTouch    = new CCTouch;
    m_pSet      = new CCSet;
	m_eInitOrientation = CCDirector::sharedDirector()->getDeviceOrientation();
}

CCEGLView::~CCEGLView()
{
	release();
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);
	CC_SAFE_DELETE(m_pEGL);
}

CCSize CCEGLView::getSize()
{
	CCSize s;
	if (m_nowOrientation == ORIENTATION_PORTRAIT || m_nowOrientation == ORIENTATION_PORTRAIT_REVERSE)
	{
		if (m_bNotHVGA)
		{
			s = CCSizeMake(480, 800);
		}
		else
		{
			s = CCSizeMake(320, 480);
		}
	}
	else
	{
		if (m_bNotHVGA)
		{
			s = CCSizeMake(800, 480);
		}
		else
		{
			s = CCSizeMake(480, 320);
		}
	}
	return s;
}

CCRect CCEGLView::getFrame()
{
	CCRect rc;
	if (m_bNotHVGA)
	{
		rc = CCRectMake(0, 0, 800, 480);
	}
	else
	{
		rc = CCRectMake(0, 0, 480, 320);
	}
	return rc;
}

bool CCEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCEGLView::release()
{
	if (m_pTimer)
	{
		m_pTimer->Cancel();
		delete m_pTimer;
		m_pTimer = null;
	}
	Application::GetInstance()->Terminate();
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

bool CCEGLView::canSetContentScaleFactor()
{
    // can scale content?
    return false;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
	m_fScreenScaleFactor = contentScaleFactor;
}

static int badaOrientation[4] = {
		ORIENTATION_PORTRAIT,
		ORIENTATION_PORTRAIT_REVERSE,
		ORIENTATION_LANDSCAPE,
		ORIENTATION_LANDSCAPE_REVERSE
};

int CCEGLView::setDeviceOrientation(int eOritation)
{
	m_nowOrientation = (Orientation)badaOrientation[eOritation];
	SetOrientation(m_nowOrientation);
	return m_eInitOrientation;
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
            (GLint)(y * factor) + m_rcViewPort.origin.y,
            (GLint)(w * factor),
            (GLint)(h * factor));
    }
    else
    {
        glViewport((GLint)x,
            (GLint)y,
            (GLint)w,
            (GLint)h);
    }
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
    if (m_bNotHVGA)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
            (GLint)(y * factor) + m_rcViewPort.origin.y,
            (GLint)(w * factor),
            (GLint)(h * factor));
    }
    else
    {
        glScissor((GLint)x,
            (GLint)y,
            (GLint)w,
            (GLint)h);
    }
}

void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{
}

//bada
bool
CCEGLView::Create(Osp::App::Application* pApp)
{
	// Construct an XML form
	Construct(FORM_STYLE_NORMAL);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pFrame->AddControl(*this);
	pFrame->SetCurrentForm(*this);

	m_pEGL = CCEGL::create(this);
	if (m_pEGL == null)
		return false;
	s_pMainWindow = this;
	Draw();
	Show();
	return true;
}

result
CCEGLView::OnInitializing(void)
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

	Rectangle rc = GetBounds();
	if ((rc.width == 480 && rc.height == 720)
			|| (rc.width == 720 && rc.height == 480))
	{
		m_bNotHVGA = false;
		m_sSizeInPoint.width = 480;
		m_sSizeInPoint.height = 320;
	}
	else
	{
		m_bNotHVGA = true;
		m_sSizeInPoint.width = 800;
		m_sSizeInPoint.height = 480;
	}



	// calculate the factor and the rect of viewport
	m_fScreenScaleFactor =  MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width,
		                         (float)m_sSizeInPixel.height / m_sSizeInPoint.height);
	int viewPortW = (int)(m_sSizeInPoint.width * m_fScreenScaleFactor);
	int viewPortH = (int)(m_sSizeInPoint.height * m_fScreenScaleFactor);
	m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
	m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
	m_rcViewPort.size.width = viewPortW;
	m_rcViewPort.size.height = viewPortH;

	return r;
}

result
CCEGLView::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
CCEGLView::OnTimerExpired(Timer& timer)
{
	if (!m_pTimer)
	{
		return;
	}

	m_pTimer->Start(TIME_OUT);
	CCDirector::sharedDirector()->mainLoop();
}

// touch event
void CCEGLView::OnTouchIndicated(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& startPosition, const Osp::Graphics::Point& currentPoint)
{

}

void CCEGLView::OnTouchPressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchPressed... x = %d, y = %d", currentPosition.x, currentPosition.y);
	if (m_pDelegate && m_pTouch)
	{
		m_bCaptured = true;
		if (m_bNotHVGA)
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
		}
		else
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x*2/3, (float)currentPosition.y*2/3);
		}

		m_pSet->addObject(m_pTouch);
		m_pDelegate->touchesBegan(m_pSet, NULL);
	}



}

void CCEGLView::OnTouchLongPressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCEGLView::OnTouchReleased(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchReleased... x = %d, y = %d", currentPosition.x, currentPosition.y);
	if (m_bCaptured)
	{
		if (m_bNotHVGA)
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
		}
		else
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x*2/3, (float)currentPosition.y*2/3);
		}

		m_pDelegate->touchesEnded(m_pSet, NULL);
		m_pSet->removeObject(m_pTouch);
		m_bCaptured = false;
	}
}


void CCEGLView::OnTouchMoved(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	AppLog("OnTouchMoved... x = %d, y = %d", currentPosition.x, currentPosition.y);
	if (m_bCaptured)
	{
		if (m_bNotHVGA)
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x, (float)currentPosition.y);
		}
		else
		{
			m_pTouch->SetTouchInfo(0, (float)currentPosition.x*2/3, (float)currentPosition.y*2/3);
		}
        m_pDelegate->touchesMoved(m_pSet, NULL);
	}
}


void CCEGLView::OnTouchDoublePressed(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCEGLView::OnTouchFocusIn(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}


void CCEGLView::OnTouchFocusOut(const Osp::Ui::Control& source,
	const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{

}

result CCEGLView::OnDraw(void)
{
	result r = E_SUCCESS;
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->drawScene();
	return r;
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    CC_ASSERT(s_pMainWindow);
    return *s_pMainWindow;
}

NS_CC_END;
