#include "SchedulerTest.h"
#include "../testResource.h"

enum {
    kTagAnimationDance = 1,
};

static int sceneIdx = -1;

Layer* nextSchedulerTest();
Layer* backSchedulerTest();
Layer* restartSchedulerTest();

TESTLAYER_CREATE_FUNC(SchedulerTimeScale)
TESTLAYER_CREATE_FUNC(TwoSchedulers)
TESTLAYER_CREATE_FUNC(SchedulerAutoremove)
TESTLAYER_CREATE_FUNC(SchedulerPauseResume)
TESTLAYER_CREATE_FUNC(SchedulerPauseResumeAll)
TESTLAYER_CREATE_FUNC(SchedulerPauseResumeAllUser)
TESTLAYER_CREATE_FUNC(SchedulerUnscheduleAll)
TESTLAYER_CREATE_FUNC(SchedulerUnscheduleAllHard)
TESTLAYER_CREATE_FUNC(SchedulerUnscheduleAllUserLevel)
TESTLAYER_CREATE_FUNC(SchedulerSchedulesAndRemove)
TESTLAYER_CREATE_FUNC(SchedulerUpdate)
TESTLAYER_CREATE_FUNC(SchedulerUpdateAndCustom)
TESTLAYER_CREATE_FUNC(SchedulerUpdateFromCustom)
TESTLAYER_CREATE_FUNC(RescheduleSelector)
TESTLAYER_CREATE_FUNC(SchedulerDelayAndRepeat)
TESTLAYER_CREATE_FUNC(SchedulerIssue2268)

static NEWTESTFUNC createFunctions[] = {
    CF(SchedulerTimeScale),
    CF(TwoSchedulers),
    CF(SchedulerAutoremove),
    CF(SchedulerPauseResume),
    CF(SchedulerPauseResumeAll),
    CF(SchedulerPauseResumeAllUser),
    CF(SchedulerUnscheduleAll),
    CF(SchedulerUnscheduleAllHard),
    CF(SchedulerUnscheduleAllUserLevel),
    CF(SchedulerSchedulesAndRemove),
    CF(SchedulerUpdate),
    CF(SchedulerUpdateAndCustom),
    CF(SchedulerUpdateFromCustom),
    CF(RescheduleSelector),
    CF(SchedulerDelayAndRepeat),
    CF(SchedulerIssue2268)
};

#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextSchedulerTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

Layer* backSchedulerTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

Layer* restartSchedulerTest()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
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

void SchedulerTestLayer::backCallback(Object* pSender)
{
    Scene* pScene = new SchedulerTestScene();
    Layer* pLayer = backSchedulerTest();

    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::nextCallback(Object* pSender)
{
    Scene* pScene = new SchedulerTestScene();
    Layer* pLayer = nextSchedulerTest();

    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::restartCallback(Object* pSender)
{
    Scene* pScene = new SchedulerTestScene();
    Layer* pLayer = restartSchedulerTest();

    pScene->addChild(pLayer);
    Director::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

std::string SchedulerTestLayer::title()
{
    return "No title";
}

std::string SchedulerTestLayer::subtitle()
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

std::string SchedulerAutoremove::title()
{
    return "Self-remove an scheduler";
}

std::string SchedulerAutoremove::subtitle()
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
    Director::sharedDirector()->getScheduler()->pauseTarget(this);
}

std::string SchedulerPauseResume::title()
{
    return "Pause / Resume";
}

std::string SchedulerPauseResume::subtitle()
{
    return "Scheduler should be paused after 3 seconds. See console";
}

//------------------------------------------------------------------
//
// SchedulerPauseResumeAll
//
//------------------------------------------------------------------

SchedulerPauseResumeAll::SchedulerPauseResumeAll()
: _pausedTargets(NULL)
{
    
}

SchedulerPauseResumeAll::~SchedulerPauseResumeAll()
{
    CC_SAFE_RELEASE(_pausedTargets);
}

void SchedulerPauseResumeAll::onEnter()
{
    SchedulerTestLayer::onEnter();

    Sprite *sprite = Sprite::create("Images/grossinis_sister1.png");
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
    if(_pausedTargets != NULL)
    {
        Director::sharedDirector()->getScheduler()->resumeTargets(_pausedTargets);
    }
}

void SchedulerPauseResumeAll::tick1(float dt)
{
    CCLog("tick1");
}

void SchedulerPauseResumeAll::tick2(float dt)
{
    CCLog("tick2");
}

void SchedulerPauseResumeAll::pause(float dt)
{
    CCLog("Pausing");
    Director* pDirector = Director::sharedDirector();
    _pausedTargets = pDirector->getScheduler()->pauseAllTargets();
    CC_SAFE_RETAIN(_pausedTargets);
    
    unsigned int c = _pausedTargets->count();
    
    if (c > 2)
    {
        // should have only 2 items: ActionManager, self
        CCLog("Error: pausedTargets should have only 2 items, and not %u", (unsigned int)c);
    }
}

void SchedulerPauseResumeAll::resume(float dt)
{
    CCLog("Resuming");
    Director* pDirector = Director::sharedDirector();
    pDirector->getScheduler()->resumeTargets(_pausedTargets);
    CC_SAFE_RELEASE_NULL(_pausedTargets);
}

std::string SchedulerPauseResumeAll::title()
{
    return "Pause / Resume";
}

std::string SchedulerPauseResumeAll::subtitle()
{
    return "Everything will pause after 3s, then resume at 5s. See console";
}

//------------------------------------------------------------------
//
// SchedulerPauseResumeAllUser
//
//------------------------------------------------------------------

SchedulerPauseResumeAllUser::SchedulerPauseResumeAllUser()
: _pausedTargets(NULL)
{

}

SchedulerPauseResumeAllUser::~SchedulerPauseResumeAllUser()
{
    CC_SAFE_RELEASE(_pausedTargets);
}

void SchedulerPauseResumeAllUser::onEnter()
{
    SchedulerTestLayer::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    Sprite *sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));

    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick1), 0.5f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick2), 1.0f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::pause), 3.0f, false, 0);
    //TODO: [self performSelector:@selector(resume) withObject:nil afterDelay:5];
}

