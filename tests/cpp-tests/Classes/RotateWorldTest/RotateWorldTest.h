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
