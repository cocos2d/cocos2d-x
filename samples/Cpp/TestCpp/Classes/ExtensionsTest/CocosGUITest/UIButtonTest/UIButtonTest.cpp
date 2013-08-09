

#include "UIButtonTest.h"

// UIButtonTest
UIButtonTest::UIButtonTest()
: m_pDisplayValueLabel(NULL)
{
}

UIButtonTest::~UIButtonTest()
{
}

bool UIButtonTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);        
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Button");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the button
        UIButton *button = UIButton::create();
        button->setTouchEnable(true);
        button->setTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addPushDownEvent(this, coco_pushselector(UIButtonTest::touchBeganEvent));
        button->addMoveEvent(this, coco_moveselector(UIButtonTest::touchMovedEvent));
        button->addReleaseEvent(this, coco_releaseselector(UIButtonTest::touchEndedEvent));
        m_pUiLayer->addWidget(button);

        return true;
    }
    return false;
}

void UIButtonTest::touchBeganEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
}

void UIButtonTest::touchMovedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
}

void UIButtonTest::touchEndedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
}


// UIButtonTest_Scale9
UIButtonTest_Scale9::UIButtonTest_Scale9()
: m_pDisplayValueLabel(NULL)
{
    
}

UIButtonTest_Scale9::~UIButtonTest_Scale9()
{
    
}

bool UIButtonTest_Scale9::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Button scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the button
        UIButton *button = UIButton::create();
        button->setTouchEnable(true);
        // open scale9 render
        button->setScale9Enable(true);
        button->setTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setScale9Size(CCSizeMake(150, button->getContentSize().height * 1.5f));
        button->addPushDownEvent(this, coco_pushselector(UIButtonTest_Scale9::touchBeganEvent));
        button->addMoveEvent(this, coco_moveselector(UIButtonTest_Scale9::touchMovedEvent));
        button->addReleaseEvent(this, coco_releaseselector(UIButtonTest_Scale9::touchEndedEvent));
        m_pUiLayer->addWidget(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_Scale9::touchBeganEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
}

void UIButtonTest_Scale9::touchMovedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
}

void UIButtonTest_Scale9::touchEndedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
}