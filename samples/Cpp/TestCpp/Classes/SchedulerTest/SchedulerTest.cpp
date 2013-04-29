#include "SchedulerTest.h"
#include "../testResource.h"

enum {
    kTagAnimationDance = 1,
};

static int sceneIdx = -1;

CCLayer* nextSchedulerTest();
CCLayer* backSchedulerTest();
CCLayer* restartSchedulerTest();

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

CCLayer* nextSchedulerTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backSchedulerTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    

    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartSchedulerTest()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
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
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y-50));

    std::string subTitle = subtitle();
    if(! subTitle.empty())
    {
        CCLabelTTF* l = CCLabelTTF::create(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(SchedulerTestLayer::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png","Images/r2.png", this, menu_selector(SchedulerTestLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(SchedulerTestLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);
}

void SchedulerTestLayer::backCallback(CCObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = backSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::nextCallback(CCObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = nextSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::restartCallback(CCObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = restartSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
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
    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
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
: m_pPausedTargets(NULL)
{
    
}

SchedulerPauseResumeAll::~SchedulerPauseResumeAll()
{
    CC_SAFE_RELEASE(m_pPausedTargets);
}

void SchedulerPauseResumeAll::onEnter()
{
    SchedulerTestLayer::onEnter();

    CCSprite *sprite = CCSprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(VisibleRect::center());
    this->addChild(sprite);
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(3.0, 360)));

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
    if(m_pPausedTargets != NULL)
    {
        CCDirector::sharedDirector()->getScheduler()->resumeTargets(m_pPausedTargets);
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
    CCDirector* pDirector = CCDirector::sharedDirector();
    m_pPausedTargets = pDirector->getScheduler()->pauseAllTargets();
    CC_SAFE_RETAIN(m_pPausedTargets);
    
    unsigned int c = m_pPausedTargets->count();
    
    if (c > 2)
    {
        // should have only 2 items: CCActionManager, self
        CCLog("Error: pausedTargets should have only 2 items, and not %u", (unsigned int)c);
    }
}

void SchedulerPauseResumeAll::resume(float dt)
{
    CCLog("Resuming");
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getScheduler()->resumeTargets(m_pPausedTargets);
    CC_SAFE_RELEASE_NULL(m_pPausedTargets);
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
: m_pPausedTargets(NULL)
{

}

SchedulerPauseResumeAllUser::~SchedulerPauseResumeAllUser()
{
    CC_SAFE_RELEASE(m_pPausedTargets);
}

void SchedulerPauseResumeAllUser::onEnter()
{
    SchedulerTestLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(3.0, 360)));

    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick1), 0.5f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::tick2), 1.0f);
    schedule(schedule_selector(SchedulerPauseResumeAllUser::pause), 3.0f, false, 0);
    //TODO: [self performSelector:@selector(resume) withObject:nil afterDelay:5];
}

void SchedulerPauseResumeAllUser::onExit()
{
    if(m_pPausedTargets != NULL)
    {
        CCDirector::sharedDirector()->getScheduler()->resumeTargets(m_pPausedTargets);
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
    CCDirector* pDirector = CCDirector::sharedDirector();
    m_pPausedTargets = pDirector->getScheduler()->pauseAllTargetsWithMinPriority(kCCPriorityNonSystemMin);
    CC_SAFE_RETAIN(m_pPausedTargets);
}

void SchedulerPauseResumeAllUser::resume(float dt)
{
    CCLog("Resuming");
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getScheduler()->resumeTargets(m_pPausedTargets);
    CC_SAFE_RELEASE_NULL(m_pPausedTargets);
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(3.0, 360)));

    m_bActionManagerActive = true;

    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick1), 0.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick2), 1.0f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick3), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick4), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::unscheduleAll), 4);
}

