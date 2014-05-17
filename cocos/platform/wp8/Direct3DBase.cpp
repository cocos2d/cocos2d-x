// XXX: For some reason, this file must not be compiled
// XXX: Ask MS why
#if 0

#include "Direct3DBase.h"


using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// Constructor.
Direct3DBase::Direct3DBase()
{
}

// Initialize the Direct3D resources required to run.
void Direct3DBase::Initialize(CoreWindow^ window)
{
    m_window = window;

    CreateDeviceResources();
    CreateWindowSizeDependentResources();
}

// This method is called in the event handler for the SizeChanged event.
void Direct3DBase::UpdateForWindowSizeChange()
{
    if (m_window == nullptr)
        return;
    if (m_window->Bounds.Width  != m_windowBounds.Width ||
        m_window->Bounds.Height != m_windowBounds.Height ||
        m_orientation != DisplayProperties::CurrentOrientation )
    {
        ID3D11RenderTargetView* nullViews[] = {nullptr};
        m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
        m_renderTargetView = nullptr;
        m_depthStencilView = nullptr;
        m_d3dContext->Flush();
        CreateWindowSizeDependentResources();
    }
}


// Recreate all device resources and set them back to the current state.
void Direct3DBase::HandleDeviceLost()
{
    // Reset these member variables to ensure that UpdateForWindowSizeChange recreates all resources.
    m_windowBounds.Width = 0;
    m_windowBounds.Height = 0;
    m_swapChain = nullptr;

    CreateDeviceResources();
    UpdateForWindowSizeChange();
}

// These are the resources that depend on the device.
void Direct3DBase::CreateDeviceResources()
{
    // This flag adds support for surfaces with a different color channel ordering
    // than the API default. It is required for compatibility with Direct2D.
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    // If the project is in a debug build, enable debugging via SDK Layers with this flag.
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // This array defines the set of DirectX hardware feature levels this app will support.
    // Note the ordering should be preserved.
    // Don't forget to declare your application's minimum required feature level in its
    // description.  All applications are assumed to support 9.1 unless otherwise stated.
    D3D_FEATURE_LEVEL featureLevels[] = 
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3
    };

    // Create the Direct3D 11 API device object and a corresponding context.
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    DX::ThrowIfFailed(
        D3D11CreateDevice(
        nullptr, // Specify nullptr to use the default adapter.
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags, // Set set debug and Direct2D compatibility flags.
        featureLevels, // List of feature levels this app can support.
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION.
        &device, // Returns the Direct3D device created.
        &m_featureLevel, // Returns feature level of device created.
        &context // Returns the device immediate context.
        )
        );

    // Get the Direct3D 11.1 API device and context interfaces.
    DX::ThrowIfFailed(
        device.As(&m_d3dDevice)
        );

    DX::ThrowIfFailed(
        context.As(&m_d3dContext)
        );
}

// Allocate all memory resources that depend on the window size.
void Direct3DBase::CreateWindowSizeDependentResources()
{
    m_windowBounds = m_window->Bounds;

    // Calculate the necessary swap chain and render target size in pixels.
    m_renderTargetSize.Width = ConvertDipsToPixels(m_windowBounds.Width);
    m_renderTargetSize.Height = ConvertDipsToPixels(m_windowBounds.Height);

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
    swapChainDesc.Width = static_cast<UINT>(m_renderTargetSize.Width); // Match the size of the window.
    swapChainDesc.Height = static_cast<UINT>(m_renderTargetSize.Height);
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // This is the most common swap chain format.
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1; // Don't use multi-sampling.
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1; // On phone, only single buffering is supported.
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH; // On phone, only stretch and aspect-ratio stretch scaling are allowed.
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // On phone, no swap effects are supported.
    swapChainDesc.Flags = 0;

    ComPtr<IDXGIDevice1> dxgiDevice;
    DX::ThrowIfFailed(
        m_d3dDevice.As(&dxgiDevice)
        );

    ComPtr<IDXGIAdapter> dxgiAdapter;
    DX::ThrowIfFailed(
        dxgiDevice->GetAdapter(&dxgiAdapter)
        );

    ComPtr<IDXGIFactory2> dxgiFactory;
    DX::ThrowIfFailed(
        dxgiAdapter->GetParent(
        __uuidof(IDXGIFactory2), 
        &dxgiFactory
        )
        );

    Windows::UI::Core::CoreWindow^ window = m_window.Get();
    DX::ThrowIfFailed(
        dxgiFactory->CreateSwapChainForCoreWindow(
        m_d3dDevice.Get(),
        reinterpret_cast<IUnknown*>(window),
        &swapChainDesc,
        nullptr, // Allow on all displays.
        &m_swapChain
        )
        );

    // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
    // ensures that the application will only render after each VSync, minimizing power consumption.
    DX::ThrowIfFailed(
        dxgiDevice->SetMaximumFrameLatency(1)
        );

    // Create a render target view of the swap chain back buffer.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(
        m_swapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        &backBuffer
        )
        );

    DX::ThrowIfFailed(
        m_d3dDevice->CreateRenderTargetView(
        backBuffer.Get(),
        nullptr,
        &m_renderTargetView
        )
        );

    // Create a depth stencil view.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        static_cast<UINT>(m_renderTargetSize.Width),
        static_cast<UINT>(m_renderTargetSize.Height),
        1,
        1,
        D3D11_BIND_DEPTH_STENCIL
        );

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(
        m_d3dDevice->CreateTexture2D(
        &depthStencilDesc,
        nullptr,
        &depthStencil
        )
        );

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(
        m_d3dDevice->CreateDepthStencilView(
        depthStencil.Get(),
        &depthStencilViewDesc,
        &m_depthStencilView
        )
        );

    // Set the rendering viewport to target the entire window.
    CD3D11_VIEWPORT viewport(
        0.0f,
        0.0f,
        m_renderTargetSize.Width,
        m_renderTargetSize.Height
        );

    m_d3dContext->RSSetViewports(1, &viewport);

    ComputeOrientationMatrices();
}

