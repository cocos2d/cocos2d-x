#ifndef __cocos2d_tests__SpritePolygonTest__
#include "../testBasic.h"
#include "../BaseTest.h"
#include "2d/SpritePolygon.h"
DEFINE_TEST_SUITE(SpritePolygonTest);

class SpritePolygonTestCase : public TestCase
{
protected:
    virtual void onBackCallback(Ref* sender);
    std::string _title;
    std::string _subtitle;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
};

class SpritePolygonTestDemo : public SpritePolygonTestCase
{
public:
    void initDefaultSprite(const std::string &filename, cocos2d::experimental::SpritePolygon *inst);
protected:
    cocos2d::experimental::SpritePolygon* spp;
    cocos2d::Sprite* sp;
    cocos2d::DrawNode *debugForNormalSprite;
};

class SpritePolygonPerformance : public SpritePolygonTestCase
{
public:
    CREATE_FUNC(SpritePolygonPerformance);
    SpritePolygonPerformance();
    virtual void update(float dt);
protected:
    int spriteCount;
    int vertCount;
    int triCount;
    int pixelCount;
    float elapsedTime;
    cocos2d::Label * perfLabel;
    void updateLabel();
    int continuousLowDt;
    float continuousHighDtTime;
    float waitingTime;
    
    int _posX;
    int _posY;
    int _leftX;
    int _rightX;
    bool goRight;
    bool ended;
    
    float prevDt;
    
    virtual Node* makeSprite();
    virtual void incrementStats();
    
    void initIncrementStats();
    int _incVert;
    int _incTri;
    int _incPix;
};

class SpritePolygonPerformanceTestStatic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePolygonPerformanceTestStatic);
    SpritePolygonPerformanceTestStatic();
protected:
    cocos2d::experimental::SpritePolygon* makeSprite();
    void initIncrementStats();
};

class SpritePerformanceTestStatic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePerformanceTestStatic);
    SpritePerformanceTestStatic();
protected:
    cocos2d::Sprite* makeSprite();
    void initIncrementStats();
};

class SpritePolygonPerformanceTestDynamic : public SpritePolygonPerformanceTestStatic
{
public:
    CREATE_FUNC(SpritePolygonPerformanceTestDynamic);
    SpritePolygonPerformanceTestDynamic();
protected:
    cocos2d::experimental::SpritePolygon* makeSprite();
};

class SpritePerformanceTestDynamic : public SpritePerformanceTestStatic
{
public:
    CREATE_FUNC(SpritePerformanceTestDynamic);
    SpritePerformanceTestDynamic();
protected:
    cocos2d::Sprite* makeSprite();
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
