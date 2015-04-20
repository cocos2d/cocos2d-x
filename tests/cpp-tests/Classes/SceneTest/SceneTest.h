#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(SceneTests);

class SceneTestLayer1 : public cocos2d::Layer
{
public:
    CREATE_FUNC(SceneTestLayer1);

    SceneTestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    void testDealloc(float dt);
    void onPushScene(cocos2d::Ref* sender);
    void onPushSceneTran(cocos2d::Ref* sender);
    void onQuit(cocos2d::Ref* sender);
} ;

class SceneTestLayer2 : public cocos2d::Layer
{
    float    _timeCounter;
public:
    CREATE_FUNC(SceneTestLayer2);

    SceneTestLayer2();

    void testDealloc(float dt);
    void onGoBack(cocos2d::Ref* sender);
    void onReplaceScene(cocos2d::Ref* sender);
    void onReplaceSceneTran(cocos2d::Ref* sender);
} ;

class SceneTestLayer3 : public cocos2d::LayerColor
{
public:
    CREATE_FUNC(SceneTestLayer3);

    SceneTestLayer3();

    virtual bool init() override;
    virtual void testDealloc(float dt);
    void item0Clicked(cocos2d::Ref* sender);
    void item1Clicked(cocos2d::Ref* sender);
    void item2Clicked(cocos2d::Ref* sender);
    void item3Clicked(cocos2d::Ref* sender);
} ;

class SceneTestScene : public TestCase
{
public:
    static SceneTestScene* create(int testIndex = 1);
};

#endif
