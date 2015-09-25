#include "UICheckBoxTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UICheckBoxTests::UICheckBoxTests()
{
    ADD_TEST_CASE(UICheckBoxTest);
    ADD_TEST_CASE(UICheckBoxDefaultBehaviorTest);
    ADD_TEST_CASE(UICheckBoxCopyTest);
}

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
        Size widgetSize = _widget->getContentSize();;
        
        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("CheckBox","fonts/Marker Felt.ttf",30 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the checkbox
        CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_normal_press.png",
                                              "cocosui/check_box_active.png",
                                              "cocosui/check_box_normal_disable.png",
                                              "cocosui/check_box_active_disable.png");
        checkBox->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
        _uiLayer->addChild(checkBox);
        
        return true;
    }
    return false;
}

void UICheckBoxTest::selectedEvent(Ref* pSender,CheckBox::EventType type)
{
    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            _displayValueLabel->setString(StringUtils::format("Selected"));
            break;
            
        case CheckBox::EventType::UNSELECTED:
            _displayValueLabel->setString(StringUtils::format("Unselected"));
            break;
            
        default:
            break;
    }
    
}


// UICheckBoxDefaultBehaviorTest
UICheckBoxDefaultBehaviorTest::UICheckBoxDefaultBehaviorTest()
: _displayValueLabel(nullptr)
{
    
}

UICheckBoxDefaultBehaviorTest::~UICheckBoxDefaultBehaviorTest()
{
}

bool UICheckBoxDefaultBehaviorTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();;
        
        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Only left two and the last checkbox can be cliked!","fonts/Marker Felt.ttf",20 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);
        
        // Create the checkbox
        CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
        checkBox->setPosition(Vec2(widgetSize.width / 2.0f - 50, widgetSize.height / 2.0f));
        
        _uiLayer->addChild(checkBox);
        
        
        // Create the checkbox
        CheckBox* checkBox2 = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
        checkBox2->setPosition(Vec2(widgetSize.width / 2.0f - 150, widgetSize.height / 2.0f));
        checkBox2->ignoreContentAdaptWithSize(false);
        checkBox2->setZoomScale(0.5);
        checkBox2->setContentSize(Size(80,80));
        checkBox2->setName("bigCheckBox");
        _uiLayer->addChild(checkBox2);
        
        
        // Create the checkbox
        CheckBox* checkBoxDisabled = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
        checkBoxDisabled->setPosition(Vec2(widgetSize.width / 2.0f + 20, widgetSize.height / 2.0f));
        checkBoxDisabled->setEnabled(false);
        checkBoxDisabled->setBright(false);
        _uiLayer->addChild(checkBoxDisabled);
        
        CheckBox* checkBoxDisabled2 = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
        checkBoxDisabled2->setPosition(Vec2(widgetSize.width / 2.0f + 70, widgetSize.height / 2.0f));
        checkBoxDisabled2->setBright(false);
        checkBoxDisabled2->setSelected(true);
        _uiLayer->addChild(checkBoxDisabled2);
        return true;
    }
    return false;
}


// UICheckBoxCopyTest
UICheckBoxCopyTest::UICheckBoxCopyTest()
: _displayValueLabel(nullptr)
{

}

UICheckBoxCopyTest::~UICheckBoxCopyTest()
{
}

bool UICheckBoxCopyTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();;

        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);

        // Add the alert
        Text* alert = Text::create("Two checkbox are identical.","fonts/Marker Felt.ttf",20 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);

        // Create the checkbox
        CheckBox* checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_active.png");
        checkBox->setPosition(Vec2(widgetSize.width / 2.0f - 50, widgetSize.height / 2.0f));

        _uiLayer->addChild(checkBox);

        auto checkboxCopy = checkBox->clone();
        checkboxCopy->setPosition(checkBox->getPosition() + Vec2(50,0));
        _uiLayer->addChild(checkboxCopy);


        return true;
    }
    return false;
}
