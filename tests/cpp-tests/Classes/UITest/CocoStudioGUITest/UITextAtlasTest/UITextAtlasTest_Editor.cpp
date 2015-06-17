#include "UITextAtlasTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextAtlasEditorTests::UITextAtlasEditorTests()
{
    ADD_TEST_CASE(UITextAtlasTest_Editor);
}

bool UITextAtlasTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILabelAtlas/res.csb");        
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}
