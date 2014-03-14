/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

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

#pragma once

#include "EditBox.g.h"
#include "CCEGLView.h"
USING_NS_CC;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Core;

namespace TestCpp
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class EditBox sealed
	{
	public:
		EditBox(CCEditBoxParam^ params);
		void initTextinput(int maxLen, int inputMode);
	private:
		void editbox_load(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void pwdBox_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SetInputScope(TextBox^ curBox, int inputMode);
		void textinput_TextChanged(Platform::Object^ sender, TextChangedEventArgs^ e);
		void textinput_GotFocus(Platform::Object^ sender, RoutedEventArgs^ e);
		void textinput_LostFocus(Platform::Object^ sender, RoutedEventArgs^ e);
		void OnKeyDownHandler(Platform::Object^ sender, KeyRoutedEventArgs^ e);
		void Done_Click(Platform::Object^ sender, RoutedEventArgs^ e);
		void Cancel_Click(Platform::Object^ sender, RoutedEventArgs^ e);

	private:
		Platform::String^ m_strText;
		Platform::String^ m_strPlaceholder;
		bool bIsFocus;
		int m_inputFlag;
		Windows::UI::Xaml::Controls::Control^ m_textinput;			
		Windows::Foundation::EventHandler<Platform::String^>^ m_responseHandler;
	};
}
