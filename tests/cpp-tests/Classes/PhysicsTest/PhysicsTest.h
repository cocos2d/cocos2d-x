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
};

#if CC_USE_PHYSICS == 0
class PhysicsDemoDisabled : public BaseTest
{
public:
    CREATE_FUNC(PhysicsDemoDisabled);
    
    virtual void onEnter() override;
};
#else

#define CREATE_WITH_PHYSICS_FUNC(__TYPE__) \
static __TYPE__* createWithPhysics() \
{ \
__TYPE__ *ret = new __TYPE__(); \
if (ret && ret->initWithPhysics()) \
{ \
ret->autorelease(); \
return ret; \
} \
else \
{ \
delete ret; \
ret = nullptr; \
return nullptr; \
} \
}
class PhysicsDemo : public BaseTest
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemo);
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
    void toggleDebugCallback(Ref* sender);
    
    Sprite* addGrossiniAtPosition(Vector2 p, float scale = 1.0);
    Sprite* makeBall(Vector2 point, float radius, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    Sprite* makeBox(Vector2 point, Size size, int color = 0, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    Sprite* makeTriangle(Vector2 point, Size size, int color = 0, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void toggleDebug();
    inline void setRoot(bool isRoot) { _isRoot = isRoot; }
    
protected:
    Texture2D* _spriteTexture;    // weak ref
    SpriteBatchNode* _ball;
    std::unordered_map<int, Node*> _mouses;
    
private:
    bool _debugDraw;
    bool _isRoot;
};

class PhysicsDemoClickAdd : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoClickAdd);

    virtual ~PhysicsDemoClickAdd();
    void onEnter() override;
    virtual std::string subtitle() const override;
    
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    void onAcceleration(Acceleration* acc, Event* event);
};

class PhysicsDemoLogoSmash : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoLogoSmash);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoPyramidStack : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoPyramidStack);

    void onEnter() override;
    void updateOnce(float delta);
    virtual std::string title() const override;
};

class PhysicsDemoRayCast : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoRayCast);

    PhysicsDemoRayCast();

    void onEnter() override;
    virtual std::string title() const override;
    void update(float delta) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    
    void changeModeCallback(Ref* sender);
    
    bool anyRay(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    
private:
    float _angle;
    DrawNode* _node;
    int _mode;
};

class PhysicsDemoJoints : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoJoints);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoActions : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoActions);

    void onEnter() override;
    virtual std::string title() const override;
};

class PhysicsDemoPump : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoPump);

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
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoOneWayPlatform);

    void onEnter() override;
    virtual std::string title() const override;
    
    bool onContactBegin(PhysicsContact& contact);
};

class PhysicsDemoSlice : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoSlice);

    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    bool slice(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);
    void clipPoly(PhysicsShapePolygon* shape, Vector2 normal, float distance);
    
    void onTouchEnded(Touch *touch, Event *event);
    
private:
    int _sliceTag;
};

class PhysicsDemoBug3988 : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsDemoBug3988);

    void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class PhysicsContactTest : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsContactTest);
    
    void onEnter() override;
    void resetTest();
    bool onContactBegin(PhysicsContact& contact);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
    void onDecrease(Ref* sender);
    void onIncrease(Ref* sender);
    
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
    virtual std::string subtitle() const override;
};

class PhysicsSetGravityEnableTest : public PhysicsDemo
{
public:
    CREATE_WITH_PHYSICS_FUNC(PhysicsSetGravityEnableTest);
    
    void onEnter() override;
    void onScheduleOnce(float delta);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


#endif
#endif
