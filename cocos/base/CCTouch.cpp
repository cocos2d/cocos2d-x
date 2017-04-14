/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2017 Chukong Technologies Inc.
 
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

#include "base/CCTouch.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

// returns the current touch location in screen coordinates
Vec2 Touch::getLocationInView() const 
{ 
    return _point; 
}

// returns the previous touch location in screen coordinates
Vec2 Touch::getPreviousLocationInView() const 
{ 
    return _prevPoint; 
}

// returns the start touch location in screen coordinates
Vec2 Touch::getStartLocationInView() const 
{ 
    return _startPoint; 
}

// returns the current touch location in OpenGL coordinates
Vec2 Touch::getLocation() const
{ 
    return Director::getInstance()->convertToGL(_point); 
}

// returns the previous touch location in OpenGL coordinates
Vec2 Touch::getPreviousLocation() const
{ 
    return Director::getInstance()->convertToGL(_prevPoint);  
}

// returns the start touch location in OpenGL coordinates
Vec2 Touch::getStartLocation() const
{ 
    return Director::getInstance()->convertToGL(_startPoint);  
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
Vec2 Touch::getDelta() const
{     
    return getLocation() - getPreviousLocation();
}

// Returns the current touch force for 3d touch.
float Touch::getCurrentForce() const
{
    return _curForce;
}

// Returns the maximum touch force for 3d touch.
float Touch::getMaxForce() const
{
    return _maxForce;
}

NS_CC_END
