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

#include "gui/UILayoutParameter.h"
#include "gui/UILayout.h"

namespace gui {


UILayoutParameter* UILayoutParameter::create()
{
    UILayoutParameter* parameter = new UILayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void UILayoutParameter::setMargin(const UIMargin &margin)
{
    _margin = margin;
}

const UIMargin& UILayoutParameter::getMargin() const
{
    return _margin;
}

LayoutParameterType UILayoutParameter::getLayoutType() const
{
    return _layoutParameterType;
}

UILinearLayoutParameter* UILinearLayoutParameter::create()
{
    UILinearLayoutParameter* parameter = new UILinearLayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void UILinearLayoutParameter::setGravity(UILinearGravity gravity)
{
    _linearGravity = gravity;
}

UILinearGravity UILinearLayoutParameter::getGravity() const
{
    return _linearGravity;
}

UIRelativeLayoutParameter* UIRelativeLayoutParameter::create()
{
    UIRelativeLayoutParameter* parameter = new UIRelativeLayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void UIRelativeLayoutParameter::setAlign(UIRelativeAlign align)
{
    _relativeAlign = align;
}

UIRelativeAlign UIRelativeLayoutParameter::getAlign() const
{
    return _relativeAlign;
}

void UIRelativeLayoutParameter::setRelativeToWidgetName(const char *name)
{
    _relativeWidgetName = name;
}

const char* UIRelativeLayoutParameter::getRelativeToWidgetName() const
{
    return _relativeWidgetName.c_str();
}

void UIRelativeLayoutParameter::setRelativeName(const char* name)
{
    _relativeLayoutName = name;
}

const char* UIRelativeLayoutParameter::getRelativeName() const
{
    return _relativeLayoutName.c_str();
}

}