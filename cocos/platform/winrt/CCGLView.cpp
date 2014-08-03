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

#include "base/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "CCGLView.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCIMEDispatcher.h"
#include "CCApplication.h"
#include "CCWinRTUtils.h"

#if (_MSC_VER >= 1800)
#include <d3d11_2.h>
#endif


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

static GLView* s_pEglView = NULL;

//////////////////////////////////////////////////////////////////////////
// impliment GLView
//////////////////////////////////////////////////////////////////////////
WinRTWindow::WinRTWindow(CoreWindow^ window, Windows::UI::Xaml::Controls::SwapChainPanel^ panel) :
	m_lastPointValid(false),
	m_textInputEnabled(false)
{
	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &WinRTWindow::OnVisibilityChanged);

	window->SizeChanged += 
	ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &WinRTWindow::OnWindowSizeChanged);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &WinRTWindow::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &WinRTWindow::OnOrientationChanged);

	currentDisplayInformation->DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &WinRTWindow::OnDisplayContentsInvalidated);

	panel->CompositionScaleChanged +=
		ref new TypedEventHandler<SwapChainPanel^, Object^>(this, &WinRTWindow::OnCompositionScaleChanged);

	panel->SizeChanged +=
		ref new SizeChangedEventHandler(this, &WinRTWindow::OnSwapChainPanelSizeChanged); 
	
	m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &WinRTWindow::OnRendering));

	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinRTWindow::OnPointerPressed);
	window->PointerReleased +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinRTWindow::OnPointerReleased);
	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinRTWindow::OnPointerMoved);
	window->PointerWheelChanged +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &WinRTWindow::OnPointerWheelChanged);
	window->KeyDown += 
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &WinRTWindow::OnKeyDown);
	window->KeyUp +=
		ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &WinRTWindow::OnKeyUp);
}



void WinRTWindow::OnSuspending()
{
#if (_MSC_VER >= 1800)
    Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
	Microsoft::WRL::ComPtr<ID3D11Device> device = m_d3dDevice;
    HRESULT result = device.As(&dxgiDevice);
    if (SUCCEEDED(result))
    {
        dxgiDevice->Trim();
    }
#endif
}


void WinRTWindow::ResizeWindow()
{
     GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

cocos2d::Vec2 WinRTWindow::GetCCPoint(PointerEventArgs^ args) {
	auto p = args->CurrentPoint;
	float x = getScaledDPIValue(p->Position.X);
	float y = getScaledDPIValue(p->Position.Y);
    Vec2 pt(x, y);

	float zoomFactor = GLView::sharedOpenGLView()->getFrameZoomFactor();

	if(zoomFactor > 0.0f) {
		pt.x /= zoomFactor;
		pt.y /= zoomFactor;
	}
	return pt;
}

void WinRTWindow::ShowKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    GLView::sharedOpenGLView()->ShowKeyboard(args->OccludedRect);
}

void WinRTWindow::HideKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    GLView::sharedOpenGLView()->HideKeyboard(args->OccludedRect);
}

void WinRTWindow::OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
{
    float direction = (float)args->CurrentPoint->Properties->MouseWheelDelta;
    int id = 0;
    Vec2 p(0.0f,0.0f);
    GLView::sharedOpenGLView()->handleTouchesBegin(1, &id, &p.x, &p.y);
    p.y += direction;
    GLView::sharedOpenGLView()->handleTouchesMove(1, &id, &p.x, &p.y);
    GLView::sharedOpenGLView()->handleTouchesEnd(1, &id, &p.x, &p.y);
}

void WinRTWindow::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vec2 pt = GetCCPoint(args);
    GLView::sharedOpenGLView()->handleTouchesBegin(1, &id, &pt.x, &pt.y);
}

void WinRTWindow::OnPointerMoved(CoreWindow^ sender, PointerEventArgs^ args)
{
	auto currentPoint = args->CurrentPoint;
	if (currentPoint->IsInContact)
	{
		if (m_lastPointValid)
		{
			int id = args->CurrentPoint->PointerId;
			Vec2 p = GetCCPoint(args);
			GLView::sharedOpenGLView()->handleTouchesMove(1, &id, &p.x, &p.y);
		}
		m_lastPoint = currentPoint->Position;
		m_lastPointValid = true;
	}
	else
	{
		m_lastPointValid = false;
	}
}

void WinRTWindow::OnPointerReleased(CoreWindow^ sender, PointerEventArgs^ args)
{
    int id = args->CurrentPoint->PointerId;
    Vec2 pt = GetCCPoint(args);
    GLView::sharedOpenGLView()->handleTouchesEnd(1, &id, &pt.x, &pt.y);
}

void WinRTWindow::OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
{
	if (!args->KeyStatus.WasKeyDown)
	{
		EventKeyboard keyboardEvent(GetCocosKeyCode(args->VirtualKey), true);
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->dispatchEvent(&keyboardEvent);
	}
}

void WinRTWindow::OnKeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
{
	if (args->KeyStatus.IsKeyReleased)
	{
		EventKeyboard keyboardEvent(GetCocosKeyCode(args->VirtualKey), false);
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->dispatchEvent(&keyboardEvent);
	}
}

