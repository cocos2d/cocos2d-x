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
#include "2d/CCLabel.h"
#include "2d/CCAction.h"
#include "2d/CCActionInterval.h"

using namespace std;

NS_CC_EXT_BEGIN

enum
{
    kZoomActionTag = 0xCCCB0001,
};

ControlButton::ControlButton()
: _isPushed(false)
, _parentInited(false)
, _doesAdjustBackgroundImage(false)
, _currentTitleColor(Color3B::WHITE)
, _titleLabel(nullptr)
, _backgroundSprite(nullptr)
, _zoomOnTouchDown(false)
, _marginV(ControlButtonMarginTB)
, _marginH(ControlButtonMarginLR)
{

}

ControlButton::~ControlButton()
{
    CC_SAFE_RELEASE(_titleLabel);
    CC_SAFE_RELEASE(_backgroundSprite);
}

//initialisers

bool ControlButton::init()
{
    return this->initWithLabelAndBackgroundSprite(Label::createWithSystemFont("", "Helvetica", 12), cocos2d::ui::Scale9Sprite::create());
}

bool ControlButton::initWithLabelAndBackgroundSprite(Node* node, ui::Scale9Sprite* backgroundSprite)
{
    if (Control::init())
    {
        CCASSERT(node != nullptr, "node must not be nil.");
        LabelProtocol* label = dynamic_cast<LabelProtocol*>(node);
        CCASSERT(backgroundSprite != nullptr, "Background sprite must not be nil.");
        CCASSERT(label != nullptr, "label must not be nil.");
        
        _parentInited = true;

        _isPushed = false;

        // Adjust the background image by default
        setAdjustBackgroundImage(true);
        setPreferredSize(Size::ZERO);
        // Zooming button by default
        _zoomOnTouchDown = true;
        _scaleRatio = 1.1f;
        
        // Set the default anchor point
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        
        // Set the nodes
        setTitleLabel(node);
        setBackgroundSprite(backgroundSprite);

        // Set the default color and opacity
        setColor(Color3B::WHITE);
        setOpacity(255.0f);
        setOpacityModifyRGB(true);
        
        // Initialize the dispatch table
        
        setTitleForState(label->getString(), Control::State::NORMAL);
        setTitleColorForState(node->getColor(), Control::State::NORMAL);
        setTitleLabelForState(node, Control::State::NORMAL);
        setBackgroundSpriteForState(backgroundSprite, Control::State::NORMAL);
        
        setLabelAnchorPoint(Vec2::ANCHOR_MIDDLE);

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

ControlButton* ControlButton::create(Node* label, cocos2d::ui::Scale9Sprite* backgroundSprite)
{
    ControlButton *pRet = new (std::nothrow) ControlButton();
    pRet->initWithLabelAndBackgroundSprite(label, backgroundSprite);
    pRet->autorelease();
    return pRet;
}

bool ControlButton::initWithTitleAndFontNameAndFontSize(const std::string& title, const std::string& fontName, float fontSize)
{
    return initWithLabelAndBackgroundSprite(Label::createWithSystemFont(title, fontName, fontSize), cocos2d::ui::Scale9Sprite::create());
}

ControlButton* ControlButton::create(const std::string& title, const std::string& fontName, float fontSize)
{
    ControlButton *pRet = new (std::nothrow) ControlButton();
    pRet->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
    pRet->autorelease();
    return pRet;
}

bool ControlButton::initWithBackgroundSprite(cocos2d::ui::Scale9Sprite* sprite)
{
    Label *label = Label::createWithSystemFont("", "Arial", 30);//
    return initWithLabelAndBackgroundSprite(label, sprite);
}

ControlButton* ControlButton::create(cocos2d::ui::Scale9Sprite* sprite)
{
    ControlButton *pRet = new (std::nothrow) ControlButton();
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
        _state = Control::State::HIGH_LIGHTED;
    }
    else
    {
        _state = Control::State::NORMAL;
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
        float scaleValue = (isHighlighted() && isEnabled() && !isSelected()) ? _scaleRatio : 1.0f;
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

void ControlButton::setPreferredSize(const Size& size)
{
    if(size.width == 0 && size.height == 0)
    {
        _doesAdjustBackgroundImage = true;
    }
    else
    {
        _doesAdjustBackgroundImage = false;
        
        for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
        {
            iter->second->setPreferredSize(size);
        }
    }

    _preferredSize = size;
    needsLayout();
}

const Size& ControlButton::getPreferredSize() const
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

const Vec2& ControlButton::getLabelAnchorPoint() const
{
    return this->_labelAnchorPoint;
}

void ControlButton::setLabelAnchorPoint(const Vec2& labelAnchorPoint)
{
    this->_labelAnchorPoint = labelAnchorPoint;
    if (_titleLabel != nullptr)
    {
        this->_titleLabel->setAnchorPoint(labelAnchorPoint);
    }
}

std::string ControlButton::getTitleForState(State state)
{
    auto iter = _titleDispatchTable.find((int)state);
    if (iter != _titleDispatchTable.end())
    {
        return iter->second;
    }
    
    iter = _titleDispatchTable.find((int)Control::State::NORMAL);
    
    return iter != _titleDispatchTable.end() ? iter->second : "";
}

void ControlButton::setTitleForState(const std::string& title, State state)
{
    _titleDispatchTable.erase((int)state);

    if (!title.empty())
    {
        _titleDispatchTable[(int)state] = title;
    }
    
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}


Color3B ControlButton::getTitleColorForState(State state) const
{
    Color3B returnColor = Color3B::WHITE;

    auto iter = _titleColorDispatchTable.find((int)state);
    if (iter != _titleColorDispatchTable.end())
    {
        returnColor = iter->second;
    }
    else
    {
        iter = _titleColorDispatchTable.find((int)Control::State::NORMAL);
        if (iter != _titleColorDispatchTable.end())
        {
            returnColor = iter->second;
        }
    }

    return returnColor;
}

void ControlButton::setTitleColorForState(const Color3B& color, State state)
{
    _titleColorDispatchTable.erase((int)state);
    _titleColorDispatchTable[(int)state] = color;
      
    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

Node* ControlButton::getTitleLabelForState(State state)
{
    Node* titleLabel = _titleLabelDispatchTable.at((int)state);
    if (titleLabel)
    {
        return titleLabel;
    }
    return _titleLabelDispatchTable.at((int)Control::State::NORMAL);
}

void ControlButton::setTitleLabelForState(Node* titleLabel, State state)
{
    Node* previousLabel = _titleLabelDispatchTable.at((int)state);
    if (previousLabel)
    {
        removeChild(previousLabel, true);
        _titleLabelDispatchTable.erase((int)state);
    }

    _titleLabelDispatchTable.insert((int)state, titleLabel);
    titleLabel->setVisible(false);
    titleLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(titleLabel, 1);

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void ControlButton::setTitleTTFForState(const std::string& fontName, State state)
{
    this->setTitleLabelForState(Label::createWithSystemFont(getTitleForState(state), fontName, 12), state);
}

const std::string& ControlButton::getTitleTTFForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    Label* labelTTF = dynamic_cast<Label*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getSystemFontName();
    }

    static std::string ret("");
    return ret;
}

void ControlButton::setTitleTTFSizeForState(float size, State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    if(label)
    {
        Label* labelTTF = dynamic_cast<Label*>(label);
        if(labelTTF != 0)
        {
            return labelTTF->setSystemFontSize(size);
        }
    }
}

float ControlButton::getTitleTTFSizeForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    Label* labelTTF = dynamic_cast<Label*>(label);
    if(labelTTF != 0)
    {
        return labelTTF->getSystemFontSize();
    }
    else
    {
        return 0;
    }
}

void ControlButton::setTitleBMFontForState(const std::string& fntFile, State state)
{
    std::string title = this->getTitleForState(state);
    this->setTitleLabelForState(Label::createWithBMFont(fntFile, title), state);
}

const std::string& ControlButton::getTitleBMFontForState(State state)
{
    LabelProtocol* label = dynamic_cast<LabelProtocol*>(this->getTitleLabelForState(state));
    auto labelBMFont = dynamic_cast<Label*>(label);
    if(labelBMFont != 0)
    {
        return labelBMFont->getBMFontFilePath();
    }

    static std::string ret("");
    return ret;
}


ui::Scale9Sprite* ControlButton::getBackgroundSpriteForState(State state)
{
    auto backgroundSprite = _backgroundSpriteDispatchTable.at((int)state);
    if (backgroundSprite)
    {
        return backgroundSprite;
    }
    return _backgroundSpriteDispatchTable.at((int)Control::State::NORMAL);
}


void ControlButton::setBackgroundSpriteForState(ui::Scale9Sprite* sprite, State state)
{
    Size oldPreferredSize = _preferredSize;

    auto previousBackgroundSprite = _backgroundSpriteDispatchTable.at((int)state);
    if (previousBackgroundSprite)
    {
        removeChild(previousBackgroundSprite, true);
        _backgroundSpriteDispatchTable.erase((int)state);
    }

    _backgroundSpriteDispatchTable.insert((int)state, sprite);
    sprite->setVisible(false);
    sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    addChild(sprite);

    if (this->_preferredSize.width != 0 || this->_preferredSize.height != 0)
    {
        if (oldPreferredSize.equals(_preferredSize))
        {
            // Force update of preferred size
            sprite->setPreferredSize(Size(oldPreferredSize.width+1, oldPreferredSize.height+1));
        }
        
        sprite->setPreferredSize(this->_preferredSize);
    }

    // If the current state if equal to the given state we update the layout
    if (getState() == state)
    {
        needsLayout();
    }
}

void ControlButton::setBackgroundSpriteFrameForState(SpriteFrame * spriteFrame, State state)
{
    ui::Scale9Sprite * sprite = ui::Scale9Sprite::createWithSpriteFrame(spriteFrame);
    this->setBackgroundSpriteForState(sprite, state);
}


void ControlButton::needsLayout()
{
    if (!_parentInited) {
        return;
    }
    // Hide the background and the label
    if (_titleLabel != nullptr) {
        _titleLabel->setVisible(false);
    }
    if (_backgroundSprite) {
        _backgroundSprite->setVisible(false);
    }
    // Update anchor of all labels
    this->setLabelAnchorPoint(this->_labelAnchorPoint);
    
    // Update the label to match with the current state
    _currentTitle = getTitleForState(_state);

    _currentTitleColor = getTitleColorForState(_state);

    this->setTitleLabel(getTitleLabelForState(_state));

    LabelProtocol* label = dynamic_cast<LabelProtocol*>(_titleLabel);
    if (label && !_currentTitle.empty())
    {
        label->setString(_currentTitle);
    }

    if (_titleLabel)
    {
        _titleLabel->setColor(_currentTitleColor);
    }
    if (_titleLabel != nullptr)
    {
        _titleLabel->setPosition(getContentSize().width / 2, getContentSize().height / 2);
    }
    
    // Update the background sprite
    this->setBackgroundSprite(this->getBackgroundSpriteForState(_state));
    if (_backgroundSprite != nullptr)
    {
        _backgroundSprite->setPosition(getContentSize().width / 2, getContentSize().height / 2);
    }
   
    // Get the title label size
    Size titleLabelSize;
    if (_titleLabel != nullptr)
    {
        titleLabelSize = _titleLabel->getBoundingBox().size;
    }
    
    // Adjust the background image if necessary
    if (_doesAdjustBackgroundImage)
    {
        // Add the margins
        if (_backgroundSprite != nullptr)
        {
            _backgroundSprite->setContentSize(Size(titleLabelSize.width + _marginH * 2, titleLabelSize.height + _marginV * 2));
        }
    } 
    else
    {        
        //TODO: should this also have margins if one of the preferred sizes is relaxed?
        if (_backgroundSprite != nullptr)
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
    if (_titleLabel != nullptr)
    {
        rectTitle = _titleLabel->getBoundingBox();
    }
    Rect rectBackground;
    if (_backgroundSprite != nullptr)
    {
        rectBackground = _backgroundSprite->getBoundingBox();
    }

    Rect maxRect = ControlUtils::RectUnion(rectTitle, rectBackground);
    setContentSize(Size(maxRect.size.width, maxRect.size.height));        
    
    if (_titleLabel != nullptr)
    {
        _titleLabel->setPosition(getContentSize().width/2, getContentSize().height/2);
        // Make visible the background and the label
        _titleLabel->setVisible(true);
    }
  
    if (_backgroundSprite != nullptr)
    {
        _backgroundSprite->setPosition(getContentSize().width/2, getContentSize().height/2);
        _backgroundSprite->setVisible(true);   
    }   
}



bool ControlButton::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible() || !hasVisibleParents() )
    {
        return false;
    }
    
    for (Node *c = this->_parent; c != nullptr; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    _isPushed = true;
    this->setHighlighted(true);
    sendActionsForControlEvents(Control::EventType::TOUCH_DOWN);
    return true;
}

void ControlButton::onTouchMoved(Touch *pTouch, Event *pEvent)
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
        sendActionsForControlEvents(Control::EventType::DRAG_ENTER);
    }
    else if (isTouchMoveInside && isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_INSIDE);
    }
    else if (!isTouchMoveInside && isHighlighted())
    {
        setHighlighted(false);
        
        sendActionsForControlEvents(Control::EventType::DRAG_EXIT);        
    }
    else if (!isTouchMoveInside && !isHighlighted())
    {
        sendActionsForControlEvents(Control::EventType::DRAG_OUTSIDE);        
    }
}
void ControlButton::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    
    
    if (isTouchInside(pTouch))
    {
        sendActionsForControlEvents(Control::EventType::TOUCH_UP_INSIDE);        
    }
    else
    {
        sendActionsForControlEvents(Control::EventType::TOUCH_UP_OUTSIDE);        
    }
}

