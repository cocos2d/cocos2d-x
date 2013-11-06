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

#include "UILayoutParameter.h"
#include "UILayout.h"

NS_CC_EXT_BEGIN

UILayoutParameter* UILayoutParameter::create()
{
    UILayoutParameter* parameter = new UILayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return NULL;
}

void UILayoutParameter::setMargin(const UIMargin &margin)
{
    m_margin = margin;
}

const UIMargin& UILayoutParameter::getMargin() const
{
    return m_margin;
}

LayoutParameterType UILayoutParameter::getLayoutType() const
{
    return m_eLayoutParameterType;
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
    return NULL;
}

void UILinearLayoutParameter::setGravity(UILinearGravity gravity)
{
    m_eLinearGravity = gravity;
}

UILinearGravity UILinearLayoutParameter::getGravity() const
{
    return m_eLinearGravity;
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
    return NULL;
}

void UIRelativeLayoutParameter::setAlign(UIRelativeAlign align)
{
    m_eRelativeAlign = align;
}

UIRelativeAlign UIRelativeLayoutParameter::getAlign() const
{
    return m_eRelativeAlign;
}

void UIRelativeLayoutParameter::setRelativeToWidgetName(const char *name)
{
    m_strRelativeWidgetName = name;
}

const char* UIRelativeLayoutParameter::getRelativeToWidgetName() const
{
    return m_strRelativeWidgetName.c_str();
}

void UIRelativeLayoutParameter::setRelativeName(const char* name)
{
    m_strRelativeLayoutName = name;
}

const char* UIRelativeLayoutParameter::getRelativeName() const
{
    return m_strRelativeLayoutName.c_str();
}

NS_CC_EXT_END