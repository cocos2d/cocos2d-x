/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
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
#include "support/CCPointExtension.h"
#include "label_nodes/CCLabelTTF.h"
#include "label_nodes/CCLabelBMFont.h"
#include "actions/CCAction.h"
#include "actions/CCActionInterval.h"

using namespace std;

NS_CC_EXT_BEGIN

enum
{
    kZoomActionTag = 0xCCCB0001,
};

CCControlButton::CCControlButton()
: m_currentTitle(nullptr)
, m_currentTitleColor(ccWHITE)
, m_doesAdjustBackgroundImage(false)
, m_titleLabel(nullptr)
, m_backgroundSprite(nullptr)
, m_zoomOnTouchDown(false)
, m_isPushed(false)
, m_bParentInited(false)
, m_titleDispatchTable(nullptr)
, m_titleColorDispatchTable(nullptr)
, m_titleLabelDispatchTable(nullptr)
, m_backgroundSpriteDispatchTable(nullptr)
, m_marginV(CCControlButtonMarginTB)
, m_marginH(CCControlButtonMarginLR)
{

}

CCControlButton::~CCControlButton()
{
    CC_SAFE_RELEASE(m_currentTitle);
    CC_SAFE_RELEASE(m_titleLabel);
    CC_SAFE_RELEASE(m_backgroundSpriteDispatchTable);
    CC_SAFE_RELEASE(m_titleLabelDispatchTable);
    CC_SAFE_RELEASE(m_titleColorDispatchTable);
    CC_SAFE_RELEASE(m_titleDispatchTable);
    CC_SAFE_RELEASE(m_backgroundSprite);
}

//initialisers

bool CCControlButton::init(bool is9Patch /*= true*/)
{
    CCNode* pBackgroundSprite;
    if(is9Patch)
    {
    	pBackgroundSprite = CCScale9Sprite::create();
    }
    else
    {
    	pBackgroundSprite = CCSprite::create();
    }
    return this->initWithLabelAndBackgroundSprite(CCLabelTTF::create("", "Helvetica", 12), pBackgroundSprite);
}

bool CCControlButton::initWithLabelAndBackgroundSprite(CCNode* pNode, CCNode* pBackgroundSprite)
{
    if (CCControl::init())
    {
        CCAssert(pNode != nullptr, "Label must not be nil.");
        CCLabelProtocol* pLabel = dynamic_cast<CCLabelProtocol*>(pNode);
        CCRGBAProtocol* pRgbaLabel = dynamic_cast<CCRGBAProtocol*>(pNode);
        CCAssert(pBackgroundSprite != nullptr, "Background sprite must not be nil.");
        CCAssert(pLabel != nullptr || pRgbaLabel!=nullptr || pBackgroundSprite != nullptr, "");
        
        m_bParentInited = true;

        // Initialize the button state tables
        this->setTitleDispatchTable(CCDictionary::create());
        this->setTitleColorDispatchTable(CCDictionary::create());
        this->setTitleLabelDispatchTable(CCDictionary::create());
        this->setBackgroundSpriteDispatchTable(CCDictionary::create());

        setTouchEnabled(true);
        m_isPushed = false;
        m_zoomOnTouchDown = true;

        m_currentTitle=nullptr;

        // Adjust the background image by default if we have CCScale9Sprite
        setAdjustBackgroundImage(dynamic_cast<CCScale9Sprite*>(pBackgroundSprite) != nullptr);

        setPreferredSize(m_doesAdjustBackgroundImage ?
        	CCSizeZero
        	:pBackgroundSprite->boundingBox().size);
        // Zooming button by default
        m_zoomOnTouchDown = true;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp(0.5f, 0.5f));
        
        // Set the nodes
        setTitleLabel(pNode);
        setBackgroundSprite(pBackgroundSprite);

        // Set the default color and opacity
        setColor(ccc3(255.0f, 255.0f, 255.0f));
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        CCString* pTempString = CCString::create(pLabel->getString());
        //tempString->autorelease();
        setTitleForState(pTempString, CCControlStateNormal);
        setTitleColorForState(pRgbaLabel->getColor(), CCControlStateNormal);
        setTitleLabelForState(pNode, CCControlStateNormal);
        setBackgroundSpriteForState(pBackgroundSprite, CCControlStateNormal);
        
        setLabelAnchorPoint(ccp(0.5f, 0.5f));

        // Layout update
        needsLayout();

        return true;
    }
    //couldn't init the CCControl
    else
    {
        return false;
    }
}

