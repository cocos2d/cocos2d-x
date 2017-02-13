/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "NodeTest.h"
#include <regex>
#include "../testResource.h"

USING_NS_CC;

enum 
{
    kTagSprite1 = 1,
    kTagSprite2 = 2,
    kTagSprite3 = 3,
    kTagSlider,
};


//------------------------------------------------------------------
//
// TestCocosNodeDemo
//
//------------------------------------------------------------------

CocosNodeTests::CocosNodeTests()
{
    //ADD_TEST_CASE(CameraTest1);
    // TODO: Camera has been removed from CCNode; add new feature to support it
    // ADD_TEST_CASE(CameraTest2);
    //ADD_TEST_CASE(CameraCenterTest);
    ADD_TEST_CASE(NodeTest2);
    ADD_TEST_CASE(NodeTest4);
    ADD_TEST_CASE(NodeTest5);
    ADD_TEST_CASE(NodeTest6);
    ADD_TEST_CASE(StressTest1);
    ADD_TEST_CASE(StressTest2);
    ADD_TEST_CASE(NodeToWorld);
    ADD_TEST_CASE(NodeToWorld3D);
    ADD_TEST_CASE(SchedulerTest1);
    ADD_TEST_CASE(SchedulerCallbackTest);
    ADD_TEST_CASE(CameraOrbitTest);
    // TODO: Camera has been removed from CCNode; add new feature to support it
    //ADD_TEST_CASE(CameraZoomTest);
    ADD_TEST_CASE(ConvertToNode);
    ADD_TEST_CASE(NodeOpaqueTest);
    ADD_TEST_CASE(NodeNonOpaqueTest);
    ADD_TEST_CASE(NodeGlobalZValueTest);
    ADD_TEST_CASE(NodeNormalizedPositionTest1);
    ADD_TEST_CASE(NodeNormalizedPositionTest2);
    ADD_TEST_CASE(NodeNormalizedPositionBugTest);
    ADD_TEST_CASE(NodeNameTest);
    ADD_TEST_CASE(Issue16100Test);
    ADD_TEST_CASE(Issue16735Test);
}

TestCocosNodeDemo::TestCocosNodeDemo(void)
{
}

TestCocosNodeDemo::~TestCocosNodeDemo(void)
{
}

std::string TestCocosNodeDemo::title() const
{
    return "Node Test";
}

//------------------------------------------------------------------
//
// NodeTest2
//
//------------------------------------------------------------------

void NodeTest2::onEnter()
{
    TestCocosNodeDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();
    
    auto sp1 = Sprite::create(s_pathSister1);
    auto sp2 = Sprite::create(s_pathSister2);
    auto sp3 = Sprite::create(s_pathSister1);
    auto sp4 = Sprite::create(s_pathSister2);
    
    sp1->setPosition(Vec2(100, s.height /2 ));
    sp2->setPosition(Vec2(380, s.height /2 ));
    addChild(sp1);
    addChild(sp2);
    
    sp3->setScale(0.25f);
    sp4->setScale(0.25f);
    
    sp1->addChild(sp3);
    sp2->addChild(sp4);
    
    auto a1 = RotateBy::create(2, 360);
    auto a2 = ScaleBy::create(2, 2);
    
    auto action1 = RepeatForever::create( Sequence::create(a1, a2, a2->reverse(), nullptr) );
    auto action2 = RepeatForever::create( Sequence::create(
																	a1->clone(),
																	a2->clone(),
																	a2->reverse(),
																	nullptr)
												);
    
    sp2->setAnchorPoint(Vec2(0,0));
    
    sp1->runAction(action1);
    sp2->runAction(action2);
}

std::string NodeTest2::subtitle() const
{
    return "anchorPoint and children";
}


//------------------------------------------------------------------
//
// NodeTest4
//
//------------------------------------------------------------------
#define SID_DELAY2        1
#define SID_DELAY4        2

NodeTest4::NodeTest4()
{
    auto sp1 = Sprite::create(s_pathSister1);
    auto sp2 = Sprite::create(s_pathSister2);
    
    sp1->setPosition( Vec2(100,160) );
    sp2->setPosition( Vec2(380,160) );
    
    addChild(sp1, 0, 2);
    addChild(sp2, 0, 3);
    
    schedule(CC_CALLBACK_1(NodeTest4::delay2, this), 2.0f, "delay2_key");
    schedule(CC_CALLBACK_1(NodeTest4::delay4, this), 4.0f, "delay4_key");
}

void NodeTest4::delay2(float dt)
{
    auto node = static_cast<Sprite*>(getChildByTag(2));
    auto action1 = RotateBy::create(1, 360);
    node->runAction(action1);
}

void NodeTest4::delay4(float dt)
{
    unschedule("delay4_key");
    removeChildByTag(3, false);
}

std::string NodeTest4::subtitle() const
{
    return "tags";
}


