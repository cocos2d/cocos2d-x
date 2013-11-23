//-----------------------------------------------------------------------------------------------
// Copyright (c) 2012 Andrew Garrison
//-----------------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), to deal in the Software without 
// restriction, including without limitation the rights to use, copy, modify, merge, publish, 
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or 
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-----------------------------------------------------------------------------------------------
#pragma once

#include <wrl/client.h>
#include <d3d11_1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <dwrite_1.h>
#include <wincodec.h>
#include <agile.h>
#include <DirectXMath.h>
#include "DirectXHelper.h"

#pragma warning (disable: 4449)
using namespace Windows::UI::ViewManagement;

// Helper class that initializes DirectX APIs
ref class DirectXBase abstract
{
internal:
   DirectXBase();

public:
   virtual void Initialize(Windows::UI::Core::CoreWindow^ window, Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^ panel, float dpi);
   virtual void CreateDeviceIndependentResources();
   virtual void CreateDeviceResources();
   virtual void SetDpi(float dpi);
   virtual void CreateWindowSizeDependentResources();
   virtual void UpdateForWindowSizeChange();
   virtual void Present();
   virtual float ConvertDipsToPixels(float dips);

protected private:

   Platform::Agile<Windows::UI::Core::CoreWindow>         m_window;
   Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^ m_panel;

   // Direct2D Objects
   Microsoft::WRL::ComPtr<ID2D1Factory1>                  m_d2dFactory;
   Microsoft::WRL::ComPtr<ID2D1Device>                    m_d2dDevice;
   Microsoft::WRL::ComPtr<ID2D1DeviceContext>             m_d2dContext;
   Microsoft::WRL::ComPtr<ID2D1Bitmap1>                   m_d2dTargetBitmap;

   // DirectWrite & Windows Imaging Component Objects
   Microsoft::WRL::ComPtr<IDWriteFactory1>                m_dwriteFactory;
   Microsoft::WRL::ComPtr<IWICImagingFactory2>            m_wicFactory;

   // Direct3D Objects
   Microsoft::WRL::ComPtr<ID3D11Device1>                  m_d3dDevice;
   Microsoft::WRL::ComPtr<ID3D11DeviceContext1>           m_d3dContext;
   Microsoft::WRL::ComPtr<IDXGISwapChain1>                m_swapChain;
   Microsoft::WRL::ComPtr<ID3D11RenderTargetView>         m_renderTargetView;
   Microsoft::WRL::ComPtr<ID3D11DepthStencilView>         m_depthStencilView;

   D3D_FEATURE_LEVEL                                      m_featureLevel;
   Windows::Foundation::Size                              m_renderTargetSize;
   Windows::Foundation::Rect                              m_windowBounds;
   float                                                  m_dpi;
};

#pragma warning (default: 4449)
