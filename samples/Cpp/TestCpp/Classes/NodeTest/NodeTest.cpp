#include "NodeTest.h"
#include "../testResource.h"

enum 
{
    kTagSprite1 = 1,
    kTagSprite2 = 2,
    kTagSprite3 = 3,
    kTagSlider,
};


Layer* nextCocosNodeAction();
Layer* backCocosNodeAction();
Layer* restartCocosNodeAction();

//------------------------------------------------------------------
//
// TestCocosNodeDemo
//
//------------------------------------------------------------------

static int sceneIdx = -1; 

#define MAX_LAYER    14

Layer* createCocosNodeLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new CameraCenterTest();
        case 1: return new Test2();
        case 2: return new Test4();
        case 3: return new Test5();
        case 4: return new Test6();
        case 5: return new StressTest1();
        case 6: return new StressTest2();
        case 7: return new NodeToWorld();
        case 8: return new SchedulerTest1();
        case 9: return new CameraOrbitTest();
        case 10: return new CameraZoomTest();
        case 11: return new ConvertToNode();
        case 12: return new NodeOpaqueTest();
        case 13: return new NodeNonOpaqueTest();
    }

    return NULL;
}

Layer* nextCocosNodeAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* layer = createCocosNodeLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backCocosNodeAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* layer = createCocosNodeLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartCocosNodeAction()
{
    Layer* layer = createCocosNodeLayer(sceneIdx);
    layer->autorelease();

    return layer;
} 


TestCocosNodeDemo::TestCocosNodeDemo(void)
{
}

TestCocosNodeDemo::~TestCocosNodeDemo(void)
{
}

std::string TestCocosNodeDemo::title()
{
    return "No title";
}

std::string TestCocosNodeDemo::subtitle()
{
    return "";
}

void TestCocosNodeDemo::onEnter()
{
    BaseTest::onEnter();
}

