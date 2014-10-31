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

#include "Keyboard-winrt.h"

using namespace cocos2d;
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

KeyBoardWinRT::KeyBoardWinRT()
{

}

KeyBoardWinRT::~KeyBoardWinRT()
{

}

KeyBoardWinRT::KeyBoardWinRT(Windows::UI::Core::CoreDispatcher^ dispatcher, Windows::UI::Xaml::Controls::Panel^ panel)
    : m_dispatcher(dispatcher)
    , m_panel(panel)
{

}

void KeyBoardWinRT::ShowKeyboard(Platform::String^ text)
{
    if (m_dispatcher.Get() && m_panel.Get())
    {
        // run on main UI thread
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, text]()
        {
            if (m_textBox == nullptr)
            {
                m_textBox = ref new TextBox();
                m_textBox->Opacity = 0.0;
                m_textBox->Width = 1;
                m_textBox->Height = 1;
                m_textBox->AddHandler(UIElement::KeyDownEvent, ref new KeyEventHandler(this, &KeyBoardWinRT::OnKeyPressed), true);
                m_textBox->AddHandler(UIElement::KeyUpEvent, ref new KeyEventHandler(this, &KeyBoardWinRT::OnKeyReleased), true);
                m_textBox->TextChanged += ref new TextChangedEventHandler(this, &KeyBoardWinRT::OnTextChanged);
#if (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
                // Need to use InputScopeNameValue::Search to prevent auto-capitalize
                m_textBox->InputScope = ref new InputScope();
                auto n = m_textBox->InputScope->Names;
                n->Append(ref new InputScopeName(InputScopeNameValue::Search));
#endif
                m_panel.Get()->Children->Append(m_textBox);
            }
            m_textBox->SelectionLength = 0;
            m_textBox->SelectionStart = 32768;
            m_textBox->Focus(FocusState::Programmatic);
        }));
    }
}

void KeyBoardWinRT::HideKeyboard(Platform::String^ text)
{
    if (m_dispatcher.Get() && m_panel.Get())
    {
        // run on main UI thread
        m_dispatcher.Get()->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, text]()
        {
            if (m_textBox != nullptr)
            {
                unsigned int index;
                if (m_panel->Children->IndexOf(m_textBox, &index))
                {
                    m_panel->Children->RemoveAt(index);
                }
            }
            m_textBox = nullptr;
        }));
    }
}

void KeyBoardWinRT::QueueKeyEvent(Cocos2dKeyEvent key)
{
    std::shared_ptr<cocos2d::InputEvent> e(new cocos2d::KeyboardEvent(key));
    cocos2d::GLViewImpl::sharedOpenGLView()->QueueEvent(e);
}

void KeyBoardWinRT::OnKeyPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args)
{
    switch (args->Key)
    {
    case VirtualKey::Escape:
        QueueKeyEvent(Cocos2dKeyEvent::Escape);
        args->Handled = true;
        break;
    case VirtualKey::Back:
        QueueKeyEvent(Cocos2dKeyEvent::Back);
        args->Handled = true;
        break;
    case VirtualKey::Enter:
        QueueKeyEvent(Cocos2dKeyEvent::Enter);
        args->Handled = true;
        break;
    default:

        break;
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


void KeyBoardWinRT::OnKeyReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args)
{
    //m_textBox->Text = L"";
}

NS_CC_END

