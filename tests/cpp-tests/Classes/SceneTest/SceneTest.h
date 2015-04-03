#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(SceneTests);

class SceneTestLayer1 : public Layer
{
public:
    CREATE_FUNC(SceneTestLayer1);
    SceneTestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    void testDealloc(float dt);
    void onPushScene(Ref* sender);
    void onPushSceneTran(Ref* sender);
    void onQuit(Ref* sender);
} ;

class SceneTestLayer2 : public Layer
{
    float    _timeCounter;
public:
    CREATE_FUNC(SceneTestLayer2);
    SceneTestLayer2();

    void testDealloc(float dt);
    void onGoBack(Ref* sender);
    void onReplaceScene(Ref* sender);
    void onReplaceSceneTran(Ref* sender);
} ;

class SceneTestLayer3 : public LayerColor
{
public:
    CREATE_FUNC(SceneTestLayer3);
    SceneTestLayer3();
    bool init();
    virtual void testDealloc(float dt);
    void item0Clicked(Ref* sender);
    void item1Clicked(Ref* sender);
    void item2Clicked(Ref* sender);
    void item3Clicked(Ref* sender);
} ;

class SceneTestScene : public TestCase
{
public:
    CREATE_FUNC(SceneTestScene);

    virtual bool init() override;
};

#endif