void TestCocosNodeDemo::restartCallback(Object* sender)
{
    Scene* s = new CocosNodeTestScene();//CCScene::create();
    s->addChild(restartCocosNodeAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void TestCocosNodeDemo::nextCallback(Object* sender)
{
    Scene* s = new CocosNodeTestScene();//CCScene::create();
    s->addChild( nextCocosNodeAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void TestCocosNodeDemo::backCallback(Object* sender)
{
    Scene* s = new CocosNodeTestScene();//CCScene::create();
    s->addChild( backCocosNodeAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Test2
//
//------------------------------------------------------------------
void Test2::onEnter()
{
    TestCocosNodeDemo::onEnter();

    Size s = Director::getInstance()->getWinSize();
    
    Sprite *sp1 = Sprite::create(s_pathSister1);
    Sprite *sp2 = Sprite::create(s_pathSister2);
    Sprite *sp3 = Sprite::create(s_pathSister1);
    Sprite *sp4 = Sprite::create(s_pathSister2);
    
    sp1->setPosition(Point(100, s.height /2 ));
    sp2->setPosition(Point(380, s.height /2 ));
    addChild(sp1);
    addChild(sp2);
    
    sp3->setScale(0.25f);
    sp4->setScale(0.25f);
    
    sp1->addChild(sp3);
    sp2->addChild(sp4);
    
    ActionInterval* a1 = RotateBy::create(2, 360);
    ActionInterval* a2 = ScaleBy::create(2, 2);
    
    Action* action1 = RepeatForever::create( Sequence::create(a1, a2, a2->reverse(), NULL) );
    Action* action2 = RepeatForever::create( Sequence::create(
																	a1->clone(),
																	a2->clone(),
																	a2->reverse(),
																	NULL)
												);
    
    sp2->setAnchorPoint(Point(0,0));
    
    sp1->runAction(action1);
    sp2->runAction(action2);
}

std::string Test2::title()
{
    return "anchorPoint and children";
}


//------------------------------------------------------------------
//
// Test4
//
//------------------------------------------------------------------
#define SID_DELAY2        1
#define SID_DELAY4        2

Test4::Test4()
{
    Sprite *sp1 = Sprite::create(s_pathSister1);
    Sprite *sp2 = Sprite::create(s_pathSister2);
    
    sp1->setPosition( Point(100,160) );
    sp2->setPosition( Point(380,160) );
    
    addChild(sp1, 0, 2);
    addChild(sp2, 0, 3);
    
    schedule( schedule_selector(Test4::delay2), 2.0f); 
    schedule( schedule_selector(Test4::delay4), 4.0f); 
}

void Test4::delay2(float dt)
{
    Sprite* node = static_cast<Sprite*>(getChildByTag(2));
    Action* action1 = RotateBy::create(1, 360);
    node->runAction(action1);
}

void Test4::delay4(float dt)
{
    unschedule(schedule_selector(Test4::delay4)); 
    removeChildByTag(3, false);
}

std::string Test4::title()
{
    return "tags";
}


//------------------------------------------------------------------
//
// Test5
//
//------------------------------------------------------------------
Test5::Test5()
{
    Sprite* sp1 = Sprite::create(s_pathSister1);
    Sprite* sp2 = Sprite::create(s_pathSister2);
    
    sp1->setPosition(Point(100,160));
    sp2->setPosition(Point(380,160));

    RotateBy* rot = RotateBy::create(2, 360);
    ActionInterval* rot_back = rot->reverse();
    Action* forever = RepeatForever::create(Sequence::create(rot, rot_back, NULL));
    Action* forever2 = forever->clone();
    forever->setTag(101);
    forever2->setTag(102);
                                                  
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
            
    sp1->runAction(forever);
    sp2->runAction(forever2);
    
    schedule( schedule_selector(Test5::addAndRemove), 2.0f);
}

void Test5::addAndRemove(float dt)
{
    Node* sp1 = getChildByTag(kTagSprite1);
    Node* sp2 = getChildByTag(kTagSprite2);

    sp1->retain();
    sp2->retain();
    
    removeChild(sp1, false);
    removeChild(sp2, true);
    
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
    
    sp1->release();
    sp2->release();
}

std::string Test5::title()
{
    return "remove and cleanup";
}

//------------------------------------------------------------------
//
// Test6
//
//------------------------------------------------------------------
Test6::Test6()
{
    Sprite* sp1 = Sprite::create(s_pathSister1);
    Sprite* sp11 = Sprite::create(s_pathSister1);

    Sprite* sp2 = Sprite::create(s_pathSister2);
    Sprite* sp21 = Sprite::create(s_pathSister2);
        
    sp1->setPosition(Point(100,160));
    sp2->setPosition(Point(380,160));
        
    ActionInterval* rot = RotateBy::create(2, 360);
    ActionInterval* rot_back = rot->reverse();
    Action* forever1 = RepeatForever::create(Sequence::create(rot, rot_back, NULL));
    Action* forever11 = forever1->clone();

    Action* forever2 = forever1->clone();
    Action* forever21 = forever1->clone();
    
    addChild(sp1, 0, kTagSprite1);
    sp1->addChild(sp11);
    addChild(sp2, 0, kTagSprite2);
    sp2->addChild(sp21);
    
    sp1->runAction(forever1);
    sp11->runAction(forever11);
    sp2->runAction(forever2);
    sp21->runAction(forever21);
    
    schedule( schedule_selector(Test6::addAndRemove), 2.0f);
}

void Test6::addAndRemove(float dt)
{
    Node* sp1 = getChildByTag(kTagSprite1);
    Node* sp2 = getChildByTag(kTagSprite2);

    sp1->retain();
    sp2->retain();
    
    removeChild(sp1, false);
    removeChild(sp2, true);
    
    addChild(sp1, 0, kTagSprite1);
    addChild(sp2, 0, kTagSprite2);
    
    sp1->release();
    sp2->release();

}

std::string Test6::title()
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
    Size s = Director::getInstance()->getWinSize();

    Sprite *sp1 = Sprite::create(s_pathSister1);
    addChild(sp1, 0, kTagSprite1);
    
    sp1->setPosition( Point(s.width/2, s.height/2) );        

    schedule( schedule_selector(StressTest1::shouldNotCrash), 1.0f);
}

void StressTest1::shouldNotCrash(float dt)
{
    unschedule(schedule_selector(StressTest1::shouldNotCrash));

    Size s = Director::getInstance()->getWinSize();

    // if the node has timers, it crashes
    ParticleSun* explosion = ParticleSun::create();
    explosion->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
    
    // if it doesn't, it works Ok.
//    CocosNode *explosion = [Sprite create:@"grossinis_sister2.png");

    explosion->setPosition( Point(s.width/2, s.height/2) );
    
    runAction( Sequence::create(
                            RotateBy::create(2, 360),
                            CallFuncN::create(CC_CALLBACK_1(StressTest1::removeMe, this)),
                            NULL) );
    
    addChild(explosion);
}

// remove
void StressTest1::removeMe(Node* node)
{    
    getParent()->removeChild(node, true);
    nextCallback(this);
}


std::string StressTest1::title()
{
    return "stress test #1: no crashes";
}

//------------------------------------------------------------------
//
// StressTest2
//
//------------------------------------------------------------------
StressTest2::StressTest2()
{
    Size s = Director::getInstance()->getWinSize();
    
    Layer* sublayer = Layer::create();
    
    Sprite *sp1 = Sprite::create(s_pathSister1);
    sp1->setPosition( Point(80, s.height/2) );
    
    ActionInterval* move = MoveBy::create(3, Point(350,0));
    ActionInterval* move_ease_inout3 = EaseInOut::create(move->clone(), 2.0f);
    ActionInterval* move_ease_inout_back3 = move_ease_inout3->reverse();
    Sequence* seq3 = Sequence::create( move_ease_inout3, move_ease_inout_back3, NULL);
    sp1->runAction( RepeatForever::create(seq3) );
    sublayer->addChild(sp1, 1);

    ParticleFire* fire = ParticleFire::create();
    fire->setTexture(TextureCache::getInstance()->addImage("Images/fire.png"));
    fire->setPosition( Point(80, s.height/2-50) );
    
    ActionInterval* copy_seq3 = seq3->clone();
    
    fire->runAction( RepeatForever::create(copy_seq3) );
    sublayer->addChild(fire, 2);
            
    schedule(schedule_selector(StressTest2::shouldNotLeak), 6.0f);
    
    addChild(sublayer, 0, kTagSprite1);
}

void StressTest2::shouldNotLeak(float dt)
{
    unschedule( schedule_selector(StressTest2::shouldNotLeak) );
    Layer* sublayer = static_cast<Layer*>( getChildByTag(kTagSprite1) );
    sublayer->removeAllChildrenWithCleanup(true); 
}

std::string StressTest2::title()
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
    Layer*layer = Layer::create();
    //CCLOG("retain count after init is %d", layer->retainCount());                // 1
    
    addChild(layer, 0);
    //CCLOG("retain count after addChild is %d", layer->retainCount());      // 2
    
    layer->schedule( schedule_selector(SchedulerTest1::doSomething) );
    //CCLOG("retain count after schedule is %d", layer->retainCount());      // 3 : (object-c viersion), but win32 version is still 2, because Timer class don't save target.
    
    layer->unschedule(schedule_selector(SchedulerTest1::doSomething));
    //CCLOG("retain count after unschedule is %d", layer->retainCount());        // STILL 3!  (win32 is '2')
}

void SchedulerTest1::doSomething(float dt)
{

}

std::string SchedulerTest1::title()
{
    return "cocosnode scheduler test #1";
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

    Sprite *back = Sprite::create(s_back3);
    addChild( back, -10);
    back->setAnchorPoint( Point(0,0) );
    Size backSize = back->getContentSize();
    
    MenuItem *item = MenuItemImage::create(s_PlayNormal, s_PlaySelect);
    Menu *menu = Menu::create(item, NULL);
    menu->alignItemsVertically();
    menu->setPosition( Point(backSize.width/2, backSize.height/2));
    back->addChild(menu);
    
    ActionInterval* rot = RotateBy::create(5, 360);
    Action* fe = RepeatForever::create( rot);
    item->runAction( fe );
    
    ActionInterval* move = MoveBy::create(3, Point(200,0));
    ActionInterval* move_back = move->reverse();
    Sequence* seq = Sequence::create( move, move_back, NULL);
    Action* fe2 = RepeatForever::create(seq);
    back->runAction(fe2);
}

std::string NodeToWorld::title()
{
    return "nodeToParent transform";
}

//------------------------------------------------------------------
//
// CameraOrbitTest
//
//------------------------------------------------------------------
void CameraOrbitTest::onEnter()
{
    TestCocosNodeDemo::onEnter();
    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void CameraOrbitTest::onExit()
{
    Director::getInstance()->setProjection(Director::Projection::_2D);
    TestCocosNodeDemo::onExit();
}

CameraOrbitTest::CameraOrbitTest()
{
    Size s = Director::getInstance()->getWinSize();

    Sprite *p = Sprite::create(s_back3);
    addChild( p, 0);
    p->setPosition( Point(s.width/2, s.height/2) );
    p->setOpacity( 128 );
    
    Sprite* sprite;
    OrbitCamera* orbit;
    Size ss;

    // LEFT
    s = p->getContentSize();
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale(0.5f);
    p->addChild(sprite, 0);        
    sprite->setPosition( Point(s.width/4*1, s.height/2) );
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 0, 0);
    sprite->runAction( RepeatForever::create( orbit ) );
    
    // CENTER
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale( 1.0f );
    p->addChild(sprite, 0);        
    sprite->setPosition( Point(s.width/4*2, s.height/2) );
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 45, 0);
    sprite->runAction( RepeatForever::create( orbit ) );
    
    
    // RIGHT
    sprite = Sprite::create(s_pathGrossini);
    sprite->setScale( 2.0f );
    p->addChild(sprite, 0);        
    sprite->setPosition( Point(s.width/4*3, s.height/2) );
    ss = sprite->getContentSize();        
    orbit = OrbitCamera::create(2, 1, 0, 0, 360, 90, -45),
    sprite->runAction( RepeatForever::create(orbit) );
            
    
    // PARENT
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 90);
    p->runAction( RepeatForever::create( orbit ) );

    setScale( 1 );
}

std::string CameraOrbitTest::title()
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
    
    Director::getInstance()->setProjection(Director::Projection::_3D);
}

void CameraZoomTest::onExit()
{
    Director::getInstance()->setProjection(Director::Projection::_2D);
    TestCocosNodeDemo::onExit();
}

CameraZoomTest::CameraZoomTest()
{
    Size s = Director::getInstance()->getWinSize();
    
    Sprite *sprite;
    Camera *cam;
    
    // LEFT
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0);        
    sprite->setPosition( Point(s.width/4*1, s.height/2) );
    cam = sprite->getCamera();
    cam->setEyeXYZ(0, 0, 415/2);
    cam->setCenterXYZ(0, 0, 0);
    
    // CENTER
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0, 40);
    sprite->setPosition(Point(s.width/4*2, s.height/2));
    
    // RIGHT
    sprite = Sprite::create(s_pathGrossini);
    addChild( sprite, 0, 20);
    sprite->setPosition(Point(s.width/4*3, s.height/2));

    _z = 0;
    scheduleUpdate();
}

