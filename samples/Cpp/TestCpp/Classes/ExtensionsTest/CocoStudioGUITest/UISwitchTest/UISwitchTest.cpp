

#include "UISwitchTest.h"

// UISwitchTest_Horizontal
UISwitchTest_Horizontal::UISwitchTest_Horizontal()
{
}

UISwitchTest_Horizontal::~UISwitchTest_Horizontal()
{
}

bool UISwitchTest_Horizontal::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the switch events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Switch Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the switch
        UISwitch* pSwitch = UISwitch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask.png", "cocosgui/switch-on.png", "cocosgui/switch-off.png", "cocosgui/switch-thumb.png");
        pSwitch->setOnTitleText("Hello\nWorld");
        pSwitch->setOffTitleText("Come\nOn");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(10);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(10);
        CCSize switchSize = pSwitch->getSize();
        pSwitch->setPosition(ccp((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        m_pUiLayer->addWidget(pSwitch);
        
        return true;
    }
    return false;
}

void UISwitchTest_Horizontal::switchEvent(CCObject *pSender, SwitchEventType type)
{
    UISwitch *pSwitch = static_cast<UISwitch*>(pSender);
    
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel->setText("Hello World");
    }
    else
    {
        m_pDisplayValueLabel->setText("Come On");
    }
    
    switch (type)
    {
        case SWITCH_EVENT_ON:
            
            break;
            
        case SWITCH_EVENT_OFF:
            
            break;
            
        default:
            break;
    }
}

// UISwitchTest_Vertical
UISwitchTest_Vertical::UISwitchTest_Vertical()
{
}

UISwitchTest_Vertical::~UISwitchTest_Vertical()
{
}

bool UISwitchTest_Vertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the switch events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Switch Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75));
        m_pUiLayer->addWidget(alert);
        
        // Create the switch
        UISwitch* pSwitch = UISwitch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask_v.png", "cocosgui/switch-on_v.png", "cocosgui/switch-off_v.png", "cocosgui/switch-thumb_v.png");
        pSwitch->setOnTitleText("On");
        pSwitch->setOffTitleText("Off");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(16);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(16);
        CCSize switchSize = pSwitch->getSize();
        pSwitch->setPosition(ccp((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        m_pUiLayer->addWidget(pSwitch);
        
        pSwitch->setDirection(SWITCH_DIRECTION_VERTICAL);
        
        return true;
    }
    return false;
}

void UISwitchTest_Vertical::switchEvent(CCObject *pSender, SwitchEventType type)
{
    UISwitch *pSwitch = static_cast<UISwitch*>(pSender);
    
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel->setText("On");
    }
    else
    {
        m_pDisplayValueLabel->setText("Off");
    }
    
    switch (type)
    {
        case SWITCH_EVENT_ON:
            
            break;
            
        case SWITCH_EVENT_OFF:
            
            break;
            
        default:
            break;
    }
}

// UISwitchTest_VerticalAndTitleVertical
UISwitchTest_VerticalAndTitleVertical::UISwitchTest_VerticalAndTitleVertical()
{
}

UISwitchTest_VerticalAndTitleVertical::~UISwitchTest_VerticalAndTitleVertical()
{
}

bool UISwitchTest_VerticalAndTitleVertical::init()
{
    if (UIScene::init())
    {
        CCSize widgetSize = m_pWidget->getSize();
        
        // Add a label in which the switch events will be displayed
        m_pDisplayValueLabel = UILabel::create();
        m_pDisplayValueLabel->setText("No Event");
        m_pDisplayValueLabel->setFontName("Marker Felt");
        m_pDisplayValueLabel->setFontSize(32);
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1));
        m_pDisplayValueLabel->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        m_pUiLayer->addWidget(m_pDisplayValueLabel);
        
        // Add the alert
        UILabel *alert = UILabel::create();
        alert->setText("Switch Vertical and Title Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(ccc3(159, 168, 176));
        alert->setPosition(ccp(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7));
        m_pUiLayer->addWidget(alert);
        
        // Create the switch
        UISwitch* pSwitch = UISwitch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask_v.png", "cocosgui/switch-on_v.png", "cocosgui/switch-off_v.png", "cocosgui/switch-thumb_v.png");
        pSwitch->setOnTitleText("On");
        pSwitch->setOffTitleText("Off");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(16);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(16);
        CCSize switchSize = pSwitch->getSize();
        pSwitch->setPosition(ccp((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        m_pUiLayer->addWidget(pSwitch);
        
        
        pSwitch->setDirection(SWITCH_DIRECTION_VERTICAL);
        
        // set unicode text with title vertical direction
        pSwitch->setTitleDirection(SWITCH_TITLE_DIRECTION_VERTICAL);
        
        return true;
    }
    return false;
}

void UISwitchTest_VerticalAndTitleVertical::switchEvent(CCObject *pSender, SwitchEventType type)
{
    UISwitch *pSwitch = static_cast<UISwitch*>(pSender);
    
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel->setText("On");
    }
    else
    {
        m_pDisplayValueLabel->setText("Off");
    }
    
    switch (type)
    {
        case SWITCH_EVENT_ON:
            
            break;
            
        case SWITCH_EVENT_OFF:
            
            break;
            
        default:
            break;
    }
}
