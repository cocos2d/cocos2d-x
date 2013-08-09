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
m_scale9Size(CCSizeZero),
m_eNormalTexType(UI_TEX_TYPE_LOCAL),
m_ePressedTexType(UI_TEX_TYPE_LOCAL),
m_eDisabledTexType(UI_TEX_TYPE_LOCAL)
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
    m_pButtonNormal = CCSprite::create();
    m_pButtonClicked = CCSprite::create();
    m_pButtonDisable = CCSprite::create();
    m_pRender->addChild(m_pButtonNormal,-1);
    m_pRender->addChild(m_pButtonClicked,-1);
    m_pRender->addChild(m_pButtonDisable,-1);
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
        m_pButtonNormal = CCScale9Sprite::create();
        m_pButtonClicked = CCScale9Sprite::create();
        m_pButtonDisable = CCScale9Sprite::create();
    }
    else
    {
        m_pButtonNormal = CCSprite::create();
        m_pButtonClicked = CCSprite::create();
        m_pButtonDisable = CCSprite::create();
    }
//    setTextures(m_strNormalFileName.c_str(), m_strClickedFileName.c_str(), m_strDisabledFileName.c_str(),getUseMergedTexture());
    setNormalTexture(m_strNormalFileName.c_str(), m_eNormalTexType);
    setPressedTexture(m_strClickedFileName.c_str(), m_ePressedTexType);
    setDisabledTexture(m_strDisabledFileName.c_str(), m_eDisabledTexType);
    m_pRender->addChild(m_pButtonNormal,-1);
    m_pRender->addChild(m_pButtonClicked,-1);
    m_pRender->addChild(m_pButtonDisable,-1);
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
    dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setContentSize(size);
    dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setContentSize(size);
    dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setContentSize(size);
}

void UIButton::setTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType)
{
    setNormalTexture(normal,texType);
    setPressedTexture(selected,texType);
    setDisabledTexture(disabled,texType);
}

void UIButton::setNormalTexture(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strNormalFileName = normal;
//    setUseMergedTexture(useSpriteFrame);
    m_eNormalTexType = texType;
    if (m_bScale9Enable)
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonNormal)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setOpacity(getOpacity());
    }
    updateAnchorPoint();
}

void UIButton::setPressedTexture(const char* selected,TextureResType texType)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    m_strClickedFileName = selected;
//    setUseMergedTexture(useSpriteFrame);
    m_ePressedTexType = texType;
    if (m_bScale9Enable)
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonClicked)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setOpacity(getOpacity());
    }
    updateAnchorPoint();
}

void UIButton::setDisabledTexture(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strDisabledFileName = disabled;
//    setUseMergedTexture(useSpriteFrame);
    m_eDisabledTexType = texType;
    if (m_bScale9Enable)
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonDisable)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setOpacity(getOpacity());
    }
    updateAnchorPoint();
}

void UIButton::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setCapInsets(capInsets);
    dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setCapInsets(capInsets);
    dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setCapInsets(capInsets);
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

CCNode* UIButton::getValidNode()
{
    CCNode* res = NULL;
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
    if (m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormal)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonClicked)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonDisable)->setFlipX(flipX);
}

void UIButton::setFlipY(bool flipY)
{
    if (m_bScale9Enable)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormal)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonClicked)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonDisable)->setFlipY(flipY);
}

bool UIButton::isFlipX()
{
    if (m_bScale9Enable)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormal)->isFlipX();
}

bool UIButton::isFlipY()
{
    if (m_bScale9Enable)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormal)->isFlipY();
}

void UIButton::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pButtonNormal->setAnchorPoint(pt);
    m_pButtonClicked->setAnchorPoint(pt);
    m_pButtonDisable->setAnchorPoint(pt);
}

void UIButton::setNormalSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setDisplayFrame(frame);
    }
}

void UIButton::setPressedSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setDisplayFrame(frame);
    }
}

void UIButton::setDisabledSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setDisplayFrame(frame);
    }
}

void UIButton::setColor(const ccColor3B &color)
{
    if (m_bScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setColor(color);
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setColor(color);
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setColor(color);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setColor(color);
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setColor(color);
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setColor(color);
    }
}

NS_CC_EXT_END