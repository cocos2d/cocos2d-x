#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

#include <map>


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
    
    Sprite* addGrossiniAtPosition(Point p, float scale = 1.0);
    Sprite* makeBall(Point point, float radius, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    Sprite* makeBox(Point point, Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    Sprite* makeTriangle(Point point, Size size, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
protected:
    PhysicsTestScene* _scene;
    Texture2D* _spriteTexture;    // weak ref
    SpriteBatchNode* _ball;
    std::map<int, Node*> _mouses;
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    virtual ~PhysicsDemoClickAdd();
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
    
    bool anyRay(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    
private:
    float _angle;
    DrawNode* _node;
    int _mode;
};

class PhysicsDemoJoints : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
};

class PhysicsDemoActions : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
};

class PhysicsDemoPump : public PhysicsDemo
{
public:
    void onEnter() override;
    void update(float delta) override;
    std::string title() override;
    std::string subtitle() override;
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
private:
    float _distance;
    float _rotationV;
};

class PhysicsDemoOneWayPlatform : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
    
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
};

class PhysicsDemoSlice : public PhysicsDemo
{
public:
    void onEnter() override;
    std::string title() override;
    std::string subtitle() override;
    
    bool slice(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    void clipPoly(PhysicsShapePolygon* shape, Point normal, float distance);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    
private:
    int _sliceTag;
};

#endif
