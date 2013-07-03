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

ControlButton::ControlButton()
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
, _marginV(ControlButtonMarginTB)
, _marginH(ControlButtonMarginLR)
{

}

ControlButton::~ControlButton()
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

bool ControlButton::init()
{
    return this->initWithLabelAndBackgroundSprite(LabelTTF::create("", "Helvetica", 12), Scale9Sprite::create());
}

bool ControlButton::initWithLabelAndBackgroundSprite(Node* node, Scale9Sprite* backgroundSprite)
{
    if (Control::init())
    {
        CCAssert(node != NULL, "Label must not be nil.");
        LabelProtocol* label = dynamic_cast<LabelProtocol*>(node);
        RGBAProtocol* rgbaLabel = dynamic_cast<RGBAProtocol*>(node);
        CCAssert(backgroundSprite != NULL, "Background sprite must not be nil.");
        CCAssert(label != NULL || rgbaLabel!=NULL || backgroundSprite != NULL, "");
        
        _parentInited = true;

        // Initialize the button state tables
        this->setTitleDispatchTable(Dictionary::create());
        this->setTitleColorDispatchTable(Dictionary::create());
        this->setTitleLabelDispatchTable(Dictionary::create());
        this->setBackgroundSpriteDispatchTable(Dictionary::create());

        setTouchEnabled(true);
        _isPushed = false;
        _zoomOnTouchDown = true;

        _currentTitle=NULL;

        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(SizeZero);
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
        
        String* tempString = String::create(label->getString());
        //tempString->autorelease();
        setTitleForState(tempString, ControlStateNormal);
        setTitleColorForState(rgbaLabel->getColor(), ControlStateNormal);
        setTitleLabelForState(node, ControlStateNormal);
        setBackgroundSpriteForState(backgroundSprite, ControlStateNormal);
        
        setLabelAnchorPoint(ccp(0.5f, 0.5f));

        // Layout update
        needsLayout();

        return true;
    }
    //couldn't init the Control
    else
    {
        return false;
    }
}

