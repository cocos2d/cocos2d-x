/*
 * ControlSliderTest.m
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

ControlSliderTest::ControlSliderTest()
{
 
}

ControlSliderTest::~ControlSliderTest()
{
    CC_SAFE_RELEASE_NULL(_displayValueLabel);
}

bool ControlSliderTest::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();

        // Add a label in which the slider value will be displayed
        _displayValueLabel = LabelTTF::create("Move the slider thumb!\nThe lower slider is restricted." ,"Marker Felt", 32);
        _displayValueLabel->retain();
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(screenSize.width / 1.7f, screenSize.height / 2.0f));
        addChild(_displayValueLabel);

        // Add the slider
        ControlSlider *slider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        slider->setAnchorPoint(Point(0.5f, 1.0f));
        slider->setMinimumValue(0.0f); // Sets the min value of range
        slider->setMaximumValue(5.0f); // Sets the max value of range
        slider->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f + 16));
		slider->setTag(1);

        // When the value of the slider will change, the given selector will be call
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlSliderTest::valueChanged), Control::EventType::VALUE_CHANGED);

		ControlSlider *restrictSlider = ControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
        restrictSlider->setAnchorPoint(Point(0.5f, 1.0f));
        restrictSlider->setMinimumValue(0.0f); // Sets the min value of range
        restrictSlider->setMaximumValue(5.0f); // Sets the max value of range
		restrictSlider->setMaximumAllowedValue(4.0f);
		restrictSlider->setMinimumAllowedValue(1.5f);
		restrictSlider->setValue(3.0f);
        restrictSlider->setPosition(Point(screenSize.width / 2.0f, screenSize.height / 2.0f - 24));
		restrictSlider->setTag(2);

	//same with restricted
		restrictSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlSliderTest::valueChanged), Control::EventType::VALUE_CHANGED);

        addChild(slider);    
		addChild(restrictSlider);
        return true;
    }
    return false;
}

void ControlSliderTest::valueChanged(Object *sender, Control::EventType controlEvent)
{
    ControlSlider* pSlider = (ControlSlider*)sender;
    // Change value of label.
	if(pSlider->getTag() == 1)
		_displayValueLabel->setString(String::createWithFormat("Upper slider value = %.02f", pSlider->getValue())->getCString());  
	if(pSlider->getTag() == 2)
		_displayValueLabel->setString(String::createWithFormat("Lower slider value = %.02f", pSlider->getValue())->getCString());  
}

