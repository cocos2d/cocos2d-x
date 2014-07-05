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

#include <wrl/client.h>
#include <mutex>
#include <queue>
#include <memory>
#include "Cocos2dRenderer.h"
#include "InputEvent.h"
#include <DrawingSurfaceNative.h>


namespace PhoneDirect3DXamlAppComponent
{

public delegate void RequestAdditionalFrameHandler();
public delegate void RecreateSynchronizedTextureHandler();

[Windows::Foundation::Metadata::WebHostHidden]
public ref class Direct3DInterop sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
{
public:
    Direct3DInterop();

	Windows::Phone::Graphics::Interop::IDrawingSurfaceBackgroundContentProvider^ CreateContentProvider();

    // IDrawingSurfaceManipulationHandler
    virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

	event RequestAdditionalFrameHandler^ RequestAdditionalFrame;
	event RecreateSynchronizedTextureHandler^ RecreateSynchronizedTexture;

	property Windows::Foundation::Size WindowBounds;
	property Windows::Foundation::Size NativeResolution;
	property Windows::Foundation::Size RenderResolution
	{
		Windows::Foundation::Size get(){ return m_renderResolution; }
		void set(Windows::Foundation::Size renderResolution);
	}

    void UpdateForWindowSizeChange(float width, float height);
    Windows::Foundation::IAsyncAction^ OnSuspending();

    void OnBackKeyPress();
    void OnCocos2dKeyEvent(Cocos2dKeyEvent key);
    void OnCocos2dKeyEvent(Cocos2dKeyEvent key, Platform::String^ text);
    void OnCocos2dEditboxEvent(Platform::Object^ sender, Platform::String^ args, Windows::Foundation::EventHandler<Platform::String^>^ handler);

    void SetCocos2dEventDelegate(Cocos2dEventDelegate^ delegate);
    void SetCocos2dMessageBoxDelegate(Cocos2dMessageBoxDelegate ^ delegate);
    void SetCocos2dEditBoxDelegate(Cocos2dEditBoxDelegate ^ delegate);
	bool SendCocos2dEvent(Cocos2dEvent event);


protected:
    // Event Handlers
    void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

internal:
	HRESULT STDMETHODCALLTYPE Connect(_In_ IDrawingSurfaceRuntimeHostNative* host);
	void STDMETHODCALLTYPE Disconnect();
	HRESULT STDMETHODCALLTYPE PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty);
	HRESULT STDMETHODCALLTYPE GetTexture(_In_ const DrawingSurfaceSizeF* size, _Inout_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Inout_ DrawingSurfaceRectF* textureSubRectangle);
	ID3D11Texture2D* GetTexture();

private:
    Cocos2dRenderer^ m_renderer;
	Windows::Foundation::Size m_renderResolution;

    Cocos2dEventDelegate^ m_delegate;
    Cocos2dMessageBoxDelegate^ m_messageBoxDelegate;
    Cocos2dEditBoxDelegate^ m_editBoxDelegate;

};

}
