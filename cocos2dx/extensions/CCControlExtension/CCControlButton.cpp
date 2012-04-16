/*
 * CCControlButton.m
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "CCControlButton.h"
#include "CCScale9Sprite.h"

using namespace std;

enum
{
	kZoomActionTag = 0xCCCB0001,
};

CCControlButton::~CCControlButton()
{
	CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
	CC_SAFE_RELEASE(m_titleLabelDispatchTable);
	CC_SAFE_RELEASE(m_titleColorDispatchTable);
	CC_SAFE_RELEASE(m_titleDispatchTable);
}

//initialisers


bool CCControlButton::initWithLabelAndBackgroundSprite(CCNode* node, CCScale9Sprite* backgroundSprite)
{
	if (CCControl::init())
	{
		assert(node != NULL);
		CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(node);
		CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(node);
		assert(label != NULL || rgbaLabel!=NULL || backgroundSprite != NULL);
		
		setIsTouchEnabled(true);
		pushed=false;
		m_nState=CCControlStateInitial;
		m_currentTitle=NULL;
		m_backgroundSprite=NULL;
		m_titleLabel=NULL;

        // Adjust the background image by default
		m_adjustBackgroundImage=true;

		// Set the default anchor point
		setIsRelativeAnchorPoint(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
        
        // Set the nodes
		m_titleLabel=(node);
        m_backgroundSprite=(backgroundSprite);
        
		 
        // Initialize the button state tables
		m_titleDispatchTable=new CCDictionary();
		//m_titleDispatchTable->autorelease();
		m_titleColorDispatchTable=new CCDictionary();
		//m_titleColorDispatchTable->autorelease();
		m_titleLabelDispatchTable=new CCDictionary();
		//m_titleLabelDispatchTable->autorelease();
		m_backgroundSpriteDispatchTable=new CCDictionary();
		//m_backgroundSpriteDispatchTable->autorelease();

        // Set the default color and opacity
		setColor(ccc3(255, 255, 255));
		setOpacity(255);
		setIsOpacityModifyRGB(true);
        
        // Initialize the dispatch table
		
		CCString* tempString=new CCString(label->getString());
		//tempString->autorelease();
		setTitleForState(tempString, CCControlStateNormal);
		setTitleColorForState(rgbaLabel->getColor(), CCControlStateNormal);
		setTitleLabelForState(node, CCControlStateNormal);
		setBackgroundSpriteForState(backgroundSprite, CCControlStateNormal);
		
		m_nState=CCControlStateNormal;
		
		//default margins
		m_marginH=24;	
		m_marginV=12;

        // Layout update
		needsLayout();

    	return true;
	}
	//couldn't init the CCControl
	else
		return false;
}

CCControlButton* CCControlButton::buttonWithLabelAndBackgroundSprite(CCNode* label, CCScale9Sprite* backgroundSprite)
{
	CCControlButton *pRet = new CCControlButton();
	pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
	pRet->autorelease();
	return pRet;
}

bool CCControlButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
	CCLabelTTF *label = CCLabelTTF::labelWithString(title.c_str(), fontName, fontSize);
	return initWithLabelAndBackgroundSprite(label, CCScale9Sprite::node());
}

CCControlButton* CCControlButton::buttonWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
	CCControlButton *pRet = new CCControlButton();
	pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
	pRet->autorelease();
	return pRet;
}

bool CCControlButton::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
	CCLabelTTF *label = CCLabelTTF::labelWithString("", "Arial", 30);//
	return initWithLabelAndBackgroundSprite(label, sprite);
}

CCControlButton* CCControlButton::buttonWithBackgroundSprite(CCScale9Sprite* sprite)
{
	CCControlButton *pRet = new CCControlButton();
	pRet->initWithBackgroundSprite(sprite);
	pRet->autorelease();
	return pRet;
}


void CCControlButton::setMargins(int marginH, int marginV)
{
	m_marginV=marginV;
	m_marginH=marginH;
	needsLayout();
}

void CCControlButton::setIsEnabled(bool enabled)
{
	CCControl::setIsEnabled(enabled);
	needsLayout();
}

void CCControlButton::setIsSelected(bool enabled)
{
	CCControl::setIsSelected(enabled);
	needsLayout();
}

void CCControlButton::setIsHighlighted(bool enabled)
{
	CCControl::setIsHighlighted(enabled);

	CCAction *action =getActionByTag(kZoomActionTag);
    if (action)
    {
		stopAction(action);        
    }
	needsLayout();

    float scaleValue = (getIsHighlighted() && getIsEnabled() && !getIsSelected()) ? 1.1f : 1.0f;
	CCAction *zoomAction =CCScaleTo::actionWithDuration(0.05f, scaleValue);
	zoomAction->setTag(kZoomActionTag);
	runAction(zoomAction);
}
void CCControlButton::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
	m_adjustBackgroundImage=adjustBackgroundImage;
	needsLayout();
}

bool CCControlButton::getAdjustBackgroundImage()
{
	return m_adjustBackgroundImage;
}

CCString* CCControlButton::getTitleForState(CCControlState state)
{
	CCString* title=(CCString*)m_titleDispatchTable->objectForKey(state);    
    if (title)
    {
        return title;
    }
    return (CCString*)m_titleDispatchTable->objectForKey(CCControlStateNormal);
}

void CCControlButton::setTitleForState(CCString* title, CCControlState state)
{
	m_titleDispatchTable->removeObjectForKey(state);

    if (title)
    {
		m_titleDispatchTable->setObject(title, state);
    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


const ccColor3B CCControlButton::getTitleColorForState(CCControlState state)
{
    ccColor3B returnColor;
	CCColor3bObject* colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(state);    
    if (colorObject)
    {
		returnColor= colorObject->value;
        return returnColor;
    }
	colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(CCControlStateNormal);    
	returnColor=colorObject->value;
    return returnColor;
}

void CCControlButton::setTitleColorForState(ccColor3B color, CCControlState state)
{
	//ccColor3B* colorValue=&color;
	CCColor3bObject* previousObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(state); 
	CC_SAFE_RELEASE(previousObject);
	m_titleColorDispatchTable->removeObjectForKey(state); 
	m_titleColorDispatchTable->setObject(new CCColor3bObject(color), state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

CCNode* CCControlButton::getTitleLabelForState(CCControlState state)
{
	CCNode* titleLabel=(CCNode*)m_titleLabelDispatchTable->objectForKey(state);    
    if (titleLabel)
    {
        return titleLabel;
    }
    return (CCNode*)m_titleLabelDispatchTable->objectForKey(CCControlStateNormal);
}

void CCControlButton::setTitleLabelForState(CCNode* titleLabel, CCControlState state)
{
	CCNode* previousLabel = (CCNode*)m_titleLabelDispatchTable->objectForKey(state);
	if (previousLabel)
    {
		removeChild(previousLabel, true);
		m_titleLabelDispatchTable->removeObjectForKey(state);        
    }

	m_titleLabelDispatchTable->setObject(titleLabel, state);
	titleLabel->setIsVisible(false);
	titleLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(titleLabel, 1);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


CCScale9Sprite* CCControlButton::getBackgroundSpriteForState(CCControlState state)
{
	CCScale9Sprite* backgroundSprite=(CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);    
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}


void CCControlButton::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
	CCScale9Sprite* previousSprite = (CCScale9Sprite*)m_backgroundSpriteDispatchTable->objectForKey(state);
	if (previousSprite)
    {
		removeChild(previousSprite, true);
		m_backgroundSpriteDispatchTable->removeObjectForKey(state);        
    }

	m_backgroundSpriteDispatchTable->setObject(sprite, state);
	sprite->setIsVisible(false);
	sprite->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(sprite);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCControlButton::needsLayout()
{
	// Hide the background and the label
	m_titleLabel->setIsVisible(false);
	m_backgroundSprite->setIsVisible(false);
    
    // Update the label to match with the current state
	//CC_SAFE_RELEASE(m_currentTitle)
	
	m_currentTitle=getTitleForState(m_nState);
	m_currentTitleColor=getTitleColorForState(m_nState);

	m_titleLabel=getTitleLabelForState(m_nState);
	
	CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(m_titleLabel);
	if (label)
		label->setString(m_currentTitle->getCString());
	CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(m_titleLabel);
	if (rgbaLabel)
		rgbaLabel->setColor(m_currentTitleColor);
	m_titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    
    
    // Update the background sprite
	m_backgroundSprite=getBackgroundSpriteForState(m_nState);
	m_backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));

    // Get the title label size
	CCSize titleLabelSize =m_titleLabel->boundingBox().size;
    
    // Adjust the background image if necessary
	if (m_adjustBackgroundImage)
	{
        // Add the margins
		m_backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + m_marginH * 2, titleLabelSize.height + m_marginV * 2));
    } 
	else
    {		
		//TODO: should this also have margins if one of the preferred sizes is relaxed?
        CCSize preferredSize = m_backgroundSprite->getPreferredSize();
        if (preferredSize.width <= 0)
        {
            preferredSize.width = titleLabelSize.width;
        }
        if (preferredSize.height <= 0)
        {
            preferredSize.height = titleLabelSize.height;
        }
        
		m_backgroundSprite->setContentSize(preferredSize);        
    }
    
    // Set the content size
	
	CCRect maxRect = CCControlUtils::CCRectUnion(m_titleLabel->boundingBox(), m_backgroundSprite->boundingBox());
	setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));		
    
	m_titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
	m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
    
	// Make visible the background and the label
	m_titleLabel->setIsVisible(true);
	m_backgroundSprite->setIsVisible(true);	
}



bool CCControlButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !getIsEnabled())
    {
		return false;
	}
    
	m_nState=CCControlStateHighlighted;
	pushed=true;
	this->setIsHighlighted(true);
	sendActionsForControlEvents(CCControlEventTouchDown);
    return true;
}

void CCControlButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{	
    if (!m_bEnabled || !pushed || m_bSelected)
    {
        if (m_bHighlighted)
        {
			setIsHighlighted(false);
        }
        return;
    }
    
	bool isTouchMoveInside = isTouchInside(pTouch);
    if (isTouchMoveInside && !m_bHighlighted)
    {
        m_nState = CCControlStateHighlighted;
		setIsHighlighted(true);
		sendActionsForControlEvents(CCControlEventTouchDragEnter);
    }
	else if (isTouchMoveInside && m_bHighlighted)
    {
		sendActionsForControlEvents(CCControlEventTouchDragInside);
    }
	else if (!isTouchMoveInside && m_bHighlighted)
    {
        m_nState = CCControlStateNormal;
			setIsHighlighted(false);
        
		sendActionsForControlEvents(CCControlEventTouchDragExit);        
    }
	else if (!isTouchMoveInside && !m_bHighlighted)
    {
		sendActionsForControlEvents(CCControlEventTouchDragOutside);        
    }
}
void CCControlButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_nState = CCControlStateNormal;
    pushed = false;
	setIsHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
		sendActionsForControlEvents(CCControlEventTouchUpInside);        
    }
	else
    {
		sendActionsForControlEvents(CCControlEventTouchUpOutside);        
    }
}

void CCControlButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_nState = CCControlStateNormal;
    pushed = false;
	setIsHighlighted(false);
	sendActionsForControlEvents(CCControlEventTouchCancel);
}
