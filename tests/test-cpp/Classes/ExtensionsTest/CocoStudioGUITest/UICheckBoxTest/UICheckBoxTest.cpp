

#include "UICheckBoxTest.h"


// UICheckBoxTest
UICheckBoxTest::UICheckBoxTest()
: _displayValueLabel(nullptr)
{
    
}

UICheckBoxTest::~UICheckBoxTest()
{
}

bool UICheckBoxTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getSize();;
        
        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = gui::Text::create();
        _displayValueLabel->setText("No Event");
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(32);
        _displayValueLabel->setAnchorPoint(Point(0.5f, -1));
        _displayValueLabel->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        gui::Text* alert = gui::Text::create();
        alert->setText("CheckBox");
        alert->setFontName("Marker Felt");
        alert->setFontSize(30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the checkbox
        CheckBox* checkBox = CheckBox::create();
        checkBox->setTouchEnabled(true);
        checkBox->loadTextures("cocosgui/check_box_normal.png",
                               "cocosgui/check_box_normal_press.png",
                               "cocosgui/check_box_active.png",
                               "cocosgui/check_box_normal_disable.png",
                               "cocosgui/check_box_active_disable.png");
        checkBox->setPosition(Point(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(UICheckBoxTest::selectedEvent));
        _uiLayer->addChild(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedEvent(Object* pSender,CheckBoxEventType type)
{
    switch (type)
    {
        case CHECKBOX_STATE_EVENT_SELECTED:
            _displayValueLabel->setText(String::createWithFormat("Selected")->getCString());
            break;
            
        case CHECKBOX_STATE_EVENT_UNSELECTED:
            _displayValueLabel->setText(String::createWithFormat("Unselected")->getCString());
            break;
            
        default:
            break;
    }
    
}