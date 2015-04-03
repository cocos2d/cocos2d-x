#include "UIImageViewTest_Editor.h"

UIImageViewEditorTests::UIImageViewEditorTests()
{
    ADD_TEST_CASE(UIImageViewTest_Editor);
}

// UIImageViewTest_Editor
bool UIImageViewTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIImageView/crossplatform_UIImageView_Editor_1.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}
