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

#include "WinRTEditBox.g.h"
#include "CCEGLView.h"

namespace cocos2d
{
	[Windows::Foundation::Metadata::WebHostHidden]
    public ref class WinRTXamlEditBox sealed
	{
	public:
        WinRTXamlEditBox(CCEditBoxParam^ params);
		void initTextinput(int maxLen, int inputMode);
	private:
		void editbox_load(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void pwdBox_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void SetInputScope(Windows::UI::Xaml::Controls::TextBox^ curBox, int inputMode);
        void textinput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
        void textinput_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void textinput_LostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void OnKeyDownHandler(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
        void Done_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void Cancel_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

	private:

        Platform::Object^ findXamlElement(Platform::Object^ parent, Platform::String^ name);

		Platform::String^ m_strText;
		Platform::String^ m_strPlaceholder;
		bool bIsFocus;
		int m_inputFlag;
		Windows::UI::Xaml::Controls::Control^ m_textinput;			
		Windows::Foundation::EventHandler<Platform::String^>^ m_responseHandler;

        Windows::UI::Xaml::Controls::Button^ m_doneButton;
        Windows::UI::Xaml::Controls::Button^ m_cancelButton;

        Windows::Foundation::EventRegistrationToken m_doneToken;
        Windows::Foundation::EventRegistrationToken m_cancelToken;
	};
}
