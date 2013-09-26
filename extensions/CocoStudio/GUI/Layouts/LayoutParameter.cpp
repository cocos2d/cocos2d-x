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

#include "LayoutParameter.h"
#include "Layout.h"

NS_CC_EXT_BEGIN

LayoutParameter* LayoutParameter::create()
{
    LayoutParameter* parameter = new LayoutParameter();
    if (parameter)
    {
        parameter->autorelease();
        return parameter;
    }
    CC_SAFE_DELETE(parameter);
    return NULL;
}

void LayoutParameter::setMargin(const UIMargin &margin)
{
    m_margin = margin;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getParent();
        if (parent)
        {
            Layout* containerParent = dynamic_cast<Layout*>(parent);
            if (containerParent)
            {
                LayoutExecutant* exe = containerParent->getLayoutExecutant();
                if (exe)
                {
                    exe->doLayout();
                }
            }
        }
    }
}

const UIMargin& LayoutParameter::getMargin() const
{
    return m_margin;
}

LayoutParameterType LayoutParameter::getLayoutType() const
{
    return m_eLayoutParameterType;
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
    return NULL;
}

void LinearLayoutParameter::setGravity(UILinearGravity gravity)
{
    m_eLinearGravity = gravity;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getParent();
        if (parent)
        {
            Layout* containerParent = dynamic_cast<Layout*>(parent);
            if (containerParent)
            {
                LayoutExecutant* exe = containerParent->getLayoutExecutant();
                if (exe && (exe->getLayoutType() == LAYOUT_LINEAR_HORIZONTAL || exe->getLayoutType() == LAYOUT_LINEAR_VERTICAL))
                {
                    exe->doLayout();
                }
            }
        }
    }
}

UILinearGravity LinearLayoutParameter::getGravity() const
{
    return m_eLinearGravity;
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
    return NULL;
}

void RelativeLayoutParameter::setAlign(UIRelativeAlign align)
{
    m_eRelativeAlign = align;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getParent();
        if (parent)
        {
            Layout* containerParent = dynamic_cast<Layout*>(parent);
            if (containerParent)
            {
                LayoutExecutant* exe = containerParent->getLayoutExecutant();
                if (exe && (exe->getLayoutType() == LAYOUT_RELATIVE))
                {
                    exe->doLayout();
                }
            }
        }
    }
}

UIRelativeAlign RelativeLayoutParameter::getAlign() const
{
    return m_eRelativeAlign;
}

void RelativeLayoutParameter::setRelativeToWidgetName(const char *name)
{
    m_strRelativeWidgetName = name;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getParent();
        if (parent)
        {
            Layout* containerParent = dynamic_cast<Layout*>(parent);
            if (containerParent)
            {
                LayoutExecutant* exe = containerParent->getLayoutExecutant();
                if (exe && (exe->getLayoutType() == LAYOUT_RELATIVE))
                {
                    exe->doLayout();
                }
            }
        }
    }
}

const char* RelativeLayoutParameter::getRelativeToWidgetName() const
{
    return m_strRelativeWidgetName.c_str();
}

void RelativeLayoutParameter::setRelativeName(const char* name)
{
    m_strRelativeLayoutName = name;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getParent();
        if (parent)
        {
            Layout* containerParent = dynamic_cast<Layout*>(parent);
            if (containerParent)
            {
                LayoutExecutant* exe = containerParent->getLayoutExecutant();
                if (exe && (exe->getLayoutType() == LAYOUT_RELATIVE))
                {
                    exe->doLayout();
                }
            }
        }
    }
}

const char* RelativeLayoutParameter::getRelativeName() const
{
    return m_strRelativeLayoutName.c_str();
}

NS_CC_EXT_END