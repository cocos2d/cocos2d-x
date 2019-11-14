/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("CheckBox","fonts/Marker Felt.ttf",30 );
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 1.75f));
        _uiLayer->addChild(alert);        
        
        // Create the checkbox
        _checkBox = CheckBox::create("cocosui/check_box_normal.png",
                                              "cocosui/check_box_normal_press.png",
                                              "cocosui/check_box_active.png",
                                              "cocosui/check_box_normal_disable.png",
                                              "cocosui/check_box_active_disable.png");
        _checkBox->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        
        _checkBox->addEventListener(CC_CALLBACK_2(UICheckBoxTest::selectedEvent, this));
        _uiLayer->addChild(_checkBox);

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        auto label1 = Label::createWithTTF(ttfConfig, "Print Resources");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(UICheckBoxTest::printWidgetResources, this));
        item1->setPosition(Vec2(VisibleRect::left().x + 60, VisibleRect::bottom().y + item1->getContentSize().height * 3));
        auto pMenu1 = Menu::create(item1, nullptr);
        pMenu1->setPosition(Vec2(0.0f, 0.0f));
        this->addChild(pMenu1, 10);
        
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

void UICheckBoxTest::printWidgetResources(cocos2d::Ref* sender)
{
    cocos2d::ResourceData backGroundFileName = _checkBox->getBackNormalFile();
    CCLOG("backGroundFile  Name : %s, Type: %d", backGroundFileName.file.c_str(),backGroundFileName.type);
    cocos2d::ResourceData backGroundSelectedFileName = _checkBox->getBackPressedFile();
    CCLOG("backGroundSelectedFile  Name : %s, Type: %d", backGroundSelectedFileName.file.c_str(), backGroundSelectedFileName.type);
    cocos2d::ResourceData backGroundDisabledFileName = _checkBox->getBackDisabledFile();
    CCLOG("backGroundDisabledFile  Name : %s, Type: %d", backGroundDisabledFileName.file.c_str(), backGroundDisabledFileName.type);
    cocos2d::ResourceData frontCrossFileName = _checkBox->getCrossNormalFile();
    CCLOG("frontCrossFile  Name : %s, Type: %d", frontCrossFileName.file.c_str(), frontCrossFileName.type);
    cocos2d::ResourceData frontCrossDisabledFileName = _checkBox->getCrossDisabledFile();
    CCLOG("frontCrossDisabledFile  Name : %s, Type: %d", frontCrossDisabledFileName.file.c_str(), frontCrossDisabledFileName.type);
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
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
        _uiLayer->addChild(_displayValueLabel);
        
        // Add the alert
        Text* alert = Text::create("Only left two and the last checkbox can be clicked!","fonts/Marker Felt.ttf",20 );
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
        checkBox2->setZoomScale(0.5f);
        checkBox2->setContentSize(Size(80.0f,80.0f));
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
        Size widgetSize = _widget->getContentSize();

        // Add a label in which the checkbox events will be displayed
        _displayValueLabel = Text::create("No Event", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
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
        checkboxCopy->setPosition(checkBox->getPosition() + Vec2(50.0f,0.0f));
        _uiLayer->addChild(checkboxCopy);


        return true;
    }
    return false;
}
