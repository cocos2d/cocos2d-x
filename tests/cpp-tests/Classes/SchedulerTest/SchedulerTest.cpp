#include "SchedulerTest.h"
#include "../testResource.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum {
    kTagAnimationDance = 1,
};

SchedulerTests::SchedulerTests()
{
    ADD_TEST_CASE(SchedulerTimeScale);
    ADD_TEST_CASE(TwoSchedulers);
    ADD_TEST_CASE(SchedulerAutoremove);
    ADD_TEST_CASE(SchedulerPauseResume);
    ADD_TEST_CASE(SchedulerPauseResumeAll);
    ADD_TEST_CASE(SchedulerPauseResumeAllUser);
    ADD_TEST_CASE(SchedulerUnscheduleAll);
    ADD_TEST_CASE(SchedulerUnscheduleAllHard);
    ADD_TEST_CASE(SchedulerUnscheduleAllUserLevel);
    ADD_TEST_CASE(SchedulerSchedulesAndRemove);
    ADD_TEST_CASE(SchedulerUpdate);
    ADD_TEST_CASE(SchedulerUpdateAndCustom);
    ADD_TEST_CASE(SchedulerUpdateFromCustom);
    ADD_TEST_CASE(RescheduleSelector);
    ADD_TEST_CASE(SchedulerDelayAndRepeat);
    ADD_TEST_CASE(SchedulerIssue2268);
    ADD_TEST_CASE(ScheduleCallbackTest);
    ADD_TEST_CASE(ScheduleUpdatePriority);
    ADD_TEST_CASE(SchedulerIssue10232);
};

//------------------------------------------------------------------
//
// SchedulerAutoremove
//
//------------------------------------------------------------------
void SchedulerAutoremove::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(CC_SCHEDULE_SELECTOR(SchedulerAutoremove::autoremove), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerAutoremove::tick), 0.5f);
    accum = 0;
}

void SchedulerAutoremove::autoremove(float dt)
{
    accum += dt;
    CCLOG("Time: %f", accum);

    if( accum > 3 )
    {
        unschedule(CC_SCHEDULE_SELECTOR(SchedulerAutoremove::autoremove));
        CCLOG("scheduler removed");
    }
}

void SchedulerAutoremove::tick(float dt)
{
    CCLOG("This scheduler should not be removed");
}

std::string SchedulerAutoremove::title() const
{
    return "Self-remove an scheduler";
}

std::string SchedulerAutoremove::subtitle() const
{
    return "1 scheduler will be autoremoved in 3 seconds. See console";
}

//------------------------------------------------------------------
//
// SchedulerPauseResume
//
//------------------------------------------------------------------
void SchedulerPauseResume::onEnter()
{
    SchedulerTestLayer::onEnter();
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResume::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResume::tick2), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResume::pause), 3.0f);
}

void SchedulerPauseResume::tick1(float dt)
{
    CCLOG("tick1");
}

void SchedulerPauseResume::tick2(float dt)
{
    CCLOG("tick2");
}

void SchedulerPauseResume::pause(float dt)
{
    CCLOG("paused, tick1 and tick2 should called six times");
    Director::getInstance()->getScheduler()->pauseTarget(this);
}

std::string SchedulerPauseResume::title() const
{
    return "Pause / Resume";
}

std::string SchedulerPauseResume::subtitle() const
{
    return "Scheduler should be paused after 3 seconds. See console";
}

//------------------------------------------------------------------
//
// SchedulerPauseResumeAll
//
//------------------------------------------------------------------

SchedulerPauseResumeAll::SchedulerPauseResumeAll()
{
    
}

SchedulerPauseResumeAll::~SchedulerPauseResumeAll()
{

}

void SchedulerPauseResumeAll::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(VisibleRect::center());
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));
    sprite->setTag(123);
    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAll::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAll::tick2), 1.0f);
    scheduleOnce(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAll::pause), 3.0f);
}

void SchedulerPauseResumeAll::update(float delta)
{
    // do nothing
}

void SchedulerPauseResumeAll::onExit()
{
    if (!_pausedTargets.empty())
    {
        Director::getInstance()->getScheduler()->resumeTargets(_pausedTargets);
    }
    SchedulerTestLayer::onExit();
}

