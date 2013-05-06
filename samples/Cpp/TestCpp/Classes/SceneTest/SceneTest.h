#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class SceneTestLayer1 : public CCLayer
{
public:
    SceneTestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();

    void testDealloc(float dt);
    void onPushScene(CCObject* pSender);
    void onPushSceneTran(CCObject* pSender);
    void onQuit(CCObject* pSender);

    //CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public CCLayer
{
    float    m_timeCounter;
public:
    SceneTestLayer2();

    void testDealloc(float dt);
    void onGoBack(CCObject* pSender);
    void onReplaceScene(CCObject* pSender);
    void onReplaceSceneTran(CCObject* pSender);

    //CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public CCLayerColor
{
public:
    SceneTestLayer3();
    bool init();
    virtual void testDealloc(float dt);
    void item0Clicked(CCObject* pSender);
    void item1Clicked(CCObject* pSender);
    void item2Clicked(CCObject* pSender);
    void item3Clicked(CCObject* pSender);
    CREATE_FUNC(SceneTestLayer3)
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
