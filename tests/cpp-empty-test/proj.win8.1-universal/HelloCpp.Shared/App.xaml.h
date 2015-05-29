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

    private:

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
        Windows::UI::Xaml::Media::Animation::TransitionCollection^ _transitions;
        Windows::Foundation::EventRegistrationToken _firstNavigatedToken;

        void RootFrame_FirstNavigated(Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);
#endif

        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);

        OpenGLESPage^ mPage;
        OpenGLES mOpenGLES;
    };
}
