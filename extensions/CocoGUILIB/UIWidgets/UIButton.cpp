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

#include "UIButton.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN
    
UIButton::UIButton():
m_pButtonNormal(NULL),
m_pButtonClicked(NULL),
m_pButtonDisable(NULL),
m_bScale9Enable(false),
m_strClickedFileName(""),
m_strDisabledFileName(""),
m_strNormalFileName(""),
m_capInsets(CCRectZero),
m_scale9Size(CCSizeZero)
{
    m_WidgetName = WIDGET_BUTTON;
}

UIButton::~UIButton()
{
    
}

UIButton* UIButton::create()
{
    UIButton* widget = new UIButton();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIButton::init()
{
    if (UIWidget::init())
    {
        
        initPressState(WidgetStateNormal);
        return true;
    }
    return false;
}

void UIButton::initNodes()
{
    UIWidget::initNodes();
    m_pButtonNormal = cocos2d::CCSprite::create();
    m_pButtonClicked = cocos2d::CCSprite::create();
    m_pButtonDisable = cocos2d::CCSprite::create();
    m_pRender->addChild(m_pButtonNormal);
    m_pRender->addChild(m_pButtonClicked);
    m_pRender->addChild(m_pButtonDisable);
}

void UIButton::initPressState(WidgetState state)
{
    UIWidget::initPressState(state);
    m_pButtonNormal->setVisible(true);
    m_pButtonClicked->setVisible(false);
    m_pButtonDisable->setVisible(false);
}

void UIButton::setScale9Enable(bool able)
{
    if (m_bScale9Enable == able)
    {
        return;
    }
    m_nPrevPressstate = WidgetStateNone;
    m_nCurPressState = WidgetStateNone;
    m_bScale9Enable = able;
    
    m_pRender->removeChild(m_pButtonNormal, true);
    m_pRender->removeChild(m_pButtonClicked, true);
    m_pRender->removeChild(m_pButtonDisable, true);
    
    m_pButtonNormal = NULL;
    m_pButtonClicked = NULL;
    m_pButtonDisable = NULL;
    if (m_bScale9Enable)
    {
        m_pButtonNormal = cocos2d::extension::CCScale9Sprite::create();
        m_pButtonClicked = cocos2d::extension::CCScale9Sprite::create();
        m_pButtonDisable = cocos2d::extension::CCScale9Sprite::create();
    }
    else
    {
        m_pButtonNormal = cocos2d::CCSprite::create();
        m_pButtonClicked = cocos2d::CCSprite::create();
        m_pButtonDisable = cocos2d::CCSprite::create();
    }
    setTextures(m_strNormalFileName.c_str(), m_strClickedFileName.c_str(), m_strDisabledFileName.c_str(),getUseMergedTexture());
    m_pRender->addChild(m_pButtonNormal);
    m_pRender->addChild(m_pButtonClicked);
    m_pRender->addChild(m_pButtonDisable);
    initPressState(WidgetStateNormal);
    setCapInsets(m_capInsets);
    setScale9Size(m_scale9Size);
}

void UIButton::setScale9Size(const CCSize &size)
{
    if (size.equals(CCSizeZero))
    {
        return;
    }
    else
    {
        m_scale9Size = size;
    }
    if (!m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonNormal)->setContentSize(size);
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonClicked)->setContentSize(size);
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonDisable)->setContentSize(size);
}

void UIButton::setTextures(const char* normal,const char* selected,const char* disabled,bool useSpriteFrame)
{
    setNormalTexture(normal,useSpriteFrame);
    setPressedTexture(selected,useSpriteFrame);
    setDisabledTexture(disabled,useSpriteFrame);
}

void UIButton::setNormalTexture(const char* normal,bool useSpriteFrame)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strNormalFileName = normal;
    setUseMergedTexture(useSpriteFrame);
    if (m_bScale9Enable)
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
        }
        else
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonNormal)->initWithFile(normal);
        }
    }
    else
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->initWithFile(normal);
        }
    }
    updateAnchorPoint();
}

void UIButton::setPressedTexture(const char* selected,bool useSpriteFrame)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    m_strClickedFileName = selected;
    setUseMergedTexture(useSpriteFrame);
    if (m_bScale9Enable)
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
        }
        else
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonClicked)->initWithFile(selected);
        }
    }
    else
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->initWithFile(selected);
        }
    }
    updateAnchorPoint();
}

void UIButton::setDisabledTexture(const char* disabled,bool useSpriteFrame)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strDisabledFileName = disabled;
    setUseMergedTexture(useSpriteFrame);
    if (m_bScale9Enable)
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
        }
        else
        {
            dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonDisable)->initWithFile(disabled);
        }
    }
    else
    {
        if (useSpriteFrame)
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
        }
        else
        {
            dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->initWithFile(disabled);
        }
    }

    updateAnchorPoint();
}

void UIButton::setCapInsets(const cocos2d::CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonNormal)->setCapInsets(capInsets);
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonClicked)->setCapInsets(capInsets);
    dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonDisable)->setCapInsets(capInsets);
}

void UIButton::onPressStateChangedToNormal()
{
    m_pButtonNormal->setVisible(true);
    m_pButtonClicked->setVisible(false);
    m_pButtonDisable->setVisible(false);
}

void UIButton::onPressStateChangedToPressed()
{
    m_pButtonNormal->setVisible(false);
    m_pButtonClicked->setVisible(true);
    m_pButtonDisable->setVisible(false);
}

void UIButton::onPressStateChangedToDisabled()
{
    m_pButtonNormal->setVisible(false);
    m_pButtonClicked->setVisible(false);
    m_pButtonDisable->setVisible(true);
}

cocos2d::CCNode* UIButton::getValidNode()
{
    cocos2d::CCNode* res = NULL;
    switch (m_nCurPressState)
    {
        case WidgetStateNormal:
            res = m_pButtonNormal;
            break;
        case WidgetStateSelected:
            res = m_pButtonClicked;
            break;
        case WidgetStateDisabled:
            res = m_pButtonDisable;
            break;
        default:
            break;
    }
    return res;
}

void UIButton::setFlipX(bool flipX)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->setFlipX(flipX);
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->setFlipX(flipX);
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->setFlipX(flipX);
}

void UIButton::setFlipY(bool flipY)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->setFlipY(flipY);
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->setFlipY(flipY);
    dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->setFlipY(flipY);
}

bool UIButton::isFlipX()
{
    if (!m_bScale9Enable)
    {
        return false;
    }
    return dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->isFlipX();
}

bool UIButton::isFlipY()
{
    if (!m_bScale9Enable)
    {
        return false;
    }
    return dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->isFlipY();
}

void UIButton::setAnchorPoint(const cocos2d::CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pButtonNormal->setAnchorPoint(pt);
    m_pButtonClicked->setAnchorPoint(pt);
    m_pButtonDisable->setAnchorPoint(pt);
}

void UIButton::setNormalSpriteFrame(cocos2d::CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonNormal)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<cocos2d::CCSprite*>(m_pButtonNormal)->setDisplayFrame(frame);
    }
}

void UIButton::setPressedSpriteFrame(cocos2d::CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonClicked)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<cocos2d::CCSprite*>(m_pButtonClicked)->setDisplayFrame(frame);
    }
}

void UIButton::setDisabledSpriteFrame(cocos2d::CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pButtonDisable)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<cocos2d::CCSprite*>(m_pButtonDisable)->setDisplayFrame(frame);
    }
}

NS_CC_EXT_END