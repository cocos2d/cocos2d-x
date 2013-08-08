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

#include "UIZoomButton.h"

NS_CC_EXT_BEGIN

UIZoomButton::UIZoomButton():
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

UIZoomButton::~UIZoomButton()
{
    
}

UIZoomButton* UIZoomButton::create()
{
    UIZoomButton* widget = new UIZoomButton();
    if (widget && widget->init()) {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIZoomButton::init()
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

void UIZoomButton::initNodes()
{
    UIWidget::initNodes();
    m_pNormalTitle = CCLabelTTF::create();
    m_pPressedTitle = CCLabelTTF::create();
    m_pDisabledTitle = CCLabelTTF::create();

    m_pNormalBackGround = CCScale9Sprite::create();
    m_pPressedBackGround = CCScale9Sprite::create();
    m_pDisabledBackGround = CCScale9Sprite::create();
}

void UIZoomButton::setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled)
{
    m_pNormalBackGround->initWithFile(backgroundNormal);
    m_pPressedBackGround->initWithFile(backgroundPressed);
    m_pDisabledBackGround->initWithFile(backgroundDisabled);
    
    m_pNormalBackGround->setColor(getColor());
    m_pNormalBackGround->setOpacity(getOpacity());
    m_pPressedBackGround->setColor(getColor());
    m_pPressedBackGround->setOpacity(getOpacity());
    m_pDisabledBackGround->setColor(getColor());
    m_pDisabledBackGround->setOpacity(getOpacity());
    
    m_pNormalBackGround->setContentSize(CCSize(m_pNormalTitle->boundingBox().size.width+8*2,m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(CCSize(m_pPressedTitle->boundingBox().size.width+8*2,m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(CCSize(m_pDisabledTitle->boundingBox().size.width+8*2,m_pDisabledTitle->boundingBox().size.height+2*2));
}

void UIZoomButton::setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled)
{
    m_pNormalTitle->setString(titleNormal);
    m_pPressedTitle->setString(titlePressed);
    m_pDisabledTitle->setString(titleDisabled);
    
    m_pNormalBackGround->setContentSize(CCSize(m_pNormalTitle->boundingBox().size.width+8*2,m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(CCSize(m_pPressedTitle->boundingBox().size.width+8*2,m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(CCSize(m_pDisabledTitle->boundingBox().size.width+8*2,m_pDisabledTitle->boundingBox().size.height+2*2));
}

void UIZoomButton::onPressStateChangedToNormal()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    CCAction *zoomAction = CCScaleTo::create(0.05f, 1.0f);
    runAction(zoomAction);
    
    m_pNormalBackGround->setVisible(true);
    m_pPressedBackGround->setVisible(false);
    m_pDisabledBackGround->setVisible(false);
    
    m_pNormalTitle->setVisible(true);
    m_pPressedTitle->setVisible(false);
    m_pDisabledTitle->setVisible(false);
}

void UIZoomButton::onPressStateChangedToPressed()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    CCAction *zoomAction = CCScaleTo::create(0.05f, 1.1f);
    runAction(zoomAction);
    
    m_pNormalBackGround->setVisible(false);
    m_pPressedBackGround->setVisible(true);
    m_pDisabledBackGround->setVisible(false);
    
    m_pNormalTitle->setVisible(false);
    m_pPressedTitle->setVisible(true);
    m_pDisabledTitle->setVisible(false);
}

void UIZoomButton::onPressStateChangedToDisabled()
{
    m_pNormalBackGround->setVisible(false);
    m_pPressedBackGround->setVisible(false);
    m_pDisabledBackGround->setVisible(true);
    
    m_pNormalTitle->setVisible(false);
    m_pPressedTitle->setVisible(false);
    m_pDisabledTitle->setVisible(true);
}

CCNode* UIZoomButton::getValidNode()
{
    CCNode* validNode = NULL;
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

void UIZoomButton::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pNormalBackGround->setAnchorPoint(pt);
    m_pPressedBackGround->setAnchorPoint(pt);
    m_pDisabledBackGround->setAnchorPoint(pt);
}

void UIZoomButton::setFlipX(bool flipX)
{
    m_pNormalTitle->setFlipX(flipX);
    m_pPressedTitle->setFlipX(flipX);
    m_pDisabledTitle->setFlipX(flipX);
}

void UIZoomButton::setFlipY(bool flipY)
{
    m_pNormalTitle->setFlipY(flipY);
    m_pPressedTitle->setFlipY(flipY);
    m_pDisabledTitle->setFlipY(flipY);
}

bool UIZoomButton::isFlipX()
{
    return m_pNormalTitle->isFlipX();
}

bool UIZoomButton::isFlipY()
{
    return m_pNormalTitle->isFlipY();
}

void UIZoomButton::setNormalTitle(const char *title)
{
    m_pNormalTitle->setString(title);
}

void UIZoomButton::setPressedTitle(const char *title)
{
    m_pPressedTitle->setString(title);
}

void UIZoomButton::setDisabledTitle(const char *title)
{
    m_pDisabledTitle->setString(title);
}

void UIZoomButton::setNormalFontName(const char *name)
{
    m_pNormalTitle->setFontName(name);
}

void UIZoomButton::setPressedFontName(const char *name)
{
    m_pPressedTitle->setFontName(name);
}

void UIZoomButton::setDisabledFontName(const char *name)
{
    m_pDisabledTitle->setFontName(name);
}

void UIZoomButton::setNormalFontSize(float size)
{
    m_pNormalTitle->setFontSize(size);
}

void UIZoomButton::setPressedFontSize(float size)
{
    m_pPressedTitle->setFontSize(size);
}

void UIZoomButton::setDisabledFontSize(float size)
{
    m_pDisabledTitle->setFontSize(size);
}

void UIZoomButton::setNormalFontColor(const ccColor3B &color)
{
    m_pNormalTitle->setColor(color);
}

void UIZoomButton::setPressedFontColor(const ccColor3B &color)
{
    m_pPressedTitle->setColor(color);
}

void UIZoomButton::setDisalbedFontColor(const ccColor3B &color)
{
    m_pDisabledTitle->setColor(color);
}

void UIZoomButton::setLabelAnchorPoint(const CCPoint &labelAnchorPoint)
{
    m_pNormalTitle->setAnchorPoint(labelAnchorPoint);
    m_pPressedTitle->setAnchorPoint(labelAnchorPoint);
    m_pDisabledTitle->setAnchorPoint(labelAnchorPoint);
}

void UIZoomButton::setPreferredSize(const CCSize &size)
{
    m_pNormalBackGround->setPreferredSize(size);
    m_pPressedBackGround->setPreferredSize(size);
    m_pDisabledBackGround->setPreferredSize(size);
    
    m_preferredSize = size;
}

void UIZoomButton::setNormalBackgroundSpriteFrame(CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pNormalBackGround->setSpriteFrame(spriteFrame);
    m_pNormalBackGround->setColor(getColor());
    m_pNormalBackGround->setOpacity(getOpacity());
    m_pNormalBackGround->setPreferredSize(m_preferredSize);
}

void UIZoomButton::setPressedBackgroundSpriteFrame(CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pPressedBackGround->setSpriteFrame(spriteFrame);
    m_pPressedBackGround->setColor(getColor());
    m_pPressedBackGround->setOpacity(getOpacity());
    m_pPressedBackGround->setPreferredSize(m_preferredSize);
}

void UIZoomButton::setDisabledBackgroundSpriteFrame(CCSpriteFrame *spriteFrame)
{
    if (!spriteFrame)
    {
        return;
    }
    m_pDisabledBackGround->setSpriteFrame(spriteFrame);
    m_pDisabledBackGround->setColor(getColor());
    m_pDisabledBackGround->setOpacity(getOpacity());
    m_pDisabledBackGround->setPreferredSize(m_preferredSize);
}

void UIZoomButton::setZoomOnTouchDown(bool zoom)
{
    m_bZoomOnTouchDown = zoom;
}

bool UIZoomButton::getZoomOnTouchDown()
{
    return m_bZoomOnTouchDown;
}

NS_CC_EXT_END

