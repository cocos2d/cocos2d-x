/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

http://www.cocos2d-x.org

* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved

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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "UIEditBoxImpl-winrt.h"
#include "UIEditBox.h"
#include "CCGLViewImpl-winrt.h"
#include "base/CCScriptSupport.h"
#include "base/ccUTF8.h"
#include "2d/CCLabel.h"

using namespace Platform;
using namespace Concurrency;
using namespace Windows::System;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

NS_CC_BEGIN

namespace ui {

EditBoxWinRT::EditBoxWinRT()
{

}

EditBoxWinRT::~EditBoxWinRT()
{

}

EditBoxWinRT::EditBoxWinRT(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, EditBox::InputMode inputMode, EditBox::InputFlag inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler)
{
    m_dispatcher = cocos2d::GLViewImpl::sharedOpenGLView()->getDispatcher();
    m_panel = cocos2d::GLViewImpl::sharedOpenGLView()->getPanel();
    m_strText = strText;
    m_strPlaceholder = strPlaceHolder;
    m_inputMode = inputMode;
    m_inputFlag = inputFlag;
    m_receiveHandler = receiveHandler;
    m_maxLength = maxLength;
}



void EditBoxWinRT::OpenXamlEditBox(Platform::String^ strText)
{
    m_strText = strText;
    if (m_control != nullptr)
    {
        return;
    }

    if (m_dispatcher.Get() == nullptr || m_panel.Get() == nullptr)
    {
        return;
    }

    // must create XAML element on main UI thread
    m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]()
    {
        if (m_inputFlag == EditBox::InputFlag::PASSWORD)
        {
            m_control = CreatePasswordBox(m_maxLength);
        }
        else
        {
            m_control = CreateTextBox(m_maxLength);
        }

        if (m_control)
        {
            //control->Margin = ref new Thickness(0, 0, 220, 0);
            m_control->Height = 72.0;
            m_control->TabIndex = 0;
            m_control->VerticalAlignment = VerticalAlignment::Top;
            m_control->Focus(FocusState::Programmatic);
            m_control->Loaded += ref new RoutedEventHandler(this, &EditBoxWinRT::OnLoaded);
            m_panel.Get()->Children->Append(m_control);
        }
    }));
}

Control^ EditBoxWinRT::CreateTextBox(int maxLength)
{
    if (m_textBox == nullptr)
    {
        auto box = ref new TextBox();
        box->MaxLength = maxLength < 0 ? 0 : maxLength;
        SetInputScope(box, m_inputMode);
        box->PlaceholderText = m_strPlaceholder;
        if (m_strText->Length() > 0)
        {
            box->Text = m_strText;
        }

        box->AddHandler(UIElement::KeyDownEvent, ref new KeyEventHandler(this, &EditBoxWinRT::OnKeyPressed), true);
        box->TextChanged += ref new TextChangedEventHandler(this, &EditBoxWinRT::OnTextChanged);
        box->LostFocus += ref new RoutedEventHandler(this, &EditBoxWinRT::OnLostFocus);
        box->GotFocus += ref new RoutedEventHandler(this, &EditBoxWinRT::OnGotFocus);

        m_textBox = box;
    }

    return m_textBox;
}

Control^ EditBoxWinRT::CreatePasswordBox(int maxLength)
{
    if (m_passwordBox == nullptr)
    {
        PasswordBox^ box = ref new PasswordBox();
        box->MaxLength = maxLength < 0 ? 0 : maxLength;
        box->Password = m_strText;
        box->GotFocus += ref new RoutedEventHandler(this, &EditBoxWinRT::OnGotFocusPassword);
        box->AddHandler(UIElement::KeyDownEvent, ref new KeyEventHandler(this, &EditBoxWinRT::OnKeyPressed), true);
        m_passwordBox = box;
    }

    return m_passwordBox;
}

void EditBoxWinRT::SetInputScope(TextBox^ box, EditBox::InputMode inputMode)
{
    // TextBox.SetInputScope
    InputScope^ inputScope = ref new InputScope();
    InputScopeName^ name = ref new InputScopeName();

    switch (inputMode)
    {
    case EditBox::InputMode::ANY:
        name->NameValue = InputScopeNameValue::Default;
        break;
    case EditBox::InputMode::EMAIL_ADDRESS:
        name->NameValue = InputScopeNameValue::EmailSmtpAddress;
        break;
    case EditBox::InputMode::NUMERIC:
        name->NameValue = InputScopeNameValue::Number;
        break;
    case EditBox::InputMode::PHONE_NUMBER:
        name->NameValue = InputScopeNameValue::TelephoneNumber;
        break;
    case EditBox::InputMode::URL:
        name->NameValue = InputScopeNameValue::Url;
        break;
    case EditBox::InputMode::DECIMAL:
        name->NameValue = InputScopeNameValue::Number;
        break;
    case EditBox::InputMode::SINGLE_LINE:
        name->NameValue = InputScopeNameValue::Default;
        break;
    default:
        name->NameValue = InputScopeNameValue::Default;
        break;
    }

    inputScope->Names->Append(name);
    box->InputScope = inputScope;
}

