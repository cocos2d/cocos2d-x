#include "UILoadingBarTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UILoadingBarEditorTests::UILoadingBarEditorTests()
{
    ADD_TEST_CASE(UILoadingBarTest_Editor);
}
// UILoadingBarTest_Editor

UILoadingBarTest_Editor::UILoadingBarTest_Editor()
:_count(0)
{
    
}

UILoadingBarTest_Editor::~UILoadingBarTest_Editor()
{
    
}

void UILoadingBarTest_Editor::configureGUIScene()
{
    UIScene_Editor::configureGUIScene();

    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    LoadingBar* loadingBar_left_to_right = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(root, "LoadingBar_856"));
    loadingBar_left_to_right->setPercent(0);
    
    LoadingBar* loadingBar_right_to_left = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(root, "LoadingBar_857"));
    loadingBar_right_to_left->setPercent(0);
}

bool UILoadingBarTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        scheduleUpdate();
        
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILoadingBar/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}

void UILoadingBarTest_Editor::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    LoadingBar* loadingBar_left_to_right = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(root, "LoadingBar_856"));
    loadingBar_left_to_right->setPercent(_count);
    
    LoadingBar* loadingBar_right_to_left = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(root, "LoadingBar_857"));
    loadingBar_right_to_left->setPercent(_count);
}
