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

#include "TG3.h"
#include "ssBackLightControl.h"

#include "EGL/egl.h"
#include "GLES/gl.h"

#include "CCSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

#include "TCOM_Sensors_Interface.h"
#include "CCAccelerometer.h"
#include "CCKeypadDispatcher.h"

#include "CCApplication.h"
#include "ccMacros.h"

namespace cocos2d {

#define MAX_TOUCHES         4
static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };

class CCEGL
{
public:
	~CCEGL() 
	{
		if (EGL_NO_DISPLAY == m_eglDisplay)
		{
			return;
		}

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

	static CCEGL * create(TWindow * pWindow)
	{
		CCEGL * pEGL = new CCEGL;
		Boolean bSuccess = FALSE;
		do 
		{
			CC_BREAK_IF(! pEGL);

			TUChar szError[] = {'E','R','R','O','R',0};
			TUChar szEglInitFailed[] = {'e','g','l','I','n','i','t','i','a','l','i','z','e',' ','f','a','i','l','e','d',0};
			TUChar szCreateContextFailed[] = {'e','g','l','C','r','e','a','t','e','C','o','n','t','e','x','t',' ','f','a','i','l','e','d',0};
			TUChar szEglCreateWindowSurfaceFailed[] = {'e','g','l','C','r','e','a','t','e','W','i','n','d','o','w','S','u','r','f','a','c','e',' ','f','a','i','l','e','d',0};
			TUChar szEglMakeCurrentFailed[] = {'e','g','l','M','a','k','e','C','u','r','r','e','n','t',' ','f','a','i','l','e','d',0};

			pEGL->m_eglNativeWindow = pWindow;

			EGLDisplay eglDisplay;
			CC_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglNativeDisplay)));

			EGLint nMajor, nMinor;
			EGLBoolean bEglRet;
			
			bEglRet = eglInitialize(eglDisplay, &nMajor, &nMinor);
			if ( EGL_FALSE == bEglRet || 1 != nMajor )
			{
				TApplication::GetCurrentApplication()->MessageBox(szEglInitFailed, szError, WMB_OK);
				break;
			}

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
			CC_BREAK_IF( EGL_FALSE == eglChooseConfig(eglDisplay, aConfigAttribs, &eglConfig, 1, &iConfigs) ||
						  (iConfigs != 1) );

			EGLContext eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, NULL);
			if (EGL_NO_CONTEXT == eglContext)
			{
				TApplication::GetCurrentApplication()->MessageBox(szCreateContextFailed, szError, WMB_OK);
				break;
			}

			EGLSurface eglSurface;
			eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, pEGL->m_eglNativeWindow, NULL);
			if (EGL_NO_SURFACE == eglSurface)
			{
				TApplication::GetCurrentApplication()->MessageBox(szEglCreateWindowSurfaceFailed, szError, WMB_OK);
				break;
			}

			bEglRet = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
			if (EGL_FALSE == bEglRet)
			{
				TApplication::GetCurrentApplication()->MessageBox(szEglMakeCurrentFailed, szError, WMB_OK);
				break;
			}

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
		// 		if (! m_eglWnd || EGL_NO_DISPLAY == m_eglDisplay)
		// 		{
		// 			return;
		// 		}
		// 
		// 		// release old surface
		// 		if (EGL_NO_SURFACE != m_eglSurface)
		// 		{
		// 			eglDestroySurface(m_eglDisplay, m_eglSurface);
		// 			m_eglSurface = EGL_NO_SURFACE;
		// 		}
		// 
		// 		// create new surface and make current
		// 		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_eglWnd, NULL);
		// 		eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
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

static CCEGLView* s_pMainWindow = NULL;

CCEGLView::CCEGLView(TApplication * pApp)
: TWindow(pApp)
, m_pDelegate(NULL)
, m_pEGL(NULL)
, m_fScreenScaleFactor(1.0f)
{
}

CCEGLView::~CCEGLView()
{
    CC_SAFE_DELETE(m_pDelegate);
    CC_SAFE_DELETE(m_pEGL);
}