void SchedulerPauseResumeAll::tick1(float dt)
{
    log("tick1");
}

void SchedulerPauseResumeAll::tick2(float dt)
{
    log("tick2");
}

void SchedulerPauseResumeAll::pause(float dt)
{
    log("Pausing, tick1 should be called six times and tick2 three times");
    auto scheduler = Director::getInstance()->getScheduler();
    _pausedTargets = scheduler->pauseAllTargets();

    // should have only 2 items: ActionManager, self
    CCASSERT(_pausedTargets.size() == 2, "Error: pausedTargets should have only 2 items");
    
    // because target 'this' has been paused above, so use another node(tag:123) as target
    getChildByTag(123)->scheduleOnce([this](float dt)
                                     {
                                         this->resume(dt);
                                     }, 2.0f, "test resume");
}

void SchedulerPauseResumeAll::resume(float dt)
{
    log("Resuming");
    auto director = Director::getInstance();
    director->getScheduler()->resumeTargets(_pausedTargets);
    _pausedTargets.clear();
}

std::string SchedulerPauseResumeAll::title() const
{
    return "Pause / Resume All";
}

std::string SchedulerPauseResumeAll::subtitle() const
{
    return "Everything will pause after 3s, then resume at 5s. See console";
}

//------------------------------------------------------------------
//
// SchedulerPauseResumeAllUser
//
//------------------------------------------------------------------

SchedulerPauseResumeAllUser::SchedulerPauseResumeAllUser()
{

}

SchedulerPauseResumeAllUser::~SchedulerPauseResumeAllUser()
{

}

void SchedulerPauseResumeAllUser::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    sprite->setTag(123);
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAllUser::tick1), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAllUser::tick2), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerPauseResumeAllUser::pause), 3.0f, false, 0);
}

void SchedulerPauseResumeAllUser::onExit()
{
    if (!_pausedTargets.empty())
    {
        Director::getInstance()->getScheduler()->resumeTargets(_pausedTargets);
    }
    SchedulerTestLayer::onExit();
}

void SchedulerPauseResumeAllUser::tick1(float dt)
{
    log("tick1");
}

void SchedulerPauseResumeAllUser::tick2(float dt)
{
    log("tick2");
}

void SchedulerPauseResumeAllUser::pause(float dt)
{
    log("Pausing, tick1 and tick2 should be called three times");
    auto director = Director::getInstance();
    _pausedTargets = director->getScheduler()->pauseAllTargetsWithMinPriority(Scheduler::PRIORITY_NON_SYSTEM_MIN);
    // because target 'this' has been paused above, so use another node(tag:123) as target
    getChildByTag(123)->scheduleOnce([this](float dt)
                                     {
                                         this->resume(dt);
                                     }, 2.0f, "test resume");
}

void SchedulerPauseResumeAllUser::resume(float dt)
{
    log("Resuming");
    getScheduler()->resumeTargets(_pausedTargets);
    _pausedTargets.clear();
}

std::string SchedulerPauseResumeAllUser::title() const
{
    return "Pause / Resume All User scheduler";
}

std::string SchedulerPauseResumeAllUser::subtitle() const
{
    return "ticks will pause after 3s, then resume at 5s. See console";
}


//------------------------------------------------------------------
//
// SchedulerUnscheduleAll
//
//------------------------------------------------------------------
void SchedulerUnscheduleAll::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAll::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAll::tick2), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAll::tick3), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAll::tick4), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAll::unscheduleAll), 4);
}

void SchedulerUnscheduleAll::tick1(float dt)
{
    CCLOG("tick1");
}

void SchedulerUnscheduleAll::tick2(float dt)
{
    CCLOG("tick2");
}

void SchedulerUnscheduleAll::tick3(float dt)
{
    CCLOG("tick3");
}

void SchedulerUnscheduleAll::tick4(float dt)
{
    CCLOG("tick4");
}

void SchedulerUnscheduleAll::unscheduleAll(float dt)
{
    unscheduleAllCallbacks();
}

std::string SchedulerUnscheduleAll::title() const
{
    return "Unschedule All selectors";
}

