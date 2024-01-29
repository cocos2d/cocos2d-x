/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "editor-support/cocosbuilder/CCBKeyframe.h"

using namespace cocos2d;

namespace cocosbuilder {

CCBKeyframe::CCBKeyframe()
: _object(nullptr)
, _time(0.0f)
, _easingType(EasingType::INSTANT)
, _easingOpt(0.0f)
{}

CCBKeyframe::~CCBKeyframe()
{
    CC_SAFE_RELEASE(_object);
}

const Value& CCBKeyframe::getValue() const
{
    return _value;
}

void CCBKeyframe::setValue(const Value& value)
{
    _value = value;
}
    
Ref* CCBKeyframe::getObject() const
{
    return _object;
}

void CCBKeyframe::setObject(Ref* obj)
{
    CC_SAFE_RETAIN(obj);
    CC_SAFE_RELEASE(_object);
    _object = obj;
}

float CCBKeyframe::getTime()
{
    return _time;
}

void CCBKeyframe::setTime(float fTime)
{
    _time = fTime;
}

CCBKeyframe::EasingType CCBKeyframe::getEasingType()
{
    return _easingType;
}

void CCBKeyframe::setEasingType(CCBKeyframe::EasingType easingType)
{
    _easingType = easingType;
}

float CCBKeyframe::getEasingOpt()
{
    return _easingOpt;
}

void CCBKeyframe::setEasingOpt(float fEasingOpt)
{
    _easingOpt = fEasingOpt;
}

}
