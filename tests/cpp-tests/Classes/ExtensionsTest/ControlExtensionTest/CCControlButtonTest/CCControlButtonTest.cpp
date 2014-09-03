/*
 * ControlButtonTest.m
 *
 * Copyright (c) 2011 Yannick Loriot
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

#include "CCControlButtonTest.h"

bool ControlButtonTest_HelloVariableSize::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();
        
        // Defines an array of title to create buttons dynamically
        std::vector<std::string> vec;
        vec.push_back("Hello");
        vec.push_back("Variable");
        vec.push_back("Size");
        vec.push_back("!");
        
        auto layer = Node::create();
        addChild(layer, 1);
        
        double total_width = 0, height = 0;
        
        int i = 0;
        
        for (auto& title : vec)
        {
            // Creates a button with this string as title
            ControlButton *button = standardButtonWithTitle(title.c_str());
            if (i == 0)
            {
                button->setOpacity(50);
                button->setColor(Color3B(0, 255, 0));
            }
            else if (i == 1)
            {
                button->setOpacity(200);
                button->setColor(Color3B(0, 255, 0));
            }
            else if (i == 2)
            {
                button->setOpacity(100);
                button->setColor(Color3B(0, 0, 255));
            }
            
            button->setPosition(total_width + button->getContentSize().width / 2, button->getContentSize().height / 2);
            layer->addChild(button);
            
            // Compute the size of the layer
            height = button->getContentSize().height;
            total_width += button->getContentSize().width;
            i++;
        }

        layer->setAnchorPoint(Vec2 (0.5, 0.5));
        layer->setContentSize(Size(total_width, height));
        layer->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        
        // Add the black background
        auto background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(Size(total_width + 14, height + 14));
        background->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        addChild(background);
        return true;
    }
    return false;
}

ControlButton *ControlButtonTest_HelloVariableSize::standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    auto backgroundButton = cocos2d::extension::Scale9Sprite::create("extensions/button.png");
    auto backgroundHighlightedButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonHighlighted.png");
    
    auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);

    titleButton->setColor(Color3B(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    button->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);

    return button;
}

ControlButtonTest_Event::ControlButtonTest_Event()
: _displayValueLabel(nullptr)
, _displayBitmaskLabel(nullptr)
{

}

ControlButtonTest_Event::~ControlButtonTest_Event()
{
    CC_SAFE_RELEASE_NULL(_displayValueLabel);
    CC_SAFE_RELEASE_NULL(_displayBitmaskLabel);
}

bool ControlButtonTest_Event::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();

        // Add a label in which the button events will be displayed
        setDisplayValueLabel(Label::createWithTTF("No Event", "fonts/Marker Felt.ttf", 32));
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        addChild(_displayValueLabel, 1);

        setDisplayBitmaskLabel(Label::createWithTTF("No bitmask event", "fonts/Marker Felt.ttf", 24));
        _displayBitmaskLabel->setAnchorPoint(Vec2(0.5f, -1));
        Vec2 bitmaskLabelPos = _displayValueLabel->getPosition() - Vec2(0, _displayBitmaskLabel->getBoundingBox().size.height);
        _displayBitmaskLabel->setPosition(bitmaskLabelPos);
        addChild(_displayBitmaskLabel, 1);

        // Add the button
        auto backgroundButton = Scale9Sprite::create("extensions/button.png");
        auto backgroundHighlightedButton = Scale9Sprite::create("extensions/buttonHighlighted.png");
        
        auto titleButton = Label::createWithTTF("Touch Me!", "fonts/Marker Felt.ttf", 30);

        titleButton->setColor(Color3B(159, 168, 176));
        
        ControlButton *controlButton = ControlButton::create(titleButton, backgroundButton);
        controlButton->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
        controlButton->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);
        
        controlButton->setAnchorPoint(Vec2(0.5f, 1));
        controlButton->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        addChild(controlButton, 1);

        // Add the black background
        auto background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(Size(300, 170));
        background->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        addChild(background);
        
        // Sets up event handlers
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDownAction), Control::EventType::TOUCH_DOWN);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragInsideAction), Control::EventType::DRAG_INSIDE);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragOutsideAction), Control::EventType::DRAG_OUTSIDE);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragEnterAction), Control::EventType::DRAG_ENTER);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragExitAction), Control::EventType::DRAG_EXIT);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchUpInsideAction), Control::EventType::TOUCH_UP_INSIDE);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchUpOutsideAction), Control::EventType::TOUCH_UP_OUTSIDE);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchCancelAction), Control::EventType::TOUCH_CANCEL);
        // test for issue 2882
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchBitmaskAction),
            Control::EventType::TOUCH_DOWN | Control::EventType::DRAG_INSIDE | Control::EventType::DRAG_OUTSIDE | Control::EventType::DRAG_ENTER | Control::EventType::DRAG_EXIT | Control::EventType::TOUCH_UP_INSIDE | Control::EventType::TOUCH_UP_OUTSIDE | Control::EventType::TOUCH_CANCEL | Control::EventType::VALUE_CHANGED);

        return true;
    }
    return false;
}

void ControlButtonTest_Event::touchBitmaskAction(Ref *senderz, Control::EventType controlEvent)
{
    _displayBitmaskLabel->setString(String::createWithFormat("using bitmask (%d)", controlEvent)->getCString());
}

void ControlButtonTest_Event::touchDownAction(Ref *senderz, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
}

void ControlButtonTest_Event::touchDragInsideAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Inside")->getCString());
}

void ControlButtonTest_Event::touchDragOutsideAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Outside")->getCString());
}

void ControlButtonTest_Event::touchDragEnterAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Enter")->getCString());
}

void ControlButtonTest_Event::touchDragExitAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Exit")->getCString());
}

void ControlButtonTest_Event::touchUpInsideAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Up Inside.")->getCString());
}

void ControlButtonTest_Event::touchUpOutsideAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Up Outside.")->getCString());
}

void ControlButtonTest_Event::touchCancelAction(Ref *sender, Control::EventType controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Cancel")->getCString());
}


//CCControlButtonTest_Styling

bool ControlButtonTest_Styling::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();

        auto layer = Node::create();
        addChild(layer, 1);
        
        int space = 10; // px
        
        double max_w = 0, max_h = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Add the buttons
                ControlButton *button = standardButtonWithTitle(String::createWithFormat("%d",rand() % 30)->getCString());
                button->setAdjustBackgroundImage(false);  // Tells the button that the background image must not be adjust
                                                    // It'll use the prefered size of the background image
                button->setPosition(button->getContentSize().width / 2 + (button->getContentSize().width + space) * i,
                                       button->getContentSize().height / 2 + (button->getContentSize().height + space) * j);
                layer->addChild(button);
                
                max_w = MAX(button->getContentSize().width * (i + 1) + space  * i, max_w);
                max_h = MAX(button->getContentSize().height * (j + 1) + space * j, max_h);
            }
        }
        
        layer->setAnchorPoint(Vec2(0.5, 0.5));
        layer->setContentSize(Size(max_w, max_h));
        layer->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        
        // Add the black background
        auto backgroundButton = cocos2d::extension::Scale9Sprite::create("extensions/buttonBackground.png");
        backgroundButton->setContentSize(Size(max_w + 14, max_h + 14));
        backgroundButton->setPosition(screenSize.width / 2.0f, screenSize.height / 2.0f);
        addChild(backgroundButton);
        return true;
    }
    return false;
}


//CCControlButtonTest_Styling

ControlButton *ControlButtonTest_Styling::standardButtonWithTitle(const char *title)
{
    /** Creates and return a button with a default background and title color. */
    auto backgroundButton = Scale9Sprite::create("extensions/button.png");
    backgroundButton->setPreferredSize(Size(45, 45));  // Set the prefered size
    auto backgroundHighlightedButton = Scale9Sprite::create("extensions/buttonHighlighted.png");
    backgroundHighlightedButton->setPreferredSize(Size(45, 45));  // Set the prefered size
    
    auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);

    titleButton->setColor(Color3B(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    button->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);
    
    return button;
}

