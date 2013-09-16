#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class PhysicsTestLayer : public Layer
{
    Texture2D* _spriteTexture;    // weak ref
    
public:
    PhysicsTestLayer();
    ~PhysicsTestLayer();

    void createResetButton();
    
    void toggleDebugCallback(Object* sender);
    void addNewSpriteAtPosition(Point p);
    virtual void ccTouchesEnded(Set* touches, Event* event);
} ;

class PhysicsTestScene : public TestScene
{
public:
    virtual bool initTest() override;
    virtual void runThisTest();
};

#endif
