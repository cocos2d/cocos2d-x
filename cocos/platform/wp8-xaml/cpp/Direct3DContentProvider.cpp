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
#include "Direct3DInterop.h"

using namespace PhoneDirect3DXamlAppComponent;

Direct3DContentProvider::Direct3DContentProvider(Direct3DInterop^ controller) :
	m_controller(controller)
{
	m_controller->RequestAdditionalFrame += ref new RequestAdditionalFrameHandler([=] ()
		{
			if (m_host)
			{
				m_host->RequestAdditionalFrame();
			}
		});

	m_controller->RecreateSynchronizedTexture += ref new RecreateSynchronizedTextureHandler([=]()
	{
		if (m_host)
		{
			m_host->CreateSynchronizedTexture(m_controller->GetTexture(), &m_synchronizedTexture);
		}
	});
}

// IDrawingSurfaceContentProviderNative interface
HRESULT Direct3DContentProvider::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host)
{
	m_host = host;

	return m_controller->Connect(host);
}

void Direct3DContentProvider::Disconnect()
{
	m_controller->Disconnect();
	m_host = nullptr;
	m_synchronizedTexture = nullptr;
}

HRESULT Direct3DContentProvider::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty)
{
	return m_controller->PrepareResources(presentTargetTime, contentDirty);
}

HRESULT Direct3DContentProvider::GetTexture(_In_ const DrawingSurfaceSizeF* size, _Out_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Out_ DrawingSurfaceRectF* textureSubRectangle)
{
	HRESULT hr = S_OK;

	if (!m_synchronizedTexture)
{
		hr = m_host->CreateSynchronizedTexture(m_controller->GetTexture(), &m_synchronizedTexture);
}

	// Set output parameters.
	textureSubRectangle->left = 0.0f;
	textureSubRectangle->top = 0.0f;
	textureSubRectangle->right = static_cast<FLOAT>(size->width);
	textureSubRectangle->bottom = static_cast<FLOAT>(size->height);

	m_synchronizedTexture.CopyTo(synchronizedTexture);

	// Draw to the texture.
	if (SUCCEEDED(hr))
	{
		hr = m_synchronizedTexture->BeginDraw();

		if (SUCCEEDED(hr))
		{
			hr = m_controller->GetTexture(size, synchronizedTexture, textureSubRectangle);
		}

		m_synchronizedTexture->EndDraw();
	}

	return hr;
}