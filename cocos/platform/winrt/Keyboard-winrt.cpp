/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
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

#include "platform/winrt/Keyboard-winrt.h"
#include "base/CCEventKeyboard.h"
#include "platform/winrt/CCGLViewImpl-winrt.h"
#include "base/CCIMEDispatcher.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

using namespace cocos2d;
using namespace Platform;
using namespace Windows::System;
using namespace Windows::System::Threading;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

NS_CC_BEGIN

struct keyCodeItem
{
    int key;
    EventKeyboard::KeyCode keyCode;
};

static std::map<int, EventKeyboard::KeyCode> g_keyCodeMap;

// http://www.kbdedit.com/manual/low_level_vk_list.html
// https://msdn.microsoft.com/library/windows/apps/windows.system.virtualkey.aspx

static keyCodeItem g_keyCodeStructArray [] = {
    /* The unknown key */
    { (int) VirtualKey::None, EventKeyboard::KeyCode::KEY_NONE },
    /* Printable keys */
    { (int) VirtualKey::Space, EventKeyboard::KeyCode::KEY_SPACE },
    { (int) VK_OEM_7, EventKeyboard::KeyCode::KEY_APOSTROPHE },
    { (int) VK_OEM_COMMA, EventKeyboard::KeyCode::KEY_COMMA },
    { (int) VK_OEM_MINUS, EventKeyboard::KeyCode::KEY_MINUS },
    { (int) VK_OEM_PERIOD, EventKeyboard::KeyCode::KEY_PERIOD },
    { (int) VK_OEM_2, EventKeyboard::KeyCode::KEY_SLASH },
    { (int) VK_OEM_3, EventKeyboard::KeyCode::KEY_TILDE },

    { (int) VirtualKey::Number0, EventKeyboard::KeyCode::KEY_0 },
    { (int) VirtualKey::Number1, EventKeyboard::KeyCode::KEY_1 },
    { (int) VirtualKey::Number2, EventKeyboard::KeyCode::KEY_2 },
    { (int) VirtualKey::Number3, EventKeyboard::KeyCode::KEY_3 },
    { (int) VirtualKey::Number4, EventKeyboard::KeyCode::KEY_4 },
    { (int) VirtualKey::Number5, EventKeyboard::KeyCode::KEY_5 },
    { (int) VirtualKey::Number6, EventKeyboard::KeyCode::KEY_6 },
    { (int) VirtualKey::Number7, EventKeyboard::KeyCode::KEY_7 },
    { (int) VirtualKey::Number8, EventKeyboard::KeyCode::KEY_8 },
    { (int) VirtualKey::Number9, EventKeyboard::KeyCode::KEY_9 },
    { (int) VK_OEM_1, EventKeyboard::KeyCode::KEY_SEMICOLON },
    { (int) VK_OEM_PLUS, EventKeyboard::KeyCode::KEY_EQUAL },
    { (int) VirtualKey::A, EventKeyboard::KeyCode::KEY_A },
    { (int) VirtualKey::B, EventKeyboard::KeyCode::KEY_B },
    { (int) VirtualKey::C, EventKeyboard::KeyCode::KEY_C },
    { (int) VirtualKey::D, EventKeyboard::KeyCode::KEY_D },
    { (int) VirtualKey::E, EventKeyboard::KeyCode::KEY_E },
    { (int) VirtualKey::F, EventKeyboard::KeyCode::KEY_F },
    { (int) VirtualKey::G, EventKeyboard::KeyCode::KEY_G },
    { (int) VirtualKey::H, EventKeyboard::KeyCode::KEY_H },
    { (int) VirtualKey::I, EventKeyboard::KeyCode::KEY_I },
    { (int) VirtualKey::J, EventKeyboard::KeyCode::KEY_J },
    { (int) VirtualKey::K, EventKeyboard::KeyCode::KEY_K },
    { (int) VirtualKey::L, EventKeyboard::KeyCode::KEY_L },
    { (int) VirtualKey::M, EventKeyboard::KeyCode::KEY_M },
    { (int) VirtualKey::N, EventKeyboard::KeyCode::KEY_N },
    { (int) VirtualKey::O, EventKeyboard::KeyCode::KEY_O },
    { (int) VirtualKey::P, EventKeyboard::KeyCode::KEY_P },
    { (int) VirtualKey::Q, EventKeyboard::KeyCode::KEY_Q },
    { (int) VirtualKey::R, EventKeyboard::KeyCode::KEY_R },
    { (int) VirtualKey::S, EventKeyboard::KeyCode::KEY_S },
    { (int) VirtualKey::T, EventKeyboard::KeyCode::KEY_T },
    { (int) VirtualKey::U, EventKeyboard::KeyCode::KEY_U },
    { (int) VirtualKey::V, EventKeyboard::KeyCode::KEY_V },
    { (int) VirtualKey::W, EventKeyboard::KeyCode::KEY_W },
    { (int) VirtualKey::X, EventKeyboard::KeyCode::KEY_X },
    { (int) VirtualKey::Y, EventKeyboard::KeyCode::KEY_Y },
    { (int) VirtualKey::Z, EventKeyboard::KeyCode::KEY_Z },
    { VK_OEM_4, EventKeyboard::KeyCode::KEY_LEFT_BRACKET },
    { VK_OEM_5, EventKeyboard::KeyCode::KEY_BACK_SLASH },
    { VK_OEM_6, EventKeyboard::KeyCode::KEY_RIGHT_BRACKET },
    //	{ GLFW_KEY_GRAVE_ACCENT			, EventKeyboard::KeyCode::KEY_GRAVE },

    /* Function keys */
    { (int) VirtualKey::Escape, EventKeyboard::KeyCode::KEY_ESCAPE },
    { (int) VirtualKey::Enter, EventKeyboard::KeyCode::KEY_ENTER },
    { (int) VirtualKey::Tab, EventKeyboard::KeyCode::KEY_TAB },
    { (int) VirtualKey::Back, EventKeyboard::KeyCode::KEY_BACKSPACE },
    { (int) VirtualKey::Insert, EventKeyboard::KeyCode::KEY_INSERT },
    { (int) VirtualKey::Delete, EventKeyboard::KeyCode::KEY_DELETE },
    { (int) VirtualKey::Right, EventKeyboard::KeyCode::KEY_RIGHT_ARROW },
    { (int) VirtualKey::Left, EventKeyboard::KeyCode::KEY_LEFT_ARROW },
    { (int) VirtualKey::Down, EventKeyboard::KeyCode::KEY_DOWN_ARROW },
    { (int) VirtualKey::Up, EventKeyboard::KeyCode::KEY_UP_ARROW },
    { VK_PRIOR, EventKeyboard::KeyCode::KEY_PG_UP },
    { VK_NEXT, EventKeyboard::KeyCode::KEY_PG_DOWN },
    { VK_HOME, EventKeyboard::KeyCode::KEY_HOME },
    { VK_END, EventKeyboard::KeyCode::KEY_END },
    { VK_CAPITAL, EventKeyboard::KeyCode::KEY_CAPS_LOCK },
    { VK_SCROLL, EventKeyboard::KeyCode::KEY_SCROLL_LOCK },
    { VK_NUMLOCK, EventKeyboard::KeyCode::KEY_NUM_LOCK },
    { VK_SNAPSHOT, EventKeyboard::KeyCode::KEY_PRINT },
    { VK_PAUSE, EventKeyboard::KeyCode::KEY_PAUSE },
    { (int) VirtualKey::F1, EventKeyboard::KeyCode::KEY_F1 },
    { (int) VirtualKey::F2, EventKeyboard::KeyCode::KEY_F2 },
    { (int) VirtualKey::F3, EventKeyboard::KeyCode::KEY_F3 },
    { (int) VirtualKey::F4, EventKeyboard::KeyCode::KEY_F4 },
    { (int) VirtualKey::F5, EventKeyboard::KeyCode::KEY_F5 },
    { (int) VirtualKey::F6, EventKeyboard::KeyCode::KEY_F6 },
    { (int) VirtualKey::F7, EventKeyboard::KeyCode::KEY_F7 },
    { (int) VirtualKey::F8, EventKeyboard::KeyCode::KEY_F8 },
    { (int) VirtualKey::F9, EventKeyboard::KeyCode::KEY_F9 },
    { (int) VirtualKey::F10, EventKeyboard::KeyCode::KEY_F10 },
    { (int) VirtualKey::F11, EventKeyboard::KeyCode::KEY_F11 },
    { (int) VirtualKey::F12, EventKeyboard::KeyCode::KEY_F12 },
    { (int) VirtualKey::F13, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F14, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F15, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F16, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F17, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F18, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F19, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F20, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F21, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F22, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F23, EventKeyboard::KeyCode::KEY_NONE },
    { (int) VirtualKey::F24, EventKeyboard::KeyCode::KEY_NONE },

    { (int) VirtualKey::NumberPad0, EventKeyboard::KeyCode::KEY_0 },
    { (int) VirtualKey::NumberPad1, EventKeyboard::KeyCode::KEY_1 },
    { (int) VirtualKey::NumberPad2, EventKeyboard::KeyCode::KEY_2 },
    { (int) VirtualKey::NumberPad3, EventKeyboard::KeyCode::KEY_3 },
    { (int) VirtualKey::NumberPad4, EventKeyboard::KeyCode::KEY_4 },
    { (int) VirtualKey::NumberPad5, EventKeyboard::KeyCode::KEY_5 },
    { (int) VirtualKey::NumberPad6, EventKeyboard::KeyCode::KEY_6 },
    { (int) VirtualKey::NumberPad7, EventKeyboard::KeyCode::KEY_7 },
    { (int) VirtualKey::NumberPad8, EventKeyboard::KeyCode::KEY_8 },
    { (int) VirtualKey::NumberPad9, EventKeyboard::KeyCode::KEY_9 },
#if 0
    { GLFW_KEY_KP_1, EventKeyboard::KeyCode::KEY_1 },
    { GLFW_KEY_KP_2, EventKeyboard::KeyCode::KEY_2 },
    { GLFW_KEY_KP_3, EventKeyboard::KeyCode::KEY_3 },
    { GLFW_KEY_KP_4, EventKeyboard::KeyCode::KEY_4 },
    { GLFW_KEY_KP_5, EventKeyboard::KeyCode::KEY_5 },
    { GLFW_KEY_KP_6, EventKeyboard::KeyCode::KEY_6 },
    { GLFW_KEY_KP_7, EventKeyboard::KeyCode::KEY_7 },
    { GLFW_KEY_KP_8, EventKeyboard::KeyCode::KEY_8 },
    { GLFW_KEY_KP_9, EventKeyboard::KeyCode::KEY_9 },
#endif
    { (int) VirtualKey::Decimal, EventKeyboard::KeyCode::KEY_PERIOD },
    { (int) VirtualKey::Divide, EventKeyboard::KeyCode::KEY_KP_DIVIDE },
    { (int) VirtualKey::Multiply, EventKeyboard::KeyCode::KEY_KP_MULTIPLY },
    { (int) VirtualKey::Subtract, EventKeyboard::KeyCode::KEY_KP_MINUS },
    { (int) VirtualKey::Add, EventKeyboard::KeyCode::KEY_KP_PLUS },
    //{ GLFW_KEY_KP_ENTER        , EventKeyboard::KeyCode::KEY_KP_ENTER },
    //{ GLFW_KEY_KP_EQUAL        , EventKeyboard::KeyCode::KEY_EQUAL },
    { (int) VirtualKey::Shift, EventKeyboard::KeyCode::KEY_LEFT_SHIFT },
    { (int) VirtualKey::Control, EventKeyboard::KeyCode::KEY_LEFT_CTRL },
    { VK_LMENU, EventKeyboard::KeyCode::KEY_LEFT_ALT },
    { (int) VirtualKey::LeftWindows, EventKeyboard::KeyCode::KEY_HYPER },
    { (int) VirtualKey::RightShift, EventKeyboard::KeyCode::KEY_RIGHT_SHIFT },
    { (int) VirtualKey::RightControl, EventKeyboard::KeyCode::KEY_RIGHT_CTRL },
    { VK_RMENU, EventKeyboard::KeyCode::KEY_RIGHT_ALT },
    { (int) VirtualKey::RightWindows, EventKeyboard::KeyCode::KEY_HYPER },
    { (int) VirtualKey::Menu, EventKeyboard::KeyCode::KEY_MENU },
    { (int) VirtualKey::LeftMenu, EventKeyboard::KeyCode::KEY_MENU },
    { (int) VirtualKey::RightMenu, EventKeyboard::KeyCode::KEY_MENU }
};

