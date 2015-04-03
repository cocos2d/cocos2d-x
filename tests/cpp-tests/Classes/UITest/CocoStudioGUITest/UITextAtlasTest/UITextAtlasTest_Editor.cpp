#include "UITextAtlasTest_Editor.h"

UITextAtlasEditorTests::UITextAtlasEditorTests()
{
    ADD_TEST_CASE(UITextAtlasTest_Editor);
}

bool UITextAtlasTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILabelAtlas/crossplatform_UILabelAtlas_Editor_1.csb");        
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}