CCControlButton* CCControlButton::create(CCNode* pLabel, CCNode* pBackgroundSprite)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithLabelAndBackgroundSprite(pLabel, pBackgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool CCControlButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize, bool is9Patch /*= true*/)
{
    CCLabelTTF *label = CCLabelTTF::create(title.c_str(), fontName, fontSize);
    CCNode* pBackgroundSprite;
    if(is9Patch)
    {
    	pBackgroundSprite = CCScale9Sprite::create();
    }
    else
    {
    	pBackgroundSprite = CCSprite::create();
    }
    return initWithLabelAndBackgroundSprite(label, pBackgroundSprite);
}

CCControlButton* CCControlButton::create(string title, const char * fontName, float fontSize, bool is9Patch /*= true*/)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize,is9Patch);
    pRet->autorelease();
    return pRet;
}

bool CCControlButton::initWithBackgroundSprite(CCNode* pSprite)
{
    CCLabelTTF *label = CCLabelTTF::create("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, pSprite);
}

CCControlButton* CCControlButton::create(CCNode* pSprite)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithBackgroundSprite(pSprite);
    pRet->autorelease();
    return pRet;
}


void CCControlButton::setMargins(int marginH, int marginV)
{
    m_marginV = marginV;
    m_marginH = marginH;
    needsLayout();
}

void CCControlButton::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    needsLayout();
}

void CCControlButton::setSelected(bool enabled)
{
    CCControl::setSelected(enabled);
    needsLayout();
}

void CCControlButton::setHighlighted(bool enabled)
{
    if (enabled == true)
    {
        m_eState = CCControlStateHighlighted;
    }
    else
    {
        m_eState = CCControlStateNormal;
    }
    
    CCControl::setHighlighted(enabled);

    CCAction *action = getActionByTag(kZoomActionTag);
    if (action)
    {
        stopAction(action);        
    }
    needsLayout();
    if( m_zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
        CCAction *zoomAction = CCScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kZoomActionTag);
        runAction(zoomAction);
    }
}

void CCControlButton::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    m_zoomOnTouchDown = zoomOnTouchDown;
}

bool CCControlButton::getZoomOnTouchDown()
{
    return m_zoomOnTouchDown;
}

void CCControlButton::setPreferredSize(CCSize size)
{
    if(size.width == 0 && size.height == 0)
    {
        m_doesAdjustBackgroundImage = true;
    }
    else
    {
        m_doesAdjustBackgroundImage = false;
        CCDictElement * item = nullptr;
        CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
        {
            CCObject* pObject = item->getObject();
            CCScale9Sprite* pSprite = dynamic_cast<CCScale9Sprite*>(pObject);
            if(pSprite != nullptr)
            {
            	pSprite->setPreferredSize(size);
            }
        }
    }

    m_preferredSize = size;
    needsLayout();
}

CCSize CCControlButton::getPreferredSize()
{
    return m_preferredSize;
}

void CCControlButton::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
    m_doesAdjustBackgroundImage=adjustBackgroundImage;
    needsLayout();
}

bool CCControlButton::doesAdjustBackgroundImage()
{
    return m_doesAdjustBackgroundImage;
}

CCPoint CCControlButton::getLabelAnchorPoint()
{
    return this->m_labelAnchorPoint;
}

void CCControlButton::setLabelAnchorPoint(CCPoint labelAnchorPoint)
{
    this->m_labelAnchorPoint = labelAnchorPoint;
    if (m_titleLabel != nullptr)
    {
        this->m_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

CCString* CCControlButton::getTitleForState(CCControlState state)
{
    if (m_titleDispatchTable != nullptr)
    {
        CCString* title=(CCString*)m_titleDispatchTable->objectForKey(state);    
        if (title)
        {
            return title;
        }
        return (CCString*)m_titleDispatchTable->objectForKey(CCControlStateNormal);
    }
    return CCString::create("");
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
    ccColor3B returnColor = ccWHITE;
    do 
    {
        CC_BREAK_IF(nullptr == m_titleColorDispatchTable);
        CCColor3bObject* colorObject=(CCColor3bObject*)m_titleColorDispatchTable->objectForKey(state);    
        if (colorObject)
        {
            returnColor = colorObject->value;
            break;
        }

        colorObject = (CCColor3bObject*)m_titleColorDispatchTable->objectForKey(CCControlStateNormal);   
        if (colorObject)
        {
            returnColor = colorObject->value;
        }
    } while (0);

    return returnColor;
}

void CCControlButton::setTitleColorForState(ccColor3B color, CCControlState state)
{
    //ccColor3B* colorValue=&color;
    m_titleColorDispatchTable->removeObjectForKey(state); 
    CCColor3bObject* pColor3bObject = new CCColor3bObject(color);
    pColor3bObject->autorelease();
    m_titleColorDispatchTable->setObject(pColor3bObject, state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

CCNode* CCControlButton::getTitleLabelForState(CCControlState state)
{
    CCNode* titleLabel = (CCNode*)m_titleLabelDispatchTable->objectForKey(state);    
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
    titleLabel->setVisible(false);
    titleLabel->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(titleLabel, 1);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCControlButton::setTitleTTFForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelTTF::create(title->getCString(), fntFile, 12), state);
}

const char * CCControlButton::getTitleTTFForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != nullptr)
    {
        return labelTTF->getFontName();
    }
    else
    {
        return "";
    }
}

void CCControlButton::setTitleTTFSizeForState(float size, CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
        if(labelTTF != nullptr)
        {
            return labelTTF->setFontSize(size);
        }
    }
}

