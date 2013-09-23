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
#include "cocos2d.h"
#include "WP8Keyboard.h"

using namespace cocos2d;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::Phone::UI::Core;
using namespace Windows::System;
using namespace Platform;
using namespace Windows::UI::ViewManagement;

NS_CC_BEGIN

WP8Keyboard::WP8Keyboard(CoreWindow^ parentWindow)
{
	m_parentWindow = parentWindow;
	m_inputBuffer = ref new KeyboardInputBuffer();

    auto inputPane = InputPane::GetForCurrentView();
	m_showKeyboardToken = inputPane->Showing += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>(this, &WP8Keyboard::ShowKeyboard);
	m_hideKeyboardToken = inputPane->Hiding += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>(this, &WP8Keyboard::HideKeyboard);
}

WP8Keyboard::~WP8Keyboard()
{
    auto inputPane = InputPane::GetForCurrentView();
    if(inputPane)
    {
        inputPane->Showing -= m_showKeyboardToken;
        inputPane->Hiding  -= m_hideKeyboardToken;
    }
}


void WP8Keyboard::ShowKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->ShowKeyboard(args->OccludedRect);
}

void WP8Keyboard::HideKeyboard(InputPane^ inputPane, InputPaneVisibilityEventArgs^ args)
{
    CCEGLView::sharedOpenGLView()->HideKeyboard(args->OccludedRect);
}


void WP8Keyboard::SetFocus(bool hasFocus)
{
	m_hasFocus = hasFocus;

	if(m_hasFocus)
	{
		m_inputBuffer->InputScope = CoreInputScope::Default;
		m_parentWindow->IsKeyboardInputEnabled = true;
		m_keydownToken = m_parentWindow->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &WP8Keyboard::OnKeyDown);	
		m_characterReceivedToken = m_parentWindow->CharacterReceived += ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &WP8Keyboard::OnCharacterReceived); 
	}
	else
	{
		m_parentWindow->IsKeyboardInputEnabled = false;
		m_parentWindow->KeyDown -= m_keydownToken;
		m_parentWindow->CharacterReceived -= m_characterReceivedToken;
	}
}

void WP8Keyboard::OnKeyDown(CoreWindow^ sender, KeyEventArgs^ args)
{
	if(!m_hasFocus)
	{
		return;
	}

	args->Handled = true;

    auto key = args->VirtualKey;

    switch(key)
    {
    case VirtualKey::Escape:
        CCDirector::sharedDirector()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
		args->Handled = true;
        break;
	case VirtualKey::Back:
        CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
        break;
    case VirtualKey::Enter:
		SetFocus(false);
        CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
        break;
    default:
        break;
    }	
}

void WP8Keyboard::OnCharacterReceived(CoreWindow^ sender, CharacterReceivedEventArgs^ args)
{
	wchar_t c = args->KeyCode;
    char szUtf8[8] = {0};
    int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&c, 1, szUtf8, sizeof(szUtf8), NULL, NULL);
    CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
}

NS_CC_END
