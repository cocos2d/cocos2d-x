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

#ifndef __WINRT_INPUT_EVENT__
#define __WINRT_INPUT_EVENT__

#include "CCPlatformMacros.h"
#include "InputEventTypes.h"
#include "base/ccTypes.h"
#include <agile.h>

NS_CC_BEGIN


enum PointerEventType
{
    PointerPressed,
    PointerMoved,
    PointerReleased,
    MousePressed,
    MouseMoved,
    MouseReleased,
    MouseWheelChanged,
};
enum MouseButton
{
    Left = 0,
    Right = 1,
    Middle = 2,
    None
};

class CC_DLL InputEvent
{
public:
    InputEvent() {};
    virtual ~InputEvent() {};
    virtual void execute() = 0;
};


class CC_DLL AccelerometerEvent : public InputEvent
{
public:
    AccelerometerEvent(const cocos2d::Acceleration& event);
    virtual void execute();

private:
    cocos2d::Acceleration m_event;
};

class CC_DLL PointerEvent : public InputEvent
{
public:
    PointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args);
    virtual void execute();


private:
    PointerEventType m_type;
    Platform::Agile<Windows::UI::Core::PointerEventArgs> m_args;
};

class CC_DLL KeyboardEvent : public InputEvent

{
public:
    KeyboardEvent(Cocos2dKeyEvent type);
    KeyboardEvent(Cocos2dKeyEvent type, Platform::String^ text);
    virtual void execute();

private:
    Cocos2dKeyEvent m_type;
    Platform::Agile<Platform::String> m_text;
};

enum WinRTKeyboardEventType
{
	KeyPressed,
	KeyReleased,
};

class CC_DLL WinRTKeyboardEvent : public InputEvent
{
public:
	WinRTKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args);
	virtual void execute();

private:
	WinRTKeyboardEventType m_type;
	Platform::Agile<Windows::UI::Core::KeyEventArgs> m_key;
};


class CC_DLL BackButtonEvent : public InputEvent
{
public:
    BackButtonEvent();
    virtual void execute();
};

class CC_DLL CustomInputEvent : public InputEvent
{
public:
    CustomInputEvent(const std::function<void()>&);
    virtual void execute();
private:
    std::function<void()> m_fun;
};

class UIEditBoxEvent : public cocos2d::InputEvent
{
public:
    UIEditBoxEvent(Platform::Object^ sender, Platform::String^ text, Windows::Foundation::EventHandler<Platform::String^>^ handle);

    virtual void execute();

private:
    Platform::Agile<Platform::Object^> m_sender;
    Platform::Agile<Platform::String^> m_text;
    Platform::Agile<Windows::Foundation::EventHandler<Platform::String^>^> m_handler;
};

NS_CC_END

#endif // #ifndef __WINRT_INPUT_EVENT__

