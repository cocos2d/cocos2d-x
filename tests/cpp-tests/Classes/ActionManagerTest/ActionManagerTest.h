#ifndef _ACTION_MANAGER_TEST_H_
#define _ACTION_MANAGER_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class ActionManagerTest: public BaseTest
{
protected:
    TextureAtlas* _atlas;

    std::string    _title;

public:
    ActionManagerTest(void);
    ~ActionManagerTest(void);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};

class CrashTest : public ActionManagerTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void removeThis();
};

class LogicTest : public ActionManagerTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void bugMe(Node* node);
};

class PauseTest : public ActionManagerTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void unpause(float dt);
};

class StopActionTest : public ActionManagerTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void stopAction();
};

class ResumeTest : public ActionManagerTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
    void resumeGrossini(float time);
};

class ActionManagerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
