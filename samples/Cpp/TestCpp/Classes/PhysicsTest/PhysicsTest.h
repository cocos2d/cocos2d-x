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
    Sprite* makeBall(float x, float y, float radius, PhysicsMaterial material = PhysicsMaterial(1.0f, 1.0f, 1.0f));
    Sprite* makeBox(float x, float y, Size size, PhysicsMaterial material = PhysicsMaterial(1.0f, 1.0f, 1.0f));
    Sprite* makeTriangle(float x, float y, Size size, PhysicsMaterial material = PhysicsMaterial(1.0f, 1.0f, 1.0f));
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    
protected:
    Texture2D* _spriteTexture;    // weak ref
    SpriteBatchNode* _ball;
    DrawNode* _mouse;
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string subtitle() override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onAcceleration(Acceleration* acc, Event* event);
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
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

class PhysicsDemoRayCast : public PhysicsDemo
{
public:
    PhysicsDemoRayCast();
public:
    void onEnter() override;
    std::string title() override;
    void update(float delta) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    
    void changeModeCallback(Object* sender);
    
    static bool anyRay(PhysicsWorld& world, PhysicsShape& shape, Point point, Point normal, float fraction, void* data);
    
private:
    float _angle;
    DrawNode* _node;
    int _mode;
};

class PhysicsDemoJoints : public PhysicsDemo
{
public:
    PhysicsDemoJoints();
    
public:
    void onEnter() override;
    std::string title() override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
};

#endif
