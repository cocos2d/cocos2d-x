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
#include "DirectXBase.h"

class AppDelegate;
 
ref class Cocos2dRenderer sealed : public DirectXBase
{
public:
	Cocos2dRenderer();

	// Direct3DBase methods.
	virtual void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation) override;
	virtual bool OnRender() override;
    virtual void CreateGLResources() override;

    void OnBackButton();
    void OnKeyPressed(Platform::String^ text);
    void OnCocos2dKeyEvent(PhoneDirect3DXamlAppComponent::Cocos2dKeyEvent event);
    void SetXamlEventDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEventDelegate^ delegate);
    void SetXamlMessageBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dMessageBoxDelegate^ delegate);
    void SetXamlEditBoxDelegate(PhoneDirect3DXamlAppComponent::Cocos2dEditBoxDelegate^ delegate);

    Windows::Foundation::IAsyncAction^ OnSuspending();
    void Connect();
    void Disconnect();

protected:
    virtual void OnUpdateDevice() override;

private:

    bool m_loadingComplete;
    bool mInitialized;

    PhoneDirect3DXamlAppComponent::Cocos2dEventDelegate^ m_delegate;
    PhoneDirect3DXamlAppComponent::Cocos2dMessageBoxDelegate^ m_messageBoxDelegate;
    PhoneDirect3DXamlAppComponent::Cocos2dEditBoxDelegate^ m_editBoxDelegate;

	// The AppDelegate for the Cocos2D app
	AppDelegate* mApp;
};
