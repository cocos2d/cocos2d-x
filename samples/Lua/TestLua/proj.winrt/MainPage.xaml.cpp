//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "CCEGLView.h"
USING_NS_CC;

using namespace TestLua;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();

	CCEGLView* eglView = new CCEGLView();
	eglView->Create(Window::Current->CoreWindow, SwapChainPanel);
	eglView->setViewName("HelloLua");
	CCApplication::sharedApplication()->run();
}

void TestLua::MainPage::OnPreviousPressed( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e )
{

}

void TestLua::MainPage::OnNextPressed( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e )
{

}

void TestLua::MainPage::SaveInternalState( Windows::Foundation::Collections::IPropertySet^ state )
{
	CCEGLView::sharedOpenGLView()->OnSuspending();
}

void TestLua::MainPage::LoadInternalState( Windows::Foundation::Collections::IPropertySet^ state )
{

}
