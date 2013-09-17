#ifndef _PHYSICS_TEST_H_
#define _PHYSICS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class PhysicsTestLayer : public Layer
{
    Texture2D* _spriteTexture;    // weak ref
    Scene* _scene;
    
public:
    PhysicsTestLayer();
    ~PhysicsTestLayer();

    void createResetButton();
    
    inline void setScene(Scene* scene) { _scene = scene; }
    void toggleDebugCallback(Object* sender);
    void addNewSpriteAtPosition(Point p);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onAcceleration(Acceleration* acc, Event* event) override;
} ;

class PhysicsTestScene : public TestScene
{
public:
    virtual bool initTest() override;
    virtual void runThisTest();
};

#endif
