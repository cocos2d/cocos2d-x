#ifndef _SCHEDULER_TEST_H_
#define _SCHEDULER_TEST_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../testBasic.h"

USING_NS_CC_EXT;

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

    void autoremove(float dt);
    void tick(float dt);
private:
    float accum;
};

class SchedulerPauseResume : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void pause(float dt);
};

class SchedulerPauseResumeAll : public SchedulerTestLayer
{
public:
    SchedulerPauseResumeAll();
    virtual ~SchedulerPauseResumeAll();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void pause(float dt);
    void resume(float dt);
private:
    CCSet* m_pPausedTargets;
};

class SchedulerPauseResumeAllUser : public SchedulerTestLayer
{
public:
    SchedulerPauseResumeAllUser();
    virtual ~SchedulerPauseResumeAllUser();
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void pause(float dt);
    void resume(float dt);
private:
    CCSet* m_pPausedTargets;
};

class SchedulerUnscheduleAll : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void tick3(float dt);
    void tick4(float dt);
    void unscheduleAll(float dt);
};

class SchedulerUnscheduleAllHard : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void tick3(float dt);
    void tick4(float dt);
    void unscheduleAll(float dt);
private:
    bool m_bActionManagerActive;
};

class SchedulerUnscheduleAllUserLevel : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void tick3(float dt);
    void tick4(float dt);
    void unscheduleAll(float dt);
};

class SchedulerSchedulesAndRemove : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void tick1(float dt);
    void tick2(float dt);
    void tick3(float dt);
    void tick4(float dt);
    void scheduleAndUnschedule(float dt);
};

class SchedulerUpdate : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void removeUpdates(float dt);
};

class SchedulerUpdateAndCustom : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void update(float dt);
    void tick(float dt);
    void stopSelectors(float dt);
};

class SchedulerUpdateFromCustom : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void update(float dt);
    void schedUpdate(float dt);
    void stopUpdate(float dt);
};

class TestNode : public CCNode
{
public:
    ~TestNode();

    void initWithString(CCString* pStr, int priority);
    virtual void update(float dt);
private:
    CCString* m_pstring;
};

class RescheduleSelector : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void schedUpdate(float dt);
private:
    float m_fInterval;
    int   m_nTicks;
};

class SchedulerDelayAndRepeat : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void update(float dt);
};

class SchedulerTimeScale : public SchedulerTestLayer
{
public:
    void onEnter();
    void onExit();
    virtual std::string title();
    virtual std::string subtitle();
    CCControlSlider* sliderCtl();
    void sliderAction(CCObject* pSender, CCControlEvent controlEvent);
    CCControlSlider* m_pSliderCtl;
};


class TwoSchedulers : public SchedulerTestLayer
{
public:
    virtual ~TwoSchedulers();
    virtual std::string title();
    virtual std::string subtitle();
    void onEnter();
    CCControlSlider* sliderCtl();
    void sliderAction(CCObject* sender, CCControlEvent controlEvent);
    CCScheduler *sched1;
    CCScheduler *sched2;
    CCActionManager *actionManager1;
    CCActionManager *actionManager2;

    CCControlSlider    *sliderCtl1;
    CCControlSlider    *sliderCtl2;
};

class SchedulerIssue2268 : public SchedulerTestLayer
{
	public:
		~SchedulerIssue2268();
		std::string title();
		std::string subtitle();
		void onEnter();
		void update(float dt);
	private:
		CCNode *testNode;
};

class SchedulerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
