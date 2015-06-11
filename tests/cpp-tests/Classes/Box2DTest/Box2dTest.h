#ifndef _BOX2D_TEST_H_
#define _BOX2D_TEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(Box2DTests);

class Box2DTest : public TestCase
{
public:
    CREATE_FUNC(Box2DTest);

    virtual bool init() override;

#if CC_ENABLE_BOX2D_INTEGRATION
    Box2DTest();
    ~Box2DTest();

    void initPhysics();
    void createResetButton();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

    void addNewSpriteAtPosition(cocos2d::Vec2 p);
    void update(float dt) override;
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

private:
    cocos2d::Mat4 _modelViewMV;
    void onDraw();
    cocos2d::CustomCommand _customCommand;
    cocos2d::Texture2D* _spriteTexture;
    b2World* world;
#endif
} ;

#endif
