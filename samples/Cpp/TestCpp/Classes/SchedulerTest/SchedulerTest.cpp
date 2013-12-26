#include "SchedulerTest.h"
#include "../testResource.h"

enum {
    kTagAnimationDance = 1,
};

static int sceneIdx = -1;

Layer* nextSchedulerTest();
Layer* backSchedulerTest();
Layer* restartSchedulerTest();

static std::function<Layer*()> createFunctions[] = {
    CL(SchedulerTimeScale),
    CL(TwoSchedulers),
    CL(SchedulerAutoremove),
    CL(SchedulerPauseResume),
    CL(SchedulerPauseResumeAll),
    CL(SchedulerPauseResumeAllUser),
    CL(SchedulerUnscheduleAll),
    CL(SchedulerUnscheduleAllHard),
    CL(SchedulerUnscheduleAllUserLevel),
    CL(SchedulerSchedulesAndRemove),
    CL(SchedulerUpdate),
    CL(SchedulerUpdateAndCustom),
    CL(SchedulerUpdateFromCustom),
    CL(RescheduleSelector),
    CL(SchedulerDelayAndRepeat),
    CL(SchedulerIssue2268)
};

#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextSchedulerTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backSchedulerTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartSchedulerTest()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

//------------------------------------------------------------------
//
// SchedulerTestLayer
//
//------------------------------------------------------------------
void SchedulerTestLayer::onEnter()
{
    BaseTest::onEnter();
}

void SchedulerTestLayer::backCallback(Object* sender)
{
    auto scene = new SchedulerTestScene();
    auto layer = backSchedulerTest();

    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void SchedulerTestLayer::nextCallback(Object* sender)
{
    auto scene = new SchedulerTestScene();
    auto layer = nextSchedulerTest();

    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

void SchedulerTestLayer::restartCallback(Object* sender)
{
    auto scene = new SchedulerTestScene();
    auto layer = restartSchedulerTest();

    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
    scene->release();
}

std::string SchedulerTestLayer::title() const
{
    return "No title";
}

std::string SchedulerTestLayer::subtitle() const
{
    return "";
}

//------------------------------------------------------------------
//
// SchedulerAutoremove
//
//------------------------------------------------------------------
void SchedulerAutoremove::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(schedule_selector(SchedulerAutoremove::autoremove), 0.5f);
    schedule(schedule_selector(SchedulerAutoremove::tick), 0.5f);
    accum = 0;
}

void SchedulerAutoremove::autoremove(float dt)
{
    accum += dt;
    CCLOG("Time: %f", accum);

    if( accum > 3 )
    {
        unschedule(schedule_selector(SchedulerAutoremove::autoremove));
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

    schedule(schedule_selector(SchedulerPauseResume::tick1), 0.5f);
    schedule(schedule_selector(SchedulerPauseResume::tick2), 0.5f);
    schedule(schedule_selector(SchedulerPauseResume::pause), 0.5f);
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

    scheduleUpdate();
    schedule(schedule_selector(SchedulerPauseResumeAll::tick1), 0.5f);
    schedule(schedule_selector(SchedulerPauseResumeAll::tick2), 1.0f);
    schedule(schedule_selector(SchedulerPauseResumeAll::pause), 3.0f, false, 0);
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
    log("Pausing");
    auto director = Director::getInstance();
    _pausedTargets = director->getScheduler()->pauseAllTargets();
    
    int c = _pausedTargets.size();
    
    if (c > 2)
    {
        // should have only 2 items: ActionManager, self
        log("Error: pausedTargets should have only 2 items, and not %u", (unsigned int)c);
    }
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
    return "Pause / Resume";
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
    sprite->setPosition(Point(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick1), 0.5f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick2), 1.0f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::pause), 3.0f, false, 0);
    //TODO: [self performSelector:@selector(resume) withObject:nil afterDelay:5];
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
    log("Pausing");
    auto director = Director::getInstance();
    _pausedTargets = director->getScheduler()->pauseAllTargetsWithMinPriority(Scheduler::PRIORITY_NON_SYSTEM_MIN);
}

void SchedulerPauseResumeAllUser::resume(float dt)
{
    log("Resuming");
    auto director = Director::getInstance();
    director->getScheduler()->resumeTargets(_pausedTargets);
    _pausedTargets.clear();
}

std::string SchedulerPauseResumeAllUser::title() const
{
    return "Pause / Resume";
}

