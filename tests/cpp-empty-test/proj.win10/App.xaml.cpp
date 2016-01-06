#include "App.xaml.h"
#include "OpenGLESPage.xaml.h"

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace cocos2d;
using namespace CocosAppWinRT;

App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
    Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
    if (mPage == nullptr)
    {
        mPage = ref new OpenGLESPage(&mOpenGLES);
    }

    // Place the page in the current window and ensure that it is active.
    Windows::UI::Xaml::Window::Current->Content = mPage;
    Windows::UI::Xaml::Window::Current->Activate();
}

/// <summary>
/// Invoked when application execution is being suspended. Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void)sender;	// Unused parameter
    (void)e;		// Unused parameter

    mPage->SetVisibility(false);
}

/// <summary>
/// Invoked when application execution is being resumed.
/// </summary>
/// <param name="sender">The source of the resume request.</param>
/// <param name="args">Details about the resume request.</param>
void App::OnResuming(Object ^sender, Object ^args)
{
    (void)sender; // Unused parameter
    (void)args; // Unused parameter

    mPage->SetVisibility(true);
}