KeyBoardWinRT::KeyBoardWinRT()
{
    g_keyCodeMap.clear();
    for (auto& item : g_keyCodeStructArray)
    {
        g_keyCodeMap[item.key] = item.keyCode;
    }
}

KeyBoardWinRT::~KeyBoardWinRT()
{

}


void KeyBoardWinRT::ShowKeyboard(Platform::String^ text)
{
    auto panel = cocos2d::GLViewImpl::sharedOpenGLView()->getPanel();
    auto dispatcher = cocos2d::GLViewImpl::sharedOpenGLView()->getDispatcher();

    if (dispatcher && panel)
    {
        // run on main UI thread
        dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, text, panel]()
        {
            if (m_textBox == nullptr)
            {
                m_textBox = ref new TextBox();
                m_textBox->Opacity = 0.0;
                m_textBox->Width = 1;
                m_textBox->Height = 1;
                m_textBox->TextChanged += ref new TextChangedEventHandler(this, &KeyBoardWinRT::OnTextChanged);
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
                // Need to use InputScopeNameValue::Search to prevent auto-capitalize
                m_textBox->InputScope = ref new InputScope();
                auto n = m_textBox->InputScope->Names;
                n->Append(ref new InputScopeName(InputScopeNameValue::Search));
#endif
                panel->Children->Append(m_textBox);
            }
            m_textBox->SelectionLength = 0;
            m_textBox->SelectionStart = 32768;
            m_textBox->Focus(FocusState::Programmatic);
        }));
    }
}

