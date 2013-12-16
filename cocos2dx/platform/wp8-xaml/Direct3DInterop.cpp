#include "pch.h"

#include "Direct3DInterop.h"
#include "Direct3DContentProvider.h"

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;
using namespace Windows::Graphics::Display;
using namespace DirectX;

namespace PhoneDirect3DXamlAppComponent
{

Direct3DInterop::Direct3DInterop() 
    : mCurrentOrientation(DisplayOrientations::Portrait)
{
    m_renderer = ref new Cocos2dRenderer();
}


IDrawingSurfaceContentProvider^ Direct3DInterop::CreateContentProvider()
{
    ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
    return reinterpret_cast<IDrawingSurfaceContentProvider^>(provider.Get());
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

void Direct3DInterop::OnFocusChange(bool active)
{
   m_renderer->OnFocusChange(active);
}

void Direct3DInterop::OnResuming()
{
    m_renderer->OnResuming();
}

IAsyncAction^ Direct3DInterop::OnSuspending()
{
    return m_renderer->OnSuspending();
}

bool Direct3DInterop::OnBackKeyPress()
{
    return m_renderer->OnBackKeyPress();
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

void Direct3DInterop::AddPointerEvent(PointerEventType type, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);
    std::shared_ptr<PointerEvent> e(new PointerEvent(type, args));
    mPointerEvents.push(e);
}

void Direct3DInterop::ProcessEvents()
{
    std::lock_guard<std::mutex> guard(mMutex);

    while(!mPointerEvents.empty())
    {
        PointerEvent* e = mPointerEvents.front().get();
        switch(e->m_type)
        {
        case PointerEventType::PointerPressed:
        	m_renderer->OnPointerPressed(e->m_args.Get());
            break;
        case PointerEventType::PointerMoved:
        	m_renderer->OnPointerMoved(e->m_args.Get());
            break;           
        case PointerEventType::PointerReleased:
        	m_renderer->OnPointerReleased(e->m_args.Get());
            break;
        }

        mPointerEvents.pop();
    }
}

// Interface With Direct3DContentProvider
void Direct3DInterop::Connect()
{
    m_renderer->Connect();
}

void Direct3DInterop::Disconnect()
{
    m_renderer->Disconnect();
}

void Direct3DInterop::PrepareResources(LARGE_INTEGER presentTargetTime)
{
}

void Direct3DInterop::Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
    m_renderer->UpdateDevice(device, context, renderTargetView);
    if(mCurrentOrientation != WindowOrientation)
    {
        mCurrentOrientation = WindowOrientation;
        m_renderer->OnOrientationChanged(mCurrentOrientation);
    }
    ProcessEvents();
    m_renderer->Render();
}

}
