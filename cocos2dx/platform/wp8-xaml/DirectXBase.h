#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include "DirectXHelper.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "../src/common/winrtangle.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class DirectXBase abstract
{
internal:
    DirectXBase();

    virtual void Initialize();
    virtual void CreateDeviceResources();
    virtual void UpdateDevice(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTargetView);
    virtual void UpdateForWindowSizeChange(float width, float height);
    virtual void CreateWindowSizeDependentResources();
	virtual void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation);

    virtual void CreateGLResources() = 0;

    void Render();

protected:

    // return true if eglSwapBuffers was called by OnRender
	virtual bool OnRender() = 0;
    virtual void OnUpdateDevice() = 0;
    bool InitializeAngle();
    void CloseAngle();

protected private:
    // Direct3D Objects.
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3dRenderTargetView;
	D3D_FEATURE_LEVEL m_featureLevel;

    // Cached renderer properties.
    Windows::Foundation::Size m_renderTargetSize;
    Windows::Foundation::Rect m_windowBounds;
	Windows::Graphics::Display::DisplayOrientations m_orientation;

    // Angle EGL 
    bool m_bAngleInitialized;
	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;
	Microsoft::WRL::ComPtr<IWinrtEglWindow> m_eglWindow;
	Microsoft::WRL::ComPtr<IWinPhone8XamlD3DWindow> m_eglPhoneWindow;
    DirectX::XMMATRIX m_orientationMatrix;
    float m_aspectRatio;
};