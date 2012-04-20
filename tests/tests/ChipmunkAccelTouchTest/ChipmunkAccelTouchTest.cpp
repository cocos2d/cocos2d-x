//
// Accelerometer + Chipmunk physics + multi touches example
// a cocos2d example
// http://www.cocos2d-x.org
//

#include "ChipmunkAccelTouchTest.h"

enum {
    kTagParentNode = 1,
};

// callback to remove Shapes from the Space
void removeShape( cpBody *body, cpShape *shape, void *data )
{
    cpShapeFree( shape );
}

ChipmunkPhysicsSprite::ChipmunkPhysicsSprite()
: body_(NULL)
{

}

ChipmunkPhysicsSprite::~ChipmunkPhysicsSprite()
{
    cpBodyEachShape(body_, removeShape, NULL);
    cpBodyFree( body_ );
}

void ChipmunkPhysicsSprite::setPhysicsBody(cpBody * body)
{
    body_ = body;
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
    CCFloat x = body_->p.x;
    CCFloat y = body_->p.y;

    if ( !getIsRelativeAnchorPoint() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }

    // Make matrix
    CCFloat c = body_->rot.x;
    CCFloat s = body_->rot.y;

    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_tTransform;
}

ChipmunkAccelTouchTestLayer::ChipmunkAccelTouchTestLayer()
{
    // enable events
    setIsTouchEnabled(true);
    setIsAccelerometerEnabled(true);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // title
    CCLabelTTF *label = CCLabelTTF::labelWithString("Multi touch the screen", "Marker Felt", 36);
    label->setPosition(ccp( s.width / 2, s.height - 30));
    this->addChild(label, -1);

    // reset button
    createResetButton();

    // init physics
    initPhysics();

#if 1
    // Use batch node. Faster
    CCSpriteBatchNode *parent = CCSpriteBatchNode::batchNodeWithFile("Images/grossini_dance_atlas.png", 100);
    spriteTexture_ = parent->getTexture();
#else
    // doesn't use batch node. Slower
    spriteTexture_ = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas.png");
    CCNode *parent = CCNode::node();
#endif
    addChild(parent, 0, kTagParentNode);

    addNewSpriteAtPosition(ccp(200,200));

    scheduleUpdate();
}

ChipmunkAccelTouchTestLayer::~ChipmunkAccelTouchTestLayer()
{
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( walls_[i] );
    }

    cpSpaceFree( space_ );

}

void ChipmunkAccelTouchTestLayer::initPhysics()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // init chipmunk
    cpInitChipmunk();

    space_ = cpSpaceNew();

    space_->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    walls_[0] = cpSegmentShapeNew( space_->staticBody, cpv(0,0), cpv(s.width,0), 0.0f);

    // top
    walls_[1] = cpSegmentShapeNew( space_->staticBody, cpv(0,s.height), cpv(s.width,s.height), 0.0f);

    // left
    walls_[2] = cpSegmentShapeNew( space_->staticBody, cpv(0,0), cpv(0,s.height), 0.0f);

    // right
    walls_[3] = cpSegmentShapeNew( space_->staticBody, cpv(s.width,0), cpv(s.width,s.height), 0.0f);

    for( int i=0;i<4;i++) {
        walls_[i]->e = 1.0f;
        walls_[i]->u = 1.0f;
        cpSpaceAddStaticShape(space_, walls_[i] );
    }
}

void ChipmunkAccelTouchTestLayer::update(ccTime delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    CCFloat dt = CCDirector::sharedDirector()->getAnimationInterval()/(CCFloat)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(space_, dt);
    }
}

void ChipmunkAccelTouchTestLayer::createResetButton()
{
    CCMenuItemImage *reset = CCMenuItemImage::itemWithNormalImage("Images/r1.png", "Images/r2.png", this, menu_selector(ChipmunkAccelTouchTestLayer::reset));

    CCMenu *menu = CCMenu::menuWithItems(reset, NULL);

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    menu->setPosition(ccp(s.width/2, 30));
    this->addChild(menu, -1);
}

void ChipmunkAccelTouchTestLayer::reset(CCObject* sender)
{
    CCScene* s = new ChipmunkAccelTouchTestScene();
    ChipmunkAccelTouchTestLayer* child = new ChipmunkAccelTouchTestLayer();
    s->addChild(child);
    child->release();
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ChipmunkAccelTouchTestLayer::addNewSpriteAtPosition(CCPoint pos)
{
    int posx, posy;

    CCNode *parent = getChildByTag(kTagParentNode);

    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;

    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;

    ChipmunkPhysicsSprite *sprite = new ChipmunkPhysicsSprite();
    sprite->initWithTexture(spriteTexture_, CCRectMake(posx, posy, 85, 121));
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
    cpSpaceAddBody(space_, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f; shape->u = 0.5f;
    cpSpaceAddShape(space_, shape);

    sprite->setPhysicsBody(body);
}

void ChipmunkAccelTouchTestLayer::onEnter()
{
    CCLayer::onEnter();
}

void ChipmunkAccelTouchTestLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->locationInView();

        location = CCDirector::sharedDirector()->convertToGL(location);

        addNewSpriteAtPosition( location );
    }
}

void ChipmunkAccelTouchTestLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
    static float prevX=0, prevY=0;

#define kFilterFactor 0.05f

    float accelX = (float) pAccelerationValue->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) pAccelerationValue->y * kFilterFactor + (1- kFilterFactor)*prevY;

    prevX = accelX;
    prevY = accelY;

    CCPoint v = ccp( accelX, accelY);
    v = ccpMult(v, 200);
    space_->gravity = cpv(v.x, v.y);
}

void ChipmunkAccelTouchTestScene::runThisTest()
{
    CCLayer* pLayer = new ChipmunkAccelTouchTestLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}

