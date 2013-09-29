#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"


class PhysicsDemo : public BaseTest
{
protected:
    Scene* _scene;
    
public:
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual void onEnter();
    virtual std::string title();
    virtual std::string subtitle();
    
    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
    void toggleDebugCallback(Object* sender);
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
private:
    Texture2D* _spriteTexture;    // weak ref
    
public:
    void onEnter();
    std::string subtitle();
    
    void addNewSpriteAtPosition(Point p);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onAcceleration(Acceleration* acc, Event* event);
};

class PhysicsTestScene : public TestScene
{
public:
    virtual bool initTest() override;
    virtual void runThisTest();
};

#endif
