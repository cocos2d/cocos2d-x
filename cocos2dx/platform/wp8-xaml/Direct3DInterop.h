#pragma once

#include "pch.h"

#include <mutex>
#include <queue>
#include <memory>

#include "../../../Classes/AppDelegate.h"
#include "Cocos2dRenderer.h"

namespace PhoneDirect3DXamlAppComponent
{

enum PointerEventType
{
    PointerPressed,
    PointerMoved,
    PointerReleased,
};

struct PointerEvent
{
    PointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
        : m_type(type), m_args(args)
    {

    }

    PointerEventType m_type;
    Platform::Agile<Windows::UI::Core::PointerEventArgs> m_args;
};


[Windows::Foundation::Metadata::WebHostHidden]
public ref class Direct3DInterop sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
{
public:
    Direct3DInterop();

    Windows::Phone::Graphics::Interop::IDrawingSurfaceContentProvider^ CreateContentProvider();

    // IDrawingSurfaceManipulationHandler
    virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

    void UpdateForWindowSizeChange(float width, float height);
    void OnFocusChange(bool active);
    void OnResuming();
    Windows::Foundation::IAsyncAction^ OnSuspending();
    bool OnBackKeyPress();

    property Windows::Graphics::Display::DisplayOrientations WindowOrientation;

    property Windows::Foundation::Size NativeResolution;
    property Windows::Foundation::Size RenderResolution;
    property Windows::Foundation::Size WindowBounds;

protected:
    // Event Handlers
    void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
    void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

internal:
    void Connect();
    void Disconnect();
    void PrepareResources(LARGE_INTEGER presentTargetTime);
    void Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView);

private:
    void ProcessEvents();
    void AddPointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);
    Cocos2dRenderer^ m_renderer;
    Windows::Graphics::Display::DisplayOrientations mCurrentOrientation;

    std::queue<std::shared_ptr<PointerEvent>> mPointerEvents;
    std::mutex mMutex;

	// The AppDelegate for the Cocos2D app
	AppDelegate app;

    Windows::Foundation::Size m_renderResolution;
};

}
