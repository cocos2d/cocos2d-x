#include "SchedulerTest.h"
#include "../testResource.h"

enum {
    kTagAnimationDance = 1,
};

#define MAX_TESTS           11
static int sceneIdx = -1;

CCLayer* nextSchedulerTest();
CCLayer* backSchedulerTest();
CCLayer* restartSchedulerTest();

CCLayer* createSchedulerTest(int nIndex)
{
    CCLayer* pLayer = NULL;

    switch (nIndex)
    {
    case 0:
        pLayer = new SchedulerDelayAndRepeat(); break;
    case 1:
        pLayer = new SchedulerTimeScale(); break;
    case 2:
        pLayer = new TwoSchedulers(); break;
    case 3:
        pLayer = new SchedulerAutoremove(); break;
    case 4:
        pLayer = new SchedulerPauseResume(); break;
    case 5:
        pLayer = new SchedulerUnscheduleAll(); break;
    case 6:
        pLayer = new SchedulerUnscheduleAllHard(); break;
    case 7:
        pLayer = new SchedulerSchedulesAndRemove(); break;
    case 8:
        pLayer = new SchedulerUpdate(); break;
    case 9:
        pLayer = new SchedulerUpdateAndCustom(); break;
    case 10:
        pLayer = new SchedulerUpdateFromCustom(); break;
    default:
        break;
    }
    pLayer->autorelease();

    return pLayer;
}

CCLayer* nextSchedulerTest()
{

    sceneIdx++;
    sceneIdx = sceneIdx % MAX_TESTS;

    return createSchedulerTest(sceneIdx);
}

CCLayer* backSchedulerTest()
{
    sceneIdx--;
    if( sceneIdx < 0 )
        sceneIdx += MAX_TESTS;

    return createSchedulerTest(sceneIdx);
}

CCLayer* restartSchedulerTest()
{
    return createSchedulerTest(sceneIdx);
}

//------------------------------------------------------------------
//
// SchedulerTestLayer
//
//------------------------------------------------------------------
void SchedulerTestLayer::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(s.width/2, s.height-50));

    std::string subTitle = subtitle();
    if(! subTitle.empty())
    {
        CCLabelTTF* l = CCLabelTTF::labelWithString(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::itemWithNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(SchedulerTestLayer::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::itemWithNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(SchedulerTestLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemWithNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(SchedulerTestLayer::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    item1->setPosition(ccp( s.width/2 - 100,30));
    item2->setPosition(ccp( s.width/2, 30));
    item3->setPosition(ccp( s.width/2 + 100,30));

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

void SchedulerAutoremove::autoremove(ccTime dt)
{
    accum += dt;
    CCLOG("Time: %f", accum);

    if( accum > 3 )
    {
        unschedule(schedule_selector(SchedulerAutoremove::autoremove));
        CCLOG("scheduler removed");
    }
}

void SchedulerAutoremove::tick(ccTime dt)
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

void SchedulerPauseResume::tick1(ccTime dt)
{
    CCLOG("tick1");
}

void SchedulerPauseResume::tick2(ccTime dt)
{
    CCLOG("tick2");
}

void SchedulerPauseResume::pause(ccTime dt)
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

void SchedulerUnscheduleAll::tick1(ccTime dt)
{
    CCLOG("tick1");
}

void SchedulerUnscheduleAll::tick2(ccTime dt)
{
    CCLOG("tick2");
}

void SchedulerUnscheduleAll::tick3(ccTime dt)
{
    CCLOG("tick3");
}

void SchedulerUnscheduleAll::tick4(ccTime dt)
{
    CCLOG("tick4");
}

void SchedulerUnscheduleAll::unscheduleAll(ccTime dt)
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

    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick1), 0.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick2), 1.0f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick3), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::tick4), 1.5f);
    schedule(schedule_selector(SchedulerUnscheduleAllHard::unscheduleAll), 4);
}

void SchedulerUnscheduleAllHard::tick1(ccTime dt)
{
    CCLOG("tick1");
}

void SchedulerUnscheduleAllHard::tick2(ccTime dt)
{
    CCLOG("tick2");
}

void SchedulerUnscheduleAllHard::tick3(ccTime dt)
{
    CCLOG("tick3");
}

void SchedulerUnscheduleAllHard::tick4(ccTime dt)
{
    CCLOG("tick4");
}

void SchedulerUnscheduleAllHard::unscheduleAll(ccTime dt)
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectors();
}

std::string SchedulerUnscheduleAllHard::title()
{
    return "Unschedule All selectors #2";
}

