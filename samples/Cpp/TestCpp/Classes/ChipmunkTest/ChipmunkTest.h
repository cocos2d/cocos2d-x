//
// cocos2d
//
#ifndef __CHIPMUNKTEST_H__
#define __CHIPMUNKTEST_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "../testBasic.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class ChipmunkTestLayer : public CCLayer
{
public:
    ChipmunkTestLayer();
    ~ChipmunkTestLayer();
    void onEnter();
    void initPhysics();
    void createResetButton();
    void reset(CCObject* sender);

    void addNewSpriteAtPosition(CCPoint p);
    void update(float dt);
    void toggleDebugCallback(CCObject* pSender);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

private:
    CCTexture2D* _spriteTexture; // weak ref
#if CC_ENABLE_CHIPMUNK_INTEGRATION    
    CCPhysicsDebugNode* _debugLayer; // weak ref
#endif
    cpSpace* _space; // strong ref
    cpShape* _walls[4];
};

class ChipmunkAccelTouchTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __CHIPMUNKACCELTOUCHTEST_H__ */
