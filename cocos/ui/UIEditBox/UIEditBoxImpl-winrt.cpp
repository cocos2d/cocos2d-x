///****************************************************************************
//Copyright (c) 2014 cocos2d-x.org
//
//http://www.cocos2d-x.org
//
//* Portions Copyright (c) Microsoft Open Technologies, Inc.
//* All Rights Reserved
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
//****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "ui/UIEditBox/UIEditBoxImpl-winrt.h"
#include "platform/winrt/CCWinRTUtils.h"
#include "platform/winrt/CCGLViewImpl-winrt.h"
#include "2d/CCFontFreeType.h"

#if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#define XAML_TOP_PADDING 10.0f
#else
#define XAML_TOP_PADDING 0.0f
#endif

namespace cocos2d {

  namespace ui {

    Platform::String^ EDIT_BOX_XAML_NAME = L"cocos2d_editbox";
    Platform::String^ CANVAS_XAML_NAME = L"cocos2d_canvas";

    EditBoxImpl* __createSystemEditBox(EditBox* pEditBox)
    {
      return new UIEditBoxImplWinrt(pEditBox);
    }

    EditBoxWinRT::EditBoxWinRT(Windows::Foundation::EventHandler<Platform::String^>^ beginHandler,
      Windows::Foundation::EventHandler<Platform::String^>^ changeHandler,
      Windows::Foundation::EventHandler<cocos2d::EndEventArgs^>^ endHandler) :
      _beginHandler(beginHandler),
      _changeHandler(changeHandler),
      _endHandler(endHandler),
      _color(Windows::UI::Colors::White),
      _alignment(),
      _initialText(L""),
      _fontFamily(L"Segoe UI"),
      _fontSize(12),
      _password(false),
      _isEditing(false),
      _multiline(false),
      _maxLength(0 /* unlimited */)
    {
      m_dispatcher = cocos2d::GLViewImpl::sharedOpenGLView()->getDispatcher();
      m_panel = cocos2d::GLViewImpl::sharedOpenGLView()->getPanel();
    }

