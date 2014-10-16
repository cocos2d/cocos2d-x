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

#ifndef __INPUT_EVENT__
#define __INPUT_EVENT__

#include "cocos2d.h"
#include "InputEventTypes.h"
#include <agile.h>


namespace PhoneDirect3DXamlAppComponent
{
    public delegate void Cocos2dEventDelegate(Cocos2dEvent event, Platform::String^ text);
    public delegate void Cocos2dMessageBoxDelegate(Platform::String^  title, Platform::String^ text);
    public delegate void Cocos2dEditBoxDelegate(Platform::String^ strPlaceHolder, Platform::String^ strText, int maxLength, int inputMode, int inputFlag, Windows::Foundation::EventHandler<Platform::String^>^ receiveHandler);
    public delegate void Cocos2dOpenURLDelegate(Platform::String^ url);
}

NS_CC_BEGIN

enum PointerEventType
{
    PointerPressed,
    PointerMoved,
    PointerReleased,
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
    KeyboardEvent(PhoneDirect3DXamlAppComponent::Cocos2dKeyEvent type);
    KeyboardEvent(PhoneDirect3DXamlAppComponent::Cocos2dKeyEvent type, Platform::String^ text);
    virtual void execute();

private:
    PhoneDirect3DXamlAppComponent::Cocos2dKeyEvent m_type;
    Platform::Agile<Platform::String> m_text;
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

NS_CC_END

#endif // #ifndef __INPUT_EVENT__

