

#include "UILoadingBarTest_Editor.h"


// UILoadingBarTest_Editor

UILoadingBarTest_Editor::UILoadingBarTest_Editor()
:_count(0)
{
    
}

UILoadingBarTest_Editor::~UILoadingBarTest_Editor()
{
    
}

void UILoadingBarTest_Editor::switchLoadMethod(cocos2d::Ref *pSender)
{
    MenuItemToggle *item = (MenuItemToggle*)pSender;
    _count = 0;
    
    if (item->getSelectedIndex() == 0){
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.csb"));
        _touchGroup->addChild(_layout);
        
        this->configureGUIScene();
    }
}

void UILoadingBarTest_Editor::configureGUIScene()
{
    Size screenSize = CCDirector::getInstance()->getWinSize();
    Size rootSize = _layout->getContentSize();
    _touchGroup->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
                                  (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_layout->getChildByName("root_Panel"));
    
    Text* back_label = static_cast<Text*>(Helper::seekWidgetByName(root, "back"));
    //        back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    back_label->addTouchEventListener(CC_CALLBACK_2(UIScene_Editor::toGUIEditorTestScene, this));
    
    _sceneTitle = static_cast<Text*>(Helper::seekWidgetByName(root, "UItest"));
    
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
        
        _layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json"));
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

void UILoadingBarTest_Editor::toCocosGUITestScene(Ref* sender, Widget::TouchEventType event)
{
    switch (event)
    {
        case Widget::TouchEventType::ENDED:
        {
            unscheduleUpdate();
            
            UIScene_Editor::toGUIEditorTestScene(sender, event);
        }
            break;
            
        default:
            break;
    }
}
