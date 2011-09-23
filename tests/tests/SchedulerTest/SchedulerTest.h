#ifndef _SCHEDULER_TEST_H_
#define _SCHEDULER_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
//#import "cocos2d.h"


class SchedulerTestLayer : public CCLayer
{
public:
    virtual void onEnter();

    virtual std::string title();
    virtual std::string subtitle();

    void backCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void restartCallback(CCObject* pSender);
};

// class SchedulerTestLayer : CCLayer
// {
// }
// -(CCString*) title;
// -(CCString*) subtitle;
// 
// -(void) backCallback:(id) sender;
// -(void) nextCallback:(id) sender;
// -(void) restartCallback:(id) sender;
// 

class SchedulerAutoremove : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void autoremove(ccTime dt);
    void tick(ccTime dt);
private:
	ccTime accum;
};

class SchedulerPauseResume : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(ccTime dt);
    void tick2(ccTime dt);
    void pause(ccTime dt);
};

class SchedulerUnscheduleAll : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(ccTime dt);
    void tick2(ccTime dt);
    void tick3(ccTime dt);
    void tick4(ccTime dt);
    void unscheduleAll(ccTime dt);
};

class SchedulerUnscheduleAllHard : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(ccTime dt);
    void tick2(ccTime dt);
    void tick3(ccTime dt);
    void tick4(ccTime dt);
    void unscheduleAll(ccTime dt);
};

class SchedulerSchedulesAndRemove : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(ccTime dt);
    void tick2(ccTime dt);
    void tick3(ccTime dt);
    void tick4(ccTime dt);
    void scheduleAndUnschedule(ccTime dt);
};

class SchedulerUpdate : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void removeUpdates(ccTime dt);
};

class SchedulerUpdateAndCustom : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void update(ccTime dt);
    void tick(ccTime dt);
    void stopSelectors(ccTime dt);
};

class SchedulerUpdateFromCustom : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void update(ccTime dt);
    void schedUpdate(ccTime dt);
    void stopUpdate(ccTime dt);
};

class TestNode : public CCNode
{
public:
    ~TestNode();

    void initWithString(CCString* pStr, int priority);
private:
    CCString* m_pstring;
};

class RescheduleSelector : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void schedUpdate(ccTime dt);
private:
    float m_fInterval;
    int   m_nTicks;
};

class SchedulerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
