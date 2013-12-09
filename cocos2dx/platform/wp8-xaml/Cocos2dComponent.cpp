#include "pch.h"
#include "Cocos2dComponent.h"
#include "Direct3DContentProvider.h"
#include "CCApplication.h"
#include "CCEGLView.h"

using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Microsoft::WRL;
using namespace Windows::Phone::Graphics::Interop;
using namespace Windows::Phone::Input::Interop;
using namespace Windows::Graphics::Display;

USING_NS_CC;

namespace PhoneDirect3DXamlAppComponent
{

Direct3DBackground::Direct3DBackground() :
    mInitialized(false), mCurrentOrientation(DisplayOrientations::None)
{

}

IDrawingSurfaceBackgroundContentProvider^ Direct3DBackground::CreateContentProvider()
{
	ComPtr<Direct3DContentProvider> provider = Make<Direct3DContentProvider>(this);
	return reinterpret_cast<IDrawingSurfaceBackgroundContentProvider^>(provider.Get());
}

// IDrawingSurfaceManipulationHandler
void Direct3DBackground::SetManipulationHost(DrawingSurfaceManipulationHost^ manipulationHost)
{
	manipulationHost->PointerPressed +=
		ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DBackground::OnPointerPressed);

	manipulationHost->PointerMoved +=
		ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DBackground::OnPointerMoved);

	manipulationHost->PointerReleased +=
		ref new TypedEventHandler<DrawingSurfaceManipulationHost^, PointerEventArgs^>(this, &Direct3DBackground::OnPointerReleased);
}

// Event Handlers
void Direct3DBackground::OnPointerPressed(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);

    PointerEvent e;
    e.type = PointerEventType::PointerPressed;
    e.args = args;
    mPointerEvents.push(e);
}

void Direct3DBackground::OnPointerMoved(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);

    PointerEvent e;
    e.type = PointerEventType::PointerMoved;
    e.args = args;
    mPointerEvents.push(e);
}

void Direct3DBackground::OnPointerReleased(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
    std::lock_guard<std::mutex> guard(mMutex);

    PointerEvent e;
    e.type = PointerEventType::PointerReleased;
    e.args = args;
    mPointerEvents.push(e);
}

// Interface With Direct3DContentProvider
HRESULT Direct3DBackground::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host, _In_ ID3D11Device1* device)
{
	return S_OK;
}

void Direct3DBackground::Disconnect()
{
	// m_renderer = nullptr;
}

HRESULT Direct3DBackground::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Inout_ DrawingSurfaceSizeF* desiredRenderTargetSize)
{
	return S_OK;
}

void Direct3DBackground::ProcessEvents()
{
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    std::lock_guard<std::mutex> guard(mMutex);

    while(!mPointerEvents.empty())
    {
        PointerEvent e = mPointerEvents.front();
        mPointerEvents.pop();
        switch(e.type)
        {
        case PointerEventType::PointerPressed:
        	pEGLView->OnPointerPressed(e.args.Get());
            break;
        case PointerEventType::PointerMoved:
        	pEGLView->OnPointerMoved(e.args.Get());
            break;           
        case PointerEventType::PointerReleased:
        	pEGLView->OnPointerReleased(e.args.Get());
            break;
        }
    }
}


HRESULT Direct3DBackground::Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
    if(!mInitialized)
    {
        mInitialized = true;
        CCEGLView* pEGLView = new CCEGLView();
	    pEGLView->Create(device, context, renderTargetView);
 		pEGLView->UpdateOrientation(mCurrentOrientation);
        pEGLView->setViewName("Cocos2d-x");
        CCApplication::sharedApplication()->run();
    }
    else
    {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	    if(mCurrentOrientation != WindowOrientation)
	    {
		    mCurrentOrientation = WindowOrientation;
		    pEGLView->UpdateOrientation(mCurrentOrientation);
	    }

        ProcessEvents();
	    pEGLView->UpdateDevice(device, context, renderTargetView);
	    pEGLView->Render();
    }
    RequestAdditionalFrame();
    return S_OK;
}

}