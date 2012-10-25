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

#ifndef __CC_EGLVIEW_MARMALADE_H__
#define __CC_EGLVIEW_MARMALADE_H__

#include "CCGeometry.h"
#include "CCEGLViewProtocol.h"					// MH: Added because CCEGLView should be derived from CCEGLViewProtocol
#include "s3eKeyboard.h"
#include "s3ePointer.h"
#include "IwUtil.h"

NS_CC_BEGIN

class CC_DLL CCEGLView : public CCEGLViewProtocol		// MH: Added because CCEGLView should be derived from CCEGLViewProtocol
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setIMEKeyboardState(bool bOpen);

	// static function
	/**
	 @brief	get the shared main open gl window
	 */
	static CCEGLView* sharedOpenGLView();			// MH: Cocos2D now uses pointer instead of ref

private:
	bool				m_bAccelState;
	bool				m_bCaptured;
	s3eKey				m_Key;
    bool				m_isMultiTouch;
	
	static CCEGLView*	m_pInstance ;
	
	void	setTouch(void* systemData);
	void	setMotionTouch(void* systemData);
    void	setMultiTouch(void* systemData);
	void	setMultiMotionTouch(void* systemData);
	void	setKeyTouch(void* systemData);
	void	setCharTouch(void* systemData);

	static int32 TouchEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setTouch(systemData);
		return 0;
	}

	static int32 MotionEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setMotionTouch(systemData);
		return 0;
	}
	
    static int32 MultiTouchEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setMultiTouch(systemData);
		return 0;
	}
	
    static int32 MultiMotionEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setMultiMotionTouch(systemData);
		return 0;
	}

	static int32 KeyEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setKeyTouch(systemData);
		return 0;
	}

	static int32 CharEventHandler(void* systemData, void* userData)
	{
		((CCEGLView*)userData)->setCharTouch(systemData);
		return 0;
	}
};
	
NS_CC_END

#endif	// end of __CC_EGLVIEW_MARMALADE_H__
