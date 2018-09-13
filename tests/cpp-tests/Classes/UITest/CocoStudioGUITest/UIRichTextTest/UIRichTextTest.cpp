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

#include "UIRichTextTest.h"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "editor-support/cocostudio/CCArmature.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIRichTextTests::UIRichTextTests()
{
    ADD_TEST_CASE(UIRichTextTest);
    ADD_TEST_CASE(UIRichTextXMLBasic);
    ADD_TEST_CASE(UIRichTextXMLSmallBig);
    ADD_TEST_CASE(UIRichTextXMLColor);
    ADD_TEST_CASE(UIRichTextXMLSUIB);
    ADD_TEST_CASE(UIRichTextXMLSUIB2);
    ADD_TEST_CASE(UIRichTextXMLSUIB3);
    ADD_TEST_CASE(UIRichTextXMLImg);
    ADD_TEST_CASE(UIRichTextXMLUrl);
    ADD_TEST_CASE(UIRichTextXMLUrlImg);
    ADD_TEST_CASE(UIRichTextXMLFace);
    ADD_TEST_CASE(UIRichTextXMLBR);
    ADD_TEST_CASE(UIRichTextXMLInvalid);
    ADD_TEST_CASE(UIRichTextXMLOutline);
    ADD_TEST_CASE(UIRichTextXMLShadow);
    ADD_TEST_CASE(UIRichTextXMLGlow);
    ADD_TEST_CASE(UIRichTextXMLExtend);
    ADD_TEST_CASE(UIRichTextXMLSpace);
}


//
// UIRichTextTest
//
bool UIRichTextTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        auto config = Configuration::getInstance();
        config->loadConfigFile("configs/config-test-ok.plist");


        std::string str1 = config->getValue("Chinese").asString();
        std::string str2 = config->getValue("Japanese").asString();
        CCLOG("str1:%s ascii length = %ld, utf8 length = %ld, substr = %s",
            str1.c_str(),
            static_cast<long>(str1.length()),
            StringUtils::getCharacterCountInUTF8String(str1),
            Helper::getSubStringOfUTF8String(str1, 0, 5).c_str());
        CCLOG("str2:%s ascii length = %ld, utf8 length = %ld, substr = %s",
            str2.c_str(),
            static_cast<long>(str2.length()),
            StringUtils::getCharacterCountInUTF8String(str2),
            Helper::getSubStringOfUTF8String(str2, 0, 2).c_str());

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);

        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextTest::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextTest::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextTest::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::create();
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        RichElementText* re1 = RichElementText::create(1, Color3B::WHITE, 255, str1, "SimSun", 10);
        RichElementText* re2 = RichElementText::create(2, Color3B::YELLOW, 255, "And this is yellow. ", "Helvetica", 10);
        RichElementText* re3 = RichElementText::create(3, Color3B::GRAY, 255, str2, "Yu Mincho", 10);
        RichElementText* re4 = RichElementText::create(4, Color3B::GREEN, 255, "And green with TTF support. ", "fonts/Marker Felt.ttf", 10);
        RichElementText* re5 = RichElementText::create(5, Color3B::RED, 255, "Last one is red ", "Helvetica", 10);

        RichElementImage* reimg = RichElementImage::create(6, Color3B::WHITE, 255, "cocosui/sliderballnormal.png");

        cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("cocosui/100/100.ExportJson");
        cocostudio::Armature *pAr = cocostudio::Armature::create("100");
        pAr->getAnimation()->play("Animation1");

        RichElementCustomNode* recustom = RichElementCustomNode::create(1, Color3B::WHITE, 255, pAr);
        RichElementText* re6 = RichElementText::create(7, Color3B::ORANGE, 255, "Have fun!! ", "Helvetica", 10);
        _richText->pushBackElement(re1);
        _richText->insertElement(re2, 1);
        _richText->pushBackElement(re3);
        _richText->pushBackElement(re4);
        _richText->pushBackElement(re5);
        _richText->insertElement(reimg, 2);
        _richText->pushBackElement(recustom);
        _richText->pushBackElement(re6);

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextTest::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextTest::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextTest::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLBasic
//
bool UIRichTextXMLBasic::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBasic::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBasic::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBasic::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("This is just a simple text. no xml tags here. testing the basics. testing word-wrapping. testing, testing, testing");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLBasic::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLBasic::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLBasic::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLSmallBig
//
bool UIRichTextXMLSmallBig::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSmallBig::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSmallBig::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSmallBig::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("Regular size.<small>smaller size.</small><big>bigger.<small>normal.</small>bigger</big>.normal.");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLSmallBig::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLSmallBig::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLSmallBig::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLColor
//
bool UIRichTextXMLColor::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLColor::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLColor::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLColor::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("Default color.<font color='#ff0000'>red.<font color='#00ff00'>green</font>red again.</font>default again");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLColor::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLColor::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLColor::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLSUIB
//
bool UIRichTextXMLSUIB::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("system font: <u>underline</u><i>italics</i><b>bold</b><del>strike-through</del>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLSUIB::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLSUIB::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLSUIB::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLSUIB2
//
bool UIRichTextXMLSUIB2::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB2::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB2::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB2::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font face='fonts/Marker Felt.ttf' size='24'>ttf font: <u>underline</u><i>italics</i><b>bold</b><del>strike-through</del></font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLSUIB2::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLSUIB2::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLSUIB2::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLSUIB3
//
bool UIRichTextXMLSUIB3::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB3::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB3::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB3::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font face='fonts/Marker Felt.ttf' size='20'>ttf font: <i><u>italics and underline</u></i><del><b>bold and strike-through</b></del></font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLSUIB3::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLSUIB3::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLSUIB3::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLImg
//
bool UIRichTextXMLImg::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLImg::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLImg::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLImg::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("you should see an image here: <img src='cocosui/sliderballnormal.png'/> and this is text again. and this is the same image, but bigger: <img src='cocosui/sliderballnormal.png' width='30' height='30' /> and here goes text again");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLImg::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLImg::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLImg::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLUrl
//
bool UIRichTextXMLUrl::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrl::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrl::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrl::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("This link will redirect you to google: <a href='http://www.google.com'>click me</a>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLUrl::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLUrl::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLUrl::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLUrlImg
//
bool UIRichTextXMLUrlImg::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrlImg::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrlImg::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrlImg::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("This link will redirect you to google: <a href='http://www.google.com'><img src=\"cocosui/ccicon.png\" height=\"48\" width=\"48\" /></a>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLUrlImg::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLUrlImg::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLUrlImg::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLFace
//
bool UIRichTextXMLFace::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLFace::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLFace::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLFace::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font size='20' face='fonts/Marker Felt.ttf'>Marker Felt 20.<font face='fonts/arial.ttf'>Arial 20.</font></font><font face='font/Thonburi.ttf' size='24' color='#0000ff'>Thonburi 24 blue</font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(120, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLFace::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLFace::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLFace::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLBR
//
bool UIRichTextXMLBR::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBR::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBR::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBR::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("this is one line.<br/>this should be in another line.<br/>and this is another line");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLBR::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLBR::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLBR::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLInvalid
//
bool UIRichTextXMLInvalid::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Invalid XML test", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        // RichText
        _richText = RichText::createWithXML("this is an invalid xml. <i>no closing tag");
        if (_richText)
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));

            _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
            _richText->setLocalZOrder(10);


            _widget->addChild(_richText);

            // test remove all children, this call won't effect the test
            _richText->removeAllChildren();
        }
        return true;
    }
    return false;
}

