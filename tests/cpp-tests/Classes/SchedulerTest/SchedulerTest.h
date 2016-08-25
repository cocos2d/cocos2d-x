#ifndef _SCHEDULER_TEST_H_
#define _SCHEDULER_TEST_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../BaseTest.h"


DEFINE_TEST_SUITE(SchedulerTests);

class SchedulerTestLayer : public TestCase
{
public:
};

class SchedulerAutoremove : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerAutoremove);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void autoremove(float dt);
    void tick(float dt);
private:
    float accum;
};

class SchedulerPauseResume : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerPauseResume);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void tick1(float dt);
    void tick2(float dt);
    using SchedulerTestLayer::pause;
    void pause(float dt);
};

class SchedulerPauseResumeAll : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerPauseResumeAll);

    SchedulerPauseResumeAll();
    virtual ~SchedulerPauseResumeAll();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float delta) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void tick1(float dt);
    void tick2(float dt);
    using SchedulerTestLayer::pause;
    void pause(float dt);
    using SchedulerTestLayer::resume;
    void resume(float dt);
private:
    std::set<void*> _pausedTargets;
};

class SchedulerPauseResumeAllUser : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerPauseResumeAllUser);

    SchedulerPauseResumeAllUser();
    virtual ~SchedulerPauseResumeAllUser();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void tick1(float dt);
    void tick2(float dt);
    using SchedulerTestLayer::pause;
    void pause(float dt);
    using SchedulerTestLayer::resume;
    void resume(float dt);
private:
    std::set<void*> _pausedTargets;
};

class SchedulerUnscheduleAll : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerUnscheduleAll);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

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

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

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

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

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

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

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

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void removeUpdates(float dt);
};

class SchedulerUpdateAndCustom : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerUpdateAndCustom);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void update(float dt) override;
    void tick(float dt);
    void stopSelectors(float dt);
};

class SchedulerUpdateFromCustom : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerUpdateFromCustom);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void update(float dt) override;
    void schedUpdate(float dt);
    void stopUpdate(float dt);
};

class TestNode : public cocos2d::Node
{
public:
    CREATE_FUNC(TestNode);

    ~TestNode();

    void initWithString(const std::string& str, int priority);
    virtual void update(float dt) override;
private:
    std::string _string;
};

class RescheduleSelector : public SchedulerTestLayer
{
public:
    CREATE_FUNC(RescheduleSelector);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void schedUpdate(float dt);
private:
    float _interval;
    int   _ticks;
};

class SchedulerDelayAndRepeat : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerDelayAndRepeat);

    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void update(float dt) override;
};

class SchedulerTimeScale : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerTimeScale);

    void onEnter() override;
    void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    cocos2d::extension::ControlSlider* sliderCtl();
    void sliderAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    cocos2d::extension::ControlSlider* _sliderCtl;
};


class TwoSchedulers : public SchedulerTestLayer
{
public:
    CREATE_FUNC(TwoSchedulers);

    virtual ~TwoSchedulers();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onEnter() override;
    cocos2d::extension::ControlSlider* sliderCtl();
    void sliderAction(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    cocos2d::Scheduler* sched1;
    cocos2d::Scheduler* sched2;
    cocos2d::ActionManager* actionManager1;
    cocos2d::ActionManager* actionManager2;

    cocos2d::extension::ControlSlider* sliderCtl1;
    cocos2d::extension::ControlSlider* sliderCtl2;
};

class SchedulerIssue2268 : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerIssue2268);

    ~SchedulerIssue2268();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onEnter() override;
    void update(float dt) override;

private:
    cocos2d::Node* testNode;
};

class ScheduleCallbackTest : public SchedulerTestLayer
{
public:
    CREATE_FUNC(ScheduleCallbackTest);
    
    ~ScheduleCallbackTest();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onEnter() override;
    
    void callback(float dt);
    
private:
};

class ScheduleUpdatePriority : public SchedulerTestLayer
{
public:
    CREATE_FUNC(ScheduleUpdatePriority);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void onEnter() override;
    void onExit() override;
    
    virtual void update(float dt) override;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};

class SchedulerIssue10232 : public SchedulerTestLayer
{
public:
    CREATE_FUNC(SchedulerIssue10232);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;

    void onEnter() override;
    void update(float dt) override;
};

#endif
