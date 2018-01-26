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

class StopActionsByFlagsTest : public ActionManagerTest
{
public:
    CREATE_FUNC(StopActionsByFlagsTest);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction(float time);
protected:
    const unsigned int kMoveFlag = 0x01;
    const unsigned int kScaleFlag = 0x02;
    const unsigned int kRotateFlag = 0x04;
    const unsigned int kRepeatForeverFlag = 0x08; // You don't need this for the test, but it's for demonstration how to activate several flags on an action.
};

class Issue14050Test : public ActionManagerTest
{
public:
    CREATE_FUNC(Issue14050Test);

    virtual std::string subtitle() const override;
    virtual void onEnter() override;
protected:
};

#endif
