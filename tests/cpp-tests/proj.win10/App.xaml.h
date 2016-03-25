#pragma once

#include "app.g.h"
#include "OpenGLES.h"
#include "OpenGLESPage.xaml.h"

namespace CocosAppWinRT
{
    ref class App sealed
    {
    public:
        App();
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

    private:
        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
        void OnResuming(Platform::Object ^sender, Platform::Object ^args);
        void OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e);

        OpenGLESPage^ mPage;
        OpenGLES mOpenGLES;
    };
}
