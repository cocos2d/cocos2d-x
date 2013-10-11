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

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::System;
using namespace Windows::UI::ViewManagement;

NS_CC_BEGIN

static CCEGLView* s_pEglView = NULL;

//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////

// Initialize the DirectX resources required to run.
void DirectXView::Initialize(CoreWindow^ window, SwapChainBackgroundPanel^ panel)
{
	DirectXBase::Initialize(window, panel, DisplayProperties::LogicalDpi);

 	esInitContext ( &m_esContext );
	m_esContext.hWnd = WINRT_EGL_WINDOW(panel);
    // width and height are ignored and determined from the CoreWindow the SwapChainBackgroundPanel is in.
    esCreateWindow ( &m_esContext, TEXT("Cocos2d-x"), 0, 0, ES_WINDOW_RGB | ES_WINDOW_ALPHA | ES_WINDOW_DEPTH | ES_WINDOW_STENCIL );

	m_window->PointerPressed +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &DirectXView::OnPointerPressed);
    m_window->PointerReleased +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &DirectXView::OnPointerReleased);
    m_window->PointerMoved +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &DirectXView::OnPointerMoved);
    m_window->PointerWheelChanged +=
        ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &DirectXView::OnPointerWheelChanged);

	m_dummy = ref new Button();
	m_dummy->Opacity = 0.0;
	m_dummy->Width=1;
	m_dummy->Height=1;
	m_dummy->IsEnabled = true;
	panel->Children->Append(m_dummy);

	m_textBox = ref new TextBox();
	m_textBox->Opacity = 0.0;
	m_textBox->Width=1;
	m_textBox->Height=1;
	m_textBox->MaxLength = 1;

	panel->Children->Append(m_textBox);
	m_textBox->AddHandler(UIElement::KeyDownEvent, ref new KeyEventHandler(this, &DirectXView::OnTextKeyDown), true);
	m_textBox->AddHandler(UIElement::KeyUpEvent, ref new KeyEventHandler(this, &DirectXView::OnTextKeyUp), true);
	m_textBox->IsEnabled = false;

	auto keyboard = InputPane::GetForCurrentView();
	keyboard->Showing += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>(this, &DirectXView::ShowKeyboard);
	keyboard->Hiding += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>(this, &DirectXView::HideKeyboard);
	setIMEKeyboardState(false);
}

DirectXView::DirectXView(CoreWindow^ window) :
	m_lastPointValid(false),
	m_textInputEnabled(false)
{
	window->SizeChanged += 
	ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &DirectXView::OnWindowSizeChanged);

	DisplayProperties::LogicalDpiChanged +=
		ref new DisplayPropertiesEventHandler(this, &DirectXView::OnLogicalDpiChanged);

	DisplayProperties::OrientationChanged +=
        ref new DisplayPropertiesEventHandler(this, &DirectXView::OnOrientationChanged);

	DisplayProperties::DisplayContentsInvalidated +=
		ref new DisplayPropertiesEventHandler(this, &DirectXView::OnDisplayContentsInvalidated);
	
	m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &DirectXView::OnRendering));
}


void DirectXView::swapBuffers()
{
	eglSwapBuffers(m_esContext.eglDisplay, m_esContext.eglSurface);  
}

void DirectXView::ResizeWindow()
{
    UpdateForWindowSizeChange();
}

CCPoint DirectXView::GetCCPoint(PointerEventArgs^ args) {
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

void DirectXView::ShowKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->ShowKeyboard(args->OccludedRect);
}

void DirectXView::HideKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->HideKeyboard(args->OccludedRect);
}

void DirectXView::setIMEKeyboardState(bool bOpen)
{
	m_textInputEnabled = bOpen;
	if(m_textInputEnabled)
	{
		m_textBox->IsEnabled = true;
		m_textBox->Focus(FocusState::Pointer);
	}
	else
	{
		m_dummy->Focus(FocusState::Pointer);
		m_textBox->IsEnabled = false;
	}
}



void DirectXView::OnTextKeyDown(Object^ sender, KeyRoutedEventArgs^ args)
{
#if 0
	if(!m_textInputEnabled)
	{
		return;
	}

    auto key = args->Key;

    switch(key)
    {
    default:
        break;
    }
#endif
}

void DirectXView::OnTextKeyUp(Object^ sender, KeyRoutedEventArgs^ args)
{
	if(!m_textInputEnabled)
	{
		return;
	}

	args->Handled = true;

    auto key = args->Key;

    switch(key)
    {
    case VirtualKey::Escape:
        CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
		args->Handled = true;
        break;
	case VirtualKey::Back:
        CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        break;
    case VirtualKey::Enter:
		setIMEKeyboardState(false);
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
        break;
    default:
        char szUtf8[8] = {0};
        int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)m_textBox->Text->Data(), 1, szUtf8, sizeof(szUtf8), NULL, NULL);
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
        break;
    }	
	m_textBox->Text = "";
}