void CameraZoomTest::update(float dt)
{
    Node *sprite;
    Camera *cam;
    
    _z += dt * 100;
    
    sprite = getChildByTag(20);
    cam = sprite->getCamera();
    cam->setEyeXYZ(0, 0, _z);
    
    sprite = getChildByTag(40);
    cam = sprite->getCamera();
    cam->setEyeXYZ(0, 0, -_z);    
}

std::string CameraZoomTest::title()
{
    return "Camera Zoom test";
}

//------------------------------------------------------------------
//
// CameraCenterTest
//
//------------------------------------------------------------------
CameraCenterTest::CameraCenterTest()
{
    Size s = Director::getInstance()->getWinSize();
            
    Sprite *sprite;
    OrbitCamera *orbit;
    
    // LEFT-TOP
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0);
    sprite->setPosition(Point(s.width/5*1, s.height/5*1));
    sprite->setColor(Color3B::RED);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ));
//        [sprite setAnchorPoint: Point(0,1));

    
    
    // LEFT-BOTTOM
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Point(s.width/5*1, s.height/5*4));
    sprite->setColor(Color3B::BLUE);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ));


    // RIGHT-TOP
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0);    
    sprite->setPosition(Point(s.width/5*4, s.height/5*1));
    sprite->setColor(Color3B::YELLOW);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit) );

    
    // RIGHT-BOTTOM
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Point(s.width/5*4, s.height/5*4));
    sprite->setColor(Color3B::GREEN);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction( RepeatForever::create( orbit ) );

    // CENTER
    sprite = Sprite::create("Images/white-512x512.png");
    addChild( sprite, 0, 40);
    sprite->setPosition(Point(s.width/2, s.height/2));
    sprite->setColor(Color3B::WHITE);
    sprite->setTextureRect(Rect(0, 0, 120, 50));
    orbit = OrbitCamera::create(10, 1, 0, 0, 360, 0, 0);
    sprite->runAction(RepeatForever::create( orbit ) );
}

