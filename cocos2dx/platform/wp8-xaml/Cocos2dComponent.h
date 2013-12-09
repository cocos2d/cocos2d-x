#pragma once

#include "pch.h"
#include <DrawingSurfaceNative.h>
#include <mutex>
#include <queue>

#include "../../../Classes/AppDelegate.h"

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
    PointerEventType type;
    Platform::Agile<Windows::UI::Core::PointerEventArgs> args;
};


public delegate void RequestAdditionalFrameHandler();

[Windows::Foundation::Metadata::WebHostHidden]
public ref class Direct3DBackground sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
{
public:
	Direct3DBackground();

	Windows::Phone::Graphics::Interop::IDrawingSurfaceBackgroundContentProvider^ CreateContentProvider();

	// IDrawingSurfaceManipulationHandler
	virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

	event RequestAdditionalFrameHandler^ RequestAdditionalFrame;

    property Windows::Graphics::Display::DisplayOrientations WindowOrientation;

protected:
	// Event Handlers
	void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

internal:
	HRESULT Connect(_In_ IDrawingSurfaceRuntimeHostNative* host, _In_ ID3D11Device1* device);
	void Disconnect();

	HRESULT PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Inout_ DrawingSurfaceSizeF* desiredRenderTargetSize);
	HRESULT Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView);

private:

    void ProcessEvents();

    Windows::Graphics::Display::DisplayOrientations mCurrentOrientation;

    std::queue<PointerEvent> mPointerEvents;

    std::mutex mMutex;
	// The AppDelegate for the Cocos2D app
	AppDelegate app;
    bool mInitialized;
};

}