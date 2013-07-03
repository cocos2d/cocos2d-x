#include "MotionStreakTest.h"
#include "../testResource.h"

enum {
	kTagLabel = 1,
	kTagSprite1 = 2,
	kTagSprite2 = 3,
};

Layer* nextMotionAction();
Layer* backMotionAction();
Layer* restartMotionAction();

//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
    MotionStreakTest::onEnter();

    Size s = Director::sharedDirector()->getWinSize();
  
    // the root object just rotates around
    _root = Sprite::create(s_pPathR1);
    addChild(_root, 1);
    _root->setPosition(ccp(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    _target = Sprite::create(s_pPathR1);
    _root->addChild(_target);
    _target->setPosition(ccp(s.width/4, 0));

    // create the streak object and add it to the scene
    streak = MotionStreak::create(2, 3, 32, ccGREEN, s_streak);
    addChild(streak);
    // schedule an update on each frame so we can syncronize the streak with the target
    schedule(schedule_selector(MotionStreakTest1::onUpdate));
  
    ActionInterval* a1 = RotateBy::create(2, 360);

    Action* action1 = RepeatForever::create(a1);
    ActionInterval* motion = MoveBy::create(2, ccp(100,0) );
    _root->runAction( RepeatForever::create(Sequence::create(motion, motion->reverse(), NULL) ) );
    _root->runAction( action1 );

    ActionInterval *colorAction = RepeatForever::create(Sequence::create(
        TintTo::create(0.2f, 255, 0, 0),
        TintTo::create(0.2f, 0, 255, 0),
        TintTo::create(0.2f, 0, 0, 255),
        TintTo::create(0.2f, 0, 255, 255),
        TintTo::create(0.2f, 255, 255, 0),
        TintTo::create(0.2f, 255, 0, 255),
        TintTo::create(0.2f, 255, 255, 255),
        NULL));

    streak->runAction(colorAction);
}

void MotionStreakTest1::onUpdate(float delta)
{
    streak->setPosition( _target->convertToWorldSpace(PointZero) );
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

    Size s = Director::sharedDirector()->getWinSize();
        
    // create the streak object and add it to the scene
    streak = MotionStreak::create(3, 3, 64, ccWHITE, s_streak );
    addChild(streak);
    
    streak->setPosition( ccp(s.width/2, s.height/2) ); 
}

void MotionStreakTest2::ccTouchesMoved(Set* touches, Event* event)
{
    Touch* touch = (Touch*) touches->anyObject();

    Point touchLocation = touch->getLocation();    
    
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
    Size size = Director::sharedDirector()->getWinSize();
    
    streak = MotionStreak::create(2.0f, 1.0f, 50.0f, ccc3(255, 255, 0), "Images/Icon.png");
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

Layer* createMotionLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new MotionStreakTest1();
        case 1: return new MotionStreakTest2();
        case 2: return new Issue1358();
    }

    return NULL;
}

Layer* nextMotionAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backMotionAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createMotionLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartMotionAction()
{
    Layer* pLayer = createMotionLayer(sceneIdx);
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

    Size s = Director::sharedDirector()->getWinSize();

    MenuItemToggle *itemMode = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MotionStreakTest::modeCallback, this),
        MenuItemFont::create("Use High Quality Mode"),
        MenuItemFont::create("Use Fast Mode"),
        NULL);

    Menu *menuMode = Menu::create(itemMode, NULL);
    addChild(menuMode);

    menuMode->setPosition(ccp(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(Object *pSender)
{
    bool fastMode = streak->isFastMode();
    streak->setFastMode(! fastMode);
}

void MotionStreakTest::restartCallback(Object* pSender)
{
    Scene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild(restartMotionAction()); 

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::nextCallback(Object* pSender)
{
    Scene* s = new MotionStreakTestScene();//CCScene::create();
    s->addChild( nextMotionAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void MotionStreakTest::backCallback(Object* pSender)
{
    Scene* s = new MotionStreakTestScene;//CCScene::create();
    s->addChild( backMotionAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
} 

void MotionStreakTestScene::runThisTest()
{
    Layer* pLayer = nextMotionAction();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
}
