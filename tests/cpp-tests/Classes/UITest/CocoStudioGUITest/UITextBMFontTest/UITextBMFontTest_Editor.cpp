#include "UITextBMFontTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UITextBMFontEditorTest::UITextBMFontEditorTest()
{
    ADD_TEST_CASE(UITextBMFontTest_Editor);
}

// UITextBMFontTest_Editor

bool UITextBMFontTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UILabelBMFont/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}
