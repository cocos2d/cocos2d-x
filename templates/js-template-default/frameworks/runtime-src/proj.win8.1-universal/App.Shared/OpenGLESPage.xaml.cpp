/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2014 - cocos2d-x community
*
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "App.xaml.h"
#include "OpenGLESPage.xaml.h"

using namespace cocos2d;
using namespace Platform;
using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
using namespace Windows::Phone::UI::Input;
#endif

OpenGLESPage::OpenGLESPage() :
    OpenGLESPage(nullptr)
{

}

OpenGLESPage::OpenGLESPage(OpenGLES* openGLES) :
    mOpenGLES(openGLES),
    mRenderSurface(EGL_NO_SURFACE),
    mCustomRenderSurfaceSize(0,0),
    mUseCustomRenderSurfaceSize(false),
    m_coreInput(nullptr),
    m_dpi(0.0f),
    m_visible(false),
    m_deviceLost(false),
    m_orientation(DisplayOrientations::Landscape)
{
    InitializeComponent();

    Windows::UI::Core::CoreWindow^ window = Windows::UI::Xaml::Window::Current->CoreWindow;

    window->VisibilityChanged +=
        ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^>(this, &OpenGLESPage::OnVisibilityChanged);

    swapChainPanel->SizeChanged +=
        ref new Windows::UI::Xaml::SizeChangedEventHandler(this, &OpenGLESPage::OnSwapChainPanelSizeChanged);

    DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

    currentDisplayInformation->OrientationChanged +=
        ref new TypedEventHandler<DisplayInformation^, Object^>(this, &OpenGLESPage::OnOrientationChanged);

    m_orientation = currentDisplayInformation->CurrentOrientation;

    this->Loaded +=
        ref new Windows::UI::Xaml::RoutedEventHandler(this, &OpenGLESPage::OnPageLoaded);

    mSwapChainPanelSize = { swapChainPanel->RenderSize.Width, swapChainPanel->RenderSize.Height };

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
    Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->HideAsync();
    HardwareButtons::BackPressed += ref new EventHandler<BackPressedEventArgs^>(this, &OpenGLESPage::OnBackButtonPressed);   
#else
    // Disable all pointer visual feedback for better performance when touching.
    // This is not supported on Windows Phone applications.
    auto pointerVisualizationSettings = Windows::UI::Input::PointerVisualizationSettings::GetForCurrentView();
    pointerVisualizationSettings->IsContactFeedbackEnabled = false;
    pointerVisualizationSettings->IsBarrelButtonFeedbackEnabled = false;
#endif

    // Register our SwapChainPanel to get independent input pointer events
    auto workItemHandler = ref new WorkItemHandler([this](IAsyncAction ^)
    {
        // The CoreIndependentInputSource will raise pointer events for the specified device types on whichever thread it's created on.
        m_coreInput = swapChainPanel->CreateCoreIndependentInputSource(
            Windows::UI::Core::CoreInputDeviceTypes::Mouse |
            Windows::UI::Core::CoreInputDeviceTypes::Touch |
            Windows::UI::Core::CoreInputDeviceTypes::Pen
            );

        // Register for pointer events, which will be raised on the background thread.
        m_coreInput->PointerPressed += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerPressed);
        m_coreInput->PointerMoved += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerMoved);
        m_coreInput->PointerReleased += ref new TypedEventHandler<Object^, PointerEventArgs^>(this, &OpenGLESPage::OnPointerReleased);

        // Begin processing input messages as they're delivered.
        m_coreInput->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
    });

    // Run task on a dedicated high priority background thread.
    m_inputLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);

}

OpenGLESPage::~OpenGLESPage()
{
    StopRenderLoop();
    DestroyRenderSurface();
}

void OpenGLESPage::OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    // The SwapChainPanel has been created and arranged in the page layout, so EGL can be initialized.
    CreateRenderSurface();
    m_visible = true;
    StartRenderLoop();
}

void OpenGLESPage::OnPointerPressed(Object^ sender, PointerEventArgs^ e)
{
    if (m_renderer)
    {
        m_renderer->QueuePointerEvent(PointerEventType::PointerPressed, e);
    }
}

void OpenGLESPage::OnPointerMoved(Object^ sender, PointerEventArgs^ e)
{
    if (m_renderer)
    {
        m_renderer->QueuePointerEvent(PointerEventType::PointerMoved, e);
    }
}

void OpenGLESPage::OnPointerReleased(Object^ sender, PointerEventArgs^ e)
{
    if (m_renderer)
    {
        m_renderer->QueuePointerEvent(PointerEventType::PointerReleased, e);
    }
}

void OpenGLESPage::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
    critical_section::scoped_lock lock(mSwapChainPanelSizeCriticalSection);
   m_orientation = sender->CurrentOrientation;
}

void OpenGLESPage::OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args)
{
    if (args->Visible && mRenderSurface != EGL_NO_SURFACE)
    {
        m_visible = true;
    }
    else
    {
        m_visible = false;
    }
}

