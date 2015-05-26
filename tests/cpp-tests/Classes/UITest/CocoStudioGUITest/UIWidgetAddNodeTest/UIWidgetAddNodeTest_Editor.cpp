#include "UIWidgetAddNodeTest_Editor.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIWidgetAddNodeEditorTests::UIWidgetAddNodeEditorTests()
{
    ADD_TEST_CASE(UIWidgetAddNodeTest_Editor);
}

// UIWidgetAddNodeTest_Editor

UIWidgetAddNodeTest_Editor::UIWidgetAddNodeTest_Editor()
{
    
}

UIWidgetAddNodeTest_Editor::~UIWidgetAddNodeTest_Editor()
{
    
}

void UIWidgetAddNodeTest_Editor::configureGUIScene()
{
    UIScene_Editor::configureGUIScene();

    Size rootSize = _layout->getContentSize();

    // Create the ui widget
    Widget* widget = Widget::create();
    widget->setPosition(Vec2(rootSize.width / 2.0f, rootSize.height / 2.0f));
    widget->setLocalZOrder(_layout->getLocalZOrder() + 1);
    _layout->addChild(widget);
    
    Sprite* sprite = Sprite::create("cocosui/ccicon.png");
    widget->addChild(sprite);
}


bool UIWidgetAddNodeTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        Node* node = CSLoader::createNode("cocosui/UIEditorTest/UIWidgetAddNode/res.csb");
        Node* child = node->getChildByTag(5);
        child->removeFromParent();
        _layout = static_cast<Layout*>(child);
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
        
        return true;
    }
    
    return false;
}

