

#include "UIRichTextTest.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"

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
        Size widgetSize = _widget->getSize();
        
        // Add the alert
        Text *alert = Text::create("RichText", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.125));
        _widget->addChild(alert);
        
        
        Button* button = Button::create("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png");
        button->setTouchEnabled(true);
        button->setTitleText("switch");
        button->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + button->getSize().height * 2.5));
        button->addTouchEventListener(this, toucheventselector(UIRichTextTest::touchEvent));
        button->setLocalZOrder(10);
        _widget->addChild(button);
        
        
        // RichText
        _richText = RichText::create();
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setSize(Size(100, 100));
        
        RichElementText* re1 = RichElementText::create(1, Color3B::WHITE, 255, "This color is white. ", "Helvetica", 10);
        RichElementText* re2 = RichElementText::create(2, Color3B::YELLOW, 255, "And this is yellow. ", "Helvetica", 10);
        RichElementText* re3 = RichElementText::create(3, Color3B::BLUE, 255, "This one is blue. ", "Helvetica", 10);
        RichElementText* re4 = RichElementText::create(4, Color3B::GREEN, 255, "And green. ", "Helvetica", 10);
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
        
        _richText->setPosition(Vector2(widgetSize.width / 2, widgetSize.height / 2));
        _richText->setLocalZOrder(10);
        
        
        _widget->addChild(_richText);
        
        return true;
    }
    return false;
}

void UIRichTextTest::touchEvent(Ref *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
        {
            if (_richText->isIgnoreContentAdaptWithSize())
            {
                _richText->ignoreContentAdaptWithSize(false);
                _richText->setSize(Size(100, 100));
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