Boolean CCEGLView::Create(int nWidthInPoints, int nHeightInPoints)
{
    // record the window size in points
    m_tSizeInPoints.SetWidth(nWidthInPoints);
    m_tSizeInPoints.SetHeight(nHeightInPoints);

    // get the screen size
    TApplication* pApp = TApplication::GetCurrentApplication();
    Int32 nWidth  = pApp->GetScreenWidth();
    Int32 nHeight = pApp->GetScreenHeight();

    // calculate the factor and the rect of viewport
    m_fScreenScaleFactor =  MIN((float)nWidth / nWidthInPoints, (float)nHeight / nHeightInPoints);
    int viewPortW = (int)(m_tSizeInPoints.Width() * m_fScreenScaleFactor);
    int viewPortH = (int)(m_tSizeInPoints.Height() * m_fScreenScaleFactor);
    m_rcViewPort.SetX((nWidth - viewPortW) / 2);
    m_rcViewPort.SetY((nHeight - viewPortH) / 2);
    m_rcViewPort.SetWidth(viewPortW);
    m_rcViewPort.SetHeight(viewPortH);

    Boolean bRet = TWindow::Create(&TRectangle(0, 0, nWidth, nHeight));

    if (bRet)
    {
        s_pMainWindow = this;
    }

    return bRet;
}

Boolean CCEGLView::AfterCreate(void)
{
    return (m_pEGL = CCEGL::create(this)) ? TRUE : FALSE;
}

Boolean CCEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_WinInit:
        CfgRegisterScreenSwitchNotify(GetWindowHwndId(), 0);
        bHandled = TRUE;
        break;

    case EVENT_WinPaint:
        if (CfgGetScreenStatus())
        {
            // draw 
            CCDirector::sharedDirector()->mainLoop();
        }
        bHandled = TRUE;
        break;

    case EVENT_PenDown:
        bHandled = OnPenDown(pEvent, 0);
        break;

    case EVENT_PenMove:
        bHandled = OnPenMove(pEvent);
        break;

    case EVENT_PenUp:
        bHandled = OnPenUp(pEvent, 0);
        break;

    case EVENT_MultiTouchDown:
        bHandled = OnPenDown(pEvent, pEvent->lParam3);
        break;

    case EVENT_MultiTouchUp:
        bHandled = OnPenUp(pEvent, pEvent->lParam3);
        break;

    case EVENT_KeyCommand:
        {
            if (pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_UP ||
                pEvent->sParam1 == SYS_KEY_SOFTKEY_RIGHT_LONG)
            {
                bHandled = CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
            }
            else if (pEvent->sParam1 == KEY_COMMAND_MAINMENU)
            {
                bHandled = CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
            }
        }
        break;

    case MESSAGE_SENSORS_DATA:
        {
            TG3SensorsDataType	data;

            if (Sys_GetMessageBody((MESSAGE_t *)pEvent, &data, sizeof(TG3SensorsDataType)) == sizeof(TG3SensorsDataType) &&
                TG3_SENSOR_TYPE_ACCELEROMETER == data.sensorMask)
            {
                // convert the data to iphone format
                CCAcceleration AccValue;
                AccValue.x = -(data.acceleration.x / TG3_GRAVITY_EARTH);
                AccValue.y = -(data.acceleration.y / TG3_GRAVITY_EARTH);
                AccValue.z = -(data.acceleration.z / TG3_GRAVITY_EARTH);
                AccValue.timestamp = (double) TimGetTicks() / 100;

                // call delegates' didAccelerate function
                CCAccelerometer::sharedAccelerometer()->didAccelerate(&AccValue);
                bHandled = TRUE;
            }
        }
        break;

    case EVENT_WinClose:
        CfgUnRegisterScreenSwitchNotify(GetWindowHwndId(), 0);
        // Stop the application since the main form has been closed
        pApp->SendStopEvent();
        break;

    case EVENT_ScreenSwitchNotify:
        {
            CCApplication::sharedApplication().switchNotify(pEvent->sParam1);
            break;
        }

    }
//     {
//         char szType[32];
//         sprintf(szType, "%d", pEvent->eType);
//         const char * pszType = szType;
//         switch (pEvent->eType)
//         {
//         case EVENT_ScreenSwitchNotify:
//             pszType = "EVENT_ScreenSwitchNotify";
//             break;
// 
//         case EVENT_GlesUpdateNotify:
//             pszType = "EVENT_GlesUpdateNotify";
//             break;
// 
//         case EVENT_WinPaint:
//             pszType = "EVENT_GlesUpdateNotify";
//             break;
//         }
//         if (pszType)
//         {
//             char szMsg[256];
//             sprintf(szMsg, "%d: %s: %d \r\n", TimGetTicks(), pszType, pEvent->sParam1);
// #if defined (_TRANZDA_VM_)
// #define LOG_FILE_NAME "d:/Work7/NEWPLUS/TDA_DATA/UserData/mesagelog.txt"
// #else
// #define LOG_FILE_NAME "/NEWPLUS/TDA_DATA/UserData/mesagelog.txt"
// #endif
//             FILE * pf = fopen(LOG_FILE_NAME, "a+");
//             fwrite(szMsg, 1, strlen(szMsg), pf);
//             fclose(pf);
//         }
//     }

    if (! bHandled)
    {
        return TWindow::EventHandler(pApp, pEvent);
    }
    return bHandled;
}

