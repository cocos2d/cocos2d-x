/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

NS_CC_BEGIN

namespace gui {


LayoutParameter* LayoutParameter::create()
{
    LayoutParameter* parameter = new LayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void LayoutParameter::setMargin(const Margin &margin)
{
    _margin = margin;
}

const Margin& LayoutParameter::getMargin() const
{
    return _margin;
}

LayoutParameterType LayoutParameter::getLayoutType() const
{
    return _layoutParameterType;
}

LinearLayoutParameter* LinearLayoutParameter::create()
{
    LinearLayoutParameter* parameter = new LinearLayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void LinearLayoutParameter::setGravity(LinearGravity gravity)
{
    _linearGravity = gravity;
}

LinearGravity LinearLayoutParameter::getGravity() const
{
    return _linearGravity;
}

RelativeLayoutParameter* RelativeLayoutParameter::create()
{
    RelativeLayoutParameter* parameter = new RelativeLayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return nullptr;
}

void RelativeLayoutParameter::setAlign(RelativeAlign align)
{
    _relativeAlign = align;
}

RelativeAlign RelativeLayoutParameter::getAlign() const
{
    return _relativeAlign;
}

void RelativeLayoutParameter::setRelativeToWidgetName(const char *name)
{
    _relativeWidgetName = name;
}

const char* RelativeLayoutParameter::getRelativeToWidgetName() const
{
    return _relativeWidgetName.c_str();
}

void RelativeLayoutParameter::setRelativeName(const char* name)
{
    _relativeLayoutName = name;
}

const char* RelativeLayoutParameter::getRelativeName() const
{
    return _relativeLayoutName.c_str();
}

}

NS_CC_END