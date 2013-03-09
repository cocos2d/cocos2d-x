#ifndef _ACTION_MANAGER_TEST_H_
#define _ACTION_MANAGER_TEST_H_

#include "../testBasic.h"

class ActionManagerTest: public CCLayer
{
protected:
    CCTextureAtlas* m_atlas;

    std::string    m_strTitle;

public:
    ActionManagerTest(void);
    ~ActionManagerTest(void);

    virtual std::string title();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class CrashTest : public ActionManagerTest
{
public:
    virtual std::string title();
    virtual void onEnter();
    void removeThis();
};

class LogicTest : public ActionManagerTest
{
public:
    virtual std::string title();
    virtual void onEnter();
    void bugMe(CCNode* node);
};

class PauseTest : public ActionManagerTest
{
public:
    virtual std::string title();
    virtual void onEnter();
    void unpause(float dt);
};

class RemoveTest : public ActionManagerTest
{
public:
    virtual std::string title();
    virtual void onEnter();
    void stopAction();
};

class ResumeTest : public ActionManagerTest
{
public:
    virtual std::string title();
    virtual void onEnter();
    void resumeGrossini(float time);
};

class ActionManagerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
