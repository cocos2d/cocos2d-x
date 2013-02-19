#ifndef _ROTATE_WORLD_TEST_H_
#define _ROTATE_WORLD_TEST_H_

#include "../testBasic.h"

class RotateWorldTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class SpriteLayer : public CCLayer
{
public:
    virtual void onEnter();
    CREATE_FUNC(SpriteLayer)
};

class TestLayer : public CCLayer
{
public:
    virtual void onEnter();

    CREATE_FUNC(TestLayer)
};

class RotateWorldMainLayer : public CCLayer
{
public:
    virtual void onEnter();

    CREATE_FUNC(RotateWorldMainLayer)
};

#endif
