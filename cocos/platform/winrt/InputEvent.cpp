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

#include "platform/winrt/InputEvent.h"
#include "platform/winrt/CCWinRTUtils.h"
#include "platform/winrt/CCGLViewImpl-winrt.h"
#include "base/CCEventAcceleration.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCIMEDispatcher.h"

NS_CC_BEGIN

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
        GLViewImpl::sharedOpenGLView()->OnPointerPressed(m_args.Get());
        break;
    case PointerEventType::PointerMoved:
        GLViewImpl::sharedOpenGLView()->OnPointerMoved(m_args.Get());
        break;           
    case PointerEventType::PointerReleased:
        GLViewImpl::sharedOpenGLView()->OnPointerReleased(m_args.Get());
        break;
    case cocos2d::MousePressed:
        GLViewImpl::sharedOpenGLView()->OnMousePressed(m_args.Get());
        break;
    case cocos2d::MouseMoved:
        GLViewImpl::sharedOpenGLView()->OnMouseMoved(m_args.Get());
        break;
    case cocos2d::MouseReleased:
        GLViewImpl::sharedOpenGLView()->OnMouseReleased(m_args.Get());
        break;
    case cocos2d::MouseWheelChanged:
        GLViewImpl::sharedOpenGLView()->OnMouseWheelChanged(m_args.Get());
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
        std::string utf8String = PlatformStringToString(m_text.Get());
        IMEDispatcher::sharedDispatcher()->dispatchInsertText(utf8String.c_str(), utf8String.size());
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
            IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
            break;
        default:
            break;
        }        
        break;
    }
}

WinRTKeyboardEvent::WinRTKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args)
	: m_type(type), m_key(args)
{
}

void WinRTKeyboardEvent::execute()
{
	GLViewImpl::sharedOpenGLView()->OnWinRTKeyboardEvent(m_type, m_key.Get());
}

BackButtonEvent::BackButtonEvent()
{

}

void BackButtonEvent::execute()
{
    GLViewImpl::sharedOpenGLView()->OnBackKeyPress();
}

CustomInputEvent::CustomInputEvent(const std::function<void()>& fun)
: m_fun(fun)
{
}

void CustomInputEvent::execute()
{
    m_fun();
}

UIEditBoxEvent::UIEditBoxEvent(Platform::Object^ sender, Platform::String^ text, Windows::Foundation::EventHandler<Platform::String^>^ handle) 
    : m_sender(sender)
    , m_text(text)
    , m_handler(handle)
{

}

void UIEditBoxEvent::execute()
{
    if (m_handler.Get())
    {
        m_handler.Get()->Invoke(m_sender.Get(), m_text.Get());
    }
}

NS_CC_END


