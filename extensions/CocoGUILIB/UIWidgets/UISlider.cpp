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

#include "UISlider.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

UISlider::UISlider()
: m_fBarLength(0.0)
, m_nDirection(0)
, m_nBarPercent(0)
, m_pSlidBall(NULL)
, m_fBarNodeScaleValue(1.0)
, m_fTouchMoveStartLocation(0.0)
, m_fMinLength(0.0)
, m_pBarNode(NULL)
, m_pPercentListener(NULL)
, m_pfnPercentSelector(NULL)
, m_bBarScale9Enable(false)
, m_bProgressBarVisible(false)
, m_pProgressBarNode(NULL)
, m_eBarTexType(UI_TEX_TYPE_LOCAL)
, m_eBarTexS9Type(UI_TEX_TYPE_LOCAL)
, m_eBallNTexType(UI_TEX_TYPE_LOCAL)
, m_eBallPTexType(UI_TEX_TYPE_LOCAL)
, m_eBallDTexType(UI_TEX_TYPE_LOCAL)
, m_strTextureFile("")
, m_capInsets(CCRectZero)
, m_scale9Size(CCSizeZero)
, m_strProgressTextureFile("")
, m_eProgressBarTexType(UI_TEX_TYPE_LOCAL)
, m_bProgressBarScale9Enable(false)
, m_progressBarCapInsets(CCRectZero)
, m_progressBarScale9Size(CCSizeZero)
{
    m_WidgetName = WIDGET_SLIDER;
}

UISlider::~UISlider()
{
    
}

UISlider* UISlider::create()
{
    UISlider* widget = new UISlider();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UISlider::init()
{
    if (UIWidget::init())
    {
        m_pBarNode = CCSprite::create();
        m_pRender->addChild(m_pBarNode, -1);
        
        m_pProgressBarNode = CCSprite::create();
        m_pProgressBarNode->setVisible(false);
        m_pRender->addChild(m_pProgressBarNode, 0);
        
        m_pSlidBall = UIButton::create();
		m_pSlidBall->setWidgetZOrder(1);
        addChild(m_pSlidBall);
        
        return true;
    }
    return false;
}

void UISlider::setBarTexture(const char* fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strTextureFile = fileName;
    m_eBarTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bBarScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarNode)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarNode)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bBarScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarNode)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarNode)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bBarScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBarNode)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pBarNode)->setOpacity(getOpacity());
    }
    
    m_fBarLength = m_pBarNode->getContentSize().width - m_pSlidBall->getContentSize().width;
    setSlidBallPercent(m_nBarPercent);	

	m_pProgressBarNode->setPosition(ccp(m_pBarNode->getPosition().x - (m_fBarLength / 2 + m_pSlidBall->getContentSize().width / 2), 
										m_pBarNode->getPosition().y));
}

void UISlider::setScale9Enable(bool able)
{
    if (m_bBarScale9Enable == able)
    {
        return;
    }
    m_bBarScale9Enable = able;
    
    m_pRender->removeChild(m_pBarNode, true);
    m_pBarNode = NULL;
    if (m_bBarScale9Enable)
    {
        m_pBarNode = CCScale9Sprite::create();
    }
    else
    {
        m_pBarNode = CCSprite::create();
    }
    
    setBarTexture(m_strTextureFile.c_str(), m_eBarTexType);
    m_pRender->addChild(m_pBarNode, -1);	
}

void UISlider::setCapInsets(const CCRect &capInsets)
{
    if (!m_bBarScale9Enable)
    {
        return;
    }
    m_capInsets = capInsets;
    dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setCapInsets(capInsets);
}

void UISlider::setScale9Size(const CCSize &size)
{
    if (!m_bBarScale9Enable)
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
    dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setContentSize(size);
    m_fBarLength = size.width - m_pSlidBall->getContentSize().width;
    setSlidBallPercent(m_nBarPercent);	

	m_pProgressBarNode->setPosition(ccp(m_pBarNode->getPosition().x - (m_fBarLength / 2 + m_pSlidBall->getContentSize().width / 2), 
                                        m_pBarNode->getPosition().y));
}

void UISlider::setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
    m_pSlidBall->setTextures(normal, pressed, disabled,texType);
    if (m_bBarScale9Enable)
    {
        m_fBarLength = m_scale9Size.width - m_pSlidBall->getContentSize().width;
    }
    else
    {
        m_fBarLength = m_pBarNode->getContentSize().width - m_pSlidBall->getContentSize().width;
    }
    setSlidBallPercent(m_nBarPercent);
}

