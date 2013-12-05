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
USING_NS_CC;

namespace PhoneDirect3DXamlAppComponent
{

Direct3DBackground::Direct3DBackground() :
    mInitialized(false)
{
    OrientationChanged = false;
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
	CCEGLView::sharedOpenGLView()->OnPointerPressed(args);
}

void Direct3DBackground::OnPointerMoved(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnPointerMoved(args);
}

void Direct3DBackground::OnPointerReleased(DrawingSurfaceManipulationHost^ sender, PointerEventArgs^ args)
{
	CCEGLView::sharedOpenGLView()->OnPointerReleased(args);
}

// Interface With Direct3DContentProvider
HRESULT Direct3DBackground::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host, _In_ ID3D11Device1* device)
{
#if 0
    m_renderer = ref new CubeRenderer();
    m_renderer->Initialize(device);
    m_renderer->UpdateForWindowSizeChange(WindowBounds.Width, WindowBounds.Height);

#endif // 0

	return S_OK;
}

void Direct3DBackground::Disconnect()
{
	// m_renderer = nullptr;
}

HRESULT Direct3DBackground::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Inout_ DrawingSurfaceSizeF* desiredRenderTargetSize)
{
    // m_renderer->Update(0.0f, 0.0f);

	desiredRenderTargetSize->width = RenderResolution.Width;
	desiredRenderTargetSize->height = RenderResolution.Height;

	return S_OK;
}

HRESULT Direct3DBackground::Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
    if(!mInitialized)
    {
        mInitialized = true;
        CCEGLView* pEGLView = new CCEGLView();
	    pEGLView->Create(device, context, renderTargetView);
        pEGLView->UpdateForWindowSizeChange(WindowBounds.Width, WindowBounds.Height);
        pEGLView->setViewName("HelloCpp");
        CCApplication::sharedApplication()->run();
    }
    else
    {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	    if(OrientationChanged)
	    {
		    OrientationChanged = false;
		    pEGLView->UpdateForWindowSizeChange(WindowBounds.Width, WindowBounds.Height);
	    }

	    pEGLView->UpdateDevice(device, context, renderTargetView);
	    pEGLView->Render();
	    RequestAdditionalFrame();
    }
    return S_OK;
}

}