void EditBoxWinRT::RemoveControl(Control^ control)
{
    if (control != nullptr)
    {
        unsigned int index;
        if (m_panel->Children->IndexOf(control, &index))
        {
            m_panel->Children->RemoveAt(index);
        }
    }
}

void EditBoxWinRT::RemoveControls()
{
    if (m_dispatcher.Get() && m_panel.Get())
    {
        // run on main UI thread
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]()
        {
            RemoveControl(m_control);
            m_textBox = nullptr;
            m_passwordBox = nullptr;
            m_control = nullptr;
        }));
    }
}

void EditBoxWinRT::OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    m_control->Focus(FocusState::Programmatic);
}

void EditBoxWinRT::OnGotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    m_textBox->Select(m_textBox->Text->Length(), 0);
}

void EditBoxWinRT::OnGotFocusPassword(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    m_passwordBox->Password = m_strText;
    m_passwordBox->SelectAll();
}

void EditBoxWinRT::OnLostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{

}

void EditBoxWinRT::OnKeyPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args)
{
    switch (args->Key)
    {
     case VirtualKey::Enter:
         QueueText();
         RemoveControls();
         args->Handled = true;
        break;
     case VirtualKey::Escape:
         RemoveControls();
         args->Handled = true;
         break;
    default:
        break;
    }
}

void EditBoxWinRT::QueueText()
{
    Platform::String^ text = m_inputFlag == EditBox::InputFlag::PASSWORD ? m_passwordBox->Password : m_textBox->Text;
    std::shared_ptr<cocos2d::InputEvent> e(new UIEditBoxEvent(this, text, m_receiveHandler));
    cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(e);
}

void EditBoxWinRT::OnTextChanged(Platform::Object^ sender, TextChangedEventArgs^ args)
{
    m_strText = m_textBox->Text;
}


EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
{
	return new UIEditBoxImplWinrt(pEditBox);
}

UIEditBoxImplWinrt::UIEditBoxImplWinrt( EditBox* pEditText )
	: EditBoxImpl(pEditText)
	, m_pLabel(NULL)
	, m_pLabelPlaceHolder(NULL)
	, m_eEditBoxInputMode(EditBox::InputMode::SINGLE_LINE)
	, m_eEditBoxInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS)
	, m_eKeyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
	, m_colText(Color3B::WHITE)
	, m_colPlaceHolder(Color3B::GRAY)
	, m_nMaxLength(-1)
{

}

UIEditBoxImplWinrt::~UIEditBoxImplWinrt()
{

}

void UIEditBoxImplWinrt::openKeyboard()
{
	if (_delegate != NULL)
	{
		_delegate->editBoxEditingDidBegin(_editBox);
	}

	EditBox* pEditBox = this->getEditBox();
	if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
	{
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
	}

	std::string placeHolder = m_pLabelPlaceHolder->getString();
	if (placeHolder.length() == 0)
		placeHolder = "Enter value";

	char pText[100]= {0};
	std::string text = getText();
	if (text.length())
		strncpy(pText, text.c_str(), 100);


    if (!m_editBoxWinrt)
    {
        Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler = ref new Windows::Foundation::EventHandler<Platform::String^>(
            [this](Platform::Object^ sender, Platform::String^ arg)
        {
            setText(PlatformStringTostring(arg).c_str());
            if (_delegate != NULL) {
                _delegate->editBoxTextChanged(_editBox, getText());
                _delegate->editBoxEditingDidEnd(_editBox);
                _delegate->editBoxReturn(_editBox);
            }
        });

        m_editBoxWinrt = ref new EditBoxWinRT(stringToPlatformString(placeHolder), stringToPlatformString(getText()), m_nMaxLength, m_eEditBoxInputMode, m_eEditBoxInputFlag, receiveHandler);
    }

    m_editBoxWinrt->OpenXamlEditBox(stringToPlatformString(getText()));
}

bool UIEditBoxImplWinrt::initWithSize( const Size& size )
{
	//! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
	m_pLabel = Label::createWithSystemFont("", "", size.height-12);
	// align the text vertically center
	m_pLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	m_pLabel->setPosition(Vec2(5.0, size.height / 2.0f));
	m_pLabel->setColor(m_colText);
	_editBox->addChild(m_pLabel);

	m_pLabelPlaceHolder = Label::createWithSystemFont("", "", size.height-12);
	// align the text vertically center
	m_pLabelPlaceHolder->setAnchorPoint(Vec2(0.0f, 0.5f));
	m_pLabelPlaceHolder->setPosition(Vec2(5.0f, size.height / 2.0f));
	m_pLabelPlaceHolder->setVisible(false);
	m_pLabelPlaceHolder->setColor(m_colPlaceHolder);
	_editBox->addChild(m_pLabelPlaceHolder);

	m_EditSize = size;
	return true;
}