ControlButton* ControlButton::create(Node* label, Scale9Sprite* backgroundSprite)
{
    ControlButton *pRet = new ControlButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool ControlButton::initWithTitleAndFontNameAndFontSize(string title, const char * fontName, float fontSize)
{
    LabelTTF *label = LabelTTF::create(title.c_str(), fontName, fontSize);
    return initWithLabelAndBackgroundSprite(label, Scale9Sprite::create());
}

ControlButton* ControlButton::create(string title, const char * fontName, float fontSize)
{
    ControlButton *pRet = new ControlButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool ControlButton::initWithBackgroundSprite(Scale9Sprite* sprite)
{
    LabelTTF *label = LabelTTF::create("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

ControlButton* ControlButton::create(Scale9Sprite* sprite)
{
    ControlButton *pRet = new ControlButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}


void ControlButton::setMargins(int marginH, int marginV)
{
    _marginV = marginV;
    _marginH = marginH;
    needsLayout();
}

void ControlButton::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    needsLayout();
}

void ControlButton::setSelected(bool enabled)
{
    Control::setSelected(enabled);
    needsLayout();
}

void ControlButton::setHighlighted(bool enabled)
{
    if (enabled == true)
    {
        _state = ControlStateHighlighted;
    }
    else
    {
        _state = ControlStateNormal;
    }
    
    Control::setHighlighted(enabled);

    Action *action = getActionByTag(kZoomActionTag);
    if (action)
    {
        stopAction(action);        
    }
    needsLayout();
    if( _zoomOnTouchDown )
    {
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? 1.1f : 1.0f;
        Action *zoomAction = ScaleTo::create(0.05f, scaleValue);
        zoomAction->setTag(kZoomActionTag);
        runAction(zoomAction);
    }
}

void ControlButton::setZoomOnTouchDown(bool zoomOnTouchDown)
{
    _zoomOnTouchDown = zoomOnTouchDown;
}

bool ControlButton::getZoomOnTouchDown()
{
    return _zoomOnTouchDown;
}

void ControlButton::setPreferredSize(Size size)
{
    if(size.width == 0 && size.height == 0)
    {
        _doesAdjustBackgroundImage = true;
    }
    else
    {
        _doesAdjustBackgroundImage = false;
        DictElement * item = NULL;
        CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
        {
            Scale9Sprite* sprite = (Scale9Sprite*)item->getObject();
            sprite->setPreferredSize(size);
        }
    }

    _preferredSize = size;
    needsLayout();
}

Size ControlButton::getPreferredSize()
{
    return _preferredSize;
}

void ControlButton::setAdjustBackgroundImage(bool adjustBackgroundImage)
{
    _doesAdjustBackgroundImage=adjustBackgroundImage;
    needsLayout();
}

bool ControlButton::doesAdjustBackgroundImage()
{
    return _doesAdjustBackgroundImage;
}

Point ControlButton::getLabelAnchorPoint()
{
    return this->_labelAnchorPoint;
}

void ControlButton::setLabelAnchorPoint(Point labelAnchorPoint)
{
    this->_labelAnchorPoint = labelAnchorPoint;
    if (_titleLabel != NULL)
    {
        this->_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

String* ControlButton::getTitleForState(ControlState state)
{
    if (_titleDispatchTable != NULL)
    {
        String* title=(String*)_titleDispatchTable->objectForKey(state);    
        if (title)
        {
            return title;
        }
        return (String*)_titleDispatchTable->objectForKey(ControlStateNormal);
    }
    return String::create("");
}

void ControlButton::setTitleForState(String* title, ControlState state)
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


const ccColor3B ControlButton::getTitleColorForState(ControlState state)
{
    ccColor3B returnColor = ccWHITE;
    do 
    {
        CC_BREAK_IF(NULL == _titleColorDispatchTable);
        Color3bObject* colorObject=(Color3bObject*)_titleColorDispatchTable->objectForKey(state);    
        if (colorObject)
        {
            returnColor = colorObject->value;
            break;
        }

        colorObject = (Color3bObject*)_titleColorDispatchTable->objectForKey(ControlStateNormal);   
        if (colorObject)
        {
            returnColor = colorObject->value;
        }
    } while (0);

    return returnColor;
}

void ControlButton::setTitleColorForState(ccColor3B color, ControlState state)
{
    //ccColor3B* colorValue=&color;
    _titleColorDispatchTable->removeObjectForKey(state); 
    Color3bObject* pColor3bObject = new Color3bObject(color);
    pColor3bObject->autorelease();
    _titleColorDispatchTable->setObject(pColor3bObject, state);
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

Node* ControlButton::getTitleLabelForState(ControlState state)
{
    Node* titleLabel = (Node*)_titleLabelDispatchTable->objectForKey(state);    
    if (titleLabel)
    {
        return titleLabel;
    }
    return (Node*)_titleLabelDispatchTable->objectForKey(ControlStateNormal);
}

void ControlButton::setTitleLabelForState(Node* titleLabel, ControlState state)
{
    Node* previousLabel = (Node*)_titleLabelDispatchTable->objectForKey(state);
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

void ControlButton::setTitleTTFForState(const char * fntFile, ControlState state)
{
    String * title = this->getTitleForState(state);
    if (!title)
    {
        title = String::create("");
    }
    this->setTitleLabelForState(LabelTTF::create(title->getCString(), fntFile, 12), state);
}

const char * ControlButton::getTitleTTFForState(ControlState state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    LabelTTF* labelTTF = dynamic_cast<LabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontName();
    }
    else
    {
        return "";
    }
}

void ControlButton::setTitleTTFSizeForState(float size, ControlState state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        LabelTTF* labelTTF = dynamic_cast<LabelTTF*>(label);
        if(labelTTF != 0)
        {
            return labelTTF->setFontSize(size);
        }
    }
}

float ControlButton::getTitleTTFSizeForState(ControlState state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    LabelTTF* labelTTF = dynamic_cast<LabelTTF*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getFontSize();
    }
    else
    {
        return 0;
    }
}

void ControlButton::setTitleBMFontForState(const char * fntFile, ControlState state)
{
    String * title = this->getTitleForState(state);
    if (!title)
    {
        title = String::create("");
    }
    this->setTitleLabelForState(LabelBMFont::create(title->getCString(), fntFile), state);
}

const char * ControlButton::getTitleBMFontForState(ControlState state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    LabelBMFont* labelBMFont = dynamic_cast<LabelBMFont*>(label);
    if(labelBMFont != 0)
    {
        return labelBMFont->getFntFile();
    }
    else
    {
        return "";
    }
}


Scale9Sprite* ControlButton::getBackgroundSpriteForState(ControlState state)
{
    Scale9Sprite* backgroundSprite = (Scale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(state);    
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return (Scale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(ControlStateNormal);
}


void ControlButton::setBackgroundSpriteForState(Scale9Sprite* sprite, ControlState state)
{
    Size oldPreferredSize = _preferredSize;

    Scale9Sprite* previousBackgroundSprite = (Scale9Sprite*)_backgroundSpriteDispatchTable->objectForKey(state);
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

void ControlButton::setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, ControlState state)
{
    Scale9Sprite * sprite = Scale9Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void ControlButton::needsLayout()
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

    LabelProtocol* label = dynamic_cast<LabelProtocol*>(_titleLabel);
    if (label && _currentTitle)
    {
        label->setString(_currentTitle->getCString());
    }

    RGBAProtocol* rgbaLabel = dynamic_cast<RGBAProtocol*>(_titleLabel);
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
    Size titleLabelSize;
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
            Size preferredSize = _backgroundSprite->getPreferredSize();
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
    Rect rectTitle;
    if (_titleLabel != NULL)
    {
        rectTitle = _titleLabel->boundingBox();
    }
    Rect rectBackground;
    if (_backgroundSprite != NULL)
    {
        rectBackground = _backgroundSprite->boundingBox();
    }

    Rect maxRect = ControlUtils::RectUnion(rectTitle, rectBackground);
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



bool ControlButton::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    
    for (Node *c = this->_parent; c != NULL; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    _isPushed = true;
    this->setHighlighted(true);
    sendActionsForControlEvents(ControlEventTouchDown);
    return true;
}

void ControlButton::ccTouchMoved(Touch *pTouch, Event *pEvent)
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
        sendActionsForControlEvents(ControlEventTouchDragEnter);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(ControlEventTouchDragInside);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        setHighlighted(false);
        
        sendActionsForControlEvents(ControlEventTouchDragExit);        
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(ControlEventTouchDragOutside);        
    }
}
void ControlButton::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
        sendActionsForControlEvents(ControlEventTouchUpInside);        
    }
    else
    {
        sendActionsForControlEvents(ControlEventTouchUpOutside);        
    }
}

void ControlButton::setOpacity(GLubyte opacity)
{
    // XXX fixed me if not correct
    Control::setOpacity(opacity);
//    _opacity = opacity;
//    
//    Object* child;
//    Array* children=getChildren();
//    CCARRAY_FOREACH(children, child)
//    {
//        RGBAProtocol* pNode = dynamic_cast<RGBAProtocol*>(child);        
//        if (pNode)
//        {
//            pNode->setOpacity(opacity);
//        }
//    }
    DictElement * item = NULL;
    CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
    {
        Scale9Sprite* sprite = (Scale9Sprite*)item->getObject();
        sprite->setOpacity(opacity);
    }
}

GLubyte ControlButton::getOpacity()
{
    return _realOpacity;
}

void ControlButton::setColor(const ccColor3B & color)
{
	Control::setColor(color);
	
	DictElement * item = NULL;
    CCDICT_FOREACH(_backgroundSpriteDispatchTable, item)
    {
        Scale9Sprite* sprite = (Scale9Sprite*)item->getObject();
        sprite->setColor(color);
    }
}

const ccColor3B& ControlButton::getColor()
{
	return _realColor;
}

void ControlButton::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(ControlEventTouchCancel);
}

ControlButton* ControlButton::create()
{
    ControlButton *pControlButton = new ControlButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return NULL;
}

NS_CC_EXT_END
