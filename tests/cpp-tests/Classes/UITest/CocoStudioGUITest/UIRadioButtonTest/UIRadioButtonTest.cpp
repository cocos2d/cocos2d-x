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

#include "UIRadioButtonTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIRadioButtonTests::UIRadioButtonTests()
{
    ADD_TEST_CASE(UIRadioButtonTest);
    ADD_TEST_CASE(UIRadioButtonTwoGroupsTest);
    ADD_TEST_CASE(UIRadioButtonTabTest);
}


// UIRadioButtonTest
UIRadioButtonTest::UIRadioButtonTest() :
_radioButtonGroup(nullptr),
_allowNoSelectionText(nullptr)
{
}
UIRadioButtonTest::~UIRadioButtonTest()
{
}

static const float BUTTON_WIDTH = 30;
static float startPosX = 0;

bool UIRadioButtonTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Create a radio button group
        _radioButtonGroup = RadioButtonGroup::create();
        _uiLayer->addChild(_radioButtonGroup);
        
        // Create the radio buttons
        static const int NUMBER_OF_BUTTONS = 5;
        startPosX = widgetSize.width / 2.0f - ((NUMBER_OF_BUTTONS - 1) / 2.0f) * BUTTON_WIDTH;
        for(int i = 0; i < NUMBER_OF_BUTTONS; ++i)
        {
            RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
            float posX = startPosX + BUTTON_WIDTH * i;
            radioButton->setPosition(Vec2(posX, widgetSize.height / 2.0f + 10));
            radioButton->setScale(1.2f);
            _radioButtonGroup->addRadioButton(radioButton);
            _uiLayer->addChild(radioButton);
        }
        
        // Add button
        Button* addButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        addButton->setTitleText("Add");
        addButton->setPosition(Vec2(widgetSize.width / 2.0f - 100, widgetSize.height / 2.0f - 65));
        addButton->addClickEventListener(CC_CALLBACK_1(UIRadioButtonTest::addRadioButton, this));
        addButton->setScale(0.7f);
        _uiLayer->addChild(addButton);
        
        // Delete button
        Button* deleteButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        deleteButton->setTitleText("Delete");
        deleteButton->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 65));
        deleteButton->addClickEventListener(CC_CALLBACK_1(UIRadioButtonTest::deleteRadioButton, this));
        deleteButton->setScale(0.7f);
        _uiLayer->addChild(deleteButton);
        
        // Toggle button
        Button* allowNoSelectionToggle = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        allowNoSelectionToggle->setTitleText("Toggle Allow-No-Selection");
        allowNoSelectionToggle->setPosition(Vec2(widgetSize.width / 2.0f + 100, widgetSize.height / 2.0f - 65));
        allowNoSelectionToggle->addClickEventListener([this](Ref*) {
            _radioButtonGroup->setAllowedNoSelection(!_radioButtonGroup->isAllowedNoSelection());
            _allowNoSelectionText->setString(_radioButtonGroup->isAllowedNoSelection() ? "No selection is allowed." : "No selection is disallowed.");
        });
        allowNoSelectionToggle->setScale(0.7f);
        _uiLayer->addChild(allowNoSelectionToggle);
        
        // Add a label for toggle
        _allowNoSelectionText = Text::create("No selection is disallowed.", "fonts/Marker Felt.ttf", 20);
        _allowNoSelectionText->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 70));
        _uiLayer->addChild(_allowNoSelectionText);

        return true;
    }
    return false;
}

void UIRadioButtonTest::addRadioButton(Ref* sender)
{
    Vec2 pos;
    if(_radioButtonGroup->getNumberOfRadioButtons() > 0)
    {
        RadioButton* lastRadioButton = _radioButtonGroup->getRadioButtonByIndex((int)_radioButtonGroup->getNumberOfRadioButtons() - 1);
        pos = lastRadioButton->getPosition();
    }
    else
    {
        pos.x = startPosX - BUTTON_WIDTH;
        pos.y = _widget->getContentSize().height / 2.0f + 10;
    }
    
    RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
    pos.x += BUTTON_WIDTH;
    radioButton->setPosition(pos);
    _radioButtonGroup->addRadioButton(radioButton);
    _uiLayer->addChild(radioButton);
}