void SchedulerPauseResumeAllUser::onExit()
{
    if(_pausedTargets != NULL)
    {
        Director::sharedDirector()->getScheduler()->resumeTargets(_pausedTargets);
    }
}

void SchedulerPauseResumeAllUser::tick1(float dt)
{
    CCLog("tick1");
}

void SchedulerPauseResumeAllUser::tick2(float dt)
{
    CCLog("tick2");
}

void SchedulerPauseResumeAllUser::pause(float dt)
{
    CCLog("Pausing");
    Director* pDirector = Director::sharedDirector();
    _pausedTargets = pDirector->getScheduler()->pauseAllTargetsWithMinPriority(kPriorityNonSystemMin);
    CC_SAFE_RETAIN(_pausedTargets);
}

void SchedulerPauseResumeAllUser::resume(float dt)
{
    CCLog("Resuming");
    Director* pDirector = Director::sharedDirector();
    pDirector->getScheduler()->resumeTargets(_pausedTargets);
    CC_SAFE_RELEASE_NULL(_pausedTargets);
}

std::string SchedulerPauseResumeAllUser::title()
{
    return "Pause / Resume";
}

std::string SchedulerPauseResumeAllUser::subtitle()
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

std::string SchedulerUnscheduleAll::title()
{
    return "Unschedule All selectors";
}

std::string SchedulerUnscheduleAll::subtitle()
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

    Size s = Director::sharedDirector()->getWinSize();

    Sprite *sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
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
        Director* director = Director::sharedDirector();
        director->getScheduler()->scheduleUpdateForTarget(director->getActionManager(), kPrioritySystem, false);
    }
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
    Director::sharedDirector()->getScheduler()->unscheduleAll();
    _actionManagerActive = false;
}

std::string SchedulerUnscheduleAllHard::title()
{
    return "Unschedule All selectors (HARD)";
}

std::string SchedulerUnscheduleAllHard::subtitle()
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

    Size s = Director::sharedDirector()->getWinSize();

    Sprite *sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
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
    Director::sharedDirector()->getScheduler()->unscheduleAllWithMinPriority(kPriorityNonSystemMin);
}

std::string SchedulerUnscheduleAllUserLevel::title()
{
    return "Unschedule All user selectors";
}

std::string SchedulerUnscheduleAllUserLevel::subtitle()
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

std::string SchedulerSchedulesAndRemove::title()
{
    return "Schedule from Schedule";
}

std::string SchedulerSchedulesAndRemove::subtitle()
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
void TestNode::initWithString(String* pStr, int priority)
{
    _pstring = pStr;
    _pstring->retain();
    scheduleUpdateWithPriority(priority);
}

TestNode::~TestNode()
{
    _pstring->release();
}

void TestNode::update(float dt)
{
    CC_UNUSED_PARAM(dt);
    CCLog("%s", _pstring->getCString());
}