//
// UIRichTextXMLOutline
//
bool UIRichTextXMLOutline::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Outline", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLOutline::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLOutline::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLOutline::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font face='fonts/Marker Felt.ttf' size=\"24\"><outline color=\"#D2B48C\" size=\"2\">OUTLINE</outline></font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLOutline::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLOutline::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLOutline::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLShadow
//
bool UIRichTextXMLShadow::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Shadow", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLShadow::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLShadow::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLShadow::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font size=\"24\"><shadow color=\"#4169E1\" offsetWidth=\"8\" offsetHeight=\"-8\" blurRadius=\"2\">SHADOW</shadow></font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(150, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLShadow::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLShadow::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLShadow::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLGlow
//
bool UIRichTextXMLGlow::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Glow", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLGlow::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLGlow::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLGlow::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("<font face=\"fonts/Marker Felt.ttf\" size=\"24\"><glow color=\"#AFEEEE\">GLOW</glow></font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLGlow::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLGlow::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLGlow::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLExtend
//
bool UIRichTextXMLExtend::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Extend", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLExtend::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLExtend::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLExtend::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        /* Tag extension */
        RichText::setTagDescription("CloseNormal", false, [](const ValueMap& tagAttrValueMap) {
            RichElementImage* richElement = RichElementImage::create(0, Color3B::WHITE, 255, "cocosui/CloseNormal.png");
            return make_pair(ValueMap(), richElement);
        });
        RichText::setTagDescription("CloseSelected", false, [](const ValueMap& tagAttrValueMap) {
            RichElementImage* richElement = RichElementImage::create(0, Color3B::WHITE, 255, "cocosui/CloseSelected.png");
            return make_pair(ValueMap(), richElement);
        });

        /* Defaults */
        ValueMap defaults;
        defaults[RichText::KEY_FONT_COLOR_STRING] = "#FFF";
        defaults[RichText::KEY_FONT_SIZE] = 12.0f;
        defaults[RichText::KEY_FONT_FACE] = "fonts/Marker Felt.ttf";
        defaults[RichText::KEY_ANCHOR_FONT_COLOR_STRING] = "#f0f8ff";
        defaults[RichText::KEY_ANCHOR_TEXT_BOLD] = false;
        defaults[RichText::KEY_ANCHOR_TEXT_ITALIC] = false;
        //defaults[RichText::KEY_ANCHOR_TEXT_LINE] = RichText::VALUE_TEXT_LINE_NONE;
        //defaults[RichText::KEY_ANCHOR_TEXT_LINE] = RichText::VALUE_TEXT_LINE_DEL;
        defaults[RichText::KEY_ANCHOR_TEXT_LINE] = RichText::VALUE_TEXT_LINE_UNDER;
        //defaults[RichText::KEY_ANCHOR_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_NONE;
        //defaults[RichText::KEY_ANCHOR_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_OUTLINE;
        //defaults[RichText::KEY_ANCHOR_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_SHADOW;
        //defaults[RichText::KEY_ANCHOR_TEXT_STYLE] = RichText::VALUE_TEXT_STYLE_GLOW;
        defaults[RichText::KEY_ANCHOR_TEXT_OUTLINE_COLOR] = "#D2B48C";
        defaults[RichText::KEY_ANCHOR_TEXT_OUTLINE_SIZE] = 4;
        defaults[RichText::KEY_ANCHOR_TEXT_SHADOW_COLOR] = "#4169E1";
        defaults[RichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH] = 4.0f;
        defaults[RichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT] = -4.0f;
        defaults[RichText::KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS] = 0;
        defaults[RichText::KEY_ANCHOR_TEXT_GLOW_COLOR] = "#AFEEEE";

        // RichText
        _richText = RichText::createWithXML("<span>CloseNormal-tag:<br /><CloseNormal /><br /><br />CloseSelected-tag:<br /><CloseSelected></CloseSelected></span>",
            defaults,
            [](const std::string& url) {
            Application::getInstance()->openURL(url);
        });
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(100, 100));

        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);


        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLExtend::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(100, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLExtend::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLExtend::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}

