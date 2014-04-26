

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
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vector2(0.5f, -1));
        _displayValueLabel->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("CheckBox","fonts/Marker Felt.ttf",30 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the checkbox
        CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_normal_press.png",
                                              "cocosui/check_box_active.png",
                                              "cocosui/check_box_normal_disable.png",
                                              "cocosui/check_box_active_disable.png");
        checkBox->setPosition(Vector2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(UICheckBoxTest::selectedEvent));
        _uiLayer->addChild(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedEvent(Ref* pSender,CheckBoxEventType type)
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
