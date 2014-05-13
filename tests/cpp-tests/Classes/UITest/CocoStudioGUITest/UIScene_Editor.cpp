

#include "UIScene_Editor.h"
#include "GUIEditorTest.h"
#include "ui/CocosGUI.h"
#include "UISceneManager_Editor.h"


UIScene_Editor::UIScene_Editor()
: _sceneTitle(nullptr)
, _touchGroup(nullptr)
, _layout(nullptr)
{
    
}

UIScene_Editor::~UIScene_Editor()
{
    
}

bool UIScene_Editor::init()
{
    if (CCLayer::init())
    {
        _touchGroup = Layer::create();
        addChild(_touchGroup);                
        
        return true;
    }
    
    return false;
}

void UIScene_Editor::previousCallback(Ref *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::getInstance()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->previousUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::nextCallback(Ref *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::getInstance()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->nextUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::toGUIEditorTestScene(Ref *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
        {
            UISceneManager_Editor::sharedUISceneManager_Editor()->purge();
            
            GUIEditorTestScene* pScene = new GUIEditorTestScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
            
        default:
            break;
    }
}
