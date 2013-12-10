#ifndef _SCHEDULER_TEST_H_
#define _SCHEDULER_TEST_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
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
    CREATE_FUNC(SchedulerAutoremove);

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
    CREATE_FUNC(SchedulerPauseResume);

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
    CREATE_FUNC(SchedulerPauseResumeAll);

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
    Vector<Object*> _pausedTargets;
};

class SchedulerPauseResumeAllUser : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerPauseResumeAllUser);

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
    Vector<Object*> _pausedTargets;
};

class SchedulerUnscheduleAll : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerUnscheduleAll);

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
    CREATE_FUNC(SchedulerUnscheduleAllHard);

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
    CREATE_FUNC(SchedulerUnscheduleAllUserLevel);

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
    CREATE_FUNC(SchedulerSchedulesAndRemove);

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
    CREATE_FUNC(SchedulerUpdate);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();

    void removeUpdates(float dt);
};

class SchedulerUpdateAndCustom : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerUpdateAndCustom);

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
    CREATE_FUNC(SchedulerUpdateFromCustom);

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
    CREATE_FUNC(TestNode);

    ~TestNode();

    void initWithString(String* pStr, int priority);
    virtual void update(float dt);
private:
    String* _pstring;
};

class RescheduleSelector : public SchedulerTestLayer
{
public:
    CREATE_FUNC(RescheduleSelector);

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
    CREATE_FUNC(SchedulerDelayAndRepeat);

    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    void update(float dt);
};

class SchedulerTimeScale : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerTimeScale);

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
    CREATE_FUNC(TwoSchedulers);

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
    CREATE_FUNC(SchedulerIssue2268);

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
    CREATE_FUNC(SchedulerTestScene);

    virtual void runThisTest();
};

#endif
