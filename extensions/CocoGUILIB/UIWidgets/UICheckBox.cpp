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

#include "UICheckBox.h"

NS_CC_EXT_BEGIN

UICheckBox::UICheckBox():
m_pBackGroundBoxRenderer(NULL),
m_pBackGroundSelectedBoxRenderer(NULL),
m_pFrontCrossRenderer(NULL),
m_pBackGroundBoxDisabledRenderer(NULL),
m_pFrontCrossDisabledRenderer(NULL),
m_bIsSelected(true),
m_pSelectListener(NULL),
m_pfnSelectSelector(NULL),
m_pUnSelectListener(NULL),
m_pfnUnSelectSelector(NULL),
m_eBackGroundTexType(UI_TEX_TYPE_LOCAL),
m_eBackGroundSelectedTexType(UI_TEX_TYPE_LOCAL),
m_eFrontCrossTexType(UI_TEX_TYPE_LOCAL),
m_eBackGroundDisabledTexType(UI_TEX_TYPE_LOCAL),
m_eFrontCrossDisabledTexType(UI_TEX_TYPE_LOCAL)
{
}

UICheckBox::~UICheckBox()
{
    
}

UICheckBox* UICheckBox::create()
{
    UICheckBox* widget = new UICheckBox();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UICheckBox::init()
{
    if (UIWidget::init())
    {
        setSelectedState(false);
        return true;
    }
    return false;
}

void UICheckBox::initRenderer()
{
    UIWidget::initRenderer();
    m_pBackGroundBoxRenderer = CCSprite::create();
    m_pBackGroundSelectedBoxRenderer = CCSprite::create();
    m_pFrontCrossRenderer = CCSprite::create();
    m_pBackGroundBoxDisabledRenderer = CCSprite::create();
    m_pFrontCrossDisabledRenderer = CCSprite::create();
    m_pRenderer->addChild(m_pBackGroundBoxRenderer);
    m_pRenderer->addChild(m_pBackGroundSelectedBoxRenderer);
    m_pRenderer->addChild(m_pFrontCrossRenderer);
    m_pRenderer->addChild(m_pBackGroundBoxDisabledRenderer);
    m_pRenderer->addChild(m_pFrontCrossDisabledRenderer);
}

void UICheckBox::loadTextures(const char *backGround, const char *backGroundSelected, const char *cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType)
{
    loadBackGroundTexture(backGround,texType);
    loadBackGroundSelectedTexture(backGroundSelected,texType);
    loadFrontCrossTexture(cross,texType);
    loadBackGroundDisabledTexture(backGroundDisabled,texType);
    loadFrontCrossDisabledTexture(frontCrossDisabled,texType);
}

void UICheckBox::loadBackGroundTexture(const char *backGround,TextureResType texType)
{
    if (!backGround || strcmp(backGround, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundTexType = texType;
    switch (m_eBackGroundTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundBoxRenderer->initWithFile(backGround);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundBoxRenderer->initWithSpriteFrameName(backGround);
            break;
        default:
            break;
    }
    m_pBackGroundBoxRenderer->setColor(getColor());
    m_pBackGroundBoxRenderer->setOpacity(getOpacity());
    backGroundTextureScaleChangedWithSize();
}

void UICheckBox::loadBackGroundSelectedTexture(const char *backGroundSelected,TextureResType texType)
{
    if (!backGroundSelected || strcmp(backGroundSelected, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundSelectedTexType = texType;
    switch (m_eBackGroundSelectedTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundSelectedBoxRenderer->initWithFile(backGroundSelected);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundSelectedBoxRenderer->initWithSpriteFrameName(backGroundSelected);
            break;
        default:
            break;
    }
    m_pBackGroundSelectedBoxRenderer->setColor(getColor());
    m_pBackGroundSelectedBoxRenderer->setOpacity(getOpacity());
    backGroundSelectedTextureScaleChangedWithSize();
}

void UICheckBox::loadFrontCrossTexture(const char *cross,TextureResType texType)
{
    if (!cross || strcmp(cross, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eFrontCrossTexType = texType;
    switch (m_eFrontCrossTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pFrontCrossRenderer->initWithFile(cross);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pFrontCrossRenderer->initWithSpriteFrameName(cross);
            break;
        default:
            break;
    }
    m_pFrontCrossRenderer->setColor(getColor());
    m_pFrontCrossRenderer->setOpacity(getOpacity());
    frontCrossTextureScaleChangedWithSize();
}

void UICheckBox::loadBackGroundDisabledTexture(const char *backGroundDisabled,TextureResType texType)
{
    if (!backGroundDisabled || strcmp(backGroundDisabled, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundDisabledTexType = texType;
    switch (m_eBackGroundDisabledTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundBoxDisabledRenderer->initWithFile(backGroundDisabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundBoxDisabledRenderer->initWithSpriteFrameName(backGroundDisabled);
            break;
        default:
            break;
    }
    m_pBackGroundBoxDisabledRenderer->setColor(getColor());
    m_pBackGroundBoxDisabledRenderer->setOpacity(getOpacity());
    backGroundDisabledTextureScaleChangedWithSize();
}

void UICheckBox::loadFrontCrossDisabledTexture(const char *frontCrossDisabled,TextureResType texType)
{
    if (!frontCrossDisabled || strcmp(frontCrossDisabled, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eFrontCrossDisabledTexType = texType;
    switch (m_eFrontCrossDisabledTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pFrontCrossDisabledRenderer->initWithFile(frontCrossDisabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pFrontCrossDisabledRenderer->initWithSpriteFrameName(frontCrossDisabled);
            break;
        default:
            break;
    }
    m_pFrontCrossDisabledRenderer->setColor(getColor());
    m_pFrontCrossRenderer->setOpacity(getOpacity());
    frontCrossDisabledTextureScaleChangedWithSize();
}

void UICheckBox::onTouchEnded(const CCPoint &touchPoint)
{
    if (m_bFocus)
    {
        releaseUpEvent();
        if (m_bIsSelected){
            setSelectedState(false);
            unSelectedEvent();
        }
        else
        {
            setSelectedState(true);
            selectedEvent();
        }
    }
    setFocus(false);
    m_pWidgetParent->checkChildInfo(2,this,touchPoint);
}

void UICheckBox::onPressStateChangedToNormal()
{
    m_pBackGroundBoxRenderer->setVisible(true);
    m_pBackGroundSelectedBoxRenderer->setVisible(false);
    m_pBackGroundBoxDisabledRenderer->setVisible(false);
    m_pFrontCrossDisabledRenderer->setVisible(false);
}

void UICheckBox::onPressStateChangedToPressed()
{
    m_pBackGroundBoxRenderer->setVisible(false);
    m_pBackGroundSelectedBoxRenderer->setVisible(true);
    m_pBackGroundBoxDisabledRenderer->setVisible(false);
    m_pFrontCrossDisabledRenderer->setVisible(false);
}

void UICheckBox::onPressStateChangedToDisabled()
{
    m_pBackGroundBoxRenderer->setVisible(false);
    m_pBackGroundSelectedBoxRenderer->setVisible(false);
    m_pBackGroundBoxDisabledRenderer->setVisible(true);
    m_pFrontCrossRenderer->setVisible(false);
    if (m_bIsSelected)
    {
        m_pFrontCrossDisabledRenderer->setVisible(true);
    }
}

void UICheckBox::setSelectedState(bool selected)
{
    if (selected == m_bIsSelected)
    {
        return;
    }
    m_bIsSelected = selected;
    m_pFrontCrossRenderer->setVisible(m_bIsSelected);
}

bool UICheckBox::getSelectedState()
{
    return m_bIsSelected;
}

void UICheckBox::selectedEvent()
{
    if (m_pSelectListener && m_pfnSelectSelector)
    {
        (m_pSelectListener->*m_pfnSelectSelector)(this);
    }
}

void UICheckBox::unSelectedEvent()
{
    if (m_pUnSelectListener && m_pfnUnSelectSelector)
    {
        (m_pUnSelectListener->*m_pfnUnSelectSelector)(this);
    }
}

void UICheckBox::addSelectEvent(CCObject *target, SEL_SelectEvent selector)
{
    m_pSelectListener = target;
    m_pfnSelectSelector = selector;
}

void UICheckBox::addUnSelectEvent(CCObject *target, SEL_UnSelectEvent selector)
{
    m_pUnSelectListener = target;
    m_pfnUnSelectSelector = selector;
}

void UICheckBox::setFlipX(bool flipX)
{
    m_pBackGroundBoxRenderer->setFlipX(flipX);
    m_pBackGroundSelectedBoxRenderer->setFlipX(flipX);
    m_pFrontCrossRenderer->setFlipX(flipX);
    m_pBackGroundBoxDisabledRenderer->setFlipX(flipX);
    m_pFrontCrossDisabledRenderer->setFlipX(flipX);
}

void UICheckBox::setFlipY(bool flipY)
{
    m_pBackGroundBoxRenderer->setFlipX(flipY);
    m_pBackGroundSelectedBoxRenderer->setFlipY(flipY);
    m_pFrontCrossRenderer->setFlipY(flipY);
    m_pBackGroundBoxDisabledRenderer->setFlipY(flipY);
    m_pFrontCrossDisabledRenderer->setFlipY(flipY);
}

bool UICheckBox::isFlipX()
{
    return m_pBackGroundBoxRenderer->isFlipX();
}

bool UICheckBox::isFlipY()
{
    return m_pBackGroundBoxRenderer->isFlipY();
}

void UICheckBox::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pBackGroundBoxRenderer->setAnchorPoint(pt);
    m_pBackGroundSelectedBoxRenderer->setAnchorPoint(pt);
    m_pBackGroundBoxDisabledRenderer->setAnchorPoint(pt);
    m_pFrontCrossRenderer->setAnchorPoint(pt);
    m_pFrontCrossDisabledRenderer->setAnchorPoint(pt);
}

void UICheckBox::onSizeChanged()
{
    backGroundTextureScaleChangedWithSize();
    backGroundSelectedTextureScaleChangedWithSize();
    frontCrossTextureScaleChangedWithSize();
    backGroundDisabledTextureScaleChangedWithSize();
    frontCrossDisabledTextureScaleChangedWithSize();
}

const CCSize& UICheckBox::getContentSize() const
{
    return m_pBackGroundBoxRenderer->getContentSize();
}

CCNode* UICheckBox::getVirtualRenderer()
{
    return m_pBackGroundBoxRenderer;
}

void UICheckBox::backGroundTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundBoxRenderer->setScale(1.0f);
        m_size = m_pBackGroundBoxRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = m_pBackGroundBoxRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pBackGroundBoxRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundBoxRenderer->setScaleX(scaleX);
        m_pBackGroundBoxRenderer->setScaleY(scaleY);
    }
}

void UICheckBox::backGroundSelectedTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundSelectedBoxRenderer->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pBackGroundSelectedBoxRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pBackGroundSelectedBoxRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundSelectedBoxRenderer->setScaleX(scaleX);
        m_pBackGroundSelectedBoxRenderer->setScaleY(scaleY);
    }
}

void UICheckBox::frontCrossTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pFrontCrossRenderer->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pFrontCrossRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pFrontCrossRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pFrontCrossRenderer->setScaleX(scaleX);
        m_pFrontCrossRenderer->setScaleY(scaleY);
    }
}

void UICheckBox::backGroundDisabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundBoxDisabledRenderer->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pBackGroundBoxDisabledRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pBackGroundBoxDisabledRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundBoxDisabledRenderer->setScaleX(scaleX);
        m_pBackGroundBoxDisabledRenderer->setScaleY(scaleY);
    }
}

void UICheckBox::frontCrossDisabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pFrontCrossDisabledRenderer->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pFrontCrossDisabledRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pFrontCrossDisabledRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pFrontCrossDisabledRenderer->setScaleX(scaleX);
        m_pFrontCrossDisabledRenderer->setScaleY(scaleY);
    }
}

NS_CC_EXT_END