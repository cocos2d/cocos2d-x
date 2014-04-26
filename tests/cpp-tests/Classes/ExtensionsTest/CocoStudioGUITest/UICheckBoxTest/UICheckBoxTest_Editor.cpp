

#include "UICheckBoxTest_Editor.h"


// UICheckBoxTest_Editor

UICheckBoxTest_Editor::UICheckBoxTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UICheckBoxTest_Editor::~UICheckBoxTest_Editor()
{
    
}

bool UICheckBoxTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Vector2((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        CheckBox* checkbox = static_cast<CheckBox*>(Helper::seekWidgetByName(root, "CheckBox_540"));
        checkbox->addEventListenerCheckBox(this, checkboxselectedeventselector(UICheckBoxTest_Editor::selectedStateEvent));
        
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

void UICheckBoxTest_Editor::selectedStateEvent(Ref *pSender, CheckBoxEventType type)
{
    switch (type)
    {
        case CHECKBOX_STATE_EVENT_UNSELECTED:
            _displayValueLabel->setText("Unselected");
            break;
            
        case CHECKBOX_STATE_EVENT_SELECTED:
            _displayValueLabel->setText("Selected");
            break;
            
        default:
            break;
    }
}
