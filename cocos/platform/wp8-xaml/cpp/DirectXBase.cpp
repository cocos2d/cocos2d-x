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

#include "DirectXBase.h"
#include "DirectXHelper.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// Constructor.
DirectXBase::DirectXBase()
    : m_bAngleInitialized(false)
    , m_eglDisplay(nullptr)
    , m_eglSurface(nullptr)
    , m_eglContext(nullptr)
    , m_eglWindow(nullptr)
    , m_eglPhoneWindow(nullptr)
    , m_device(nullptr)
{
}

// Initialize the Direct3D resources required to run.
void DirectXBase::Initialize()
{
}

// These are the resources that depend on the device.
void DirectXBase::CreateDeviceResources()
{
}

void DirectXBase::SetDevice(ID3D11Device1* device)
{
    if(m_device)
    {
        m_device->Release();
        m_device = nullptr;
    }

    m_device = nullptr;
}

void DirectXBase::UpdateDevice(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTargetView)
{
    if (m_device != device)
    {
        CloseAngle();
        device->AddRef();
        m_device = device;

        CreateDeviceResources();

        // Force call to CreateWindowSizeDependentResources
        m_renderTargetSize.Width  = -1;
        m_renderTargetSize.Height = -1;
    }

    m_featureLevel = device->GetFeatureLevel();


    ComPtr<ID3D11Resource> renderTargetViewResource;
    renderTargetView->GetResource(&renderTargetViewResource);

    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(
        renderTargetViewResource.As(&backBuffer)
        );

    // Cache the rendertarget dimensions in our helper class for convenient use.
    D3D11_TEXTURE2D_DESC backBufferDesc;
    backBuffer->GetDesc(&backBufferDesc);

    if (m_renderTargetSize.Width  != static_cast<float>(backBufferDesc.Width) ||
        m_renderTargetSize.Height != static_cast<float>(backBufferDesc.Height))
    {
        m_renderTargetSize.Width  = static_cast<float>(backBufferDesc.Width);
        m_renderTargetSize.Height = static_cast<float>(backBufferDesc.Height);
        CreateWindowSizeDependentResources();
    }

    if(!m_bAngleInitialized)
    {
        InitializeAngle(device, context, renderTargetView);
        CreateGLResources();
    }
    else
    {
        m_eglPhoneWindow->Update(device, context, renderTargetView);
    }

    OnUpdateDevice();
}


void DirectXBase::UpdateForWindowSizeChange(float width, float height)
{
    if (width != m_windowBounds.Width || height != m_windowBounds.Height)
    {
        m_windowBounds.Width  = width;
        m_windowBounds.Height = height;
    }
}

// Allocate all memory resources that depend on the window size.
void DirectXBase::CreateWindowSizeDependentResources()
{


}

void DirectXBase::OnOrientationChanged(DisplayOrientations orientation)
{
	switch(orientation)
	{
		case DisplayOrientations::Portrait:
			m_orientationMatrix = XMMatrixIdentity();
            m_aspectRatio = m_renderTargetSize.Width / m_renderTargetSize.Height;
			break;

		case DisplayOrientations::PortraitFlipped:
			m_orientationMatrix = XMMatrixRotationZ(XM_PI);
            m_aspectRatio = m_renderTargetSize.Width / m_renderTargetSize.Height;
			break;

		case DisplayOrientations::Landscape:
			m_orientationMatrix = XMMatrixRotationZ(-XM_PIDIV2);
            m_aspectRatio = m_renderTargetSize.Height / m_renderTargetSize.Width;
			break;
			
		case DisplayOrientations::LandscapeFlipped:
			m_orientationMatrix = XMMatrixRotationZ(XM_PIDIV2);
            m_aspectRatio = m_renderTargetSize.Height / m_renderTargetSize.Width;
			break;
	}
}

void DirectXBase::Render()
{
    if(!OnRender())
    {
        eglSwapBuffers(m_eglDisplay, m_eglSurface);
    }
}

