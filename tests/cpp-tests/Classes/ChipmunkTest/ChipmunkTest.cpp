/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

//
// Accelerometer + Chipmunk physics + multi touches example
// a cocos2d example
// http://www.cocos2d-x.org
//

#include "chipmunk/chipmunk.h"

#include "ChipmunkTest.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum {
    kTagParentNode = 1,
};

enum {
    Z_PHYSICS_DEBUG = 100,
};

// callback to remove Shapes from the Space

ChipmunkTest::ChipmunkTest()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION      
    // enable events

    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(ChipmunkTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Device::setAccelerometerEnabled(true);
    auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(ChipmunkTest::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(accListener, this);
    
    // title
    auto label = Label::createWithTTF("Multi touch the screen", "fonts/Marker Felt.ttf", 36.0f);
    label->setPosition(VisibleRect::center().x, VisibleRect::top().y - 30);
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

    addNewSpriteAtPosition(cocos2d::Vec2(200.0f,200.0f));

    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(ChipmunkTest::toggleDebugCallback, this));

    auto menu = Menu::create(item, nullptr);
    this->addChild(menu);
    menu->setPosition(VisibleRect::right().x-100, VisibleRect::top().y-60);

    scheduleUpdate();
#else
    auto label = Label::createWithTTF("Should define CC_ENABLE_CHIPMUNK_INTEGRATION=1\n to run this test case",
                                            "fonts/arial.ttf",
                                            18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(size.width/2, size.height/2);
    
    addChild(label);
    
#endif
    
}

void ChipmunkTest::toggleDebugCallback(Ref* sender)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    _debugLayer->setVisible(! _debugLayer->isVisible());
#endif
}

ChipmunkTest::~ChipmunkTest()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( _walls[i] );
    }

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	cpSpaceFree(_space);
#else
	cpHastySpaceFree(_space);
#endif

    Device::setAccelerometerEnabled(false);
#endif
}

void ChipmunkTest::initPhysics()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    // init chipmunk
    //cpInitChipmunk();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_space = cpSpaceNew();
#else
	_space = cpHastySpaceNew();
	cpHastySpaceSetThreads(_space, 0);
#endif

    cpSpaceSetGravity(_space, cpv(0.0f, -100.0f));

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    _walls[0] = cpSegmentShapeNew( cpSpaceGetStaticBody(_space),
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y), 0.0f);

    // top
    _walls[1] = cpSegmentShapeNew( cpSpaceGetStaticBody(_space),
        cpv(VisibleRect::leftTop().x, VisibleRect::leftTop().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    // left
    _walls[2] = cpSegmentShapeNew( cpSpaceGetStaticBody(_space),
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::leftTop().x,VisibleRect::leftTop().y), 0.0f);

    // right
    _walls[3] = cpSegmentShapeNew( cpSpaceGetStaticBody(_space), 
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    for( int i=0;i<4;i++) {
        
        cpShapeSetElasticity(_walls[i], 1.0f);
        cpShapeSetFriction(_walls[i], 1.0f);
        cpSpaceAddShape(_space, _walls[i]);
    }

    // Physics debug layer
    _debugLayer = PhysicsDebugNode::create(_space);
    this->addChild(_debugLayer, Z_PHYSICS_DEBUG);
#endif
}

void ChipmunkTest::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = Director::getInstance()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		cpSpaceStep(_space, dt);
#else
		cpHastySpaceStep(_space, dt);
#endif
    }
}

void ChipmunkTest::createResetButton()
{
    auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", CC_CALLBACK_1(ChipmunkTest::reset, this));

    auto menu = Menu::create(reset, nullptr);

    menu->setPosition(VisibleRect::center().x, VisibleRect::bottom().y + 30);
    this->addChild(menu, -1);
}

void ChipmunkTest::reset(Ref* sender)
{
    getTestSuite()->restartCurrTest();
}

void ChipmunkTest::addNewSpriteAtPosition(cocos2d::Vec2 pos)
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

    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero, 0.0f));

    cpBodySetPosition(body, cpv(pos.x, pos.y));
    cpSpaceAddBody(_space, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpTransformIdentity, 0.0f);
    cpShapeSetElasticity(shape, 0.5f);
    cpShapeSetFriction(shape, 0.5f);
    cpSpaceAddShape(_space, shape);

    auto sprite = PhysicsSprite::createWithTexture(_spriteTexture, cocos2d::Rect(posx, posy, 85, 121));
    parent->addChild(sprite);

    sprite->setCPBody(body);
    sprite->setPosition(pos);
#endif
}

void ChipmunkTest::onEnter()
{
    TestCase::onEnter();
}

void ChipmunkTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location

    for( auto &touch: touches)
    {
        auto location = touch->getLocation();

        addNewSpriteAtPosition( location );
    }
}

void ChipmunkTest::onAcceleration(Acceleration* acc, Event* event)
{
    static float prevX=0, prevY=0;

#define kFilterFactor 0.05f

    float accelX = (float) acc->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acc->y * kFilterFactor + (1- kFilterFactor)*prevY;

    prevX = accelX;
    prevY = accelY;

    auto v = cocos2d::Vec2( accelX, accelY);
    v = v * 200;
    cpSpaceSetGravity(_space, cpv(v.x, v.y));
}

ChipmunkTests::ChipmunkTests()
{
    ADD_TEST_CASE(ChipmunkTest);
}

