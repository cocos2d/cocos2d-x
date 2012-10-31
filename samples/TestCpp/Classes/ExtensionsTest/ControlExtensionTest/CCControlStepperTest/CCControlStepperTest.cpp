/*
 * Copyright (c) 2012 cocos2d-x.org
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

#include "CCControlStepperTest.h"

CCControlStepperTest::CCControlStepperTest()
: m_pDisplayValueLabel(NULL)
{

}

CCControlStepperTest::~CCControlStepperTest()
{
    CC_SAFE_RELEASE(m_pDisplayValueLabel);
}

bool CCControlStepperTest::init()
{
    if (CCControlScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCNode *layer = CCNode::create();
        layer->setPosition(ccp (screenSize.width / 2, screenSize.height / 2));
        this->addChild(layer, 1);
        
        double layer_width          = 0;
        
        // Add the black background for the text
        CCScale9Sprite *background  = CCScale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(100, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);
        
        this->setDisplayValueLabel(CCLabelTTF::create("0", "HelveticaNeue-Bold", 30));

        m_pDisplayValueLabel->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel);
        
        layer_width                 += background->getContentSize().width;
        
        CCControlStepper *stepper   = this->makeControlStepper();
        stepper->setPosition(ccp (layer_width + 10 + stepper->getContentSize().width / 2, 0));
        stepper->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlStepperTest::valueChanged), CCControlEventValueChanged);
        layer->addChild(stepper);
        
        layer_width                 += stepper->getContentSize().width;
        
        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        
        // Update the value label
        this->valueChanged(stepper, CCControlEventValueChanged);
        return true;
    }
    return false;
}

CCControlStepper *CCControlStepperTest::makeControlStepper()
{
    CCSprite *minusSprite       = CCSprite::create("extensions/stepper-minus.png");
    CCSprite *plusSprite        = CCSprite::create("extensions/stepper-plus.png");
    
    return CCControlStepper::create(minusSprite, plusSprite);
}

void CCControlStepperTest::valueChanged(CCObject *sender, CCControlEvent controlEvent)
{
    CCControlStepper* pControl = (CCControlStepper*)sender;
    // Change value of label.
    m_pDisplayValueLabel->setString(CCString::createWithFormat("%0.02f", (float)pControl->getValue())->getCString());	
}

