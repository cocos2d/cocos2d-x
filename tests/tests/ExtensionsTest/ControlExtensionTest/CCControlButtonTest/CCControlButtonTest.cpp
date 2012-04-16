/*
 * CCControlButtonTest.m
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

#include "ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.h"

bool CCControlButtonTest_HelloVariableSize::init()
{
	if (CCControlScene::init())
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	    
		// Defines an array of title to create buttons dynamically
		CCArray *stringArray = CCArray::arrayWithObjects(
			ccs("Hello"),
			ccs("Variable"),
			ccs("Size"),
			ccs("!"),
			NULL);
	    
		CCNode *layer = CCNode::node();
		addChild(layer, 1);
	    
		double total_width = 0, height = 0;
	    
		// For each title in the array
		CCObject* pObj = NULL;
		CCARRAY_FOREACH(stringArray, pObj)
		{
			CCString* title = (CCString*)pObj;
			// Creates a button with this string as title
			CCControlButton *button = standardButtonWithTitle(title->getCString());
			button->setPosition(ccp (total_width + button->getContentSize().width / 2, button->getContentSize().height / 2));
			layer->addChild(button);
	        
			// Compute the size of the layer
			height = button->getContentSize().height;
			total_width += button->getContentSize().width;
		}

		layer->setAnchorPoint(ccp (0.5, 0.5));
		layer->setContentSize(CCSizeMake(total_width, height));
		layer->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
	    
		// Add the black background
		CCScale9Sprite *background = CCScale9Sprite::spriteWithFile("buttonBackground.png");
		background->setContentSize(CCSizeMake(total_width + 14, height + 14));
		background->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
		addChild(background);
		return true;
	}
	return false;
}

CCControlButton *CCControlButtonTest_HelloVariableSize::standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    CCScale9Sprite *backgroundButton = CCScale9Sprite::spriteWithFile("button.png");
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::spriteWithFile("buttonHighlighted.png");
    
    CCLabelTTF *titleButton = CCLabelTTF::labelWithString(title, "Marker Felt", 30);

    titleButton->setColor(ccc3(159, 168, 176));
    
    CCControlButton *button = CCControlButton::buttonWithLabelAndBackgroundSprite(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    
    return button;
}

CCControlButtonTest_Event::~CCControlButtonTest_Event()
{
    CC_SAFE_RELEASE_NULL(m_pDisplayValueLabel);
}

bool CCControlButtonTest_Event::init()
{
	if (CCControlScene::init())
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		// Add a label in which the button events will be displayed
		setDisplayValueLabel(CCLabelTTF::labelWithString("No Event", "Marker Felt", 32));
		m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
		m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
		addChild(m_pDisplayValueLabel, 1);
	    
		// Add the button
		CCScale9Sprite *backgroundButton = CCScale9Sprite::spriteWithFile("button.png");
		CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::spriteWithFile("buttonHighlighted.png");
	    
		CCLabelTTF *titleButton = CCLabelTTF::labelWithString("Touch Me!", "Marker Felt", 30);

		titleButton->setColor(ccc3(159, 168, 176));
	    
		CCControlButton *controlButton = CCControlButton::buttonWithLabelAndBackgroundSprite(titleButton, backgroundButton);
		controlButton->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
		controlButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
	    
		controlButton->setAnchorPoint(ccp(0.5f, 1));
		controlButton->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
		addChild(controlButton, 1);

		// Add the black background
		CCScale9Sprite *background = CCScale9Sprite::spriteWithFile("buttonBackground.png");
		background->setContentSize(CCSizeMake(300, 170));
		background->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
		addChild(background);
	    
		// Sets up event handlers
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchDownAction), CCControlEventTouchDown);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchDragInsideAction), CCControlEventTouchDragInside);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchDragOutsideAction), CCControlEventTouchDragOutside);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchDragEnterAction), CCControlEventTouchDragEnter);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchDragExitAction), CCControlEventTouchDragExit);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchUpInsideAction), CCControlEventTouchUpInside);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchUpOutsideAction), CCControlEventTouchUpOutside);
		controlButton->addTargetWithActionForControlEvent(this, menu_selector(CCControlButtonTest_Event::touchCancelAction), CCControlEventTouchCancel);
		return true;
	}
	return false;
}

void CCControlButtonTest_Event::touchDownAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Touch Down")->getCString());
}

void CCControlButtonTest_Event::touchDragInsideAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Drag Inside")->getCString());
}

void CCControlButtonTest_Event::touchDragOutsideAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Drag Outside")->getCString());
}

void CCControlButtonTest_Event::touchDragEnterAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Drag Enter")->getCString());
}

void CCControlButtonTest_Event::touchDragExitAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Drag Exit")->getCString());
}

void CCControlButtonTest_Event::touchUpInsideAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Touch Up Inside.")->getCString());
}

void CCControlButtonTest_Event::touchUpOutsideAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Touch Up Outside.")->getCString());
}

void CCControlButtonTest_Event::touchCancelAction(CCObject *sender)
{
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Touch Cancel")->getCString());
}


//CCControlButtonTest_Styling

bool CCControlButtonTest_Styling::init()
{
	if (CCControlScene::init())
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		CCNode *layer = CCNode::node();
		addChild(layer, 1);
	    
		int space = 10; // px
	    
		double max_w = 0, max_h = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Add the buttons
				CCControlButton *button = standardButtonWithTitle(CCString::stringWithFormat("%d",rand() % 30)->getCString());
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
		CCScale9Sprite *backgroundButton = CCScale9Sprite::spriteWithFile("buttonBackground.png");
		backgroundButton->setContentSize(CCSizeMake(max_w + 14, max_h + 14));
		backgroundButton->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
		addChild(backgroundButton);
		return true;
	}
	return false;
}


//CCControlButtonTest_Styling

CCControlButton *CCControlButtonTest_Styling::standardButtonWithTitle(const char *title)
{
    /** Creates and return a button with a default background and title color. */
    CCScale9Sprite *backgroundButton = CCScale9Sprite::spriteWithFile("button.png");
    backgroundButton->setPreferredSize(CCSizeMake(45, 45));  // Set the prefered size
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::spriteWithFile("buttonHighlighted.png");
    backgroundHighlightedButton->setPreferredSize(CCSizeMake(45, 45));  // Set the prefered size
    
    CCLabelTTF *titleButton = CCLabelTTF::labelWithString(title, "Marker Felt", 30);

    titleButton->setColor(ccc3(159, 168, 176));
    
    CCControlButton *button = CCControlButton::buttonWithLabelAndBackgroundSprite(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    
    return button;
}