Boolean CCEGLView::OnPenDown(EventType* pEvent, Int32 nIndex)
{
    if (m_pDelegate && nIndex < MAX_TOUCHES)
    {
        CCTouch* pTouch = s_pTouches[nIndex];
        if (!pTouch)
        {
            pTouch = new CCTouch;
        }

        pTouch->SetTouchInfo(0, (float)(pEvent->sParam1 - m_rcViewPort.X()) / m_fScreenScaleFactor,
                             (float)(pEvent->sParam2 - m_rcViewPort.Y()) / m_fScreenScaleFactor);
        s_pTouches[nIndex] = pTouch;
        CCSet set;
        set.addObject(pTouch);
        m_pDelegate->touchesBegan(&set, NULL);
    }

    return FALSE;
}

Boolean CCEGLView::OnPenUp(EventType* pEvent, Int32 nIndex)
{
    if (m_pDelegate && nIndex < MAX_TOUCHES)
    {
        CCTouch* pTouch = s_pTouches[nIndex];
        if (pTouch)
        {
            CCSet set;
            pTouch->SetTouchInfo(0, (float)(pEvent->sParam1 - m_rcViewPort.X()) / m_fScreenScaleFactor,
                                 (float)(pEvent->sParam2 - m_rcViewPort.Y()) / m_fScreenScaleFactor);
            set.addObject(pTouch);
            m_pDelegate->touchesEnded(&set, NULL);

            pTouch->release();
            for (Int32 i = nIndex; i < MAX_TOUCHES; ++i)
            {
                if (i != (MAX_TOUCHES - 1))
                {
                    s_pTouches[i] = s_pTouches[i + 1];
                }
                else
                {
                    s_pTouches[i] = NULL;
                }
            }
        }
    }

    return FALSE;
}

Boolean CCEGLView::OnPenMove(EventType* pEvent)
{
    do 
    {
        CC_BREAK_IF(!m_pDelegate);

        Int32 nCount = EvtGetPenMultiPointCount(pEvent);
        CC_BREAK_IF(nCount <= 0 || nCount > MAX_TOUCHES);

        CCSet set;
        Int32 nPosX, nPosY;
        for (Int32 i = 0; i < nCount; ++i)
        {
            CCTouch* pTouch = s_pTouches[i];
            CC_BREAK_IF(!pTouch);

            EvtGetPenMultiPointXY(pEvent, i, &nPosX, &nPosY);
            pTouch->SetTouchInfo(0, (float) (nPosX - m_rcViewPort.X()) / m_fScreenScaleFactor,
                                 (float) (nPosY - m_rcViewPort.Y()) / m_fScreenScaleFactor);
            set.addObject(pTouch);
        }

        m_pDelegate->touchesMoved(&set, NULL);
    } while (0);

    return FALSE;
}

CCSize CCEGLView::getSize()
{
    return CCSize((float)m_tSizeInPoints.Width(), (float)m_tSizeInPoints.Height());
}

CCRect CCEGLView::getFrame()
{
	TRectangle rc;
	GetClientBounds(&rc);
	return (CCRect((float)rc.X(), (float)rc.Y(), (float)rc.Width(), (float)rc.Height()));
}

bool CCEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCEGLView::release()
{
    CloseWindow();
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
	// if it supports scaling content, set it
    m_fScreenScaleFactor = contentScaleFactor;
}

void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
{
    if (m_pEGL)
    {
        float factor = m_fScreenScaleFactor / CC_CONTENT_SCALE_FACTOR();
        glViewport((GLint)(x * factor) + m_rcViewPort.X(),
            (GLint)(y * factor) + m_rcViewPort.Y(),
            (GLint)(w * factor),
            (GLint)(h * factor));
    }
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    CC_ASSERT(s_pMainWindow);
    return *s_pMainWindow;
}

}       // end of namespace cocos2d
