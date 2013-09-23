/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#ifndef __WP8_KEYBOARD_H__
#define __WP8_KEYBOARD_H__

NS_CC_BEGIN

ref class WP8Keyboard sealed
{
public:
	WP8Keyboard(Windows::UI::Core::CoreWindow^ parentWindow);

    void SetFocus(bool hasFocus);

	property bool HasFocus
    {
        bool get() { return m_hasFocus; }
    }

protected:
	void OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
    void OnCharacterReceived(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CharacterReceivedEventArgs^ args);
	void ShowKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args);
	void HideKeyboard(Windows::UI::ViewManagement::InputPane^ inputPane, Windows::UI::ViewManagement::InputPaneVisibilityEventArgs^ args);

private:
    ~WP8Keyboard();
    Platform::Agile<Windows::UI::Core::CoreWindow> m_parentWindow;
	Windows::Phone::UI::Core::KeyboardInputBuffer^ m_inputBuffer;
	Windows::Foundation::EventRegistrationToken m_keydownToken;
	Windows::Foundation::EventRegistrationToken m_characterReceivedToken;
	Windows::Foundation::EventRegistrationToken m_showKeyboardToken;
	Windows::Foundation::EventRegistrationToken m_hideKeyboardToken;

	bool m_hasFocus;

	Windows::Phone::UI::Core::CoreInputScope m_inputScope;
};

NS_CC_END

#endif    // end of __WP8_KEYBOARD_H__
