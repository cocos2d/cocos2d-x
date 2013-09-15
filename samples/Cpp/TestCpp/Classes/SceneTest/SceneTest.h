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
    void onPushScene(Object* sender);
    void onPushSceneTran(Object* sender);
    void onQuit(Object* sender);

    //CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public Layer
{
    float    _timeCounter;
public:
    SceneTestLayer2();

    void testDealloc(float dt);
    void onGoBack(Object* sender);
    void onReplaceScene(Object* sender);
    void onReplaceSceneTran(Object* sender);

    //CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public LayerColor
{
public:
    SceneTestLayer3();
    bool init();
    virtual void testDealloc(float dt);
    void item0Clicked(Object* sender);
    void item1Clicked(Object* sender);
    void item2Clicked(Object* sender);
    void item3Clicked(Object* sender);
    CREATE_FUNC(SceneTestLayer3)
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