std::string SchedulerUnscheduleAll::subtitle() const
{
    return "All scheduled selectors will be unscheduled in 4 seconds. See console";
}

//------------------------------------------------------------------
//
// SchedulerUnscheduleAllHard
//
//------------------------------------------------------------------
void SchedulerUnscheduleAllHard::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    _actionManagerActive = true;

    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllHard::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllHard::tick2), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllHard::tick3), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllHard::tick4), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllHard::unscheduleAll), 4);
}

void SchedulerUnscheduleAllHard::onExit()
{
    if(!_actionManagerActive) {
        // Restore the director's action manager.
        auto director = Director::getInstance();
        director->getScheduler()->scheduleUpdate(director->getActionManager(), Scheduler::PRIORITY_SYSTEM, false);
    }
    
    SchedulerTestLayer::onExit();
}

void SchedulerUnscheduleAllHard::tick1(float dt)
{
    CCLOG("tick1");
}

void SchedulerUnscheduleAllHard::tick2(float dt)
{
    CCLOG("tick2");
}

void SchedulerUnscheduleAllHard::tick3(float dt)
{
    CCLOG("tick3");
}

void SchedulerUnscheduleAllHard::tick4(float dt)
{
    CCLOG("tick4");
}

void SchedulerUnscheduleAllHard::unscheduleAll(float dt)
{
    Director::getInstance()->getScheduler()->unscheduleAll();
    _actionManagerActive = false;
}

std::string SchedulerUnscheduleAllHard::title() const
{
    return "Unschedule All selectors (HARD)";
}

std::string SchedulerUnscheduleAllHard::subtitle() const
{
    return "Unschedules all user selectors after 4s. Action will stop. See console";
}

//------------------------------------------------------------------
//
// SchedulerUnscheduleAllUserLevel
//
//------------------------------------------------------------------
void SchedulerUnscheduleAllUserLevel::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllUserLevel::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllUserLevel::tick2), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllUserLevel::tick3), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllUserLevel::tick4), 1.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUnscheduleAllUserLevel::unscheduleAll), 4);
}

void SchedulerUnscheduleAllUserLevel::tick1(float dt)
{
    CCLOG("tick1");
}

void SchedulerUnscheduleAllUserLevel::tick2(float dt)
{
    CCLOG("tick2");
}

void SchedulerUnscheduleAllUserLevel::tick3(float dt)
{
    CCLOG("tick3");
}

void SchedulerUnscheduleAllUserLevel::tick4(float dt)
{
    CCLOG("tick4");
}

void SchedulerUnscheduleAllUserLevel::unscheduleAll(float dt)
{
    Director::getInstance()->getScheduler()->unscheduleAllWithMinPriority(Scheduler::PRIORITY_NON_SYSTEM_MIN);
}

std::string SchedulerUnscheduleAllUserLevel::title() const
{
    return "Unschedule All user selectors";
}

std::string SchedulerUnscheduleAllUserLevel::subtitle() const
{
    return "Unschedules all user selectors after 4s. Action should not stop. See console";
}

//------------------------------------------------------------------
//
// SchedulerSchedulesAndRemove
//
//------------------------------------------------------------------
void SchedulerSchedulesAndRemove::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick1), 0.5f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick2), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::scheduleAndUnschedule), 4.0f);
}

void SchedulerSchedulesAndRemove::tick1(float dt)
{
    CCLOG("tick1");
}

void SchedulerSchedulesAndRemove::tick2(float dt)
{
    CCLOG("tick2");
}

void SchedulerSchedulesAndRemove::tick3(float dt)
{
    CCLOG("tick3");
}

void SchedulerSchedulesAndRemove::tick4(float dt)
{
    CCLOG("tick4");
}

std::string SchedulerSchedulesAndRemove::title() const
{
    return "Schedule from Schedule";
}

std::string SchedulerSchedulesAndRemove::subtitle() const
{
    return "Will unschedule and schedule selectors in 4s. See console";
}

