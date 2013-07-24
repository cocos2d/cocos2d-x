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

class ChipmunkPhysicsSprite : public cc::Sprite
{
public:
    ChipmunkPhysicsSprite();
    virtual ~ChipmunkPhysicsSprite();
    void setPhysicsBody(cpBody* body);
    virtual bool isDirty(void);
    virtual cc::AffineTransform nodeToParentTransform(void);
private:
    cpBody* _body;    // strong ref
};

// HelloWorld Layer
class HelloWorld : public cc::Layer {
public:
    HelloWorld();
    ~HelloWorld();
    bool init();
    static cc::Scene* scene();
    CREATE_FUNC(HelloWorld);
    
    void initPhysics();
    void addNewSpriteAtPosition(cc::Point p);
    void update(float dt);
    virtual void ccTouchesEnded(cc::Set* touches, cc::Event* event);
    virtual void didAccelerate(cc::Acceleration* pAccelerationValue);

private:
    cc::Texture2D* _spriteTexture; // weak ref
    cpSpace* _space; // strong ref
    cpShape* _walls[4];

};

#endif // __HELLOW_WORLD_H__
