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

#include "CCControllerDirectionPad.h"
#include "CCControllerAxisInput.h"
#include "CCControllerButtonInput.h"

NS_CC_BEGIN

ControllerDirectionPad::ControllerDirectionPad()
: _up(new ControllerButtonInput())
, _down(new ControllerButtonInput())
, _left(new ControllerButtonInput())
, _right(new ControllerButtonInput())
{
    _up->setCollection(this);
    _down->setCollection(this);
    _left->setCollection(this);
    _right->setCollection(this);
}

ControllerDirectionPad::~ControllerDirectionPad()
{
    CC_SAFE_DELETE(_up);
    CC_SAFE_DELETE(_down);
    CC_SAFE_DELETE(_left);
    CC_SAFE_DELETE(_right);
}

ControllerButtonInput* ControllerDirectionPad::getUp() const
{
    return _up;
}

ControllerButtonInput* ControllerDirectionPad::getDown() const
{
    return _down;
}

ControllerButtonInput* ControllerDirectionPad::getLeft() const
{
    return _left;
}

ControllerButtonInput* ControllerDirectionPad::getRight() const
{
    return _right;
}



NS_CC_END