void SchedulerSchedulesAndRemove::scheduleAndUnschedule(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick1));
    unschedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick2));
    unschedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::scheduleAndUnschedule));

    schedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick3), 1.0f);
    schedule(CC_SCHEDULE_SELECTOR(SchedulerSchedulesAndRemove::tick4), 1.0f);
}

//------------------------------------------------------------------
//
// TestNode
//
//------------------------------------------------------------------
void TestNode::initWithString(const std::string& str, int priority)
{
    _string = str;
    scheduleUpdateWithPriority(priority);
}

TestNode::~TestNode()
{
}

void TestNode::update(float dt)
{
    CC_UNUSED_PARAM(dt);
    log("%s", _string.c_str());
}

//------------------------------------------------------------------
//
// SchedulerUpdate
//
//------------------------------------------------------------------
void SchedulerUpdate::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto d = new (std::nothrow) TestNode();
    d->initWithString("---", 50);
    addChild(d);
    d->release();

    auto b = new (std::nothrow) TestNode();
    b->initWithString("3rd", 0);
    addChild(b);
    b->release();

    auto a = new (std::nothrow) TestNode();
    a->initWithString("1st", -10);
    addChild(a);
    a->release();

    auto c = new (std::nothrow) TestNode();
    c->initWithString("4th", 10);
    addChild(c);
    c->release();

    auto e = new (std::nothrow) TestNode();
    e->initWithString("5th", 20);
    addChild(e);
    e->release();

    auto f = new (std::nothrow) TestNode();
    f->initWithString("2nd", -5);
    addChild(f);
    f->release();

    schedule(CC_SCHEDULE_SELECTOR(SchedulerUpdate::removeUpdates), 4.0f);
}

void SchedulerUpdate::removeUpdates(float dt)
{
    auto& children = getChildren();

    for (auto& c : children)
    {
        auto obj = static_cast<Ref*>(c);
        auto node = static_cast<Node*>(obj);
        
        if (! node)
        {
            break;
        }
        node->unscheduleAllCallbacks();
    }
}

std::string SchedulerUpdate::title() const
{
    return "Schedule update with priority";
}

std::string SchedulerUpdate::subtitle() const
{
    return "3 scheduled updates. Priority should work. Stops in 4s. See console";
}

//------------------------------------------------------------------
//
// SchedulerUpdateAndCustom
//
//------------------------------------------------------------------
void SchedulerUpdateAndCustom::onEnter()
{
    SchedulerTestLayer::onEnter();

    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateAndCustom::tick));
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateAndCustom::stopSelectors), 0.4f);
}

void SchedulerUpdateAndCustom::update(float dt)
{
    CCLOG("update called:%f", dt);
}

void SchedulerUpdateAndCustom::tick(float dt)
{
    CCLOG("custom selector called:%f",dt);
}

void SchedulerUpdateAndCustom::stopSelectors(float dt)
{
    log("SchedulerUpdateAndCustom::stopSelectors");
    unscheduleAllCallbacks();
}

std::string SchedulerUpdateAndCustom::title() const
{
    return "Schedule Update + custom selector";
}

std::string SchedulerUpdateAndCustom::subtitle() const
{
    return "Update + custom selector at the same time. Stops in 4s. See console";
}

//------------------------------------------------------------------
//
// SchedulerUpdateFromCustom
//
//------------------------------------------------------------------
void SchedulerUpdateFromCustom::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateFromCustom::schedUpdate), 2.0f);
}

void SchedulerUpdateFromCustom::update(float dt)
{
    CCLOG("update called:%f", dt);
}

void SchedulerUpdateFromCustom::schedUpdate(float dt)
{
    unschedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateFromCustom::schedUpdate));
    scheduleUpdate();
    schedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateFromCustom::stopUpdate), 2.0f);
}

void SchedulerUpdateFromCustom::stopUpdate(float dt)
{
    unscheduleUpdate();
    unschedule(CC_SCHEDULE_SELECTOR(SchedulerUpdateFromCustom::stopUpdate));
}

std::string SchedulerUpdateFromCustom::title() const
{
    return "Schedule Update in 2 sec";
}

std::string SchedulerUpdateFromCustom::subtitle() const
{
    return "Update schedules in 2 secs. Stops 2 sec later. See console";
}

