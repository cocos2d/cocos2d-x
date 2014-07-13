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
#pragma once

#include "InputEvent.h"
#include "Direct3DBase.h"
#include "platform/wp8-xaml/cpp/IWP8Win.h"

class WP8Window;
 
ref class Cocos2dRenderer : public Direct3DBase
{
protected private:
	Cocos2dRenderer();

public:	
	// Direct3DBase methods.
	virtual void Render() override;
    virtual void CreateWindowSizeDependentResources() override;

    void OnBackButton();
    void OnKeyPressed(Platform::String^ text);
    void OnCocos2dKeyEvent(PhoneDirect3DXamlAppComponent::Cocos2dKeyEvent event);
    void SetXamlEventDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEventDelegate^ delegate);
    void SetXamlMessageBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dMessageBoxDelegate^ delegate);
    void SetXamlEditBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEditBoxDelegate^ delegate);

    Windows::Foundation::IAsyncAction^ OnSuspending();
    void Connect();
    void Disconnect();

protected private:
    bool m_loadingComplete;
    bool mInitialized;

    PhoneDirect3DXamlAppComponent::Cocos2dEventDelegate^ m_delegate;
    PhoneDirect3DXamlAppComponent::Cocos2dMessageBoxDelegate^ m_messageBoxDelegate;
    PhoneDirect3DXamlAppComponent::Cocos2dEditBoxDelegate^ m_editBoxDelegate;

protected private:
	static Cocos2dRenderer^ m_instance;
	WP8Window* m_wp8window;
    
public:
	static Cocos2dRenderer^ GetInstance()
	{
		return m_instance;
	}

	friend class WP8Window;
};

class WP8Window : public cocos2d::IWP8Win
{
	virtual ID3D11Device1* GetDevice()
	{
		return Cocos2dRenderer::GetInstance()->m_d3dDevice.Get();
	}

	virtual ID3D11DeviceContext1* GetContext()
	{
		return Cocos2dRenderer::GetInstance()->m_d3dContext.Get();
	}

	virtual ID3D11DepthStencilView* GetDepthStencilView()
	{
		return Cocos2dRenderer::GetInstance()->m_depthStencilView.Get();
	}

	virtual ID3D11RenderTargetView*const* GetRenderTargetView() const
	{
		return Cocos2dRenderer::GetInstance()->m_renderTargetView.GetAddressOf();
	}
};