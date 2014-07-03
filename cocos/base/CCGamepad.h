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

#ifndef __cocos2d_libs__CCGamepad__
#define __cocos2d_libs__CCGamepad__

#include "CCPlatformMacros.h"

NS_CC_BEGIN

class ControllerButtonInput;
class ControllerDirectionPad;
class ControllerThumbstick;
class Controller;

class Gamepad
{
public:
    /**
     A profile keeps a reference to the controller that this profile is mapping input from.
     */
    Controller* getController();
    
	// API for Standard / Extended Gamepad
    
	ControllerDirectionPad* getDirectionPad() const;
    
    /**
     All face buttons are required to be analog in the Extended profile. These must be arranged
     in the diamond pattern given below:
      Y
     / \
    X   B
     \ /
      A
     */
	ControllerButtonInput* getButtonA() const;
	ControllerButtonInput* getButtonB() const;
	ControllerButtonInput* getButtonX() const;
	ControllerButtonInput* getButtonY() const;
    
    // Select button
    ControllerButtonInput* getButtonSelect() const;
    
    // Start button
    ControllerButtonInput* getButtonStart() const;
    
    // Pause button
    ControllerButtonInput* getButtonPause() const;
    
    // Shoulder buttons
	ControllerButtonInput* getLeftShoulder() const;
	ControllerButtonInput* getRightShoulder() const;
    
	// API for Extended Gamepad only
    
    /**
     A thumbstick is a 2-axis control that is physically required to be analog. All the elements of this directional input are thus analog.
     */
	ControllerThumbstick* getLeftThumbstick() const;
	ControllerThumbstick* getRightThumbstick() const;
	
    /**
     If Trigger button supports analog inputs, it could be used as acceleration and decelleration in a driving game for example.
     */
	ControllerButtonInput* getLeftTrigger() const;
	ControllerButtonInput* getRightTrigger() const;
    
protected:
    
    Gamepad();
    virtual ~Gamepad();
    
    friend class Controller;
    Controller* _controller;
    
    ControllerDirectionPad* _directionPad;
    
    ControllerButtonInput* _buttonA;
    ControllerButtonInput* _buttonB;
    ControllerButtonInput* _buttonX;
    ControllerButtonInput* _buttonY;
    
    ControllerButtonInput* _buttonSelect;
    ControllerButtonInput* _buttonStart;
    ControllerButtonInput* _buttonPause;
    
    ControllerButtonInput* _leftShoulder;
    ControllerButtonInput* _rightShoulder;
    
    ControllerThumbstick* _leftThumbstick;
    ControllerThumbstick* _rightThumbstick;
    
    ControllerButtonInput* _leftTrigger;
    ControllerButtonInput* _rightTrigger;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCGamepad__) */
