

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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create("No Event","Marker Felt",32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create("Button","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the button
        UIButton* button = UIButton::create("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png");
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest::touchEvent));
        m_pUiLayer->addWidget(button);

        return true;
    }
    return false;
}

void UIButtonTest::onEnter()
{
    UIScene::onEnter();
}

void UIButtonTest::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
            break;
            
        case TOUCH_EVENT_MOVED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
            break;
            
        case TOUCH_EVENT_ENDED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
            break;
            
        case TOUCH_EVENT_CANCELED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

void UIButtonTest::selector(CCObject *pObejct)
{
    UIButton* button = static_cast<UIButton*>(pObejct);
    if (button)
    {
        CCLOG("can cast to UIButton");
    }
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
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create("No Event","Marker Felt",32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create("Button scale9 render","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the button
        UIButton* button = UIButton::create("cocosgui/button.png", "cocosgui/buttonHighlighted.png");
        // open scale9 render
        button->setScale9Enabled(true);
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setSize(CCSizeMake(150, button->getContentSize().height * 1.5f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Scale9::touchEvent));
        m_pUiLayer->addWidget(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_Scale9::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
            break;
            
        case TOUCH_EVENT_MOVED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
            break;
            
        case TOUCH_EVENT_ENDED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
            break;
            
        case TOUCH_EVENT_CANCELED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTest_PressAction
UIButtonTest_PressedAction::UIButtonTest_PressedAction()
: m_pDisplayValueLabel(NULL)
{
}

UIButtonTest_PressedAction::~UIButtonTest_PressedAction()
{
}

bool UIButtonTest_PressedAction::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the button events will be displayed
        m_pDisplayValueLabel = UILabel::create("No Event","Marker Felt",32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create("Button Pressed Action","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the button
        UIButton* button = UIButton::create("cocosgui/animationbuttonnormal.png");
        button->setPressedActionEnabled(true);
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_PressedAction::touchEvent));
        m_pUiLayer->addWidget(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_PressedAction::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
            break;
            
        case TOUCH_EVENT_MOVED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
            break;
            
        case TOUCH_EVENT_ENDED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
            break;
            
        case TOUCH_EVENT_CANCELED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

/*===*/
// UIButtonTest_Title
UIButtonTest_Title::UIButtonTest_Title()
: m_pDisplayValueLabel(NULL)
{
    
}

UIButtonTest_Title::~UIButtonTest_Title()
{
}

bool UIButtonTest_Title::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the text button events will be displayed
        m_pDisplayValueLabel = UILabel::create("No Event","Marker Felt",32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel* alert = UILabel::create("Button with title","Marker Felt",30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the button with title
        UIButton* button = UIButton::create("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png");
        button->setTitleText("Title Button");
        button->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Title::touchEvent));
        m_pUiLayer->addWidget(button);
        
        return true;
    }
    return false;
}


void UIButtonTest_Title::touchEvent(CCObject *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Down")->getCString());
            break;
            
        case TOUCH_EVENT_MOVED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Move")->getCString());
            break;
            
        case TOUCH_EVENT_ENDED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Up")->getCString());
            break;
            
        case TOUCH_EVENT_CANCELED:
            m_pDisplayValueLabel->setText(CCString::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}
/*=*/

