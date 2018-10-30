/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "platform/winrt/CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/winrt/Keyboard-winrt.h"
#include "platform/CCGLView.h"
#include "base/CCEventKeyboard.h"

#include <agile.h>
#include <concurrent_queue.h>
#include <string>
#include <memory>
#include <wrl/client.h>

NS_CC_BEGIN

class GLViewImpl;

class CC_DLL GLViewImpl : public GLView
{
public:
    static GLViewImpl* create(const std::string& viewName);

    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();

    Windows::Graphics::Display::DisplayOrientations getDeviceOrientation() {return m_orientation;};
    Size getRenerTargetSize() const { return Size(m_width, m_height); }

    virtual void setIMEKeyboardState(bool bOpen) override;
    virtual void setIMEKeyboardState(bool bOpen, const std::string& str);

    virtual bool Create(float width, float height, float dpi, Windows::Graphics::Display::DisplayOrientations orientation);

    /**
    * Hide or Show the mouse cursor if there is one.
    *
    * @param isVisible Hide or Show the mouse cursor if there is one.
    */
    virtual void setCursorVisible(bool isVisible) override;

    bool isCursorVisible() { return _isCursorVisible; }

    void setDispatcher(Windows::UI::Core::CoreDispatcher^ dispatcher);
    Windows::UI::Core::CoreDispatcher^ getDispatcher() {return m_dispatcher.Get();}

    void setPanel(Windows::UI::Xaml::Controls::Panel^ panel);
    Windows::UI::Xaml::Controls::Panel^ getPanel() {return m_panel.Get();}

	void OnPointerPressed(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::PointerEventArgs^ args);

    void OnMousePressed(Windows::UI::Core::PointerEventArgs^ args);
    void OnMouseMoved(Windows::UI::Core::PointerEventArgs^ args);
    void OnMouseReleased(Windows::UI::Core::PointerEventArgs^ args);
    void OnMouseWheelChanged(Windows::UI::Core::PointerEventArgs^ args);

	void OnWinRTKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args);


	void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerWheelChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
	void OnResuming(Platform::Object^ sender, Platform::Object^ args);
	void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    void OnBackKeyPress();
    bool AppShouldExit();
    void BackButtonListener(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void QueueBackKeyPress();
	void QueuePointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);
	void QueueWinRTKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args);
	void QueueEvent(std::shared_ptr<InputEvent>& event);

    bool ShowMessageBox(Platform::String^ title, Platform::String^ message);

	int Run();
	void Render();

    void resize(int width, int height);

	float getFrameZoomFactor();
    void centerWindow();

 	void UpdateOrientation(Windows::Graphics::Display::DisplayOrientations orientation);
    void UpdateForWindowSizeChange(float width, float height);

    void SetDPI(float dpi) { m_dpi = dpi; }
    float GetDPI() { return m_dpi; }

    // static function
    /**
    @brief    get the shared main open gl window
    */
	static GLViewImpl* sharedOpenGLView();

    void ProcessEvents();

protected:
    GLViewImpl();
    virtual ~GLViewImpl();

    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);

    /*
     * Set zoom factor for frame. This method is for debugging big resolution (e.g.new ipad) app on desktop.
     */
    void setFrameZoomFactor(float zoomFactor);

    inline bool isRetina() { return _isRetina; };

    float _frameZoomFactor;
    bool _supportTouch;
    bool _isRetina;
    bool _isCursorVisible;


private:
    CC_DISALLOW_COPY_AND_ASSIGN(GLViewImpl);

	void OnRendering();
	void UpdateWindowSize();
 
    cocos2d::Vec2 TransformToOrientation(Windows::Foundation::Point point);
 	cocos2d::Vec2  GetPoint(Windows::UI::Core::PointerEventArgs^ args);
    cocos2d::Vec2  GetPointMouse(Windows::UI::Core::PointerEventArgs^ args);
       
    Windows::Foundation::Rect m_windowBounds;
	Windows::Foundation::EventRegistrationToken m_eventToken;
	Windows::Foundation::Point m_lastPoint;

    float m_width;
    float m_height;
    float m_dpi;

    Windows::Graphics::Display::DisplayOrientations m_orientation;
	Windows::Foundation::Rect m_keyboardRect;

	bool m_lastPointValid;
	bool m_windowClosed;
	bool m_windowVisible;
    // PointerReleased for mouse not send button id, need save in PointerPressed last button
    EventMouse::MouseButton _lastMouseButtonPressed;

    bool m_running;
	bool m_initialized;
    bool m_appShouldExit;

    Concurrency::concurrent_queue<std::shared_ptr<InputEvent>> mInputEvents;

    Platform::Agile<Windows::UI::Core::CoreDispatcher> m_dispatcher;
    Platform::Agile<Windows::UI::Xaml::Controls::Panel> m_panel;

    KeyBoardWinRT^ m_keyboard;

    cocos2d::EventListenerKeyboard* m_backButtonListener;

};

NS_CC_END

#endif    // end of __CC_EGLVIEWIMPL_WINRT_H__
