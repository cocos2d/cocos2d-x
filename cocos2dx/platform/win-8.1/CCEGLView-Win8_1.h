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

#ifndef __CC_EGLVIEW_WINRT_8_1_H__
#define __CC_EGLVIEW_WINRT_8_1_H__

#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include <agile.h>

#include <wrl/client.h>

#include <agile.h>


NS_CC_BEGIN

class CCEGL;
ref class WP8Keyboard;
ref class CCEditBoxParam;




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

    virtual bool Create(float width, float height);

	void OnPointerPressed(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerWheelChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
	void OnResuming(Platform::Object^ sender, Platform::Object^ args);
	void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    void OnOrientationChanged();
    
    void openEditBox(cocos2d::CCEditBoxParam^ param);
    void SetCocosEditBoxHandler(Windows::Foundation::EventHandler<Platform::Object^>^ handler);
    void OnCloseEditBox();

    bool ShowMessageBox(Platform::String^ title, Platform::String^ message);
    bool OpenXamlEditBox(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, int inputMode, int inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler);

	Windows::UI::Core::CoreWindow^ getWindow() { return m_window.Get(); };
	
	int Run();
	void Render();

    void resize(int width, int height);
    /* 
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float fZoomFactor);
	float getFrameZoomFactor();
    void centerWindow();

 	void UpdateOrientation(Windows::Graphics::Display::DisplayOrientations orientation);
 	void UpdateForWindowSizeChange(float width, float height);
   
    // static function
    /**
    @brief    get the shared main open gl window
    */
	static CCEGLView* sharedOpenGLView();

protected:

private:
	void OnRendering();
	void UpdateForWindowSizeChange();
	void UpdateWindowSize();
    void UpdateOrientationMatrix();

	void ValidateDevice();
    CCPoint TransformToOrientation(Windows::Foundation::Point point);
 	CCPoint GetCCPoint(Windows::UI::Core::PointerEventArgs^ args);
       
    Windows::Foundation::Rect m_windowBounds;
	Windows::Foundation::EventRegistrationToken m_eventToken;
	Windows::Foundation::Point m_lastPoint;
    Windows::Foundation::EventHandler<Platform::Object^>^ m_editBoxhandler;

    float m_width;
    float m_height;

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

	Microsoft::WRL::ComPtr<IWinrtEglWindow> m_eglWindow;

};

NS_CC_END

#endif    // end of __CC_EGLVIEW_WINRT_8_1_H__