//------------------------------------------------------------------
//
// RescheduleSelector
//
//------------------------------------------------------------------
void RescheduleSelector::onEnter()
{
    SchedulerTestLayer::onEnter();

    _interval = 1.0f;
    _ticks    = 0;
    schedule(CC_SCHEDULE_SELECTOR(RescheduleSelector::schedUpdate), _interval);
}

std::string RescheduleSelector::title() const
{
    return "Reschedule Selector";
}

std::string RescheduleSelector::subtitle() const
{
    return "Interval is 1 second, then 2, then 3...";
}

void RescheduleSelector::schedUpdate(float dt)
{
    _ticks++;

    CCLOG("schedUpdate: %.4f", dt);
    if ( _ticks > 3 )
    {
        _interval += 1.0f;
        schedule(CC_SCHEDULE_SELECTOR(RescheduleSelector::schedUpdate), _interval);
        _ticks = 0;
    }
}

// SchedulerDelayAndRepeat

void SchedulerDelayAndRepeat::onEnter()
{
    SchedulerTestLayer::onEnter();
    schedule(CC_SCHEDULE_SELECTOR(SchedulerDelayAndRepeat::update), 0, 4 , 3.f);
    CCLOG("update is scheduled should begin after 3 seconds");
}

std::string SchedulerDelayAndRepeat::title() const
{
    return "Schedule with delay of 3 sec, repeat 4 times";
}

std::string SchedulerDelayAndRepeat::subtitle() const
{
    return "After 5 x executed, method unscheduled. See console";
}

void SchedulerDelayAndRepeat::update(float dt)
{
    log("update called:%f", dt);
}

// SchedulerTimeScale

ControlSlider* SchedulerTimeScale::sliderCtl()
{
    ControlSlider * slider = ControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");

    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(SchedulerTimeScale::sliderAction), Control::EventType::VALUE_CHANGED);

    slider->setMinimumValue(-3.0f);
    slider->setMaximumValue(3.0f);
    slider->setValue(1.0f);

    return slider;
}

void SchedulerTimeScale::sliderAction(Ref* sender, Control::EventType controlEvent)
{
    ControlSlider* pSliderCtl = static_cast<ControlSlider*>(sender);
    float scale;
    scale = pSliderCtl->getValue();

    Director::getInstance()->getScheduler()->setTimeScale(scale);
}

void SchedulerTimeScale::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

    // rotate and jump
    auto jump1 = JumpBy::create(4, Vec2(-s.width+80,0), 100, 4);
    auto jump2 = jump1->reverse();
    auto rot1 = RotateBy::create(4, 360*2);
    auto rot2 = rot1->reverse();

    auto seq3_1 = Sequence::create(jump2, jump1, nullptr);
    auto seq3_2 = Sequence::create(rot1, rot2, nullptr);
    auto spawn = Spawn::create(seq3_1, seq3_2, nullptr);
    auto action = Repeat::create(spawn, 50);

    auto action2 = action->clone();
    auto action3 = action->clone();

    auto grossini = Sprite::create("Images/grossini.png");
    auto tamara = Sprite::create("Images/grossinis_sister1.png");
    auto kathia = Sprite::create("Images/grossinis_sister2.png");

    grossini->setPosition(Vec2(40,80));
    tamara->setPosition(Vec2(40,80));
    kathia->setPosition(Vec2(40,80));

    addChild(grossini);
    addChild(tamara);
    addChild(kathia);

    grossini->runAction(Speed::create(action, 0.5f));
    tamara->runAction(Speed::create(action2, 1.5f));
    kathia->runAction(Speed::create(action3, 1.0f));

    auto emitter = ParticleFireworks::create();
    emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_stars1) );
    addChild(emitter);

    _sliderCtl = sliderCtl();
    _sliderCtl->setPosition(Vec2(s.width / 2.0f, s.height / 3.0f));

    addChild(_sliderCtl);
}

void SchedulerTimeScale::onExit()
{
    // restore scale
    Director::getInstance()->getScheduler()->setTimeScale(1);
    SchedulerTestLayer::onExit();
}

