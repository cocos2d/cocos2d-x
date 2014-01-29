

#include "UIButtonTest.h"


// UIButtonTest
UIButtonTest::UIButtonTest()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest::~UIButtonTest()
{
}

bool UIButtonTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);        
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Button");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);        
        alert->setColor(Color3B(159, 168, 176));                
        
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the button
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));        
        button->addTouchEventListener(this, toucheventselector(UIButtonTest::touchEvent));
        _uiLayer->addChild(button);        

        return true;
    }
    return false;
}

void UIButtonTest::touchEvent(Object *pSender, TouchEventType type)
{
    switch (type)
    {
        case gui::TOUCH_EVENT_BEGAN:
            _displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case gui::TOUCH_EVENT_MOVED:
            _displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case gui::TOUCH_EVENT_ENDED:
            _displayValueLabel->setText(String::createWithFormat("Touch Up")->getCString());
            break;
            
        case gui::TOUCH_EVENT_CANCELED:
            _displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}


// UIButtonTest_Scale9
UIButtonTest_Scale9::UIButtonTest_Scale9()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Scale9::~UIButtonTest_Scale9()
{
    
}

bool UIButtonTest_Scale9::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Button scale9 render");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the button
        Button* button = Button::create();
        button->setTouchEnabled(true);
        // open scale9 render
        button->setScale9Enabled(true);
        button->loadTextures("cocosgui/button.png", "cocosgui/buttonHighlighted.png", "");
        button->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->setSize(Size(150, button->getContentSize().height * 1.5f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Scale9::touchEvent));
        _uiLayer->addChild(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_Scale9::touchEvent(Object *pSender, TouchEventType type)
{
    switch (type)
    {
        case gui::TOUCH_EVENT_BEGAN:
            _displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case gui::TOUCH_EVENT_MOVED:
            _displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case gui::TOUCH_EVENT_ENDED:
            _displayValueLabel->setText(String::createWithFormat("Touch Up")->getCString());
            break;
            
        case gui::TOUCH_EVENT_CANCELED:
            _displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTest_PressAction
UIButtonTest_PressedAction::UIButtonTest_PressedAction()
: _displayValueLabel(nullptr)
{
}

UIButtonTest_PressedAction::~UIButtonTest_PressedAction()
{
}

bool UIButtonTest_PressedAction::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the button events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1.0f));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Button Pressed Action");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the button
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->setPressedActionEnabled(true);
        button->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "");
        button->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_PressedAction::touchEvent));        
        _uiLayer->addChild(button);
        
        return true;
    }
    return false;
}

void UIButtonTest_PressedAction::touchEvent(Object *pSender, TouchEventType type)
{
    switch (type)
    {
        case gui::TOUCH_EVENT_BEGAN:
            _displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case gui::TOUCH_EVENT_MOVED:
            _displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case gui::TOUCH_EVENT_ENDED:
            _displayValueLabel->setText(String::createWithFormat("Touch Up")->getCString());
            break;
            
        case gui::TOUCH_EVENT_CANCELED:
            _displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}

// UIButtonTest_Title
UIButtonTest_Title::UIButtonTest_Title()
: _displayValueLabel(nullptr)
{
    
}

UIButtonTest_Title::~UIButtonTest_Title()
{
}

bool UIButtonTest_Title::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();
        
        // Add a label in which the text button events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("Button with title");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the button with title
        Button* button = Button::create();
        button->setTouchEnabled(true);
        button->loadTextures("cocosgui/backtotoppressed.png", "cocosgui/backtotopnormal.png", "");
        button->setTitleText("Title Button");
        button->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        button->addTouchEventListener(this, toucheventselector(UIButtonTest_Title::touchEvent));
        _uiLayer->addChild(button);
        
        return true;
    }
    return false;
}


void UIButtonTest_Title::touchEvent(Object *pSender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_BEGAN:
            _displayValueLabel->setText(String::createWithFormat("Touch Down")->getCString());
            break;
            
        case TOUCH_EVENT_MOVED:
            _displayValueLabel->setText(String::createWithFormat("Touch Move")->getCString());
            break;
            
        case TOUCH_EVENT_ENDED:
            _displayValueLabel->setText(String::createWithFormat("Touch Up")->getCString());
            break;
            
        case TOUCH_EVENT_CANCELED:
            _displayValueLabel->setText(String::createWithFormat("Touch Cancelled")->getCString());
            break;
            
        default:
            break;
    }
}