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

#include "CCXCocos2dDefine.h"
#include "NSSet.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"

#include "TCOM_Sensors_Interface.h"
#include "CCXUIAccelerometer.h"
#include "CCKeypadDispatcher.h"

#include "CCXApplication.h"

namespace cocos2d {

#define MAX_TOUCHES         4
static CCTouch *s_pTouches[MAX_TOUCHES] = { NULL };

class CCXEGL
{
public:
	~CCXEGL() 
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

	static CCXEGL * create(TWindow * pWindow)
	{
		CCXEGL * pEGL = new CCXEGL;
		Boolean bSuccess = FALSE;
		do 
		{
			CCX_BREAK_IF(! pEGL);

			TUChar szError[] = {'E','R','R','O','R',0};
			TUChar szEglInitFailed[] = {'e','g','l','I','n','i','t','i','a','l','i','z','e',' ','f','a','i','l','e','d',0};
			TUChar szCreateContextFailed[] = {'e','g','l','C','r','e','a','t','e','C','o','n','t','e','x','t',' ','f','a','i','l','e','d',0};
			TUChar szEglCreateWindowSurfaceFailed[] = {'e','g','l','C','r','e','a','t','e','W','i','n','d','o','w','S','u','r','f','a','c','e',' ','f','a','i','l','e','d',0};
			TUChar szEglMakeCurrentFailed[] = {'e','g','l','M','a','k','e','C','u','r','r','e','n','t',' ','f','a','i','l','e','d',0};

			pEGL->m_eglNativeWindow = pWindow;

			EGLDisplay eglDisplay;
			CCX_BREAK_IF(EGL_NO_DISPLAY == (eglDisplay = eglGetDisplay(pEGL->m_eglNativeDisplay)));

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
			CCX_BREAK_IF( EGL_FALSE == eglChooseConfig(eglDisplay, aConfigAttribs, &eglConfig, 1, &iConfigs) ||
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
			CCX_SAFE_DELETE(pEGL);   
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

CCXEGLView::CCXEGLView(TApplication * pApp)
: TWindow(pApp)
, m_pDelegate(NULL)
, m_pEGL(NULL)
{
}

CCXEGLView::~CCXEGLView()
{
    CCX_SAFE_DELETE(m_pDelegate);
    CCX_SAFE_DELETE(m_pEGL);
}

Boolean CCXEGLView::AfterCreate(void)
{
    return (m_pEGL = CCXEGL::create(this)) ? TRUE : FALSE;
}

Boolean CCXEGLView::EventHandler(TApplication * pApp, EventType * pEvent)
{
    Boolean bHandled = FALSE;

    switch(pEvent->eType)
    {
    case EVENT_WinInit:
        CfgRegisterScreenSwitchNotify(GetWindowHwndId(), 0);
        bHandled = TRUE;
        break;

    case EVENT_WinPaint:
        // draw 
        CCDirector::sharedDirector()->preMainLoop();
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
            else if (pEvent->sParam1 == SYS_KEY_SOFTKEY_LEFT_UP ||
                     pEvent->sParam1 == SYS_KEY_SOFTKEY_LEFT_LONG)
            {
                bHandled == CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
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
                UIAcceleration AccValue;
                AccValue.x = -(data.acceleration.x / TG3_GRAVITY_EARTH);
                AccValue.y = -(data.acceleration.y / TG3_GRAVITY_EARTH);
                AccValue.z = -(data.acceleration.z / TG3_GRAVITY_EARTH);
                AccValue.timestamp = (double) TimGetTicks() / 100;

                // call delegates' didAccelerate function
                UIAccelerometer::sharedAccelerometer()->didAccelerate(&AccValue);
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
        if (! pEvent->sParam1)  // turn off screen
        {
            // CCDirector::sharedDirector()->pause();
            CCXApplication::sharedApplication()->applicationDidEnterBackground();
            CCXApplication::sharedApplication()->StopMainLoop();
        }
        else
        {
            // CCDirector::sharedDirector()->resume();
            CCXApplication::sharedApplication()->applicationWillEnterForeground();
            CCXApplication::sharedApplication()->StartMainLoop();
        }
        break;

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

Boolean CCXEGLView::OnPenDown(EventType* pEvent, Int32 nIndex)
{
    if (m_pDelegate && nIndex < MAX_TOUCHES)
    {
        CCTouch* pTouch = s_pTouches[nIndex];
        if (!pTouch)
        {
            pTouch = new CCTouch;
        }

        pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
        s_pTouches[nIndex] = pTouch;
        NSSet set;
        set.addObject(pTouch);
        m_pDelegate->touchesBegan(&set, NULL);
    }

    return FALSE;
}

Boolean CCXEGLView::OnPenUp(EventType* pEvent, Int32 nIndex)
{
    if (m_pDelegate && nIndex < MAX_TOUCHES)
    {
        CCTouch* pTouch = s_pTouches[nIndex];
        if (pTouch)
        {
            NSSet set;
            pTouch->SetTouchInfo(0, (float)pEvent->sParam1, (float)pEvent->sParam2);
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

Boolean CCXEGLView::OnPenMove(EventType* pEvent)
{
    do 
    {
        CCX_BREAK_IF(!m_pDelegate);

        Int32 nCount = EvtGetPenMultiPointCount(pEvent);
        CCX_BREAK_IF(nCount <= 0 || nCount > MAX_TOUCHES);

        NSSet set;
        Int32 nPosX, nPosY;
        for (Int32 i = 0; i < nCount; ++i)
        {
            CCTouch* pTouch = s_pTouches[i];
            CCX_BREAK_IF(!pTouch);

            EvtGetPenMultiPointXY(pEvent, i, &nPosX, &nPosY);
            pTouch->SetTouchInfo(0, (float) nPosX, (float) nPosY);
            set.addObject(pTouch);
        }

        m_pDelegate->touchesMoved(&set, NULL);
    } while (0);

    return FALSE;
}

CGSize CCXEGLView::getSize()
{
	Coord w, h;
	TWindow::GetWindowExtent(&w, &h);
    return CGSize((float)w, (float)h);
}

CGRect CCXEGLView::getFrame()
{
	TRectangle rc;
	GetClientBounds(&rc);
	return (CGRect((float)rc.X(), (float)rc.Y(), (float)rc.Width(), (float)rc.Height()));
}

bool CCXEGLView::isOpenGLReady()
{
    return (NULL != m_pEGL);
}

void CCXEGLView::release()
{
    CloseWindow();
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

}       // end of namespace cocos2d
