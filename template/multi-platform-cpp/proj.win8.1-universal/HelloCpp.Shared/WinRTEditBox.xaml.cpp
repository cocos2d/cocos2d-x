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
#include "WinRTEditBox.xaml.h"
#include "GUI/CCEditBox/CCEditBoxImplWinrt.h"
#include "CCDirector.h"
#include "CCWinRTUtils.h"


using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::System;
using namespace Windows::UI::Input;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Core;

USING_NS_CC;

	// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236
namespace cocos2d
{
    WinRTXamlEditBox::WinRTXamlEditBox(CCEditBoxParam^ params)
	{
		InitializeComponent();

		m_strText = params->GetEditText();
		m_strPlaceholder = params->GetPlaceHolder();
		m_inputFlag = params->GetInputFlag();
		m_responseHandler = params->GetRespondsHandler();
		initTextinput(params->GetEditLength(), params->GetInputMode());
	}

    void WinRTXamlEditBox::initTextinput(int maxLen, int inputMode)
	{
		if (m_inputFlag == 0)
		{
			// kEditBoxInputFlagPassword      
			PasswordBox^ pwdBox = ref new PasswordBox();
			pwdBox->MaxLength = maxLen < 0 ? 0 : maxLen;
			pwdBox->Password = m_strText;
            pwdBox->GotFocus += ref new RoutedEventHandler(this, &WinRTXamlEditBox::pwdBox_GotFocus);
			pwdBox->IsEnabled = true;
			m_textinput = pwdBox;
		} 
		else
		{                
			TextBox^ textbox = ref new TextBox();
			textbox->MaxLength = maxLen < 0 ? 0 : maxLen;
			SetInputScope(textbox, inputMode);
            textbox->TextChanged += ref new TextChangedEventHandler(this, &WinRTXamlEditBox::textinput_TextChanged);
            textbox->GotFocus += ref new RoutedEventHandler(this, &WinRTXamlEditBox::textinput_GotFocus);
            textbox->LostFocus += ref new RoutedEventHandler(this, &WinRTXamlEditBox::textinput_LostFocus);
			textbox->IsEnabled = true;			
			m_textinput = textbox;
		}
		m_textinput->Margin = Thickness(10, 0, 10, 0);
        m_textinput->MinWidth = 200;
        m_textinput->TabIndex = 0;
		m_textinput->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
		m_textinput->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
        m_textinput->KeyDown += ref new KeyEventHandler(this, &WinRTXamlEditBox::OnKeyDownHandler);
		this->LayoutRoot->Children->Append(m_textinput);

        auto doneButton = findXamlElement(this->LayoutRoot, "cocos2d_editbox_done");
        if (doneButton != nullptr)
        {
            m_doneButton = dynamic_cast<Controls::Button^>(doneButton);
            m_doneToken = m_doneButton->Click += ref new RoutedEventHandler(this, &WinRTXamlEditBox::Done_Click);
        }

        auto cancelButton = findXamlElement(this->LayoutRoot, "cocos2d_editbox_cancel");
        if (cancelButton != nullptr)
        {
            m_cancelButton = dynamic_cast<Controls::Button^>(cancelButton);
            m_cancelToken = m_cancelButton->Click += ref new RoutedEventHandler(this, &WinRTXamlEditBox::Cancel_Click);
        }
	}

    void WinRTXamlEditBox::editbox_load(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
	{		
        m_textinput->Focus(Windows::UI::Xaml::FocusState::Programmatic);
	}

    void WinRTXamlEditBox::pwdBox_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
	{
		((PasswordBox^)m_textinput)->SelectAll();
	}

    void WinRTXamlEditBox::SetInputScope(TextBox^ curBox, int inputMode)
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

    void WinRTXamlEditBox::textinput_TextChanged(Platform::Object^ sender, TextChangedEventArgs^ e)
	{
		// textbox->textinput_TextChanged
		if (bIsFocus)
			m_strText = ((TextBox^)m_textinput)->Text;
	}

    void WinRTXamlEditBox::textinput_GotFocus(Platform::Object^ sender, RoutedEventArgs^ e)
	{
		// textbox->GotFocus
		TextBox^ curBox = (TextBox^)m_textinput;
		bIsFocus = true;
		curBox->Text = m_strText;
		curBox->Select(0, curBox->Text->Length());
	}

    void WinRTXamlEditBox::textinput_LostFocus(Platform::Object^ sender, RoutedEventArgs^ e)
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

    void WinRTXamlEditBox::OnKeyDownHandler(Platform::Object^ sender, KeyRoutedEventArgs^ e)
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

    void WinRTXamlEditBox::Done_Click(Platform::Object^ sender, RoutedEventArgs^ e)
	{		
		if (m_responseHandler)
		{
            CCEGLView* glView = CCDirector::sharedDirector()->getOpenGLView();

            Platform::String^ text = (m_inputFlag == 0 ? ((PasswordBox^) m_textinput)->Password : m_strText);
            std::shared_ptr<cocos2d::InputEvent> e(new UIEditBoxEvent(this, text, m_responseHandler));
            glView->QueueEvent(e);
        }
		Cancel_Click(nullptr, nullptr);
	}


    void WinRTXamlEditBox::Cancel_Click(Platform::Object^ sender, RoutedEventArgs^ e)
	{
		CCEGLView* glView = CCDirector::sharedDirector()->getOpenGLView();
		glView->OnCloseEditBox();

		Window::Current->CoreWindow->GetForCurrentThread()->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, 
			ref new DispatchedHandler([=]()
		{
			Grid^ grid = (Grid^)this->Parent;

            if (grid == nullptr)
            {
                return;
            }

            unsigned int index = 0;
            bool bResult = grid->Children->IndexOf((UIElement^)this, &index);
			if (bResult)
			{
                grid->Children->RemoveAt(index);
			}

            if (m_doneButton != nullptr)
            {
                m_doneButton->Click -= m_doneToken;
                m_doneButton = nullptr;
            }

            if (m_cancelButton != nullptr)
            {
                m_cancelButton->Click -= m_cancelToken;
                m_cancelButton = nullptr;
            }

		}, CallbackContext::Any));
	}

    Platform::Object^ WinRTXamlEditBox::findXamlElement(Platform::Object^ parent, Platform::String^ name)
    {
        if (parent == nullptr || name == nullptr || name->Length() == 0)
        {
            return nullptr;
        }

        FrameworkElement^ element = dynamic_cast<FrameworkElement^>(parent);
        if (element == nullptr)
        {
            return nullptr;
        }

        if (element->Name == name)
        {
            return element;
        }

        Panel^ panel = dynamic_cast<Panel^>(element);
        if (panel == nullptr)
        {
            return nullptr;
        }

        int count = panel->Children->Size;
        for (int i = 0; i < count; i++)
        {
            auto result = findXamlElement(panel->Children->GetAt(i), name);
            if (result != nullptr)
            {
                return result;
            }
        }

        return nullptr;
    }
}