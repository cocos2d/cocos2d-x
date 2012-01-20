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
#include "CCIMEDispatcher.h"
#include <FText.h>

using namespace std;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;
using namespace Osp::Text;
using namespace Osp::System;
using namespace Osp::App;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

NS_CC_BEGIN;

static CCEGLView * s_pMainWindow;
static HashMapT<int, CCTouch*> s_mapTouches; // key: pointer id; value: CCTouch*
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
#ifdef CC_BADA_2_0
PFNGLGENERATEMIPMAPOESPROC         CCEGLView::glGenerateMipmapOES = 0;
PFNGLGENFRAMEBUFFERSOESPROC        CCEGLView::glGenFramebuffersOES = 0;
PFNGLBINDFRAMEBUFFEROESPROC		   CCEGLView::glBindFramebufferOES = 0;
PFNGLFRAMEBUFFERTEXTURE2DOESPROC   CCEGLView::glFramebufferTexture2DOES = 0;
PFNGLDELETEFRAMEBUFFERSOESPROC     CCEGLView::glDeleteFramebuffersOES = 0;
PFNGLCHECKFRAMEBUFFERSTATUSOESPROC CCEGLView::glCheckFramebufferStatusOES = 0;
#endif
CCEGLView::CCEGLView()
: m_pKeypad(null)
, m_bNotHVGA(true)
, m_pDelegate(NULL)
, m_fScreenScaleFactor(1.0)
, m_bCaptured(false)
, m_pEGL(NULL)
{
#ifdef CC_BADA_2_0
	glGenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC)eglGetProcAddress("glGenerateMipmapOES");
	glGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC)eglGetProcAddress("glGenFramebuffersOES");
	glBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC)eglGetProcAddress("glBindFramebufferOES");
	glFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC)eglGetProcAddress("glFramebufferTexture2DOES");
	glDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC)eglGetProcAddress("glDeleteFramebuffersOES");
	glCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC)eglGetProcAddress("glCheckFramebufferStatusOES");
#endif
    m_pTouch    = new CCTouch;
    m_pSet      = new CCSet;
	m_eInitOrientation = CCDirector::sharedDirector()->getDeviceOrientation();
	s_mapTouches.Construct();
}

CCEGLView::~CCEGLView()
{
	release();
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);
	CC_SAFE_DELETE(m_pEGL);
	CC_SAFE_DELETE(m_pKeypad);
}

CCSize CCEGLView::getSize()
{
	CCSize s;
//	if (m_bNotHVGA)
	{
		s = CCSizeMake(m_sSizeInPoint.width, m_sSizeInPoint.height);
	}
//	else
//	{
//		s = CCSizeMake(m_sSizeInPixel.width, m_sSizeInPixel.height);
//	}
	return s;
}

CCRect CCEGLView::getFrame()
{
	CCRect rc;
//	if (m_bNotHVGA)
//	{
//		rc = CCRectMake(0, 0, m_sSizeInPixel.width, m_sSizeInPixel.height);
//	}
//	else
	{
		rc = CCRectMake(0, 0, m_sSizeInPoint.width, m_sSizeInPoint.height);
	}
	return rc;
}

