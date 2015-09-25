#pragma once

#include <map>

#include "../BaseTest.h"

#if CC_USE_PHYSICS


DEFINE_TEST_SUITE(PhysicsTests);

class PhysicsDemo : public TestCase
{
public:
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual std::string title() const override;
    
    void toggleDebugCallback(cocos2d::Ref* sender);
    
    cocos2d::Sprite* addGrossiniAtPosition(cocos2d::Vec2 p, float scale = 1.0);
    cocos2d::Sprite* makeBall(cocos2d::Vec2 point, float radius, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    cocos2d::Sprite* makeBox(cocos2d::Vec2 point, cocos2d::Size size, int color = 0, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    cocos2d::Sprite* makeTriangle(cocos2d::Vec2 point, cocos2d::Size size, int color = 0, cocos2d::PhysicsMaterial material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void toggleDebug();
    
protected:
    
    cocos2d::Texture2D* _spriteTexture;
    cocos2d::SpriteBatchNode* _ball;
    std::unordered_map<int, cocos2d::Node*> _mouses;
    bool _debugDraw;
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoLogoSmash);
    
    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoClickAdd);
    
    virtual ~PhysicsDemoClickAdd();
    void onEnter() override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
};

class PhysicsDemoPyramidStack : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoPyramidStack);
    
    void onEnter() override;
    void updateOnce(float delta);
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
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void changeModeCallback(cocos2d::Ref* sender);
    
    bool anyRay(cocos2d::PhysicsWorld& world, const cocos2d::PhysicsRayCastInfo& info, void* data);
    
private:
    float _angle;
    cocos2d::DrawNode* _node;
    int _mode;
};

class PhysicsDemoActions : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoActions);
    
    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoJoints : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoJoints);
    
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
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
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
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

class PhysicsDemoSlice : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoSlice);
    
    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    bool slice(cocos2d::PhysicsWorld& world, const cocos2d::PhysicsRayCastInfo& info, void* data);
    void clipPoly(cocos2d::PhysicsShapePolygon* shape, cocos2d::Vec2 normal, float distance);
    
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    int _sliceTag;
};

class PhysicsDemoBug3988 : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoBug3988);
    
    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PhysicsContactTest : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsContactTest);
    
    void onEnter() override;
    void resetTest();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onDecrease(cocos2d::Ref* sender);
    void onIncrease(cocos2d::Ref* sender);
    
private:
    int _yellowBoxNum;
    int _blueBoxNum;
    int _yellowTriangleNum;
    int _blueTriangleNum;
};

class PhysicsPositionRotationTest : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsPositionRotationTest);
    
    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsSetGravityEnableTest : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsSetGravityEnableTest);
    
    void onEnter() override;
    void onScheduleOnce(float delta);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PhysicsDemoBug5482 : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsDemoBug5482);
    
    void onEnter() override;
    void onExit() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void changeBodyCallback(cocos2d::Ref* sender);
private:
    cocos2d::Sprite* _nodeA;
    cocos2d::Sprite* _nodeB;
    cocos2d::PhysicsBody* _body;
    cocos2d::MenuItemFont* _button;
    bool _bodyInA;
};

class PhysicsFixedUpdate : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsFixedUpdate);
    void onEnter() override;
    void updateStart(float delta);
    void addBall();
    virtual void update(float delta) override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PhysicsTransformTest : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsTransformTest);
    
    void onEnter() override;
    virtual std::string title() const override;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    cocos2d::Sprite* _parentSprite;
    cocos2d::Layer* _rootLayer;
};

class PhysicsIssue9959 : public PhysicsDemo
{
public:
    CREATE_FUNC(PhysicsIssue9959);
    
    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

#endif // #if CC_USE_PHYSICS