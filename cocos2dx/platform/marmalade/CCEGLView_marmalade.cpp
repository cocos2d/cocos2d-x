/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck

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

#include "IwGL.h"

#include "CCApplication.h"
#include "CCDirector.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#include "CCKeypadDispatcher.h"
#include "CCIMEDispatcher.h"
#include "ccMacros.h"

#include <stdlib.h>
#include <s3eOSReadString.h>

NS_CC_BEGIN;

CCEGLView* CCEGLView::m_pInstance = 0 ;


CCEGLView::CCEGLView()
: m_pDelegate(NULL)
, m_fScreenScaleFactor(1.0)
, m_bNotHVGA(false)
, m_bCaptured(false)
, m_bAccelState(false)
, m_Key(s3eKeyFirst)
{
	IW_CALLSTACK("CCEGLView::CCEGLView");
	

	IwGLInit();

	m_sSizeInPixel.width = IwGLGetInt(IW_GL_WIDTH);
	m_sSizeInPixel.height = IwGLGetInt(IW_GL_HEIGHT);

    m_pSet      = new CCSet;
	m_pTouch    = new CCTouch;

    // Determine if the device supports multi-touch
    m_isMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
    
	// For multi-touch devices we handle touch and motion events using different callbacks
    if (m_isMultiTouch)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &MultiTouchEventHandler, this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &MultiMotionEventHandler, this);
        
        for (int i = 0; i < S3E_POINTER_TOUCH_MAX; i++) {
            touchSet[i] = NULL;
        }
    }
    else
    {        
        // Register pointer touch button event handler
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, &TouchEventHandler, this);
        
        // Register pointer motion button event handler
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, &MotionEventHandler, this);
    }
    
    // Register keyboard event handler
//	s3eKeyboardRegister(S3E_KEYBOARD_KEY_EVENT, &KeyEventHandler, this);
//	s3eKeyboardRegister(S3E_KEYBOARD_CHAR_EVENT, &CharEventHandler, this);
}

void CCEGLView::setFrameWidthAndHeight(int width, int height)
{
	m_sSizeInPixel.width = width;
	m_sSizeInPixel.height = height;
}
void CCEGLView::create(int width, int height)
{
	if (width == 0 || height == 0)
	{
		return;
	}
		
	m_sSizeInPoint.width = width;
	m_sSizeInPoint.height = height;
		
	// calculate the factor and the rect of viewport	
	m_fScreenScaleFactor =  MIN((float)m_sSizeInPixel.width / m_sSizeInPoint.width, 
								(float)m_sSizeInPixel.height / m_sSizeInPoint.height);
	int viewPortW = (int)(m_sSizeInPoint.width * m_fScreenScaleFactor);
	int viewPortH = (int)(m_sSizeInPoint.height * m_fScreenScaleFactor);
	m_rcViewPort.origin.x = (m_sSizeInPixel.width - viewPortW) / 2;
	m_rcViewPort.origin.y = (m_sSizeInPixel.height - viewPortH) / 2;
	m_rcViewPort.size.width = viewPortW;
	m_rcViewPort.size.height = viewPortH;
		
	m_bNotHVGA = true;
		
}
CCEGLView::~CCEGLView()
{
	IW_CALLSTACK("CCEGLView::~CCEGLView");

	CC_SAFE_DELETE(m_pDelegate);
    CC_SAFE_DELETE(m_pSet);
	CC_SAFE_DELETE(m_pTouch);

}
	
CCSize  CCEGLView::getSize()
{
	if (m_bNotHVGA)
	{
		CCSize size(m_sSizeInPoint.width, m_sSizeInPoint.height);
		return size;
	}
	else
	{
		CCSize size(m_sSizeInPixel.width, m_sSizeInPixel.height);
		return size;
	}
		
}

void CCEGLView::setTouch(void* systemData)
{
	s3ePointerEvent* event =(s3ePointerEvent*)systemData;
	
	switch (event->m_Pressed)
	{
	case S3E_POINTER_STATE_DOWN :
		m_bCaptured = true;
		m_pTouch->SetTouchInfo(0, (float)event->m_x, (float)event->m_y);
		m_pSet->addObject(m_pTouch);
		m_pDelegate->touchesBegan(m_pSet, NULL);
		break;

	case S3E_POINTER_STATE_UP :
		if (m_bCaptured)
		{
			m_pTouch->SetTouchInfo(0, (float)event->m_x, (float)event->m_y);
			m_pDelegate->touchesEnded(m_pSet, NULL);
			m_pSet->removeObject(m_pTouch);
			m_bCaptured = false;
		}
		break;
	}
}