void UISlider::setSlidBallNormalTexture(const char* normal,TextureResType texType)
{
    m_pSlidBall->setNormalTexture(normal,texType);
	if (m_bBarScale9Enable)
	{
		m_fBarLength = m_scale9Size.width - m_pSlidBall->getContentSize().width;
	}
	else
	{
		m_fBarLength = m_pBarNode->getContentSize().width - m_pSlidBall->getContentSize().width;
	}
	setSlidBallPercent(m_nBarPercent);
}

void UISlider::setSlidBallPressedTexture(const char* pressed,TextureResType texType)
{
    m_pSlidBall->setPressedTexture(pressed,texType);
	if (m_bBarScale9Enable)
	{
		m_fBarLength = m_scale9Size.width - m_pSlidBall->getContentSize().width;
	}
	else
	{
		m_fBarLength = m_pBarNode->getContentSize().width - m_pSlidBall->getContentSize().width;
	}
	setSlidBallPercent(m_nBarPercent);
}

void UISlider::setSlidBallDisabledTexture(const char* disabled,TextureResType texType)
{
    m_pSlidBall->setDisabledTexture(disabled,texType);
	if (m_bBarScale9Enable)
	{
		m_fBarLength = m_scale9Size.width - m_pSlidBall->getContentSize().width;
	}
	else
	{
		m_fBarLength = m_pBarNode->getContentSize().width - m_pSlidBall->getContentSize().width;
	}
	setSlidBallPercent(m_nBarPercent);
}

void UISlider::setSlidBallAnchorPoint(const CCPoint &anchor)
{
    m_pSlidBall->setAnchorPoint(anchor);
}

void UISlider::setBarLength(float length)
{
    if (!m_bBarScale9Enable)
    {
        return;
    }
    m_fBarLength = length;
    dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setContentSize(CCSize(length, m_pBarNode->getContentSize().height));
    setSlidBallPercent(m_nBarPercent);
    setProgressBarScale();
}

void UISlider::setSlidBallPercent(int percent)
{
    m_nBarPercent = percent;
    float dis = m_fBarLength * (percent / 100.0);
    m_pSlidBall->setPosition(ccp(-m_fBarLength / 2.0 + dis, 0));    
}

int UISlider::getClickPercent(float location)
{
    getLocationInWindow();
    float leftEndPos = m_locationInWindow.x - m_fBarLength/2.0;
    float per = (location - leftEndPos)/m_fBarLength;
    per *= 100;
    return per;
}

void UISlider::checkSlidBoundary()
{
    if (m_pSlidBall->getPosition().x > m_fBarLength / 2.0)
    {
        m_pSlidBall->setPosition(ccp(m_fBarLength / 2.0, 0));
    }
    else if(m_pSlidBall->getPosition().x < -m_fBarLength / 2.0)
    {
        m_pSlidBall->setPosition(ccp(-m_fBarLength / 2.0, 0));
    }
}

bool UISlider::isProgressBarVisible()
{
    return m_bProgressBarVisible;
}

void UISlider::setProgressBarVisible(bool show)
{
    if (m_bProgressBarVisible == show)
    {
        return;
    }
    m_bProgressBarVisible = show;
    
    m_pProgressBarNode->setVisible(m_bProgressBarVisible);
}

const CCSize& UISlider::getProgressBarTextureSize() const
{
	return m_pProgressBarTextureSize;
}

void UISlider::setProgressBarTexture(const char *fileName, TextureResType texType)
{   
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strProgressTextureFile = fileName;
    
	m_eProgressBarTexType = texType;
    switch (m_eProgressBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bProgressBarScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pProgressBarNode)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bProgressBarScale9Enable)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->initWithSpriteFrameName(fileName);
            }
            else
            {                
                dynamic_cast<CCSprite*>(m_pProgressBarNode)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bProgressBarScale9Enable)
    {
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pProgressBarNode)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pProgressBarNode)->setOpacity(getOpacity());
    }    
	m_pProgressBarTextureSize = m_pProgressBarNode->getContentSize();
    m_pProgressBarNode->setAnchorPoint(ccp(0.0, 0.5));    
	m_pProgressBarNode->setPosition(ccp(m_pBarNode->getPosition().x - (m_fBarLength / 2 + m_pSlidBall->getContentSize().width / 2), 
										m_pBarNode->getPosition().y));
}

