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

#include "InputEvent.h"
#include "Cocos2dRenderer.h"

namespace PhoneDirect3DXamlAppComponent
{

PointerEvent::PointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
    : m_type(type), m_args(args)
{

}

void PointerEvent::execute(Cocos2dRenderer ^ renderer)
{
    switch(m_type)
    {
    case PointerEventType::PointerPressed:
        renderer->OnPointerPressed(m_args.Get());
        break;
    case PointerEventType::PointerMoved:
        renderer->OnPointerMoved(m_args.Get());
        break;           
    case PointerEventType::PointerReleased:
        renderer->OnPointerReleased(m_args.Get());
        break;
    }
}

KeyboardEvent::KeyboardEvent(Cocos2dKeyEvent type)
    : m_type(type), m_text(nullptr)
{

}

KeyboardEvent::KeyboardEvent(Cocos2dKeyEvent type, Platform::String^ text)
    : m_type(type), m_text(text)
{

}

void KeyboardEvent::execute(Cocos2dRenderer ^ renderer)
{
    switch(m_type)
    {
    case Cocos2dKeyEvent::Text:
        renderer->OnKeyPressed(m_text.Get());
        break;
    default:
        renderer->OnCocos2dKeyEvent(m_type);
        break;      
    }
}


BackButtonEvent::BackButtonEvent()
{

}

void BackButtonEvent::execute(Cocos2dRenderer ^ renderer)
{
    renderer->OnBackKeyPress();
}


}

