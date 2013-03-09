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
: m_pBody(NULL)
{

}

ChipmunkPhysicsSprite::~ChipmunkPhysicsSprite()
{
    cpBodyEachShape(m_pBody, removeShape, NULL);
    cpBodyFree( m_pBody );
}

void ChipmunkPhysicsSprite::setPhysicsBody(cpBody * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool ChipmunkPhysicsSprite::isDirty(void)
{
    return true;
}

CCAffineTransform ChipmunkPhysicsSprite::nodeToParentTransform(void)
{
    float x = m_pBody->p.x;
    float y = m_pBody->p.y;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float c = m_pBody->rot.x;
    float s = m_pBody->rot.y;

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( m_pWalls[i] );
    }
    
    cpSpaceFree( m_pSpace );
    
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object.
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object.
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    // enable events
    setTouchEnabled(true);
    setAccelerometerEnabled(true);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // title
    CCLabelTTF *label = CCLabelTTF::create("Multi touch the screen", "Marker Felt", 36);
    label->setPosition(ccp( s.width / 2, s.height - 30));
    this->addChild(label, -1);

    // init physics
    initPhysics();

#if 1
    // Use batch node. Faster
    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("grossini_dance_atlas.png", 100);
    m_pSpriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    m_pSpriteTexture = CCTextureCache::sharedTextureCache()->addImage("grossini_dance_atlas.png");
    CCNode *parent = CCNode::node();
#endif
    addChild(parent, 0, kTagParentNode);

    addNewSpriteAtPosition(ccp(200,200));

    scheduleUpdate();

    return true;
}


void HelloWorld::initPhysics()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // init chipmunk
    cpInitChipmunk();

    m_pSpace = cpSpaceNew();

    m_pSpace->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    m_pWalls[0] = cpSegmentShapeNew( m_pSpace->staticBody, cpv(0,0), cpv(s.width,0), 0.0f);

    // top
    m_pWalls[1] = cpSegmentShapeNew( m_pSpace->staticBody, cpv(0,s.height), cpv(s.width,s.height), 0.0f);

    // left
    m_pWalls[2] = cpSegmentShapeNew( m_pSpace->staticBody, cpv(0,0), cpv(0,s.height), 0.0f);

    // right
    m_pWalls[3] = cpSegmentShapeNew( m_pSpace->staticBody, cpv(s.width,0), cpv(s.width,s.height), 0.0f);

    for( int i=0;i<4;i++) {
        m_pWalls[i]->e = 1.0f;
        m_pWalls[i]->u = 1.0f;
        cpSpaceAddStaticShape(m_pSpace, m_pWalls[i] );
    }
}

void HelloWorld::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = CCDirector::sharedDirector()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(m_pSpace, dt);
    }
}

void HelloWorld::addNewSpriteAtPosition(CCPoint pos)
{
    int posx, posy;

    CCNode *parent = getChildByTag(kTagParentNode);

    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;

    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;

    ChipmunkPhysicsSprite *sprite = new ChipmunkPhysicsSprite();
    sprite->initWithTexture(m_pSpriteTexture, CCRectMake(posx, posy, 85, 121));
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
    cpSpaceAddBody(m_pSpace, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f; shape->u = 0.5f;
    cpSpaceAddShape(m_pSpace, shape);

    sprite->setPhysicsBody(body);
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocationInView();

        location = CCDirector::sharedDirector()->convertToGL(location);

        addNewSpriteAtPosition( location );
    }
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
    static float prevX=0, prevY=0;

#define kFilterFactor 0.05f

    float accelX = (float) pAccelerationValue->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) pAccelerationValue->y * kFilterFactor + (1- kFilterFactor)*prevY;

    prevX = accelX;
    prevY = accelY;

    CCPoint v = ccp( accelX, accelY);
    v = ccpMult(v, 200);
    m_pSpace->gravity = cpv(v.x, v.y);
}


