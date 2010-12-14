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

#include "CCXCocos2dDefine_bada.h"
#include "CGGeometry.h"

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FSystem.h>


namespace   cocos2d {
class NSSet;
class CCTouch;
class EGLTouchDelegate;

class CCXEGL;

class CCX_DLL CCXEGLView :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::ITouchEventListener,
	public Osp::Base::Runtime::ITimerEventListener
{
public:

    CCXEGLView();
    virtual ~CCXEGLView();

	CGRect  getFrame();
    CGSize  getSize();
    bool    isOpenGLReady();
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();

	int setDeviceOrientation(int eOritation);

	//bada
	bool Create(Osp::App::Application* pApp);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	void OnTimerExpired(Osp::Base::Runtime::Timer& timer);
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
private:

    bool                m_bCaptured;
	bool				m_bOrientationReverted;
	bool				m_bOrientationInitVertical;
    NSSet *             m_pSet;
    CCTouch *           m_pTouch;
    EGLTouchDelegate *  m_pDelegate;

    CCXEGL *            m_pEGL;

	int					m_eInitOrientation;
	Osp::Ui::Orientation  m_nowOrientation;
	// bada
	Osp::Base::Runtime::Timer* m_pTimer;
};

}   // end of namespace   cocos2d

#endif	// end of __CCX_EGLVIEW_WIN32_H__