    void EditBoxWinRT::closeKeyboard()
    {
      m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
        removeTextBox();
        _textBox = nullptr;
        auto canvas = static_cast<Canvas^>(findXamlElement(m_panel.Get(), CANVAS_XAML_NAME));
        canvas->Visibility = Visibility::Collapsed;
      }));
    }

    Windows::UI::Xaml::Controls::Control^ EditBoxWinRT::createPasswordBox()
    {
      auto passwordBox = ref new PasswordBox;
      passwordBox->BorderThickness = 0;
      passwordBox->Name = EDIT_BOX_XAML_NAME;
      passwordBox->Width = _size.Width;
      passwordBox->Height = _size.Height;
      passwordBox->Foreground = ref new Media::SolidColorBrush(_color);
      passwordBox->FontSize = _fontSize;
      passwordBox->FontFamily = ref new Media::FontFamily(_fontFamily);
      passwordBox->MaxLength = _maxLength;
      passwordBox->Password = _initialText;
      _changeToken = passwordBox->PasswordChanged += ref new Windows::UI::Xaml::RoutedEventHandler(this, &cocos2d::ui::EditBoxWinRT::onPasswordChanged);
      return passwordBox;
    }

    Windows::UI::Xaml::Controls::Control^ EditBoxWinRT::createTextBox()
    {
      auto textBox = ref new TextBox;
      textBox->BorderThickness = 0;
      textBox->Name = EDIT_BOX_XAML_NAME;
      textBox->Width = _size.Width;
      textBox->Height = _size.Height;
      textBox->Foreground = ref new Media::SolidColorBrush(_color);
      textBox->FontSize = _fontSize;
      textBox->FontFamily = ref new Media::FontFamily(_fontFamily);
      textBox->MaxLength = _maxLength;
      textBox->AcceptsReturn = _multiline;
      textBox->TextWrapping = _multiline ? TextWrapping::Wrap : TextWrapping::NoWrap;
      textBox->Text = _initialText;
      setInputScope(textBox);
      _setTextHorizontalAlignment(textBox);
      _changeToken = textBox->TextChanged += ref new Windows::UI::Xaml::Controls::TextChangedEventHandler(this, &cocos2d::ui::EditBoxWinRT::onTextChanged);
      return textBox;
    }

    void EditBoxWinRT::onPasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
    {
      onTextChanged(sender, nullptr);
    }

    void EditBoxWinRT::onTextChanged(Platform::Object ^sender, Windows::UI::Xaml::Controls::TextChangedEventArgs ^e)
    {
      Platform::String^ text = L"";
      if (_password) {
        text = static_cast<PasswordBox^>(_textBox)->Password;
      }
      else {
        text = static_cast<TextBox^>(_textBox)->Text;
      }
      std::shared_ptr<cocos2d::InputEvent> inputEvent(new UIEditBoxEvent(this, text, _changeHandler));
      cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(inputEvent);
    }

    void EditBoxWinRT::onKeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args)
    {
      if (args->Key == Windows::System::VirtualKey::Enter && !_multiline) {
        onLostFocus(nullptr, args);
      }
      else if (args->Key == Windows::System::VirtualKey::Tab) {
        onLostFocus(nullptr, args);
      }
    }

    void EditBoxWinRT::onGotFocus(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^args)
    {
      Concurrency::critical_section::scoped_lock lock(_critical_section);
      std::shared_ptr<cocos2d::InputEvent> inputEvent(new UIEditBoxEvent(this, nullptr, _beginHandler));
      cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(inputEvent);
      _isEditing = true;
    }

    void EditBoxWinRT::onLostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs ^args)
    {
      EditBoxDelegate::EditBoxEndAction action = EditBoxDelegate::EditBoxEndAction::UNKNOWN;
      Windows::UI::Xaml::Input::KeyRoutedEventArgs^ keyArgs = dynamic_cast<Windows::UI::Xaml::Input::KeyRoutedEventArgs^>(args);
      if (keyArgs) {
        if (keyArgs->Key == Windows::System::VirtualKey::Enter && !_multiline) {
          action = EditBoxDelegate::EditBoxEndAction::RETURN;
        }
        else if (keyArgs->Key == Windows::System::VirtualKey::Tab) {
          action = EditBoxDelegate::EditBoxEndAction::TAB_TO_NEXT;
        }
      }

      _isEditing = false;
      Concurrency::critical_section::scoped_lock lock(_critical_section);
      Platform::String^ text = L"";
      if (_password) {
        text = static_cast<PasswordBox^>(_textBox)->Password;
        static_cast<PasswordBox^>(_textBox)->PasswordChanged -= _changeToken;
      }
      else {
        text = static_cast<TextBox^>(_textBox)->Text;
        static_cast<TextBox^>(_textBox)->TextChanged -= _changeToken;
      }

      std::shared_ptr<cocos2d::InputEvent> inputEvent(new UIEditBoxEndEvent(this, text, static_cast<int>(action), _endHandler));
      cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(inputEvent);

      _textBox->LostFocus -= _unfocusToken;
      _textBox->GotFocus -= _focusToken;
      _textBox->KeyDown -= _keydownToken;
      closeKeyboard();
    }

    bool EditBoxWinRT::isEditing() {
      return _isEditing;
    }

    void EditBoxWinRT::openKeyboard()
    {
      m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
        removeTextBox();
        Canvas^ canvas = static_cast<Canvas^>(findXamlElement(m_panel.Get(), CANVAS_XAML_NAME));

        if (_password) {
          _textBox = createPasswordBox();
        }
        else {
          _textBox = createTextBox();
        }

        // Position the text box
        canvas->SetLeft(_textBox, _rect.X);
        canvas->SetTop(_textBox, _rect.Y - XAML_TOP_PADDING);

        // Finally, insert it into the XAML scene hierarchy and make the containing canvas visible
        canvas->Children->InsertAt(0, _textBox);
        canvas->Background = ref new Media::SolidColorBrush();
        canvas->Visibility = Visibility::Visible;

        _keydownToken = _textBox->KeyDown += ref new Windows::UI::Xaml::Input::KeyEventHandler(this, &cocos2d::ui::EditBoxWinRT::onKeyDown);
        _focusToken = _textBox->GotFocus += ref new Windows::UI::Xaml::RoutedEventHandler(this, &cocos2d::ui::EditBoxWinRT::onGotFocus);
        _unfocusToken = _textBox->LostFocus += ref new Windows::UI::Xaml::RoutedEventHandler(this, &cocos2d::ui::EditBoxWinRT::onLostFocus);

        _textBox->Focus(FocusState::Programmatic);
        if (_password) {
          static_cast<PasswordBox^>(_textBox)->SelectAll();
        }
        else {
          static_cast<TextBox^>(_textBox)->Select(_initialText->Length(), 0);
        }

        auto inputPane = Windows::UI::ViewManagement::InputPane::GetForCurrentView();
      }));
    }

    void EditBoxWinRT::setFontColor(Windows::UI::Color color)
    {
      _color = color;
    }

    void EditBoxWinRT::setFontFamily(Platform::String^ fontFamily)
    {
      _fontFamily = fontFamily;
    }

    void EditBoxWinRT::setFontSize(int fontSize)
    {
      _fontSize = fontSize;
    }

    void EditBoxWinRT::removeTextBox()
    {
      auto canvas = findXamlElement(m_panel.Get(), CANVAS_XAML_NAME);
      auto box = findXamlElement(canvas, EDIT_BOX_XAML_NAME);
      removeXamlElement(canvas, box);
      _isEditing = false;
    }

    void EditBoxWinRT::setInputFlag(int inputFlags) {
      _password = false;
      switch ((EditBox::InputFlag)inputFlags) {
      case EditBox::InputFlag::PASSWORD:
        _password = true;
        break;
      default:
        CCLOG("Warning: cannot set INITIAL_CAPS_* input flags for WinRT edit boxes");
      }
    }

    void EditBoxWinRT::setInputMode(int inputMode) {
      _multiline = (EditBox::InputMode)inputMode == EditBox::InputMode::ANY;
      _inputMode = inputMode;
    }

    void EditBoxWinRT::setTextHorizontalAlignment(int alignment) {
      _alignment = alignment;
    }

    void EditBoxWinRT::setMaxLength(int maxLength) {
      _maxLength = maxLength;
    }

    void EditBoxWinRT::_setTextHorizontalAlignment(TextBox^ textBox)
    {
      switch (_alignment) {
        default:
        case 0:
          textBox->TextAlignment = TextAlignment::Left;
          break;
        case 1:
          textBox->TextAlignment = TextAlignment::Center;
          break;
        case 2:
          textBox->TextAlignment = TextAlignment::Right;
          break;
      }
    }

    void EditBoxWinRT::setInputScope(TextBox^ textBox)
    {
      InputScope^ inputScope = ref new InputScope;
      InputScopeName^ name = ref new InputScopeName;

      switch ((EditBox::InputMode)_inputMode) {
      case EditBox::InputMode::SINGLE_LINE:
      case EditBox::InputMode::ANY:
        name->NameValue = InputScopeNameValue::Default;
        break;
      case EditBox::InputMode::EMAIL_ADDRESS:
        name->NameValue = InputScopeNameValue::EmailSmtpAddress;
        break;
      case EditBox::InputMode::DECIMAL:
      case EditBox::InputMode::NUMERIC:
        name->NameValue = InputScopeNameValue::Number;
        break;
      case EditBox::InputMode::PHONE_NUMBER:
        name->NameValue = InputScopeNameValue::TelephoneNumber;
        break;
      case EditBox::InputMode::URL:
        name->NameValue = InputScopeNameValue::Url;
        break;
      }

      textBox->InputScope = nullptr;
      inputScope->Names->Append(name);
      textBox->InputScope = inputScope;
    }

    void EditBoxWinRT::setPosition(Windows::Foundation::Rect rect)
    {
      _rect = rect;
    }

    void EditBoxWinRT::setSize(Windows::Foundation::Size size)
    {
      _size = size;
    }

    void EditBoxWinRT::setText(Platform::String^ text)
    {
      _initialText = text;
      // If already editing
      if (_isEditing) {
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
          auto textBox = static_cast<TextBox^>(_textBox);
          unsigned int currentStart = textBox->SelectionStart;
          bool cursorAtEnd = currentStart == textBox->Text->Length();
          textBox->Text = _initialText;
          if (cursorAtEnd || currentStart > textBox->Text->Length()) {
            currentStart = textBox->Text->Length();
          }
          textBox->Select(currentStart, 0);
        }));
      }
    }

    void EditBoxWinRT::setVisible(bool visible)
    {
      _visible = visible;
      // If already editing
      m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([this]() {
        Canvas^ canvas = static_cast<Canvas^>(findXamlElement(m_panel.Get(), CANVAS_XAML_NAME));
        canvas->Visibility = _visible ? Visibility::Visible : Visibility::Collapsed;
      }));
    }




    UIEditBoxImplWinrt::UIEditBoxImplWinrt(EditBox* pEditText) : EditBoxImplCommon(pEditText)
    {
      auto beginHandler = ref new Windows::Foundation::EventHandler<Platform::String^>([this](Platform::Object^ sender, Platform::String^ arg) {
        this->editBoxEditingDidBegin();
      });
      auto changeHandler = ref new Windows::Foundation::EventHandler<Platform::String^>([this](Platform::Object^ sender, Platform::String^ arg) {
        auto text = PlatformStringToString(arg);
        this->editBoxEditingChanged(text);
      });
      auto endHandler = ref new Windows::Foundation::EventHandler<cocos2d::EndEventArgs^>([this](Platform::Object^ sender, cocos2d::EndEventArgs^ arg) {
        auto text = PlatformStringToString(arg->GetText());
        auto action = arg->GetAction();
        this->editBoxEditingDidEnd(text, static_cast<cocos2d::ui::EditBoxDelegate::EditBoxEndAction>(action));
        this->onEndEditing(text);
      });
      _system_control = ref new EditBoxWinRT(beginHandler, changeHandler, endHandler);
    }

    void UIEditBoxImplWinrt::setNativeFont(const char* pFontName, int fontSize)
    {
      // fontSize
      _fontSize = fontSize;
      auto transform = _editBox->getNodeToWorldTransform();
      cocos2d::Vec3 scale;
      transform.getScale(&scale);
      _system_control->setFontSize(_fontSize * cocos2d::Director::getInstance()->getOpenGLView()->getScaleY() /** scale.y*/);

      // fontFamily
      auto font = cocos2d::FontFreeType::create(pFontName, fontSize, cocos2d::GlyphCollection::DYNAMIC, nullptr);
      if (font != nullptr) {
        std::string fontName = "ms-appx:///Assets/Resources/" + std::string(pFontName) +'#' + font->getFontFamily();
        _system_control->setFontFamily(PlatformStringFromString(fontName));
      }
    }

    void UIEditBoxImplWinrt::setNativeFontColor(const Color4B& color)
    {
      Windows::UI::Color win_color = { 0xFF, color.r, color.g, color.b };
      _system_control->setFontColor(win_color);
    }

    void UIEditBoxImplWinrt::setNativeInputMode(EditBox::InputMode inputMode)
    {
      _system_control->setInputMode((int)inputMode);
    }

    void UIEditBoxImplWinrt::setNativeInputFlag(EditBox::InputFlag inputFlag)
    {
      _system_control->setInputFlag((int)inputFlag);
    }

    void UIEditBoxImplWinrt::setNativeTextHorizontalAlignment(cocos2d::TextHAlignment alignment)
    {
      _system_control->setTextHorizontalAlignment((int)alignment);
    }

    void UIEditBoxImplWinrt::setNativeText(const char* pText)
    {
      _system_control->setText(PlatformStringFromString(pText));
    }

    void UIEditBoxImplWinrt::setNativeVisible(bool visible)
    {
      _system_control->setVisible(visible);
    }

    void UIEditBoxImplWinrt::updateNativeFrame(const Rect& rect)
    {

    }

    void UIEditBoxImplWinrt::nativeOpenKeyboard()
    {
      // Update the text
      _system_control->setText(PlatformStringFromString(getText()));
      // Size
      auto glView = cocos2d::Director::getInstance()->getOpenGLView();
      auto transform = _editBox->getNodeToWorldTransform();
      cocos2d::Vec3 scale;
      transform.getScale(&scale);
      Windows::Foundation::Size xamlSize = { _editBox->getContentSize().width * glView->getScaleX() * scale.x, _editBox->getContentSize().height * glView->getScaleY() * scale.y };
      _system_control->setSize(xamlSize);
      _system_control->setFontSize(_fontSize * cocos2d::Director::getInstance()->getOpenGLView()->getScaleY() /** scale.y*/);
      // Position
      auto directorInstance = cocos2d::Director::getInstance();
      auto frameSize = glView->getFrameSize();
      auto winSize = directorInstance->getWinSize();
      auto leftBottom = _editBox->convertToWorldSpace(cocos2d::Point::ZERO);
      auto rightTop = _editBox->convertToWorldSpace(cocos2d::Point(_editBox->getContentSize().width, _editBox->getContentSize().height));
      Windows::Foundation::Rect rect;
      rect.X = frameSize.width / 2 + (leftBottom.x - winSize.width / 2) * glView->getScaleX();
      rect.Y = frameSize.height / 2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
      rect.Width = (rightTop.x - leftBottom.x) * glView->getScaleX();
      rect.Height = (rightTop.y - leftBottom.y) * glView->getScaleY();
      _system_control->setPosition(rect);
      // .. and open
      _system_control->openKeyboard();
    }

    void UIEditBoxImplWinrt::nativeCloseKeyboard()
    {
      _system_control->closeKeyboard();
    }

    void UIEditBoxImplWinrt::setNativeMaxLength(int maxLength)
    {
      _system_control->setMaxLength(maxLength);
    }

    cocos2d::Vec2 UIEditBoxImplWinrt::convertDesignCoordToXamlCoord(const cocos2d::Vec2& designCoord)
    {
      auto glView = cocos2d::Director::getInstance()->getOpenGLView();
      float viewH = glView->getFrameSize().height;
      Vec2 visiblePos = Vec2(designCoord.x * glView->getScaleX(), designCoord.y * glView->getScaleY());
      Vec2 screenGLPos = visiblePos + glView->getViewPortRect().origin;
      Vec2 xamlPos(screenGLPos.x, viewH - screenGLPos.y);
      return xamlPos;
    }

  } // namespace ui

} // namespace cocos2d

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
