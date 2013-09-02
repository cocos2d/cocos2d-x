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

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(m_pImageRenderer)
#define DYNAMIC_CAST_SCALE9SPRITE dynamic_cast<cocos2d::extension::CCScale9Sprite*>(m_pImageRenderer)

UIImageView::UIImageView():
m_nViewType(1),
m_nClickCount(0),
m_fClickTimeInterval(0.0),
m_bStartCheckDoubleClick(false),
m_touchRelease(false),
m_bDoubleClickEnabled(false),
m_bScale9Enabled(false),
m_pImageRenderer(NULL),
m_strTextureFile(""),
m_capInsets(CCRectZero),
m_eImageTexType(UI_TEX_TYPE_LOCAL),
m_imageTextureSize(m_size),
m_bPrevIgnoreSize(true)
{

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

void UIImageView::initRenderer()
{
    UIWidget::initRenderer();
    m_pImageRenderer = CCSprite::create();
    m_pRenderer->addChild(m_pImageRenderer);
}

void UIImageView::loadTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strTextureFile = fileName;
    m_eImageTexType = texType;
    switch (m_eImageTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
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
            if (m_bScale9Enabled)
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
    m_imageTextureSize = m_pImageRenderer->getContentSize();
    updateAnchorPoint();
    imageTextureScaleChangedWithSize();
}

void UIImageView::setTextureRect(const CCRect &rect)
{
    if (m_bScale9Enabled)
    {
//        DYNAMIC_CAST_SCALE9SPRITE->setTextureRect(rect);
    }
    else
    {
        DYNAMIC_CAST_CCSPRITE->setTextureRect(rect);
    }
}

bool UIImageView::onTouchBegan(const CCPoint &touchPoint)
{
    setFocus(true);
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    pushDownEvent();
    
    if (m_bDoubleClickEnabled)
    {
        m_fClickTimeInterval = 0;
        m_bStartCheckDoubleClick = true;
        m_nClickCount++;
        m_touchRelease = false;
    }
    return m_bTouchPassedEnabled;
}

void UIImageView::onTouchEnded(const CCPoint &touchPoint)
{
    if (m_bDoubleClickEnabled)
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

void UIImageView::setDoubleClickEnabled(bool able)
{
    if (able == m_bDoubleClickEnabled)
    {
        return;
    }
    m_bDoubleClickEnabled = able;
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
    if (m_bScale9Enabled)
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
    if (m_bScale9Enabled)
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
    if (m_bScale9Enabled)
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
    if (m_bScale9Enabled)
    {
        return false;
    }
    else
    {
        return DYNAMIC_CAST_CCSPRITE->isFlipY();
    }
}

void UIImageView::setScale9Enabled(bool able)
{
    if (m_bScale9Enabled == able)
    {
        return;
    }
    
    
    m_bScale9Enabled = able;
    m_pRenderer->removeChild(m_pImageRenderer, true);
    m_pImageRenderer = NULL;
    if (m_bScale9Enabled)
    {
        m_pImageRenderer = extension::CCScale9Sprite::create();
    }
    else
    {
        m_pImageRenderer = CCSprite::create();
    }
    loadTexture(m_strTextureFile.c_str(),m_eImageTexType);
    m_pRenderer->addChild(m_pImageRenderer);
    if (m_bScale9Enabled)
    {
        bool ignoreBefore = m_bIgnoreSize;
        ignoreContentAdaptWithSize(false);
        m_bPrevIgnoreSize = ignoreBefore;
    }
    else
    {
        ignoreContentAdaptWithSize(m_bPrevIgnoreSize);
    }
    setCapInsets(m_capInsets);
}

void UIImageView::ignoreContentAdaptWithSize(bool ignore)
{
    if (!m_bScale9Enabled || (m_bScale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        m_bPrevIgnoreSize = ignore;
    }
}

void UIImageView::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
    if (!pNewFrame)
    {
        return;
    }
    if (m_bScale9Enabled)
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
    if (m_bScale9Enabled)
    {
        DYNAMIC_CAST_SCALE9SPRITE->setSpriteFrame(pNewFrame);
    }
    else
    {
//        DYNAMIC_CAST_CCSPRITE->setSpriteFrame(pNewFrame);
    }
}

void UIImageView::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    DYNAMIC_CAST_SCALE9SPRITE->setCapInsets(capInsets);
}

void UIImageView::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pImageRenderer->setAnchorPoint(pt);
}

void UIImageView::onSizeChanged()
{
    imageTextureScaleChangedWithSize();
}

const CCSize& UIImageView::getContentSize() const
{
    return m_imageTextureSize;
}

CCNode* UIImageView::getVirtualRenderer()
{
    return m_pImageRenderer;
}

void UIImageView::imageTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            m_pImageRenderer->setScale(1.0f);
            m_size = m_imageTextureSize;
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pImageRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize textureSize = m_pImageRenderer->getContentSize();
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                m_pImageRenderer->setScale(1.0f);
                return;
            }
            float scaleX = m_size.width / textureSize.width;
            float scaleY = m_size.height / textureSize.height;
            m_pImageRenderer->setScaleX(scaleX);
            m_pImageRenderer->setScaleY(scaleY);
        }
    }
}

NS_CC_EXT_END