void UIEditBoxImplWinrt::setFont( const char* pFontName, int fontSize )
{
	if(m_pLabel != NULL) {
		m_pLabel->setSystemFontName(pFontName);
		m_pLabel->setSystemFontSize(fontSize);
	}

	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setSystemFontName(pFontName);
		m_pLabelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void UIEditBoxImplWinrt::setFontColor( const Color3B& color )
{
	m_colText = color;
	m_pLabel->setColor(color);
}

void UIEditBoxImplWinrt::setPlaceholderFont( const char* pFontName, int fontSize )
{
	if(m_pLabelPlaceHolder != NULL) {
		m_pLabelPlaceHolder->setSystemFontName(pFontName);
		m_pLabelPlaceHolder->setSystemFontSize(fontSize);
	}
}

void UIEditBoxImplWinrt::setPlaceholderFontColor( const Color3B& color )
{
	m_colPlaceHolder = color;
	m_pLabelPlaceHolder->setColor(color);
}

void UIEditBoxImplWinrt::setInputMode( EditBox::InputMode inputMode )
{
	m_eEditBoxInputMode = inputMode;
}

void UIEditBoxImplWinrt::setInputFlag(EditBox::InputFlag inputFlag )
{
	m_eEditBoxInputFlag = inputFlag;
}

void UIEditBoxImplWinrt::setMaxLength( int maxLength )
{
	m_nMaxLength = maxLength;
}

int UIEditBoxImplWinrt::getMaxLength()
{
	return m_nMaxLength;
}

void UIEditBoxImplWinrt::setReturnType( EditBox::KeyboardReturnType returnType )
{
	m_eKeyboardReturnType = returnType;
}

bool UIEditBoxImplWinrt::isEditing()
{
	return false;
}

void UIEditBoxImplWinrt::setText( const char* pText )
{
	if (pText != NULL)
	{
		m_strText = pText;

		if (m_strText.length() > 0)
		{
			m_pLabelPlaceHolder->setVisible(false);

			std::string strToShow;

			if (EditBox::InputFlag::PASSWORD == m_eEditBoxInputFlag)
			{
				long length = cc_utf8_strlen(m_strText.c_str(), -1);
				for (long i = 0; i < length; i++)
				{
					strToShow.append("*");
				}
			}
			else
			{
				strToShow = m_strText;
			}

			//! std::string strWithEllipsis = getStringWithEllipsisJni(strToShow.c_str(), m_EditSize.width, m_EditSize.height-12);
			//! m_pLabel->setString(strWithEllipsis.c_str());
			m_pLabel->setString(strToShow.c_str());
		}
		else
		{
			m_pLabelPlaceHolder->setVisible(true);
			m_pLabel->setString("");
		}

	}
}

const char* UIEditBoxImplWinrt::getText( void )
{
	return m_strText.c_str();
}

void UIEditBoxImplWinrt::setPlaceHolder( const char* pText )
{
	if (pText != NULL)
	{
		m_strPlaceHolder = pText;
		if (m_strPlaceHolder.length() > 0 && m_strText.length() == 0)
		{
			m_pLabelPlaceHolder->setVisible(true);
		}

		m_pLabelPlaceHolder->setString(m_strPlaceHolder.c_str());
	}
}

void UIEditBoxImplWinrt::setPosition( const Vec2& pos )
{

}

void UIEditBoxImplWinrt::setVisible( bool visible )
{

}

void UIEditBoxImplWinrt::setContentSize( const Size& size )
{

}

void UIEditBoxImplWinrt::setAnchorPoint( const Vec2& anchorPoint )
{

}

void UIEditBoxImplWinrt::visit( void )
{

}

void UIEditBoxImplWinrt::doAnimationWhenKeyboardMove( float duration, float distance )
{

}

void UIEditBoxImplWinrt::closeKeyboard()
{

}

void UIEditBoxImplWinrt::onEnter( void )
{

}

Platform::String^ UIEditBoxImplWinrt::stringToPlatformString( std::string strSrc )
{
	// to wide char
	int nStrLen = MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, NULL, 0);  
	wchar_t* pWStr = new wchar_t[nStrLen + 1];  
	memset(pWStr, 0, nStrLen + 1);  
	MultiByteToWideChar(CP_UTF8, 0, strSrc.c_str(), -1, pWStr, nStrLen);  
	Platform::String^ strDst = ref new Platform::String(pWStr);
	delete[] pWStr;
	return strDst;
}

std::string UIEditBoxImplWinrt::PlatformStringTostring( Platform::String^ strSrc )
{
	const wchar_t* pWStr = strSrc->Data();
	int nStrLen = WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, NULL, 0, NULL, NULL);  
	char* pStr = new char[nStrLen + 1];  
	memset(pStr, 0, nStrLen + 1);  
	WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, pStr, nStrLen, NULL, NULL);  ;  

	std::string strDst = std::string(pStr);

	delete[] pStr;
	return strDst;
}

}

NS_CC_END

#endif // WP8
