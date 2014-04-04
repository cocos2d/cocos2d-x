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
#include "Direct3DInterop.h"
#include "Direct3DContentProvider.h"
#include "EditBoxEvent.h"

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;
using namespace Windows::Graphics::Display;
using namespace DirectX;
using namespace PhoneDirect3DXamlAppComponent;

namespace PhoneDirect3DXamlAppComponent
{

Direct3DInterop::Direct3DInterop() 
    : mCurrentOrientation(DisplayOrientations::Portrait), m_delegate(nullptr)
{
    m_renderer = ref new Cocos2dRenderer();
}

IDrawingSurfaceBackgroundContentProvider^ Direct3DInterop::CreateContentProvider()
{
	ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
	return reinterpret_cast<IDrawingSurfaceBackgroundContentProvider^>(provider.Get());
}


// Interface With Direct3DContentProvider
HRESULT Direct3DInterop::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host, _In_ ID3D11Device1* device)
{
    //m_renderer->SetDevice(device);
    return S_OK;
}

void Direct3DInterop::Disconnect()
{
    std::lock_guard<std::mutex> guard(mRenderingMutex);
    m_renderer->Disconnect();
}

// IDrawingSurfaceManipulationHandler
void Direct3DInterop::SetManipulationHost(DrawingSurfaceManipulationHost^ manipulationHost)
{
    manipulationHost->PointerPressed +=
        ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerPressed);

    manipulationHost->PointerMoved +=
        ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerMoved);

    manipulationHost->PointerReleased +=
        ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DInterop::OnPointerReleased);
}

void Direct3DInterop::UpdateForWindowSizeChange(float width, float height)
{
    m_renderer->UpdateForWindowSizeChange(width, height);
}


IAsyncAction^ Direct3DInterop::OnSuspending()
{
    return m_renderer->OnSuspending();
}

void Direct3DInterop::OnBackKeyPress()
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<BackButtonEvent> e(new BackButtonEvent());
    mInputEvents.push(e);
}

// Pointer Event Handlers. We need to queue up pointer events to pass them to the drawing thread
void Direct3DInterop::OnPointerPressed(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    AddPointerEvent(PointerEventType::PointerPressed, args);
}


void Direct3DInterop::OnPointerMoved(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    AddPointerEvent(PointerEventType::PointerMoved, args);
}

void Direct3DInterop::OnPointerReleased(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    AddPointerEvent(PointerEventType::PointerReleased, args);
}

void Direct3DInterop::OnCocos2dKeyEvent(Cocos2dKeyEvent key)
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<KeyboardEvent> e(new KeyboardEvent(key));
    mInputEvents.push(e);
}


void Direct3DInterop::OnCocos2dKeyEvent(Cocos2dKeyEvent key, Platform::String^ text)
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<KeyboardEvent> e(new KeyboardEvent(key,text));
    mInputEvents.push(e);
}


void Direct3DInterop::AddPointerEvent(PointerEventType type, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<PointerEvent> e(new PointerEvent(type, args));
    mInputEvents.push(e);
}

void Direct3DInterop::OnCocos2dEditboxEvent(Object^ sender, Platform::String^ args, Windows::Foundation::EventHandler<Platform::String^>^ handler)
{
	std::lock_guard<std::mutex> guard(mMutex);
	std::shared_ptr<EditBoxEvent> e(new EditBoxEvent(sender, args, handler));
	mInputEvents.push(e);
}

void Direct3DInterop::ProcessEvents()
{
    std::lock_guard<std::mutex> guard(mMutex);

    while(!mInputEvents.empty())
    {
        InputEvent* e = mInputEvents.front().get();
        e->execute(m_renderer);
        mInputEvents.pop();
    }
}


HRESULT Direct3DInterop::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Inout_ DrawingSurfaceSizeF* desiredRenderTargetSize)
{
	desiredRenderTargetSize->width = WindowBounds.Width;
	desiredRenderTargetSize->height = WindowBounds.Height;
	return S_OK;
}

HRESULT Direct3DInterop::Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
    std::lock_guard<std::mutex> guard(mRenderingMutex);

    m_renderer->UpdateDevice(device, context, renderTargetView);
#if 0
    if(mCurrentOrientation != WindowOrientation)
    {
        mCurrentOrientation = WindowOrientation;
        m_renderer->OnOrientationChanged(mCurrentOrientation);
    }  
#endif // 0

    ProcessEvents();
    m_renderer->Render();
	RequestAdditionalFrame();
	return S_OK;
}

void Direct3DInterop::SetCocos2dEventDelegate(Cocos2dEventDelegate^ delegate) 
{ 
    m_delegate = delegate; 
    m_renderer->SetXamlEventDelegate(delegate);
}

void Direct3DInterop::SetCocos2dMessageBoxDelegate(Cocos2dMessageBoxDelegate ^ delegate)
{
    m_messageBoxDelegate = delegate;
    m_renderer->SetXamlMessageBoxDelegate(delegate);
}

void Direct3DInterop::SetCocos2dEditBoxDelegate(Cocos2dEditBoxDelegate ^ delegate)
{
    m_editBoxDelegate = delegate;
    m_renderer->SetXamlEditBoxDelegate(delegate);
}


bool Direct3DInterop::SendCocos2dEvent(Cocos2dEvent event)
{
    if(m_delegate)
    {
        m_delegate->Invoke(event);
        return true;
    }
    return false;
}

}