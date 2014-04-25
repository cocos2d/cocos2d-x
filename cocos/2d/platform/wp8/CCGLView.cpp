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

#include "CCGLView.h"
#include "CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "CCTouch.h"
#include "CCIMEDispatcher.h"
#include "CCApplication.h"
#include "CCWinRTUtils.h"
#include "CCNotificationCenter.h"

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
using namespace PhoneDirect3DXamlAppComponent;


NS_CC_BEGIN

static GLView* s_pEglView = NULL;

GLView* GLView::create(const std::string& viewName)
{
    auto ret = new GLView;
    if(ret && ret->initWithFullScreen(viewName))
    {
        ret->autorelease();
        return ret;
    }

    return nullptr;
}


GLView::GLView()
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
    UpdateOrientationMatrix();
}

GLView::~GLView()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}

bool GLView::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor)
{
    setViewName(viewName);
    setFrameSize(rect.size.width, rect.size.height);
    setFrameZoomFactor(frameZoomFactor);
    return true;
}

bool GLView::initWithFullScreen(const std::string& viewName)
{
    return initWithRect(viewName, Rect(0, 0, m_width, m_height), 1.0f);
}


bool GLView::Create(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface, float width, float height)
{
    m_eglDisplay = eglDisplay;
    m_eglContext = eglContext;
    m_eglSurface = eglSurface;
    UpdateForWindowSizeChange(width, height);
    return true;
}

void GLView::UpdateDevice(EGLDisplay eglDisplay, EGLContext eglContext, EGLSurface eglSurface)
{
    m_eglDisplay = eglDisplay;
    m_eglContext = eglContext;
    m_eglSurface = eglSurface;

    //UpdateForWindowSizeChange(width, height);
}

void GLView::setIMEKeyboardState(bool bOpen)
{
    if(m_delegate)
    {
        if(bOpen)
        {
            m_delegate->Invoke(Cocos2dEvent::ShowKeyboard);
        }
        else
        {
            m_delegate->Invoke(Cocos2dEvent::HideKeyboard);
        }
    }
}

void GLView::swapBuffers()
{
    eglSwapBuffers(m_eglDisplay, m_eglSurface);  
}


bool GLView::isOpenGLReady()
{
	// TODO: need to revisit this
    return (m_eglDisplay && m_orientation != DisplayOrientations::None);
}

void GLView::end()
{
	m_windowClosed = true;
}


void GLView::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
}

void GLView::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}

// user pressed the Back Key on the phone
void GLView::OnBackKeyPress()
{
    if(m_delegate)
    {
        m_delegate->Invoke(Cocos2dEvent::TerminateApp);
    }
}

void GLView::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerPressed(args);
}

void GLView::OnPointerPressed(PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vector2 pt = GetPoint(args);
    handleTouchesBegin(1, &id, &pt.x, &pt.y);
}


void GLView::OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
{
    float direction = (float)args->CurrentPoint->Properties->MouseWheelDelta;
    int id = 0;
    Vector2 p(0.0f,0.0f);
    handleTouchesBegin(1, &id, &p.x, &p.y);
    p.y += direction;
    handleTouchesMove(1, &id, &p.x, &p.y);
    handleTouchesEnd(1, &id, &p.x, &p.y);
}

void GLView::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void GLView::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

void GLView::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerMoved(args);   
}

void GLView::OnPointerMoved( PointerEventArgs^ args)
{
	auto currentPoint = args->CurrentPoint;
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			int id = args->CurrentPoint->PointerId;
			Vector2 p = GetPoint(args);
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

void GLView::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerReleased(args);
}

void GLView::OnPointerReleased(PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vector2 pt = GetPoint(args);
    handleTouchesEnd(1, &id, &pt.x, &pt.y);
}



void GLView::resize(int width, int height)
{

}

void GLView::setFrameZoomFactor(float fZoomFactor)
{
    _frameZoomFactor = fZoomFactor;
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
    //resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
}

