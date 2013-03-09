#ifndef _ACTIONS__PROGRESS_TEST_H_
#define _ACTIONS_PROGRESS_TEST_H_

#include "../testBasic.h"

class SpriteDemo : public CCLayer
{
public:
    SpriteDemo(void);
    ~SpriteDemo(void);

    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class SpriteProgressToRadial : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressToHorizontal : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressToVertical : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressToRadialMidpointChanged : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressBarVarious : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressBarTintAndFade : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class SpriteProgressWithSpriteFrame : public SpriteDemo
{
public:
    virtual void onEnter();
    virtual std::string subtitle();
};

class ProgressActionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
