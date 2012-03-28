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
	kTagBatchNode = 1,
};

static void
eachShape(void *ptr, void* unused)
{
        cpShape *shape = (cpShape*) ptr;
        CCSprite *sprite = (CCSprite*)shape->data;
        if( sprite ) 
        {
                cpBody *body = shape->body;
		
                // TIP: cocos2d and chipmunk uses the same struct to store it's position
                // chipmunk uses: cpVect, and cocos2d uses CGPoint but in reality the are the same
                // since v0.7.1 you can mix them if you want.		
                sprite->setPosition(CCPointMake(body->p.x, body->p.y));
                
                sprite->setRotation((float) CC_RADIANS_TO_DEGREES( -body->a ));
        }
}

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
}

CCScene* HelloWorld::scene()
{
        // 'scene' is an autorelease object.
        CCScene *scene = CCScene::node();
	
        // 'layer' is an autorelease object.
        HelloWorld *layer = HelloWorld::node();
	
        // add layer as a child to scene
        scene->addChild(layer);
	
        // return the scene
        return scene;
}


void HelloWorld::addNewSpriteX(float x,  float y)
{
        int posx, posy;
	
        CCSpriteBatchNode *batch = (CCSpriteBatchNode*) getChildByTag(kTagBatchNode);
	
        posx = (CCRANDOM_0_1() * 200);
        posy = (CCRANDOM_0_1() * 200);
	
        posx = (posx % 4) * 85;
        posy = (posy % 3) * 121;
	
        CCSprite *sprite = CCSprite::spriteWithBatchNode(batch, CCRectMake(posx, posy, 85, 121));
        batch->addChild(sprite);
	
        sprite->setPosition(ccp(x, y));
	
        int num = 4;
        cpVect verts[] = {
                cpv(-24,-54),
                cpv(-24, 54),
                cpv( 24, 54),
                cpv( 24,-54),
        };
	
        cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpv(0, 0)));
	
        // TIP:
        // since v0.7.1 you can assign CGPoint to chipmunk instead of cpVect.
        // cpVect == CGPoint
        body->p = cpv(x, y);
        cpSpaceAddBody(space, body);
	
        cpShape* shape = cpPolyShapeNew(body, num, verts, cpv(0, 0));
        shape->e = 0.5f; shape->u = 0.5f;
        shape->data = sprite;
        cpSpaceAddShape(space, shape);
}

bool HelloWorld::init()
{
        bool ret = false;
        
        if (ret = CCLayer::init()) 
        {
                setIsTouchEnabled(true);
		
                CCSize wins = CCDirector::sharedDirector()->getWinSize();
                cpInitChipmunk();
		
                cpBody *staticBody = cpBodyNew(INFINITY, INFINITY);
                space = cpSpaceNew();
                cpSpaceResizeStaticHash(space, 400.0f, 40);
                cpSpaceResizeActiveHash(space, 100, 600);
		
                space->gravity = cpv(0, 0);
                space->elasticIterations = space->iterations;
		
                cpShape *shape;
		
                // bottom
                shape = cpSegmentShapeNew(staticBody, cpv(0,0), cpv(wins.width,0), 0.0f);
                shape->e = 1.0f; shape->u = 1.0f;
                cpSpaceAddStaticShape(space, shape);
		
                // top
                shape = cpSegmentShapeNew(staticBody, cpv(0,wins.height), cpv(wins.width,wins.height), 0.0f);
                shape->e = 1.0f; shape->u = 1.0f;
                cpSpaceAddStaticShape(space, shape);
		
                // left
                shape = cpSegmentShapeNew(staticBody, cpv(0,0), cpv(0,wins.height), 0.0f);
                shape->e = 1.0f; shape->u = 1.0f;
                cpSpaceAddStaticShape(space, shape);
		
                // right
                shape = cpSegmentShapeNew(staticBody, cpv(wins.width,0), cpv(wins.width,wins.height), 0.0f);
                shape->e = 1.0f; shape->u = 1.0f;
                cpSpaceAddStaticShape(space, shape);
		
                CCSpriteBatchNode *batch = CCSpriteBatchNode::batchNodeWithFile("grossini_dance_atlas.png", 100);
                addChild(batch, 0, kTagBatchNode);
		
                addNewSpriteX(200, 200);
		
                schedule(schedule_selector(HelloWorld::step));
        }
        
        return ret;
}

void HelloWorld::onEnter()
{
        CCLayer::onEnter();
}

void HelloWorld::step(ccTime delta)
{
        int steps = 2;
        CGFloat dt = delta/(CGFloat)steps;
	
        for(int i=0; i<steps; i++)
        {
                cpSpaceStep(space, dt);
        }
        cpSpaceHashEach(space->activeShapes, &eachShape, NULL);
        cpSpaceHashEach(space->staticShapes, &eachShape, NULL);
}


void HelloWorld::ccTouchesEnded(CCSet *touches, CCEvent *event)
{
        CCSetIterator it;
        CCTouch *touch;
        
        for (it = touches->begin(); it != touches->end(); it++) {
                touch = (CCTouch*)(*it);
                
                if (! touch) {
                        break;
                }
                
                CCPoint location = touch->locationInView();
                location = CCDirector::sharedDirector()->convertToGL(location);
                addNewSpriteX(location.x, location.y);
        }
}

