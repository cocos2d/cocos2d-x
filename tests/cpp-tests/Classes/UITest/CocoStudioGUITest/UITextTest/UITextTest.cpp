/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UITextTest.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

UITextTests::UITextTests()
{
    ADD_TEST_CASE(UITextTest);
    ADD_TEST_CASE(UITextTest_LineWrap);
    ADD_TEST_CASE(UILabelTest_Effect);
    ADD_TEST_CASE(UITextTest_TTF);
    ADD_TEST_CASE(UITextTest_IgnoreContentSize);
    ADD_TEST_CASE(UITextTest_Clone);
    ADD_TEST_CASE(Issue16073Test);
}

// UITextTest

bool UITextTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* alert = Text::create("Text","fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the text
        Text* text = Text::create("Text", "AmericanTypewriter", 30);
        text->setPosition(Vec2(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f
                               + text->getContentSize().height / 4.0f));
        _uiLayer->addChild(text);

        return true;
    }
    return false;
}

// UITextTest_LineWrap

bool UITextTest_LineWrap::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* alert = Text::create("Text line wrap","fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the line wrap
        Text* text = Text::create("TextArea Widget can line wrap",
                                  "AmericanTypewriter",32);
        text->ignoreContentAdaptWithSize(false);
        text->setContentSize(Size(280.0f, 150.0f));
        text->setTextHorizontalAlignment(TextHAlignment::CENTER);
        text->setTouchScaleChangeEnabled(true);
        text->setTouchEnabled(true);
        text->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED)
            {
                if ((int)text->getContentSize().width == 280)
                {
                    text->setContentSize(Size(380.0f,100.0f));
                }else
                {
                    text->setContentSize(Size(280.0f, 150.0f));
                }
            }
        });
        text->setPosition(Vec2(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f
                               - text->getContentSize().height / 8.0f));
        _uiLayer->addChild(text);

        return true;
    }
    return false;
}

// UILabelTest_Effect


bool UILabelTest_Effect::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* alert = Text::create();
        alert->setString("Label Effect");
        alert->setFontName("fonts/Marker Felt.ttf");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 3.05f));
        _uiLayer->addChild(alert);


        // create the shadow only label
        Text* shadow_label = Text::create();

        shadow_label->enableShadow();
        shadow_label->setString("Shadow");
        shadow_label->setFontName("fonts/Marker Felt.ttf");
        shadow_label->setPosition(Vec2(widgetSize.width / 2.0f,
                                       widgetSize.height / 2.0f
                                      + shadow_label->getContentSize().height + 20));

        _uiLayer->addChild(shadow_label);


        // create the stroke only label
        Text* glow_label = Text::create();
        glow_label->setFontName("fonts/Marker Felt.ttf");
        glow_label->setString("Glow");
        glow_label->enableGlow(Color4B::RED);


        glow_label->setPosition(Vec2(widgetSize.width / 2.0f,
                                     widgetSize.height / 2.0f - 20));

        _uiLayer->addChild(glow_label);


        // create the label stroke and shadow
        Text* outline_label = Text::create();
        outline_label->setString("Outline");
        CCLOG("content size without outline: %f %f",
              outline_label->getContentSize().width,
              outline_label->getContentSize().height);
        outline_label->enableOutline(Color4B::GREEN, 4);
        outline_label->setPosition(Vec2(widgetSize.width / 2.0f,
                                        widgetSize.height / 2.0f
                                      - shadow_label->getContentSize().height - 50));

        _uiLayer->addChild(outline_label);
        CCLOG("content size after applying outline: %f %f",
              outline_label->getContentSize().width,
              outline_label->getContentSize().height);

        //create buttons to disable effect and add
        auto disableOutlineBtn= Button::create();
        disableOutlineBtn->setTitleText("Disable outline");
        disableOutlineBtn->setTitleFontName("fonts/Marker Felt.ttf");
        disableOutlineBtn->setPosition(Vec2(widgetSize.width * 0.3f,
                                 widgetSize.height * 0.7f));
        disableOutlineBtn->setPressedActionEnabled(true);
        disableOutlineBtn->addClickEventListener([=](Ref*){
            outline_label->disableEffect(LabelEffect::OUTLINE);
            CCLOG("content size after disable outline: %f %f",
                  outline_label->getContentSize().width,
                  outline_label->getContentSize().height);
        });
        this->addChild(disableOutlineBtn);

        auto buttonWidth = disableOutlineBtn->getContentSize().width;

        auto disableGlowBtn = (Button*)disableOutlineBtn->clone();
        disableGlowBtn->setPosition(disableOutlineBtn->getPosition()
                                    + Vec2(buttonWidth + 40,0.0f));
        disableGlowBtn->setTitleText("Disable Glow");
        disableGlowBtn->addClickEventListener([=](Ref*){
            glow_label->disableEffect(LabelEffect::GLOW);
        });
        this->addChild(disableGlowBtn);

        auto disableShadowBtn = (Button*)disableGlowBtn->clone();
        disableShadowBtn->setPosition(disableGlowBtn->getPosition()
                                      + Vec2(buttonWidth + 40,0.0f));
        disableShadowBtn->setTitleText("Disable Shadow");
        disableShadowBtn->addClickEventListener([=](Ref*){
            shadow_label->disableEffect(LabelEffect::SHADOW);
        });
        this->addChild(disableShadowBtn);


        return true;
    }
    return false;
}


