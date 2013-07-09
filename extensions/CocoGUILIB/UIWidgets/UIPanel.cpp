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

#include "UIPanel.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"
#include "../Drawable/UIClippingLayer.h"


NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIClippingLayer*>(m_pRender)

UIPanel::UIPanel():
m_bBackGroundScale9Enable(false),
m_pBackGroundImage(NULL),
m_strBackGroundImageFileName(""),
m_backGroundImageCapInsets(CCRectZero)
{
    m_WidgetName = WIDGET_PANEL;
}

UIPanel* UIPanel::create()
{
    UIPanel* widget = new UIPanel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIPanel::initNodes()
{
    UIContainerWidget::initNodes();
    m_pBackGroundImage = cocos2d::CCSprite::create();
    m_pBackGroundImage->setZOrder(-1);
    m_pRender->addChild(m_pBackGroundImage);
}

UIPanel::~UIPanel()
{
    
}

void UIPanel::setBackGroundImageScale9Enable(bool able)
{
    if (m_bBackGroundScale9Enable == able)
    {
        return;
    }
    m_pRender->removeChild(m_pBackGroundImage, true);
    m_pBackGroundImage = NULL;
    m_bBackGroundScale9Enable = able;
    if (m_bBackGroundScale9Enable)
    {
        m_pBackGroundImage = CCScale9Sprite::create();
        m_pRender->addChild(m_pBackGroundImage);
    }
    else
    {
        m_pBackGroundImage = CCSprite::create();
        m_pRender->addChild(m_pBackGroundImage);
    }
    m_pBackGroundImage->setZOrder(-1);
    setBackGroundImage(m_strBackGroundImageFileName.c_str(),getUseMergedTexture());
    setBackGroundImageCapInsets(m_backGroundImageCapInsets);
}
    
void UIPanel::setSize(const cocos2d::CCSize &size)
{
    UIContainerWidget::setSize(size);
    m_pBackGroundImage->setPosition(ccp(m_pRender->getContentSize().width/2.0f, m_pRender->getContentSize().height/2.0f));
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pBackGroundImage)->setContentSize(m_pRender->getContentSize());
    }
}

void UIPanel::setBackGroundImage(const char* fileName,bool useSpriteFrame)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strBackGroundImageFileName = fileName;
    setUseMergedTexture(useSpriteFrame);
    if (m_bBackGroundScale9Enable)
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
        }
        else
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pBackGroundImage)->initWithFile(fileName);
        }
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pBackGroundImage)->setContentSize(m_pRender->getContentSize());
    }
    else
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pBackGroundImage)->initWithSpriteFrameName(fileName);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pBackGroundImage)->initWithFile(fileName);
        }
    }
    m_pBackGroundImage->setPosition(ccp(m_pRender->getContentSize().width/2, m_pRender->getContentSize().height/2));
}

void UIPanel::setBackGroundImageCapInsets(const cocos2d::CCRect &capInsets)
{
    m_backGroundImageCapInsets = capInsets;
    if (m_bBackGroundScale9Enable)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pBackGroundImage)->setCapInsets(capInsets);
    }
}

void UIPanel::setBackGroundColorType(PanelColorType type)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setColorType((UILayerColorType)type);
}

void UIPanel::setBackGroundColor(const ccColor3B &color)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setColor(color);
}

void UIPanel::setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor)
{
    UIClippingLayer * render = DYNAMIC_CAST_CLIPPINGLAYER;
    render->setStartColor(startColor);
    render->setEndColor(endColor);
}

void UIPanel::setBackGroundColorOpacity(int opacity)
{
    DYNAMIC_CAST_CLIPPINGLAYER->setColorOpacity(opacity);
}

NS_CC_EXT_END