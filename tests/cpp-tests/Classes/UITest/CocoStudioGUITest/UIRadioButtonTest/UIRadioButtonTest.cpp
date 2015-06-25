#include "UIRadioButtonTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIRadioButtonTests::UIRadioButtonTests()
{
	ADD_TEST_CASE(UIRadioButtonTest);
	ADD_TEST_CASE(UIRadioButtonTabTest);
}

// UIRadioButtonTest
UIRadioButtonTest::UIRadioButtonTest()
: _groupEventLabel(nullptr),
_buttonEventLabel(nullptr),
_logConsole(nullptr),
_numberOfLogLines(0)
{
	_radioButtonGroups[0] = nullptr;
	_radioButtonGroups[1] = nullptr;
}

UIRadioButtonTest::~UIRadioButtonTest()
{
}

bool UIRadioButtonTest::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();;
        
        // Add a label in which the radio button events will be displayed
		_groupEventLabel = Text::create("RadioButtonGroup : No Event", "fonts/Marker Felt.ttf", 25);
		_groupEventLabel->setAnchorPoint(Vec2(0.5f, -1));
		_groupEventLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 70));
		_uiLayer->addChild(_groupEventLabel);
		
        _buttonEventLabel = Text::create("RadioButton : No Event", "fonts/Marker Felt.ttf", 25);
        _buttonEventLabel->setAnchorPoint(Vec2(0.5f, -1));
        _buttonEventLabel->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f + 35));
        _uiLayer->addChild(_buttonEventLabel);
		
		_logConsole = Text::create("", "fonts/Marker Felt.ttf", 10);
		_logConsole->setAnchorPoint(Vec2(0, 1));
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
				_radioButtonGroups[type]->addEventListener(CC_CALLBACK_3(UIRadioButtonTest::onChangedRadioButtonGroup1, this));
				normalImage = "cocosui/radio_button_off.png";
				selectedImage = "cocosui/radio_button_on.png";
				posYAdjust = 35;
			}
			else
			{
				_radioButtonGroups[type]->addEventListener(CC_CALLBACK_3(UIRadioButtonTest::onChangedRadioButtonGroup2, this));
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
				
				radioButton->addEventListener(CC_CALLBACK_2(UIRadioButtonTest::onChangedRadioButtonSelect, this));
				radioButton->setTag(i);
				_radioButtonGroups[type]->addRadioButton(radioButton);
			}
		}
		
		Button* clearButton = Button::create("cocosui/backtotopnormal.png", "cocosui/backtotoppressed.png");
		clearButton->setTitleText("Clear");
		clearButton->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 65));
		clearButton->addClickEventListener(CC_CALLBACK_1(UIRadioButtonTest::clearRadioButtonGroup, this));
		clearButton->setScale(0.8f);
		_uiLayer->addChild(clearButton);
		
		Text* text1 = Text::create("Upper radio button group is allowed non-selection, but lower one is not.", "fonts/Marker Felt.ttf", 15);
		text1->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - 100));
		_uiLayer->addChild(text1);

        return true;
    }
    return false;
}

void UIRadioButtonTest::onChangedRadioButtonGroup1(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
	CCASSERT(index == _radioButtonGroups[0]->getSelectedButtonIndex(), "The two indexes must match!");
	__String* text = String::createWithFormat("RadioButtonGroup1 : %d", index);
	_groupEventLabel->setString(text->getCString());
	addLog(text->getCString());
}

void UIRadioButtonTest::onChangedRadioButtonGroup2(RadioButton* radioButton, int index, cocos2d::ui::RadioButtonGroup::EventType type)
{
	CCASSERT(index == _radioButtonGroups[1]->getSelectedButtonIndex(), "The two indexes must match!");
	__String* text = String::createWithFormat("RadioButtonGroup2 : %d", index);
	_groupEventLabel->setString(text->getCString());
	addLog(text->getCString());
}

void UIRadioButtonTest::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type)
{
	if(radioButton == nullptr)
	{
		return;
	}
	__String* text = String::createWithFormat("RadioButton %d : ", radioButton->getTag());
    switch (type)
    {
        case RadioButton::EventType::SELECTED:
		{
			text->append("Selected");
			break;
		}
			
        case RadioButton::EventType::UNSELECTED:
		{
			text->append("Unselected");
			break;
		}
        default:
            break;
    }
	_buttonEventLabel->setString(text->getCString());
	addLog(text->getCString());
}

void UIRadioButtonTest::clearRadioButtonGroup(Ref* sender)
{
	for(int i = 0; i < 2; ++i)
	{
		_radioButtonGroups[i]->setSelectedButton(nullptr);
	}
}

void UIRadioButtonTest::addLog(const std::string& log)
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
		size_t pos = existingLog.find("\n") + 1;
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
		Size widgetSize = _widget->getContentSize();;
		
		static const float BUTTON_SCALE = 0.5f;
		const float buttonWidth = 350 * BUTTON_SCALE / Director::getInstance()->getContentScaleFactor();
		
		// Background for buttons
		LayerColor* colorLayer = LayerColor::create(Color4B::WHITE);
		colorLayer->ignoreAnchorPointForPosition(false);
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
			__String* filePathNormal = String::createWithFormat("cocosui/btn_exercise%02d_n.png", i + 1);
			__String* filePathSelected = String::createWithFormat("cocosui/btn_exercise%02d_p.png", i + 1);
			RadioButton* radioButton = RadioButton::create(filePathNormal->getCString(), filePathSelected->getCString());
			float posX = startPosX + buttonWidth * i;
			radioButton->setPosition(Vec2(posX, widgetSize.height / 2.0f));
			radioButton->setScale(BUTTON_SCALE);
			radioButton->setZoomScale(0.05f);
			radioButtonGroup->addRadioButton(radioButton);
		}
		radioButtonGroup->setSelectedButton(0);
		return true;
	}
	return false;
}