bool CCEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCEGLView::release()
{
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

int CCEGLView::setDeviceOrientation(Orientation eOritation)
{
	SetOrientation(eOritation);

	if (eOritation == ORIENTATION_PORTRAIT || eOritation == ORIENTATION_PORTRAIT_REVERSE)
	{
		int width = MIN(m_sSizeInPixel.width, m_sSizeInPixel.height);
		m_sSizeInPixel.height = MAX(m_sSizeInPixel.width, m_sSizeInPixel.height);
		m_sSizeInPixel.width = width;
		width = MIN(m_sSizeInPoint.width, m_sSizeInPoint.height);
		m_sSizeInPoint.height = MAX(m_sSizeInPoint.width, m_sSizeInPoint.height);
		m_sSizeInPoint.width = width;
		resize(m_sSizeInPoint.width, m_sSizeInPoint.height);
	}
	else
	{
		int width = MAX(m_sSizeInPixel.width, m_sSizeInPixel.height);
		m_sSizeInPixel.height = MIN(m_sSizeInPixel.width, m_sSizeInPixel.height);
		m_sSizeInPixel.width = width;
		width = MAX(m_sSizeInPoint.width, m_sSizeInPoint.height);
		m_sSizeInPoint.height = MIN(m_sSizeInPoint.width, m_sSizeInPoint.height);
		m_sSizeInPoint.width = width;
		resize(m_sSizeInPoint.width, m_sSizeInPoint.height);
	}

	return m_eInitOrientation;
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
	float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
	glViewport((GLint)(x * factor) + m_rcViewPort.origin.x,
		(GLint)(y * factor) + m_rcViewPort.origin.y,
		(GLint)(w * factor),
		(GLint)(h * factor));
}

void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
{
	float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
	glScissor((GLint)(x * factor) + m_rcViewPort.origin.x,
		(GLint)(y * factor) + m_rcViewPort.origin.y,
		(GLint)(w * factor),
		(GLint)(h * factor));
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
	if (bOpen)
	{
		const char * pszText = CCIMEDispatcher::sharedDispatcher()->getContentText();
		m_pKeypad->SetText(pszText);
	    m_pKeypad->SetShowState(bOpen);
	    m_pKeypad->Show();
	}
}

bool CCEGLView::Create(Osp::App::Application* pApp, int width, int height)
{
	m_sSizeInPoint.width = MIN(width, height);
	m_sSizeInPoint.height = MAX(width, height);
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


void CCEGLView::resize(int width, int height)
{
	int viewPortW = (int)ceil(width * m_fScreenScaleFactor);
	int viewPortH = (int)ceil(height * m_fScreenScaleFactor);
	m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
	m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
	m_rcViewPort.size.width = viewPortW;
	m_rcViewPort.size.height = viewPortH;
	CCLOG("m_rcViewPort.origin.x = %f, y = %f, width = %f, height = %f", \
			m_rcViewPort.origin.x, m_rcViewPort.origin.y, m_rcViewPort.size.width, m_rcViewPort.size.height);
}

result CCEGLView::OnInitializing(void)
{
	result r = E_SUCCESS;

	AddTouchEventListener(*this);
	Touch touch;
	touch.SetMultipointEnabled(*this, true);

    m_pKeypad = new Keypad();
    m_pKeypad->Construct(KEYPAD_STYLE_NORMAL, KEYPAD_MODE_ALPHA);
    m_pKeypad->AddTextEventListener(*this);

	Rectangle rc = GetBounds();
	if ((rc.width == 480 && rc.height == 720)
			|| (rc.width == 720 && rc.height == 480))
	{
		m_bNotHVGA = false;
		m_sSizeInPixel.width = rc.width / 1.5f;
		m_sSizeInPixel.height = rc.height / 1.5f;
	}
	else
	{
		m_bNotHVGA = true;
		m_sSizeInPixel.width = rc.width;
		m_sSizeInPixel.height = rc.height;
	}

	// calculate the factor and the rect of viewport
	m_fScreenScaleFactor =  MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width,
		                         (float)m_sSizeInPixel.height / m_sSizeInPoint.height);
	CCLOG("rc.width = %d, rc.height = %d, m_fScreenScaleFactor = %f", rc.width, rc.height, m_fScreenScaleFactor);
	resize(m_sSizeInPoint.width, m_sSizeInPoint.height);

	return r;
}

result CCEGLView::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void CCEGLView::onTouchesBegin(int id[], float x[], float y[], int pointerNumber)
{
	result r = E_SUCCESS;
	CCSet set;
	for(int i = 0 ; i < pointerNumber ; i++ ) {
		CCTouch *pTouch = NULL;
		r = s_mapTouches.GetValue(id[i], pTouch);
		if (E_OBJ_NOT_FOUND == r && NULL == pTouch)
		{
			pTouch = new CCTouch();
			pTouch->SetTouchInfo(0, (x[i] - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
					             (y[i] - m_rcViewPort.origin.y) / m_fScreenScaleFactor, id[i]);
			s_mapTouches.Add(id[i], pTouch);
			set.addObject(pTouch);
			m_pDelegate->touchesBegan(&set, NULL);
		}
		else
		{
			CCLOG("Beginnig touches with id: %d error", id[i]);
		}
	}
}

void CCEGLView::onTouchesMove(int id[], float x[], float y[], int pointerNumber)
{
	result r = E_SUCCESS;
	CCSet set;
	for(int i = 0 ; i < pointerNumber ; i++ ) {
		CCLOG("Moving touches with id: %d, x=%f, y=%f", id[i], x[i], y[i]);
		CCTouch *pTouch = NULL;
		r = s_mapTouches.GetValue(id[i], pTouch);

		if (E_SUCCESS == r && pTouch != NULL)
		{
			pTouch->SetTouchInfo(0, (x[i] - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
								(y[i] - m_rcViewPort.origin.y) / m_fScreenScaleFactor, id[i]);
			set.addObject(pTouch);
		}
		else
		{
			// It is error, should return.
			CCLOG("Moving touches with id: %d error", id[i]);
			return;
		}
	}

	m_pDelegate->touchesMoved(&set, NULL);
}

void CCEGLView::onTouchesEnd(int id[], float x[], float y[], int pointerNumber)
{
	result r = E_SUCCESS;
	CCSet set;
	for(int i = 0 ; i < pointerNumber ; i++ ) {
		CCTouch *pTouch = NULL;
		r = s_mapTouches.GetValue(id[i], pTouch);
		if (E_SUCCESS == r && pTouch != NULL)
		{
			pTouch->SetTouchInfo(0, (x[i] - m_rcViewPort.origin.x) / m_fScreenScaleFactor,
		                        (y[i] - m_rcViewPort.origin.y) / m_fScreenScaleFactor, id[i]);
			set.addObject(pTouch);
			s_mapTouches.Remove(id[i]);
			pTouch->release();
			CCLOG("Ending touches with id: %d, x=%f, y=%f, retain count = %d", id[i], x[i], y[i], pTouch->retainCount());
		}
	}

	m_pDelegate->touchesEnded(&set, NULL);
}

void CCEGLView::onTouchEvent(const Control& source, TouchStatus status)
{
	IList *pList = null;
    do
    {
        CC_BREAK_IF(!m_pDelegate);
        int i = 0;
    	Touch touch;
    	pList = touch.GetTouchInfoListN(source);

    	CC_BREAK_IF(pList == NULL);

       	int pointerNumber = pList->GetCount();

        CC_BREAK_IF(pointerNumber <= 0);

    	int id[30] = {0};
    	float x[30] = {0};
    	float y[30] = {0};

    	for (i = 0; i < pointerNumber; i++) {
    		TouchInfo *pTouchInfo = static_cast<TouchInfo *>(pList->GetAt(i));
            id[i] = (int)pTouchInfo->id;
            float tmpX = (float)pTouchInfo->position.x;
            float tmpY = (float)pTouchInfo->position.y;
        	if (!m_bNotHVGA)
        	{
        		x[i] = tmpX * 2 / 3;
        		y[i] = tmpY * 2 / 3;
        	}
        	else
        	{
				x[i] = tmpX;
				y[i] = tmpY;
        	}
        }
    	if (TOUCH_PRESSED == status)
    	{
    		onTouchesBegin(id, x, y, pointerNumber);
    	}
    	else if (TOUCH_MOVED == status)
    	{
    		onTouchesMove(id, x, y, pointerNumber);
    	}
    	else if (TOUCH_RELEASED == status)
    	{
    		onTouchesEnd(id, x, y, pointerNumber);
    	}

    } while (0);

    if (pList != null)
    {
   		pList->RemoveAll(true);
    	delete pList;
    }
}

// touch event
void CCEGLView::OnTouchIndicated(const Control& source,
	const Point& startPosition, const Point& currentPoint)
{

}

void CCEGLView::OnTouchPressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{
	int id = (int)touchInfo.GetPointId();
    float x = (float)touchInfo.GetCurrentPosition().x;
    float y = (float)touchInfo.GetCurrentPosition().y;
    CCLOG("OnTouchPressed id = %d,x = %f,y = %f, count = %d", id, x, y, s_mapTouches.GetCount());
	if (!m_bNotHVGA)
	{
		x = x * 2 / 3;
		y = y * 2 / 3;
	}

	onTouchesBegin(&id, &x, &y, 1);
}

void CCEGLView::OnTouchLongPressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{

}


void CCEGLView::OnTouchReleased(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{
	int id = (int)touchInfo.GetPointId();
    float x = (float)touchInfo.GetCurrentPosition().x;
    float y = (float)touchInfo.GetCurrentPosition().y;
	if (!m_bNotHVGA)
	{
		x = x * 2 / 3;
		y = y * 2 / 3;
	}

	onTouchesEnd(&id, &x, &y, 1);
	CCLOG("OnTouchReleased id = %d,x = %f,y = %f", id, x, y);
}


void CCEGLView::OnTouchMoved(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{
	onTouchEvent(source, TOUCH_MOVED);
}


void CCEGLView::OnTouchDoublePressed(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{
	CCLOG("double pressed..");
	OnTouchPressed(source, currentPosition, touchInfo);
}


void CCEGLView::OnTouchFocusIn(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{

}


void CCEGLView::OnTouchFocusOut(const Control& source,
	const Point& currentPosition, const TouchEventInfo & touchInfo)
{

}

result CCEGLView::OnDraw(void)
{
	result r = E_SUCCESS;
	CCDirector * pDirector = CCDirector::sharedDirector();
	pDirector->drawScene();
	return r;
}

// Implement an ITextEventListener
void CCEGLView::OnTextValueChanged(const Control& source)
{
	// clear textinput text
	std::string strOldText = CCIMEDispatcher::sharedDispatcher()->getContentText();

	for (int i = 0; i < strOldText.length(); i++)
	{
		CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
	}

	String str = m_pKeypad->GetText();
	if (str.GetLength() <= 0)
	{
		CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
	}
	else
	{
		Utf8Encoding utf8;
		ByteBuffer* pBuffer = utf8.GetBytesN(str);
		if (pBuffer != null)
		{
			const char* pszText = (const char*)pBuffer->GetPointer();
			if (pszText != NULL)
			{
				int len = strlen(pszText);
				if (pszText[len-1] != '\n')
				{
					std::string strText = pszText;
					strText.append("\n");
					CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(strText.c_str(), strText.length());
				}
			}
			delete pBuffer;
		}
	}
}

void CCEGLView::OnTextValueChangeCanceled(const Control& source)
{
	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    CC_ASSERT(s_pMainWindow);
    return *s_pMainWindow;
}

NS_CC_END;
