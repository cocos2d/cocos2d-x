

#include "UICheckBoxTest_Editor.h"


// UICheckBoxTest_Editor

UICheckBoxTest_Editor::UICheckBoxTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UICheckBoxTest_Editor::~UICheckBoxTest_Editor()
{
    
}

void UICheckBoxTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    if (item->getSelectedIndex() == 0){
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.csb"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }
}

void UICheckBoxTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    CheckBox* checkbox = static_cast<CheckBox*>(Helper::seekWidgetByName(root, "CheckBox_540"));
    checkbox->addEventListener(CC_CALLBACK_2(UICheckBoxTest_Editor::selectedStateEvent, this));
    
}

bool UICheckBoxTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UICheckBox_Editor/ui_checkbox_editor_1.json"));
        _touchGroup->addChild(_layout);
     
        this->configureGUIScene();
        
        _displayValueLabel = Text::create();
        _displayValueLabel->setFontName("fonts/Marker Felt.ttf");
        _displayValueLabel->setFontSize(30);
        _displayValueLabel->setString("No event");
        _displayValueLabel->setPosition(Vec2(_layout->getContentSize().width / 2,
                                              _layout->getContentSize().height - _displayValueLabel->getContentSize().height * 1.75f));
        _touchGroup->addChild(_displayValueLabel,20);
        
        return true;
    }
    
    return false;
}

void UICheckBoxTest_Editor::selectedStateEvent(Ref *pSender, CheckBox::EventType type)
{
    switch (type)
    {
        case CheckBox::EventType::UNSELECTED:
            _displayValueLabel->setString("Unselected");
            break;
            
        case CheckBox::EventType::SELECTED:
            _displayValueLabel->setString("Selected");
            break;
            
        default:
            break;
    }
}
