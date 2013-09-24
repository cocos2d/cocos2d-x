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

#include "CCEGLView.h"
#include "cocoa/CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "support/CCPointExtension.h"
#include "CCApplication.h"
#include "CCWinRTUtils.h"
#include "WP8Keyboard.h"

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


NS_CC_BEGIN

static CCEGLView* s_pEglView = NULL;

WP8Window::WP8Window(CoreWindow^ window)
{
	m_window = window;
    DisplayProperties::OrientationChanged += ref new DisplayPropertiesEventHandler(this, &WP8Window::OnOrientationChanged);
}

void WP8Window::OnOrientationChanged(Platform::Object^ sender)
{
    CCEGLView::sharedOpenGLView()->OnOrientationChanged();
}

CCEGLView::CCEGLView()
	: m_window(nullptr)
	, m_fFrameZoomFactor(1.0f)
	, m_bSupportTouch(false)
	, m_lastPointValid(false)
	, m_running(false)
	, m_initialized(false)
    , m_textInputEnabled(false)
	, m_windowClosed(false)
	, m_windowVisible(true)
    , mKeyboard(nullptr)
{
	s_pEglView = this;
    strcpy_s(m_szViewName, "Cocos2dxWP8");
}

CCEGLView::~CCEGLView()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}

bool CCEGLView::Create(CoreWindow^ window)
{
    bool bRet = false;
	m_window = window;
	m_bSupportTouch = true;

 	esInitContext ( &m_esContext );
	m_esContext.hWnd = WINRT_EGL_WINDOW(window);
    esCreateWindow ( &m_esContext, TEXT("Cocos2d-x"), 0, 0, ES_WINDOW_RGB | ES_WINDOW_ALPHA | ES_WINDOW_DEPTH | ES_WINDOW_STENCIL );

    m_wp8Window = ref new WP8Window(window);
    m_orientation = DisplayOrientations::None;
    m_initialized = false;
    UpdateForWindowSizeChange();

    return bRet;
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
	m_textInputEnabled = bOpen;
    if(!mKeyboard)
        mKeyboard = ref new WP8Keyboard(m_window.Get());

    mKeyboard->SetFocus(m_textInputEnabled);
}

void CCEGLView::swapBuffers()
{
	eglSwapBuffers(m_esContext.eglDisplay, m_esContext.eglSurface);  
}


bool CCEGLView::isOpenGLReady()
{
	// TODO: need to revisit this
    return (m_window.Get() != nullptr && m_orientation != DisplayOrientations::None);
}

void CCEGLView::end()
{
	m_windowClosed = true;
}


void CCEGLView::OnOrientationChanged()
{
    UpdateForWindowSizeChange();
}

void CCEGLView::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
}

void CCEGLView::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}


void CCEGLView::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    CCPoint pt = GetCCPoint(args);
    handleTouchesBegin(1, &id, &pt.x, &pt.y);
}

void CCEGLView::OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
{
    float direction = (float)args->CurrentPoint->Properties->MouseWheelDelta;
    int id = 0;
    CCPoint p(0.0f,0.0f);
    handleTouchesBegin(1, &id, &p.x, &p.y);
    p.y += direction;
    handleTouchesMove(1, &id, &p.x, &p.y);
    handleTouchesEnd(1, &id, &p.x, &p.y);
}

void CCEGLView::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void CCEGLView::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

void CCEGLView::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	auto currentPoint = args->CurrentPoint;
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			int id = args->CurrentPoint->PointerId;
			CCPoint p = GetCCPoint(args);
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

void CCEGLView::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    CCPoint pt = GetCCPoint(args);
    handleTouchesEnd(1, &id, &pt.x, &pt.y);
}




void CCEGLView::resize(int width, int height)
{

}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    resize(m_obScreenSize.width * fZoomFactor, m_obScreenSize.height * fZoomFactor);
    centerWindow();



    CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}

float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}



void CCEGLView::centerWindow()
{
	// not implemented in WinRT. Window is always full screen
}



CCEGLView* CCEGLView::sharedOpenGLView()
{
    return s_pEglView;
}

int CCEGLView::Run() 
{
	m_running = true; 
	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			OnRendering();
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
	return 0;
};

void CCEGLView::OnRendering()
{
	if(m_running && m_initialized)
	{
		CCDirector::sharedDirector()->mainLoop();
	}
}

void CCEGLView::HideKeyboard(Rect r)
{
    return; // not yet implemented
	int height = m_keyboardRect.Height;
	float factor = m_fScaleY / CC_CONTENT_SCALE_FACTOR();
	height = (float)height / factor;

	CCRect rect_end(0, 0, 0, 0);
	CCRect rect_begin(0, 0, m_obScreenSize.width / factor, height);

    CCIMEKeyboardNotificationInfo info;
    info.begin = rect_begin;
    info.end = rect_end;
    info.duration = 0;
    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardWillHide(info);
    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardDidHide(info);
}

