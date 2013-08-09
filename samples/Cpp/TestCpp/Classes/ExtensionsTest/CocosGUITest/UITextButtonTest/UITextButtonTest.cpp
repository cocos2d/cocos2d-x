

#include "UITextButtonTest.h"

// UITextButtonTest
UITextButtonTest::UITextButtonTest()
: m_pDisplayValueLabel(NULL)
{
    
}

UITextButtonTest::~UITextButtonTest()
{
}

bool UITextButtonTest::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the text button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextButton");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);        
        
        // Create the text button
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setTextures("cocosgui/backtotopnormal.png", "cocosgui/backtotoppressed.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textButton->addPushDownEvent(this, coco_pushselector(UITextButtonTest::touchBeganEvent));
        textButton->addMoveEvent(this, coco_moveselector(UITextButtonTest::touchMovedEvent));
        textButton->addReleaseEvent(this, coco_releaseselector(UITextButtonTest::touchEndedEvent));
        m_pUiLayer->addWidget(textButton);
        
        return true;
    }
    return false;
}

void UITextButtonTest::touchBeganEvent(CCObject *pSender)
{
        m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
}

void UITextButtonTest::touchMovedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
}

void UITextButtonTest::touchEndedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
}

// UITextButtonTest_Scale9
UITextButtonTest_Scale9::UITextButtonTest_Scale9()
: m_pDisplayValueLabel(NULL)
{
    
}

UITextButtonTest_Scale9::~UITextButtonTest_Scale9()
{
    
}

bool UITextButtonTest_Scale9::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getRect().size;
        
        // Add a label in which the text button events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("TextButton scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getRect().size.height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the text button
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->setScale9Enable(true);
        textButton->setTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        textButton->setScale9Size(CCSizeMake(180, textButton->getContentSize().height * 1.5f));
        textButton->setText("Text Button scale9 render");
        textButton->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        textButton->addPushDownEvent(this, coco_pushselector(UITextButtonTest::touchBeganEvent));
        textButton->addMoveEvent(this, coco_moveselector(UITextButtonTest::touchMovedEvent));
        textButton->addReleaseEvent(this, coco_releaseselector(UITextButtonTest::touchEndedEvent));
        m_pUiLayer->addWidget(textButton);
        
        return true;
    }
    return false;
}

void UITextButtonTest_Scale9::touchBeganEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
}

void UITextButtonTest_Scale9::touchMovedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
}

void UITextButtonTest_Scale9::touchEndedEvent(CCObject *pSender)
{
    m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
}