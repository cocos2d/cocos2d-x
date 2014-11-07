/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
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

#include "CCGLViewImpl-wp8.h"
#include "deprecated/CCSet.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCIMEDispatcher.h"
#include "CCApplication.h"
#include "CCWinRTUtils.h"
#include "deprecated/CCNotificationCenter.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Phone::UI::Core;
using namespace Platform;
using namespace Microsoft::WRL;


NS_CC_BEGIN

static GLViewImpl* s_pEglView = NULL;

GLViewImpl* GLViewImpl::create(const std::string& viewName)
{
    auto ret = new GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName))
    {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}


GLViewImpl::GLViewImpl()
	: _frameZoomFactor(1.0f)
	, _supportTouch(true)
    , _isRetina(false)
	, m_lastPointValid(false)
	, m_running(false)
	, m_initialized(false)
	, m_windowClosed(false)
	, m_windowVisible(true)
    , m_width(0)
    , m_height(0)
    , m_eglDisplay(nullptr)
    , m_eglContext(nullptr)
    , m_eglSurface(nullptr)
    , m_delegate(nullptr)
    , m_messageBoxDelegate(nullptr)
    , m_orientation(DisplayOrientations::Landscape)
{
	s_pEglView = this;
    _viewName =  "cocos2dx";
}

GLViewImpl::~GLViewImpl()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    setViewName(viewName);
    setFrameSize(rect.size.width, rect.size.height);
    setFrameZoomFactor(frameZoomFactor);
    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName)
{
    return initWithRect(viewName, Rect(0, 0, m_width, m_height), 1.0f);
}


bool GLViewImpl::Create(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface, float width, float height, DisplayOrientations orientation)
{
    m_orientation = orientation;
    m_eglDisplay = eglDisplay;
    m_eglContext = eglContext;
    m_eglSurface = eglSurface;
    UpdateForWindowSizeChange(width, height);
    return true;
}

void GLViewImpl::UpdateDevice(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface)
{
    m_eglDisplay = eglDisplay;
    m_eglContext = eglContext;
    m_eglSurface = eglSurface;

    //UpdateForWindowSizeChange(width, height);
}

void GLViewImpl::setIMEKeyboardState(bool bOpen)
{
    std::string str;
    setIMEKeyboardState(bOpen, str);
}

void GLViewImpl::setIMEKeyboardState(bool bOpen, std::string str)
{
    if(m_delegate)
    {
        if(bOpen)
        {
            m_delegate->Invoke(Cocos2dEvent::ShowKeyboard, stringToPlatformString(str));
        }
        else
        {
            m_delegate->Invoke(Cocos2dEvent::HideKeyboard, stringToPlatformString(str));
        }
    }
}

Platform::String^ GLViewImpl::stringToPlatformString(std::string strSrc)
{
    // to wide char
    int strLen = MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[strLen + 1];
    memset(wstr, 0, strLen + 1);
    MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, wstr, strLen);
    Platform::String^ strDst = ref new Platform::String(wstr);
    delete[] wstr;
    return strDst;
}

void GLViewImpl::swapBuffers()
{
    eglSwapBuffers(m_eglDisplay, m_eglSurface);  
}


bool GLViewImpl::isOpenGLReady()
{
	// TODO: need to revisit this
    return (m_eglDisplay && m_orientation != DisplayOrientations::None);
}

void GLViewImpl::end()
{
	m_windowClosed = true;
}


void GLViewImpl::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
}

void GLViewImpl::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}

// user pressed the Back Key on the phone
void GLViewImpl::OnBackKeyPress()
{
    std::string str;
    if(m_delegate)
    {
        m_delegate->Invoke(Cocos2dEvent::TerminateApp, stringToPlatformString(str));
    }
}

void GLViewImpl::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerPressed(args);
}

void GLViewImpl::OnPointerPressed(PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vec2 pt = GetPoint(args);
    handleTouchesBegin(1, &id, &pt.x, &pt.y);
}


void GLViewImpl::OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
{
    float direction = (float)args->CurrentPoint->Properties->MouseWheelDelta;
    int id = 0;
    Vec2 p(0.0f,0.0f);
    handleTouchesBegin(1, &id, &p.x, &p.y);
    p.y += direction;
    handleTouchesMove(1, &id, &p.x, &p.y);
    handleTouchesEnd(1, &id, &p.x, &p.y);
}

