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

#include "UIImageView.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(m_pImageRender)
#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pImageRender)

UIImageView::UIImageView():
m_nViewType(1),
m_nClickCount(0),
m_fClickTimeInterval(0.0),
m_bStartCheckDoubleClick(false),
m_touchRelease(false),
m_bDoubleClickEnable(false),
m_bScale9Enable(false),
m_pImageRender(NULL),
m_strTextureFile(""),
m_capInsets(CCRectZero),
m_scale9Size(CCSizeZero),
m_eImageTexType(UI_TEX_TYPE_LOCAL)
{
    m_WidgetName = WIDGET_IMAGEVIEW;
}

UIImageView::~UIImageView()
{
    
}

UIImageView* UIImageView::create()
{
    UIImageView* widget = new UIImageView();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIImageView::initNodes()
{
    UIWidget::initNodes();
    m_pImageRender = CCSprite::create();
    m_pRender->addChild(m_pImageRender);
}

void UIImageView::setTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strTextureFile = fileName;
//    setUseMergedTexture(useSpriteFrame);
    m_eImageTexType = texType;
    switch (m_eImageTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enable)
            {
                DYNAMIC_CAST_SCALE9SPRITE->initWithFile(fileName);
                DYNAMIC_CAST_SCALE9SPRITE->setColor(getColor());
                DYNAMIC_CAST_SCALE9SPRITE->setOpacity(getOpacity());
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->initWithFile(fileName);
                DYNAMIC_CAST_CCSPRITE->setColor(getColor());
                DYNAMIC_CAST_CCSPRITE->setOpacity(getOpacity());
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enable)
            {
                DYNAMIC_CAST_SCALE9SPRITE->initWithSpriteFrameName(fileName);
                DYNAMIC_CAST_SCALE9SPRITE->setColor(getColor());
                DYNAMIC_CAST_SCALE9SPRITE->setOpacity(getOpacity());
            }
            else
            {
                DYNAMIC_CAST_CCSPRITE->initWithSpriteFrameName(fileName);
                DYNAMIC_CAST_CCSPRITE->setColor(getColor());
                DYNAMIC_CAST_CCSPRITE->setOpacity(getOpacity());
            }
            break;
        default:
            break;
    }
}

void UIImageView::setTextureRect(const CCRect &rect)
{
    if (m_bScale9Enable)
    {
//        DYNAMIC_CAST_SCALE9SPRITE->setTextureRect(rect);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}

void UIImageView::onTouchBegan(const CCPoint &touchPoint)
{
    setFocus(true);
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    pushDownEvent();
    
    if (m_bDoubleClickEnable)
    {
        m_fClickTimeInterval = 0;
        m_bStartCheckDoubleClick = true;
        m_nClickCount++;
        m_touchRelease = false;
    }
}

void UIImageView::onTouchEnded(const CCPoint &touchPoint)
{
    if (m_bDoubleClickEnable)
    {
        if (m_nClickCount >= 2)
        {
            doubleClickEvent();
            m_nClickCount = 0;
            m_bStartCheckDoubleClick = false;
        }
        else
        {
            m_touchRelease = true;
        }
    }
    else
    {
        UIWidget::onTouchEnded(touchPoint);
    }
}

void UIImageView::doubleClickEvent()
{
    
}

void UIImageView::checkDoubleClick(float dt)
{
    if (m_bStartCheckDoubleClick)
    {
        m_fClickTimeInterval += dt;
        if (m_fClickTimeInterval >= 200 && m_nClickCount > 0)
        {
            m_fClickTimeInterval = 0;
            m_nClickCount--;
            m_bStartCheckDoubleClick = false;
        }
    }
    else
    {
        if (m_nClickCount <= 1)
        {
            if (m_touchRelease)
            {
                releaseUpEvent();
                m_fClickTimeInterval = 0;
                m_nClickCount = 0;
                m_touchRelease = false;
            }
        }
    }
}

void UIImageView::setDoubleClickEnable(bool able)
{
    if (able == m_bDoubleClickEnable)
    {
        return;
    }
    m_bDoubleClickEnable = able;
    if (able)
    {
//        COCOUISYSTEM->getUIInputManager()->addCheckedDoubleClickWidget(this);
    }
    else
    {
        
    }
}

void UIImageView::setFlipX(bool flipX)
{
    if (m_bScale9Enable)
    {
//            dynamic_cast<GUIScale9Sprite*>(m_pImage)->setFlipX(flipX);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlipX(flipX);
    }
}

void UIImageView::setFlipY(bool flipY)
{
    if (m_bScale9Enable)
    {
//            dynamic_cast<GUIScale9Sprite*>(m_pImage)->setFlipX(flipX);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setFlipY(flipY);
    }
}

bool UIImageView::isFlipX()
{
    if (m_bScale9Enable)
    {
        return false;
    }
    else
    {
        return DYNAMIC_CAST_CCSPRITE->isFlipX();
    }
}

bool UIImageView::isFlipY()
{
    if (m_bScale9Enable)
    {
        return false;
    }
    else
    {
        return DYNAMIC_CAST_CCSPRITE->isFlipY();
    }
}

void UIImageView::setScale9Enable(bool able)
{
    if (m_bScale9Enable == able)
    {
        return;
    }
    
    m_nPrevPressstate = WidgetStateNone;
    m_nCurPressState = WidgetStateNone;
    m_bScale9Enable = able;
    m_pRender->removeChild(m_pImageRender, true);
    m_pImageRender = NULL;
    if (m_bScale9Enable)
    {
        m_pImageRender = extension::CCScale9Sprite::create();
    }
    else
    {
        m_pImageRender = CCSprite::create();
    }
    setTexture(m_strTextureFile.c_str(),m_eImageTexType);
    m_pRender->addChild(m_pImageRender);
    setCapInsets(m_capInsets);
    setScale9Size(m_scale9Size);
}

void UIImageView::setScale9Size(const CCSize &size)
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
    DYNAMIC_CAST_SCALE9SPRITE->setContentSize(size);
}

void UIImageView::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
    if (!pNewFrame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
//        DYNAMIC_CAST_SCALE9SPRITE->setDisplayFrame(pNewFrame);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setDisplayFrame(pNewFrame);
    }
}

void UIImageView::setSpriteFrame(CCSpriteFrame *pNewFrame)
{
    if (!pNewFrame)
    {
        return;
    }
    if (m_bScale9Enable)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setSpriteFrame(pNewFrame);
    }
    else
    {
//        DYNAMIC_CAST_CCSPRITE->setSpriteFrame(pNewFrame);
    }
}

void UIImageView::setPreferredSize(const CCSize &pSize)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setPreferredSize(pSize);
}

void UIImageView::setInsetLeft(float insetLeft)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetLeft(insetLeft);
}

void UIImageView::setInsetTop(float insetTop)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetTop(insetTop);
}

void UIImageView::setInsetRight(float insetRight)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetRight(insetRight);
}

void UIImageView::setInsetBottom(float insetBottom)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setInsetBottom(insetBottom);
}

void UIImageView::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enable)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}

CCNode* UIImageView::getValidNode()
{
    return m_pImageRender;
}

void UIImageView::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pImageRender->setAnchorPoint(pt);
}

NS_CC_EXT_END