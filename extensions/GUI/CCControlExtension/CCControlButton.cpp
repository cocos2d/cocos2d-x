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
: _currentTitle(NULL)
, _currentTitleColor(ccWHITE)
, _doesAdjustBackgroundImage(false)
, _titleLabel(NULL)
, _backgroundSprite(NULL)
, _zoomOnTouchDown(false)
, _isPushed(false)
, _parentInited(false)
, _titleDispatchTable(NULL)
, _titleColorDispatchTable(NULL)
, _titleLabelDispatchTable(NULL)
, _backgroundSpriteDispatchTable(NULL)
, _marginV(CCControlButtonMarginTB)
, _marginH(CCControlButtonMarginLR)
{

}

CCControlButton::~CCControlButton()
{
    CC_SAFE_RELEASE(_currentTitle);
    CC_SAFE_RELEASE(_titleLabel);
    CC_SAFE_RELEASE(_backgroundSpriteDispatchTable);
    CC_SAFE_RELEASE(_titleLabelDispatchTable);
    CC_SAFE_RELEASE(_titleColorDispatchTable);
    CC_SAFE_RELEASE(_titleDispatchTable);
    CC_SAFE_RELEASE(_backgroundSprite);
}

//initialisers

bool CCControlButton::init()
{
    return this->initWithLabelAndBackgroundSprite(CCLabelTTF::create("", "Helvetica", 12), CCScale9Sprite::create());
}

bool CCControlButton::initWithLabelAndBackgroundSprite(CCNode* node, CCScale9Sprite* backgroundSprite)
{
    if (CCControl::init())
    {
        CCAssert(node != NULL, "Label must not be nil.");
        CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(node);
        CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(node);
        CCAssert(backgroundSprite != NULL, "Background sprite must not be nil.");
        CCAssert(label != NULL || rgbaLabel!=NULL || backgroundSprite != NULL, "");
        
        _parentInited = true;

        // Initialize the button state tables
        this->setTitleDispatchTable(CCDictionary::create());
        this->setTitleColorDispatchTable(CCDictionary::create());
        this->setTitleLabelDispatchTable(CCDictionary::create());
        this->setBackgroundSpriteDispatchTable(CCDictionary::create());

        setTouchEnabled(true);
        _isPushed = false;
        _zoomOnTouchDown = true;

        _currentTitle=NULL;

        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(CCSizeZero);
        // Zooming button by default
        _zoomOnTouchDown = true;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp(0.5f, 0.5f));
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);

        // Set the default color and opacity
        setColor(ccc3(255.0f, 255.0f, 255.0f));
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        CCString* tempString = CCString::create(label->getString());
        //tempString->autorelease();
        setTitleForState(tempString, CCControlStateNormal);
        setTitleColorForState(rgbaLabel->getColor(), CCControlStateNormal);
        setTitleLabelForState(node, CCControlStateNormal);
        setBackgroundSpriteForState(backgroundSprite, CCControlStateNormal);
        
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

CCControlButton* CCControlButton::create(CCNode* label, CCScale9Sprite* backgroundSprite)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool CCControlButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    CCLabelTTF *label = CCLabelTTF::create(title.c_str(), fontName, fontSize);
    return initWithLabelAndBackgroundSprite(label, CCScale9Sprite::create());
}

CCControlButton* CCControlButton::create(string title, const char * fontName, float fontSize)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool CCControlButton::initWithBackgroundSprite(CCScale9Sprite* sprite)
{
    CCLabelTTF *label = CCLabelTTF::create("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

CCControlButton* CCControlButton::create(CCScale9Sprite* sprite)
{
    CCControlButton *pRet = new CCControlButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}


void CCControlButton::setMargins(int marginH, int marginV)
{
    _marginV = marginV;
    _marginH = marginH;
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
        _state = CCControlStateHighlighted;
    }
    else
    {
        _state = CCControlStateNormal;
    }
    
    CCControl::setHighlighted(enabled);

    CCAction *action = getActionByTag(kZoomActionTag);
    if (action)
    {
        stopAction(action);        
    }
    needsLayout();
    if( _zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
        CCAction *zoomAction = CCScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kZoomActionTag);
        runAction(zoomAction);
    }
}

void CCControlButton::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    _zoomOnTouchDown = zoomOnTouchDown;
}

bool CCControlButton::getZoomOnTouchDown()
{
    return _zoomOnTouchDown;
}

