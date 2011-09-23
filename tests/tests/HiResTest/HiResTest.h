#ifndef _HIRES_TEST_H_
#define _HIRES_TEST_H_

#include "../testBasic.h"

class HiResDemo : public CCLayer
{
public:
    virtual std::string title();
    virtual std::string subtitle();
    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
};

class HiResTest1 : public HiResDemo
{
public:
    virtual void onEnter();

    virtual std::string title();
    virtual std::string subtitle();
};

class HiResTest2 : public HiResDemo
{
public:
    virtual void onEnter();

    virtual std::string title();
    virtual std::string subtitle();
};

class HiResTestScene : public TestScene
{
public:
    virtual void runThisTest();
    virtual void MainMenuCallback(CCObject* pSender);

    static bool sm_bRitinaDisplay;
};

#endif
