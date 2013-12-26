

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
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the switch events will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Switch Horizontal");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the switch
        Switch* pSwitch = Switch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask.png", "cocosgui/switch-on.png", "cocosgui/switch-off.png", "cocosgui/switch-thumb.png");
        pSwitch->setOnTitleText("On");
        pSwitch->setOffTitleText("Off");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(16);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(16);
        Size switchSize = pSwitch->getSize();
        pSwitch->setPosition(Point((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        _uiLayer->addChild(pSwitch);
        
        return true;
    }
    return false;
}

void UISwitchTest_Horizontal::switchEvent(Object *pSender, SwitchEventType type)
{
    Switch* pSwitch = static_cast<Switch*>(pSender);
    
    if (pSwitch->isOn())
    {
        _displayValueLabel->setText("On");
    }
    else
    {
        _displayValueLabel->setText("Off");
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
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the switch events will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Switch Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the switch
        Switch* pSwitch = Switch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask_v.png", "cocosgui/switch-on_v.png", "cocosgui/switch-off_v.png", "cocosgui/switch-thumb_v.png");
        pSwitch->setOnTitleText("On");
        pSwitch->setOffTitleText("Off");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(16);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(16);
        Size switchSize = pSwitch->getSize();
        pSwitch->setPosition(Point((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        _uiLayer->addChild(pSwitch);
        
        pSwitch->setDirection(SWITCH_DIRECTION_VERTICAL);
        
        return true;
    }
    return false;
}

void UISwitchTest_Vertical::switchEvent(Object *pSender, SwitchEventType type)
{
    Switch *pSwitch = static_cast<Switch*>(pSender);
    
    if (pSwitch->isOn())
    {
        _displayValueLabel->setText("On");
    }
    else
    {
        _displayValueLabel->setText("Off");
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
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the switch events will be displayed
        _displayValueLabel = gui::Label::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Label* alert = gui::Label::create();
        alert->setText("Switch Vertical and Title Vertical");
        alert->setFontName("Marker Felt");
        alert->setFontSize(20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 2.7));
        _uiLayer->addChild(alert);
        
        // Create the switch
        Switch* pSwitch = Switch::create();
        pSwitch->setTouchEnabled(true);
        pSwitch->loadTextures("cocosgui/switch-mask_v.png", "cocosgui/switch-on_v.png", "cocosgui/switch-off_v.png", "cocosgui/switch-thumb_v.png");
        pSwitch->setOnTitleText("On");
        pSwitch->setOffTitleText("Off");
        pSwitch->setOnTitleFontName("Arial-BoldMT");
        pSwitch->setOnTitleFontSize(16);
        pSwitch->setOffTitleFontName("Arial-BoldMT");
        pSwitch->setOffTitleFontSize(16);
        Size switchSize = pSwitch->getSize();
        pSwitch->setPosition(Point((widgetSize.width - switchSize.width) / 2.0f, (widgetSize.height - switchSize.height) / 2.0f));
        pSwitch->addEventListenerSwitch(this, switchselector(UISwitchTest_Horizontal::switchEvent));
        _uiLayer->addChild(pSwitch);
        
        
        pSwitch->setDirection(SWITCH_DIRECTION_VERTICAL);
        
        // set unicode text with title vertical direction
        pSwitch->setTitleDirection(SWITCH_TITLE_DIRECTION_VERTICAL);
        
        return true;
    }
    return false;
}

void UISwitchTest_VerticalAndTitleVertical::switchEvent(Object *pSender, SwitchEventType type)
{
    Switch* pSwitch = static_cast<Switch*>(pSender);
    
    if (pSwitch->isOn())
    {
        _displayValueLabel->setText("On");
    }
    else
    {
        _displayValueLabel->setText("Off");
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