void SchedulerUnscheduleAllHard::onExit()
{
    if(!m_bActionManagerActive) {
        // Restore the director's action manager.
        CCDirector* director = CCDirector::sharedDirector();
        director->getScheduler()->scheduleUpdateForTarget(director->getActionManager(), kCCPrioritySystem, false);
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
    CCDirector::sharedDirector()->getScheduler()->unscheduleAll();
    m_bActionManagerActive = false;
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

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(sprite);
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(3.0, 360)));

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
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllWithMinPriority(kCCPriorityNonSystemMin);
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
void TestNode::initWithString(CCString* pStr, int priority)
{
    m_pstring = pStr;
    m_pstring->retain();
    scheduleUpdateWithPriority(priority);
}

TestNode::~TestNode()
{
    m_pstring->release();
}

void TestNode::update(float dt)
{
    CCLog(m_pstring->getCString());
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
    CCString* pStr = new CCString("---");
    d->initWithString(pStr, 50);
    pStr->release();
    addChild(d);
    d->release();

    TestNode* b = new TestNode();
    pStr = new CCString("3rd");
    b->initWithString(pStr, 0);
    pStr->release();
    addChild(b);
    b->release();

    TestNode* a = new TestNode();
    pStr = new CCString("1st");
    a->initWithString(pStr, -10);
    pStr->release();
    addChild(a);
    a->release();

    TestNode* c = new TestNode();
    pStr = new CCString("4th");
    c->initWithString(pStr, 10);
    pStr->release();
    addChild(c);
    c->release();

    TestNode* e = new TestNode();
    pStr = new CCString("5th");
    e->initWithString(pStr, 20);
    pStr->release();
    addChild(e);
    e->release();

    TestNode* f = new TestNode();
    pStr = new CCString("2nd");
    f->initWithString(pStr, -5);
    pStr->release();
    addChild(f);
    f->release();

    schedule(schedule_selector(SchedulerUpdate::removeUpdates), 4.0f);
}

