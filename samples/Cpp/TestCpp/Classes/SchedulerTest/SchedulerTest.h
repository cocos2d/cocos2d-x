#ifndef _SCHEDULER_TEST_H_
#define _SCHEDULER_TEST_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../testBasic.h"
#include "../BaseTest.h"

USING_NS_CC_EXT;

class SchedulerTestLayer : public BaseTest
{
public:
    virtual void onEnter();

    virtual std::string title();
    virtual std::string subtitle();

    void backCallback(Object* sender);
    void nextCallback(Object* sender);
    void restartCallback(Object* sender);
};

// class SchedulerTestLayer : Layer
// {
// }
// -(String*) title;
// -(String*) subtitle;
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
    Set* _pausedTargets;
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
    Set* _pausedTargets;
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
    bool _actionManagerActive;
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

class TestNode : public Node
{
public:
    ~TestNode();

    void initWithString(String* pStr, int priority);
    virtual void update(float dt);
private:
    String* _pstring;
};

class RescheduleSelector : public SchedulerTestLayer
{
public:
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void schedUpdate(float dt);
private:
    float _interval;
    int   _ticks;
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
    ControlSlider* sliderCtl();
    void sliderAction(Object* sender, Control::EventType controlEvent);
    ControlSlider* _sliderCtl;
};


class TwoSchedulers : public SchedulerTestLayer
{
public:
    virtual ~TwoSchedulers();
    virtual std::string title();
    virtual std::string subtitle();
    void onEnter();
    ControlSlider* sliderCtl();
    void sliderAction(Object* sender, Control::EventType controlEvent);
    Scheduler *sched1;
    Scheduler *sched2;
    ActionManager *actionManager1;
    ActionManager *actionManager2;

    ControlSlider    *sliderCtl1;
    ControlSlider    *sliderCtl2;
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
		Node *testNode;
};

class SchedulerTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
