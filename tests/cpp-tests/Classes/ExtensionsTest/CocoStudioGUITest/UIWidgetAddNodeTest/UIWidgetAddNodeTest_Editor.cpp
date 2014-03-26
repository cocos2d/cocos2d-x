

#include "UIWidgetAddNodeTest_Editor.h"


// UIWidgetAddNodeTest_Editor

UIWidgetAddNodeTest_Editor::UIWidgetAddNodeTest_Editor()
{
    
}

UIWidgetAddNodeTest_Editor::~UIWidgetAddNodeTest_Editor()
{
    
}

bool UIWidgetAddNodeTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.json"));
        _touchGroup->addChild(_layout);
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _layout->getSize();
        _touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                       (screenSize.height - rootSize.height) / 2));
        
        Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
        
        Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
        
        _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
        
        
        // Create the ui widget
        Widget* widget = Widget::create();
        widget->setPosition(Point(rootSize.width / 2.0f, rootSize.height / 2.0f));
        widget->setLocalZOrder(_layout->getLocalZOrder() + 1);
        _layout->addChild(widget);
        
        Sprite* sprite = Sprite::create("cocosui/ccicon.png");
        widget->addChild(sprite);
        
        return true;
    }
    
    return false;
}

