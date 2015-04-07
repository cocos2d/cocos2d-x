#ifndef _BOX2D_TEST_H_
#define _BOX2D_TEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(Box2DTests);

class Box2DTest : public TestCase
{
    Texture2D* _spriteTexture;    // weak ref
    b2World* world;
//    GLESDebugDraw* _debugDraw;

public:
    Box2DTest();
    ~Box2DTest();

    void initPhysics();
    void createResetButton();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    void addNewSpriteAtPosition(Vec2 p);
    void update(float dt) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

#if CC_ENABLE_BOX2D_INTEGRATION
protected:
    Mat4 _modelViewMV;
    void onDraw();
    CustomCommand _customCommand;
#endif
} ;

#endif