void GLViewImpl::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void GLViewImpl::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

void GLViewImpl::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerMoved(args);   
}

void GLViewImpl::OnPointerMoved( PointerEventArgs^ args)
{
	auto currentPoint = args->CurrentPoint;
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			int id = args->CurrentPoint->PointerId;
			Vec2 p = GetPoint(args);
			handleTouchesMove(1, &id, &p.x, &p.y);
		}
		m_lastPoint = currentPoint->Position;
		m_lastPointValid = true;
	}
	else
	{
		m_lastPointValid = false;
	}
}

void GLViewImpl::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerReleased(args);
}

void GLViewImpl::OnPointerReleased(PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vec2 pt = GetPoint(args);
    handleTouchesEnd(1, &id, &pt.x, &pt.y);
}



void GLViewImpl::resize(int width, int height)
{

}

void GLViewImpl::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
    //resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
}

float GLViewImpl::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void GLViewImpl::centerWindow()
{
	// not implemented in WinRT. Window is always full screen
}

GLViewImpl* GLViewImpl::sharedOpenGLView()
{
    return s_pEglView;
}

int GLViewImpl::Run() 
{
    // XAML version does not have a run loop
	m_running = true; 
    return 0;
};

void GLViewImpl::Render()
{
    OnRendering();
}

void GLViewImpl::OnRendering()
{
	if(m_running && m_initialized)
	{
        Director::getInstance()->mainLoop();
	}
}



bool GLViewImpl::ShowMessageBox(Platform::String^ title, Platform::String^ message)
{
    if(m_messageBoxDelegate)
    {
        m_messageBoxDelegate->Invoke(title, message);
        return true;
    }
    return false;
}

bool GLViewImpl::OpenXamlEditBox(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, int inputMode, int inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler)
{
    if(m_editBoxDelegate)
    {
        m_editBoxDelegate->Invoke(strPlaceHolder, strText, maxLength, inputMode, inputFlag, receiveHandler);
        return true;
    }
    return false;
}



// called by orientation change from WP8 XAML
void GLViewImpl::UpdateOrientation(DisplayOrientations orientation)
{
    if(m_orientation != orientation)
    {
        m_orientation = orientation;
        UpdateWindowSize();
    }
}

// called by size change from WP8 XAML
void GLViewImpl::UpdateForWindowSizeChange(float width, float height)
{
    m_width = width;
    m_height = height;
    UpdateWindowSize();
}

#if 0
win32 version

void GLViewEventHandler::OnGLFWWindowSizeFunCallback(GLFWwindow *windows, int width, int height)
{	
	auto view = Director::getInstance()->getOpenGLView();
	if(view && view->getResolutionPolicy() != ResolutionPolicy::UNKNOWN)
	{
		Size resSize=view->getDesignResolutionSize();
		ResolutionPolicy resPolicy=view->getResolutionPolicy();
		view->setFrameSize(width, height);
 		view->setDesignResolutionSize(resSize.width, resSize.height, resPolicy);
		Director::getInstance()->setViewport();
	}
}
#endif

void GLViewImpl::UpdateWindowSize()
{
    float width, height;

    if(m_orientation == DisplayOrientations::Landscape || m_orientation == DisplayOrientations::LandscapeFlipped)
    {
        width = m_height;
        height = m_width;
    }
    else
    {
        width = m_width;
        height = m_height;
    }

    UpdateOrientationMatrix();

    //CCSize designSize = getDesignResolutionSize();
    if(!m_initialized)
    {
        m_initialized = true;
        GLView::setFrameSize(width, height);
    }

    auto view = Director::getInstance()->getOpenGLView();
	if(view && view->getResolutionPolicy() != ResolutionPolicy::UNKNOWN)
	{
		Size resSize=view->getDesignResolutionSize();
		ResolutionPolicy resPolicy=view->getResolutionPolicy();
		view->setFrameSize(width, height);
 		view->setDesignResolutionSize(resSize.width, resSize.height, resPolicy);
		Director::getInstance()->setViewport();
        Director::sharedDirector()->setProjection(Director::sharedDirector()->getProjection());
	}
}

const Mat4& GLViewImpl::getOrientationMatrix() const 
{
    return m_orientationMatrix;
};


