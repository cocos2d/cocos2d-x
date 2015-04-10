#pragma once

#include "app.g.h"
#include "OpenGLES.h"
#include "openglespage.xaml.h"

namespace cocos2d
{
    ref class App sealed
    {
    public:
        App();
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
	protected:
		virtual void OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs ^ args) override;
#endif
    private:
        OpenGLESPage^ mPage;
        OpenGLES mOpenGLES;
    };
}
