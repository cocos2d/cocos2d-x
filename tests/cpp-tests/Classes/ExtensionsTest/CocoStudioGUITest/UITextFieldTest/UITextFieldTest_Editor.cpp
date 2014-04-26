

#include "UITextFieldTest_Editor.h"


// UITextFieldTest_Editor

UITextFieldTest_Editor::UITextFieldTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UITextFieldTest_Editor::~UITextFieldTest_Editor()
{
    
}

bool UITextFieldTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        TextField* textField_normal = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1109"));
        textField_normal->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
        
        TextField* textField_max_character = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1110"));
        textField_max_character->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
        
        TextField* textField_password = static_cast<TextField*>(Helper::seekWidgetByName(root, "TextField_1107"));
        textField_password->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setText("No event");
        _displayValueLabel->setPosition(Vector2(_layout->getSize().width / 2,
                                              _layout->getSize().height - _displayValueLabel->getSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel);
        
        return true;
    }
    
    return false;
}

void UITextFieldTest_Editor::textFieldEvent(Ref *pSender, TextFiledEventType type)
{
    switch (type)
    {
        case TEXTFIELD_EVENT_ATTACH_WITH_IME:
            _displayValueLabel->setText("attach with IME");
            break;
            
        case TEXTFIELD_EVENT_DETACH_WITH_IME:
            _displayValueLabel->setText("detach with IME");
            break;
            
        case TEXTFIELD_EVENT_INSERT_TEXT:
            _displayValueLabel->setText("insert words");
            break;
            
        case TEXTFIELD_EVENT_DELETE_BACKWARD:
            _displayValueLabel->setText("delete word");
            break;
            
        default:
            break;
    }
}
