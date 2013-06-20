//
//  HelloWorldScene.h
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

class PhysicsSprite : public cocos2d::Sprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::AffineTransform nodeToParentTransform(void);
private:
    b2Body* _body;    // strong ref
};

class HelloWorld : public cocos2d::Layer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::Scene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::Point p);

    virtual void draw();
    virtual void ccTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);
    void update(float dt);
    
private:
    b2World* world;
    cocos2d::Texture2D* _spriteTexture; // weak ref
};

#endif // __HELLO_WORLD_H__
