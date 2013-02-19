/*
 * CCControlSwitchTest.m
 *
 * Copyright (c) 2012 Yannick Loriot
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

#include "CCControlSwitchTest.h"

CCControlSwitchTest::~CCControlSwitchTest()
{
    CC_SAFE_RELEASE(m_pDisplayValueLabel);
}

bool CCControlSwitchTest::init()
{
    if (CCControlScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCNode *layer = CCNode::create();
        layer->setPosition(ccp (screenSize.width / 2, screenSize.height / 2));
        addChild(layer, 1);
        
        double layer_width = 0;
        
        // Add the black background for the text
        CCScale9Sprite *background = CCScale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(80, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);
        
        layer_width += background->getContentSize().width;
        
        m_pDisplayValueLabel  = CCLabelTTF::create("#color" ,"Marker Felt" ,30);
        m_pDisplayValueLabel->retain();

        m_pDisplayValueLabel->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel);
        
        // Create the switch
        CCControlSwitch *switchControl = CCControlSwitch::create
            (
                CCSprite::create("extensions/switch-mask.png"),
                CCSprite::create("extensions/switch-on.png"),
                CCSprite::create("extensions/switch-off.png"),
                CCSprite::create("extensions/switch-thumb.png"),
                CCLabelTTF::create("On", "Arial-BoldMT", 16),
                CCLabelTTF::create("Off", "Arial-BoldMT", 16)
            );
        switchControl->setPosition(ccp (layer_width + 10 + switchControl->getContentSize().width / 2, 0));
        layer->addChild(switchControl);

        switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlSwitchTest::valueChanged), CCControlEventValueChanged);
        
        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        
        // Update the value label
        valueChanged(switchControl, CCControlEventValueChanged);
        return true;
    }
    return false;
}

void CCControlSwitchTest::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel->setString("On");
    } 
    else
    {
        m_pDisplayValueLabel->setString("Off");
    }
}

