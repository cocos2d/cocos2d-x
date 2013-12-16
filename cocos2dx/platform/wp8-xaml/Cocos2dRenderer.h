#pragma once

#include "DirectXBase.h"
#include <DirectXMath.h>

// This class renders a simple spinning cube.
ref class Cocos2dRenderer sealed : public DirectXBase
{
public:
	Cocos2dRenderer();

	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;

	void Update(float timeTotal, float timeDelta);
	virtual void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation) override;
	virtual bool OnRender() override;
    virtual void CreateGLResources() override;

	void OnPointerPressed(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerMoved(Windows::UI::Core::PointerEventArgs^ args);
	void OnPointerReleased(Windows::UI::Core::PointerEventArgs^ args);
    Windows::Foundation::IAsyncAction^ OnSuspending();
    void OnResuming();
    bool OnBackPressed();

protected:
    virtual void OnUpdateDevice() override;

private:

    bool m_loadingComplete;
    bool mInitialized;

};
