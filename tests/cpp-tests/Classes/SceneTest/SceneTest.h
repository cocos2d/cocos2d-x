#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../testBasic.h"

class SceneTestLayer1 : public Layer
{
public:
    SceneTestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;

    void testDealloc(float dt);
    void onPushScene(Ref* sender);
    void onPushSceneTran(Ref* sender);
    void onQuit(Ref* sender);

    //CREATE_NODE(SceneTestLayer1);
} ;

class SceneTestLayer2 : public Layer
{
    float    _timeCounter;
public:
    SceneTestLayer2();
    virtual void onExit() override;
    void testDealloc(float dt);
    void onGoBack(Ref* sender);
    void onReplaceScene(Ref* sender);
    void onReplaceSceneTran(Ref* sender);

    //CREATE_NODE(SceneTestLayer2);
} ;

class SceneTestLayer3 : public LayerColor
{
public:
    SceneTestLayer3();
    bool init();
    virtual void onExit() override;
    virtual void testDealloc(float dt);
    virtual void cleanup() override;

    void item0Clicked(Ref* sender);
    void item1Clicked(Ref* sender);
    void item2Clicked(Ref* sender);
    void item3Clicked(Ref* sender);
    CREATE_FUNC(SceneTestLayer3)
} ;

class SceneTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
