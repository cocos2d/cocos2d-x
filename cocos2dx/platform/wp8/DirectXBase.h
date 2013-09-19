#pragma once

#include "DirectXHelper.h"
#include <wrl/client.h>
#include <d3d11_1.h>
#include <agile.h>

// Helper class that initializes DirectX APIs for 3D rendering.
ref class DirectXBase abstract
{
internal:
	DirectXBase();

public:
	virtual void Initialize(Windows::UI::Core::CoreWindow^ window, float dpi);
	virtual void HandleDeviceLost();
	virtual void CreateDeviceResources();
	virtual void CreateWindowSizeDependentResources();
	virtual void UpdateForWindowSizeChange();
	virtual void ReleaseResourcesForSuspending();
	virtual void Present();
	virtual float ConvertDipsToPixels(float dips);
	virtual void SetDpi(float dpi);

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
	float m_dpi;

};