//------------------------------------------------------------------
//
// SchedulerUpdate
//
//------------------------------------------------------------------
void SchedulerUpdate::onEnter()
{
    SchedulerTestLayer::onEnter();

    TestNode* d = new TestNode();
    String* pStr = new String("---");
    d->initWithString(pStr, 50);
    pStr->release();
    addChild(d);
    d->release();

    TestNode* b = new TestNode();
    pStr = new String("3rd");
    b->initWithString(pStr, 0);
    pStr->release();
    addChild(b);
    b->release();

    TestNode* a = new TestNode();
    pStr = new String("1st");
    a->initWithString(pStr, -10);
    pStr->release();
    addChild(a);
    a->release();

    TestNode* c = new TestNode();
    pStr = new String("4th");
    c->initWithString(pStr, 10);
    pStr->release();
    addChild(c);
    c->release();

    TestNode* e = new TestNode();
    pStr = new String("5th");
    e->initWithString(pStr, 20);
    pStr->release();
    addChild(e);
    e->release();

    TestNode* f = new TestNode();
    pStr = new String("2nd");
    f->initWithString(pStr, -5);
    pStr->release();
    addChild(f);
    f->release();

    schedule(schedule_selector(SchedulerUpdate::removeUpdates), 4.0f);
}

void SchedulerUpdate::removeUpdates(float dt)
{
    Array* children = getChildren();
    Node* pNode;
    Object* pObject;
    CCARRAY_FOREACH(children, pObject)
    {
        pNode = (Node*)pObject;

        if (! pNode)
        {
            break;
        }
        pNode->unscheduleAllSelectors();
    }
}

std::string SchedulerUpdate::title()
{
    return "Schedule update with priority";
}

std::string SchedulerUpdate::subtitle()
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

std::string SchedulerUpdateAndCustom::title()
{
    return "Schedule Update + custom selector";
}

std::string SchedulerUpdateAndCustom::subtitle()
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

std::string SchedulerUpdateFromCustom::title()
{
    return "Schedule Update in 2 sec";
}

std::string SchedulerUpdateFromCustom::subtitle()
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

std::string RescheduleSelector::title()
{
    return "Reschedule Selector";
}

std::string RescheduleSelector::subtitle()
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

std::string SchedulerDelayAndRepeat::title()
{
    return "Schedule with delay of 3 sec, repeat 4 times";
}

std::string SchedulerDelayAndRepeat::subtitle()
{
    return "After 5 x executed, method unscheduled. See console";
}

void SchedulerDelayAndRepeat::update(float dt)
{
    CCLog("update called:%f", dt);
}

// SchedulerTimeScale

ControlSlider* SchedulerTimeScale::sliderCtl()
{
    ControlSlider * slider = ControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");

    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(SchedulerTimeScale::sliderAction), ControlEventValueChanged);

    slider->setMinimumValue(-3.0f);
    slider->setMaximumValue(3.0f);
    slider->setValue(1.0f);

    return slider;
}

void SchedulerTimeScale::sliderAction(Object* pSender, ControlEvent controlEvent)
{
    ControlSlider* pSliderCtl = (ControlSlider*)pSender;
    float scale;
    scale = pSliderCtl->getValue();

    Director::sharedDirector()->getScheduler()->setTimeScale(scale);
}

void SchedulerTimeScale::onEnter()
{
    SchedulerTestLayer::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

    // rotate and jump
    ActionInterval *jump1 = JumpBy::create(4, ccp(-s.width+80,0), 100, 4);
    ActionInterval *jump2 = jump1->reverse();
    ActionInterval *rot1 = RotateBy::create(4, 360*2);
    ActionInterval *rot2 = rot1->reverse();

    Sequence* seq3_1 = Sequence::create(jump2, jump1, NULL);
    Sequence* seq3_2 = Sequence::create(rot1, rot2, NULL);
    FiniteTimeAction* spawn = Spawn::create(seq3_1, seq3_2, NULL);
    Repeat* action = Repeat::create(spawn, 50);

    Repeat* action2 = action->clone();
    Repeat* action3 = action->clone();

    Sprite *grossini = Sprite::create("Images/grossini.png");
    Sprite *tamara = Sprite::create("Images/grossinis_sister1.png");
    Sprite *kathia = Sprite::create("Images/grossinis_sister2.png");

    grossini->setPosition(ccp(40,80));
    tamara->setPosition(ccp(40,80));
    kathia->setPosition(ccp(40,80));

    addChild(grossini);
    addChild(tamara);
    addChild(kathia);

    grossini->runAction(Speed::create(action, 0.5f));
    tamara->runAction(Speed::create(action2, 1.5f));
    kathia->runAction(Speed::create(action3, 1.0f));

    ParticleSystem *emitter = ParticleFireworks::create();
    emitter->setTexture( TextureCache::sharedTextureCache()->addImage(s_stars1) );
    addChild(emitter);

    _sliderCtl = sliderCtl();
    _sliderCtl->setPosition(ccp(s.width / 2.0f, s.height / 3.0f));

    addChild(_sliderCtl);
}

