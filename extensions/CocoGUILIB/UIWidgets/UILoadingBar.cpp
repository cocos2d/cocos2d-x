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

#include "UILoadingBar.h"
/* gui mark */
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"
/**/

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(m_pRenderBar)

UILoadingBar::UILoadingBar():
m_nBarType(LoadingBarTypeLeft),
m_nPercent(100),
m_fTotalLength(0),
m_fBarHeight(0),
m_pRenderBar(NULL),
m_eRenderBarTexType(UI_TEX_TYPE_LOCAL),
/* gui mark */
m_bScale9Enable(false),
m_capInsets(CCRectZero),
m_scale9Size(CCSizeZero),
m_strTextureFile("")
/**/
{
    m_WidgetName = WIDGET_LOADINGBAR;
}

UILoadingBar::~UILoadingBar()
{
    
}

UILoadingBar* UILoadingBar::create()
{
    UILoadingBar* widget = new UILoadingBar();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILoadingBar::initNodes()
{
    UIWidget::initNodes();
    m_pRenderBar = CCSprite::create();
    m_pRender->addChild(m_pRenderBar);
    m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
}

void UILoadingBar::setDirection(LoadingBarType dir)
{
    if (m_nBarType == dir)
    {
        return;
    }
    m_nBarType = dir;

    switch (m_nBarType)
    {
        case LoadingBarTypeLeft:
            m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
            m_pRenderBar->setPosition(ccp(-m_fTotalLength*0.5f,0.0f));
            /* gui mark */
            if (!m_bScale9Enable)
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->setFlipX(false);
            }
            // before
//            m_pRenderBar->setFlipX(false);
            /**/
            break;
        case LoadingBarTypeRight:
            m_pRenderBar->setAnchorPoint(ccp(1.0,0.5));
            m_pRenderBar->setPosition(ccp(m_fTotalLength*0.5f,0.0f));
            /* gui mark */
            if (!m_bScale9Enable)
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->setFlipX(true);
            }
            // before
//            m_pRenderBar->setFlipX(true);
            /**/

            break;
    }
}

int UILoadingBar::getDirection()
{
    return m_nBarType;
}

void UILoadingBar::setTexture(const char* texture,TextureResType texType)
{
    if (!texture || strcmp(texture, "") == 0)
    {
        return;
    }
    m_strTextureFile = texture;
//    setUseMergedTexture(useSpriteFrame);
    m_eRenderBarTexType = texType;
    switch (m_eRenderBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            /* gui mark */
            if (m_bScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->initWithFile(texture);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->initWithFile(texture);
            }
            // before
//            m_pRenderBar->initWithFile(texture);
            /**/
            break;
        case UI_TEX_TYPE_PLIST:
            /* gui mark */
            if (m_bScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->initWithSpriteFrameName(texture);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->initWithSpriteFrameName(texture);
            }
            // before
//            m_pRenderBar->initWithSpriteFrameName(texture);
            /**/
            break;
        default:
            break;
    }
    
    /* gui mark */
    if (m_bScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pRenderBar)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pRenderBar)->setOpacity(getOpacity());
    }
    // before
    /*
    m_pRenderBar->setColor(getColor());
    m_pRenderBar->setOpacity(getOpacity());
     */
    /**/
    
    m_fTotalLength = m_pRenderBar->getContentSize().width;
    m_fBarHeight = m_pRenderBar->getContentSize().height;        

    switch (m_nBarType)
    {
    case LoadingBarTypeLeft:
        m_pRenderBar->setAnchorPoint(ccp(0.0,0.5));
        m_pRenderBar->setPosition(ccp(-m_fTotalLength*0.5f,0.0f));
            /* gui mark */
            if (!m_bScale9Enable)
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->setFlipX(false);
            }
            // before
//        m_pRenderBar->setFlipX(false);
            /**/
        break;
    case LoadingBarTypeRight:
        m_pRenderBar->setAnchorPoint(ccp(1.0,0.5));
        m_pRenderBar->setPosition(ccp(m_fTotalLength*0.5f,0.0f));
            /* gui mark */
            if (!m_bScale9Enable)
            {
                dynamic_cast<CCSprite*>(m_pRenderBar)->setFlipX(true);
            }
            // before
//        m_pRenderBar->setFlipX(true);
            /**/
        break;
    }
}

/* gui mark */
void UILoadingBar::setScale9Enable(bool able)
{
    if (m_bScale9Enable == able)
    {
        return;
    }
    
    m_nPrevPressstate = WidgetStateNone;
    m_nCurPressState = WidgetStateNone;
    m_bScale9Enable = able;
    m_pRender->removeChild(m_pRenderBar, true);
    m_pRenderBar = NULL;
    if (m_bScale9Enable)
    {
        m_pRenderBar= CCScale9Sprite::create();
    }
    else
    {
        m_pRenderBar = CCSprite::create();
    }
    setTexture(m_strTextureFile.c_str(),m_eRenderBarTexType);
    m_pRender->addChild(m_pRenderBar);
//    setCapInsets(m_capInsets);
//    setScale9Size(m_scale9Size);
}

void UILoadingBar::setCapInsets(const CCRect &capInsets)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    m_capInsets = capInsets;
    
    dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->setCapInsets(capInsets);
}

void UILoadingBar::setScale9Size(const CCSize &size)
{
    if (!m_bScale9Enable)
    {
        return;
    }
    if (size.equals(CCSizeZero))
    {
        return;
    }
    else
    {
        m_scale9Size = size;
    }
    dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->setContentSize(size);
    
    m_fTotalLength = size.width;
    setScale9Scale();
}

void UILoadingBar::setScale9Scale()
{
    switch (m_nBarType)
    {
        case LoadingBarTypeLeft:
            m_pRenderBar->setPosition(ccp(-m_fTotalLength * 0.5f, 0.0f));
            break;
            
        case LoadingBarTypeRight:
            m_pRenderBar->setPosition(ccp(m_fTotalLength * 0.5f, 0.0f));
            break;
            
        default:
            break;
    }
    float width = (float)(m_nPercent) / 100 * m_fTotalLength;
    dynamic_cast<CCScale9Sprite*>(m_pRenderBar)->setContentSize(CCSizeMake(width, m_fBarHeight));
}
/**/

void UILoadingBar::setPercent(int percent)
{
    if ( percent < 0 || percent > 100)
    {
        return;
    }
    if (m_fTotalLength <= 0)
    {
        return;
    }
    m_nPercent = percent;
    float res = m_nPercent/100.0;
    
    int x = 0, y = 0;
    switch (m_eRenderBarTexType)
    {
        case UI_TEX_TYPE_PLIST:
        {
            CCSprite* barNode = DYNAMIC_CAST_CCSPRITE;
            if (barNode)
            {
                CCPoint to = barNode->getTextureRect().origin;
                x = to.x;
                y = to.y;
            }
            break;
        }
        default:
            break;
    }
    
    /* gui mark */
    if (m_bScale9Enable)
    {        
        setScale9Scale();
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pRenderBar)->setTextureRect(CCRectMake(x, y, m_fTotalLength * res, m_fBarHeight));
    }
//    m_pRenderBar->setTextureRect(CCRect(x, y, m_fTotalLength * res, m_fBarHeight));
    /**/
}

int UILoadingBar::getPercent()
{
    return m_nPercent;
}

CCNode* UILoadingBar::getValidNode()
{
    return m_pRenderBar;
}

float UILoadingBar::getTotalWidth()
{
    return m_fTotalLength;
}

float UILoadingBar::getTotalHeight()
{
    return m_fBarHeight;
}

NS_CC_EXT_END