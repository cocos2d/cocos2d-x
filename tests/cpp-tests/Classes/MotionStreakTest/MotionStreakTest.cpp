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

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
	CL(MotionStreakTest1),
    CL(MotionStreakTest2),
    CL(Issue1358),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

Layer* nextMotionAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* backMotionAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

Layer* restartMotionAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}
//------------------------------------------------------------------
//
// MotionStreakTest1
//
//------------------------------------------------------------------

void MotionStreakTest1::onEnter()
{
    MotionStreakTest::onEnter();

    auto s = Director::getInstance()->getWinSize();
  
    // the root object just rotates around
    _root = Sprite::create(s_pathR1);
    addChild(_root, 1);
    _root->setPosition(Vector2(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    _target = Sprite::create(s_pathR1);
    _root->addChild(_target);
    _target->setPosition(Vector2(s.width/4, 0));

    // create the streak object and add it to the scene
    streak = MotionStreak::create(2, 3, 32, Color3B::GREEN, s_streak);
    addChild(streak);
    // schedule an update on each frame so we can syncronize the streak with the target
    schedule(schedule_selector(MotionStreakTest1::onUpdate));
  
    auto a1 = RotateBy::create(2, 360);

    auto action1 = RepeatForever::create(a1);
    auto motion = MoveBy::create(2, Vector2(100,0) );
    _root->runAction( RepeatForever::create(Sequence::create(motion, motion->reverse(), NULL) ) );
    _root->runAction( action1 );

    auto colorAction = RepeatForever::create(Sequence::create(
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
    streak->setPosition( _target->convertToWorldSpace(Vector2::ZERO) );
}

std::string MotionStreakTest1::title() const
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

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(MotionStreakTest2::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();
        
    // create the streak object and add it to the scene
    streak = MotionStreak::create(3, 3, 64, Color3B::WHITE, s_streak );
    addChild(streak);
    
    streak->setPosition( Vector2(s.width/2, s.height/2) ); 
}

void MotionStreakTest2::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    auto touchLocation = touches[0]->getLocation();
    
    streak->setPosition( touchLocation );
}

std::string MotionStreakTest2::title() const
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
    auto size = Director::getInstance()->getWinSize();
    
    streak = MotionStreak::create(2.0f, 1.0f, 50.0f, Color3B(255, 255, 0), "Images/Icon.png");
    addChild(streak);
    
    
    _center  = Vector2(size.width/2, size.height/2);
    _radius = size.width/3;
    _angle = 0.0f;
    
    schedule(schedule_selector(Issue1358::update), 0);
}

void Issue1358::update(float dt)
{
    _angle += 1.0f;
    streak->setPosition(Vector2(_center.x + cosf(_angle/180 * M_PI)*_radius,
                            _center.y + sinf(_angle/ 180 * M_PI)*_radius));
}

std::string Issue1358::title() const
{
    return "Issue 1358";
}

std::string Issue1358::subtitle() const
{
    return "The tail should use the texture";
}

//------------------------------------------------------------------
//
// MotionStreakTest
//
//------------------------------------------------------------------

MotionStreakTest::MotionStreakTest(void)
{
}

MotionStreakTest::~MotionStreakTest(void)
{
}

std::string MotionStreakTest::title() const
{
    return "No title";
}

std::string MotionStreakTest::subtitle() const
{
    return "";
}

void MotionStreakTest::onEnter()
{
    BaseTest::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto itemMode = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MotionStreakTest::modeCallback, this),
        MenuItemFont::create("Use High Quality Mode"),
        MenuItemFont::create("Use Fast Mode"),
        NULL);

    auto menuMode = Menu::create(itemMode, NULL);
    addChild(menuMode);

    menuMode->setPosition(Vector2(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(Ref *pSender)
{
    bool fastMode = streak->isFastMode();
    streak->setFastMode(! fastMode);
}

void MotionStreakTest::restartCallback(Ref* sender)
{
    auto s = new MotionStreakTestScene();//CCScene::create();
    s->addChild(restartMotionAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void MotionStreakTest::nextCallback(Ref* sender)
{
    auto s = new MotionStreakTestScene();//CCScene::create();
    s->addChild( nextMotionAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void MotionStreakTest::backCallback(Ref* sender)
{
    auto s = new MotionStreakTestScene;//CCScene::create();
    s->addChild( backMotionAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void MotionStreakTestScene::runThisTest()
{
    auto layer = nextMotionAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