void ControlButton::setOpacity(GLubyte opacity)
{
    Control::setOpacity(opacity);
    
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->setOpacity(opacity);
    }

    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->setOpacity(opacity);
    }
}

void ControlButton::updateDisplayedOpacity(GLubyte parentOpacity)
{
    Control::updateDisplayedOpacity(parentOpacity);

    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedOpacity(parentOpacity);
    }

    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedOpacity(parentOpacity);
    }
}

void ControlButton::setColor(const Color3B & color)
{
	Control::setColor(color);
	
    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->setColor(color);
    }

    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->setColor(color);
    }
}

void ControlButton::updateDisplayedColor(const Color3B& parentColor)
{
    Control::updateDisplayedColor(parentColor);

    for (auto iter = _backgroundSpriteDispatchTable.begin(); iter != _backgroundSpriteDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedColor(parentColor);
    }

    for (auto iter = _titleLabelDispatchTable.begin(); iter != _titleLabelDispatchTable.end(); ++iter)
    {
        iter->second->updateDisplayedColor(parentColor);
    }
}

void ControlButton::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    _isPushed = false;
    setHighlighted(false);
    sendActionsForControlEvents(Control::EventType::TOUCH_CANCEL);
}

ControlButton* ControlButton::create()
{
    ControlButton *pControlButton = new (std::nothrow) ControlButton();
    if (pControlButton && pControlButton->init())
    {
        pControlButton->autorelease();
        return pControlButton;
    }
    CC_SAFE_DELETE(pControlButton);
    return nullptr;
}

NS_CC_EXT_END