std::string SchedulerUnscheduleAllHard::subtitle()
{
    return "Unschedules all selectors after 4s. Uses CCScheduler. See console";
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

void SchedulerSchedulesAndRemove::tick1(ccTime dt)
{
    CCLOG("tick1");
}

void SchedulerSchedulesAndRemove::tick2(ccTime dt)
{
    CCLOG("tick2");
}

void SchedulerSchedulesAndRemove::tick3(ccTime dt)
{
    CCLOG("tick3");
}

void SchedulerSchedulesAndRemove::tick4(ccTime dt)
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

void SchedulerSchedulesAndRemove::scheduleAndUnschedule(ccTime dt)
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

void SchedulerUpdate::removeUpdates(ccTime dt)
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

void SchedulerUpdateAndCustom::update(ccTime dt)
{
    CCLOG("update called:%f", dt);
}

void SchedulerUpdateAndCustom::tick(ccTime dt)
{
    CCLOG("custom selector called:%f",dt);
}

void SchedulerUpdateAndCustom::stopSelectors(ccTime dt)
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

void SchedulerUpdateFromCustom::update(ccTime dt)
{
    CCLOG("update called:%f", dt);
}

void SchedulerUpdateFromCustom::schedUpdate(ccTime dt)
{
    unschedule(schedule_selector(SchedulerUpdateFromCustom::schedUpdate));
    scheduleUpdate();
    schedule(schedule_selector(SchedulerUpdateFromCustom::stopUpdate), 2.0f);
}

void SchedulerUpdateFromCustom::stopUpdate(ccTime dt)
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

void RescheduleSelector::schedUpdate(ccTime dt)
{
    m_nTicks++;

    CCLOG("schedUpdate: %.2f", dt);
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

void SchedulerDelayAndRepeat::update(ccTime dt)
{
    CCLog("update called:%f", dt);
}

// SchedulerTimeScale

CCControlSlider* SchedulerTimeScale::sliderCtl()
{
    CCControlSlider * slider = CCControlSlider::sliderWithFiles("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");

    slider->addTargetWithActionForControlEvents(this, menu_selector(SchedulerTimeScale::sliderAction), CCControlEventValueChanged);

    slider->setMinimumValue(-3.0f);
    slider->setMaximumValue(3.0f);
    slider->setValue(1.0f);

    return slider;
}

void SchedulerTimeScale::sliderAction(CCObject* pSender)
{
    CCControlSlider* pSliderCtl = (CCControlSlider*)pSender;
    ccTime scale;
    scale = pSliderCtl->getValue();

    CCDirector::sharedDirector()->getScheduler()->setTimeScale(scale);
}

void SchedulerTimeScale::onEnter()
{
    SchedulerTestLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // rotate and jump
    CCActionInterval *jump1 = CCJumpBy::actionWithDuration(4, ccp(-s.width+80,0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();
    CCActionInterval *rot1 = CCRotateBy::actionWithDuration(4, 360*2);
    CCActionInterval *rot2 = rot1->reverse();

    CCFiniteTimeAction* seq3_1 = CCSequence::actions(jump2, jump1, NULL);
    CCFiniteTimeAction* seq3_2 = CCSequence::actions(rot1, rot2, NULL);
    CCFiniteTimeAction* spawn = CCSpawn::actions(seq3_1, seq3_2, NULL);
    CCRepeat* action = CCRepeat::actionWithAction(spawn, 50);

    CCRepeat* action2 = (CCRepeat*)action->copy()->autorelease();
    CCRepeat* action3 = (CCRepeat*)action->copy()->autorelease();

    CCSprite *grossini = CCSprite::spriteWithFile("Images/grossini.png");
    CCSprite *tamara = CCSprite::spriteWithFile("Images/grossinis_sister1.png");
    CCSprite *kathia = CCSprite::spriteWithFile("Images/grossinis_sister2.png");

    grossini->setPosition(ccp(40,80));
    tamara->setPosition(ccp(40,80));
    kathia->setPosition(ccp(40,80));

    addChild(grossini);
    addChild(tamara);
    addChild(kathia);

    grossini->runAction(CCSpeed::actionWithAction(action, 0.5f));
    tamara->runAction(CCSpeed::actionWithAction(action2, 1.5f));
    kathia->runAction(CCSpeed::actionWithAction(action3, 1.0f));

    CCParticleSystem *emitter = CCParticleFireworks::node();
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
    CCControlSlider *slider = CCControlSlider::sliderWithFiles("extensions/sliderTrack2.png","extensions/sliderProgress2.png" ,"extensions/sliderThumb.png");
        //[[UISlider alloc] initWithFrame:frame];
    slider->addTargetWithActionForControlEvents(this, menu_selector(TwoSchedulers::sliderAction), CCControlEventValueChanged);

    // in case the parent view draws with a custom color or gradient, use a transparent color
    //slider.backgroundColor = [UIColor clearColor];

    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(2.0f);
    //slider.continuous = YES;
    slider->setValue(1.0f);

    return slider;
}

void TwoSchedulers::sliderAction(CCObject* sender)
{
    ccTime scale;

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
    CCActionInterval *jump1 = CCJumpBy::actionWithDuration(4, ccp(0,0), 100, 4);
    CCActionInterval *jump2 = jump1->reverse();

    CCFiniteTimeAction* seq = CCSequence::actions(jump2, jump1, NULL);
    CCRepeatForever* action = CCRepeatForever::actionWithAction((CCActionInterval *)seq);

        //
        // Center
        //
    CCSprite *grossini = CCSprite::spriteWithFile("Images/grossini.png");
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
        CCSprite *sprite = CCSprite::spriteWithFile("Images/grossinis_sister1.png");

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
        CCSprite *sprite = CCSprite::spriteWithFile("Images/grossinis_sister2.png");

        // IMPORTANT: Set the actionManager running any action
        sprite->setActionManager(actionManager2);

        addChild(sprite);
        sprite->setPosition(ccp(s.width-30-15*i,100));

        sprite->runAction((CCAction*)action->copy()->autorelease());
    }

    sliderCtl1 = sliderCtl();
    addChild(sliderCtl1);
    sliderCtl1->retain();
    sliderCtl1->setPosition(ccp(s.width / 4.0f, s.height - 20));

    sliderCtl2 = sliderCtl();
    addChild(sliderCtl2);
    sliderCtl2->retain();
    sliderCtl2->setPosition(ccp(s.width / 4.0f*3.0f, s.height-20));
}


TwoSchedulers::~TwoSchedulers()
{
    CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();
    defaultScheduler->unscheduleAllSelectorsForTarget(sched1);
    defaultScheduler->unscheduleAllSelectorsForTarget(sched2);

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
