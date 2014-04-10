/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
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
//
// MainPage.xaml.cpp
// Implementation of the MainPage.xaml class.
//

#include "MainPage.xaml.h"

#include "CCApplication.h"
#include "CCEGLView.h"
#include "EditBox.xaml.h"

USING_NS_CC;

using namespace TestCpp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::ViewManagement;

// Cocos2D application delegate


MainPage::MainPage()
{
	InitializeComponent();

	// Note AppDelegate is in MainPage.xaml.h
    CCEGLView* eglView = new CCEGLView();
	eglView->Create(Window::Current->CoreWindow, SwapChainPanel);
    eglView->setViewName("TestCpp");
	eglView->SetCocosEditBoxHandler(ref new EventHandler<Object^>(this, &MainPage::OnOpenEditBox));
	CCApplication::sharedApplication()->run();
}



void MainPage::OnPreviousPressed(Object^ sender, RoutedEventArgs^ args)
{
}

void MainPage::OnNextPressed(Object^ sender, RoutedEventArgs^ args)
{
}

void MainPage::SaveInternalState(IPropertySet^ state)
{
    CCEGLView::sharedOpenGLView()->OnSuspending();
}

void MainPage::LoadInternalState(IPropertySet^ state)
{
	//m_renderer->LoadInternalState(state);
}


void TestCpp::MainPage::OnOpenEditBox(Object^ sender, Object^ args)
{
	// get Main thread
	Windows::UI::Core::CoreWindow^ wnd = Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow;
	assert(wnd != nullptr);

	wnd->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, 
		ref new DispatchedHandler([=]()
	{
		CCEditBoxParam^ params = (CCEditBoxParam^)args;
		EditBox^ editBox = ref new EditBox(params);
		editBox->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;

		// grid
		Grid^ grid = ref new Grid();
		grid->IsHitTestVisible = true;
		grid->IsTapEnabled = true;
		grid->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Stretch;
		grid->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Stretch;

		// background
		Border^ overlay = ref new Border();
		overlay->IsHitTestVisible = false;
		overlay->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Stretch;
		overlay->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Stretch;
		overlay->Background = ref new SolidColorBrush(Windows::UI::Colors::Gray);
		overlay->Opacity = 0.5;
		overlay->IsTapEnabled = true;

		grid->Children->Append(overlay);
		grid->Children->Append(editBox);

		this->SwapChainPanel->Children->Append(grid);
	}));
}
