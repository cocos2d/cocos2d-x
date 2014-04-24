

#include "UICheckBoxTest_Editor.h"


// UICheckBoxTest_Editor

UICheckBoxTest_Editor::UICheckBoxTest_Editor()
: _displayValueLabel(NULL)
{
    
}

UICheckBoxTest_Editor::~UICheckBoxTest_Editor()
{
    
}

bool UICheckBoxTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("cocosgui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json"));
        _touchGroup->addWidget(_layout);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        CCSize rootSize = _layout->getSize();
        _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                         (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
        
        ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
        
        CheckBox* checkbox = static_cast<CheckBox*>(UIHelper::seekWidgetByName(root, "CheckBox_540"));
        checkbox->addEventListenerCheckBox(this, checkboxselectedeventselector(UICheckBoxTest_Editor::selectedStateEvent));
        
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

void UICheckBoxTest_Editor::selectedStateEvent(CCObject *pSender, CheckBoxEventType type)
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
