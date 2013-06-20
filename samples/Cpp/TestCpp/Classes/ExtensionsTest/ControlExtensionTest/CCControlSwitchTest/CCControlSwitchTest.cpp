/*
 * ControlSwitchTest.m
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

ControlSwitchTest::~ControlSwitchTest()
{
    CC_SAFE_RELEASE(_displayValueLabel);
}

bool ControlSwitchTest::init()
{
    if (ControlScene::init())
    {
        Size screenSize = Director::sharedDirector()->getWinSize();
        
        Node *layer = Node::create();
        layer->setPosition(ccp (screenSize.width / 2, screenSize.height / 2));
        addChild(layer, 1);
        
        double layer_width = 0;
        
        // Add the black background for the text
        Scale9Sprite *background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(80, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);
        
        layer_width += background->getContentSize().width;
        
        _displayValueLabel  = LabelTTF::create("#color" ,"Marker Felt" ,30);
        _displayValueLabel->retain();

        _displayValueLabel->setPosition(background->getPosition());
        layer->addChild(_displayValueLabel);
        
        // Create the switch
        ControlSwitch *switchControl = ControlSwitch::create
            (
                Sprite::create("extensions/switch-mask.png"),
                Sprite::create("extensions/switch-on.png"),
                Sprite::create("extensions/switch-off.png"),
                Sprite::create("extensions/switch-thumb.png"),
                LabelTTF::create("On", "Arial-BoldMT", 16),
                LabelTTF::create("Off", "Arial-BoldMT", 16)
            );
        switchControl->setPosition(ccp (layer_width + 10 + switchControl->getContentSize().width / 2, 0));
        layer->addChild(switchControl);

        switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlSwitchTest::valueChanged), ControlEventValueChanged);
        
        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        
        // Update the value label
        valueChanged(switchControl, ControlEventValueChanged);
        return true;
    }
    return false;
}

void ControlSwitchTest::valueChanged(Object* sender, ControlEvent controlEvent)
{
    ControlSwitch* pSwitch = (ControlSwitch*)sender;
    if (pSwitch->isOn())
    {
        _displayValueLabel->setString("On");
    } 
    else
    {
        _displayValueLabel->setString("Off");
    }
}