void DirectXView::OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
{
    float direction = (float)args->CurrentPoint->Properties->MouseWheelDelta;
    int id = 0;
    CCPoint p(0.0f,0.0f);
    CCEGLView::sharedOpenGLView()->handleTouchesBegin(1, &id, &p.x, &p.y);
    p.y += direction;
    CCEGLView::sharedOpenGLView()->handleTouchesMove(1, &id, &p.x, &p.y);
    CCEGLView::sharedOpenGLView()->handleTouchesEnd(1, &id, &p.x, &p.y);
}


void DirectXView::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    CCPoint pt = GetCCPoint(args);
    CCEGLView::sharedOpenGLView()->handleTouchesBegin(1, &id, &pt.x, &pt.y);
}

void DirectXView::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	auto currentPoint = args->CurrentPoint;
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			int id = args->CurrentPoint->PointerId;
			CCPoint p = GetCCPoint(args);
			CCEGLView::sharedOpenGLView()->handleTouchesMove(1, &id, &p.x, &p.y);
		}
		m_lastPoint = currentPoint->Position;
		m_lastPointValid = true;
	}
	else
	{
		m_lastPointValid = false;
	}
}

void DirectXView::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    CCPoint pt = GetCCPoint(args);
    CCEGLView::sharedOpenGLView()->handleTouchesEnd(1, &id, &pt.x, &pt.y);
}

void DirectXView::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	ResizeWindow();
	CCEGLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void DirectXView::OnLogicalDpiChanged(Object^ sender)
{
	SetDpi(DisplayProperties::LogicalDpi);
}

void DirectXView::OnOrientationChanged(Object^ sender)
{
	ResizeWindow();
	CCEGLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void DirectXView::OnDisplayContentsInvalidated(Object^ sender)
{
	CCEGLView::sharedOpenGLView()->ValidateDevice();
}

void DirectXView::OnRendering(Object^ sender, Object^ args)
{
	CCEGLView::sharedOpenGLView()->OnRendering();
}


CCEGLView::CCEGLView()
	: m_window(nullptr)
	, m_fFrameZoomFactor(1.0f)
	, m_bSupportTouch(false)
	, m_lastPointValid(false)
	, m_running(false)
	, m_directXView(nullptr)
	, m_initialized(false)
{
	s_pEglView = this;
    strcpy(m_szViewName, "Cocos2dxWinRT");
}

CCEGLView::~CCEGLView()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}

bool CCEGLView::Create(CoreWindow^ window, SwapChainBackgroundPanel^ panel)
{
    bool bRet = false;
	m_window = window;

	m_bSupportTouch = true;
	m_directXView = ref new DirectXView(window);
	m_directXView->Initialize(window, panel);
	UpdateForWindowSizeChange();
	m_initialized = true;
    return bRet;
}

bool CCEGLView::isOpenGLReady()
{
	// TODO: need to revisit this
    return (m_window.Get() != nullptr);
}

void CCEGLView::end()
{
	// TODO: need to implement

}

void CCEGLView::swapBuffers()
{
	m_directXView->swapBuffers();
}


void CCEGLView::setIMEKeyboardState(bool bOpen)
{
	if(m_directXView) 
	{
		m_directXView->setIMEKeyboardState(bOpen);
	}
}


void CCEGLView::resize(int width, int height)
{

}

void CCEGLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    resize((int)(m_obScreenSize.width * fZoomFactor), (int)(m_obScreenSize.height * fZoomFactor));
    centerWindow();
    CCDirector::sharedDirector()->setProjection(CCDirector::sharedDirector()->getProjection());
}


float CCEGLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void CCEGLView::setFrameSize(float width, float height)
{
	// not implemented in WinRT. Window is always full screen
    // CCEGLViewProtocol::setFrameSize(width, height);
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


void CCEGLView::OnRendering()
{
	if(m_running && m_initialized)
	{
		CCDirector::sharedDirector()->mainLoop();
		// TODO: fix audio
		// CocosDenshion::SimpleAudioEngine::sharedEngine()->render();
	}
}

void CCEGLView::HideKeyboard(Rect r)
{
    return; // not implemented
	float height = m_keyboardRect.Height;
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
    return; // not implemented
	float height = r.Height;
	float factor = m_fScaleY / CC_CONTENT_SCALE_FACTOR();
	height = (float)height / factor;

	CCRect rect_begin(0.0f, 0.0f - height, m_obScreenSize.width / factor, height);
	CCRect rect_end(0.0f, 0.0f, m_obScreenSize.width / factor, height);

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
	CCEGLViewProtocol::setFrameSize(ConvertDipsToPixels(m_window->Bounds.Width),ConvertDipsToPixels(m_window->Bounds.Height));
}

NS_CC_END