//------------------------------------------------------------------
//
// NodeTest5
//
//------------------------------------------------------------------
NodeTest5::NodeTest5()
{
    auto sp1 = Sprite::create(s_pathSister1);
    auto sp2 = Sprite::create(s_pathSister2);
    
    sp1->setPosition(Vec2(100,160));
    sp2->setPosition(Vec2(380,160));

    auto rot = RotateBy::create(2, 360);
    auto rot_back = rot->reverse();
    auto forever = RepeatForever::create(Sequence::create(rot, rot_back, nullptr));
    auto forever2 = forever->clone();
    forever->setTag(101);
    forever2->setTag(102);
                                                  
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
            
    sp1->runAction(forever);
    sp2->runAction(forever2);
    
    schedule(CC_CALLBACK_1(NodeTest5::addAndRemove, this), 2.0f, "add_and_remove_key");
}

void NodeTest5::addAndRemove(float dt)
{
    auto sp1 = getChildByTag(kTagSprite1);
    auto sp2 = getChildByTag(kTagSprite2);

    sp1->retain();
    sp2->retain();
    
    removeChild(sp1, false);
    removeChild(sp2, true);
    
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
    
    sp1->release();
    sp2->release();
}

std::string NodeTest5::subtitle() const
{
    return "remove and cleanup";
}

//------------------------------------------------------------------
//
// NodeTest6
//
//------------------------------------------------------------------
NodeTest6::NodeTest6()
{
    auto sp1 = Sprite::create(s_pathSister1);
    auto sp11 = Sprite::create(s_pathSister1);

    auto sp2 = Sprite::create(s_pathSister2);
    auto sp21 = Sprite::create(s_pathSister2);
        
    sp1->setPosition(Vec2(100,160));
    sp2->setPosition(Vec2(380,160));
        
    auto rot = RotateBy::create(2, 360);
    auto rot_back = rot->reverse();
    auto forever1 = RepeatForever::create(Sequence::create(rot, rot_back, nullptr));
    auto forever11 = forever1->clone();

    auto forever2 = forever1->clone();
    auto forever21 = forever1->clone();
    
    addChild(sp1, 0, kTagSprite1);
    sp1->addChild(sp11);
    addChild(sp2, 0, kTagSprite2);
    sp2->addChild(sp21);
    
    sp1->runAction(forever1);
    sp11->runAction(forever11);
    sp2->runAction(forever2);
    sp21->runAction(forever21);
    
    schedule(CC_CALLBACK_1(NodeTest6::addAndRemove, this), 2.0f, "add_and_remove_key");
}

void NodeTest6::addAndRemove(float dt)
{
    auto sp1 = getChildByTag(kTagSprite1);
    auto sp2 = getChildByTag(kTagSprite2);

    sp1->retain();
    sp2->retain();
    
    removeChild(sp1, false);
    removeChild(sp2, true);
    
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
    
    sp1->release();
    sp2->release();

}

std::string NodeTest6::subtitle() const
{
    return "remove/cleanup with children";
}


//------------------------------------------------------------------
//
// StressTest1
//
//------------------------------------------------------------------
StressTest1::StressTest1()
{
    auto s = Director::getInstance()->getWinSize();

    auto sp1 = Sprite::create(s_pathSister1);
    addChild(sp1, 0, kTagSprite1);
    
    sp1->setPosition( Vec2(s.width/2, s.height/2) );        

    schedule(CC_CALLBACK_1(StressTest1::shouldNotCrash, this), 1.0f, "should_not_crash_key");
}

void StressTest1::shouldNotCrash(float dt)
{
    unschedule("should_not_crash_key");

    auto s = Director::getInstance()->getWinSize();

    // if the node has timers, it crashes
    auto explosion = ParticleSun::create();
    explosion->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
    
    // if it doesn't, it works Ok.
//    auto explosion = [Sprite create:@"grossinis_sister2.png");

    explosion->setPosition( Vec2(s.width/2, s.height/2) );
    
    runAction( Sequence::create(
                            RotateBy::create(2, 360),
                            CallFuncN::create(CC_CALLBACK_1(StressTest1::removeMe, this)),
                            nullptr) );
    
    addChild(explosion);
}

// remove
void StressTest1::removeMe(Node* node)
{
    getTestSuite()->enterNextTest();
}


std::string StressTest1::subtitle() const
{
    return "stress test #1: no crashes";
}

//------------------------------------------------------------------
//
// StressNodeTest2
//
//------------------------------------------------------------------
StressTest2::StressTest2()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto sublayer = Layer::create();
    
    auto sp1 = Sprite::create(s_pathSister1);
    sp1->setPosition( Vec2(80, s.height/2) );
    
    auto move = MoveBy::create(3, Vec2(350,0));
    auto move_ease_inout3 = EaseInOut::create(move->clone(), 2.0f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    auto seq3 = Sequence::create( move_ease_inout3, move_ease_inout_back3, nullptr);
    sp1->runAction( RepeatForever::create(seq3) );
    sublayer->addChild(sp1, 1);

    auto fire = ParticleFire::create();
    fire->setTexture(Director::getInstance()->getTextureCache()->addImage("Images/fire.png"));
    fire->setPosition( Vec2(80, s.height/2-50) );
    
    auto copy_seq3 = seq3->clone();

    fire->runAction( RepeatForever::create(copy_seq3) );
    sublayer->addChild(fire, 2);
            
    schedule(CC_CALLBACK_1(StressTest2::shouldNotLeak,this), 6.0f, "should_not_leak_key");
    
    addChild(sublayer, 0, kTagSprite1);
}