void CCEGLView::ShowKeyboard(Rect r)
{
    return; // not yet implemented
	int height = r.Height;
	float factor = m_fScaleY / CC_CONTENT_SCALE_FACTOR();
	height = (float)height / factor;

	CCRect rect_begin(0, 0 - height, m_obScreenSize.width / factor, height);
	CCRect rect_end(0, 0, m_obScreenSize.width / factor, height);

    CCIMEKeyboardNotificationInfo info;
    info.begin = rect_begin;
    info.end = rect_end;
    info.duration = 0;
    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardWillShow(info);
    CCIMEDispatcher::sharedDispatcher()->dispatchKeyboardDidShow(info);
	m_keyboardRect = r;
}

void CCEGLView::ValidateDevice()
{

}

void CCEGLView::UpdateForWindowSizeChange()
{
    float width, height;

    m_orientation = DisplayProperties::CurrentOrientation;

    m_windowBounds = m_window->Bounds;
    
    if(m_orientation == DisplayOrientations::Landscape || m_orientation == DisplayOrientations::LandscapeFlipped)
    {
        width = ConvertDipsToPixels(m_window->Bounds.Height);
        height = ConvertDipsToPixels(m_window->Bounds.Width);
    }
    else
    {
        width = ConvertDipsToPixels(m_window->Bounds.Width);
        height = ConvertDipsToPixels(m_window->Bounds.Height);
    }

    UpdateOrientationMatrix();

    //CCSize designSize = getDesignResolutionSize();
    if(!m_initialized)
    {
        m_initialized = true;
        CCEGLViewProtocol::setFrameSize(width, height);
    }
    else
    {
        m_obScreenSize = CCSizeMake(width, height);
        CCSize designSize = getDesignResolutionSize();
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
        CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
   }
}

void CCEGLView::UpdateOrientationMatrix()
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



Point CCEGLView::TransformToOrientation(Point point, bool dipsToPixels)
{
    Point returnValue;

    switch (DisplayProperties::CurrentOrientation)
    {
    case DisplayOrientations::Portrait:
        returnValue = point;
        break;
    case DisplayOrientations::Landscape:
        returnValue = Point(point.Y, m_windowBounds.Width - point.X);
        break;
    case DisplayOrientations::PortraitFlipped:
        returnValue = Point(m_windowBounds.Width - point.X, m_windowBounds.Height - point.Y);
        break;
    case DisplayOrientations::LandscapeFlipped:
        returnValue = Point(m_windowBounds.Height -point.Y, point.X);
        break;
    default:
        throw ref new Platform::FailureException();
        break;
    }

    return dipsToPixels ? Point(ConvertDipsToPixels(returnValue.X),
                                ConvertDipsToPixels(returnValue.Y)) 
                        : returnValue;
}

#if 1

CCPoint CCEGLView::GetCCPoint(PointerEventArgs^ args) {

	auto p = TransformToOrientation(args->CurrentPoint->Position, false);
	float x = getScaledDPIValue(p.X);
	float y = getScaledDPIValue(p.Y);
    CCPoint pt(x, y);

	float zoomFactor = CCEGLView::sharedOpenGLView()->getFrameZoomFactor();

	if(zoomFactor > 0.0f) {
		pt.x /= zoomFactor;
		pt.y /= zoomFactor;
	}
	return pt;
}

#else
CCPoint CCEGLView::GetCCPoint(PointerEventArgs^ args) {
	auto p = args->CurrentPoint;
	float x = getScaledDPIValue(p->Position.X);
	float y = getScaledDPIValue(p->Position.Y);
    CCPoint pt(x, y);

	float zoomFactor = CCEGLView::sharedOpenGLView()->getFrameZoomFactor();

	if(zoomFactor > 0.0f) {
		pt.x /= zoomFactor;
		pt.y /= zoomFactor;
	}
	return pt;
}
#endif

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    switch(m_orientation)
	{
		case DisplayOrientations::Landscape:
		case DisplayOrientations::LandscapeFlipped:
            glViewport((GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
                       (GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
                       (GLsizei)(h * m_fScaleY),
                       (GLsizei)(w * m_fScaleX));
			break;

        default:
            glViewport((GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
                       (GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
                       (GLsizei)(w * m_fScaleX),
                       (GLsizei)(h * m_fScaleY));
	}
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    switch(m_orientation)
	{
		case DisplayOrientations::Landscape:
		case DisplayOrientations::LandscapeFlipped:
            glViewport((GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
                       (GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
                       (GLsizei)(h * m_fScaleY),
                       (GLsizei)(w * m_fScaleX));
			break;

        default:
            glViewport((GLint)(x * m_fScaleX + m_obViewPortRect.origin.x),
                       (GLint)(y * m_fScaleY + m_obViewPortRect.origin.y),
                       (GLsizei)(w * m_fScaleX),
                       (GLsizei)(h * m_fScaleY));
	}
}


NS_CC_END
