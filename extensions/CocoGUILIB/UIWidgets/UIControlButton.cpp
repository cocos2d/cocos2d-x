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

#include "UIControlButton.h"

NS_CC_EXT_BEGIN

UIControlButton::UIControlButton():
m_pNormalBackGround(NULL),
m_pPressedBackGround(NULL),
m_pDisabledBackGround(NULL),
m_pNormalTitle(NULL),
m_pPressedTitle(NULL),
m_pDisabledTitle(NULL),
m_bZoomOnTouchDown(true),
m_preferredSize(CCSizeZero)
{
    m_WidgetName = WIDGET_CONTROLBUTTON;
}

UIControlButton::~UIControlButton()
{
    
}

UIControlButton* UIControlButton::create()
{
    UIControlButton* widget = new UIControlButton();
    if (widget && widget->init()) {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIControlButton::init()
{
    if (UIWidget::init())
    {
        m_pRender->addChild(m_pNormalBackGround);
        m_pRender->addChild(m_pPressedBackGround);
        m_pRender->addChild(m_pDisabledBackGround);
        m_pRender->addChild(m_pNormalTitle);
        m_pRender->addChild(m_pPressedTitle);
        m_pRender->addChild(m_pDisabledTitle);
        setPressState(WidgetStateNormal);
        return true;
    }
    return false;
}

void UIControlButton::initNodes()
{
    UIWidget::initNodes();
    m_pNormalTitle = cocos2d::CCLabelTTF::create();
    m_pPressedTitle = cocos2d::CCLabelTTF::create();
    m_pDisabledTitle = cocos2d::CCLabelTTF::create();

    m_pNormalBackGround = cocos2d::extension::CCScale9Sprite::create();
    m_pPressedBackGround = cocos2d::extension::CCScale9Sprite::create();
    m_pDisabledBackGround = cocos2d::extension::CCScale9Sprite::create();
}

void UIControlButton::setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled)
{
    m_pNormalBackGround->initWithFile(backgroundNormal);
    m_pPressedBackGround->initWithFile(backgroundPressed);
    m_pDisabledBackGround->initWithFile(backgroundDisabled);
    
    m_pNormalBackGround->setContentSize(cocos2d::CCSize(m_pNormalTitle->boundingBox().size.width+8*2,m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(cocos2d::CCSize(m_pPressedTitle->boundingBox().size.width+8*2,m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(cocos2d::CCSize(m_pDisabledTitle->boundingBox().size.width+8*2,m_pDisabledTitle->boundingBox().size.height+2*2));
}

void UIControlButton::setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled)
{
    m_pNormalTitle->setString(titleNormal);
    m_pPressedTitle->setString(titlePressed);
    m_pDisabledTitle->setString(titleDisabled);
    
    m_pNormalBackGround->setContentSize(cocos2d::CCSize(m_pNormalTitle->boundingBox().size.width+8*2,m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(cocos2d::CCSize(m_pPressedTitle->boundingBox().size.width+8*2,m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(cocos2d::CCSize(m_pDisabledTitle->boundingBox().size.width+8*2,m_pDisabledTitle->boundingBox().size.height+2*2));
}

void UIControlButton::onPressStateChangedToNormal()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.0f);
    runAction(zoomAction);
    
    m_pNormalBackGround->setVisible(true);
    m_pPressedBackGround->setVisible(false);
    m_pDisabledBackGround->setVisible(false);
}

void UIControlButton::onPressStateChangedToPressed()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.1f);
    runAction(zoomAction);
    
    m_pNormalBackGround->setVisible(false);
    m_pPressedBackGround->setVisible(true);
    m_pDisabledBackGround->setVisible(false);
}

void UIControlButton::onPressStateChangedToDisabled()
{
    m_pNormalBackGround->setVisible(false);
    m_pPressedBackGround->setVisible(false);
    m_pDisabledBackGround->setVisible(true);
}

cocos2d::CCNode* UIControlButton::getValidNode()
{
    cocos2d::CCNode* validNode = NULL;
    switch (m_nCurPressState)
    {
        case WidgetStateNormal:
            validNode = m_pNormalBackGround;
            break;
        case WidgetStateSelected:
            validNode = m_pPressedBackGround;
            break;
        case WidgetStateDisabled:
            validNode = m_pDisabledBackGround;
            break;
        default:
            break;
    }
    return validNode;
}

void UIControlButton::setAnchorPoint(const cocos2d::CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pNormalBackGround->setAnchorPoint(pt);
    m_pPressedBackGround->setAnchorPoint(pt);
    m_pDisabledBackGround->setAnchorPoint(pt);
}

void UIControlButton::setFlipX(bool flipX)
{
    m_pNormalTitle->setFlipX(flipX);
    m_pPressedTitle->setFlipX(flipX);
    m_pDisabledTitle->setFlipX(flipX);
}

void UIControlButton::setFlipY(bool flipY)
{
    m_pNormalTitle->setFlipY(flipY);
    m_pPressedTitle->setFlipY(flipY);
    m_pDisabledTitle->setFlipY(flipY);
}

bool UIControlButton::isFlipX()
{
    return m_pNormalTitle->isFlipX();
}

bool UIControlButton::isFlipY()
{
    return m_pNormalTitle->isFlipY();
}

void UIControlButton::setNormalTitle(const char *title)
{
    m_pNormalTitle->setString(title);
}

void UIControlButton::setPressedTitle(const char *title)
{
    m_pPressedTitle->setString(title);
}

void UIControlButton::setDisabledTitle(const char *title)
{
    m_pDisabledTitle->setString(title);
}

void UIControlButton::setNormalFontName(const char *name)
{
    m_pNormalTitle->setFontName(name);
}

void UIControlButton::setPressedFontName(const char *name)
{
    m_pPressedTitle->setFontName(name);
}

void UIControlButton::setDisabledFontName(const char *name)
{
    m_pDisabledTitle->setFontName(name);
}

void UIControlButton::setNormalFontSize(float size)
{
    m_pNormalTitle->setFontSize(size);
}

void UIControlButton::setPressedFontSize(float size)
{
    m_pPressedTitle->setFontSize(size);
}

void UIControlButton::setDisabledFontSize(float size)
{
    m_pDisabledTitle->setFontSize(size);
}

void UIControlButton::setNormalFontColor(const cocos2d::ccColor3B &color)
{
    m_pNormalTitle->setColor(color);
}

void UIControlButton::setPressedFontColor(const cocos2d::ccColor3B &color)
{
    m_pPressedTitle->setColor(color);
}

void UIControlButton::setDisalbedFontColor(const cocos2d::ccColor3B &color)
{
    m_pDisabledTitle->setColor(color);
}

void UIControlButton::setLabelAnchorPoint(const cocos2d::CCPoint &labelAnchorPoint)
{
    m_pNormalTitle->setAnchorPoint(labelAnchorPoint);
    m_pPressedTitle->setAnchorPoint(labelAnchorPoint);
    m_pDisabledTitle->setAnchorPoint(labelAnchorPoint);
}

void UIControlButton::setPreferredSize(const cocos2d::CCSize &size)
{
    m_pNormalBackGround->setPreferredSize(size);
    m_pPressedBackGround->setPreferredSize(size);
    m_pDisabledBackGround->setPreferredSize(size);
    
    m_preferredSize = size;
}

void UIControlButton::setNormalBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pNormalBackGround->setSpriteFrame(spriteFrame);
    m_pNormalBackGround->setPreferredSize(m_preferredSize);
}

void UIControlButton::setPressedBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pPressedBackGround->setSpriteFrame(spriteFrame);
    m_pPressedBackGround->setPreferredSize(m_preferredSize);
}

void UIControlButton::setDisabledBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pDisabledBackGround->setSpriteFrame(spriteFrame);
    m_pDisabledBackGround->setPreferredSize(m_preferredSize);
}

void UIControlButton::setZoomOnTouchDown(bool zoom)
{
    m_bZoomOnTouchDown = zoom;
}

bool UIControlButton::getZoomOnTouchDown()
{
    return m_bZoomOnTouchDown;
}

NS_CC_EXT_END