std::string SchedulerTimeScale::title() const
{
    return "Scheduler timeScale Test";
}

std::string SchedulerTimeScale::subtitle() const
{
    return "Fast-forward and rewind using scheduler.timeScale";
}

//TwoSchedulers

ControlSlider *TwoSchedulers::sliderCtl()
{
   // auto frame = CGRectMake(12.0f, 12.0f, 120.0f, 7.0f);
    ControlSlider *slider = ControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");
        //[[UISlider alloc] initWithFrame:frame];
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(TwoSchedulers::sliderAction), Control::EventType::VALUE_CHANGED);

    // in case the parent view draws with a custom color or gradient, use a transparent color
    //slider.backgroundColor = [UIColor clearColor];

    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(2.0f);
    //slider.continuous = YES;
    slider->setValue(1.0f);

    return slider;
}

void TwoSchedulers::sliderAction(Ref* sender, Control::EventType controlEvent)
{
    float scale;

    ControlSlider *slider = static_cast<ControlSlider*>(sender);
    scale = slider->getValue();

    if( sender == sliderCtl1 )
        sched1->setTimeScale(scale);
    else
        sched2->setTimeScale(scale);
}

void TwoSchedulers::onEnter()
{
    SchedulerTestLayer::onEnter();

    auto s = Director::getInstance()->getWinSize();

        // rotate and jump
    auto jump1 = JumpBy::create(4, Vec2(0,0), 100, 4);
    auto jump2 = jump1->reverse();

    auto seq = Sequence::create(jump2, jump1, nullptr);
    auto action = RepeatForever::create(seq);

        //
        // Center
        //
    auto grossini = Sprite::create("Images/grossini.png");
    addChild(grossini);
    grossini->setPosition(Vec2(s.width/2,100));
    grossini->runAction(action->clone());

    auto defaultScheduler = Director::getInstance()->getScheduler();

    //
    // Left:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched1 = new (std::nothrow) Scheduler();

    defaultScheduler->scheduleUpdate(sched1, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager1 = new (std::nothrow) ActionManager();
    sched1->scheduleUpdate(actionManager1, 0, false);

    for( unsigned int i=0; i < 10; i++ ) 
    {
        auto sprite = Sprite::create("Images/grossinis_sister1.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager1);

        addChild(sprite);
        sprite->setPosition(Vec2(30+15*i,100));

        sprite->runAction(action->clone());
    }


    //
    // Right:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched2 = new (std::nothrow) Scheduler();;
    defaultScheduler->scheduleUpdate(sched2, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager2 = new (std::nothrow) ActionManager();
    sched2->scheduleUpdate(actionManager2, 0, false);

    for( unsigned int i=0; i < 10; i++ ) {
        auto sprite = Sprite::create("Images/grossinis_sister2.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager2);

        addChild(sprite);
        sprite->setPosition(Vec2(s.width-30-15*i,100));

        sprite->runAction(action->clone());
    }

    sliderCtl1 = sliderCtl();
    addChild(sliderCtl1);
    sliderCtl1->retain();
    sliderCtl1->setPosition(Vec2(s.width / 4.0f, VisibleRect::top().y - 20));

    sliderCtl2 = sliderCtl();
    addChild(sliderCtl2);
    sliderCtl2->retain();
    sliderCtl2->setPosition(Vec2(s.width / 4.0f*3.0f, VisibleRect::top().y-20));
}


TwoSchedulers::~TwoSchedulers()
{
    auto defaultScheduler = Director::getInstance()->getScheduler();
    defaultScheduler->unscheduleAllForTarget(sched1);
    defaultScheduler->unscheduleAllForTarget(sched2);

    sliderCtl1->release();
    sliderCtl2->release();

    sched1->release();
    sched2->release();

    actionManager1->release();
    actionManager2->release();
}

std::string TwoSchedulers::title() const
{
    return "Two custom schedulers";
}

std::string TwoSchedulers::subtitle() const
{
    return "Three schedulers. 2 custom + 1 default. Two different time scales";
}

class TestNode2 : public Node
{
public:
    CREATE_FUNC(TestNode2);

	~TestNode2() {
		cocos2d::log("Delete TestNode (should not crash)");
		this->unscheduleAllCallbacks();
	}

	void update(float dt) {
	}
};

void SchedulerIssue2268::onEnter()
{
	SchedulerTestLayer::onEnter();

	testNode = TestNode2::create();
	testNode->retain();
	testNode->schedule(SEL_SCHEDULE(&TestNode::update));
	this->addChild(testNode);


	this->scheduleOnce(SEL_SCHEDULE(&SchedulerIssue2268::update), 0.25f);
}

void SchedulerIssue2268::update(float dt)
{
	if ( testNode != nullptr ) {
		// do something with testNode

		// at some point we are done, pause the nodes actions and schedulers
		testNode->removeFromParentAndCleanup(false);

		// at some other point we are completely done with the node and want to clear it
		testNode->unscheduleAllCallbacks();
		testNode->release();
		testNode = nullptr;

	}
}
SchedulerIssue2268::~SchedulerIssue2268()
{
    CC_SAFE_RELEASE(testNode);
}

std::string SchedulerIssue2268::title() const
{
    return "Issue #2268";
}

std::string SchedulerIssue2268::subtitle() const
{
    return "Should not crash";
}

// ScheduleCallbackTest

ScheduleCallbackTest::~ScheduleCallbackTest()
{
    
}

std::string ScheduleCallbackTest::title() const
{
    return "ScheduleCallbackTest";
}

std::string ScheduleCallbackTest::subtitle() const
{
    return "\n\n\n\nPlease see console.\n\
schedule(lambda, ...)\n\
schedule(CC_CALLBACK_1(XXX::member_function), this), this, ...)\n\
schedule(global_function, ...)\n\
";
}

static void ScheduleCallbackTest_global_callback(float dt)
{
    log("In the callback of schedule(global_function, ...), dt = %f", dt);
}

void ScheduleCallbackTest::onEnter()
{
    SchedulerTestLayer::onEnter();
    
    _scheduler->schedule([](float dt){
        log("In the callback of schedule(lambda, ...), dt = %f", dt);
    }, this, 1.0f, false, "lambda");
    
    _scheduler->schedule(CC_CALLBACK_1(ScheduleCallbackTest::callback, this), this, 1.0f, false, "member_function");
    
    _scheduler->schedule(ScheduleCallbackTest_global_callback, this, 1.0f, false, "global_function");
}

void ScheduleCallbackTest::callback(float dt)
{
    log("In the callback of schedule(CC_CALLBACK_1(XXX::member_function), this), this, ...), dt = %f", dt);
}


// ScheduleUpdatePriority

std::string ScheduleUpdatePriority::title() const
{
    return "ScheduleUpdatePriorityTest";
}

std::string ScheduleUpdatePriority::subtitle() const
{
    return "click to change update priority with random value";
}

bool ScheduleUpdatePriority::onTouchBegan(Touch* touch, Event* event)
{
    int priority = static_cast<int>(CCRANDOM_0_1() * 11) - 5;  // -5 ~ 5
    CCLOG("change update priority to %d", priority);
    scheduleUpdateWithPriority(priority);
    return true;
}

void ScheduleUpdatePriority::onEnter()
{
    SchedulerTestLayer::onEnter();
    
    scheduleUpdate();

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ScheduleUpdatePriority::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ScheduleUpdatePriority::onExit()
{
    Node::onExit();
    unscheduleUpdate();
}

void ScheduleUpdatePriority::update(float dt)
{
}

void SchedulerIssue10232::onEnter()
{
    SchedulerTestLayer::onEnter();

    this->scheduleOnce(SEL_SCHEDULE(&SchedulerIssue2268::update), 0.25f);

    this->scheduleOnce([](float dt){
        log("SchedulerIssue10232:Schedules a lambda function");
    }, 0.25f,"SchedulerIssue10232");
}

void SchedulerIssue10232::update(float dt)
{
    log("SchedulerIssue10232:Schedules a selector");
}

std::string SchedulerIssue10232::title() const
{
    return "Issue #10232";
}

std::string SchedulerIssue10232::subtitle() const
{
    return "Should not crash";
}
