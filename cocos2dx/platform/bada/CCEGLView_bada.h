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

#ifndef __CCX_EGLVIEW_BADA_H__
#define __CCX_EGLVIEW_BADA_H__

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FSystem.h>
#include "CCGeometry.h"
#include <GLES/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>

NS_CC_BEGIN;

class CCSet;
class CCTouch;
class EGLTouchDelegate;

class CCEGL;

class CC_DLL CCEGLView
	:public Osp::Ui::Controls::Form
	,public Osp::Ui::ITouchEventListener
	,public Osp::Ui::ITextEventListener
{
public:

    CCEGLView();
    virtual ~CCEGLView();

	CCRect  getFrame();
    CCSize  getSize();
    bool    isOpenGLReady();
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor);

	int setDeviceOrientation(Osp::Ui::Orientation eOritation);
    void setViewPortInPoints(float x, float y, float w, float h);
    void setScissorInPoints(float x, float y, float w, float h);

    void setIMEKeyboardState(bool bOpen);
	// static function
	/**
	@brief	get the shared main open gl window
	*/
	static CCEGLView& sharedOpenGLView();

	/*
	 * param
	 *   width[in]: resource width
	 *   height[in]: resource height
	 */
	bool Create(Osp::App::Application* pApp, int width, int height);
	void resize(int width, int height);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	void onTouchesBegin(int id[], float x[], float y[], int pointerNumber);
	void onTouchesMove(int id[], float x[], float y[], int pointerNumber);
	void onTouchesEnd(int id[], float x[], float y[], int pointerNumber);
	void onTouchEvent(const Osp::Ui::Control& source, Osp::Ui::TouchStatus status);

	// touch event
	virtual void OnTouchIndicated(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& startPosition, const Osp::Graphics::Point& currentPoint);

	virtual void OnTouchPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchLongPressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchReleased(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchMoved(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchDoublePressed(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchFocusIn(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual void OnTouchFocusOut(const Osp::Ui::Control& source,
		const Osp::Graphics::Point& currentPosition, const Osp::Ui::TouchEventInfo & touchInfo);

	virtual result OnDraw(void);

    virtual void OnTextValueChanged(const Osp::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Osp::Ui::Control& source);

#ifdef CC_BADA_2_0
	// pointer to OES methods from EGL
	static PFNGLGENERATEMIPMAPOESPROC         glGenerateMipmapOES;
	static PFNGLGENFRAMEBUFFERSOESPROC        glGenFramebuffersOES;
	static PFNGLBINDFRAMEBUFFEROESPROC		  glBindFramebufferOES;
	static PFNGLFRAMEBUFFERTEXTURE2DOESPROC   glFramebufferTexture2DOES;
	static PFNGLDELETEFRAMEBUFFERSOESPROC     glDeleteFramebuffersOES;
	static PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glCheckFramebufferStatusOES;
#endif

private:
	Osp::Ui::Controls::Keypad *m_pKeypad;

	CCSize m_sSizeInPixel;
	CCSize m_sSizeInPoint;
	CCRect m_rcViewPort;
	bool   m_bNotHVGA;

	EGLTouchDelegate *m_pDelegate;
	float  m_fScreenScaleFactor;

    bool                m_bCaptured;

    CCSet *             m_pSet;
    CCTouch *           m_pTouch;
    CCEGL *            m_pEGL;

	int					m_eInitOrientation;

	Osp::Ui::Orientation  m_nowOrientation;
};

NS_CC_END;

#endif	// end of __CCX_EGLVIEW_WIN32_H__
