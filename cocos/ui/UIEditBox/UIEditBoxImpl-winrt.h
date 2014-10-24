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
#ifndef __UIEditBoxIMPLWINRT_H__
#define __UIEditBoxIMPLWINRT_H__

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "UIEditBoxImpl.h"

NS_CC_BEGIN

namespace ui {
    class EditBox;
  
    ref class EditBoxWinRT sealed
    {
    public:
        EditBoxWinRT();
        virtual ~EditBoxWinRT();
    internal:

        EditBoxWinRT(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, EditBox::InputMode inputMode, EditBox::InputFlag inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler);
        void OpenXamlEditBox(Platform::String^ strText);

    private:
        Windows::UI::Xaml::Controls::Control^ CreateTextBox(int maxLength);
        Windows::UI::Xaml::Controls::Control^ CreatePasswordBox(int maxLength);
        void SetInputScope(Windows::UI::Xaml::Controls::TextBox^ box, EditBox::InputMode inputMode);

        void EditBoxWinRT::SetupTextBox();
        void EditBoxWinRT::SetupPasswordBox();
        void EditBoxWinRT::RemoveTextBox();
        void RemoveControls();
        void QueueText();

        void Done(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void Cancel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void Closed(Platform::Object^ sender, Platform::Object^ e);
        void HideKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args);
        void HideFlyout();

        Platform::Agile<Windows::UI::Core::CoreDispatcher> m_dispatcher;
        Platform::Agile<Windows::UI::Xaml::Controls::Panel> m_panel;
        Windows::Foundation::EventHandler<Platform::String^>^ m_receiveHandler;

        Windows::UI::Xaml::Controls::TextBox^ m_textBox;
        Windows::UI::Xaml::Controls::PasswordBox^ m_passwordBox;
        Windows::UI::Xaml::Controls::Flyout^ m_flyout;
        Windows::UI::Xaml::Controls::Button^ m_doneButton;
        Windows::UI::Xaml::Controls::Button^ m_cancelButton;

        Windows::Foundation::EventRegistrationToken m_doneToken;
        Windows::Foundation::EventRegistrationToken m_cancelToken;
        Windows::Foundation::EventRegistrationToken m_closedToken;
        Windows::Foundation::EventRegistrationToken m_hideKeyboardToken;

        Concurrency::critical_section m_criticalSection;

        Platform::String^ m_strText;
        Platform::String^ m_strPlaceholder;
        EditBox::InputMode m_inputMode;
        EditBox::InputFlag m_inputFlag;
        int m_maxLength;
    };

    class CC_GUI_DLL UIEditBoxImplWinrt : public EditBoxImpl
    {
    public:
        UIEditBoxImplWinrt(EditBox* pEditText);
        virtual ~UIEditBoxImplWinrt();
        
        virtual bool initWithSize(const Size& size);
        virtual void setFont(const char* pFontName, int fontSize);
        virtual void setFontColor(const Color3B& color);
        virtual void setPlaceholderFont(const char* pFontName, int fontSize);
        virtual void setPlaceholderFontColor(const Color3B& color);
        virtual void setInputMode(EditBox::InputMode inputMode);
        virtual void setInputFlag(EditBox::InputFlag inputFlag);
        virtual void setMaxLength(int maxLength);
        virtual int  getMaxLength();
        virtual void setReturnType(EditBox::KeyboardReturnType returnType);
        virtual bool isEditing();
        
        virtual void setText(const char* pText);
        virtual const char* getText(void);
        virtual void setPlaceHolder(const char* pText);
        virtual void setPosition(const Vec2& pos);
        virtual void setVisible(bool visible);
        virtual void setContentSize(const Size& size);
        virtual void setAnchorPoint(const Vec2& anchorPoint);
        virtual void visit(void);
        virtual void doAnimationWhenKeyboardMove(float duration, float distance);
        virtual void openKeyboard();
        virtual void closeKeyboard();
        virtual void onEnter(void);
    private:
        Platform::String^ stringToPlatformString(std::string strSrc);
        std::string PlatformStringTostring(Platform::String^ strSrc);
    private:
        
        EditBoxWinRT^ m_editBoxWinrt;

        Label* m_pLabel;
        Label* m_pLabelPlaceHolder;
        EditBox::InputMode    m_eEditBoxInputMode;
        EditBox::InputFlag    m_eEditBoxInputFlag;
        (EditBox::KeyboardReturnType  m_eKeyboardReturnType;
         
         std::string m_strText;
         std::string m_strPlaceHolder;
         
         Color3B m_colText;
         Color3B m_colPlaceHolder;
         
         int   m_nMaxLength;
         Size m_EditSize;
    };
}

NS_CC_END

#endif //CC_PLATFORM_WINRT

#endif