std::string CameraCenterTest::title()
{
    return "Camera Center test";
}

std::string CameraCenterTest::subtitle()
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
    setTouchEnabled(true);
    Size s = Director::getInstance()->getWinSize();

    RotateBy* rotate = RotateBy::create(10, 360);
    RepeatForever* action = RepeatForever::create(rotate);
    for(int i = 0; i < 3; i++)
    {
        Sprite *sprite = Sprite::create("Images/grossini.png");
        sprite->setPosition(Point( s.width/4*(i+1), s.height/2));

        Sprite *point = Sprite::create("Images/r1.png");
        point->setScale(0.25f);
        point->setPosition(sprite->getPosition());
        addChild(point, 10, 100 + i);

        switch(i)
        {
        case 0:
            sprite->setAnchorPoint(Point::ZERO);
            break;
        case 1:
            sprite->setAnchorPoint(Point(0.5f, 0.5f));
            break;
        case 2:
            sprite->setAnchorPoint(Point(1,1));
            break;
        }

        point->setPosition(sprite->getPosition());

        sprite->runAction( action->clone() );
        addChild(sprite, i);
    }
}

void ConvertToNode::ccTouchesEnded(Set* touches, Event *event)
{
    for( SetIterator it = touches->begin(); it != touches->end(); ++it)
    {
        Touch* touch = static_cast<Touch*>(*it);
        Point location = touch->getLocation();

        for( int i = 0; i < 3; i++)
        {
            Node *node = getChildByTag(100+i);
            Point p1, p2;

            p1 = node->convertToNodeSpaceAR(location);
            p2 = node->convertToNodeSpace(location);

            CCLOG("AR: x=%.2f, y=%.2f -- Not AR: x=%.2f, y=%.2f", p1.x, p1.y, p2.x, p2.y);
        }
    }    
}

