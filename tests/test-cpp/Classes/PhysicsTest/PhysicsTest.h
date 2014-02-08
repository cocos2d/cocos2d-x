#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"
#include "../BaseTest.h"

#include <map>


class PhysicsTestScene : public TestScene
{
public:
    PhysicsTestScene();
    
public:
    virtual void runThisTest();
    
    void toggleDebug();
    
private:
    bool _debugDraw;
};

#if CC_USE_PHYSICS == 0
class PhysicsDemoDisabled : public BaseTest
{
public:
    CREATE_FUNC(PhysicsDemoDisabled);
    
    virtual void onEnter() override;
};
#else

class PhysicsDemo : public BaseTest
{
public:
    CREATE_FUNC(PhysicsDemo);

    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
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
    std::unordered_map<int, Node*> _mouses;
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoClickAdd);

    virtual ~PhysicsDemoClickAdd();
    void onEnter() override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onAcceleration(Acceleration* acc, Event* event);
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoLogoSmash);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoPyramidStack : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoPyramidStack);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoRayCast : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoRayCast);

    PhysicsDemoRayCast();

    void onEnter() override;
    virtual std::string title() const override;
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
    CREATE_FUNC(PhysicsDemoJoints);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoActions : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoActions);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoPump : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoPump);

    void onEnter() override;
    void update(float delta) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
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
    CREATE_FUNC(PhysicsDemoOneWayPlatform);

    void onEnter() override;
    virtual std::string title() const override;
    
    bool onContactBegin(EventCustom* event, const PhysicsContact& contact);
};

class PhysicsDemoSlice : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoSlice);

    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    bool slice(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    void clipPoly(PhysicsShapePolygon* shape, Point normal, float distance);
    
    void onTouchEnded(Touch *touch, Event *event);
    
private:
    int _sliceTag;
};

#endif
#endif
