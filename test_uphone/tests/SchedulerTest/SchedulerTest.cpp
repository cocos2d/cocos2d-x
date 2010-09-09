#include "SchedulerTest.h"
#include "../testResource.h"

enum {
	kTagAnimationDance = 1,
};

#define MAX_TESTS           8
static int sceneIdx = -1;

CCLayer* createSchedulerTest(int nIndex)
{
    CCLayer* pLayer = NULL;

    switch (nIndex)
    {
    case 0:
        pLayer = new SchedulerAutoremove(); break;
    case 1:
        pLayer = new SchedulerPauseResume(); break;
    case 2:
        pLayer = new SchedulerUnscheduleAll(); break;
    case 3:
        pLayer = new SchedulerUnscheduleAllHard(); break;
    case 4:
        pLayer = new SchedulerSchedulesAndRemove(); break;
    case 5:
        pLayer = new SchedulerUpdate(); break;
    case 6:
        pLayer = new SchedulerUpdateAndCustom(); break;
    case 7:
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

    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(s.width/2, s.height-50));

    std::string subTitle = subtitle();
    if(! subTitle.empty())
    {
        CCLabel* l = CCLabel::labelWithString(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }

    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(SchedulerTestLayer::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(SchedulerTestLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(SchedulerTestLayer::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
    menu->setPosition(CGPointZero);
    item1->setPosition(ccp( s.width/2 - 100,30));
    item2->setPosition(ccp( s.width/2, 30));
    item3->setPosition(ccp( s.width/2 + 100,30));

    addChild(menu, 1);
}

void SchedulerTestLayer::backCallback(NSObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = backSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::getSharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::nextCallback(NSObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = nextSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::getSharedDirector()->replaceScene(pScene);
    pScene->release();
}

void SchedulerTestLayer::restartCallback(NSObject* pSender)
{
    CCScene* pScene = new SchedulerTestScene();
    CCLayer* pLayer = restartSchedulerTest();

    pScene->addChild(pLayer);
    CCDirector::getSharedDirector()->replaceScene(pScene);
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
    ////NSLog(@"Time: %f", accum);

    if( accum > 3 )
    {
        unschedule(schedule_selector(SchedulerAutoremove::autoremove));
        ////NSLog(@"scheduler removed");
    }
}

void SchedulerAutoremove::tick(ccTime dt)
{
    ////NSLog(@"This scheduler should not be removed");
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
    ////NSLog(@"tick1");
}

void SchedulerPauseResume::tick2(ccTime dt)
{
    ////NSLog(@"tick1");
}

void SchedulerPauseResume::pause(ccTime dt)
{
    CCScheduler::getSharedScheduler()->pauseTarget(this);
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
    ////NSLog(@"tick1");
}

void SchedulerUnscheduleAll::tick2(ccTime dt)
{
    ////NSLog(@"tick2");
}

void SchedulerUnscheduleAll::tick3(ccTime dt)
{
    ////NSLog(@"tick3");
}

void SchedulerUnscheduleAll::tick4(ccTime dt)
{
    ////NSLog(@"tick4");
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
    ////NSLog(@"tick1");
}

void SchedulerUnscheduleAllHard::tick2(ccTime dt)
{
    ////NSLog(@"tick2");
}

void SchedulerUnscheduleAllHard::tick3(ccTime dt)
{
    ////NSLog(@"tick3");
}

void SchedulerUnscheduleAllHard::tick4(ccTime dt)
{
    ////NSLog(@"tick4");
}

void SchedulerUnscheduleAllHard::unscheduleAll(ccTime dt)
{
    CCScheduler::getSharedScheduler()->unscheduleAllSelectors();
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
    ////NSLog(@"tick1");
}

void SchedulerSchedulesAndRemove::tick2(ccTime dt)
{
    ////NSLog(@"tick2");
}

void SchedulerSchedulesAndRemove::tick3(ccTime dt)
{
    ////NSLog(@"tick3");
}

void SchedulerSchedulesAndRemove::tick4(ccTime dt)
{
    ////NSLog(@"tick4");
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
void TestNode::initWithString(NSString* pStr, int priority)
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
    NSString* pStr = new NSString("---");
    d->initWithString(pStr, 50);
    pStr->release();
    addChild(d);
    d->release();

    TestNode* b = new TestNode();
    pStr = new NSString("3rd");
    b->initWithString(pStr, 0);
    pStr->release();
    addChild(b);
    b->release();

    TestNode* a = new TestNode();
    pStr = new NSString("1st");
    a->initWithString(pStr, -10);
    pStr->release();
    addChild(a);
    a->release();

    TestNode* c = new TestNode();
    pStr = new NSString("4th");
    c->initWithString(pStr, 10);
    pStr->release();
    addChild(c);
    c->release();

    TestNode* e = new TestNode();
    pStr = new NSString("5th");
    e->initWithString(pStr, 20);
    pStr->release();
    addChild(e);
    e->release();

    TestNode* f = new TestNode();
    pStr = new NSString("2nd");
    f->initWithString(pStr, -5);
    pStr->release();
    addChild(f);
    f->release();

    schedule(schedule_selector(SchedulerUpdate::removeUpdates), 4.0f);
}

void SchedulerUpdate::removeUpdates(ccTime dt)
{
    NSMutableArray<CCNode*> * children = getChildren();
    NSMutableArray<CCNode*>::NSMutableArrayIterator it;

    CCNode* pNode;
    for (it = children->begin(); it != children->end(); it++)
    {
        pNode = (CCNode*)(*it);

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
    ////NSLog(@"update called:%f", dt);
}

void SchedulerUpdateAndCustom::tick(ccTime dt)
{
    ////NSLog(@"custom selector called:%f",dt);
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
    ////NSLog(@"update called:%f", dt);
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
// SchedulerTestScene
//
//------------------------------------------------------------------
void SchedulerTestScene::runThisTest()
{
    CCLayer* pLayer = nextSchedulerTest();
    addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene(this);
}