EventKeyboard::KeyCode WinRTWindow::GetCocosKeyCode(Windows::System::VirtualKey key)
{
	switch (key)
	{
	case VirtualKey::A:
		return EventKeyboard::KeyCode::KEY_A;		
		// TODO : add all 
	case VirtualKey::Escape:
		return EventKeyboard::KeyCode::KEY_ESCAPE;
	case VirtualKey::Space:
		return EventKeyboard::KeyCode::KEY_SPACE;
	case VirtualKey::Up:
		return EventKeyboard::KeyCode::KEY_UP_ARROW;
	case VirtualKey::Down:
		return EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	case VirtualKey::Left:
		return EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	case VirtualKey::Right:
		return EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	case VirtualKey::Control:	
		return EventKeyboard::KeyCode::KEY_CTRL;
	case VirtualKey::Enter:
		return EventKeyboard::KeyCode::KEY_ENTER;
	}

	return EventKeyboard::KeyCode::KEY_NONE;
}

void WinRTWindow::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	ResizeWindow();
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
	ResizeWindow();
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnRendering(Object^ sender, Object^ args)
{
	GLView::sharedOpenGLView()->OnRendering();
}

void WinRTWindow::OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel^ sender, Object^ args)
{
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnSwapChainPanelSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
	GLView::sharedOpenGLView()->UpdateForWindowSizeChange();
}

void WinRTWindow::OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args)
{
	
}

GLView::GLView()
	: m_window(nullptr)
	, m_fFrameZoomFactor(1.0f)
	, m_bSupportTouch(false)
	, m_lastPointValid(false)
	, m_running(false)
	, m_winRTWindow(nullptr)
	, m_initialized(false)
{
	s_pEglView = this;
    _viewName = "Cocos2dxWinRT";
}

GLView::~GLView()
{
	CC_ASSERT(this == s_pEglView);
    s_pEglView = NULL;

	// TODO: cleanup 
}

bool GLView::Create(CoreWindow^ window, SwapChainPanel^ panel)
{
    bool bRet = false;
	m_window = window;

	m_bSupportTouch = true;
	m_winRTWindow = ref new WinRTWindow(window, panel);
	m_winRTWindow->Initialize(window, panel, -1);
    m_initialized = false;
	UpdateForWindowSizeChange();
    return bRet;
}

bool GLView::isOpenGLReady()
{
	// TODO: need to revisit this
    return (m_window.Get() != nullptr);
}

void GLView::end()
{
	// TODO: need to implement

}

void GLView::swapBuffers()
{
	m_winRTWindow->Present();
}


void GLView::setIMEKeyboardState(bool bOpen)
{
	}

void GLView::resize(int width, int height)
{

}

void GLView::setFrameZoomFactor(float fZoomFactor)
{
    m_fFrameZoomFactor = fZoomFactor;
    resize((int) (_screenSize.width * fZoomFactor), (int) (_screenSize.height * fZoomFactor));
    centerWindow();
    Director::getInstance()->setProjection(Director::getInstance()->getProjection());
}


float GLView::getFrameZoomFactor()
{
    return m_fFrameZoomFactor;
}

void GLView::setFrameSize(float width, float height)
{
	// not implemented in WinRT. Window is always full screen
    // GLViewProtocol::setFrameSize(width, height);
}

void GLView::centerWindow()
{
	// not implemented in WinRT. Window is always full screen
}

void GLView::OnSuspending()
{
	m_running = false;

    if (m_winRTWindow)
    {
        m_winRTWindow->OnSuspending();
    }
}

void GLView::OnResume()
{
	m_running = true;
}

GLView* GLView::sharedOpenGLView()
{
    return s_pEglView;
}

int GLView::Run() 
{
	m_running = true; 

	return 0;
};


void GLView::OnRendering()
{
	if(m_running && m_initialized)
	{
		const float midnightBlue[] = { 1, 1, 1, 1.0f };
		m_winRTWindow->m_d3dContext->ClearRenderTargetView(
			m_winRTWindow->m_renderTargetView.Get(),
			midnightBlue
			);

		m_winRTWindow->m_d3dContext->ClearDepthStencilView(
			m_winRTWindow->m_depthStencilView.Get(),
			D3D11_CLEAR_DEPTH,
			1.0f,
			0
			);

		Director::sharedDirector()->mainLoop();
	}
}

void GLView::HideKeyboard(Windows::Foundation::Rect r)
{

}

void GLView::ShowKeyboard(Windows::Foundation::Rect r)
{

}

void GLView::UpdateForWindowSizeChange()
{
    float width = ConvertDipsToPixels(m_window->Bounds.Width);
    float height = ConvertDipsToPixels(m_window->Bounds.Height);

	if(!m_initialized)
    {
        m_initialized = true;
        GLViewProtocol::setFrameSize(width, height);
    }
    else
    {
        setFrameSize(width, height);
        Size designSize = getDesignResolutionSize();
        GLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
        Director::sharedDirector()->setProjection(Director::sharedDirector()->getProjection());
   }
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
