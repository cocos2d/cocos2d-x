#pragma once

// XXX: For some reason, this file must not be compiled
// XXX: Ask MS why
#if 0


#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include "DirectXHelper.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class Direct3DBase abstract
{
internal:
    Direct3DBase();

public:
    virtual void Initialize(Windows::UI::Core::CoreWindow^ window);
    virtual void HandleDeviceLost();
    virtual void CreateDeviceResources();
    virtual void CreateWindowSizeDependentResources();
    virtual void UpdateForWindowSizeChange();
    virtual void ReleaseResourcesForSuspending();
    //virtual void Render() = 0;
    virtual void Present();
    virtual float ConvertDipsToPixels(float dips);
    virtual void ComputeOrientationMatrices();
    virtual Windows::Foundation::Point TransformToOrientation(Windows::Foundation::Point point, bool dipsToPixels=true);

	float getOrientedWindowWidth() {return m_orientedScreenSize.Width;};
	float getOrientedWindowHeight() {return m_orientedScreenSize.Height;};

protected private:
    // Direct3D Objects.
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    // Cached renderer properties.
    D3D_FEATURE_LEVEL m_featureLevel;
    Windows::Foundation::Size m_renderTargetSize;
    Windows::Foundation::Rect m_windowBounds;
    Platform::Agile<Windows::UI::Core::CoreWindow> m_window;

    
    // Store the current Orientation of the device
    Windows::Graphics::Display::DisplayOrientations m_orientation;

    // Size of the virtual, oriented screen
    Windows::Foundation::Size m_orientedScreenSize;

    // Transforms used for rendering 2D and 3D elements in proper orientation
    DirectX::XMMATRIX m_orientationTransform3D;
    DirectX::XMMATRIX m_orientationTransform2D;
};

#endif // 0