void UIRadioButtonTest::deleteRadioButton(Ref* sender)
{
    if(_radioButtonGroup->getNumberOfRadioButtons() > 0)
    {
        RadioButton* radioButton = _radioButtonGroup->getRadioButtonByIndex((int)_radioButtonGroup->getNumberOfRadioButtons() - 1);
        _radioButtonGroup->removeRadioButton(radioButton);
        _uiLayer->removeChild(radioButton);
    }
}




// UIRadioButtonTwoGroupsTest
UIRadioButtonTwoGroupsTest::UIRadioButtonTwoGroupsTest()
: _groupEventLabel(nullptr),
_buttonEventLabel(nullptr),
_logConsole(nullptr),
_numberOfLogLines(0)
{
    _radioButtonGroups[0] = nullptr;
    _radioButtonGroups[1] = nullptr;
}

UIRadioButtonTwoGroupsTest::~UIRadioButtonTwoGroupsTest()
{
}

bool UIRadioButtonTwoGroupsTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        // Add a label in which the radio button events will be displayed
        _groupEventLabel = Text::create("RadioButtonGroup : No Event", "fonts/Marker Felt.ttf", 25);
        _groupEventLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _groupEventLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 70));
        _uiLayer->addChild(_groupEventLabel);
        
        _buttonEventLabel = Text::create("RadioButton : No Event", "fonts/Marker Felt.ttf", 25);
        _buttonEventLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _buttonEventLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 35));
        _uiLayer->addChild(_buttonEventLabel);
        
        _logConsole = Text::create("", "fonts/Marker Felt.ttf", 10);
        _logConsole->setAnchorPoint(Vec2(0.0f, 1.0f));
        _logConsole->setPosition(Vec2(widgetSize.width / 2.0f + 110, widgetSize.height / 2.0f + 55));
        _uiLayer->addChild(_logConsole);

        static const int NUMBER_OF_BUTTONS = 4;
        static const float SPACE_BETWEEN_BUTTONS = 50;
        float startPosX = widgetSize.width / 2.0f - ((NUMBER_OF_BUTTONS - 1) / 2.0f) * SPACE_BETWEEN_BUTTONS;
        
        for(int type = 0; type < 2; ++type)
        {
            // Create a radio button group
            const char *normalImage, *selectedImage;
            float posYAdjust = 0;
            _radioButtonGroups[type] = RadioButtonGroup::create();
            if(type == 0)
            {
                _radioButtonGroups[type]->addEventListener(CC_CALLBACK_3(UIRadioButtonTwoGroupsTest::onChangedRadioButtonGroup1, this));
                normalImage = "cocosui/radio_button_off.png";
                selectedImage = "cocosui/radio_button_on.png";
                posYAdjust = 35;
            }
            else
            {
                _radioButtonGroups[type]->addEventListener(CC_CALLBACK_3(UIRadioButtonTwoGroupsTest::onChangedRadioButtonGroup2, this));
                normalImage = "cocosui/UIEditorTest/2.1/Button/button_common_box03_003 copy 221.png";
                selectedImage = "cocosui/UIEditorTest/2.1/Button/button_common_box03_001.png";
                posYAdjust = -15;
            }
            _uiLayer->addChild(_radioButtonGroups[type]);
            
            // Set allowing no selections
            _radioButtonGroups[type]->setAllowedNoSelection(type == 0);

            // Create the radio buttons
            for(int i = 0; i < NUMBER_OF_BUTTONS; ++i)
            {
                RadioButton* radioButton = nullptr;
                float posY = widgetSize.height / 2.0f + posYAdjust;
                radioButton = RadioButton::create(normalImage, selectedImage);
                float posX = startPosX + SPACE_BETWEEN_BUTTONS * i;
                radioButton->setScale(1.5f);
                radioButton->setPosition(Vec2(posX, posY));
                
                radioButton->addEventListener(CC_CALLBACK_2(UIRadioButtonTwoGroupsTest::onChangedRadioButtonSelect, this));
                radioButton->setTag(i);
                _uiLayer->addChild(radioButton);
                _radioButtonGroups[type]->addRadioButton(radioButton);
            }
        }
        
        Button* clearButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
        clearButton->setTitleText("Clear");
        clearButton->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 65));
        clearButton->addClickEventListener(CC_CALLBACK_1(UIRadioButtonTwoGroupsTest::clearRadioButtonGroup, this));
        clearButton->setScale(0.8f);
        _uiLayer->addChild(clearButton);
        
        Text* text1 = Text::create("Upper radio button group is allowed non-selection, but lower one is not.", "fonts/Marker Felt.ttf", 15);
        text1->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 100));
        _uiLayer->addChild(text1);

        return true;
    }
    return false;
}

