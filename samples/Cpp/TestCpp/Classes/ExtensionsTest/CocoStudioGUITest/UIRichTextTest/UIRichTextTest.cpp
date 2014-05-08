

#include "UIRichTextTest.h"

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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("RichText");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 3.125));
        m_pUiLayer->addWidget(alert);
        
        
        UIButton* button = UIButton::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosui/animationbuttonnormal.png", "cocosui/animationbuttonpressed.png", "");
        button->setTitleText("switch");
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f + button->getSize().height * 2.5));
        button->addTouchEventListener(this, toucheventselector(UIRichTextTest::touchEvent));
        m_pUiLayer->addWidget(button);
        
        
        // RichText
        _richText = RichText::create();
        _richText->ignoreContentAdaptWithSize(false);
        _richText->setSize(CCSizeMake(100, 100));
        
        RichElementText* re1 = RichElementText::create(1, ccWHITE, 255, "This color is white. ", "Helvetica", 10);
        RichElementText* re2 = RichElementText::create(2, ccYELLOW, 255, "And this is yellow. ", "Helvetica", 10);
        RichElementText* re3 = RichElementText::create(3, ccBLUE, 255, "This one is blue. ", "Helvetica", 10);
        RichElementText* re4 = RichElementText::create(4, ccGREEN, 255, "And green. ", "Helvetica", 10);
        RichElementText* re5 = RichElementText::create(5, ccRED, 255, "Last one is red ", "Helvetica", 10);
        
        RichElementImage* reimg = RichElementImage::create(6, ccWHITE, 255, "cocosui/sliderballnormal.png");
        
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("cocosui/100/100.ExportJson");
        CCArmature *pAr = CCArmature::create("100");
        pAr->getAnimation()->play("Animation1");
        
        RichElementCustomNode* recustom = RichElementCustomNode::create(1, ccWHITE, 255, pAr);
        RichElementText* re6 = RichElementText::create(7, ccORANGE, 255, "Have fun!! ", "Helvetica", 10);
        _richText->pushBackElement(re1);
        _richText->insertElement(re2, 1);
        _richText->pushBackElement(re3);
        _richText->pushBackElement(re4);
        _richText->pushBackElement(re5);
        _richText->insertElement(reimg, 2);
        _richText->pushBackElement(recustom);
        _richText->pushBackElement(re6);
        
        _richText->setPosition(ccp(widgetSize.width / 2, widgetSize.height / 2));
        
        m_pUiLayer->addWidget(_richText);
        
        return true;
    }
    return false;
}

void UIRichTextTest::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
        {
            if (_richText->isIgnoreContentAdaptWithSize())
            {
                _richText->ignoreContentAdaptWithSize(false);
                _richText->setSize(CCSizeMake(100, 100));
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