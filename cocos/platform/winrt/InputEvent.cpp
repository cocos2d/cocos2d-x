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
#include "CCGLView.h"
#include "base/CCEventAcceleration.h"

NS_CC_BEGIN

using namespace PhoneDirect3DXamlAppComponent;


AccelerometerEvent::AccelerometerEvent(const Acceleration& event)
    : m_event(event)
{

}

void AccelerometerEvent::execute()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    cocos2d::EventAcceleration accEvent(m_event);
    dispatcher->dispatchEvent(&accEvent);
}


PointerEvent::PointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
    : m_type(type), m_args(args)
{

}

void PointerEvent::execute()
{
    switch(m_type)
    {
    case PointerEventType::PointerPressed:
        GLView::sharedOpenGLView()->OnPointerPressed(m_args.Get());
        break;
    case PointerEventType::PointerMoved:
        GLView::sharedOpenGLView()->OnPointerMoved(m_args.Get());
        break;           
    case PointerEventType::PointerReleased:
        GLView::sharedOpenGLView()->OnPointerReleased(m_args.Get());
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

void KeyboardEvent::execute()
{
    switch(m_type)
    {
    case Cocos2dKeyEvent::Text:
    {
        char szUtf8[8] = { 0 };
        int nLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR) m_text.Get()->Data(), 1, szUtf8, sizeof(szUtf8), NULL, NULL);
        IMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
        break;
    }
    default:
        switch (m_type)
        {
        case Cocos2dKeyEvent::Escape:
            //Director::getInstance()()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
            break;
        case Cocos2dKeyEvent::Back:
            IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
            break;
        case Cocos2dKeyEvent::Enter:
            //SetFocus(false);
            IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
            break;
        default:
            break;
        }        
        break;
    }
}


BackButtonEvent::BackButtonEvent()
{

}

void BackButtonEvent::execute()
{
    GLView::sharedOpenGLView()->OnBackKeyPress();
}


NS_CC_END