//
// UIRichTextXMLSpace
//
bool UIRichTextXMLSpace::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();

        // Add the alert
        Text *alert = Text::create("Space", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.125));
        _widget->addChild(alert);


        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vec2(widgetSize.width * 1 / 3, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSpace::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);

        Button* button2 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button2->setTouchEnabled(true);
        button2->setTitleText("wrap mode");
        button2->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSpace::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);

        Button* button3 = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button3->setTouchEnabled(true);
        button3->setTitleText("alignment");
        button3->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button3->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSpace::switchAlignment, this));
        button3->setLocalZOrder(10);
        _widget->addChild(button3);

        // RichText
        _richText = RichText::createWithXML("words should be divided with space.<br /><br /><font face='fonts/Marker Felt.ttf' color='#ffff00'>HELLO </font><font color='#ffff00'>WORLD</font><br /><br /><font color='#ff00ff'>HELLO</font><font face='fonts/Marker Felt.ttf' color='#ff00ff'> WORLD</font>");
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setContentSize(Size(50, 100));
        _richText->setPosition(Vec2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);

        _widget->addChild(_richText);

        // test remove all children, this call won't effect the test
        _richText->removeAllChildren();

        return true;
    }
    return false;
}

void UIRichTextXMLSpace::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        if (_richText->isIgnoreContentAdaptWithSize())
        {
            _richText->ignoreContentAdaptWithSize(false);
            _richText->setContentSize(Size(50, 100));
        }
        else
        {
            _richText->ignoreContentAdaptWithSize(true);
        }
    }
    break;

    default:
        break;
    }
}

void UIRichTextXMLSpace::switchWrapMode(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto wrapMode = _richText->getWrapMode();
        wrapMode = (wrapMode == RichText::WRAP_PER_WORD) ? RichText::WRAP_PER_CHAR : RichText::WRAP_PER_WORD;
        _richText->setWrapMode(wrapMode);
    }
}

void UIRichTextXMLSpace::switchAlignment(Ref *sender, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED)
    {
        auto alignment = _richText->getHorizontalAlignment();
        alignment = static_cast<RichText::HorizontalAlignment>((static_cast<std::underlying_type<RichText::HorizontalAlignment>::type>(alignment) + 1) % 3);
        _richText->setHorizontalAlignment(alignment);
    }
}
