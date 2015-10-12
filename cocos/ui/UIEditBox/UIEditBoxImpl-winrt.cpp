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
#include "CCWinRTUtils.h"

using namespace Platform;
using namespace Concurrency;
using namespace Windows::System;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::Foundation;
using namespace Windows::UI::ViewManagement;

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
    if (m_dispatcher.Get() == nullptr || m_panel.Get() == nullptr)
    {
        return;
    }

    // must create XAML element on main UI thread
    m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, strText]()
    {
        critical_section::scoped_lock lock(m_criticalSection);
        m_strText = strText;
        auto item = findXamlElement(m_panel.Get(), "cocos2d_editbox");
        if (item != nullptr)
        {
            Controls::Button^ button = dynamic_cast<Controls::Button^>(item);
            if (button)
            {
                m_flyout = dynamic_cast<Flyout^>(button->Flyout);
                if (m_flyout)
                {
                    if (m_inputFlag == EditBox::InputFlag::PASSWORD)
                    {
                        SetupPasswordBox();
                    }
                    else
                    {
                        SetupTextBox();
                    }

                    auto doneButton = findXamlElement(m_flyout->Content, "cocos2d_editbox_done");
                    if (doneButton != nullptr)
                    {
                        m_doneButton = dynamic_cast<Controls::Button^>(doneButton);
                        m_doneToken = m_doneButton->Click += ref new RoutedEventHandler(this, &EditBoxWinRT::Done);
                    }

                    auto cancelButton = findXamlElement(m_flyout->Content, "cocos2d_editbox_cancel");
                    if (cancelButton != nullptr)
                    {
                        m_cancelButton = dynamic_cast<Controls::Button^>(cancelButton);
                        m_cancelToken = m_cancelButton->Click += ref new RoutedEventHandler(this, &EditBoxWinRT::Cancel);
                    }
                }
            }

            if (m_flyout)
            {
                auto inputPane = InputPane::GetForCurrentView();
                m_hideKeyboardToken = inputPane->Hiding += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>(this, &EditBoxWinRT::HideKeyboard);

                m_closedToken = m_flyout->Closed += ref new EventHandler<Platform::Object^>(this, &EditBoxWinRT::Closed);
                m_flyout->ShowAt(m_panel.Get());
            }
        }
    }));
}

void EditBoxWinRT::Closed(Platform::Object^ sender, Platform::Object^ e)
{
    critical_section::scoped_lock lock(m_criticalSection);
    RemoveControls();
}

void EditBoxWinRT::Done(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    QueueText();
    HideFlyout();
}

void EditBoxWinRT::Cancel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    HideFlyout();
}

void EditBoxWinRT::HideKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args)
{
    // we don't want to hide the flyout when the user hide the keyboard
    //HideFlyout();
}

void EditBoxWinRT::HideFlyout()
{
    critical_section::scoped_lock lock(m_criticalSection);
    if (m_flyout)
    {
        m_flyout->Hide();
    }
}

void EditBoxWinRT::RemoveControls()
{
    if (m_dispatcher.Get() && m_panel.Get())
    {
        // run on main UI thread
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]()
        {
            critical_section::scoped_lock lock(m_criticalSection);

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

            m_textBox = nullptr;
            m_passwordBox = nullptr;

            if (m_flyout != nullptr)
            {
                m_flyout->Closed -= m_closedToken;
                m_flyout = nullptr;
            }

            auto inputPane = InputPane::GetForCurrentView();
            inputPane->Hiding -= m_hideKeyboardToken;
        }));
    }
}

void EditBoxWinRT::RemoveTextBox()
{
    auto g = findXamlElement(m_flyout->Content, "cocos2d_editbox_grid");
    auto grid = dynamic_cast<Grid^>(g);
    auto box = findXamlElement(m_flyout->Content, "cocos2d_editbox_textbox");

    if (box)
    {
        removeXamlElement(grid, box);
    }
}

void EditBoxWinRT::SetupTextBox()
{
    RemoveTextBox();
    m_textBox = ref new TextBox;
    m_textBox->Text = m_strText;
    m_textBox->Name = "cocos2d_editbox_textbox";
    m_textBox->MinWidth = 200;
    m_textBox->PlaceholderText = m_strPlaceholder;
    m_textBox->Select(m_textBox->Text->Length(), 0);
    m_textBox->MaxLength = m_maxLength < 0 ? 0 : m_maxLength;
    SetInputScope(m_textBox, m_inputMode);
    auto g = findXamlElement(m_flyout->Content, "cocos2d_editbox_grid");
    auto grid = dynamic_cast<Grid^>(g);
    grid->Children->InsertAt(0, m_textBox);
}

