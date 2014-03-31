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
#include "Direct3DContentProvider.h"

using namespace PhoneDirect3DXamlAppComponent;

Direct3DContentProvider::Direct3DContentProvider(Direct3DInterop^ controller) :
    m_controller(controller)
{
}

// IDrawingSurfaceContentProviderNative interface
HRESULT Direct3DContentProvider::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host)
{
    m_host = host;
    Initialize();
    m_controller->Connect();

    return S_OK;
}

void Direct3DContentProvider::Disconnect()
{
    m_controller->Disconnect();
    m_host = nullptr;
    m_synchronizedTexture = nullptr;
    m_d3dDevice = nullptr;
    m_d3dContext = nullptr;
    m_renderTarget = nullptr;
    m_renderTargetView = nullptr;
}

HRESULT Direct3DContentProvider::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty)
{
    m_controller->PrepareResources(*presentTargetTime);
    *contentDirty = true;

    return S_OK;
}

HRESULT Direct3DContentProvider::GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle)
{
    if (!size || !synchronizedTexture || !textureSubRectangle) return E_INVALIDARG;

    HRESULT hr = S_OK;

    if (!m_synchronizedTexture ||
        m_renderTargetSize.Width != m_controller->WindowBounds.Width ||
        m_renderTargetSize.Height != m_controller->WindowBounds.Height)
    {
        UpdateForWindowSizeChange(m_controller->WindowBounds.Width, m_controller->WindowBounds.Height);
        hr = InitializeTexture();
    }

    // Draw to the texture.
    if (SUCCEEDED(hr))
    {
        hr = m_synchronizedTexture->BeginDraw();
        
        if (SUCCEEDED(hr))
        {
            m_controller->Draw(m_d3dDevice.Get(), m_d3dContext.Get(), m_renderTargetView.Get());
            hr = m_synchronizedTexture->EndDraw();
        }
    }

    // Set output parameters.
    if (SUCCEEDED(hr))
    {    
        textureSubRectangle->left = 0.0f;
        textureSubRectangle->top = 0.0f;
	    textureSubRectangle->right = static_cast<FLOAT>(size->width);
	    textureSubRectangle->bottom = static_cast<FLOAT>(size->height);

        hr = m_synchronizedTexture.CopyTo(synchronizedTexture);

        if (SUCCEEDED(hr))
        {
            hr = m_host->RequestAdditionalFrame();
        }
    }

    return hr;
}

HRESULT Direct3DContentProvider::InitializeTexture()
{
    return m_host->CreateSynchronizedTexture(m_renderTarget.Get(), &m_synchronizedTexture);
}
