/*
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2012 Yannick Loriot
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

#include "CCControlPotentiometerTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

ControlPotentiometerTest::ControlPotentiometerTest()
: _displayValueLabel(nullptr)
{

}

ControlPotentiometerTest::~ControlPotentiometerTest()
{
    CC_SAFE_RELEASE(_displayValueLabel);
}

bool ControlPotentiometerTest::init()
{
    if (ControlScene::init())
    {
        auto screenSize = Director::getInstance()->getWinSize();
        
        auto layer = Node::create();
        layer->setPosition(screenSize.width / 2, screenSize.height / 2);
        this->addChild(layer, 1);
        
        double layer_width = 0;
        
        // Add the black background for the text
        auto background  = ui::Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(Size(80, 50));
        background->setPosition(layer_width + background->getContentSize().width / 2.0f, 0);
        layer->addChild(background);
        
        layer_width += background->getContentSize().width;
        
        this->setDisplayValueLabel(Label::createWithSystemFont("", "HelveticaNeue-Bold", 30));

        _displayValueLabel->setPosition(background->getPosition());
        layer->addChild(_displayValueLabel);
		
        // Add the slider
        ControlPotentiometer *potentiometer = ControlPotentiometer::create("extensions/potentiometerTrack.png"
                                                                                ,"extensions/potentiometerProgress.png"
                                                                                ,"extensions/potentiometerButton.png");
        potentiometer->setPosition(layer_width + 10 + potentiometer->getContentSize().width / 2, 0);

        // When the value of the slider will change, the given selector will be call
        potentiometer->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlPotentiometerTest::valueChanged), Control::EventType::VALUE_CHANGED);
        
		layer->addChild(potentiometer);
        
        layer_width += potentiometer->getContentSize().width;
        
        // Set the layer size
        layer->setContentSize(Size(layer_width, 0));
        layer->setAnchorPoint(Vec2(0.5f, 0.5f));
        
        // Update the value label
        this->valueChanged(potentiometer, Control::EventType::VALUE_CHANGED);
        return true;
	}
	return false;
}

void ControlPotentiometerTest::valueChanged(Ref *sender, Control::EventType controlEvent)
{
    ControlPotentiometer* pControl = (ControlPotentiometer*)sender;
	// Change value of label.
    _displayValueLabel->setString(StringUtils::format("%.02f", pControl->getValue()));
}

