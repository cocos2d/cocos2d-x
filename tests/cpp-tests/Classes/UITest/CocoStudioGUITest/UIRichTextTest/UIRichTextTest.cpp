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
    ADD_TEST_CASE(UIRichTextXMLFace);
    ADD_TEST_CASE(UIRichTextXMLBR);
    ADD_TEST_CASE(UIRichTextXMLInvalid);
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
              str1.length(),
              StringUtils::getCharacterCountInUTF8String(str1),
              Helper::getSubStringOfUTF8String(str1, 0, 5).c_str());
        CCLOG("str2:%s ascii length = %ld, utf8 length = %ld, substr = %s",
              str2.c_str(),
              str2.length(),
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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextTest::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBasic::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSmallBig::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLColor::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


        // RichText
        _richText = RichText::createWithXML("Defaul color.<font color='#ff0000'>red.<font color='#00ff00'>green</font>red again.</font>default again");
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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB2::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLSUIB3::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLImg::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLUrl::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


        // RichText
        _richText = RichText::createWithXML("And this link will redirect you to google: <a href='http://www.google.com'>click me</a>");
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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLFace::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


        // RichText
        _richText = RichText::createWithXML("<font size='20' face='fonts/Marker Felt.ttf'>Marker Felt 20.<font face='fonts/arial.ttf'>Arial 20.</font></font><font face='font/Thonburi.ttf' size='24' color='#0000ff'>Thonburi 24 blue</font>");
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
        button2->setPosition(Vec2(widgetSize.width * 2 / 3, widgetSize.height / 2.0f + button2->getContentSize().height * 2.5));
        button2->addTouchEventListener(CC_CALLBACK_2(UIRichTextXMLBR::switchWrapMode, this));
        button2->setLocalZOrder(10);
        _widget->addChild(button2);


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

