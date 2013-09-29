#include "PhysicsTest.h"
#include "../testResource.h"
USING_NS_CC;



static std::function<Layer*()> createFunctions[] = {
    
    CL(PhysicsDemoClickAdd),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

namespace
{
    static Layer* next()
    {
        sceneIdx++;
        sceneIdx = sceneIdx % MAX_LAYER;
        
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
    
    static Layer* back()
    {
        sceneIdx--;
        int total = MAX_LAYER;
        if( sceneIdx < 0 )
            sceneIdx += total;
        
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
    
    static Layer* restart()
    {
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
}

bool PhysicsTestScene::initTest()
{
#ifdef CC_USE_PHYSICS
    if (TestScene::initWithPhysics())
    {
        this->getPhysicsWorld()->setDebugDraw(true);
        return true;
    }
#else
    return TestScene::init();
#endif
    
    return false;
}

void PhysicsTestScene::runThisTest()
{
#ifdef CC_USE_PHYSICS
    sceneIdx = -1;
    addChild(next());
    
    Director::getInstance()->replaceScene(this);
#else
#endif
}

PhysicsDemo::PhysicsDemo()
: _scene(nullptr)
{
    
}

PhysicsDemo::~PhysicsDemo()
{
    
}

std::string PhysicsDemo::title()
{
    return "PhysicsTest";
}

std::string PhysicsDemo::subtitle()
{
    return "";
}

void PhysicsDemo::restartCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( restart() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::nextCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( next() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::backCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( back() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::onEnter()
{
    BaseTest::onEnter();
    
    _scene = dynamic_cast<Scene*>(this->getParent());
#ifdef CC_USE_PHYSICS
    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(PhysicsDemo::toggleDebugCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Point(VisibleRect::right().x-50, VisibleRect::top().y-10));
#else
#endif
}


void PhysicsDemo::toggleDebugCallback(Object* sender)
{
#ifdef CC_USE_PHYSICS
    if (_scene != nullptr)
    {
        _scene->getPhysicsWorld()->setDebugDraw(!_scene->getPhysicsWorld()->isDebugDraw());
    }
#endif
}

void PhysicsDemoClickAdd::onEnter()
{
    PhysicsDemo::onEnter();
    
#ifdef CC_USE_PHYSICS
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    
    auto sp = Sprite::create();
    auto body = PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size);
    sp->setPhysicsBody(body);
    sp->setPosition(VisibleRect::center());
    this->addChild(sp);
    
    auto parent = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
    _spriteTexture = parent->getTexture();
    
    addNewSpriteAtPosition(VisibleRect::center());
    
#else
    auto label = LabelTTF::create("Should define CC_USE_BOX2D or CC_USE_CHIPMUNK\n to run this test case",
                                  "Arial",
                                  18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Point(size.width/2, size.height/2));
    
    addChild(label);
#endif
}

void PhysicsDemoClickAdd::addNewSpriteAtPosition(Point p)
{
#ifdef CC_USE_PHYSICS
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    int posx, posy;
    
    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;
    
    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;
    
    auto sp = Sprite::createWithTexture(_spriteTexture, Rect(posx, posy, 85, 121));
    auto body = PhysicsBody::createBox(Size(48, 108));
    sp->setPhysicsBody(body);
    this->addChild(sp);
    sp->setPosition(p);
#endif
}

std::string PhysicsDemoClickAdd::subtitle()
{
    return "multi touch to add grossini";
}

void PhysicsDemoClickAdd::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    
    for( auto &touch: touches)
    {
        auto location = touch->getLocation();
        
        addNewSpriteAtPosition( location );
    }
}

void PhysicsDemoClickAdd::onAcceleration(Acceleration* acc, Event* event)
{
#ifdef CC_USE_PHYSICS
    static float prevX=0, prevY=0;
    
#define kFilterFactor 0.05f
    
    float accelX = (float) acc->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acc->y * kFilterFactor + (1- kFilterFactor)*prevY;
    
    prevX = accelX;
    prevY = accelY;
    
    auto v = Point( accelX, accelY);
    v = v * 200;
    
    if(_scene != nullptr)
    {
        _scene->getPhysicsWorld()->setGravity(v);
    }
#endif
}