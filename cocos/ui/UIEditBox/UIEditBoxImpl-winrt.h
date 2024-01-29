/****************************************************************************
Copyright (c) 2014 cocos2d-x.org
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __UIEditBoxIMPLWINRT_H__
#define __UIEditBoxIMPLWINRT_H__

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "ui/UIEditBox/UIEditBoxImpl-common.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

NS_CC_BEGIN

namespace ui {

  ref class EditBoxWinRT sealed
  {
  public:
    EditBoxWinRT(Windows::Foundation::EventHandler<Platform::String^>^ beginHandler,
      Windows::Foundation::EventHandler<Platform::String^>^ changeHandler,
      Windows::Foundation::EventHandler<cocos2d::EndEventArgs^>^ endHandler);

    void closeKeyboard();
    bool isEditing();
    void openKeyboard();
    void setFontColor(Windows::UI::Color color);
    void setFontFamily(Platform::String^ fontFamily);
    void setFontSize(int fontSize);
    void setInputFlag(int inputFlags);
    void setInputMode(int inputMode);
    void setTextHorizontalAlignment(int alignment);
    void setMaxLength(int maxLength);
    void setPosition(Windows::Foundation::Rect rect);
    void setSize(Windows::Foundation::Size size);
    void setText(Platform::String^ text);
    void setVisible(bool visible);

  private:

    void EditBoxWinRT::onPasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    void EditBoxWinRT::onTextChanged(Platform::Object ^sender, Windows::UI::Xaml::Controls::TextChangedEventArgs ^e);
    void EditBoxWinRT::onKeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args);
    void EditBoxWinRT::onGotFocus(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^args);
    void EditBoxWinRT::onLostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs ^args);

    Windows::UI::Xaml::Controls::Control^ createPasswordBox();
    Windows::UI::Xaml::Controls::Control^ createTextBox();
    void removeTextBox();
    void setInputScope(TextBox^ textBox);
    void _setTextHorizontalAlignment(TextBox^ textBox);
	void _setTexVerticalAlignment(Windows::UI::Xaml::Controls::Control^ textBox);
	void _setPadding(Windows::UI::Xaml::Controls::Control^ editBox);

    // Properties
    Windows::Foundation::Rect _rect;
    Windows::Foundation::Size _size;
    Windows::UI::Color _color;
    Platform::String^ _initialText;
    int _fontSize;
    Platform::String^ _fontFamily;
    int _alignment;
    int _inputMode;
    int _inputFlag;
    bool _password;
    bool _isEditing;
    bool _visible;
    bool _multiline;
    int _maxLength;

    // The actual edit box, however, could be a TextBox, PasswordBox, or a SearchBox (not yet implemented)
    Windows::UI::Xaml::Controls::Control^ _textBox = nullptr;

    Platform::Agile<Windows::UI::Core::CoreDispatcher> m_dispatcher = nullptr;
    Platform::Agile<Windows::UI::Xaml::Controls::Panel> m_panel = nullptr;
    Concurrency::critical_section _critical_section;

    Windows::Foundation::EventHandler<Platform::String^>^ _beginHandler = nullptr;
    Windows::Foundation::EventHandler<Platform::String^>^ _changeHandler = nullptr;
    Windows::Foundation::EventHandler<EndEventArgs^>^ _endHandler = nullptr;

    Windows::Foundation::EventRegistrationToken _unfocusToken;
    Windows::Foundation::EventRegistrationToken _changeToken;
    Windows::Foundation::EventRegistrationToken _focusToken;
    Windows::Foundation::EventRegistrationToken _keydownToken;
  };

  class CC_GUI_DLL UIEditBoxImplWinrt : public EditBoxImplCommon
  {
  public:
    /**
    * @js NA
    */
    UIEditBoxImplWinrt(EditBox* pEditText);

    /**
    * @js NA
    * @lua NA
    */
    virtual ~UIEditBoxImplWinrt() { };

    virtual bool isEditing() override { return _system_control->isEditing(); }
    virtual void createNativeControl(const Rect& frame) override {  }
    virtual void setNativeFont(const char* pFontName, int fontSize) override;
    virtual void setNativeFontColor(const Color4B& color) override;
    virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) override { CCLOG("Warning! You can't change WinRT placeholder font"); }
    virtual void setNativePlaceholderFontColor(const Color4B& color) override { CCLOG("Warning! You can't change WinRT placeholder font color"); }
    virtual void setNativeInputMode(EditBox::InputMode inputMode) override;
    virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) override;
    virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) override { CCLOG("Warning! You can't change WinRT return type"); }
    virtual void setNativeTextHorizontalAlignment(cocos2d::TextHAlignment alignment);
    virtual void setNativeText(const char* pText) override;
    virtual void setNativePlaceHolder(const char* pText) override { CCLOG("Warning! You can't change WinRT placeholder text"); }
    virtual void setNativeVisible(bool visible) override;
    virtual void updateNativeFrame(const Rect& rect) override; // TODO
    virtual const char* getNativeDefaultFontName() override { return "Segoe UI"; }
    virtual void nativeOpenKeyboard();
    virtual void nativeCloseKeyboard() override;
    virtual void setNativeMaxLength(int maxLength) override;

  private:
    cocos2d::Vec2 convertDesignCoordToXamlCoord(const cocos2d::Vec2& designCoord);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance) override { CCLOG("Warning! doAnimationWhenKeyboardMove not supported on WinRT"); }

    EditBoxWinRT^ _system_control;
    int _fontSize;
  };

} // namespace ui

NS_CC_END

#endif // CC_PLATFORM_WINRT

#endif // #ifdef __UIEditBoxIMPLWINRT_H__


