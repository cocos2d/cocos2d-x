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

//#include "pch.h"
#include "EditBox.xaml.h"
#include "CCEditBoxImplWinrt.h"
#include "CCDirector.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::System;
using namespace Windows::UI::Input;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Controls::Primitives;

	// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236
namespace TestCpp
{
	EditBox::EditBox(CCEditBoxParam^ params)
	{
		InitializeComponent();

		m_strText = params->GetEditText();
		m_strPlaceholder = params->GetPlaceHolder();
		m_inputFlag = params->GetInputFlag();
		m_responseHandler = params->GetRespondsHandler();
		initTextinput(params->GetEditLength(), params->GetInputMode());
	}

	void EditBox::initTextinput(int maxLen, int inputMode)
	{
		if (m_inputFlag == 0)
		{
			// kEditBoxInputFlagPassword      
			PasswordBox^ pwdBox = ref new PasswordBox();
			pwdBox->MaxLength = maxLen < 0 ? 0 : maxLen;
			pwdBox->Password = m_strText;
			pwdBox->GotFocus += ref new RoutedEventHandler(this, &EditBox::pwdBox_GotFocus);
			pwdBox->IsEnabled = true;
			m_textinput = pwdBox;
		} 
		else
		{                
			TextBox^ textbox = ref new TextBox();
			textbox->MaxLength = maxLen < 0 ? 0 : maxLen;
			SetInputScope(textbox, inputMode);
			textbox->TextChanged += ref new TextChangedEventHandler(this, &EditBox::textinput_TextChanged);
			textbox->GotFocus += ref new RoutedEventHandler(this, &EditBox::textinput_GotFocus);
			textbox->LostFocus += ref new RoutedEventHandler(this, &EditBox::textinput_LostFocus);
			textbox->IsEnabled = true;			
			m_textinput = textbox;
		}
		m_textinput->Margin = Thickness(10, 14, 0, 0);
		m_textinput->Width = 286.0;
		m_textinput->TabIndex = 0;		
		m_textinput->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
		m_textinput->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
		m_textinput->KeyDown += ref new KeyEventHandler(this, &EditBox::OnKeyDownHandler);           
		this->LayoutRoot->Children->Append(m_textinput);
	}


	void EditBox::editbox_load(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
	{		
		m_textinput->Focus(Windows::UI::Xaml::FocusState::Keyboard);
	}

	void EditBox::pwdBox_GotFocus( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e )
	{
		((PasswordBox^)m_textinput)->SelectAll();
	}

	void EditBox::SetInputScope( TextBox^ curBox, int inputMode )
	{
		// textbox->SetInputScope
		InputScope^ inputScope = ref new InputScope();
		InputScopeName^ name = ref new InputScopeName();

		switch (inputMode)
		{
		case 0:// kEditBoxInputModeAny
			name->NameValue = InputScopeNameValue::Default;
			break;
		case 1:// kEditBoxInputModeEmailAddr
			name->NameValue = InputScopeNameValue::EmailSmtpAddress;
			break;
		case 2:// kEditBoxInputModeNumeric
			name->NameValue = InputScopeNameValue::Number;
			break;
		case 3:// kEditBoxInputModePhoneNumber
			name->NameValue = InputScopeNameValue::TelephoneNumber;
			break;
		case 4:// kEditBoxInputModeUrl
			name->NameValue = InputScopeNameValue::Url;
			break;
		case 5:// kEditBoxInputModeDecimal
			name->NameValue = InputScopeNameValue::Default;
			break;
		case 6:// kEditBoxInputModeSingleLine
			name->NameValue = InputScopeNameValue::Default;
			break;
		default:
			name->NameValue = InputScopeNameValue::Default;
			break;
		}

		inputScope->Names->Append(name);
		curBox->InputScope = inputScope;
	}

	void EditBox::textinput_TextChanged( Platform::Object^ sender, TextChangedEventArgs^ e )
	{
		// textbox->textinput_TextChanged
		if (bIsFocus)
			m_strText = ((TextBox^)m_textinput)->Text;
	}

	void EditBox::textinput_GotFocus( Platform::Object^ sender, RoutedEventArgs^ e )
	{
		// textbox->GotFocus
		TextBox^ curBox = (TextBox^)m_textinput;
		bIsFocus = true;
		curBox->Text = m_strText;
		curBox->Select(0, curBox->Text->Length());
	}

	void EditBox::textinput_LostFocus( Platform::Object^ sender, RoutedEventArgs^ e )
	{
		// textbox->LostFocus
		TextBox^ curBox = (TextBox^)m_textinput;
		bIsFocus = false;
		m_strText = curBox->Text;
		String^ strText(L"");
		strText = curBox->Text;
		if (strText->IsEmpty() && m_inputFlag != 0)
		{
			curBox->Text = m_strPlaceholder;
		}                
	}

	void EditBox::OnKeyDownHandler( Platform::Object^ sender, KeyRoutedEventArgs^ e )
	{
		switch (e->Key)
		{
		case VirtualKey::Enter:
			Done_Click(sender, nullptr);
			e->Handled = true;
			break;
		default:
			break;
		}
	}

	void EditBox::Done_Click(Platform::Object^ sender, RoutedEventArgs^ e)
	{		
		if (m_responseHandler)
		{
			m_responseHandler->Invoke(sender, m_inputFlag == 0 ? ((PasswordBox^)m_textinput)->Password : m_strText);
		}		
		Cancel_Click(nullptr, nullptr);
	}


	void EditBox::Cancel_Click(Platform::Object^ sender, RoutedEventArgs^ e)
	{
		CCEGLView* glView = CCDirector::sharedDirector()->getOpenGLView();
		glView->OnCloseEditBox();

		Window::Current->CoreWindow->GetForCurrentThread()->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, 
			ref new DispatchedHandler([=]()
		{
			Grid^ grid = (Grid^)this->Parent;

			UIElementCollection^ childs = ((SwapChainBackgroundPanel^)grid->Parent)->Children;
			unsigned int index = 0;
			bool bResult = childs->IndexOf((UIElement^)grid, &index);
			if (bResult)
			{
				childs->RemoveAt(index);
			}
		}, CallbackContext::Any));
	}

}