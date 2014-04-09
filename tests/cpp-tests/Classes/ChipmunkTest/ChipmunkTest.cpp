//
// Accelerometer + Chipmunk physics + multi touches example
// a cocos2d example
// http://www.cocos2d-x.org
//

#include "ChipmunkTest.h"


enum {
    kTagParentNode = 1,
};

enum {
    Z_PHYSICS_DEBUG = 100,
};

// callback to remove Shapes from the Space

ChipmunkTestLayer::ChipmunkTestLayer()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION      
    // enable events

    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(ChipmunkTestLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Device::setAccelerometerEnabled(true);
    auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(ChipmunkTestLayer::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(accListener, this);
    
    // title
    auto label = Label::createWithTTF("Multi touch the screen", "fonts/Marker Felt.ttf", 36.0f);
    label->setPosition(cocos2d::Point( VisibleRect::center().x, VisibleRect::top().y - 30));
    this->addChild(label, -1);

    // reset button
    createResetButton();

    // init physics
    initPhysics();

#if 1
    // Use batch node. Faster
    auto parent = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
    _spriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    _spriteTexture = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
    auto parent = Node::create();
#endif
    addChild(parent, 0, kTagParentNode);

    addNewSpriteAtPosition(cocos2d::Point(200,200));

    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(ChipmunkTestLayer::toggleDebugCallback, this));

    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(cocos2d::Point(VisibleRect::right().x-100, VisibleRect::top().y-60));

    scheduleUpdate();
#else
    auto label = Label::createWithTTF("Should define CC_ENABLE_CHIPMUNK_INTEGRATION=1\n to run this test case",
                                            "fonts/arial.ttf",
                                            18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Point(size.width/2, size.height/2));
    
    addChild(label);
    
#endif
    
}

void ChipmunkTestLayer::toggleDebugCallback(Ref* sender)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    _debugLayer->setVisible(! _debugLayer->isVisible());
#endif
}

ChipmunkTestLayer::~ChipmunkTestLayer()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( _walls[i] );
    }

    cpSpaceFree( _space );

    Device::setAccelerometerEnabled(false);
#endif
}

void ChipmunkTestLayer::initPhysics()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    // init chipmunk
    //cpInitChipmunk();

    _space = cpSpaceNew();

    _space->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    _walls[0] = cpSegmentShapeNew( _space->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y), 0.0f);

    // top
    _walls[1] = cpSegmentShapeNew( _space->staticBody, 
        cpv(VisibleRect::leftTop().x, VisibleRect::leftTop().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    // left
    _walls[2] = cpSegmentShapeNew( _space->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::leftTop().x,VisibleRect::leftTop().y), 0.0f);

    // right
    _walls[3] = cpSegmentShapeNew( _space->staticBody, 
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    for( int i=0;i<4;i++) {
        _walls[i]->e = 1.0f;
        _walls[i]->u = 1.0f;
        cpSpaceAddStaticShape(_space, _walls[i] );
    }

    // Physics debug layer
    _debugLayer = PhysicsDebugNode::create(_space);
    this->addChild(_debugLayer, Z_PHYSICS_DEBUG);
#endif
}

void ChipmunkTestLayer::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = Director::getInstance()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(_space, dt);
    }
}

void ChipmunkTestLayer::createResetButton()
{
    auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", CC_CALLBACK_1(ChipmunkTestLayer::reset, this));

    auto menu = Menu::create(reset, NULL);

    menu->setPosition(cocos2d::Point(VisibleRect::center().x, VisibleRect::bottom().y + 30));
    this->addChild(menu, -1);
}

void ChipmunkTestLayer::reset(Ref* sender)
{
    auto s = new ChipmunkAccelTouchTestScene();
    auto child = new ChipmunkTestLayer();
    s->addChild(child);
    child->release();
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ChipmunkTestLayer::addNewSpriteAtPosition(cocos2d::Point pos)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    int posx, posy;

    auto parent = getChildByTag(kTagParentNode);

    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;

    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;


    int num = 4;
    cpVect verts[] = {
        cpv(-24,-54),
        cpv(-24, 54),
        cpv( 24, 54),
        cpv( 24,-54),
    };

    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));

    body->p = cpv(pos.x, pos.y);
    cpSpaceAddBody(_space, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f; shape->u = 0.5f;
    cpSpaceAddShape(_space, shape);

    auto sprite = PhysicsSprite::createWithTexture(_spriteTexture, cocos2d::Rect(posx, posy, 85, 121));
    parent->addChild(sprite);

    sprite->setCPBody(body);
    sprite->setPosition(pos);
#endif
}

void ChipmunkTestLayer::onEnter()
{
    Layer::onEnter();
}

void ChipmunkTestLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location

    for( auto &touch: touches)
    {
        auto location = touch->getLocation();

        addNewSpriteAtPosition( location );
    }
}

void ChipmunkTestLayer::onAcceleration(Acceleration* acc, Event* event)
{
    static float prevX=0, prevY=0;

#define kFilterFactor 0.05f

    float accelX = (float) acc->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acc->y * kFilterFactor + (1- kFilterFactor)*prevY;

    prevX = accelX;
    prevY = accelY;

    auto v = cocos2d::Point( accelX, accelY);
    v = v * 200;
    _space->gravity = cpv(v.x, v.y);
}

void ChipmunkAccelTouchTestScene::runThisTest()
{
    auto layer = new ChipmunkTestLayer();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}