void Direct3DBase::ReleaseResourcesForSuspending()
{
    // Phone applications operate in a memory-constrained environment, so when entering
    // the background it is a good idea to free memory-intensive objects that will be
    // easy to restore upon reactivation. The swapchain and backbuffer are good candidates
    // here, as they consume a large amount of memory and can be reinitialized quickly.
    m_swapChain = nullptr;
    m_renderTargetView = nullptr;
    m_depthStencilView = nullptr;
}

// Method to deliver the final image to the display.
void Direct3DBase::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // Discard the contents of the render target.
    // This is a valid operation only when the existing contents will be entirely
    // overwritten. If dirty or scroll rects are used, this call should be removed.
    m_d3dContext->DiscardView(m_renderTargetView.Get());

    // Discard the contents of the depth stencil.
    m_d3dContext->DiscardView(m_depthStencilView.Get());

    // If the device was removed either by a disconnect or a driver upgrade, we 
    // must recreate all device resources.
    if (hr == DXGI_ERROR_DEVICE_REMOVED)
    {
        HandleDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Method to convert a length in device-independent pixels (DIPs) to a length in physical pixels.
float Direct3DBase::ConvertDipsToPixels(float dips)
{
    static const float dipsPerInch = 96.0f;
    return floor(dips * DisplayProperties::LogicalDpi / dipsPerInch + 0.5f); // Round to nearest integer.
}

// Method to compute the matrices that will need to be used for rotating whatever we draw.
void Direct3DBase::ComputeOrientationMatrices()
{
    // Store the current device orientation
    m_orientation = DisplayProperties::CurrentOrientation;

    // Generate the matrix transformations for rendering to the new orientation.
    switch (m_orientation)
    {
    case DisplayOrientations::Portrait:
        // Portrait is default for WP8, so no changes need to be made here
        // Just use Identity Matrices
        m_orientationTransform2D = XMMatrixIdentity();
        m_orientationTransform3D = XMMatrixIdentity();
        m_orientedScreenSize = m_renderTargetSize;
        break;
    case DisplayOrientations::Landscape:
        //2D: 90-degree Rotation + translation of origin
        m_orientationTransform2D = XMMatrixMultiply(
            XMMatrixRotationZ(XM_PIDIV2),
            XMMatrixTranslation(m_renderTargetSize.Width,0 ,0));
        //3D: 90-degree Z-rotation
        m_orientationTransform3D = XMMATRIX( 
            0.0f, -1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f );
        m_orientedScreenSize = Size(m_renderTargetSize.Height, m_renderTargetSize.Width);
        break;
    case DisplayOrientations::PortraitFlipped:
        //This is not supported on the phone, but we leave the math here, just in case...
        //2D: 180-degree Rotation + translation of origin
        m_orientationTransform2D = XMMatrixMultiply(
            XMMatrixRotationZ(XM_PI),
            XMMatrixTranslation(m_renderTargetSize.Width,m_renderTargetSize.Height,0));
        //3D: // 180-degree Z-rotation
        m_orientationTransform3D = XMMATRIX( 
            -1.0f,  0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 1.0f
            );
        m_orientedScreenSize = m_renderTargetSize;
        break;
    case DisplayOrientations::LandscapeFlipped:
        //2D: 270-degree Rotation + translation of origin
        m_orientationTransform2D = XMMatrixMultiply(
            XMMatrixRotationZ(3 * XM_PIDIV2),
            XMMatrixTranslation(0,m_renderTargetSize.Height,0));
        //3D: 270-degree Z-rotation
        m_orientationTransform3D = XMMATRIX( 
            0.0f, 1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f );
        m_orientedScreenSize = Size(m_renderTargetSize.Height, m_renderTargetSize.Width);
        break;
    default:
        throw ref new Platform::FailureException();
        break;
    }
}

Point Direct3DBase::TransformToOrientation(Point point, bool dipsToPixels)
{
    Point returnValue;

    switch (m_orientation)
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
		returnValue = Point(m_windowBounds.Height - point.Y, point.X);
        break;
    default:
        throw ref new Platform::FailureException();
        break;
    }

	return dipsToPixels ? Point(ConvertDipsToPixels(returnValue.X),
                                ConvertDipsToPixels(returnValue.Y)) 
                        : returnValue;
}

#endif // 0