void CCControlButton::setPreferredSize(CCSize size)
{
    if(size.width == 0 && size.height == 0)
    {
        _doesAdjustBackgroundImage = true;
    }
    else
    {
        _doesAdjustBackgroundImage = false;
        CCDictElement * item = NULL;
        CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
        {
            CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
            sprite->setPreferredSize(size);
        }
    }

    _preferredSize = size;
    needsLayout();
}

CCSize CCControlButton::getPreferredSize()
{
    return _preferredSize;
}

void CCControlButton::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
    _doesAdjustBackgroundImage=adjustBackgroundImage;
    needsLayout();
}

bool CCControlButton::doesAdjustBackgroundImage()
{
    return _doesAdjustBackgroundImage;
}

CCPoint CCControlButton::getLabelAnchorPoint()
{
    return this->_labelAnchorPoint;
}

void CCControlButton::setLabelAnchorPoint(CCPoint labelAnchorPoint)
{
    this->_labelAnchorPoint = labelAnchorPoint;
    if (_titleLabel != NULL)
    {
        this->_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

CCString* CCControlButton::getTitleForState(CCControlState state)
{
    if (_titleDispatchTable != NULL)
    {
        CCString* title=(CCString*)_titleDispatchTable->objectForKey(state);    
        if (title)
        {
            return title;
        }
        return (CCString*)_titleDispatchTable->objectForKey(CCControlStateNormal);
    }
    return CCString::create("");
}

void CCControlButton::setTitleForState(CCString* title, CCControlState state)
{
    _titleDispatchTable->removeObjectForKey(state);

    if (title)
    {
        _titleDispatchTable->setObject(title, state);
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
        CC_BREAK_IF(NULL == _titleColorDispatchTable);
        CCColor3bObject* colorObject=(CCColor3bObject*)_titleColorDispatchTable->objectForKey(state);    
        if (colorObject)
        {
            returnColor = colorObject->value;
            break;
        }

        colorObject = (CCColor3bObject*)_titleColorDispatchTable->objectForKey(CCControlStateNormal);   
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
    _titleColorDispatchTable->removeObjectForKey(state); 
    CCColor3bObject* pColor3bObject = new CCColor3bObject(color);
    pColor3bObject->autorelease();
    _titleColorDispatchTable->setObject(pColor3bObject, state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

CCNode* CCControlButton::getTitleLabelForState(CCControlState state)
{
    CCNode* titleLabel = (CCNode*)_titleLabelDispatchTable->objectForKey(state);    
    if (titleLabel)
    {
        return titleLabel;
    }
    return (CCNode*)_titleLabelDispatchTable->objectForKey(CCControlStateNormal);
}

void CCControlButton::setTitleLabelForState(CCNode* titleLabel, CCControlState state)
{
    CCNode* previousLabel = (CCNode*)_titleLabelDispatchTable->objectForKey(state);
    if (previousLabel)
    {
        removeChild(previousLabel, true);
        _titleLabelDispatchTable->removeObjectForKey(state);        
    }

    _titleLabelDispatchTable->setObject(titleLabel, state);
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
    if(labelTTF != 0)
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
        if(labelTTF != 0)
        {
            return labelTTF->setFontSize(size);
        }
    }
}

float CCControlButton::getTitleTTFSizeForState(CCControlState state)
{
    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(this->getTitleLabelForState(state));
    CCLabelTTF* labelTTF = dynamic_cast<CCLabelTTF*>(label);
    if(labelTTF != 0)
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
    if(labelBMFont != 0)
    {
        return labelBMFont->getFntFile();
    }
    else
    {
        return "";
    }
}


CCScale9Sprite* CCControlButton::getBackgroundSpriteForState(CCControlState state)
{
    CCScale9Sprite* backgroundSprite = (CCScale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(state);    
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return (CCScale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(CCControlStateNormal);
}


void CCControlButton::setBackgroundSpriteForState(CCScale9Sprite* sprite, CCControlState state)
{
    CCSize oldPreferredSize = _preferredSize;

    CCScale9Sprite* previousBackgroundSprite = (CCScale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        _backgroundSpriteDispatchTable->removeObjectForKey(state);
    }

    _backgroundSpriteDispatchTable->setObject(sprite, state);
    sprite->setVisible(false);
    sprite->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(sprite);

    if (this->_preferredSize.width != 0 || this->_preferredSize.height != 0)
    {
        if (oldPreferredSize.equals(_preferredSize))
        {
            // Force update of preferred size
            sprite->setPreferredSize(CCSizeMake(oldPreferredSize.width+1, oldPreferredSize.height+1));
        }
        
        sprite->setPreferredSize(this->_preferredSize);
    }

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void CCControlButton::setBackgroundSpriteFrameForState(CCSpriteFrame * spriteFrame, CCControlState state)
{
    CCScale9Sprite * sprite = CCScale9Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void CCControlButton::needsLayout()
{
    if (!_parentInited) {
        return;
    }
    // Hide the background and the label
    if (_titleLabel != NULL) {
        _titleLabel->setVisible(false);
    }
    if (_backgroundSprite) {
        _backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->_labelAnchorPoint);
    
    // Update the label to match with the current state
    CC_SAFE_RELEASE(_currentTitle);
    _currentTitle = getTitleForState(_state);
    CC_SAFE_RETAIN(_currentTitle);

    _currentTitleColor = getTitleColorForState(_state);

    this->setTitleLabel(getTitleLabelForState(_state));

    CCLabelProtocol* label = dynamic_cast<CCLabelProtocol*>(_titleLabel);
    if (label && _currentTitle)
    {
        label->setString(_currentTitle->getCString());
    }

    CCRGBAProtocol* rgbaLabel = dynamic_cast<CCRGBAProtocol*>(_titleLabel);
    if (rgbaLabel)
    {
        rgbaLabel->setColor(_currentTitleColor);
    }
    if (_titleLabel != NULL)
    {
        _titleLabel->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(_state));
    if (_backgroundSprite != NULL)
    {
        _backgroundSprite->setPosition(ccp (getContentSize().width / 2, getContentSize().height / 2));
    }
   
    // Get the title label size
    CCSize titleLabelSize;
    if (_titleLabel != NULL)
    {
        titleLabelSize = _titleLabel->boundingBox().size;
    }
    
    // Adjust the background image if necessary
    if (_doesAdjustBackgroundImage)
    {
        // Add the margins
        if (_backgroundSprite != NULL)
        {
            _backgroundSprite->setContentSize(CCSizeMake(titleLabelSize.width + _marginH * 2, titleLabelSize.height + _marginV * 2));
        }
    } 
    else
    {        
        //TODO: should this also have margins if one of the preferred sizes is relaxed?
        if (_backgroundSprite != NULL)
        {
            CCSize preferredSize = _backgroundSprite->getPreferredSize();
            if (preferredSize.width <= 0)
            {
                preferredSize.width = titleLabelSize.width;
            }
            if (preferredSize.height <= 0)
            {
                preferredSize.height = titleLabelSize.height;
            }

            _backgroundSprite->setContentSize(preferredSize);
        }
    }
    
    // Set the content size
    CCRect rectTitle;
    if (_titleLabel != NULL)
    {
        rectTitle = _titleLabel->boundingBox();
    }
    CCRect rectBackground;
    if (_backgroundSprite != NULL)
    {
        rectBackground = _backgroundSprite->boundingBox();
    }

    CCRect maxRect = CCControlUtils::CCRectUnion(rectTitle, rectBackground);
    setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));        
    
    if (_titleLabel != NULL)
    {
        _titleLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        // Make visible the background and the label
        _titleLabel->setVisible(true);
    }
  
    if (_backgroundSprite != NULL)
    {
        _backgroundSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        _backgroundSprite->setVisible(true);   
    }   
}



bool CCControlButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    
    for (CCNode *c = this->_parent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    _isPushed = true;
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
    _isPushed = false;
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
//    _opacity = opacity;
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
    CCDictElement * item = NULL;
    CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
    {
        CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
        sprite->setOpacity(opacity);
    }
}

GLubyte CCControlButton::getOpacity()
{
    return _realOpacity;
}

void CCControlButton::setColor(const ccColor3B & color)
{
	CCControl::setColor(color);
	
	CCDictElement * item = NULL;
    CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
    {
        CCScale9Sprite* sprite = (CCScale9Sprite*)item->getObject();
        sprite->setColor(color);
    }
}

const ccColor3B& CCControlButton::getColor()
{
	return _realColor;
}

void CCControlButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(CCControlEventTouchCancel);
}

CCControlButton* CCControlButton::create()
{
    CCControlButton *pControlButton = new CCControlButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}

NS_CC_EXT_END
