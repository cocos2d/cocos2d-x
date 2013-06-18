#include "MotionStreakTest.h"
#include "../testResource.h"

enum {
	kTagLabel = 1,
	kTagSprite1 = 2,
	kTagSprite2 = 3,
};

CCLayer* nextMotionAction();
CCLayer* backMotionAction();
CCLayer* restartMotionAction();

//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
    MotionStreakTest::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();
  
    // the root object just rotates around
    _root = CCSprite::create(s_pPathR1);
    addChild(_root, 1);
    _root->setPosition(ccp(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    _target = CCSprite::create(s_pPathR1);
    _root->addChild(_target);
    _target->setPosition(ccp(s.width/4, 0));

    // create the streak object and add it to the scene
    streak = CCMotionStreak::create(2, 3, 32, ccGREEN, s_streak);
    addChild(streak);
    // schedule an update on each frame so we can syncronize the streak with the target
    schedule(schedule_selector(MotionStreakTest1::onUpdate));
  
    CCActionInterval* a1 = CCRotateBy::create(2, 360);

    CCAction* action1 = CCRepeatForever::create(a1);
    CCActionInterval* motion = CCMoveBy::create(2, ccp(100,0) );
    _root->runAction( CCRepeatForever::create(CCSequence::create(motion, motion->reverse(), NULL) ) );
    _root->runAction( action1 );

    CCActionInterval *colorAction = CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(0.2f, 255, 0, 0),
        CCTintTo::create(0.2f, 0, 255, 0),
        CCTintTo::create(0.2f, 0, 0, 255),
        CCTintTo::create(0.2f, 0, 255, 255),
        CCTintTo::create(0.2f, 255, 255, 0),
        CCTintTo::create(0.2f, 255, 0, 255),
        CCTintTo::create(0.2f, 255, 255, 255),
        NULL));

    streak->runAction(colorAction);
}

void MotionStreakTest1::onUpdate(float delta)
{
    streak->setPosition( _target->convertToWorldSpace(CCPointZero) );
}

std::string MotionStreakTest1::title()
{
    return "MotionStreak test 1";
}

//------------------------------------------------------------------
//
// MotionStreakTest2
//
//------------------------------------------------------------------

void MotionStreakTest2::onEnter()
{
    MotionStreakTest::onEnter();

    setTouchEnabled(true);

    CCSize s = CCDirector::sharedDirector()->getWinSize();
        
    // create the streak object and add it to the scene
    streak = CCMotionStreak::create(3, 3, 64, ccWHITE, s_streak );
    addChild(streak);
    
    streak->setPosition( ccp(s.width/2, s.height/2) ); 
}

void MotionStreakTest2::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCSetIterator it = touches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    
    streak->setPosition( touchLocation );
}

std::string MotionStreakTest2::title()
{
    return "MotionStreak test";
}

//------------------------------------------------------------------
//
// Issue1358
//
//------------------------------------------------------------------

void Issue1358::onEnter()
{
    MotionStreakTest::onEnter();
    
    // ask director the the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    streak = CCMotionStreak::create(2.0f, 1.0f, 50.0f, ccc3(255, 255, 0), "Images/Icon.png");
    addChild(streak);
    
    
    _center  = ccp(size.width/2, size.height/2);
    _radius = size.width/3;
    _angle = 0.0f;
    
    schedule(schedule_selector(Issue1358::update), 0);
}

void Issue1358::update(float dt)
{
    _angle += 1.0f;
    streak->setPosition(ccp(_center.x + cosf(_angle/180 * M_PI)*_radius,
                            _center.y + sinf(_angle/ 180 * M_PI)*_radius));
}

std::string Issue1358::title()
{
    return "Issue 1358";
}

std::string Issue1358::subtitle()
{
    return "The tail should use the texture";
}

//------------------------------------------------------------------
//
// MotionStreakTest
//
//------------------------------------------------------------------

// enum
// {
//     IDC_NEXT = 100,
//     IDC_BACK,
//     IDC_RESTART
// };

static int sceneIdx = -1; 

#define MAX_LAYER    3

CCLayer* createMotionLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new MotionStreakTest1();
        case 1: return new MotionStreakTest2();
        case 2: return new Issue1358();
    }

    return NULL;
}

CCLayer* nextMotionAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backMotionAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartMotionAction()
{
    CCLayer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


MotionStreakTest::MotionStreakTest(void)
{
}

MotionStreakTest::~MotionStreakTest(void)
{
}

std::string MotionStreakTest::title()
{
    return "No title";
}

std::string MotionStreakTest::subtitle()
{
    return "";
}

void MotionStreakTest::onEnter()
{
    BaseTest::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemToggle *itemMode = CCMenuItemToggle::createWithCallback( CC_CALLBACK_1(MotionStreakTest::modeCallback, this),
        CCMenuItemFont::create("Use High Quality Mode"),
        CCMenuItemFont::create("Use Fast Mode"),
        NULL);

    CCMenu *menuMode = CCMenu::create(itemMode, NULL);
    addChild(menuMode);

    menuMode->setPosition(ccp(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(CCObject *pSender)
{
    bool fastMode = streak->isFastMode();
    streak->setFastMode(! fastMode);
}

void MotionStreakTest::restartCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild(restartMotionAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::nextCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild( nextMotionAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::backCallback(CCObject* pSender)
{
    CCScene* s = new MotionStreakTestScene;//CCScene::create();
    s->addChild( backMotionAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void MotionStreakTestScene::runThisTest()
{
    CCLayer* pLayer = nextMotionAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
