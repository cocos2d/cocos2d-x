#include "UIImageViewTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIImageViewEditorTests::UIImageViewEditorTests()
{
    ADD_TEST_CASE(UIImageViewTest_Editor);
}

// UIImageViewTest_Editor
bool UIImageViewTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIImageView/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}
