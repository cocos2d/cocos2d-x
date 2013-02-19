#ifndef _BOX2D_TEST_H_
#define _BOX2D_TEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../testBasic.h"

class PhysicsSprite : public CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

class Box2DTestLayer : public CCLayer
{
    CCTexture2D* m_pSpriteTexture;    // weak ref
    b2World* world;
//    GLESDebugDraw* m_debugDraw;

public:
    Box2DTestLayer();
    ~Box2DTestLayer();

    void initPhysics();
    void createResetButton();
    void reset(CCObject* sender);
    virtual void draw();

    void addNewSpriteAtPosition(CCPoint p);
    void update(float dt);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);

    //CREATE_NODE(Box2DTestLayer);
} ;

class Box2DTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