void SchedulerUpdate::removeUpdates(float dt)
{
    CCArray* children = getChildren();
    CCNode* pNode;
    CCObject* pObject;
    CCARRAY_FOREACH(children, pObject)
    {
        pNode = (CCNode*)pObject;

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

    m_fInterval = 1.0f;
    m_nTicks    = 0;
    schedule(schedule_selector(RescheduleSelector::schedUpdate), m_fInterval);
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
    m_nTicks++;

    CCLOG("schedUpdate: %.4f", dt);
    if ( m_nTicks > 3 )
    {
        m_fInterval += 1.0f;
        schedule(schedule_selector(RescheduleSelector::schedUpdate), m_fInterval);
        m_nTicks = 0;
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

CCControlSlider* SchedulerTimeScale::sliderCtl()
{
    CCControlSlider * slider = CCControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");

    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(SchedulerTimeScale::sliderAction), CCControlEventValueChanged);

    slider->setMinimumValue(-3.0f);
    slider->setMaximumValue(3.0f);
    slider->setValue(1.0f);

    return slider;
}

void SchedulerTimeScale::sliderAction(CCObject* pSender, CCControlEvent controlEvent)
{
    CCControlSlider* pSliderCtl = (CCControlSlider*)pSender;
    float scale;
    scale = pSliderCtl->getValue();

    CCDirector::sharedDirector()->getScheduler()->setTimeScale(scale);
}

void SchedulerTimeScale::onEnter()
{
    SchedulerTestLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // rotate and jump
    CCActionInterval *jump1 = CCJumpBy::create(4, ccp(-s.width+80,0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();
    CCActionInterval *rot1 = CCRotateBy::create(4, 360*2);
    CCActionInterval *rot2 = rot1->reverse();

    CCSequence* seq3_1 = CCSequence::create(jump2, jump1, NULL);
    CCSequence* seq3_2 = CCSequence::create(rot1, rot2, NULL);
    CCFiniteTimeAction* spawn = CCSpawn::create(seq3_1, seq3_2, NULL);
    CCRepeat* action = CCRepeat::create(spawn, 50);

    CCRepeat* action2 = (CCRepeat*)action->copy()->autorelease();
    CCRepeat* action3 = (CCRepeat*)action->copy()->autorelease();

    CCSprite *grossini = CCSprite::create("Images/grossini.png");
    CCSprite *tamara = CCSprite::create("Images/grossinis_sister1.png");
    CCSprite *kathia = CCSprite::create("Images/grossinis_sister2.png");

    grossini->setPosition(ccp(40,80));
    tamara->setPosition(ccp(40,80));
    kathia->setPosition(ccp(40,80));

    addChild(grossini);
    addChild(tamara);
    addChild(kathia);

    grossini->runAction(CCSpeed::create(action, 0.5f));
    tamara->runAction(CCSpeed::create(action2, 1.5f));
    kathia->runAction(CCSpeed::create(action3, 1.0f));

    CCParticleSystem *emitter = CCParticleFireworks::create();
    emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
    addChild(emitter);

    m_pSliderCtl = sliderCtl();
    m_pSliderCtl->setPosition(ccp(s.width / 2.0f, s.height / 3.0f));

    addChild(m_pSliderCtl);
}

void SchedulerTimeScale::onExit()
{
    // restore scale
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(1);
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

CCControlSlider *TwoSchedulers::sliderCtl()
{
   // CGRect frame = CGRectMake(12.0f, 12.0f, 120.0f, 7.0f);
    CCControlSlider *slider = CCControlSlider::create("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");
        //[[UISlider alloc] initWithFrame:frame];
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(TwoSchedulers::sliderAction), CCControlEventValueChanged);

    // in case the parent view draws with a custom color or gradient, use a transparent color
    //slider.backgroundColor = [UIColor clearColor];

    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(2.0f);
    //slider.continuous = YES;
    slider->setValue(1.0f);

    return slider;
}

void TwoSchedulers::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    float scale;

    CCControlSlider *slider = (CCControlSlider*) sender;
    scale = slider->getValue();

    if( sender == sliderCtl1 )
        sched1->setTimeScale(scale);
    else
        sched2->setTimeScale(scale);
}

void TwoSchedulers::onEnter()
{
    SchedulerTestLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

        // rotate and jump
    CCActionInterval *jump1 = CCJumpBy::create(4, ccp(0,0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();

    CCSequence* seq = CCSequence::create(jump2, jump1, NULL);
    CCRepeatForever* action = CCRepeatForever::create(seq);

        //
        // Center
        //
    CCSprite *grossini = CCSprite::create("Images/grossini.png");
    addChild(grossini);
    grossini->setPosition(ccp(s.width/2,100));
    grossini->runAction((CCAction*)action->copy()->autorelease());



    CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();

    //
    // Left:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched1 = new CCScheduler();

    defaultScheduler->scheduleUpdateForTarget(sched1, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager1 = new CCActionManager();
    sched1->scheduleUpdateForTarget(actionManager1, 0, false);

    for( unsigned int i=0; i < 10; i++ ) 
    {
        CCSprite *sprite = CCSprite::create("Images/grossinis_sister1.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager1);

        addChild(sprite);
        sprite->setPosition(ccp(30+15*i,100));

        sprite->runAction((CCAction*)action->copy()->autorelease());
    }


    //
    // Right:
    //

    // Create a new scheduler, and link it to the main scheduler
    sched2 = new CCScheduler();;
    defaultScheduler->scheduleUpdateForTarget(sched2, 0, false);

    // Create a new ActionManager, and link it to the new scheudler
    actionManager2 = new CCActionManager();
    sched2->scheduleUpdateForTarget(actionManager2, 0, false);

    for( unsigned int i=0; i < 10; i++ ) {
        CCSprite *sprite = CCSprite::create("Images/grossinis_sister2.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager2);

        addChild(sprite);
        sprite->setPosition(ccp(s.width-30-15*i,100));

        sprite->runAction((CCAction*)action->copy()->autorelease());
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
    CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();
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

class TestNode2 : public CCNode
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
    CCLayer* pLayer = nextSchedulerTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
