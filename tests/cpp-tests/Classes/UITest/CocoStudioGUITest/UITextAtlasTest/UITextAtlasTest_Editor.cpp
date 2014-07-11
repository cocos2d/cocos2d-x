

#include "UITextAtlasTest_Editor.h"

// UITextAtlasTest_Editor
void UITextAtlasTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    
    if (item->getSelectedIndex() == 0){
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.json"));
        
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.csb"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }
}

void UITextAtlasTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
}

bool UITextAtlasTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILabelAtlas_Editor/ui_labelatlas_editor_1.json"));
        _touchGroup->addChild(_layout);
      
        this->configureGUIScene();
        return true;
    }
    
    return false;
}