// UITextTest_TTF

bool UITextTest_TTF::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* alert = Text::create("Text set TTF font",
                                   "fonts/Marker Felt.ttf",30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f
                                - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the text, and set font with .ttf
        Text* text = Text::create("Text","fonts/A Damn Mess.ttf",30);
        text->setPosition(Vec2(widgetSize.width / 2.0f,
                               widgetSize.height / 2.0f
                               + text->getContentSize().height / 4.0f));
        _uiLayer->addChild(text);

        return true;
    }
    return false;
}

// UITextTest_IgnoreContentSize

bool UITextTest_IgnoreContentSize::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* leftText = Text::create("ignore content",
                                   "fonts/Marker Felt.ttf",10);
        leftText->setPosition(Vec2(widgetSize.width / 2.0f - 50,
                                widgetSize.height / 2.0f));
        leftText->ignoreContentAdaptWithSize(false);
        leftText->setTextAreaSize(Size(60.0f,60.0f));
        leftText->setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
        leftText->setTouchScaleChangeEnabled(true);
        leftText->setTouchEnabled(true);
        _uiLayer->addChild(leftText);


        Text* rightText = Text::create("ignore content",
                                      "fonts/Marker Felt.ttf",10);
        rightText->setPosition(Vec2(widgetSize.width / 2.0f + 50,
                                   widgetSize.height / 2.0f));
        rightText->setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
        //note:setTextAreaSize must be used with ignoreContentAdaptWithSize(false)
        rightText->setTextAreaSize(Size(100.0f,30.0f));
        rightText->ignoreContentAdaptWithSize(false);
        _uiLayer->addChild(rightText);


        auto halighButton = Button::create();
        halighButton->setTitleText("Alignment Right");
        halighButton->addClickEventListener([=](Ref*){
            leftText->setTextHorizontalAlignment(TextHAlignment::RIGHT);
            rightText->setTextHorizontalAlignment(TextHAlignment::RIGHT);
        });
        halighButton->setPosition(Vec2(widgetSize.width/2 - 50,
                                       widgetSize.height/2 - 50));
        _uiLayer->addChild(halighButton);

        return true;
    }
    return false;
}

// UITextTest_IgnoreContentSize

bool UITextTest_Clone::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* singleText = Text::create("ignore content",
            "fonts/Marker Felt.ttf", 30);
        singleText->setPosition(Vec2(widgetSize.width / 2.0f - 80,
            widgetSize.height / 2.0f));
        singleText->setString("CHUKONG");
        singleText->setTouchScaleChangeEnabled(true);
        singleText->setTouchEnabled(true);
        singleText->enableOutline(Color4B(255,0,0,100), 10);
        singleText->enableShadow(Color4B::YELLOW, Size(2,-2), 0);
        _uiLayer->addChild(singleText);

        auto cloneText = singleText->clone();
        cloneText->setPosition(Vec2(widgetSize.width / 2.0f + 80,
            widgetSize.height / 2.0f));
        _uiLayer->addChild(cloneText);

        return true;
    }
    return false;
}

// Issue16073Test

bool Issue16073Test::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* singleText = Text::create("mwhahaha\360", "Verdana", 40);

        singleText->setPosition(Vec2(widgetSize.width / 2.0f - 80,
                                     widgetSize.height / 2.0f));
        _uiLayer->addChild(singleText);

        return true;
    }
    return false;
}

