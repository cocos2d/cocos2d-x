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
    
    void toggleDebug();
    
private:
    static bool _debugDraw;
};

class PhysicsDemo : public BaseTest
{
protected:
    PhysicsTestScene* _scene;
    
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
    
    void addGrossiniAtPosition(Point p, float scale = 1.0);
    
private:
    Texture2D* _spriteTexture;    // weak ref
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string subtitle() override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    void onAcceleration(Acceleration* acc, Event* event) override;
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
    
    Node* makeBall(float x, float y);
    
private:
    SpriteBatchNode* _ball;
};

class PhysicsDemoPyramidStack : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
};

class PhysicsDemoPlink : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
};

#endif
