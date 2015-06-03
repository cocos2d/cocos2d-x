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

#include "CCEGLView-Win8_1.h"
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
#include "support/CCNotificationCenter.h"
#include "Keyboard-winrt.h"

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
using namespace Platform;
using namespace Microsoft::WRL;


NS_CC_BEGIN

static CCEGLView* s_pEglView = NULL;


CCEGLView::CCEGLView()
	: m_window(nullptr)
	, m_fFrameZoomFactor(1.0f)
	, m_bSupportTouch(false)
	, m_lastPointValid(false)
	, m_running(false)
	, m_initialized(false)
	, m_windowClosed(false)
	, m_windowVisible(true)
    , m_width(0)
    , m_height(0)
    , m_orientation(DisplayOrientations::Landscape)
    , m_appShouldExit(false)
{
	s_pEglView = this;
    strcpy_s(m_szViewName, "Cocos2dxWP8.1");
}

CCEGLView::~CCEGLView()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}



bool CCEGLView::Create(float width, float height)
{
	m_bSupportTouch = true;
    UpdateForWindowSizeChange(width, height);

    return true;
}


void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        if (m_keyboard == nullptr)
        {
            m_keyboard = ref new KeyBoardWinRT(m_dispatcher.Get(), m_panel.Get());
        }
        m_keyboard->ShowKeyboard(L"");
    }
    else
    {
        if (m_keyboard != nullptr)
        {
            m_keyboard->HideKeyboard(L"");
        }
        m_keyboard = nullptr;
    }
}

void CCEGLView::swapBuffers()
{
}


bool CCEGLView::isOpenGLReady()
{
	// TODO: need to revisit this
    return (true);
}

void CCEGLView::end()
{
	m_windowClosed = true;
    m_appShouldExit = true;
}

void CCEGLView::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
}

void CCEGLView::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
}


void CCEGLView::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    OnPointerPressed(args);
}

void CCEGLView::OnPointerPressed(PointerEventArgs^ args)
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
    OnPointerMoved(args);   
}

void CCEGLView::OnPointerMoved( PointerEventArgs^ args)
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
    OnPointerReleased(args);
}

void CCEGLView::OnPointerReleased(PointerEventArgs^ args)
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
	return 0;
};

void CCEGLView::Render()
{
    OnRendering();
}

void CCEGLView::OnRendering()
{
	if(m_running && m_initialized)
	{
        ProcessEvents();
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

bool CCEGLView::ShowMessageBox(Platform::String^ title, Platform::String^ message)
{
    if (m_dispatcher.Get())
    {
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([title, message]()
        {
            // Show the message dialog
            auto msg = ref new Windows::UI::Popups::MessageDialog(message, title);
            // Set the command to be invoked when a user presses 'ESC'
            msg->CancelCommandIndex = 1;
            msg->ShowAsync();
        }));

        return true;
    }
    return false;
}


// called by orientation change from WP8 XAML
void CCEGLView::UpdateOrientation(DisplayOrientations orientation)
{
    if(m_orientation != orientation)
    {
        m_orientation = orientation;
        UpdateWindowSize();
    }
}

// called by size change from WP8 XAML
void CCEGLView::UpdateForWindowSizeChange(float width, float height)
{
    m_width = width;
    m_height = height;
    UpdateWindowSize();
}

void CCEGLView::UpdateForWindowSizeChange()
{
    m_width = ConvertDipsToPixels(m_window->Bounds.Width);
    m_height = ConvertDipsToPixels(m_window->Bounds.Height);
 
    UpdateWindowSize();
}

void CCEGLView::UpdateWindowSize()
{
    float width, height;

    width = m_width;
    height = m_height;

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
        if(m_eResolutionPolicy == kResolutionUnKnown)
        {
            m_eResolutionPolicy = kResolutionShowAll;
        }
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, m_eResolutionPolicy);
        CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
   }
}



CCPoint CCEGLView::TransformToOrientation(Point p)
{
    CCPoint returnValue = CCPoint(p.X, p.Y);

	float zoomFactor = CCEGLView::sharedOpenGLView()->getFrameZoomFactor();
	if(zoomFactor > 0.0f) {
		returnValue.x /= zoomFactor;
		returnValue.y /= zoomFactor;
	}

    // CCLOG("%.2f %.2f : %.2f %.2f", p.X, p.Y,returnValue.x, returnValue.y);

    return returnValue;
}

CCPoint CCEGLView::GetCCPoint(PointerEventArgs^ args) {

	return TransformToOrientation(args->CurrentPoint->Position);

}


void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    glViewport((GLint) (x * m_fScaleX + m_obViewPortRect.origin.x),
        (GLint) (y * m_fScaleY + m_obViewPortRect.origin.y),
        (GLsizei) (w * m_fScaleX),
        (GLsizei) (h * m_fScaleY));
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    glScissor((GLint) (x * m_fScaleX + m_obViewPortRect.origin.x),
        (GLint) (y * m_fScaleY + m_obViewPortRect.origin.y),
        (GLsizei) (w * m_fScaleX),
        (GLsizei) (h * m_fScaleY));
}

bool CCEGLView::AppShouldExit()
{
    return m_appShouldExit;
}

// user pressed the Back Key on the phone
void CCEGLView::OnBackKeyPress()
{
    auto dispatcher = CCDirector::sharedDirector()->getKeypadDispatcher();
    if (dispatcher->hasDelegates())
    {
        dispatcher->dispatchKeypadMSG(ccKeypadMSGType::kTypeBackClicked);
    }
    else
    {
        CCLOG("*********************************************************************");
        CCLOG("CCEGLView::OnBackKeyPress: Exiting application!");
        CCLOG("");
        CCLOG("If you want to listen for Windows Phone back button events,");
        CCLOG("Call setKeypadEnabled(true); from your scene's init() method");
        CCLOG("Override the CCLayer::keyBackClicked() method");
        CCLOG("Make sure you call CCDirector::sharedDirector()->end() if you");
        CCLOG("want your app to exit when the back button is pressed.");
        CCLOG("");
        CCLOG("For example, add the following to your scene's init() method...");
        CCLOG("");
        CCLOG("     setKeypadEnabled(true);");
        CCLOG("");
        CCLOG("Add the keyBackClicked() method to your Scene class...");
        CCLOG("");
        CCLOG("void HelloWorld::keyBackClicked()");
        CCLOG("{");
        CCLOG("     if (myAppShouldQuit) // or whatever logic you want...");
        CCLOG("     {");
        CCLOG("         CCDirector::sharedDirector()->end();");
        CCLOG("         return;");
        CCLOG("     }");
        CCLOG("     // Handle the back button event for your app");
        CCLOG("}");
        CCLOG("");
        CCLOG("*********************************************************************");

        CCDirector::sharedDirector()->end();
    }
}

void CCEGLView::QueueBackKeyPress()
{
    std::shared_ptr<BackButtonEvent> e(new BackButtonEvent());
    mInputEvents.push(e);
}

void CCEGLView::QueuePointerEvent(PointerEventType type, PointerEventArgs^ args)
{
    std::shared_ptr<PointerEvent> e(new PointerEvent(type, args));
    mInputEvents.push(e);
}

void CCEGLView::QueueEvent(std::shared_ptr<InputEvent>& event)
{
    mInputEvents.push(event);
}

void CCEGLView::ProcessEvents()
{
    std::shared_ptr<InputEvent> e;
    while (mInputEvents.try_pop(e))
    {
        e->execute();
    }
}
NS_CC_END
