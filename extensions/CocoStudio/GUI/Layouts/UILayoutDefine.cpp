/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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
#include "UILayoutDefine.h"

NS_CC_EXT_BEGIN


UIMargin::UIMargin(void) : left(0), top(0), right(0), bottom(0)
{
}

UIMargin::UIMargin(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b)
{
}

UIMargin::UIMargin(const UIMargin& other) : left(other.left), top(other.top), right(other.right), bottom(other.bottom)
{
}

UIMargin& UIMargin::operator= (const UIMargin& other)
{
    setMargin(other.left, other.top, other.right, other.bottom);
    return *this;
}

void UIMargin::setMargin(float l, float t, float r, float b)
{
    left = l;
    top = t;
    right = r;
    bottom = b;
}

bool UIMargin::equals(const UIMargin &target) const
{
    return (left == target.left && top == target.top && right == target.right && bottom == target.bottom);
}

NS_CC_EXT_END