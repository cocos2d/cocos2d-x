//
//  CCLayoutParameterProtocol.cpp
//  cocos2d_libs
//
//  Created by cai wenzhi on 14-5-7.
//
//

#include "layout/CCLayoutParameterProtocol.h"

NS_CC_BEGIN
namespace layout{
    
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
        setRelativeName(parameter->_relativeLayoutName.c_str());
        setRelativeToWidgetName(parameter->_relativeWidgetName.c_str());
    }
}
    
LayoutParameterProtocol::LayoutParameterProtocol()
{
    
}
    
LayoutParameterProtocol::~LayoutParameterProtocol()
{
    
}
    
void LayoutParameterProtocol::setLayoutParameter(LayoutParameter *parameter)
{
    if (!parameter)
    {
        return;
    }
    _layoutParameterDictionary.insert(parameter->getLayoutType(), parameter);
}

LayoutParameter* LayoutParameterProtocol::getLayoutParameter(LayoutParameterType type)
{
    return dynamic_cast<LayoutParameter*>(_layoutParameterDictionary.at(type));
}
    
}
NS_CC_END