void StressTest2::shouldNotLeak(float dt)
{
    unschedule("should_not_leak_key");
    auto sublayer = static_cast<Layer*>( getChildByTag(kTagSprite1) );
    sublayer->removeAllChildrenWithCleanup(true); 
}

std::string StressTest2::subtitle() const
{
    return "stress test #2: no leaks";
}


//------------------------------------------------------------------
//
// SchedulerTest1
//
//------------------------------------------------------------------
SchedulerTest1::SchedulerTest1()
{
    auto layer = Layer::create();
    //CCLOG("retain count after init is %d", layer->getReferenceCount());                // 1
    
    addChild(layer, 0);
    //CCLOG("retain count after addChild is %d", layer->getReferenceCount());      // 2
    
    layer->schedule(CC_CALLBACK_1(SchedulerTest1::doSomething, this), "do_something_key");
    //CCLOG("retain count after schedule is %d", layer->getReferenceCount());      // 3 : (objective-c version), but win32 version is still 2, because Timer class don't save target.
    
    layer->unschedule("do_something_key");
    //CCLOG("retain count after unschedule is %d", layer->getReferenceCount());        // STILL 3!  (win32 is '2')
}

void SchedulerTest1::doSomething(float dt)
{

}

std::string SchedulerTest1::subtitle() const
{
    return "cocosnode scheduler test #1";
}

//------------------------------------------------------------------
//
// SchedulerCallbackTest
//
//------------------------------------------------------------------
SchedulerCallbackTest::SchedulerCallbackTest()
{
    auto node = Node::create();
    addChild(node, 0);
    node->setName("a node");

    _total = 0;
    node->schedule([&](float dt) {
        _total += dt;
        log("hello world: %f - total: %f", dt, _total);
    }
                   ,0.5
                   ,"some_key");


    node->scheduleOnce([&](float dt) {
        // the local variable "node" will go out of scope, so I have to get it from "this"
        auto anode = this->getChildByName("a node");
        anode->unschedule("some_key");
    }
                       ,5
                       ,"ignore_key");
}

void SchedulerCallbackTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    log("--onEnter-- Must be called before the scheduled lambdas");
}

std::string SchedulerCallbackTest::subtitle() const
{
    return "Node scheduler with lambda";
}

//------------------------------------------------------------------
//
// NodeToWorld
//
//------------------------------------------------------------------
NodeToWorld::NodeToWorld()
{
    //
    // This code tests that nodeToParent works OK:
    //  - It tests different anchor Points
    //  - It tests different children anchor points

    auto back = Sprite::create(s_back3);
    addChild( back, -10);
    back->setAnchorPoint( Vec2(0,0) );
    auto backSize = back->getContentSize();
    
    auto item = MenuItemImage::create(s_PlayNormal, s_PlaySelect);
    auto menu = Menu::create(item, nullptr);
    menu->alignItemsVertically();
    menu->setPosition( Vec2(backSize.width/2, backSize.height/2));
    back->addChild(menu);
    
    auto rot = RotateBy::create(5, 360);
    auto fe = RepeatForever::create( rot);
    item->runAction( fe );
    
    auto move = MoveBy::create(3, Vec2(200,0));
    auto move_back = move->reverse();
    auto seq = Sequence::create( move, move_back, nullptr);
    auto fe2 = RepeatForever::create(seq);
    back->runAction(fe2);
}

std::string NodeToWorld::subtitle() const
{
    return "nodeToParent transform";
}

//------------------------------------------------------------------
//
// NodeToWorld3D
//
//------------------------------------------------------------------
NodeToWorld3D::NodeToWorld3D()
{
    //
    // This code tests that nodeToParent works OK:
    //  - It tests different anchor Points
    //  - It tests different children anchor points

    Size s = Director::getInstance()->getWinSize();
    auto parent = Node::create();
    parent->setContentSize(s);
    parent->setAnchorPoint(Vec2(0.5, 0.5));
    parent->setPosition(s.width/2, s.height/2);
    this->addChild(parent);

    auto back = Sprite::create(s_back3);
    parent->addChild( back, -10);
    back->setAnchorPoint( Vec2(0,0) );
    auto backSize = back->getContentSize();

    auto item = MenuItemImage::create(s_PlayNormal, s_PlaySelect);
    auto menu = Menu::create(item, nullptr);
    menu->alignItemsVertically();
    menu->setPosition( Vec2(backSize.width/2, backSize.height/2));
    back->addChild(menu);

    auto rot = RotateBy::create(5, 360);
    auto fe = RepeatForever::create( rot);
    item->runAction( fe );

    auto move = MoveBy::create(3, Vec2(200,0));
    auto move_back = move->reverse();
    auto seq = Sequence::create( move, move_back, nullptr);
    auto fe2 = RepeatForever::create(seq);
    back->runAction(fe2);

    auto orbit = OrbitCamera::create(10, 0, 1, 0, 360, 0, 90);
    parent->runAction(orbit);
}

