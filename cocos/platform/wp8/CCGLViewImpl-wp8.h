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

#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"
#include "InputEvent.h"


#include <agile.h>

#include <wrl/client.h>
#include <d3d11_1.h>
#include <concurrent_queue.h>

#include <agile.h>
#include <DirectXMath.h>

#include <EGL/egl.h>


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
    virtual void setViewPortInPoints(float x , float y , float w , float h);
    virtual void setScissorInPoints(float x , float y , float w , float h);
    const Mat4& getOrientationMatrix() const;
    const Mat4& getReverseOrientationMatrix () const {return m_reverseOrientationMatrix;};

    Windows::Graphics::Display::DisplayOrientations getDeviceOrientation() {return m_orientation;};
    Size getRenerTargetSize() const { return Size(m_width, m_height); }

    virtual void setIMEKeyboardState(bool bOpen);
    virtual void setIMEKeyboardState(bool bOpen, std::string str);
    Platform::String^ stringToPlatformString(std::string strSrc);
    void ShowKeyboard(Windows::Foundation::Rect r);
    void HideKeyboard(Windows::Foundation::Rect r);

    // WP8 XAML app
    virtual bool Create(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface, float width, float height
        ,Windows::Graphics::Display::DisplayOrientations orientation);
    virtual void UpdateDevice(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface);

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
    void OnBackKeyPress();

    void QueueBackKeyPress();
    void QueuePointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);
    void GLViewImpl::QueueEvent(std::shared_ptr<InputEvent>& event);

    void SetXamlEventDelegate(Cocos2dEventDelegate^ delegate) { m_delegate = delegate; };
    void SetXamlMessageBoxDelegate(Cocos2dMessageBoxDelegate^ delegate) { m_messageBoxDelegate = delegate; };
    void SetXamlEditBoxDelegate(Cocos2dEditBoxDelegate^ delegate) { m_editBoxDelegate = delegate; };

    bool ShowMessageBox(Platform::String^ title, Platform::String^ message);
    bool OpenXamlEditBox(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, int inputMode, int inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler);

	int Run();
	void Render();

    void resize(int width, int height);

	float getFrameZoomFactor();
    void centerWindow();

 	void UpdateOrientation(Windows::Graphics::Display::DisplayOrientations orientation);
 	void UpdateForWindowSizeChange(float width, float height);
   
    // static function
    /**
    @brief    get the shared main open gl window
    */
	static GLViewImpl* sharedOpenGLView();

    void ProcessEvents();
    void AddPointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);



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


private:
    CC_DISALLOW_COPY_AND_ASSIGN(GLViewImpl);

	void OnRendering();
	void UpdateWindowSize();
    void UpdateOrientationMatrix();

    cocos2d::Vec2 TransformToOrientation(Windows::Foundation::Point point);
 	cocos2d::Vec2  GetPoint(Windows::UI::Core::PointerEventArgs^ args);
       
    Windows::Foundation::Rect m_windowBounds;
	Windows::Foundation::EventRegistrationToken m_eventToken;
	Windows::Foundation::Point m_lastPoint;

    float m_width;
    float m_height;

    Windows::Graphics::Display::DisplayOrientations m_orientation;
	Windows::Foundation::Rect m_keyboardRect;

	bool m_lastPointValid;
	bool m_windowClosed;
	bool m_windowVisible;
    Mat4 m_orientationMatrix;
    Mat4 m_reverseOrientationMatrix;


    bool m_running;
	bool m_initialized;

	Microsoft::WRL::ComPtr<IWinrtEglWindow> m_eglWindow;

	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;
    Cocos2dEventDelegate^ m_delegate;
    Cocos2dMessageBoxDelegate^ m_messageBoxDelegate;
    Cocos2dEditBoxDelegate^ m_editBoxDelegate;

    Concurrency::concurrent_queue<std::shared_ptr<InputEvent>> mInputEvents;
};

NS_CC_END

#endif    // end of __CC_EGLVIEWIMPL_WINRT_H__