float CCControlButton::getTitleTTFSizeForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != nullptr)
    {
        return labelTTF->getFontSize();
    }
    else
    {
        return 0;
    }
}

void CCControlButton::setTitleBMFontForState(const char * fntFile, CCControlState state)
{
    CCString * title = this->getTitleForState(state);
    if (!title)
    {
        title = CCString::create("");
    }
    this->setTitleLabelForState(CCLabelBMFont::create(title->getCString(), fntFile), state);
}

const char * CCControlButton::getTitleBMFontForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelBMFont* labelBMFont = dynamic_cast<CCLabelBMFont*>(label);
    if(labelBMFont != nullptr)
    {
        return labelBMFont->getFntFile();
    }
    else
    {
        return "";
    }
}


CCNode* CCControlButton::getBackgroundSpriteForState(CCControlState state)
{
    CCNode* pBackgroundSprite = (CCNode*)m_backgroundSpriteDispatchTable->objectForKey(state);
    if (pBackgroundSprite)
    {
        return pBackgroundSprite;
    }
    return (CCNode*)m_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}


void CCControlButton::setBackgroundSpriteForState(CCNode* pSprite, CCControlState state)
{
    CCSize oldPreferredSize = m_preferredSize;

    CCNode* pPreviousBackgroundSprite = (CCNode*)m_backgroundSpriteDispatchTable->objectForKey(state);
    if (pPreviousBackgroundSprite)
    {
        removeChild(pPreviousBackgroundSprite, true);
        m_backgroundSpriteDispatchTable->removeObjectForKey(state);
    }

    m_backgroundSpriteDispatchTable->setObject(pSprite, state);
    pSprite->setVisible(false);
    pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(pSprite);

    CCScale9Sprite* pScaleSprite = dynamic_cast<CCScale9Sprite*>(pSprite);

    if (pScaleSprite != nullptr && (this->m_preferredSize.width != 0 || this->m_preferredSize.height != 0))
    {

        if (oldPreferredSize.equals(m_preferredSize))
        {
            // Force update of preferred size
        	pScaleSprite->setPreferredSize(CCSizeMake(oldPreferredSize.width+1, oldPreferredSize.height+1));
        }
        
        pScaleSprite->setPreferredSize(this->m_preferredSize);
    }

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCControlButton::setBackgroundSpriteFrameForState(CCSpriteFrame * pSpriteFrame, CCControlState state,bool is9Patch/* = true*/)
{
	CCNode* pSprite;
	if(is9Patch)
	{
		pSprite = CCScale9Sprite::createWithSpriteFrame(pSpriteFrame);
	}
	else
	{
		pSprite= CCSprite::createWithSpriteFrame(pSpriteFrame);
	}
    this->setBackgroundSpriteForState(pSprite, state);
}


void CCControlButton::needsLayout()
{
    if (!m_bParentInited) {
        return;
    }
    // Hide the background and the label
    if (m_titleLabel != nullptr) {
        m_titleLabel->setVisible(false);
    }
    if (m_backgroundSprite) {
        m_backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->m_labelAnchorPoint);
    
    // Update the label to match with the current state
    CC_SAFE_RELEASE(m_currentTitle);
    m_currentTitle = getTitleForState(m_eState);
    CC_SAFE_RETAIN(m_currentTitle);

    m_currentTitleColor = getTitleColorForState(m_eState);

    this->setTitleLabel(getTitleLabelForState(m_eState));

    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(m_titleLabel);
    if (label && m_currentTitle)
    {
        label->setString(m_currentTitle->getCString());
    }

    CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(m_titleLabel);
    if (rgbaLabel)
    {
        rgbaLabel->setColor(m_currentTitleColor);
    }
    if (m_titleLabel != nullptr)
    {
        m_titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(m_eState));
    if (m_backgroundSprite != nullptr)
    {
        m_backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
   
    // Get the title label size
    CCSize titleLabelSize;
    if (m_titleLabel != nullptr)
    {
        titleLabelSize = m_titleLabel->boundingBox().size;
    }
    
    // Adjust the background image if necessary
    if (m_doesAdjustBackgroundImage)
    {
        // Add the margins
        if (m_backgroundSprite != nullptr)
        {
            m_backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + m_marginH * 2, titleLabelSize.height + m_marginV * 2));
        }
    } 
    else if(m_backgroundSprite != nullptr)
    {        
        //TODO: should this also have margins if one of the preferred sizes is relaxed?
        if (dynamic_cast<CCScale9Sprite*>(m_backgroundSprite))
        {
            CCSize preferredSize = ((CCScale9Sprite*)m_backgroundSprite)->getPreferredSize();
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
        else
        {
        	CCSize size = m_backgroundSprite->boundingBox().size;
        	m_backgroundSprite->setContentSize(size);
        }
    }
    
    // Set the content size
    CCRect rectTitle;
    if (m_titleLabel != nullptr)
    {
        rectTitle = m_titleLabel->boundingBox();
    }
    CCRect rectBackground;
    if (m_backgroundSprite != nullptr)
    {
        rectBackground = m_backgroundSprite->boundingBox();
    }

    CCRect maxRect = CCControlUtils::CCRectUnion(rectTitle, rectBackground);
    CCControl::setContentSize(maxRect.size);
    
    if (m_titleLabel != nullptr)
    {
        m_titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        m_titleLabel->setVisible(true);
    }
  
    if (m_backgroundSprite != nullptr)
    {
        m_backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        m_backgroundSprite->setVisible(true);   
    }   
}



bool CCControlButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    
    for (CCNode *c = this->m_pParent; c != nullptr; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    m_isPushed = true;
    this->setHighlighted(true);
    sendActionsForControlEvents(CCControlEventTouchDown);
    return true;
}

void CCControlButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{    
    if (!isEnabled() || !isPushed() || isSelected())
    {
        if (isHighlighted())
        {
            setHighlighted(false);
        }
        return;
    }
    
    bool isTouchMoveInside = isTouchInside(pTouch);
    if (isTouchMoveInside && !isHighlighted())
    {
        setHighlighted(true);
        sendActionsForControlEvents(CCControlEventTouchDragEnter);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragInside);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        setHighlighted(false);
        
        sendActionsForControlEvents(CCControlEventTouchDragExit);        
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(CCControlEventTouchDragOutside);        
    }
}
void CCControlButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_isPushed = false;
    setHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
        sendActionsForControlEvents(CCControlEventTouchUpInside);        
    }
    else
    {
        sendActionsForControlEvents(CCControlEventTouchUpOutside);        
    }
}