void DirectXBase::CloseAngle()
{
    eglMakeCurrent(NULL, NULL, NULL, NULL);

    if(m_eglPhoneWindow != nullptr)
    {
        m_eglPhoneWindow->Update(nullptr, nullptr, nullptr);
    }  

	if(m_eglDisplay && m_eglContext)
    {
        eglDestroyContext(m_eglDisplay, m_eglContext);
        m_eglContext = nullptr;
    }    

	if(m_eglDisplay && m_eglSurface)
    {
        eglDestroySurface(m_eglDisplay, m_eglSurface);
        m_eglSurface = nullptr;
    }

    if(m_eglDisplay)
    {
        eglTerminate(m_eglDisplay);
        m_eglDisplay = nullptr;
    }  

    if(m_device)
    {
        m_device->Release();
        m_device = nullptr;
    }

    m_eglPhoneWindow = nullptr;
    m_eglWindow = nullptr;  

    m_bAngleInitialized = false;
}

bool DirectXBase::InitializeAngle(ID3D11Device1* d3dDevice, ID3D11DeviceContext1* d3dContext, ID3D11RenderTargetView* d3dRenderTargetView)
{
	// setup EGL
	EGLint configAttribList[] = {
		EGL_RED_SIZE,       8,
		EGL_GREEN_SIZE,     8,
		EGL_BLUE_SIZE,      8,
		EGL_ALPHA_SIZE,     8,
		EGL_DEPTH_SIZE,     8,
		EGL_STENCIL_SIZE,   8,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};
	EGLint surfaceAttribList[] = {
		EGL_NONE, EGL_NONE
	};

	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

    // we need to select the correct DirectX feature level depending on the platform
    // default is D3D_FEATURE_LEVEL_9_3 Windows Phone 8.0
    ANGLE_D3D_FEATURE_LEVEL featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_3;

	switch(m_featureLevel)
	{
	case ANGLE_D3D_FEATURE_LEVEL_9_3:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_3;
		break;
				
	case ANGLE_D3D_FEATURE_LEVEL_9_2:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_2;
		break;
					
	case ANGLE_D3D_FEATURE_LEVEL_9_1:
		featureLevel = ANGLE_D3D_FEATURE_LEVEL::ANGLE_D3D_FEATURE_LEVEL_9_1;
		break;
	}		

    if(m_eglPhoneWindow == nullptr)
    {
	    DX::ThrowIfFailed(
            CreateWinPhone8XamlWindow(&m_eglPhoneWindow)
            );
    }

    m_eglPhoneWindow->Update(d3dDevice, d3dContext, d3dRenderTargetView);

    ComPtr<IUnknown> u;
    HRESULT r = m_eglPhoneWindow.As(&u);

    if(m_eglWindow == nullptr)
    { 	DX::ThrowIfFailed(
        CreateWinrtEglWindow(u.Get(), featureLevel, m_eglWindow.GetAddressOf())
        );
    }


	display = eglGetDisplay(m_eglWindow);
	if(display == EGL_NO_DISPLAY){
		//ofLogError("ofAppWinRTWindow") << "couldn't get EGL display";
		return false;
	}

	if(!eglInitialize(display, &majorVersion, &minorVersion)){
		//ofLogError("ofAppWinRTWindow") << "failed to initialize EGL";
		return false;
	}

	// Get configs
	if ( !eglGetConfigs(display, NULL, 0, &numConfigs) ){
		//ofLogError("ofAppWinRTWindow") << "failed to get configurations";
		return false;
	}

	// Choose config
	if(!eglChooseConfig(display, configAttribList, &config, 1, &numConfigs)){
		//ofLogError("ofAppWinRTWindow") << "failed to choose configuration";
		return false;
	}

    // Create a surface
    surface = eglCreateWindowSurface(display, config, m_eglWindow, surfaceAttribList);
    if(surface == EGL_NO_SURFACE){
        //ofLogError("ofAppWinRTWindow") << "failed to create EGL window surface";
        return false;
    }  

	// Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if(context == EGL_NO_CONTEXT){
		//ofLogError("ofAppWinRTWindow") << "failed to create EGL context";
		return false;
	}   

	// Make the context current
	if (!eglMakeCurrent(display, surface, surface, context)){
		//ofLogError("ofAppWinRTWindow") << "failed to make EGL context current";
		return false;
	}

	m_eglDisplay = display;
	m_eglSurface = surface;
	m_eglContext = context;

    m_bAngleInitialized = true;
    return true;
}
