#ifndef _ACTION_MANAGER_TEST_H_
#define _ACTION_MANAGER_TEST_H_

#include "../BaseTest.h"

DEFINE_TEST_SUITE(ActionManagerTests);

class ActionManagerTest : public TestCase
{
protected:
    cocos2d::TextureAtlas* _atlas;

    std::string    _title;

public:
    ActionManagerTest();
    ~ActionManagerTest();

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CrashTest : public ActionManagerTest
{
public:
    CREATE_FUNC(CrashTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

class LogicTest : public ActionManagerTest
{
public:
    CREATE_FUNC(LogicTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void bugMe(Node* node);
};

class PauseTest : public ActionManagerTest
{
public:
    CREATE_FUNC(PauseTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void unpause(float dt);
};

class StopActionTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopActionTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction();
};

class StopAllActionsTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopAllActionsTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction(float time);
};

class ResumeTest : public ActionManagerTest
{
public:
    CREATE_FUNC(ResumeTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void resumeGrossini(float time);
};

#endif
