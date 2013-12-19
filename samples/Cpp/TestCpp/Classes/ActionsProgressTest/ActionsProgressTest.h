#ifndef _ACTIONS__PROGRESS_TEST_H_
#define _ACTIONS_PROGRESS_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class SpriteDemo : public BaseTest
{
public:
    SpriteDemo(void);
    ~SpriteDemo(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onEnter();

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class SpriteProgressToRadial : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressToHorizontal : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressToVertical : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressToRadialMidpointChanged : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressBarVarious : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressBarTintAndFade : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class SpriteProgressWithSpriteFrame : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle() const override;
};

class ProgressActionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
