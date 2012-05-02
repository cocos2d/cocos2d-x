//
//  HelloWorldScene.h
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#ifndef __HELLOW_WORLD_H__
#define __HELLOW_WORLD_H__

#include "cocos2d.h"

// include Chipmunk headers
#include "chipmunk.h"

class ChipmunkPhysicsSprite : public cocos2d::CCSprite
{
public:
    ChipmunkPhysicsSprite();
    virtual ~ChipmunkPhysicsSprite();
    void setPhysicsBody(cpBody* body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    cpBody* m_pBody;    // strong ref
};

// HelloWorld Layer
class HelloWorld : public cocos2d::CCLayer {
public:
    HelloWorld();
    ~HelloWorld();
 
    static cocos2d::CCScene* scene();
    LAYER_NODE_FUNC(HelloWorld);
    
    void initPhysics();
    void addNewSpriteAtPosition(CCPoint p);
    void update(ccTime dt);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

private:
    CCTexture2D* m_pSpriteTexture; // weak ref
    cpSpace* m_pSpace; // strong ref
    cpShape* m_pWalls[4];

};

#endif // __HELLOW_WORLD_H__