void GLViewImpl::UpdateOrientationMatrix()
{
    kmMat4Identity(&m_orientationMatrix);
    kmMat4Identity(&m_reverseOrientationMatrix);
    switch(m_orientation)
	{
		case Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
			kmMat4RotationZ(&m_orientationMatrix, M_PI);
			kmMat4RotationZ(&m_reverseOrientationMatrix, -M_PI);
			break;

		case Windows::Graphics::Display::DisplayOrientations::Landscape:
            kmMat4RotationZ(&m_orientationMatrix, -M_PI_2);
			kmMat4RotationZ(&m_reverseOrientationMatrix, M_PI_2);
			break;
			
		case Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
            kmMat4RotationZ(&m_orientationMatrix, M_PI_2);
            kmMat4RotationZ(&m_reverseOrientationMatrix, -M_PI_2);
			break;

        default:
            break;
	}
}

cocos2d::Vec2 GLViewImpl::TransformToOrientation(Windows::Foundation::Point p)
{
    cocos2d::Vec2 returnValue;

    float x = p.X;
    float y = p.Y;  

    switch (m_orientation)
    {
        case DisplayOrientations::Portrait:
        default:
            returnValue = Vec2(x, y);
            break;
        case DisplayOrientations::Landscape:
            returnValue = Vec2(y, m_width - x);
            break;
        case DisplayOrientations::PortraitFlipped:
            returnValue = Vec2(m_width - x, m_height - y);
            break;
        case DisplayOrientations::LandscapeFlipped:
            returnValue = Vec2(m_height - y, x);
            break;
    }

	float zoomFactor = GLViewImpl::sharedOpenGLView()->getFrameZoomFactor();
	if(zoomFactor > 0.0f) {
		returnValue.x /= zoomFactor;
		returnValue.y /= zoomFactor;
	}

    // CCLOG("%.2f %.2f : %.2f %.2f", p.X, p.Y,returnValue.x, returnValue.y);

    return returnValue;
}

Vec2 GLViewImpl::GetPoint(PointerEventArgs^ args) {

	return TransformToOrientation(args->CurrentPoint->Position);

}


void GLViewImpl::setViewPortInPoints(float x , float y , float w , float h)
{
    switch(m_orientation)
	{
		case DisplayOrientations::Landscape:
		case DisplayOrientations::LandscapeFlipped:
            glViewport((GLint)(y * _scaleY + _viewPortRect.origin.y),
                       (GLint)(x * _scaleX + _viewPortRect.origin.x),
                       (GLsizei)(h * _scaleY),
                       (GLsizei)(w * _scaleX));
			break;

        default:
            glViewport((GLint)(x * _scaleX + _viewPortRect.origin.x),
                       (GLint)(y * _scaleY + _viewPortRect.origin.y),
                       (GLsizei)(w * _scaleX),
                       (GLsizei)(h * _scaleY));
	}
}

void GLViewImpl::setScissorInPoints(float x , float y , float w , float h)
{
    switch(m_orientation)
	{
		case DisplayOrientations::Landscape:
		case DisplayOrientations::LandscapeFlipped:
            glScissor((GLint)(y * _scaleX + _viewPortRect.origin.y),
                       (GLint)((_viewPortRect.size.width - ((x + w) * _scaleX)) + _viewPortRect.origin.x),
                       (GLsizei)(h * _scaleY),
                       (GLsizei)(w * _scaleX));
			break;

        default:
            glScissor((GLint)(x * _scaleX + _viewPortRect.origin.x),
                       (GLint)(y * _scaleY + _viewPortRect.origin.y),
                       (GLsizei)(w * _scaleX),
                       (GLsizei)(h * _scaleY));
	}
}

void GLViewImpl::QueueBackKeyPress()
{
    std::shared_ptr<BackButtonEvent> e(new BackButtonEvent());
    mInputEvents.push(e);
}

void GLViewImpl::QueuePointerEvent(PointerEventType type, PointerEventArgs^ args)
{
    std::shared_ptr<PointerEvent> e(new PointerEvent(type, args));
    mInputEvents.push(e);
}

void GLViewImpl::QueueEvent(std::shared_ptr<InputEvent>& event)
{
    mInputEvents.push(event);
}

void GLViewImpl::ProcessEvents()
{
    std::shared_ptr<InputEvent> e;
    while (mInputEvents.try_pop(e))
    {
        e->execute();
    }
}

NS_CC_END
