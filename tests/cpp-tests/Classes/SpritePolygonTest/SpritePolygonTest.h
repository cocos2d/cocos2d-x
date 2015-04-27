#ifndef __cocos2d_tests__SpritePolygonTest__
#include "../testBasic.h"
#include "../BaseTest.h"
#include "2d/SpritePolygon.h"
DEFINE_TEST_SUITE(SpritePolygonTest);

class SpritePolygonTestDemo : public TestCase
{
public:
    void initDefaultSprite(const std::string &filename, cocos2d::experimental::SpritePolygon *inst);
protected:
    cocos2d::experimental::SpritePolygon* spp;
    cocos2d::Sprite* sp;
    cocos2d::DrawNode *debugForNormalSprite;
    virtual void onBackCallback(Ref* sender);
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
};

class SpritePolygonTest1 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest1);
    SpritePolygonTest1();
};

class SpritePolygonTest2 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest2);
    SpritePolygonTest2();
};

class SpritePolygonTest3 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest3);
    SpritePolygonTest3();
};

class SpritePolygonTest4 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest4);
    SpritePolygonTest4();
};

#endif /* defined(__cocos2d_tests__SpritePolygonTest__) */
