

#include "UIWidgetAddNodeTest_Editor.h"


// UIWidgetAddNodeTest_Editor

UIWidgetAddNodeTest_Editor::UIWidgetAddNodeTest_Editor()
{
    
}

UIWidgetAddNodeTest_Editor::~UIWidgetAddNodeTest_Editor()
{
    
}

void UIWidgetAddNodeTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    if (item->getSelectedIndex() == 0){
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.json"));
        
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.csb"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }
}

void UIWidgetAddNodeTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
    
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
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UIWidgetAddNode_Editor/ui_widget_add_node_editor.json"));
        _touchGroup->addChild(_layout);
        this->configureGUIScene();
        return true;
    }
    
    return false;
}

