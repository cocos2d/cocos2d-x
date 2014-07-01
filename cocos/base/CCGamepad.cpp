/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCGamepad.h"
#include "CCControllerDirectionPad.h"
#include "CCControllerButtonInput.h"
#include "CCControllerThumbstick.h"

NS_CC_BEGIN

Gamepad::Gamepad()
: _controller(nullptr)
, _directionPad(new ControllerDirectionPad())
, _buttonA(new ControllerButtonInput())
, _buttonB(new ControllerButtonInput())
, _buttonX(new ControllerButtonInput())
, _buttonY(new ControllerButtonInput())
, _buttonSelect(new ControllerButtonInput())
, _buttonStart(new ControllerButtonInput())
, _buttonPause(new ControllerButtonInput())
, _leftShoulder(new ControllerButtonInput())
, _rightShoulder(new ControllerButtonInput())
, _leftThumbstick(new ControllerThumbstick())
, _rightThumbstick(new ControllerThumbstick())
, _leftTrigger(new ControllerButtonInput())
, _rightTrigger(new ControllerButtonInput())
{
    
}

Gamepad::~Gamepad()
{
    CC_SAFE_DELETE(_directionPad);
    CC_SAFE_DELETE(_buttonA);
    CC_SAFE_DELETE(_buttonB);
    CC_SAFE_DELETE(_buttonX);
    CC_SAFE_DELETE(_buttonY);
    CC_SAFE_DELETE(_buttonSelect);
    CC_SAFE_DELETE(_buttonStart);
    CC_SAFE_DELETE(_buttonPause);
    CC_SAFE_DELETE(_leftShoulder);
    CC_SAFE_DELETE(_rightShoulder);
    CC_SAFE_DELETE(_leftThumbstick);
    CC_SAFE_DELETE(_rightThumbstick);
    CC_SAFE_DELETE(_leftTrigger);
    CC_SAFE_DELETE(_rightTrigger);
}

Controller* Gamepad::getController()
{
    return _controller;
}

ControllerDirectionPad* Gamepad::getDirectionPad() const
{
    return _directionPad;
}

ControllerButtonInput* Gamepad::getButtonA() const
{
    return _buttonA;
}

ControllerButtonInput* Gamepad::getButtonB() const
{
    return _buttonB;
}

ControllerButtonInput* Gamepad::getButtonX() const
{
    return _buttonX;
}

ControllerButtonInput* Gamepad::getButtonY() const
{
    return _buttonY;
}

ControllerButtonInput* Gamepad::getButtonPause() const
{
    return _buttonPause;
}

ControllerButtonInput* Gamepad::getButtonSelect() const
{
    return _buttonSelect;
}

ControllerButtonInput* Gamepad::getButtonStart() const
{
    return _buttonStart;
}

ControllerButtonInput* Gamepad::getLeftShoulder() const
{
    return _leftShoulder;
}

ControllerButtonInput* Gamepad::getRightShoulder() const
{
    return _rightShoulder;
}

ControllerThumbstick* Gamepad::getLeftThumbstick() const
{
    return _leftThumbstick;
}

ControllerThumbstick* Gamepad::getRightThumbstick() const
{
    return _rightThumbstick;
}

ControllerButtonInput* Gamepad::getLeftTrigger() const
{
    return _leftTrigger;
}

ControllerButtonInput* Gamepad::getRightTrigger() const
{
    return _rightTrigger;
}

NS_CC_END