void CCControlButton::setOpacity(GLubyte opacity)
{
    // XXX fixed me if not correct
    CCControl::setOpacity(opacity);
//    m_cOpacity = opacity;
//    
//    CCObject* child;
//    CCArray* children=getChildren();
//    CCARRAY_FOREACH(children, child)
//    {
//        CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);        
//        if (pNode)
//        {
//            pNode->setOpacity(opacity);
//        }
//    }
    CCDictElement * item = nullptr;
    CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
    {
    	CCRGBAProtocol* pSprite = dynamic_cast<CCRGBAProtocol*>(item->getObject());
    	if(pSprite != nullptr)
    	{
    		pSprite->setOpacity(opacity);
    	}
    }
}

GLubyte CCControlButton::getOpacity()
{
    return _realOpacity;
}

void CCControlButton::setColor(const ccColor3B & color)
{
	CCControl::setColor(color);
	
	CCDictElement * item = nullptr;
    CCDICT_FOREACH(m_backgroundSpriteDispatchTable, item)
    {
    	CCRGBAProtocol* pSprite = dynamic_cast<CCRGBAProtocol*>(item->getObject());
    	if(pSprite != nullptr)
    	{
    		pSprite->setColor(color);
    	}
    }
}

const ccColor3B& CCControlButton::getColor()
{
	return _realColor;
}

void CCControlButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(CCControlEventTouchCancel);
}

CCControlButton* CCControlButton::create( bool is9Patch /*= true*/)
{
    CCControlButton *pControlButton = new CCControlButton();
    if (pControlButton && pControlButton->init(is9Patch))
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return nullptr;
}

NS_CC_EXT_END
