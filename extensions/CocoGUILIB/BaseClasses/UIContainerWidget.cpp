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
    if (widget && widget->init()) {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIContainerWidget::setLayoutParameter(/*LayoutParameter * parmeter*/)
{
    
}

bool UIContainerWidget::init()
{
    if (UIWidget::init()) {
        return true;
    }
    return false;
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
    while (parent != 0){
        if (parent->isClippingEnable()){
            needSetChildCheckAble = true;
            break;
        }
        parent = parent->getWidgetParent();
    }
    
    if (needSetChildCheckAble){
        child->setNeedCheckVisibleDepandParent(true);
    }
    return true;
}

void UIContainerWidget::setClippingEnable(bool able)
{
    m_bClipAble = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnable(able);
    for (int i=0; i<m_children->count(); i++)
    {
        UIWidget* child = (UIWidget*)(m_children->objectAtIndex(i));
        child->setNeedCheckVisibleDepandParent(able);
    }
}

void UIContainerWidget::setClipRect(const cocos2d::CCRect &rect)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setClipRect(rect);
}

void UIContainerWidget::updateWidth()
{

}

void UIContainerWidget::updateHeight()
{
    
}

void UIContainerWidget::setSize(const cocos2d::CCSize &size)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setContentSize(size);
    m_fWidth = size.width;
    m_fHeight = size.height;
    updateClipSize();
}

float UIContainerWidget::getWidth()
{
    return m_fWidth;
}

float UIContainerWidget::getHeight()
{
    return m_fHeight;
}

bool UIContainerWidget::hitTest(cocos2d::CCNode *node, cocos2d::CCPoint &pt)
{
    cocos2d::CCPoint nsp = node->convertToNodeSpace(pt);
    cocos2d::CCSize bb = node->getContentSize();
    if (nsp.x >= 0 && nsp.x <= bb.width && nsp.y >= 0 && nsp.y <= bb.height)
    {
        return true;
    }
    return false;
}

void UIContainerWidget::onScaleDirtyChanged()
{
    UIWidget::onScaleDirtyChanged();
    updateClipSize();
}

void UIContainerWidget::onScaleXDirtyChanged()
{
    UIWidget::onScaleXDirtyChanged();
    updateClipSize();
}

void UIContainerWidget::onScaleYDirtyChanged()
{
    UIWidget::onScaleYDirtyChanged();
    updateClipSize();
}

void UIContainerWidget::updateClipSize()
{
    float asx = getAbsoluteScaleX();
    float asy = getAbsoluteScaleY();
    cocos2d::CCSize size = DYNAMIC_CAST_CLIPPINGLAYER->getContentSize();
    DYNAMIC_CAST_CLIPPINGLAYER->setClipSize(size.width*asx, size.height*asy);
}

CCSize UIContainerWidget::getWrapSize() const
{
    for (int i=0; i<m_children->count(); i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
        switch (child->getWidgetType()) {
            case WidgetTypeWidget:
                break;
            case WidgetTypeContainer:
                break;
            default:
                break;
        }
    }
    return CCSizeZero;
}

NS_CC_EXT_END