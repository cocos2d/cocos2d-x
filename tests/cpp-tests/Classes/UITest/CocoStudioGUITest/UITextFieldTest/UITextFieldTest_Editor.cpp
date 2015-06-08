#include "UITextFieldTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextFieldEditorTests::UITextFieldEditorTests()
{
    ADD_TEST_CASE(UITextFieldTest_Editor);
}
// UITextFieldTest_Editor

UITextFieldTest_Editor::UITextFieldTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UITextFieldTest_Editor::~UITextFieldTest_Editor()
{
    
}

void UITextFieldTest_Editor::configureGUIScene()
{
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    TextField* textField_normal = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1109"));
    textField_normal->addEventListener(CC_CALLBACK_2(UITextFieldTest_Editor::textFieldEvent, this));
    
    TextField* textField_max_character = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1110"));
    textField_max_character->addEventListener(CC_CALLBACK_2(UITextFieldTest_Editor::textFieldEvent, this));
    
    TextField* textField_password = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1107"));
    textField_password->addEventListener(CC_CALLBACK_2(UITextFieldTest_Editor::textFieldEvent, this));
}

bool UITextFieldTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UITextField/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setString("No event");
        _displayValueLabel->setPosition(Vec2(_layout->getContentSize().width / 2,
                                              _layout->getContentSize().height - _displayValueLabel->getContentSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel, 20);
        
        return true;
    }
    
    return false;
}

void UITextFieldTest_Editor::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    switch (type)
    {
        case TextField::EventType::ATTACH_WITH_IME:
            _displayValueLabel->setString("attach with IME");
            break;
            
        case TextField::EventType::DETACH_WITH_IME:
            _displayValueLabel->setString("detach with IME");
            break;
            
        case TextField::EventType::INSERT_TEXT:
            _displayValueLabel->setString("insert words");
            break;
            
        case TextField::EventType::DELETE_BACKWARD:
            _displayValueLabel->setString("delete word");
            break;
            
        default:
            break;
    }
}