std::string ConvertToNode::title()
{
    return "Convert To Node Space";
}

std::string ConvertToNode::subtitle()
{
    return "testing convertToNodeSpace / AR. Touch and see console";
}

/// NodeOpaqueTest

NodeOpaqueTest::NodeOpaqueTest()
{
    Sprite *background = NULL;

    for (int i = 0; i < 50; i++)
    {
        background = Sprite::create("Images/background1.png");
        background->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );
        background->setAnchorPoint(Point::ZERO);
        addChild(background);
    }
}

std::string NodeOpaqueTest::title()
{
    return "Node Opaque Test";
}

std::string NodeOpaqueTest::subtitle()
{
    return "Node rendered with GL_BLEND disabled";
}

/// NodeNonOpaqueTest

NodeNonOpaqueTest::NodeNonOpaqueTest()
{
    Sprite *background = NULL;

    for (int i = 0; i < 50; i++)
    {
        background = Sprite::create("Images/background1.jpg");
        background->setBlendFunc(BlendFunc::DISABLE);
        background->setAnchorPoint(Point::ZERO);
        addChild(background);
    }
}

std::string NodeNonOpaqueTest::title()
{
    return "Node Non Opaque Test";
}

std::string NodeNonOpaqueTest::subtitle()
{
    return "Node rendered with GL_BLEND enabled";
}

void CocosNodeTestScene::runThisTest()
{
    Layer* layer = nextCocosNodeAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
