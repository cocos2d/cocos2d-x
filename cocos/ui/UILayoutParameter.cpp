/****************************************************************************
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

#include "ui/UILayoutParameter.h"
#include "ui/UILayout.h"

NS_CC_BEGIN

namespace ui {
    
const Margin Margin::ZERO = Margin(0,0,0,0);
    
Margin::Margin(void) : left(0), top(0), right(0), bottom(0)
{
}

Margin::Margin(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b)
{
}

Margin::Margin(const Margin& other) : left(other.left), top(other.top), right(other.right), bottom(other.bottom)
{
}

Margin& Margin::operator= (const Margin& other)
{
    setMargin(other.left, other.top, other.right, other.bottom);
    return *this;
}

void Margin::setMargin(float l, float t, float r, float b)
{
    left = l;
    top = t;
    right = r;
    bottom = b;
}

bool Margin::equals(const Margin &target) const
{
    return (left == target.left && top == target.top && right == target.right && bottom == target.bottom);
}
    

LayoutParameter* LayoutParameter::create()
{
    LayoutParameter* parameter = new (std::nothrow) LayoutParameter();
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

LayoutParameter::Type LayoutParameter::getLayoutType() const
{
    return _layoutParameterType;
}
    
LayoutParameter* LayoutParameter::clone()
{
    LayoutParameter* clonedParameter = createCloneInstance();
    clonedParameter->copyProperties(this);
    return clonedParameter;
}
    
LayoutParameter* LayoutParameter::createCloneInstance()
{
    return LayoutParameter::create();
}
    
void LayoutParameter::copyProperties(LayoutParameter *model)
{
    _margin = model->_margin;
}

LinearLayoutParameter* LinearLayoutParameter::create()
{
    LinearLayoutParameter* parameter = new (std::nothrow) LinearLayoutParameter();
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

LinearLayoutParameter::LinearGravity LinearLayoutParameter::getGravity() const
{
    return _linearGravity;
}
    
LayoutParameter* LinearLayoutParameter::createCloneInstance()
{
    return LinearLayoutParameter::create();
}

void LinearLayoutParameter::copyProperties(LayoutParameter *model)
{
    LayoutParameter::copyProperties(model);
    LinearLayoutParameter* parameter = dynamic_cast<LinearLayoutParameter*>(model);
    if (parameter)
    {
        setGravity(parameter->_linearGravity);
    }
}

RelativeLayoutParameter* RelativeLayoutParameter::create()
{
    RelativeLayoutParameter* parameter = new (std::nothrow) RelativeLayoutParameter();
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

RelativeLayoutParameter::RelativeAlign RelativeLayoutParameter::getAlign() const
{
    return _relativeAlign;
}

void RelativeLayoutParameter::setRelativeToWidgetName(const std::string& name)
{
    _relativeWidgetName = name;
}

const std::string& RelativeLayoutParameter::getRelativeToWidgetName() const
{
    return _relativeWidgetName;
}

void RelativeLayoutParameter::setRelativeName(const std::string& name)
{
    _relativeLayoutName = name;
}

const std::string& RelativeLayoutParameter::getRelativeName() const
{
    return _relativeLayoutName;
}
    
LayoutParameter* RelativeLayoutParameter::createCloneInstance()
{
    return RelativeLayoutParameter::create();
}

void RelativeLayoutParameter::copyProperties(LayoutParameter *model)
{
    LayoutParameter::copyProperties(model);
    RelativeLayoutParameter* parameter = dynamic_cast<RelativeLayoutParameter*>(model);
    if (parameter)
    {
        setAlign(parameter->_relativeAlign);
        setRelativeName(parameter->_relativeLayoutName);
        setRelativeToWidgetName(parameter->_relativeWidgetName);
    }
}

}

NS_CC_END
