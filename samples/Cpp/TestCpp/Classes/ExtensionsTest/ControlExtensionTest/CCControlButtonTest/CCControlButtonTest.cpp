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
        Size screenSize = Director::sharedDirector()->getWinSize();
        
        // Defines an array of title to create buttons dynamically
        Array *stringArray = Array::create(
            ccs("Hello"),
            ccs("Variable"),
            ccs("Size"),
            ccs("!"),
            NULL);
        
        Node *layer = Node::create();
        addChild(layer, 1);
        
        double total_width = 0, height = 0;
        
        // For each title in the array
        Object* pObj = NULL;
        int i = 0;
        CCARRAY_FOREACH(stringArray, pObj)
        {
            String* title = (String*)pObj;
            // Creates a button with this string as title
            ControlButton *button = standardButtonWithTitle(title->getCString());
            if (i == 0)
            {
                button->setOpacity(50);
                button->setColor(ccc3(0, 255, 0));
            }
            else if (i == 1)
            {
                button->setOpacity(200);
                button->setColor(ccc3(0, 255, 0));
            }
            else if (i == 2)
            {
                button->setOpacity(100);
                button->setColor(ccc3(0, 0, 255));
            }
            
            button->setPosition(ccp (total_width + button->getContentSize().width / 2, button->getContentSize().height / 2));
            layer->addChild(button);
            
            // Compute the size of the layer
            height = button->getContentSize().height;
            total_width += button->getContentSize().width;
            i++;
        }

        layer->setAnchorPoint(ccp (0.5, 0.5));
        layer->setContentSize(CCSizeMake(total_width, height));
        layer->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        
        // Add the black background
        Scale9Sprite *background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(total_width + 14, height + 14));
        background->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(background);
        return true;
    }
    return false;
}

ControlButton *ControlButtonTest_HelloVariableSize::standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    Scale9Sprite *backgroundButton = Scale9Sprite::create("extensions/button.png");
    Scale9Sprite *backgroundHighlightedButton = Scale9Sprite::create("extensions/buttonHighlighted.png");
    
    LabelTTF *titleButton = LabelTTF::create(title, "Marker Felt", 30);

    titleButton->setColor(ccc3(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, ControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, ControlStateHighlighted);

    return button;
}

ControlButtonTest_Event::ControlButtonTest_Event()
: _displayValueLabel(NULL)
{

}

ControlButtonTest_Event::~ControlButtonTest_Event()
{
    CC_SAFE_RELEASE_NULL(_displayValueLabel);
}

bool ControlButtonTest_Event::init()
{
    if (ControlScene::init())
    {
        Size screenSize = Director::sharedDirector()->getWinSize();

        // Add a label in which the button events will be displayed
        setDisplayValueLabel(LabelTTF::create("No Event", "Marker Felt", 32));
        _displayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        _displayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(_displayValueLabel, 1);
        
        // Add the button
        Scale9Sprite *backgroundButton = Scale9Sprite::create("extensions/button.png");
        Scale9Sprite *backgroundHighlightedButton = Scale9Sprite::create("extensions/buttonHighlighted.png");
        
        LabelTTF *titleButton = LabelTTF::create("Touch Me!", "Marker Felt", 30);

        titleButton->setColor(ccc3(159, 168, 176));
        
        ControlButton *controlButton = ControlButton::create(titleButton, backgroundButton);
        controlButton->setBackgroundSpriteForState(backgroundHighlightedButton, ControlStateHighlighted);
        controlButton->setTitleColorForState(ccWHITE, ControlStateHighlighted);
        
        controlButton->setAnchorPoint(ccp(0.5f, 1));
        controlButton->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(controlButton, 1);

        // Add the black background
        Scale9Sprite *background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(300, 170));
        background->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(background);
        
        // Sets up event handlers
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDownAction), ControlEventTouchDown);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragInsideAction), ControlEventTouchDragInside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragOutsideAction), ControlEventTouchDragOutside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragEnterAction), ControlEventTouchDragEnter);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDragExitAction), ControlEventTouchDragExit);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchUpInsideAction), ControlEventTouchUpInside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchUpOutsideAction), ControlEventTouchUpOutside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchCancelAction), ControlEventTouchCancel);
        return true;
    }
    return false;
}

void ControlButtonTest_Event::touchDownAction(Object *senderz, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Down")->getCString());
}

void ControlButtonTest_Event::touchDragInsideAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Inside")->getCString());
}

void ControlButtonTest_Event::touchDragOutsideAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Outside")->getCString());
}

void ControlButtonTest_Event::touchDragEnterAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Enter")->getCString());
}

void ControlButtonTest_Event::touchDragExitAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Drag Exit")->getCString());
}

void ControlButtonTest_Event::touchUpInsideAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Up Inside.")->getCString());
}

void ControlButtonTest_Event::touchUpOutsideAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Up Outside.")->getCString());
}

void ControlButtonTest_Event::touchCancelAction(Object *sender, ControlEvent controlEvent)
{
    _displayValueLabel->setString(String::createWithFormat("Touch Cancel")->getCString());
}


//CCControlButtonTest_Styling

bool ControlButtonTest_Styling::init()
{
    if (ControlScene::init())
    {
        Size screenSize = Director::sharedDirector()->getWinSize();

        Node *layer = Node::create();
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
                button->setPosition(ccp (button->getContentSize().width / 2 + (button->getContentSize().width + space) * i,
                                       button->getContentSize().height / 2 + (button->getContentSize().height + space) * j));
                layer->addChild(button);
                
                max_w = MAX(button->getContentSize().width * (i + 1) + space  * i, max_w);
                max_h = MAX(button->getContentSize().height * (j + 1) + space * j, max_h);
            }
        }
        
        layer->setAnchorPoint(ccp (0.5, 0.5));
        layer->setContentSize(CCSizeMake(max_w, max_h));
        layer->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        
        // Add the black background
        Scale9Sprite *backgroundButton = Scale9Sprite::create("extensions/buttonBackground.png");
        backgroundButton->setContentSize(CCSizeMake(max_w + 14, max_h + 14));
        backgroundButton->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(backgroundButton);
        return true;
    }
    return false;
}


//CCControlButtonTest_Styling

ControlButton *ControlButtonTest_Styling::standardButtonWithTitle(const char *title)
{
    /** Creates and return a button with a default background and title color. */
    Scale9Sprite *backgroundButton = Scale9Sprite::create("extensions/button.png");
    backgroundButton->setPreferredSize(CCSizeMake(45, 45));  // Set the prefered size
    Scale9Sprite *backgroundHighlightedButton = Scale9Sprite::create("extensions/buttonHighlighted.png");
    backgroundHighlightedButton->setPreferredSize(CCSizeMake(45, 45));  // Set the prefered size
    
    LabelTTF *titleButton = LabelTTF::create(title, "Marker Felt", 30);

    titleButton->setColor(ccc3(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, ControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, ControlStateHighlighted);
    
    return button;
}