void SchedulerTimeScale::onExit()
{
    // restore scale
    Director::sharedDirector()->getScheduler()->setTimeScale(1);
    SchedulerTestLayer::onExit();
}

std::string SchedulerTimeScale::title()
{
    return "Scheduler timeScale Test";
}

std::string SchedulerTimeScale::subtitle()
{
    return "Fast-forward and rewind using scheduler.timeScale";
}

//TwoSchedulers

ControlSlider *TwoSchedulers::sliderCtl()
{
   // CGRect frame = CGRectMake(12.0f, 12.0f, 120.0f, 7.0f);
    ControlSlider *slider = ControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");
        //[[UISlider alloc] initWithFrame:frame];
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(TwoSchedulers::sliderAction), ControlEventValueChanged);

    // in case the parent view draws with a custom color or gradient, use a transparent color
    //slider.backgroundColor = [UIColor clearColor];

    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(2.0f);
    //slider.continuous = YES;
    slider->setValue(1.0f);

    return slider;
}

void TwoSchedulers::sliderAction(Object* sender, ControlEvent controlEvent)
{
    float scale;

    ControlSlider *slider = (ControlSlider*) sender;
    scale = slider->getValue();

    if( sender == sliderCtl1 )
        sched1->setTimeScale(scale);
    else
        sched2->setTimeScale(scale);
}

void TwoSchedulers::onEnter()
{
    SchedulerTestLayer::onEnter();

    Size s = Director::sharedDirector()->getWinSize();

        // rotate and jump
    ActionInterval *jump1 = JumpBy::create(4, ccp(0,0), 100, 4);
    ActionInterval *jump2 = jump1->reverse();

    Sequence* seq = Sequence::create(jump2, jump1, NULL);
    RepeatForever* action = RepeatForever::create(seq);

        //
        // Center
        //
    Sprite *grossini = Sprite::create("Images/grossini.png");
    addChild(grossini);
    grossini->setPosition(ccp(s.width/2,100));
    grossini->runAction(action->clone());

    Scheduler *defaultScheduler = Director::sharedDirector()->getScheduler();

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
        Sprite *sprite = Sprite::create("Images/grossinis_sister1.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager1);

        addChild(sprite);
        sprite->setPosition(ccp(30+15*i,100));

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
        Sprite *sprite = Sprite::create("Images/grossinis_sister2.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager2);

        addChild(sprite);
        sprite->setPosition(ccp(s.width-30-15*i,100));

        sprite->runAction(action->clone());
    }

    sliderCtl1 = sliderCtl();
    addChild(sliderCtl1);
    sliderCtl1->retain();
    sliderCtl1->setPosition(ccp(s.width / 4.0f, VisibleRect::top().y - 20));

    sliderCtl2 = sliderCtl();
    addChild(sliderCtl2);
    sliderCtl2->retain();
    sliderCtl2->setPosition(ccp(s.width / 4.0f*3.0f, VisibleRect::top().y-20));
}


TwoSchedulers::~TwoSchedulers()
{
    Scheduler *defaultScheduler = Director::sharedDirector()->getScheduler();
    defaultScheduler->unscheduleAllForTarget(sched1);
    defaultScheduler->unscheduleAllForTarget(sched2);

    sliderCtl1->release();
    sliderCtl2->release();

    sched1->release();
    sched2->release();

    actionManager1->release();
    actionManager2->release();
}

std::string TwoSchedulers::title()
{
    return "Two custom schedulers";
}

std::string TwoSchedulers::subtitle()
{
    return "Three schedulers. 2 custom + 1 default. Two different time scales";
}

class TestNode2 : public Node
{
public:
	~TestNode2() {
		cocos2d::CCLog("Delete TestNode (should not crash)");
		this->unscheduleAllSelectors();
	}

	void update(float dt) {
	}
};

void SchedulerIssue2268::onEnter()
{
	SchedulerTestLayer::onEnter();

	testNode = new TestNode2();
	testNode->init();
	testNode->autorelease();
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

std::string SchedulerIssue2268::title()
{
    return "Issue #2268";
}

std::string SchedulerIssue2268::subtitle()
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
    Layer* pLayer = nextSchedulerTest();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
