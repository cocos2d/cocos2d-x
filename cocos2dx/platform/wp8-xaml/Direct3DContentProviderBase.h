#pragma once

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>

// Helper class that initializes DirectX APIs for 3D rendering.
class Direct3DContentProviderBase abstract
{
public:
    Direct3DContentProviderBase();
    virtual void Initialize();
    virtual void CreateDeviceResources();
    virtual void CreateWindowSizeDependentResources();
    virtual void UpdateForWindowSizeChange(float width, float height);

protected:
    // Direct3D Objects.
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_renderTarget;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

    // Cached renderer properties.
    D3D_FEATURE_LEVEL m_featureLevel;
    Windows::Foundation::Size m_renderTargetSize;
    Windows::Foundation::Rect m_windowBounds;
};