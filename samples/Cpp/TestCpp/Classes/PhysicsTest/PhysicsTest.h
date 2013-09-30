#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"


class PhysicsTestScene : public TestScene
{
public:
    virtual bool initTest() override;
    virtual void runThisTest();
};

class PhysicsDemo : public BaseTest
{
protected:
    Scene* _scene;
    
public:
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual void onEnter() override;
    virtual std::string title() override;
    virtual std::string subtitle() override;
    
    void restartCallback(Object* sender);
    void nextCallback(Object* sender);
    void backCallback(Object* sender);
    void toggleDebugCallback(Object* sender);
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string subtitle() override;
    
    void addNewSpriteAtPosition(Point p);
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    void onAcceleration(Acceleration* acc, Event* event) override;
    
private:
    Texture2D* _spriteTexture;    // weak ref
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
    
    Node* makeBall(float x, float y);
    
private:
    DrawNode* _draw;
};

#endif
