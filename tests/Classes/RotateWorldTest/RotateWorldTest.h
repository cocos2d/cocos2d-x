#ifndef _ROTATE_WORLD_TEST_H_
#define _ROTATE_WORLD_TEST_H_

#include "../testBasic.h"

class RotateWorldTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class SpriteLayer : public Layer
{
public:
    virtual void onEnter() override;
    CREATE_FUNC(SpriteLayer)
};

class TestLayer : public Layer
{
public:
    virtual void onEnter() override;

    CREATE_FUNC(TestLayer)
};

class RotateWorldMainLayer : public Layer
{
public:
    virtual void onEnter() override;

    CREATE_FUNC(RotateWorldMainLayer)
};

#endif
