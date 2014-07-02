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

#ifndef __cocos2d_libs__CCControllerThumbStick__
#define __cocos2d_libs__CCControllerThumbStick__

#include "CCPlatformMacros.h"
#include "CCControllerElement.h"

NS_CC_BEGIN

class ControllerAxisInput;
class ControllerButtonInput;

class ControllerThumbstick : public ControllerElement
{
public:
	ControllerAxisInput* getAxisX() const;
	ControllerAxisInput* getAxisY() const;
    
    ControllerButtonInput* getButton() const;
    
protected:
    
    friend class Controller;
    friend class Gamepad;
    
    ControllerThumbstick();
    virtual ~ControllerThumbstick();
    
    ControllerAxisInput* _axisX;
    ControllerAxisInput* _axisY;
    
    ControllerButtonInput* _button;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCControllerThumbStick__) */