std::string SchedulerPauseResumeAllUser::subtitle() const
{
    return "Everything will pause after 3s, then resume at 5s. See console";
}


//------------------------------------------------------------------
//
// SchedulerUnscheduleAll
//
//------------------------------------------------------------------
void SchedulerUnscheduleAll::onEnter()
{
    SchedulerTestLayer::onEnter();

    schedule(schedule_selector(SchedulerUnscheduleAll::tick1), 0.5f);
    schedule(schedule_selector(SchedulerUnscheduleAll::tick2), 1.0f);
    schedule(schedule_selector(SchedulerUnscheduleAll::tick3), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAll::tick4), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAll::unscheduleAll), 4);
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
    unscheduleAllSelectors();
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
    sprite->setPosition(Point(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    _actionManagerActive = true;

    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick1), 0.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick2), 1.0f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick3), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick4), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::unscheduleAll), 4);
}

void SchedulerUnscheduleAllHard::onExit()
{
    if(!_actionManagerActive) {
        // Restore the director's action manager.
        auto director = Director::getInstance();
        director->getScheduler()->scheduleUpdateForTarget(director->getActionManager(), Scheduler::PRIORITY_SYSTEM, false);
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
    sprite->setPosition(Point(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    schedule(schedule_selector(SchedulerUnscheduleAllUserLevel::tick1), 0.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllUserLevel::tick2), 1.0f);
    schedule(schedule_selector(SchedulerUnscheduleAllUserLevel::tick3), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllUserLevel::tick4), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllUserLevel::unscheduleAll), 4);
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

    schedule(schedule_selector(SchedulerSchedulesAndRemove::tick1), 0.5f);
    schedule(schedule_selector(SchedulerSchedulesAndRemove::tick2), 1.0f);
    schedule(schedule_selector(SchedulerSchedulesAndRemove::scheduleAndUnschedule), 4.0f);
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
    unschedule(schedule_selector(SchedulerSchedulesAndRemove::tick1));
    unschedule(schedule_selector(SchedulerSchedulesAndRemove::tick2));
    unschedule(schedule_selector(SchedulerSchedulesAndRemove::scheduleAndUnschedule));

    schedule(schedule_selector(SchedulerSchedulesAndRemove::tick3), 1.0f);
    schedule(schedule_selector(SchedulerSchedulesAndRemove::tick4), 1.0f);
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

    auto d = new TestNode();
    d->initWithString("---", 50);
    addChild(d);
    d->release();

    auto b = new TestNode();
    b->initWithString("3rd", 0);
    addChild(b);
    b->release();

    auto a = new TestNode();
    a->initWithString("1st", -10);
    addChild(a);
    a->release();

    auto c = new TestNode();
    c->initWithString("4th", 10);
    addChild(c);
    c->release();

    auto e = new TestNode();
    e->initWithString("5th", 20);
    addChild(e);
    e->release();

    auto f = new TestNode();
    f->initWithString("2nd", -5);
    addChild(f);
    f->release();

    schedule(schedule_selector(SchedulerUpdate::removeUpdates), 4.0f);
}

void SchedulerUpdate::removeUpdates(float dt)
{
    auto& children = getChildren();

    for (auto& c : children)
    {
        auto obj = static_cast<Object*>(c);
        auto node = static_cast<Node*>(obj);
        
        if (! node)
        {
            break;
        }
        node->unscheduleAllSelectors();
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
    schedule(schedule_selector(SchedulerUpdateAndCustom::tick));
    schedule(schedule_selector(SchedulerUpdateAndCustom::stopSelectors), 0.4f);
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
    unscheduleAllSelectors();
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

    schedule(schedule_selector(SchedulerUpdateFromCustom::schedUpdate), 2.0f);
}

void SchedulerUpdateFromCustom::update(float dt)
{
    CCLOG("update called:%f", dt);
}

void SchedulerUpdateFromCustom::schedUpdate(float dt)
{
    unschedule(schedule_selector(SchedulerUpdateFromCustom::schedUpdate));
    scheduleUpdate();
    schedule(schedule_selector(SchedulerUpdateFromCustom::stopUpdate), 2.0f);
}

void SchedulerUpdateFromCustom::stopUpdate(float dt)
{
    unscheduleUpdate();
    unschedule(schedule_selector(SchedulerUpdateFromCustom::stopUpdate));
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
    schedule(schedule_selector(RescheduleSelector::schedUpdate), _interval);
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
        schedule(schedule_selector(RescheduleSelector::schedUpdate), _interval);
        _ticks = 0;
    }
}

