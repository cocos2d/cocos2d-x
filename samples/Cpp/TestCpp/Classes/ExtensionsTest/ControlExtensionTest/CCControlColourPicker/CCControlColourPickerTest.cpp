/*
 * CCControlColourPickerTest.m
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

CCControlColourPickerTest::CCControlColourPickerTest()
{

}

bool CCControlColourPickerTest::init()
{
    if (CCControlScene::init())
    {
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

        CCNode *layer  = CCNode::create();
        layer->setPosition(ccp (screenSize.width / 2, screenSize.height / 2));
        addChild(layer, 1);

        double layer_width = 0;

        // Create the colour picker
        CCControlColourPicker *colourPicker = CCControlColourPicker::create();
        colourPicker->setColor(ccc3(37, 46, 252));
        colourPicker->setPosition(ccp (colourPicker->getContentSize().width / 2, 0));

        // Add it to the layer
        layer->addChild(colourPicker);

        // Add the target-action pair
        colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlColourPickerTest::colourValueChanged), CCControlEventValueChanged);


        layer_width += colourPicker->getContentSize().width;

        // Add the black background for the text
        CCScale9Sprite *background = CCScale9Sprite::create("extensions/buttonBackground.png");
        background->setContentSize(CCSizeMake(150, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);

        layer_width += background->getContentSize().width;

        m_pColorLabel = CCLabelTTF::create("#color", "Marker Felt", 30);
        m_pColorLabel->retain();

        m_pColorLabel->setPosition(background->getPosition());
        layer->addChild(m_pColorLabel);

        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));

        // Update the color text
        colourValueChanged(colourPicker, CCControlEventValueChanged);
        return true;
    }
    return false;

}

CCControlColourPickerTest::~CCControlColourPickerTest()
{
    CC_SAFE_RELEASE(m_pColorLabel);
}

void CCControlColourPickerTest::colourValueChanged(CCObject *sender, CCControlEvent controlEvent)
{
    CCControlColourPicker* pPicker = (CCControlColourPicker*)sender;
    m_pColorLabel->setString(CCString::createWithFormat("#%02X%02X%02X",pPicker->getColor().r, pPicker->getColor().g, pPicker->getColor().b)->getCString());
}


