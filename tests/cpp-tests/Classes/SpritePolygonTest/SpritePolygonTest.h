#ifndef __cocos2d_tests__SpritePolygonTest__
#include "../testBasic.h"
#include "../BaseTest.h"
#include "2d/SpritePolygon.h"
DEFINE_TEST_SUITE(SpritePolygonTest);

class SpritePolygonTestDemo : public TestCase
{
public:
    void initDefaultSprite(const std::string &filename);
protected:
    std::string    _title;
    cocos2d::experimental::SpritePolygon* inst;
};

class SpritePolygonTest1 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest1);
    SpritePolygonTest1();
    virtual std::string title() const override {return "Create Polygon Sprite";};
    virtual std::string subtitle() const override {return "from a vector of V3F_C4b_T2F";};


};

#endif /* defined(__cocos2d_tests__SpritePolygonTest__) */
