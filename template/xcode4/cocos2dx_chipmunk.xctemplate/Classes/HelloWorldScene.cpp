//
//  HelloWorldScene.cpp
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//


#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum {
    kTagParentNode = 1,
};

// callback to remove Shapes from the Space
void removeShape( cpBody *body, cpShape *shape, void *data )
{
    cpShapeFree( shape );
}

ChipmunkPhysicsSprite::ChipmunkPhysicsSprite()
: _body(NULL)
{

}

ChipmunkPhysicsSprite::~ChipmunkPhysicsSprite()
{
    cpBodyEachShape(_body, removeShape, NULL);
    cpBodyFree( _body );
}

void ChipmunkPhysicsSprite::setPhysicsBody(cpBody * body)
{
    _body = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool ChipmunkPhysicsSprite::isDirty(void)
{
    return true;
}

AffineTransform ChipmunkPhysicsSprite::nodeToParentTransform(void)
{
    float x = _body->p.x;
    float y = _body->p.y;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += _anchorPointInPoints.x;
        y += _anchorPointInPoints.y;
    }

    // Make matrix
    float c = _body->rot.x;
    float s = _body->rot.y;

    if( ! _anchorPointInPoints.equals(PointZero) ){
        x += c*-_anchorPointInPoints.x + -s*-_anchorPointInPoints.y;
        y += s*-_anchorPointInPoints.x + c*-_anchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    _transform = AffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return _transform;
}

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( _walls[i] );
    }
    
    cpSpaceFree( _space );
    
}

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object.
    Scene *scene = Scene::create();

    // 'layer' is an autorelease object.
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // enable events
    setTouchEnabled(true);
    setAccelerometerEnabled(true);

    Size s = Director::sharedDirector()->getWinSize();

    // title
    LabelTTF *label = LabelTTF::create("Multi touch the screen", "Marker Felt", 36);
    label->setPosition(ccp( s.width / 2, s.height - 30));
    this->addChild(label, -1);

    // init physics
    initPhysics();

#if 1
    // Use batch node. Faster
    SpriteBatchNode *parent = SpriteBatchNode::create("grossini_dance_atlas.png", 100);
    _spriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    _spriteTexture = TextureCache::sharedTextureCache()->addImage("grossini_dance_atlas.png");
    Node *parent = Node::node();
#endif
    addChild(parent, 0, kTagParentNode);

    addNewSpriteAtPosition(ccp(200,200));

    scheduleUpdate();

    return true;
}


void HelloWorld::initPhysics()
{
    Size s = Director::sharedDirector()->getWinSize();

    // init chipmunk
    cpInitChipmunk();

    _space = cpSpaceNew();

    _space->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    _walls[0] = cpSegmentShapeNew( _space->staticBody, cpv(0,0), cpv(s.width,0), 0.0f);

    // top
    _walls[1] = cpSegmentShapeNew( _space->staticBody, cpv(0,s.height), cpv(s.width,s.height), 0.0f);

    // left
    _walls[2] = cpSegmentShapeNew( _space->staticBody, cpv(0,0), cpv(0,s.height), 0.0f);

    // right
    _walls[3] = cpSegmentShapeNew( _space->staticBody, cpv(s.width,0), cpv(s.width,s.height), 0.0f);

    for( int i=0;i<4;i++) {
        _walls[i]->e = 1.0f;
        _walls[i]->u = 1.0f;
        cpSpaceAddStaticShape(_space, _walls[i] );
    }
}

void HelloWorld::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = Director::sharedDirector()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(_space, dt);
    }
}

void HelloWorld::addNewSpriteAtPosition(Point pos)
{
    int posx, posy;

    Node *parent = getChildByTag(kTagParentNode);

    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;

    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;

    ChipmunkPhysicsSprite *sprite = new ChipmunkPhysicsSprite();
    sprite->initWithTexture(_spriteTexture, CCRectMake(posx, posy, 85, 121));
    sprite->autorelease();

    parent->addChild(sprite);

    sprite->setPosition(pos);

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

    sprite->setPhysicsBody(body);
}

void HelloWorld::ccTouchesEnded(Set* touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    SetIterator it;
    Touch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (Touch*)(*it);

        if(!touch)
            break;

        Point location = touch->getLocationInView();

        location = Director::sharedDirector()->convertToGL(location);

        addNewSpriteAtPosition( location );
    }
}

void HelloWorld::didAccelerate(Acceleration* pAccelerationValue)
{
    static float prevX=0, prevY=0;

#define kFilterFactor 0.05f

    float accelX = (float) pAccelerationValue->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) pAccelerationValue->y * kFilterFactor + (1- kFilterFactor)*prevY;

    prevX = accelX;
    prevY = accelY;

    Point v = ccp( accelX, accelY);
    v = ccpMult(v, 200);
    _space->gravity = cpv(v.x, v.y);
}


