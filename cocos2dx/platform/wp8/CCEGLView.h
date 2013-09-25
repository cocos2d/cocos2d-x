/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#ifndef __CC_EGLVIEW_WINRT_H__
#define __CC_EGLVIEW_WINRT_H__

#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include <agile.h>

#include <wrl/client.h>
#include <d3d11_1.h>
#include "Direct3DBase.h"

#include <agile.h>
#include <DirectXMath.h>
#include "kazmath/mat4.h"

#include "esUtil.h"

NS_CC_BEGIN

class CCEGL;
class CCEGLView;
ref class WP8Keyboard;

ref class WP8Window sealed
{
public:

	WP8Window(Windows::UI::Core::CoreWindow^ parentWindow);

protected:
    void OnOrientationChanged(Platform::Object^ sender);

private:
    Platform::Agile<Windows::UI::Core::CoreWindow> m_window;

};


class CC_DLL CCEGLView : public CCEGLViewProtocol
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);
    kmMat4* getOrientationMatrix() {return &m_orientationMatrix;};
    kmMat4* getReverseOrientationMatrix (){return &m_reverseOrientationMatrix;};

    Windows::Graphics::Display::DisplayOrientations getDeviceOrientation() {return m_orientation;};



    virtual void setIMEKeyboardState(bool bOpen);
	void ShowKeyboard(Windows::Foundation::Rect r);
	void HideKeyboard(Windows::Foundation::Rect r);

    virtual bool Create(Windows::UI::Core::CoreWindow^ window);

	void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerWheelChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
	void OnResuming(Platform::Object^ sender, Platform::Object^ args);
	void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    void OnOrientationChanged();

	Windows::UI::Core::CoreWindow^ getWindow() { return m_window.Get(); };
	
	int Run();

    void resize(int width, int height);
    /* 
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float fZoomFactor);
	float getFrameZoomFactor();
    void centerWindow();

    
    // static function
    /**
    @brief    get the shared main open gl window
    */
	static CCEGLView* sharedOpenGLView();

protected:

private:
	void OnRendering();
	void UpdateForWindowSizeChange();
    void UpdateOrientationMatrix();

	void ValidateDevice();
    Windows::Foundation::Point TransformToOrientation(Windows::Foundation::Point point, bool dipsToPixels);
 	CCPoint GetCCPoint(Windows::UI::Core::PointerEventArgs^ args);
       
    Windows::Foundation::Rect m_windowBounds;
	Windows::Foundation::EventRegistrationToken m_eventToken;
	Windows::Foundation::Point m_lastPoint;

        
    Platform::Agile<Windows::UI::Core::CoreWindow> m_window;
    Windows::Graphics::Display::DisplayOrientations m_orientation;
	Windows::Foundation::Rect m_keyboardRect;

	bool m_lastPointValid;
	bool m_windowClosed;
	bool m_windowVisible;
    kmMat4 m_orientationMatrix;
    kmMat4 m_reverseOrientationMatrix;
    
    bool m_running;
	bool m_initialized;
    bool m_bSupportTouch;
    float m_fFrameZoomFactor;

	ESContext m_esContext;
	bool m_textInputEnabled;
    WP8Keyboard^ mKeyboard;
    WP8Window^ m_wp8Window;

};

NS_CC_END

#endif    // end of __CC_EGLVIEW_WINRT_H__
