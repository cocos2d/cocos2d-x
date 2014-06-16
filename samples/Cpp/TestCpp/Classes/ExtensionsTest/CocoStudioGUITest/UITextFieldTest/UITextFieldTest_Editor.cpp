

#include "UITextFieldTest_Editor.h"


// UITextFieldTest_Editor

UITextFieldTest_Editor::UITextFieldTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UITextFieldTest_Editor::~UITextFieldTest_Editor()
{
    
}

void UITextFieldTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    if (item->getSelectedIndex() == 0){
        _layout->removeAllChildrenWithCleanup(true);
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeAllChildrenWithCleanup(true);
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromBinaryFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.csb"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
    }
}

void UITextFieldTest_Editor::configureGUIScene()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize rootSize = _layout->getSize();
    _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                     (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    
    _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
    
    TextField* textField_normal = static_cast<TextField*>(UIHelper::seekWidgetByName(root, "TextField_1109"));
    textField_normal->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
    
    TextField* textField_max_character = static_cast<TextField*>(UIHelper::seekWidgetByName(root, "TextField_1110"));
    textField_max_character->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
    
    TextField* textField_password = static_cast<TextField*>(UIHelper::seekWidgetByName(root, "TextField_1107"));
    textField_password->addEventListenerTextField(this, textfieldeventselector(UITextFieldTest_Editor::textFieldEvent));
}

bool UITextFieldTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosui/UIEditorTest/UITextField_Editor/ui_textfield_editor_1.json"));

        _touchGroup->addWidget(_layout);
       
        this->configureGUIScene();
        
        _displayValueLabel = ui::Label::create();
        _displayValueLabel->setFontName("Marker Felt");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setText("No event");
        _displayValueLabel->setPosition(ccp(_layout->getSize().width / 2,
                                            _layout->getSize().height - _displayValueLabel->getSize().height * 1.75f));
        _touchGroup->addWidget(_displayValueLabel);
        
        return true;
    }
    
    return false;
}

void UITextFieldTest_Editor::textFieldEvent(CCObject *pSender, TextFiledEventType type)
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