std::string NodeToWorld3D::subtitle() const
{
    return "nodeToParent transform in 3D";
}


//------------------------------------------------------------------
//
// CameraOrbitTest
//
//------------------------------------------------------------------
void CameraOrbitTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    _preProjection = Director::getInstance()->getProjection();
    Director::getInstance()->setDepthTest(true);
    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void CameraOrbitTest::onExit()
{
    Director::getInstance()->setDepthTest(false);
    Director::getInstance()->setProjection(_preProjection);
    TestCocosNodeDemo::onExit();
}

CameraOrbitTest::CameraOrbitTest()
{
    auto s = Director::getInstance()->getWinSize();

    auto p = Sprite::create(s_back3);
    addChild( p, 0);
    p->setPosition( Vec2(s.width/2, s.height/2) );
    p->setOpacity( 128 );
    
    Sprite* sprite;
    OrbitCamera* orbit;
    Size ss;

    // LEFT
    s = p->getContentSize();
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale(0.5f);
    p->addChild(sprite, 0);        
    sprite->setPosition( Vec2(s.width/4*1, s.height/2) );
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 0, 0);
    sprite->runAction( RepeatForever::create( orbit ) );
    
    // CENTER
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale( 1.0f );
    p->addChild(sprite, 0);        
    sprite->setPosition( Vec2(s.width/4*2, s.height/2) );
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 45, 0);
    sprite->runAction( RepeatForever::create( orbit ) );
    
    
    // RIGHT
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale( 2.0f );
    p->addChild(sprite, 0);        
    sprite->setPosition( Vec2(s.width/4*3, s.height/2) );
    ss = sprite->getContentSize();        
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 90, -45),
    sprite->runAction( RepeatForever::create(orbit) );
            
    
    // PARENT
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 90);
    p->runAction( RepeatForever::create( orbit ) );

    setScale( 1 );
}

std::string CameraOrbitTest::subtitle() const
{
    return "Camera Orbit test";
}

//------------------------------------------------------------------
//
// CameraZoomTest
//
//------------------------------------------------------------------

void CameraZoomTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    _preProjection = Director::getInstance()->getProjection();
    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void CameraZoomTest::onExit()
{
    Director::getInstance()->setProjection(_preProjection);
    TestCocosNodeDemo::onExit();
}

CameraZoomTest::CameraZoomTest()
{
    auto s = Director::getInstance()->getWinSize();
    
    Sprite *sprite;
//    Camera *cam;
    
    // LEFT
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0);        
    sprite->setPosition( Vec2(s.width/4*1, s.height/2) );
//    cam = sprite->getCamera();
//    cam->setEye(0, 0, 415/2);
//    cam->setCenter(0, 0, 0);

    // CENTER
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0, 40);
    sprite->setPosition(Vec2(s.width/4*2, s.height/2));
    
    // RIGHT
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0, 20);
    sprite->setPosition(Vec2(s.width/4*3, s.height/2));

    _z = 0;
    scheduleUpdate();
}

void CameraZoomTest::update(float dt)
{
    Node *sprite;
//    Camera *cam;

    _z += dt * 100;
    
    sprite = getChildByTag(20);
//    cam = sprite->getCamera();
//    cam->setEye(0, 0, _z);

    sprite = getChildByTag(40);
//    cam = sprite->getCamera();
//    cam->setEye(0, 0, -_z);    
}

std::string CameraZoomTest::subtitle() const
{
    return "Camera Zoom test";
}

//------------------------------------------------------------------
//
// CameraCenterTest
//
//------------------------------------------------------------------
void CameraCenterTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    _preProjection = Director::getInstance()->getProjection();
    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void CameraCenterTest::onExit()
{
    TestCocosNodeDemo::onExit();
    Director::getInstance()->setProjection(_preProjection);
}

CameraCenterTest::CameraCenterTest()
{
    auto s = Director::getInstance()->getWinSize();
            
    Sprite *sprite;
    OrbitCamera *orbit;
    
    // LEFT-TOP
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0);
    sprite->setPosition(Vec2(s.width/5*1, s.height/5*1));
    sprite->setColor(Color3B::RED);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ));
