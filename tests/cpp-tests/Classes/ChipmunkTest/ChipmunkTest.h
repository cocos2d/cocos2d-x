//
// cocos2d
//
#ifndef __CHIPMUNKTEST_H__
#define __CHIPMUNKTEST_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "../BaseTest.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class ChipmunkTest : public TestCase
{
public:
    CREATE_FUNC(ChipmunkTest);

    ChipmunkTest();
    ~ChipmunkTest();
    void onEnter() override;
    void initPhysics();
    void createResetButton();
    void reset(Ref* sender);

    void addNewSpriteAtPosition(cocos2d::Vec2 p);
    void update(float dt) override;
    void toggleDebugCallback(Ref* sender);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);
    virtual void onAcceleration(Acceleration* acc, Event* event);

private:
    Texture2D* _spriteTexture; // weak ref
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    PhysicsDebugNode* _debugLayer; // weak ref
#endif
    cpSpace* _space; // strong ref
    cpShape* _walls[4];
};

DEFINE_TEST_SUITE(ChipmunkTests);

#endif /* __CHIPMUNKACCELTOUCHTEST_H__ */
