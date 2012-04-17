/*
 * CCControlSliderTest.m
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


#include "CCControlSliderTest.h"

CCControlSliderTest::CCControlSliderTest()
{
 
}

CCControlSliderTest::~CCControlSliderTest()
{
    CC_SAFE_RELEASE_NULL(m_pDisplayValueLabel);
}

bool CCControlSliderTest::init()
{
    if (CCControlScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

        // Add a label in which the slider value will be displayed
        m_pDisplayValueLabel = CCLabelTTF::labelWithString("Move the slider thumb!" ,"Marker Felt", 32);
        m_pDisplayValueLabel->retain();
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1.0f));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));
        addChild(m_pDisplayValueLabel);

        // Add the slider
        CCControlSlider *slider = CCControlSlider::sliderWithFiles("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        slider->setAnchorPoint(ccp(0.5f, 1.0f));
        slider->setMinimumValue(0.0f); // Sets the min value of range
        slider->setMaximumValue(5.0f); // Sets the max value of range
        slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f));

        // When the value of the slider will change, the given selector will be call
        slider->addTargetWithActionForControlEvents(this, menu_selector(CCControlSliderTest::valueChanged), CCControlEventValueChanged);

        addChild(slider);	
        return true;
    }
    return false;
}

void CCControlSliderTest::valueChanged(CCObject *sender)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
	// Change value of label.
    m_pDisplayValueLabel->setString(CCString::stringWithFormat("Slider value = %.02f", pSlider->getValue())->getCString());	
}

