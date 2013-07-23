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

#include "UIContainerWidget.h"
#include "../Drawable/UIClippingLayer.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIClippingLayer*>(m_pRender)
    
UIContainerWidget::UIContainerWidget():
m_fWidth(0.0),
m_fHeight(0.0),
m_bClipAble(false),
m_renderType(RENDER_TYPE_LAYERCOLOR)
{
    m_WidgetType = WidgetTypeContainer;
    m_WidgetName = WIDGET_CONTAINERWIDGET;
}

UIContainerWidget::~UIContainerWidget()
{
    
}

UIContainerWidget* UIContainerWidget::create()
{
    UIContainerWidget* widget = new UIContainerWidget();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

/*****************temp***********/
bool UIContainerWidget::init()
{
    m_children = cocos2d::CCArray::create();
    m_children->retain();
    initNodes();
    m_pRender->retain();
    m_pRender->setZOrder(m_nWidgetZOrder);
    RGBAProtocol* renderRGBA = dynamic_cast<RGBAProtocol*>(m_pRender);
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(false);
        renderRGBA->setCascadeOpacityEnabled(false);
    }
    return true;
}
/********************************/

void UIContainerWidget::setLayoutParameter(/*LayoutParameter * parmeter*/)
{
    
}

void UIContainerWidget::initNodes()
{
    m_pRender = UIClippingLayer::create();
}

bool UIContainerWidget::isClippingEnable()
{
    return m_bClipAble;
}

bool UIContainerWidget::addChild(UIWidget* child)
{   
    UIWidget::addChild(child);
    bool needSetChildCheckAble = false;
    UIWidget* parent = this;
    while (parent)
    {
        if (parent->isClippingEnable())
        {
            needSetChildCheckAble = true;
            break;
        }
        parent = parent->getWidgetParent();
    }
    
    if (needSetChildCheckAble)
    {
        child->setNeedCheckVisibleDepandParent(true);
    }
    return true;
}

void UIContainerWidget::setClippingEnable(bool able)
{
    m_bClipAble = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnable(able);
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        child->setNeedCheckVisibleDepandParent(able);
    }
}

void UIContainerWidget::setClipRect(const cocos2d::Rect &rect)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClipRect(rect);
}

void UIContainerWidget::updateWidth()
{

}

void UIContainerWidget::updateHeight()
{
    
}

void UIContainerWidget::setSize(const cocos2d::Size &size)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setContentSize(size);
    m_fWidth = size.width;
    m_fHeight = size.height;
}

float UIContainerWidget::getWidth()
{
    return m_fWidth;
}

float UIContainerWidget::getHeight()
{
    return m_fHeight;
}

bool UIContainerWidget::hitTest(cocos2d::Node *node, cocos2d::Point &pt)
{
    cocos2d::Point nsp = node->convertToNodeSpace(pt);
    cocos2d::Size bb = node->getContentSize();
    if (nsp.x >= 0.0f && nsp.x <= bb.width && nsp.y >= 0.0f && nsp.y <= bb.height)
    {
        return true;
    }
    return false;
}

Size UIContainerWidget::getWrapSize() const
{
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        switch (child->getWidgetType())
        {
            case WidgetTypeWidget:
                break;
            case WidgetTypeContainer:
                break;
            default:
                break;
        }
    }
    return Size::ZERO;
}

NS_CC_EXT_END