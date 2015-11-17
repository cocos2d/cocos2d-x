#include "MotionStreakTest.h"
#include "../testResource.h"

USING_NS_CC;

enum {
	kTagLabel = 1,
	kTagSprite1 = 2,
	kTagSprite2 = 3,
};

MotionStreakTests::MotionStreakTests()
{
    ADD_TEST_CASE(MotionStreakTest1);
    ADD_TEST_CASE(MotionStreakTest2);
    ADD_TEST_CASE(Issue1358);
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
    _root->setPosition(Vec2(s.width/2, s.height/2));
  
    // the target object is offset from root, and the streak is moved to follow it
    _target = Sprite::create(s_pathR1);
    _root->addChild(_target);
    _target->setPosition(Vec2(s.width/4, 0));

    // create the streak object and add it to the scene
    streak = MotionStreak::create(2, 3, 32, Color3B::GREEN, s_streak);
    addChild(streak);
    // schedule an update on each frame so we can syncronize the streak with the target
    schedule(CC_SCHEDULE_SELECTOR(MotionStreakTest1::onUpdate));
  
    auto a1 = RotateBy::create(2, 360);

    auto action1 = RepeatForever::create(a1);
    auto motion = MoveBy::create(2, Vec2(100,0) );
    _root->runAction( RepeatForever::create(Sequence::create(motion, motion->reverse(), nullptr) ) );
    _root->runAction( action1 );

    auto colorAction = RepeatForever::create(Sequence::create(
        TintTo::create(0.2f, 255, 0, 0),
        TintTo::create(0.2f, 0, 255, 0),
        TintTo::create(0.2f, 0, 0, 255),
        TintTo::create(0.2f, 0, 255, 255),
        TintTo::create(0.2f, 255, 255, 0),
        TintTo::create(0.2f, 255, 0, 255),
        TintTo::create(0.2f, 255, 255, 255),
        nullptr));

    streak->runAction(colorAction);
}

void MotionStreakTest1::onUpdate(float delta)
{
    streak->setPosition( _target->convertToWorldSpace(Vec2::ZERO) );
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
    
    streak->setPosition( Vec2(s.width/2, s.height/2) ); 
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
    
    
    _center  = Vec2(size.width/2, size.height/2);
    _radius = size.width/3;
    _angle = 0.0f;
    
    schedule(CC_SCHEDULE_SELECTOR(Issue1358::update), 0);
}

void Issue1358::update(float dt)
{
    _angle += 1.0f;
    streak->setPosition(Vec2(_center.x + cosf(_angle/180 * M_PI)*_radius,
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
    TestCase::onEnter();

    auto s = Director::getInstance()->getWinSize();

    auto itemMode = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MotionStreakTest::modeCallback, this),
        MenuItemFont::create("Use High Quality Mode"),
        MenuItemFont::create("Use Fast Mode"),
        nullptr);

    auto menuMode = Menu::create(itemMode, nullptr);
    addChild(menuMode);

    menuMode->setPosition(Vec2(s.width/2, s.height/4));
}

void MotionStreakTest::modeCallback(Ref *pSender)
{
    bool fastMode = streak->isFastMode();
    streak->setFastMode(! fastMode);
}
