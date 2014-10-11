

#include "UITextFieldTest_Editor.h"


// UITextFieldTest_Editor

UITextFieldTest_Editor::UITextFieldTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UITextFieldTest_Editor::~UITextFieldTest_Editor()
{
    
}

void UITextFieldTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    if (item->getSelectedIndex() == 0){
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"));
        
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.csb"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }
}

void UITextFieldTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"));
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
