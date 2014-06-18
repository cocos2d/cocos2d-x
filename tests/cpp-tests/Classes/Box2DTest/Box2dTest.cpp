#include "Box2dTest.h"
#include "../testResource.h"
#include "extensions/cocos-ext.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

USING_NS_CC_EXT;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

Box2DTestLayer::Box2DTestLayer()
: _spriteTexture(nullptr)
, world(nullptr)
{
#if CC_ENABLE_BOX2D_INTEGRATION
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(Box2DTestLayer::onTouchesEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // init physics
    this->initPhysics();
    // create reset button
    this->createResetButton();

    //Set up sprite
#if 1
    // Use batch node. Faster
    auto parent = SpriteBatchNode::create("Images/blocks.png", 100);
    _spriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    _spriteTexture = Director::getInstance()->getTextureCache()->addImage("Images/blocks.png");
    auto parent = Node::create();
#endif
    addChild(parent, 0, kTagParentNode);


    addNewSpriteAtPosition(VisibleRect::center());

    auto label = Label::createWithTTF("Tap screen", "fonts/Marker Felt.ttf", 32.0f);
    addChild(label, 0);
    label->setColor(Color3B(0,0,255));
    label->setPosition(Vec2( VisibleRect::center().x, VisibleRect::top().y-50));
    
    scheduleUpdate();
#else
    auto label = Label::createWithTTF("Should define CC_ENABLE_BOX2D_INTEGRATION=1\n to run this test case",
                                            "fonts/arial.ttf",
                                            18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(size.width/2, size.height/2));
    
    addChild(label);
#endif
}

Box2DTestLayer::~Box2DTestLayer()
{
    CC_SAFE_DELETE(world);
    
    //delete _debugDraw;
}

void Box2DTestLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);

//     _debugDraw = new GLESDebugDraw( PTM_RATIO );
//     world->SetDebugDraw(_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //_debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void Box2DTestLayer::createResetButton()
{
    auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", [](Ref *sender) {
		auto s = new Box2DTestScene();
		auto child = new Box2DTestLayer();
		s->addChild(child);
		child->release();
		Director::getInstance()->replaceScene(s);
		s->release();
	});

    auto menu = Menu::create(reset, NULL);

    menu->setPosition(Vec2(VisibleRect::bottom().x, VisibleRect::bottom().y + 30));
    this->addChild(menu, -1);

}

void Box2DTestLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    Layer::draw(renderer, transform, flags);

#if CC_ENABLE_BOX2D_INTEGRATION
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    _modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Box2DTestLayer::onDraw, this);
    renderer->addCommand(&_customCommand);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
#endif
}

#if CC_ENABLE_BOX2D_INTEGRATION
void Box2DTestLayer::onDraw()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Mat4 oldMV;
    oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
    world->DrawDebugData();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}
#endif

void Box2DTestLayer::addNewSpriteAtPosition(Vec2 p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);    
    
#if CC_ENABLE_BOX2D_INTEGRATION
    auto parent = this->getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    auto sprite = PhysicsSprite::createWithTexture(_spriteTexture,Rect(32 * idx,32 * idy,32,32));
    parent->addChild(sprite);
    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
    sprite->setPosition( Vec2( p.x, p.y) );
#endif
}


void Box2DTestLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;

    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
}

void Box2DTestLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location

    for (auto& touch : touches)
    {
        if(!touch)
            break;

        auto location = touch->getLocation();
    
        addNewSpriteAtPosition( location );
    }
}

/*
void Box2DTestLayer::accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration)
{    
    static float prevX=0, prevY=0;

//#define kFilterFactor 0.05f
#define kFilterFactor 1.0f    // don't use filter. the code is here just as an example
    
    float accelX = (float) acceleration.x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acceleration.y * kFilterFactor + (1- kFilterFactor)*prevY;
    
    prevX = accelX;
    prevY = accelY;
    
    // accelerometer values are in "Portrait" mode. Change them to Landscape left
    // multiply the gravity by 10
    b2Vec2 gravity( -accelY * 10, accelX * 10);
    
    world->SetGravity( gravity );
}
*/

void Box2DTestScene::runThisTest()
{
    auto layer = new Box2DTestLayer();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
 