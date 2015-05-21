#include "UICheckBoxTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UICheckBoxEditorTests::UICheckBoxEditorTests()
{
    ADD_TEST_CASE(UICheckBoxTest_Editor);
}

// UICheckBoxTest_Editor

UICheckBoxTest_Editor::UICheckBoxTest_Editor()
: _displayValueLabel(nullptr)
{
    
}

UICheckBoxTest_Editor::~UICheckBoxTest_Editor()
{
    
}

void UICheckBoxTest_Editor::configureGUIScene()
{
    UIScene_Editor::configureGUIScene();
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));

    CheckBox* checkbox = static_cast<CheckBox*>(Helper::seekWidgetByName(root, "CheckBox_540"));
    checkbox->addEventListener(CC_CALLBACK_2(UICheckBoxTest_Editor::selectedStateEvent, this));
    
}

bool UICheckBoxTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UICheckBox/res.csb");
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
