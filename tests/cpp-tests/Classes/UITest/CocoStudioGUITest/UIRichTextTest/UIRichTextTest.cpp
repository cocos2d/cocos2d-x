#include "UIRichTextTest.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIRichTextTests::UIRichTextTests()
{
    ADD_TEST_CASE(UIRichTextTest);
}

UIRichTextTest::UIRichTextTest()
{
    
}

UIRichTextTest::~UIRichTextTest()
{
    
}

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
        button->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + button->getContentSize().height * 2.5));
        button->addTouchEventListener(CC_CALLBACK_2(UIRichTextTest::touchEvent, this));
        button->setLocalZOrder(10);
        _widget->addChild(button);
        
        
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
