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

#include "UILayoutUnit.h"
#include "../BaseClasses/UIContainerWidget.h"

NS_CC_EXT_BEGIN

UILayoutUnit::UILayoutUnit()
{
    
}

UILayoutUnit::~UILayoutUnit()
{
    
}

void UILayoutUnit::setMargin(const UIMargin &margin)
{
    m_margin = margin;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent)
            {
                containerParent->doLayout();
            }
        }
    }
}

const UIMargin& UILayoutUnit::getMargin() const
{
    return m_margin;
}

void UILayoutUnit::setLinearGravity(UILinearGravity gravity)
{
    m_eLinearGravity = gravity;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent && (containerParent->getLayoutType() == UI_LAYOUT_LINEAR_HORIZONTAL || containerParent->getLayoutType() == UI_LAYOUT_LINEAR_VERTICAL))
            {
                containerParent->doLayout();
            }
        }
    }
}

UILinearGravity UILayoutUnit::getLinearGravity() const
{
    return m_eLinearGravity;
}

void UILayoutUnit::setRelativeAlign(UIRelativeAlign align)
{
    m_eRelativeAlign = align;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent && (containerParent->getLayoutType() == UI_LAYOUT_RELATIVE))
            {
                containerParent->doLayout();
            }
        }
    }
}

UIRelativeAlign UILayoutUnit::getRelativeAlign() const
{
    return m_eRelativeAlign;
}

void UILayoutUnit::setRelativeAlignWidget(UIRelativeAlignWidget align)
{
    m_eRelativeAlignWidget = align;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent && (containerParent->getLayoutType() == UI_LAYOUT_RELATIVE))
            {
                containerParent->doLayout();
            }
        }
    }
}

UIRelativeAlignWidget UILayoutUnit::getRelativeAlignWidget() const
{
    return m_eRelativeAlignWidget;
}

void UILayoutUnit::setRelativeWidgetName(const char *name)
{
    m_strRelativeWidgetName = name;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent && (containerParent->getLayoutType() == UI_LAYOUT_RELATIVE))
            {
                containerParent->doLayout();
            }
        }
    }
}

const char* UILayoutUnit::getRelativeWidgetName() const
{
    return m_strRelativeWidgetName.c_str();
}

void UILayoutUnit::setRelativeLayoutName(const char* name)
{
    m_strRelativeLayoutName = name;
    UIWidget* subClass = dynamic_cast<UIWidget*>(this);
    if (subClass)
    {
        UIWidget* parent = subClass->getWidgetParent();
        if (parent)
        {
            UIContainerWidget* containerParent = dynamic_cast<UIContainerWidget*>(parent);
            if (containerParent && (containerParent->getLayoutType() == UI_LAYOUT_RELATIVE))
            {
                containerParent->doLayout();
            }
        }
    }
}

const char* UILayoutUnit::getRelativeLayoutName() const
{
    return m_strRelativeLayoutName.c_str();
}

NS_CC_EXT_END