#ifndef _BOX2D_TEST_H_
#define _BOX2D_TEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../testBasic.h"

class Box2DTestLayer : public Layer
{
    Texture2D* _spriteTexture;    // weak ref
    b2World* world;
//    GLESDebugDraw* _debugDraw;

public:
    Box2DTestLayer();
    ~Box2DTestLayer();

    void initPhysics();
    void createResetButton();
    virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    void addNewSpriteAtPosition(Vec2 p);
    void update(float dt);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event* event);

#if CC_ENABLE_BOX2D_INTEGRATION
protected:
    Mat4 _modelViewMV;
    void onDraw();
    CustomCommand _customCommand;
#endif
} ;

class Box2DTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
