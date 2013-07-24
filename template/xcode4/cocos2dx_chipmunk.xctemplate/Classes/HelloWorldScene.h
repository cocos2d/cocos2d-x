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

class ChipmunkPhysicsSprite : public cocos2d::Sprite
{
public:
    ChipmunkPhysicsSprite();
    virtual ~ChipmunkPhysicsSprite();
    void setPhysicsBody(cpBody* body);
    virtual bool isDirty(void);
    virtual cocos2d::AffineTransform nodeToParentTransform(void);
private:
    cpBody* _body;    // strong ref
};

// HelloWorld Layer
class HelloWorld : public cocos2d::Layer {
public:
    HelloWorld();
    ~HelloWorld();
    bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HelloWorld);
    
    void initPhysics();
    void addNewSpriteAtPosition(cocos2d::Point p);
    void update(float dt);
    virtual void ccTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
    virtual void didAccelerate(cocos2d::Acceleration* pAccelerationValue);

private:
    cocos2d::Texture2D* _spriteTexture; // weak ref
    cpSpace* _space; // strong ref
    cpShape* _walls[4];

};

#endif // __HELLOW_WORLD_H__
