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
    ADD_TEST_CASE(UITextTest_IgnoreConentSize);
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
        text->setContentSize(Size(280, 150));
        text->setTextHorizontalAlignment(TextHAlignment::CENTER);
        text->setTouchScaleChangeEnabled(true);
        text->setTouchEnabled(true);
        text->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED)
            {
                if ((int)text->getContentSize().width == 280)
                {
                    text->setContentSize(Size(380,100));
                }else
                {
                    text->setContentSize(Size(280, 150));
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
        disableOutlineBtn->setPosition(Vec2(widgetSize.width * 0.3,
                                 widgetSize.height * 0.7));
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
                                    + Vec2(buttonWidth + 40,0));
        disableGlowBtn->setTitleText("Disable Glow");
        disableGlowBtn->addClickEventListener([=](Ref*){
            glow_label->disableEffect(LabelEffect::GLOW);
        });
        this->addChild(disableGlowBtn);

        auto disableShadowBtn = (Button*)disableGlowBtn->clone();
        disableShadowBtn->setPosition(disableGlowBtn->getPosition()
                                      + Vec2(buttonWidth + 40,0));
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

// UITextTest_IgnoreConentSize

bool UITextTest_IgnoreConentSize::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        Text* leftText = Text::create("ignore conent",
                                   "fonts/Marker Felt.ttf",10);
        leftText->setPosition(Vec2(widgetSize.width / 2.0f - 50,
                                widgetSize.height / 2.0f));
        leftText->ignoreContentAdaptWithSize(false);
        leftText->setTextAreaSize(Size(60,60));
        leftText->setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
        leftText->setTouchScaleChangeEnabled(true);
        leftText->setTouchEnabled(true);
        _uiLayer->addChild(leftText);


        Text* rightText = Text::create("ignore conent",
                                      "fonts/Marker Felt.ttf",10);
        rightText->setPosition(Vec2(widgetSize.width / 2.0f + 50,
                                   widgetSize.height / 2.0f));
        rightText->setString("Text line with break\nText line with break\nText line with break\nText line with break\n");
        //note:setTextAreaSize must be used with ignoreContentAdaptWithSize(false)
        rightText->setTextAreaSize(Size(100,30));
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
