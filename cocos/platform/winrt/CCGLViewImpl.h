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

#ifndef __CC_EGLVIEWIMPL_WINRT_H__
#define __CC_EGLVIEWIMPL_WINRT_H__

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "CCStdC.h"
#include "CCGL.h"
#include "platform/CCCommon.h"
#include "InputEvent.h"
#include "platform/CCGLView.h"
#include <agile.h>

#include <wrl/client.h>

#include <agile.h>
#include <DirectXMath.h>
#include <mutex>
#include <queue>

NS_CC_BEGIN

class CCEGL;
class GLViewImpl;

ref class WinRTWindow sealed
{

public:
    WinRTWindow(Windows::UI::Core::CoreWindow^ window);
	void Initialize(Windows::UI::Core::CoreWindow^ window, Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^ panel);
	void setIMEKeyboardState(bool bOpen);
    void swapBuffers();


private:
	cocos2d::Vec2 GetCCPoint(Windows::UI::Core::PointerEventArgs^ args);

	void OnTextKeyDown(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e); 
	void OnTextKeyUp(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e); 

	void OnPointerWheelChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
	void OnLogicalDpiChanged(Platform::Object^ sender);
	void OnOrientationChanged(Platform::Object^ sender);
	void OnDisplayContentsInvalidated(Platform::Object^ sender);
    void OnRendering(Platform::Object^ sender, Platform::Object^ args);
    void OnSuspending();
    void ResizeWindow();
    

	void ShowKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args);
	void HideKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args);

	Platform::Agile<Windows::UI::Core::CoreWindow> m_window;

	Windows::Foundation::Point m_lastPoint;
	Windows::Foundation::EventRegistrationToken m_eventToken;
	bool m_lastPointValid;
	bool m_textInputEnabled;
	Microsoft::WRL::ComPtr<IWinrtEglWindow> m_eglWindow;
	Windows::UI::Xaml::Controls::TextBox^ m_textBox;
	Windows::UI::Xaml::Controls::Button^ m_dummy;

    ESContext m_esContext;


    friend GLViewImpl;
};

class CC_DLL GLViewImpl : public GLView
{
public:
    GLViewImpl();
    virtual ~GLViewImpl();

    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual void setFrameSize(float width, float height);
    virtual void setIMEKeyboardState(bool bOpen);
	void ShowKeyboard(Windows::Foundation::Rect r);
	void HideKeyboard(Windows::Foundation::Rect r);
    virtual bool Create(Windows::UI::Core::CoreWindow^ window, Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^ panel);
	void UpdateForWindowSizeChange();
	void OnRendering();
    void OnSuspending();
    void GLViewImpl::QueueEvent(std::shared_ptr<InputEvent>& event);

    void OnPointerPressed(Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerMoved(Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerReleased(Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnBackKeyPress();


private:
	Windows::Foundation::EventRegistrationToken m_eventToken;
	Windows::Foundation::Point m_lastPoint;
	bool m_lastPointValid;

public:

    // winrt platform functions
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
	static GLViewImpl* sharedOpenGLView();

protected:

private:
    Platform::Agile<Windows::UI::Core::CoreWindow> m_window;
	bool m_running;
	bool m_initialized;
    bool m_bSupportTouch;
    float m_fFrameZoomFactor;
	WinRTWindow^ m_winRTWindow;
	Windows::Foundation::Rect m_keyboardRect;

    std::queue<std::shared_ptr<InputEvent>> mInputEvents;
    std::mutex mMutex;
};

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#endif    // end of __CC_EGLVIEWIMPL_WINRT_H__