void EditBoxWinRT::SetupPasswordBox()
{
    RemoveTextBox();
    m_passwordBox = ref new PasswordBox();
    m_passwordBox->Password = m_strText;
    m_passwordBox->MinWidth = 200;
    m_passwordBox->Name = "cocos2d_editbox_textbox";
    m_passwordBox->SelectAll();
    m_passwordBox->PlaceholderText = m_strPlaceholder;
    m_passwordBox->MaxLength = m_maxLength < 0 ? 0 : m_maxLength;
    auto g = findXamlElement(m_flyout->Content, "cocos2d_editbox_grid");
    auto grid = dynamic_cast<Grid^>(g);
    grid->Children->InsertAt(0, m_passwordBox);
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

    box->InputScope = nullptr;
    inputScope->Names->Append(name);
    box->InputScope = inputScope;
}

void EditBoxWinRT::QueueText()
{
    critical_section::scoped_lock lock(m_criticalSection);
    if ((m_passwordBox == nullptr) && (m_textBox == nullptr))
    {
        return;
    }

    m_strText = m_inputFlag == EditBox::InputFlag::PASSWORD ? m_passwordBox->Password : m_textBox->Text;
    std::shared_ptr<cocos2d::InputEvent> e(new UIEditBoxEvent(this, m_strText, m_receiveHandler));
    cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(e);
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
    , m_eEditBoxInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
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
#if CC_ENABLE_SCRIPT_BINDING
    EditBox* pEditBox = this->getEditBox();
    if (NULL != pEditBox && 0 != pEditBox->getScriptEditBoxHandler())
    {
        CommonScriptData data(pEditBox->getScriptEditBoxHandler(), "began",pEditBox);
        ScriptEvent event(kCommonEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
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
            setText(PlatformStringToString(arg).c_str());
            if (_delegate != NULL) {
                _delegate->editBoxTextChanged(_editBox, getText());
                _delegate->editBoxEditingDidEnd(_editBox);
                _delegate->editBoxReturn(_editBox);
            }
        });

        m_editBoxWinrt = ref new EditBoxWinRT(PlatformStringFromString(placeHolder), PlatformStringFromString(getText()), m_nMaxLength, m_eEditBoxInputMode, m_eEditBoxInputFlag, receiveHandler);
    }

    m_editBoxWinrt->OpenXamlEditBox(PlatformStringFromString(getText()));
}

bool UIEditBoxImplWinrt::initWithSize( const Size& size )
{
    //! int fontSize = getFontSizeAccordingHeightJni(size.height-12);
    m_pLabel = Label::createWithSystemFont("", "", size.height-12);
    // align the text vertically center
    m_pLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    m_pLabel->setPosition(Vec2(5.0, size.height / 2.0f));
    m_pLabel->setTextColor(m_colText);
    _editBox->addChild(m_pLabel);

    m_pLabelPlaceHolder = Label::createWithSystemFont("", "", size.height-12);
    // align the text vertically center
    m_pLabelPlaceHolder->setAnchorPoint(Vec2(0.0f, 0.5f));
    m_pLabelPlaceHolder->setPosition(Vec2(5.0f, size.height / 2.0f));
    m_pLabelPlaceHolder->setVisible(false);
    m_pLabelPlaceHolder->setTextColor(m_colPlaceHolder);
    _editBox->addChild(m_pLabelPlaceHolder);

    m_EditSize = size;
    return true;
}

void UIEditBoxImplWinrt::setFont( const char* pFontName, int fontSize )
{
    if(m_pLabel != NULL)
    {
        if(strlen(pFontName) > 0)
        {
            m_pLabel->setSystemFontName(pFontName);
        }
        if(fontSize > 0)
        {
            m_pLabel->setSystemFontSize(fontSize);
        }
    }

    if(m_pLabelPlaceHolder != NULL) {
        if(strlen(pFontName) > 0)
        {
            m_pLabelPlaceHolder->setSystemFontName(pFontName);
        }
        if(fontSize > 0)
        {
            m_pLabelPlaceHolder->setSystemFontSize(fontSize);
        }
    }
}

void UIEditBoxImplWinrt::setFontColor( const Color4B& color )
{
    m_colText = color;
    m_pLabel->setTextColor(color);
}

void UIEditBoxImplWinrt::setPlaceholderFont( const char* pFontName, int fontSize )
{
    if(m_pLabelPlaceHolder != NULL)
    {
        if(strlen(pFontName) > 0)
        {
            m_pLabelPlaceHolder->setSystemFontName(pFontName);
        }
        if(fontSize > 0)
        {
            m_pLabelPlaceHolder->setSystemFontSize(fontSize);
        }
    }
}

void UIEditBoxImplWinrt::setPlaceholderFontColor( const Color4B& color )
{
    m_colPlaceHolder = color;
    m_pLabelPlaceHolder->setTextColor(color);
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
                long length = StringUtils::getCharacterCountInUTF8String(m_strText);
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

void UIEditBoxImplWinrt::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags)
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

}

NS_CC_END

#endif // WP8
