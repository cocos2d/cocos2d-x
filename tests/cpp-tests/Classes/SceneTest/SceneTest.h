#ifndef _SCENE_TEST_H_
#define _SCENE_TEST_H_

////----#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(SceneTests);

class cocos2d::Scene*TestLayer1 : public cocos2d::Layer
{
public:
    CREATE_FUNC(SceneTestLayer1);
    cocos2d::Scene*TestLayer1();
    ~SceneTestLayer1();

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    void testDealloc(float dt);
    void onPushScene(cocos2d::Ref* sender);
    void onPushSceneTran(cocos2d::Ref* sender);
    void onQuit(cocos2d::Ref* sender);
} ;

class cocos2d::Scene*TestLayer2 : public cocos2d::Layer
{
    float    _timeCounter;
public:
    CREATE_FUNC(SceneTestLayer2);
    cocos2d::Scene*TestLayer2();

    void testDealloc(float dt);
    void onGoBack(cocos2d::Ref* sender);
    void onReplaceScene(cocos2d::Ref* sender);
    void onReplaceSceneTran(cocos2d::Ref* sender);
} ;

class cocos2d::Scene*TestLayer3 : public cocos2d::LayerColor
{
public:
    CREATE_FUNC(SceneTestLayer3);
    cocos2d::Scene*TestLayer3();
    bool init();
    virtual void testDealloc(float dt);
    void item0Clicked(cocos2d::Ref* sender);
    void item1Clicked(cocos2d::Ref* sender);
    void item2Clicked(cocos2d::Ref* sender);
    void item3Clicked(cocos2d::Ref* sender);
} ;

class cocos2d::Scene*TestScene : public TestCase
{
public:
    CREATE_FUNC(SceneTestScene);

    virtual bool init() override;
};

#endif
