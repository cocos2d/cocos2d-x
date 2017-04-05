#ifndef _ROTATE_WORLD_TEST_H_
#define _ROTATE_WORLD_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(RotateWorldTests);

class RotateWorldTest : public TestCase
{
public:
    CREATE_FUNC(RotateWorldTest);

    virtual bool init() override;
};

class SpriteLayer : public cocos2d::Layer
{
public:
    virtual void onEnter() override;
    CREATE_FUNC(SpriteLayer)
};

class TestLayer : public cocos2d::Layer
{
public:
    virtual void onEnter() override;

    CREATE_FUNC(TestLayer)
};

class RotateWorldMainLayer : public cocos2d::Layer
{
public:
    virtual void onEnter() override;

    CREATE_FUNC(RotateWorldMainLayer)
};

#endif