void KeyBoardWinRT::HideKeyboard(Platform::String^ text)
{
    auto panel = cocos2d::GLViewImpl::sharedOpenGLView()->getPanel();
    auto dispatcher = cocos2d::GLViewImpl::sharedOpenGLView()->getDispatcher();

    if (dispatcher && panel)
    {
        // run on main UI thread
        dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, text, panel]()
        {
            if (m_textBox != nullptr)
            {
                unsigned int index;
                if (panel->Children->IndexOf(m_textBox, &index))
                {
                    panel->Children->RemoveAt(index);
                }
            }
            m_textBox = nullptr;
        }));
    }
}

void KeyBoardWinRT::OnWinRTKeyboardEvent(WinRTKeyboardEventType type, KeyEventArgs^ args)
{
    bool pressed = (type == WinRTKeyboardEventType::KeyPressed);

    // Is key repeats
    bool repeat = pressed && args->KeyStatus.WasKeyDown;

    int key = static_cast<int>(args->VirtualKey);
    auto it = g_keyCodeMap.find(key);
    if (it != g_keyCodeMap.end())
    {

        EventKeyboard::KeyCode keyCode = it->second;

        EventKeyboard event(keyCode, pressed);
        if (!repeat)
        {
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->dispatchEvent(&event);
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
            {
                IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
            }
        }

        if (pressed && !event.isStopped())
        {
            switch (keyCode)
            {
            case EventKeyboard::KeyCode::KEY_BACKSPACE:
                IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
                break;
            case EventKeyboard::KeyCode::KEY_HOME:
            case EventKeyboard::KeyCode::KEY_KP_HOME:
            case EventKeyboard::KeyCode::KEY_DELETE:
            case EventKeyboard::KeyCode::KEY_KP_DELETE:
            case EventKeyboard::KeyCode::KEY_END:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                IMEDispatcher::sharedDispatcher()->dispatchControlKey(keyCode);
                break;
            default:
                break;
            }
        }
    }
    else
    {
        log("GLViewImpl::OnWinRTKeyboardEvent Virtual Key Code %d not supported", key);
    }
}

void KeyBoardWinRT::OnTextChanged(Platform::Object^ sender, TextChangedEventArgs^ args)
{
    auto text = m_textBox->Text;
    if (text)
    {
        std::shared_ptr<cocos2d::InputEvent> e(new cocos2d::KeyboardEvent(Cocos2dKeyEvent::Text, text));
        cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(e);
        m_textBox->Text = L"";
    }
}


NS_CC_END