float GLView::getFrameZoomFactor()
{
    return _frameZoomFactor;
}

void GLView::centerWindow()
{
	// not implemented in WinRT. Window is always full screen
}

GLView* GLView::sharedOpenGLView()
{
    return s_pEglView;
}

int GLView::Run() 
{
    // XAML version does not have a run loop
	m_running = true; 
    return 0;
};

void GLView::Render()
{
    OnRendering();
}

void GLView::OnRendering()
{
	if(m_running && m_initialized)
	{
        Director::getInstance()->mainLoop();
	}
}



bool GLView::ShowMessageBox(Platform::String^ title, Platform::String^ message)
{
    if(m_messageBoxDelegate)
    {
        m_messageBoxDelegate->Invoke(title, message);
        return true;
    }
    return false;
}

bool GLView::OpenXamlEditBox(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, int inputMode, int inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler)
{
    if(m_editBoxDelegate)
    {
        m_editBoxDelegate->Invoke(strPlaceHolder, strText, maxLength, inputMode, inputFlag, receiveHandler);
        return true;
    }
    return false;
}



// called by orientation change from WP8 XAML
void GLView::UpdateOrientation(DisplayOrientations orientation)
{
    if(m_orientation != orientation)
    {
        m_orientation = orientation;
        UpdateWindowSize();
    }
}

// called by size change from WP8 XAML
void GLView::UpdateForWindowSizeChange(float width, float height)
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

void GLView::UpdateWindowSize()
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
        GLViewProtocol::setFrameSize(width, height);
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

const kmMat4* GLView::getOrientationMatrix() const 
{
    const kmMat4* k = &m_orientationMatrix;
    return &m_orientationMatrix;
};


void GLView::UpdateOrientationMatrix()
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

cocos2d::Vector2 GLView::TransformToOrientation(Windows::Foundation::Vector2 p)
{
    cocos2d::Vector2 returnValue;

    float x = p.X;
    float y = p.Y;  

    switch (m_orientation)
    {
        case DisplayOrientations::Portrait:
        default:
            returnValue = Vector2(x, y);
            break;
        case DisplayOrientations::Landscape:
            returnValue = Vector2(y, m_width - x);
            break;
        case DisplayOrientations::PortraitFlipped:
            returnValue = Vector2(m_width - x, m_height - y);
            break;
        case DisplayOrientations::LandscapeFlipped:
            returnValue = Vector2(m_height - y, x);
            break;
    }

	float zoomFactor = GLView::sharedOpenGLView()->getFrameZoomFactor();
	if(zoomFactor > 0.0f) {
		returnValue.x /= zoomFactor;
		returnValue.y /= zoomFactor;
	}

    // CCLOG("%.2f %.2f : %.2f %.2f", p.X, p.Y,returnValue.x, returnValue.y);

    return returnValue;
}

Vector2 GLView::GetPoint(PointerEventArgs^ args) {

	return TransformToOrientation(args->CurrentPoint->Position);

}


void GLView::setViewPortInPoints(float x , float y , float w , float h)
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

void GLView::setScissorInPoints(float x , float y , float w , float h)
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

void GLView::QueueBackKeyPress()
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<BackButtonEvent> e(new BackButtonEvent());
    mInputEvents.push(e);
}

void GLView::QueuePointerEvent(PointerEventType type, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<PointerEvent> e(new PointerEvent(type, args));
    mInputEvents.push(e);
}

void GLView::QueueEvent(std::shared_ptr<InputEvent>& event)
{
    std::lock_guard<std::mutex> guard(mMutex);
    mInputEvents.push(event);
}

void GLView::ProcessEvents()
{
    std::lock_guard<std::mutex> guard(mMutex);

    while (!mInputEvents.empty())
    {
        InputEvent* e = mInputEvents.front().get();
        e->execute();
        mInputEvents.pop();
    }
}

NS_CC_END
