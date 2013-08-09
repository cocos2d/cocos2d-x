

#ifndef __TestCpp__UIScene__
#define __TestCpp__UIScene__

#include "cocos2d.h"
#include "CocoGUILIB/System/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define UI_SCENE_CREATE_FUNC(UIScene) \
public: \
static CCScene* sceneWithTitle(const char * title) \
{ \
    CCScene* pScene = CCScene::create(); \
    UIScene* uiLayer = new UIScene(); \
    if (uiLayer && uiLayer->init()) \
    { \
        uiLayer->autorelease(); \
        uiLayer->getSceneTitle()->setText(title); \
        pScene->addChild(uiLayer); \
    } \
    else \
    { \
        CC_SAFE_DELETE(uiLayer); \
    } \
    return pScene; \
}

//#define UI_SCENE_CREATE_FUNC(UIScene) \
//public: \
//static CCScene* sceneWithTitle(const char * title) \
//{ \
//    CCScene* pScene = CCScene::create(); \
//    UIScene* uiLayer = new UIScene(); \
//    if (uiLayer && uiLayer->init()) \
//    { \
//        uiLayer->autorelease(); \
//        uiLayer->getSceneTitleLabel()->setString(title); \
//        pScene->addChild(uiLayer); \
//    } \
//    else \
//    { \
//        CC_SAFE_DELETE(uiLayer); \
//    } \
//    return pScene; \
//}

class UIScene : public CCLayer
{
public:
    UIScene();
    ~UIScene();
    bool init();
    // Menu Callbacks
    void toExtensionsMainLayer(CCObject* sender);
    void previousCallback(CCObject* sender);
    void restartCallback(CCObject* sender);
    void nextCallback(CCObject* sender);
    
    /** Title label of the scene. */
//    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pSceneTitleLabel, SceneTitleLabel)
    
    CC_SYNTHESIZE_READONLY(UILabel*, m_pSceneTitle, SceneTitle)
    
    UI_SCENE_CREATE_FUNC(UIScene);
    
protected:
    UILayer *m_pUiLayer;
    UIWidget *m_pWidget;
};

#endif /* defined(__TestCpp__UIScene__) */
