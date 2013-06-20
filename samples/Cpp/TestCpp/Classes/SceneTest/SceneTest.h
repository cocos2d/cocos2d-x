#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class SceneTestLayer1 : public Layer
{
public:
    SceneTestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();

    void testDealloc(float dt);
    void onPushScene(Object* pSender);
    void onPushSceneTran(Object* pSender);
    void onQuit(Object* pSender);

    //CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public Layer
{
    float    _timeCounter;
public:
    SceneTestLayer2();

    void testDealloc(float dt);
    void onGoBack(Object* pSender);
    void onReplaceScene(Object* pSender);
    void onReplaceSceneTran(Object* pSender);

    //CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public LayerColor
{
public:
    SceneTestLayer3();
    bool init();
    virtual void testDealloc(float dt);
    void item0Clicked(Object* pSender);
    void item1Clicked(Object* pSender);
    void item2Clicked(Object* pSender);
    void item3Clicked(Object* pSender);
    CREATE_FUNC(SceneTestLayer3)
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
