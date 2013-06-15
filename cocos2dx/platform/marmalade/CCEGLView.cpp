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

NS_CC_BEGIN

CCEGLView* CCEGLView::_instance = 0;


CCEGLView::CCEGLView()
: _captured(false)
, _accelState(false)
, _key(s3eKeyFirst)
{
	IW_CALLSTACK("CCEGLView::CCEGLView");
	
	IwGLInit();

	setFrameSize((float)IwGLGetInt(IW_GL_WIDTH), (float)IwGLGetInt(IW_GL_HEIGHT));

    // Determine if the device supports multi-touch
    _isMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
    
	// For multi-touch devices we handle touch and motion events using different callbacks
    if (_isMultiTouch)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, &MultiTouchEventHandler, this);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, &MultiMotionEventHandler, this);
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

CCEGLView::~CCEGLView()
{
	IW_CALLSTACK("CCEGLView::~CCEGLView");
}
	
void CCEGLView::setTouch(void* systemData)
{
	s3ePointerEvent* event =(s3ePointerEvent*)systemData;
    int id = 0;
    float x = (float)event->_x;
    float y = (float)event->_y;
	switch (event->_pressed)
	{
	case S3E_POINTER_STATE_DOWN :
		_captured = true;
        handleTouchesBegin(1, &id, &x, &y);
		break;
	case S3E_POINTER_STATE_UP :
		if (_captured)
		{
			handleTouchesEnd(1, &id, &x, &y);
			_captured = false;
		}
		break;
	}
}

void CCEGLView::setMotionTouch(void* systemData)
{
		s3ePointerMotionEvent* event =(s3ePointerMotionEvent*)systemData;
		if (_captured)
		{
            int id = 0;
            float x = (float)event->_x;
            float y = (float)event->_y;
            handleTouchesMove(1, &id, &x, &y);
		}
}

void CCEGLView::setMultiTouch(void* systemData)
{
	s3ePointerTouchEvent* event =(s3ePointerTouchEvent*)systemData;
    int id = (int)event->_touchID;
    float x = (float)event->_x;
    float y = (float)event->_y;

	switch (event->_pressed)
	{
        case S3E_POINTER_STATE_DOWN:
            {
                handleTouchesBegin(1, &id, &x, &y);
            }
            break;
            
        case S3E_POINTER_STATE_UP:
            {
                handleTouchesEnd(1, &id, &x, &y);
            }
            break;
	}
}

void CCEGLView::setMultiMotionTouch(void* systemData)
{
    s3ePointerTouchMotionEvent* event =(s3ePointerTouchMotionEvent*)systemData;
    int id = (int)event->_touchID;
    float x = (float)event->_x;
    float y = (float)event->_y;
    handleTouchesMove(1, &id, &x, &y);
}


void CCEGLView::setKeyTouch(void* systemData)
{
// 	s3eKeyboardEvent* event = (s3eKeyboardEvent*)systemData;
// 	if (event->_pressed)
// 	{
// 		if (event->_key!=_key)
// 		{
// 			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeMenuClicked);
// 		}
// 		else
// 		{
// 			CCKeypadDispatcher::sharedDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
// 
// 		}
// 		_key =event->_key;
// 	}
}

void CCEGLView::setCharTouch( void* systemData )
{
//     s3eKeyboardCharEvent* event = (s3eKeyboardCharEvent*)systemData;
// 	s3eWChar c = event->_char ;
// 	CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&c, 1);
}

bool CCEGLView::isOpenGLReady()
{
    return (IwGLIsInitialised());
}

void CCEGLView::end()
{
	IW_CALLSTACK("CCEGLView::end");

    if (_isMultiTouch)
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

	 delete this;
}

void CCEGLView::swapBuffers()
{
	IW_CALLSTACK("CCEGLView::swapBuffers(");
	IwGLSwapBuffers();
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

CCEGLView* CCEGLView::sharedOpenGLView()		// MH: Cocos2D now uses pointer instead of ref
{
	if( !_instance ) {
		_instance = new CCEGLView() ;
	}
	return _instance;							// MH: Cocos2D now uses pointer instead of ref
}

NS_CC_END
