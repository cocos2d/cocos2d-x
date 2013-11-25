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

USING_NS_CC;

using namespace TestCpp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

// Cocos2D application delegate


MainPage::MainPage()
{
	InitializeComponent();
	// Note AppDelegate is in MainPage.xaml.h
    CCEGLView* eglView = new CCEGLView();
	eglView->Create(Window::Current->CoreWindow, SwapChainPanel);
    eglView->setViewName("TestCpp");
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

