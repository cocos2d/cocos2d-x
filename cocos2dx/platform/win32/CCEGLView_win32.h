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

#ifndef __CC_EGLVIEW_WIN32_H__
#define __CC_EGLVIEW_WIN32_H__

#include <Windows.h>

#include "CCCommon.h"
#include "CCGeometry.h"

NS_CC_BEGIN;

class CCSet;
class CCTouch;
class EGLTouchDelegate;

class CCEGL;

class CC_DLL CCEGLView
{
public:

    CCEGLView();
    virtual ~CCEGLView();

    CCSize  getSize();
    bool    isOpenGLReady();
    void    release();
    void    setTouchDelegate(EGLTouchDelegate * pDelegate);
    void    swapBuffers();
    bool    canSetContentScaleFactor();
    void    setContentScaleFactor(float contentScaleFactor);
    
    float getMainScreenScale() { return 1.0f; }

	virtual bool Create(LPCTSTR pTitle, int w, int h);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    int setDeviceOrientation(int eOritation);
    void setViewPortInPoints(float x, float y, float w, float h);
    void setScissorInPoints(float x, float y, float w, float h);

    void setIMEKeyboardState(bool bOpen);

    // win32 platform function
    HWND getHWnd();
    void resize(int width, int height);
    void centerWindow();
    void setScreenScale(float factor);
	typedef void (*LPFN_ACCELEROMETER_KEYHOOK)( UINT message,WPARAM wParam, LPARAM lParam );
	void setAccelerometerKeyHook( LPFN_ACCELEROMETER_KEYHOOK lpfnAccelerometerKeyHook );

    // static function

    /**
    @brief	get the shared main open gl window
    */
    static CCEGLView& sharedOpenGLView();

protected:

private:

    bool                m_bCaptured;
	bool				m_bOrientationReverted;
	bool				m_bOrientationInitVertical;
    CCSet *             m_pSet;
    CCTouch *           m_pTouch;
    EGLTouchDelegate *  m_pDelegate;

    CCEGL *            m_pEGL;

	HWND				m_hWnd;

	int					m_eInitOrientation;
    SIZE                m_tSizeInPoints;
    float               m_fScreenScaleFactor;
    RECT                m_rcViewPort;
	LPFN_ACCELEROMETER_KEYHOOK	m_lpfnAccelerometerKeyHook;
};

NS_CC_END;

#endif	// end of __CC_EGLVIEW_WIN32_H__
