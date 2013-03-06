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
    setTouchEnabled(true);
    setAccelerometerEnabled(true);

    // title
    CCLabelTTF *label = CCLabelTTF::create("Multi touch the screen", "Marker Felt", 36);
    label->setPosition(ccp( VisibleRect::center().x, VisibleRect::top().y - 30));
    this->addChild(label, -1);

    // reset button
    createResetButton();

    // init physics
    initPhysics();

#if 1
    // Use batch node. Faster
    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
    m_pSpriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    m_pSpriteTexture = CCTextureCache::sharedTextureCache()->addImage("Images/grossini_dance_atlas.png");
    CCNode *parent = CCNode::create();
#endif
    addChild(parent, 0, kTagParentNode);

    addNewSpriteAtPosition(ccp(200,200));

    // menu for debug layer
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont *item = CCMenuItemFont::create("Toggle debug", this, menu_selector(ChipmunkTestLayer::toggleDebugCallback));

    CCMenu *menu = CCMenu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(ccp(VisibleRect::right().x-100, VisibleRect::top().y-60));

    scheduleUpdate();
#else
    CCLabelTTF *pLabel = CCLabelTTF::create("Should define CC_ENABLE_CHIPMUNK_INTEGRATION=1\n to run this test case",
                                            "Arial",
                                            18);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition(ccp(size.width/2, size.height/2));
    
    addChild(pLabel);
    
#endif
    
}

void ChipmunkTestLayer::toggleDebugCallback(CCObject* pSender)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    m_pDebugLayer->setVisible(! m_pDebugLayer->isVisible());
#endif
}

ChipmunkTestLayer::~ChipmunkTestLayer()
{
    // manually Free rogue shapes
    for( int i=0;i<4;i++) {
        cpShapeFree( m_pWalls[i] );
    }

    cpSpaceFree( m_pSpace );

}

void ChipmunkTestLayer::initPhysics()
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    // init chipmunk
    //cpInitChipmunk();

    m_pSpace = cpSpaceNew();

    m_pSpace->gravity = cpv(0, -100);

    //
    // rogue shapes
    // We have to free them manually
    //
    // bottom
    m_pWalls[0] = cpSegmentShapeNew( m_pSpace->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y), 0.0f);

    // top
    m_pWalls[1] = cpSegmentShapeNew( m_pSpace->staticBody, 
        cpv(VisibleRect::leftTop().x, VisibleRect::leftTop().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    // left
    m_pWalls[2] = cpSegmentShapeNew( m_pSpace->staticBody,
        cpv(VisibleRect::leftBottom().x,VisibleRect::leftBottom().y),
        cpv(VisibleRect::leftTop().x,VisibleRect::leftTop().y), 0.0f);

    // right
    m_pWalls[3] = cpSegmentShapeNew( m_pSpace->staticBody, 
        cpv(VisibleRect::rightBottom().x, VisibleRect::rightBottom().y),
        cpv(VisibleRect::rightTop().x, VisibleRect::rightTop().y), 0.0f);

    for( int i=0;i<4;i++) {
        m_pWalls[i]->e = 1.0f;
        m_pWalls[i]->u = 1.0f;
        cpSpaceAddStaticShape(m_pSpace, m_pWalls[i] );
    }

    // Physics debug layer
    m_pDebugLayer = CCPhysicsDebugNode::create(m_pSpace);
    this->addChild(m_pDebugLayer, Z_PHYSICS_DEBUG);
#endif
}

void ChipmunkTestLayer::update(float delta)
{
    // Should use a fixed size step based on the animation interval.
    int steps = 2;
    float dt = CCDirector::sharedDirector()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(m_pSpace, dt);
    }
}

void ChipmunkTestLayer::createResetButton()
{
    CCMenuItemImage *reset = CCMenuItemImage::create("Images/r1.png", "Images/r2.png", this, menu_selector(ChipmunkTestLayer::reset));

    CCMenu *menu = CCMenu::create(reset, NULL);

    menu->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + 30));
    this->addChild(menu, -1);
}

void ChipmunkTestLayer::reset(CCObject* sender)
{
    CCScene* s = new ChipmunkAccelTouchTestScene();
    ChipmunkTestLayer* child = new ChipmunkTestLayer();
    s->addChild(child);
    child->release();
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ChipmunkTestLayer::addNewSpriteAtPosition(CCPoint pos)
{
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    int posx, posy;

    CCNode *parent = getChildByTag(kTagParentNode);

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
    cpSpaceAddBody(m_pSpace, body);

    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
    shape->e = 0.5f; shape->u = 0.5f;
    cpSpaceAddShape(m_pSpace, shape);

    CCPhysicsSprite *sprite = CCPhysicsSprite::createWithTexture(m_pSpriteTexture, CCRectMake(posx, posy, 85, 121));
    parent->addChild(sprite);

    sprite->setCPBody(body);
    sprite->setPosition(pos);
#endif
}

void ChipmunkTestLayer::onEnter()
{
    CCLayer::onEnter();
}

void ChipmunkTestLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);

        if(!touch)
            break;

        CCPoint location = touch->getLocation();

        addNewSpriteAtPosition( location );
    }
}

void ChipmunkTestLayer::didAccelerate(CCAcceleration* pAccelerationValue)
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

void ChipmunkAccelTouchTestScene::runThisTest()
{
    CCLayer* pLayer = new ChipmunkTestLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}

