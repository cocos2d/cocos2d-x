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
    void update(float dt);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

private:
    CCTexture2D* m_pSpriteTexture; // weak ref
    cpSpace* m_pSpace; // strong ref
    cpShape* m_pWalls[4];
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
    cpBody* m_pBody;    // strong ref
};

class ChipmunkAccelTouchTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __CHIPMUNKACCELTOUCHTEST_H__ */