// SchedulerDelayAndRepeat

void SchedulerDelayAndRepeat::onEnter()
{
    SchedulerTestLayer::onEnter();
    schedule(schedule_selector(SchedulerDelayAndRepeat::update), 0, 4 , 3.f);
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

void SchedulerTimeScale::sliderAction(Object* sender, Control::EventType controlEvent)
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
    auto jump1 = JumpBy::create(4, Point(-s.width+80,0), 100, 4);
    auto jump2 = jump1->reverse();
    auto rot1 = RotateBy::create(4, 360*2);
    auto rot2 = rot1->reverse();

    auto seq3_1 = Sequence::create(jump2, jump1, NULL);
    auto seq3_2 = Sequence::create(rot1, rot2, NULL);
    auto spawn = Spawn::create(seq3_1, seq3_2, NULL);
    auto action = Repeat::create(spawn, 50);

    auto action2 = action->clone();
    auto action3 = action->clone();

    auto grossini = Sprite::create("Images/grossini.png");
    auto tamara = Sprite::create("Images/grossinis_sister1.png");
    auto kathia = Sprite::create("Images/grossinis_sister2.png");

    grossini->setPosition(Point(40,80));
    tamara->setPosition(Point(40,80));
    kathia->setPosition(Point(40,80));

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
    _sliderCtl->setPosition(Point(s.width / 2.0f, s.height / 3.0f));

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

void TwoSchedulers::sliderAction(Object* sender, Control::EventType controlEvent)
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
    auto jump1 = JumpBy::create(4, Point(0,0), 100, 4);
    auto jump2 = jump1->reverse();

    auto seq = Sequence::create(jump2, jump1, NULL);
    auto action = RepeatForever::create(seq);

        //
        // Center
        //
    auto grossini = Sprite::create("Images/grossini.png");
    addChild(grossini);
    grossini->setPosition(Point(s.width/2,100));
    grossini->runAction(action->clone());

    auto defaultScheduler = Director::getInstance()->getScheduler();

    //
    // Left:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched1 = new Scheduler();

    defaultScheduler->scheduleUpdateForTarget(sched1, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager1 = new ActionManager();
    sched1->scheduleUpdateForTarget(actionManager1, 0, false);

    for( unsigned int i=0; i < 10; i++ ) 
    {
        auto sprite = Sprite::create("Images/grossinis_sister1.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager1);

        addChild(sprite);
        sprite->setPosition(Point(30+15*i,100));

        sprite->runAction(action->clone());
    }


    //
    // Right:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched2 = new Scheduler();;
    defaultScheduler->scheduleUpdateForTarget(sched2, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager2 = new ActionManager();
    sched2->scheduleUpdateForTarget(actionManager2, 0, false);

    for( unsigned int i=0; i < 10; i++ ) {
        auto sprite = Sprite::create("Images/grossinis_sister2.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager2);

        addChild(sprite);
        sprite->setPosition(Point(s.width-30-15*i,100));

        sprite->runAction(action->clone());
    }

    sliderCtl1 = sliderCtl();
    addChild(sliderCtl1);
    sliderCtl1->retain();
    sliderCtl1->setPosition(Point(s.width / 4.0f, VisibleRect::top().y - 20));

    sliderCtl2 = sliderCtl();
    addChild(sliderCtl2);
    sliderCtl2->retain();
    sliderCtl2->setPosition(Point(s.width / 4.0f*3.0f, VisibleRect::top().y-20));
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
		this->unscheduleAllSelectors();
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
	if ( testNode != NULL ) {
		// do something with testNode

		// at some point we are done, pause the nodes actions and schedulers
		testNode->removeFromParentAndCleanup(false);

		// at some other point we are completely done with the node and want to clear it
		testNode->release();
		testNode->unscheduleAllSelectors();
		testNode = NULL;

	}
}
SchedulerIssue2268::~SchedulerIssue2268()
{

}

std::string SchedulerIssue2268::title() const
{
    return "Issue #2268";
}

std::string SchedulerIssue2268::subtitle() const
{
    return "Should not crash";
}
//------------------------------------------------------------------
//
// SchedulerTestScene
//
//------------------------------------------------------------------
void SchedulerTestScene::runThisTest()
{
    auto layer = nextSchedulerTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