void CCEGLView::setMotionTouch(void* systemData)
{
		s3ePointerMotionEvent* event =(s3ePointerMotionEvent*)systemData;
		if (m_bCaptured)
		{
            m_pTouch->SetTouchInfo(0, (float)event->m_x, (float)event->m_y);
            m_pDelegate->touchesMoved(m_pSet, NULL);

		}
}

void CCEGLView::setMultiTouch(void* systemData)
{
	s3ePointerTouchEvent* event =(s3ePointerTouchEvent*)systemData;
	
    if (touchSet[event->m_TouchID] == NULL) {
        m_pTouch = new CCTouch;
        touchSet[event->m_TouchID] = m_pTouch;
    }
    else {
        m_pTouch = touchSet[event->m_TouchID];
    }
    
	switch (event->m_Pressed)
	{
        case S3E_POINTER_STATE_DOWN :
            m_pTouch->SetTouchInfo(0, (float)event->m_x, (float)event->m_y);
            m_pSet->addObject(m_pTouch);
            m_pDelegate->touchesBegan(m_pSet, NULL);
            break;
            
        case S3E_POINTER_STATE_UP :
            {
                m_pTouch->SetTouchInfo(0, (float)event->m_x, (float)event->m_y);
                m_pDelegate->touchesEnded(m_pSet, NULL);
                m_pSet->removeObject(m_pTouch);
                touchSet[event->m_TouchID] = NULL;
            }
            break;
	}
}

void CCEGLView::setMultiMotionTouch(void* systemData)
{
    s3ePointerTouchMotionEvent* event =(s3ePointerTouchMotionEvent*)systemData;
     m_pTouch = touchSet[event->m_TouchID];
    if (m_pTouch)
    {
        m_pTouch->SetTouchInfo((int)event, (float)event->m_x, (float)event->m_y);
        m_pDelegate->touchesMoved(m_pSet, NULL);
        
    }
}

CCTouch* CCEGLView::findTouch(int id) 
{
    CCSetIterator iter;
	for (iter = m_pSet->begin(); iter != m_pSet->end(); ++iter)
	{
        CCTouch *touch = (CCTouch*)*iter;
                
		if(touch->view() == id)
            return touch;
	}
    
    return NULL;
}


void CCEGLView::setKeyTouch(void* systemData)
{
// 	s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
// 	if (event->m_Pressed)
// 	{
// 		if (event->m_Key!=m_Key)
// 		{
// 			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
// 		}
// 		else
// 		{
// 			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
// 
// 		}
// 		m_Key =event->m_Key;
// 	}
}

void CCEGLView::setCharTouch( void* systemData )
{
//     s3eKeyboardCharEvent* event = (s3eKeyboardCharEvent*)systemData;
// 	s3eWChar c = event->m_Char ;
// 	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&c, 1);
}

bool CCEGLView::isOpenGLReady()
{
    return (IwGLIsInitialised() && m_sSizeInPixel.width != 0 && m_sSizeInPixel.height !=0);
}

void CCEGLView::release()
{
	IW_CALLSTACK("CCEGLView::release");

    if (m_isMultiTouch)
    {
        s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, &MultiTouchEventHandler);
        s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &MultiMotionEventHandler);
    }
    else
    {
        s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, &TouchEventHandler);
        s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, &MotionEventHandler);
    }
    
//	s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, &KeyEventHandler);
//	s3eKeyboardUnRegister(S3E_KEYBOARD_KEY_EVENT, &CharEventHandler);

	if (IwGLIsInitialised())
  		IwGLTerminate();

	 s3eDeviceRequestQuit() ;

	 delete this ;
}

void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
{
	m_pDelegate = pDelegate;
}

EGLTouchDelegate* CCEGLView::getDelegate(void)
{
	return m_pDelegate;
}

void CCEGLView::swapBuffers()
{
	IW_CALLSTACK("CCEGLView::swapBuffers(");
	IwGLSwapBuffers();
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

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
	if(bOpen && s3eOSReadStringAvailable() == S3E_TRUE) {
		const char* inputText = s3eOSReadStringUTF8("") ;
		if( inputText!=0 ) {
			CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(inputText, strlen(inputText));
		}
	}
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
	if( !m_pInstance ) {
		m_pInstance = new CCEGLView() ;
	}
	return *m_pInstance;
}
	
float CCEGLView::getScreenScaleFactor()
{
	return m_fScreenScaleFactor;
}
	
CCRect CCEGLView::getViewPort()
{
	if (m_bNotHVGA)
	{
		return m_rcViewPort;
	}
	else
	{
		CCRect rect(0, 0, 0, 0);
		return rect;
	}
}


NS_CC_END;