//        [sprite setAnchorPoint: Vec2(0,1));

    
    
    // LEFT-BOTTOM
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Vec2(s.width/5*1, s.height/5*4));
    sprite->setColor(Color3B::BLUE);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ));


    // RIGHT-TOP
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0);    
    sprite->setPosition(Vec2(s.width/5*4, s.height/5*1));
    sprite->setColor(Color3B::YELLOW);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit) );

    
    // RIGHT-BOTTOM
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Vec2(s.width/5*4, s.height/5*4));
    sprite->setColor(Color3B::GREEN);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction( RepeatForever::create( orbit ) );

    // CENTER
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Vec2(s.width/2, s.height/2));
    sprite->setColor(Color3B::WHITE);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ) );
}

std::string CameraCenterTest::title() const
{
    return "Camera Center test";
}

std::string CameraCenterTest::subtitle() const
{
    return "Sprites should rotate at the same speed";
}

//------------------------------------------------------------------
//
// ConvertToNode
//
//------------------------------------------------------------------
ConvertToNode::ConvertToNode()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(ConvertToNode::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto s = Director::getInstance()->getWinSize();

    auto rotate = RotateBy::create(10, 360);
    auto action = RepeatForever::create(rotate);
    for(int i = 0; i < 3; i++)
    {
        auto sprite = Sprite::create("Images/grossini.png");
        sprite->setPosition(Vec2( s.width/4*(i+1), s.height/2));

        auto point = Sprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 10, 100 + i);

        switch(i)
        {
        case 0:
            sprite->setAnchorPoint(Vec2::ZERO);
            break;
        case 1:
            sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(Vec2(1,1));
            break;
        }

        point->setPosition(sprite->getPosition());

        sprite->runAction( action->clone() );
        addChild(sprite, i);
    }
}

void ConvertToNode::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    for( auto& touch : touches)
    {
        auto location = touch->getLocation();

        for( int i = 0; i < 3; i++)
        {
            auto node = getChildByTag(100+i);
            Vec2 p1, p2;

            p1 = node->convertToNodeSpaceAR(location);
            p2 = node->convertToNodeSpace(location);

            CCLOG("AR: x=%.2f, y=%.2f -- Not AR: x=%.2f, y=%.2f", p1.x, p1.y, p2.x, p2.y);
        }
    }    
}

std::string ConvertToNode::title() const
{
    return "Convert To Node Space";
}

std::string ConvertToNode::subtitle() const
{
    return "testing convertToNodeSpace / AR. Touch and see console";
}

/// NodeOpaqueTest

NodeOpaqueTest::NodeOpaqueTest()
{
    Sprite *background = nullptr;

    for (int i = 0; i < 50; i++)
    {
        background = Sprite::create("Images/background1.png");
        background->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );
        background->setAnchorPoint(Vec2::ZERO);
        addChild(background);
    }
}

std::string NodeOpaqueTest::title() const
{
    return "Node Opaque Test";
}

std::string NodeOpaqueTest::subtitle() const
{
    return "Node rendered with GL_BLEND disabled";
}

/// NodeNonOpaqueTest

NodeNonOpaqueTest::NodeNonOpaqueTest()
{
    Sprite *background = nullptr;

    for (int i = 0; i < 50; i++)
    {
        background = Sprite::create("Images/background1.jpg");
        background->setBlendFunc(BlendFunc::DISABLE);
        background->setAnchorPoint(Vec2::ZERO);
        addChild(background);
    }
}

std::string NodeNonOpaqueTest::title() const
{
    return "Node Non Opaque Test";
}

std::string NodeNonOpaqueTest::subtitle() const
{
    return "Node rendered with GL_BLEND enabled";
}

/// NodeGlobalZValueTest

NodeGlobalZValueTest::NodeGlobalZValueTest()
{
    Size s = Director::getInstance()->getWinSize();
    for (int i = 0; i < 9; i++)
    {
        Sprite *sprite;
        auto parent = Node::create();
        if(i==4) {
            sprite = Sprite::create("Images/grossinis_sister2.png");
            _sprite = sprite;
            _sprite->setGlobalZOrder(-1);
        }
        else
            sprite = Sprite::create("Images/grossinis_sister1.png");

        parent->addChild(sprite);
        this->addChild(parent);

        float w = sprite->getContentSize().width;
        sprite->setPosition(s.width/2 - w*0.7*(i-5), s.height/2);
    }

    this->scheduleUpdate();
}

void NodeGlobalZValueTest::update(float dt)
{
    static float accum = 0;

    accum += dt;
    if( accum > 1) {
        float z = _sprite->getGlobalZOrder();
        _sprite->setGlobalZOrder(-z);
        accum = 0;
    }
}

std::string NodeGlobalZValueTest::title() const
{
    return "Global Z Value";
}

std::string NodeGlobalZValueTest::subtitle() const
{
    return "Center Sprite should change go from foreground to background";
}


//
// MySprite: Used by CameraTest1 and CameraTest2
//
class MySprite : public Sprite
{
public:
    static MySprite* create(const std::string &spritefilename)
    {
        auto sprite = new (std::nothrow) MySprite;
        sprite->initWithFile(spritefilename);
        sprite->autorelease();

        auto shaderState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
        sprite->setGLProgramState(shaderState);
        return sprite;
    }
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    void onDraw(const Mat4 &transform, uint32_t flags);

protected:
    CustomCommand _customCommand;

};

void MySprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder, transform, flags);
    _customCommand.func = CC_CALLBACK_0(MySprite::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void MySprite::onDraw(const Mat4 &transform, uint32_t flags)
{
    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::blendFunc( _blendFunc.src, _blendFunc.dst );

    GL::bindTexture2D( _texture->getName() );
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );

    #define kQuadSize sizeof(_quad.bl)
    size_t offset = (size_t)&_quad;

    // vertex
    int diff = offsetof( V3F_C4B_T2F, vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( V3F_C4B_T2F, texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( V3F_C4B_T2F, colors);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CHECK_GL_ERROR_DEBUG();
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
}
//------------------------------------------------------------------
//
// CameraTest1
//
//------------------------------------------------------------------

void CameraTest1::onEnter()
{
    TestCocosNodeDemo::onEnter();
    _preProjection = Director::getInstance()->getProjection();
    Director::getInstance()->setProjection(Director::Projection::_3D);
    Director::getInstance()->setDepthTest(true);
}

void CameraTest1::onExit()
{
    Director::getInstance()->setProjection(_preProjection);
    Director::getInstance()->setDepthTest(false);
    TestCocosNodeDemo::onExit();
}

CameraTest1::CameraTest1()
{
    auto s = Director::getInstance()->getWinSize();

    _sprite1 = MySprite::create(s_back3);
    addChild( _sprite1 );
    _sprite1->setPosition( Vec2(1*s.width/4, s.height/2) );
    _sprite1->setScale(0.5);

    _sprite2 = Sprite::create(s_back3);
    addChild( _sprite2 );
    _sprite2->setPosition( Vec2(3*s.width/4, s.height/2) );
    _sprite2->setScale(0.5);

    auto camera = OrbitCamera::create(10, 0, 1, 0, 360, 0, 0);
    _sprite1->runAction( camera );
    _sprite2->runAction( camera->clone() );
}

std::string CameraTest1::title() const
{
    return "Camera Test 1";
}

std::string CameraTest1::subtitle() const
{
    return "Both images should rotate with a 3D effect";
}

//------------------------------------------------------------------
//
// CameraTest2
//
//------------------------------------------------------------------
void CameraTest2::onEnter()
{
    TestCocosNodeDemo::onEnter();
    _preProjection = Director::getInstance()->getProjection();
    Director::getInstance()->setProjection(Director::Projection::_3D);
    Director::getInstance()->setDepthTest(true);
}

void CameraTest2::onExit()
{
    Director::getInstance()->setProjection(_preProjection);
    Director::getInstance()->setDepthTest(false);
    TestCocosNodeDemo::onExit();
}

CameraTest2::CameraTest2()
{
    auto s = Director::getInstance()->getWinSize();

    _sprite1 = MySprite::create(s_back3);
    addChild( _sprite1 );
    _sprite1->setPosition( Vec2(1*s.width/4, s.height/2) );
    _sprite1->setScale(0.5);

    _sprite2 = Sprite::create(s_back3);
    addChild( _sprite2 );
    _sprite2->setPosition( Vec2(3*s.width/4, s.height/2) );
    _sprite2->setScale(0.5);

    Vec3 eye(150, 0, 200), center(0, 0, 0), up(0, 1, 0);

    Mat4 lookupMatrix;
    Mat4::createLookAt(eye, center, up, &lookupMatrix);

    Mat4 lookupMatrix2 = lookupMatrix;

    _sprite1->setAdditionalTransform(&lookupMatrix2);
    _sprite2->setAdditionalTransform(&lookupMatrix2);

}

std::string CameraTest2::title() const
{
    return "Camera Test 2";
}

std::string CameraTest2::subtitle() const
{
    return "Both images should look the same";
}

//------------------------------------------------------------------
//
// NodeNormalizedPositionTest1
//
//------------------------------------------------------------------
NodeNormalizedPositionTest1::NodeNormalizedPositionTest1()
{
    Sprite *sprites[5];
    Vec2 positions[5];
    positions[0] = Vec2(0,0);
    positions[1] = Vec2(0,1);
    positions[2] = Vec2(0.5,0.5);
    positions[3] = Vec2(1,0);
    positions[4] = Vec2(1,1);

    for(int i=0; i<5; i++) {
        sprites[i] = Sprite::create("Images/grossini.png");
        sprites[i]->setPositionNormalized(positions[i]);
        addChild(sprites[i]);
    }
}

std::string NodeNormalizedPositionTest1::title() const
{
    return "setNormalizedPositon()";
}

std::string NodeNormalizedPositionTest1::subtitle() const
{
    return "5 sprites: One in the center, the others on the corners";
}

//------------------------------------------------------------------
//
// NodeNormalizedPositionTest2
//
//------------------------------------------------------------------
NodeNormalizedPositionTest2::NodeNormalizedPositionTest2()
: _accum(0)
{
    Sprite *sprites[5];
    Vec2 positions[5];
    positions[0] = Vec2(0,0);
    positions[1] = Vec2(0,1);
    positions[2] = Vec2(0.5,0.5);
    positions[3] = Vec2(1,0);
    positions[4] = Vec2(1,1);

    for(int i=0; i<5; i++) {
        sprites[i] = Sprite::create("Images/grossini.png");
        sprites[i]->setPositionNormalized(positions[i]);
        addChild(sprites[i]);
    }
    scheduleUpdate();

    setContentSize( Director::getInstance()->getWinSize());
    _copyContentSize = getContentSize();

//    setAnchorPoint(Vec2(0.5,0.5));
//    setPositionNormalized(Vec2(0.5,0.5));
}

std::string NodeNormalizedPositionTest2::title() const
{
    return "setNormalizedPositon() #2";
}

std::string NodeNormalizedPositionTest2::subtitle() const
{
    return "5 sprites: One in the center, the others on the corners of its parents";
}

void NodeNormalizedPositionTest2::update(float dt)
{
    _accum += dt;

    // for 5 seconds
    float norm = sinf(_accum);

    Size s = Size(_copyContentSize.width*norm, _copyContentSize.height*norm);
    setContentSize(s);
    CCLOG("s: %f,%f", s.width, s.height);
}


//------------------------------------------------------------------
//
// NodeNormalizedPositionBugTest
//
//------------------------------------------------------------------
NodeNormalizedPositionBugTest::NodeNormalizedPositionBugTest()
: _accum(0)
{
    Vec2 position;
   
    position = Vec2(0.5,0.5);

    
    sprite = Sprite::create("Images/grossini.png");
    sprite->setPositionNormalized(position);
    addChild(sprite);
    
    scheduleUpdate();
}

std::string NodeNormalizedPositionBugTest::title() const
{
    return "NodeNormalizedPositionBugTest";
}

std::string NodeNormalizedPositionBugTest::subtitle() const
{
    return "When changing sprite normalizedPosition, the sprite doesn't move!";
}

void NodeNormalizedPositionBugTest::update(float dt)
{
    _accum += dt;
    
    // for 5 seconds
    float norm = clampf(sinf(_accum), 0, 1.0);
    sprite->setPositionNormalized(Vec2(norm,norm));
}

std::string NodeNameTest::title() const
{
    return "getName()/setName()/getChildByName()/enumerateChildren()";
}

std::string NodeNameTest::subtitle() const
{
    return "see console";
}

void NodeNameTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    
    this->scheduleOnce(CC_CALLBACK_1(NodeNameTest::test, this), 0.05f, "test_key");
}

void NodeNameTest::onExit()
{
    TestCocosNodeDemo::onExit();
}

void NodeNameTest::test(float dt)
{
    auto parent = Node::create();
    
    // setName(), getName() and getChildByName()
    char name[20];
    for (int i = 0; i < 10; ++i)
    {
        sprintf(name, "node%d", i);
        auto node = Node::create();
        node->setName(name);
        parent->addChild(node);
    }
    
    for (int i = 0; i < 10; ++i)
    {
        sprintf(name, "node%d", i);
        auto node = parent->getChildByName(name);
        log("find child: %s", node->getName().c_str());
    }
    
    // enumerateChildren()
    // name = regular expression
    int i = 0;
    parent = Node::create();
    for (int i = 0; i < 100; ++i)
    {
        auto node = Node::create();
        sprintf(name, "node%d", i);
        node->setName(name);
        parent->addChild(node);
    }
    
    i = 0;
    parent->enumerateChildren("node[[:digit:]]+", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 100, "");
    
    i = 0;
    parent->enumerateChildren("node[[:digit:]]+", [&i](Node* node) -> bool {
        ++i;
        return true;
    });
    CCAssert(i == 1, "");
    
    // enumerateChildren
    // name = node[[digit]]+/node
    
    parent = Node::create();
    for (int i = 0; i < 10; ++i)
    {
        auto node = Node::create();
        sprintf(name, "node%d", i);
        node->setName(name);
        parent->addChild(node);
        
        for (int j = 0; j < 10; ++j)
        {
            auto child = Node::create();
            child->setName("node");
            node->addChild(child);
        }
    }
    
    i = 0;
    parent->enumerateChildren("node1/node", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 10, "");
    
    i = 0;
    parent->enumerateChildren("node1/node", [&i](Node* node) -> bool {
        ++i;
        return true;
    });
    CCAssert(i == 1, "");
    
    // search from root
    parent = Node::create();
    for (int i = 0; i < 10; ++i)
    {
        auto node = Node::create();
        sprintf(name, "node%d", i);
        node->setName(name);
        parent->addChild(node);
        
        for (int j = 0; j < 10; ++j)
        {
            auto child = Node::create();
            child->setName("node");
            node->addChild(child);
        }
    }
    
    i = 0;
    parent->enumerateChildren("node[[:digit:]]+/node", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 100, "");
    
    i = 0;
    parent->enumerateChildren("node[[:digit:]]+/node", [&i](Node* node) -> bool {
        ++i;
        return true;
    });
    CCAssert(i == 1, "");
    
    // search from parent
    // name is xxx/..
    i = 0;
    parent->enumerateChildren("node/..", [&i](Node* node) -> bool {
        ++i;
        return true;
    });
    CCAssert(i == 1, "");
    
    i = 0;
    parent->enumerateChildren("node/..", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 100, "");
    
    // name = //xxx : search recursively
    parent = Node::create();
    for (int j = 0; j < 10; j++)
    {
        auto node = Node::create();
        sprintf(name, "node%d", j);
        node->setName(name);
        parent->addChild(node);
        
        for (int k = 0; k < 10; ++k)
        {
            auto child = Node::create();
            sprintf(name, "node%d", k);
            child->setName(name);
            node->addChild(child);
        }
    }
    
    i = 0;
    parent->enumerateChildren("//node[[:digit:]]+", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 110, ""); // 100(children) + 10(parent)
    
    i = 0;
    parent->enumerateChildren("//node[[:digit:]]+", [&i](Node* node) -> bool {
        ++i;
        return true;
    });
    CCAssert(i == 1, "");
    
    i = 0;
    parent->enumerateChildren("//node[[:digit:]]+/..", [&i](Node* node) -> bool {
        ++i;
        return false;
    });
    CCAssert(i == 100, "");
    
    // utils::findChildren()
    
    parent = Node::create();
    for (int i = 0; i < 50; ++i)
    {
        auto child = Node::create();
        child->setName("node");
        parent->addChild(child);
    }
    auto findChildren = utils::findChildren(*parent, "node");
    CCAssert(findChildren.size() == 50, "");
}

//------------------------------------------------------------------
//
// Issue16100Test
//
//------------------------------------------------------------------
void Issue16100Test::onEnter()
{
    TestCocosNodeDemo::onEnter();

    // create user camera
    auto s = Director::getInstance()->getWinSize();

    auto delay = DelayTime::create(0.1f);
    auto f = CallFunc::create([this, s]()
    {
        auto camera = Camera::createOrthographic(s.width * 2, s.height * 2, -1024, 1024);
        camera->setCameraFlag(CameraFlag::USER1);
        addChild(camera);
    });
    this->runAction(Sequence::createWithTwoActions(delay, f));

    // grossini using default camera
    auto sprite = Sprite::create("Images/grossini.png");
    this->addChild(sprite);

    sprite->setPosition(-200,s.height/3);
    auto moveby = MoveBy::create(2, Vec2(400,0));
    auto movebyback = moveby->reverse();
    auto seq = Sequence::create(moveby, movebyback, nullptr);
    auto forever = RepeatForever::create(seq);

    sprite->runAction(forever);

    sprite->setCameraMask((int)CameraFlag::DEFAULT);


    // grossini's sister using user camera
    auto sister = Sprite::create("Images/grossinis_sister1.png");
    this->addChild(sister);

    sister->setPosition(-200,s.height*2/3);
    auto moveby1 = MoveBy::create(2, Vec2(400,0));
    auto movebyback1 = moveby1->reverse();
    auto seq1 = Sequence::create(moveby1, movebyback1, nullptr);
    auto forever1 = RepeatForever::create(seq1);

    sister->runAction(forever1);
    sister->setCameraMask((int)CameraFlag::USER1);
}

void Issue16100Test::onExit()
{
    TestCocosNodeDemo::onExit();
}

std::string Issue16100Test::title() const
{
    return "Issue 16100";
}

std::string Issue16100Test::subtitle() const
{
    return "Sprite should appear on the screen";
}

//------------------------------------------------------------------
//
// Issue16735Test
//
//------------------------------------------------------------------
void Issue16735Test::onEnter()
{
    TestCocosNodeDemo::onEnter();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto sprite1 = Sprite::create("Images/grossini.png");
    sprite1->setPosition(Vec2(visibleSize / 2) + origin);
    addChild(sprite1);

    auto sprite2 = Sprite::create("Images/grossini.png");
    sprite2->setPosition(Vec2(visibleSize / 2) + origin);
    sprite2->setSkewX(30);
    sprite2->setScale(2);
    sprite2->setRotation(30);
    addChild(sprite2);

    auto d = DrawNode::create();
    d->drawLine(Vec2(origin.x, origin.y + visibleSize.height/2), Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height/2), Color4F::RED);
    d->drawLine(Vec2(origin.x + visibleSize.width/2, origin.y), Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height), Color4F::RED);
    
    addChild(d);
}

void Issue16735Test::onExit()
{
    TestCocosNodeDemo::onExit();
}

std::string Issue16735Test::title() const
{
    return "Issue 16735";
}

std::string Issue16735Test::subtitle() const
{
    return "Sprite should appear on the center of screen";
}