void UIRadioButtonTwoGroupsTest::onChangedRadioButtonGroup1(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
    CCASSERT(index == _radioButtonGroups[0]->getSelectedButtonIndex(), "The two indexes must match!");
    auto text = StringUtils::format("RadioButtonGroup1 : %d", index);
    _groupEventLabel->setString(text);
    addLog(text);
}

void UIRadioButtonTwoGroupsTest::onChangedRadioButtonGroup2(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
    CCASSERT(index == _radioButtonGroups[1]->getSelectedButtonIndex(), "The two indexes must match!");
    auto text = StringUtils::format("RadioButtonGroup2 : %d", index);
    _groupEventLabel->setString(text);
    addLog(text);
}

void UIRadioButtonTwoGroupsTest::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type)
{
    if(radioButton == nullptr)
    {
        return;
    }
    auto text = StringUtils::format("RadioButton %d : ", radioButton->getTag());
    switch (type)
    {
        case RadioButton::EventType::SELECTED:
        {
            text.append("Selected");
            break;
        }
            
        case RadioButton::EventType::UNSELECTED:
        {
            text.append("Unselected");
            break;
        }
        default:
            break;
    }
    _buttonEventLabel->setString(text);
    addLog(text);
}

void UIRadioButtonTwoGroupsTest::clearRadioButtonGroup(Ref* sender)
{
    for(int i = 0; i < 2; ++i)
    {
        _radioButtonGroups[i]->setSelectedButton(nullptr);
    }
}

void UIRadioButtonTwoGroupsTest::addLog(const std::string& log)
{
    std::string existingLog = _logConsole->getString();
    if(!existingLog.empty())
    {
        existingLog = existingLog + "\n";
    }
    existingLog = existingLog + log;
    ++_numberOfLogLines;
    
    if(_numberOfLogLines > 10)
    {
        size_t pos = existingLog.find('\n') + 1;
        std::string newLog = existingLog.substr(pos);
        existingLog = newLog;
        --_numberOfLogLines;
    }
    
    _logConsole->setString(existingLog);
}


// UIRadioButtonTabTest
bool UIRadioButtonTabTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        static const float BUTTON_SCALE = 0.5f;
        const float buttonWidth = 350 * BUTTON_SCALE / Director::getInstance()->getContentScaleFactor();
        
        // Background for buttons
        LayerColor* colorLayer = LayerColor::create(Color4B::WHITE);
        colorLayer->setIgnoreAnchorPointForPosition(false);
        colorLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        colorLayer->setContentSize(Size(buttonWidth * 3, 170 / Director::getInstance()->getContentScaleFactor()));
        colorLayer->setPosition(widgetSize / 2.0f);
        _uiLayer->addChild(colorLayer);
        
        // Create a radio button group
        RadioButtonGroup* radioButtonGroup = RadioButtonGroup::create();
        _uiLayer->addChild(radioButtonGroup);
        
        // Create the radio buttons
        static const int NUMBER_OF_BUTTONS = 3;
        float startPosX = widgetSize.width / 2.0f - ((NUMBER_OF_BUTTONS - 1) / 2.0f) * buttonWidth;
        for(int i = 0; i < NUMBER_OF_BUTTONS; ++i)
        {
            auto filePathNormal = StringUtils::format("cocosui/btn_exercise%02d_n.png", i + 1);
            auto filePathSelected = StringUtils::format("cocosui/btn_exercise%02d_p.png", i + 1);
            RadioButton* radioButton = RadioButton::create(filePathNormal, filePathSelected);
            float posX = startPosX + buttonWidth * i;
            radioButton->setPosition(Vec2(posX, widgetSize.height / 2.0f));
            radioButton->setScale(BUTTON_SCALE);
            radioButton->setZoomScale(0.05f);
            radioButtonGroup->addRadioButton(radioButton);
            _uiLayer->addChild(radioButton);
        }
        radioButtonGroup->setSelectedButton(0);
        return true;
    }
    return false;
}
