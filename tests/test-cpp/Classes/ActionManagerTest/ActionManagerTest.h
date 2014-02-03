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

    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
};

class CrashTest : public ActionManagerTest
{
public:
    virtual std::string title() const override;
    virtual void onEnter();
    void removeThis();
};

class LogicTest : public ActionManagerTest
{
public:
    virtual std::string title() const override;
    virtual void onEnter();
    void bugMe(Node* node);
};

class PauseTest : public ActionManagerTest
{
public:
    virtual std::string title() const override;
    virtual void onEnter();
    void unpause(float dt);
};

class RemoveTest : public ActionManagerTest
{
public:
    virtual std::string title() const override;
    virtual void onEnter();
    void stopAction();
};

class ResumeTest : public ActionManagerTest
{
public:
    virtual std::string title() const override;
    virtual void onEnter();
    void resumeGrossini(float time);
};

class ActionManagerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
