//
// cocos2d
//
#ifndef __CHIPMUNKACCELTOUCHTEST_H__
#define __CHIPMUNKACCELTOUCHTEST_H__

#include "cocos2d.h"
#include "chipmunk.h"
#include "../testBasic.h"

class ChipmunkAccelTouchTestLayer : public CCLayer
{
public:
    ChipmunkAccelTouchTestLayer();
    ~ChipmunkAccelTouchTestLayer();
    void onEnter();
    void initPhysics();
    void createResetButton();
    void reset(CCObject* sender);

    void addNewSpriteAtPosition(CCPoint p);
    void update(ccTime dt);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    CCTexture2D *spriteTexture_; // weak ref

    cpSpace *space_; // strong ref

    cpShape *walls_[4];
};

class ChipmunkPhysicsSprite : public CCSprite
{
public:
    ChipmunkPhysicsSprite();
    virtual ~ChipmunkPhysicsSprite();
    void setPhysicsBody(cpBody* body);
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
private:
    cpBody *body_;    // strong ref
};

class ChipmunkAccelTouchTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __CHIPMUNKACCELTOUCHTEST_H__ */
