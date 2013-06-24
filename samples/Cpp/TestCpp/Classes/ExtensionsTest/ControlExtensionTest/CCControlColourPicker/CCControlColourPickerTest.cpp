/*
 * ControlColourPickerTest.m
 *
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

#include "CCControlColourPickerTest.h"

USING_NS_CC_EXT;

ControlColourPickerTest::ControlColourPickerTest()
{

}

bool ControlColourPickerTest::init()
{
    if (ControlScene::init())
    {
        Size screenSize = Director::sharedDirector()->getWinSize();

        Node *layer  = Node::create();
        layer->setPosition(ccp (screenSize.width / 2, screenSize.height / 2));
        addChild(layer, 1);

        double layer_width = 0;

        // Create the colour picker
        ControlColourPicker *colourPicker = ControlColourPicker::create();
        colourPicker->setColor(ccc3(37, 46, 252));
        colourPicker->setPosition(ccp (colourPicker->getContentSize().width / 2, 0));

        // Add it to the layer
        layer->addChild(colourPicker);

        // Add the target-action pair
        colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlColourPickerTest::colourValueChanged), ControlEventValueChanged);


        layer_width += colourPicker->getContentSize().width;

        // Add the black background for the text
        Scale9Sprite *background = Scale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(150, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);

        layer_width += background->getContentSize().width;

        _colorLabel = LabelTTF::create("#color", "Marker Felt", 30);
        _colorLabel->retain();

        _colorLabel->setPosition(background->getPosition());
        layer->addChild(_colorLabel);

        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));

        // Update the color text
        colourValueChanged(colourPicker, ControlEventValueChanged);
        return true;
    }
    return false;

}

ControlColourPickerTest::~ControlColourPickerTest()
{
    CC_SAFE_RELEASE(_colorLabel);
}

void ControlColourPickerTest::colourValueChanged(Object *sender, ControlEvent controlEvent)
{
    ControlColourPicker* pPicker = (ControlColourPicker*)sender;
    _colorLabel->setString(String::createWithFormat("#%02X%02X%02X",pPicker->getColor().r, pPicker->getColor().g, pPicker->getColor().b)->getCString());
}