#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
void OpenGLESPage::OnBackButtonPressed(Object^ sender, BackPressedEventArgs^ args)
{
    bool myAppCanNavigate = false;
    if (myAppCanNavigate)
    {
        args->Handled = true;
    }
    else {
        // Do nothing. Leave args->Handled set to the current value, false.
    }
}
#endif


void OpenGLESPage::OnSwapChainPanelSizeChanged(Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
    // Size change events occur outside of the render thread.  A lock is required when updating
    // the swapchainpanel size
    critical_section::scoped_lock lock(mSwapChainPanelSizeCriticalSection);
    mSwapChainPanelSize = { e->NewSize.Width, e->NewSize.Height };
}

void OpenGLESPage::GetSwapChainPanelSize(GLsizei* width, GLsizei* height)
{
    critical_section::scoped_lock lock(mSwapChainPanelSizeCriticalSection);
    // If a custom render surface size is specified, return its size instead of
    // the swapchain panel size.
    if (mUseCustomRenderSurfaceSize)
    {
        *width = static_cast<GLsizei>(mCustomRenderSurfaceSize.Width);
        *height = static_cast<GLsizei>(mCustomRenderSurfaceSize.Height);
    }
    else
    {
        *width = static_cast<GLsizei>(mSwapChainPanelSize.Width);
        *height = static_cast<GLsizei>(mSwapChainPanelSize.Height);
    }
}

void OpenGLESPage::CreateRenderSurface()
{
    if (mOpenGLES)
    {
        //
        // A Custom render surface size can be specified by uncommenting the following lines.
        // The render surface will be automatically scaled to fit the entire window.  Using a
        // smaller sized render surface can result in a performance gain.
        //
        //mCustomRenderSurfaceSize = Size(800, 600);
        //mUseCustomRenderSurfaceSize = true;

        mRenderSurface = mOpenGLES->CreateSurface(swapChainPanel, mUseCustomRenderSurfaceSize ? &mCustomRenderSurfaceSize : nullptr);
    }
}

void OpenGLESPage::DestroyRenderSurface()
{
    if (mOpenGLES)
    {
        mOpenGLES->DestroySurface(mRenderSurface);
    }
    mRenderSurface = EGL_NO_SURFACE;
}

void OpenGLESPage::RecoverFromLostDevice()
{
    // resets OpenGLES, recreates the render surface
    DestroyRenderSurface();
    mOpenGLES->Reset();
    CreateRenderSurface();
}

void OpenGLESPage::StartRenderLoop()
{
    // If the render loop is already running then do not start another thread.
    if (mRenderLoopWorker != nullptr && mRenderLoopWorker->Status == Windows::Foundation::AsyncStatus::Started)
    {
        return;
    }

    DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();
    m_dpi = currentDisplayInformation->LogicalDpi;

    auto dispatcher = Windows::UI::Xaml::Window::Current->CoreWindow->Dispatcher;

    // Create a task for rendering that will be run on a background thread.
    auto workItemHandler = ref new Windows::System::Threading::WorkItemHandler([this, dispatcher](Windows::Foundation::IAsyncAction ^ action)
    {
        mOpenGLES->MakeCurrent(mRenderSurface);
        GLsizei panelWidth = 0;
        GLsizei panelHeight = 0;
        GetSwapChainPanelSize(&panelWidth, &panelHeight);

        if (m_renderer.get() == nullptr)
        {
            m_renderer = std::make_shared<Cocos2dRenderer>(panelWidth, panelHeight, m_dpi, m_orientation, dispatcher, swapChainPanel);
        }

        m_renderer->Resume();

        while (action->Status == Windows::Foundation::AsyncStatus::Started)
        {
            if (!m_visible)
            {
                m_renderer->Pause();
                while (!m_visible)
                {
                    if (action->Status != Windows::Foundation::AsyncStatus::Started)
                    {
                        return;
                    }
                    Sleep(500);
                }
                m_renderer->Resume();
            }
           
            GetSwapChainPanelSize(&panelWidth, &panelHeight);
            m_renderer.get()->Draw(panelWidth, panelHeight, m_dpi, m_orientation);

            // The call to eglSwapBuffers might not be successful (i.e. due to Device Lost)
            // If the call fails, then we must reinitialize EGL and the GL resources.
            if (mOpenGLES->SwapBuffers(mRenderSurface) != GL_TRUE)
            {
                m_deviceLost = true;

                // XAML objects like the SwapChainPanel must only be manipulated on the UI thread.
                swapChainPanel->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=]()
                {
                    RecoverFromLostDevice();
                }, CallbackContext::Any));

                while(m_deviceLost)
                {
                    if (action->Status != Windows::Foundation::AsyncStatus::Started)
                    {
                        return;
                    }
                    Sleep(500);
                }
                mOpenGLES->MakeCurrent(mRenderSurface);
                m_renderer->DeviceLost();
            }
        }
    });

    // Run task on a dedicated high priority background thread.
    mRenderLoopWorker = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);
}

void OpenGLESPage::StopRenderLoop()
{
    if (mRenderLoopWorker)
    {
        mRenderLoopWorker->Cancel();
        mRenderLoopWorker = nullptr;
    }
}