void UISlider::setProgressBarScale9Enable(bool able)
{
    if (m_bProgressBarScale9Enable == able)
    {
        return;
    }
    m_bProgressBarScale9Enable = able;
    
    m_pRender->removeChild(m_pProgressBarNode, true);
    m_pProgressBarNode = NULL;
    if (m_bProgressBarScale9Enable)
    {
        m_pProgressBarNode = CCScale9Sprite::create();
    }
    else
    {
        m_pProgressBarNode = CCSprite::create();
    }
    m_pProgressBarNode->setVisible(m_bProgressBarVisible);
    
    setProgressBarTexture(m_strProgressTextureFile.c_str(), m_eProgressBarTexType);
    m_pRender->addChild(m_pProgressBarNode, 0);
}

void UISlider::setProgressBarCapInsets(const CCRect &capInsets)
{
    if (!m_bProgressBarScale9Enable)
    {
        return;
    }
    m_progressBarCapInsets = capInsets;
    dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setCapInsets(capInsets);
}

void UISlider::setProgressBarScale9Size(const CCSize &size)
{
    if (!m_bProgressBarScale9Enable)
    {
        return;
    }
    if (size.equals(CCSizeZero))
    {
        return;
    }
    else
    {
        m_progressBarScale9Size = size;
    }
	dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setContentSize(size);	
}

void UISlider::setProgressBarScale()
{
    float width = (float)(m_nBarPercent) / 100 * m_fBarLength;
    
    float offset = m_pSlidBall->getContentSize().width / 2;
    	
    m_pProgressBarNode->setPosition(ccp(m_pBarNode->getPosition().x - (m_fBarLength / 2 + offset), m_pBarNode->getPosition().y));
    if (m_bProgressBarScale9Enable)
    {
        if (width < m_pSlidBall->getContentSize().width)
        {			
            width = m_pSlidBall->getContentSize().width;
        }
        else
        {			
            width += offset;
        }
        m_pProgressBarNode->setContentSize(CCSize(width, m_pProgressBarNode->getContentSize().height));
    }
    else
    {
        CCRect textureRect = dynamic_cast<CCSprite*>(m_pProgressBarNode)->getTextureRect();
        CCPoint textureOrigin = textureRect.origin;
		CCSize textureSize = textureRect.size;
        dynamic_cast<CCSprite*>(m_pProgressBarNode)->setTextureRect(CCRectMake(textureOrigin.x, textureOrigin.y, width + offset, textureSize.height));
    }
}

void UISlider::onTouchBegan(const CCPoint &touchPoint)
{
    UIWidget::onTouchBegan(touchPoint);
    CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    m_pSlidBall->setPosition(ccp(nsp.x,0));
    m_pSlidBall->setPressState(WidgetStateSelected);
    m_nBarPercent = getPercentWithBallPos(m_pSlidBall->getPosition().x,0);
    percentChangedEvent();
    setProgressBarScale();
}

void UISlider::onTouchMoved(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    m_pSlidBall->setPosition(ccp(nsp.x,0));
    checkSlidBoundary();
    m_nBarPercent = getPercentWithBallPos(m_pSlidBall->getPosition().x,0);
    percentChangedEvent();
    setProgressBarScale();
}

void UISlider::onTouchEnded(const CCPoint &touchPoint)
{
    UIWidget::onTouchEnded(touchPoint);
    m_pSlidBall->setPressState(WidgetStateNormal);
}

void UISlider::onTouchCancelled(const CCPoint &touchPoint)
{
    UIWidget::onTouchCancelled(touchPoint);
    m_pSlidBall->setPressState(WidgetStateNormal);
}

float UISlider::getPercentWithBallPos(float px,float py)
{
    return (((px-(-m_fBarLength/2.0))/m_fBarLength)*100);
}

bool UISlider::pointAtSelfBody(const CCPoint &pt)
{
    if (!getAbsoluteVisible())
    {
        return false;
    }
    if (UIWidget::pointAtSelfBody(pt))
    {
        return true;
    }
    
    bool hitBall = hitTest(m_pSlidBall->getValidNode(),pt);
    if (hitBall) {
        return true;
    }
    return false;
}

CCNode* UISlider::getValidNode()
{
    return m_pBarNode;
}

void UISlider::addPercentChangedEvent(CCObject *target, SEL_PushEvent selector)
{
    m_pPercentListener = target;
    m_pfnPercentSelector = selector;
}

void UISlider::percentChangedEvent()
{
    if (m_pPercentListener && m_pfnPercentSelector)
    {
        (m_pPercentListener->*m_pfnPercentSelector)(this);
    }
}

int UISlider::getPercent()
{
    return m_nBarPercent;
}

NS_CC_EXT_END