

#include "UIScene_Editor.h"
#include "GUIEditorTest.h"
#include "UISceneManager_Editor.h"


UIScene_Editor::UIScene_Editor()
: _sceneTitle(NULL)
, _touchGroup(NULL)
, _layout(NULL)
{
    
}

UIScene_Editor::~UIScene_Editor()
{
    
}

bool UIScene_Editor::init()
{
    if (CCLayer::init())
    {
        _touchGroup = TouchGroup::create();
        addChild(_touchGroup);
        
        
        //add switch
        CCMenuItem* pLoadJsonItem = CCMenuItemFont::create("Switch to Binary Load", this,
                                                           NULL);
        CCMenuItem* pLoadBinaryItem = CCMenuItemFont::create("Switch to Json Load", this, NULL);
        pLoadJsonItem->setTag(1);
        pLoadBinaryItem->setTag(2);
        
        CCArray *array  = CCArray::create();
        array->addObject(pLoadJsonItem);
        array->addObject(pLoadBinaryItem);
        CCMenuItemToggle *pToggleItem = CCMenuItemToggle::createWithTarget(this,
                                                                           menu_selector(UIScene_Editor::switchLoadMethod),
                                                                           array);
        pToggleItem->setPosition(ccp(VisibleRect::right().x - 150, VisibleRect::top().y - 50));;
        
        CCMenu* pMenu =CCMenu::create(pToggleItem, NULL);
        pMenu->setPosition( CCPointZero );
        
        addChild(pMenu, 1);
        
        return true;
    }
    
    return false;
}


void UIScene_Editor::previousCallback(CCObject *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->previousUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::nextCallback(CCObject *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
            CCDirector::sharedDirector()->replaceScene(UISceneManager_Editor::sharedUISceneManager_Editor()->nextUIScene());
            break;
            
        default:
            break;
    }
}

void UIScene_Editor::toGUIEditorTestScene(CCObject *sender, TouchEventType type)
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
