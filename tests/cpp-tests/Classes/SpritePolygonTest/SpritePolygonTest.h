#ifndef __cocos2d_tests__SpritePolygonTest__

#include "../BaseTest.h"
#include "ui/CocosGUI.h"

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
protected:
    void initTouchDebugDraw();
    cocos2d::Sprite* spp;
    cocos2d::Sprite* sp;
};

class SpritePolygonTest1 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest1);
    SpritePolygonTest1();
    void make2Sprites();
};

class SpritePolygonTest2 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest2);
    SpritePolygonTest2();
    void make2Sprites();
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
    unsigned int _incVert;
    unsigned int _incTri;
    unsigned int _incPix;
};

class SpritePolygonPerformanceTestDynamic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePolygonPerformanceTestDynamic);
    SpritePolygonPerformanceTestDynamic();
protected:
    cocos2d::Sprite* makeSprite();
    cocos2d::PolygonInfo _pinfo;
    void initIncrementStats();
};

class SpritePerformanceTestDynamic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePerformanceTestDynamic);
    SpritePerformanceTestDynamic();
protected:
    cocos2d::Sprite* makeSprite();
    void initIncrementStats();
};

class SpritePolygonTestSlider : public SpritePolygonTestCase
{
public:
    CREATE_FUNC(SpritePolygonTestSlider);
    SpritePolygonTestSlider();
protected:
    cocos2d::Label *_epsilonLabel;
    cocos2d::Sprite* makeSprite(const std::string& filename, const cocos2d::Vec2& pos);
    void makeSprites(const std::string* list, const int count, const float y);
    cocos2d::TTFConfig _ttfConfig;
    void changeEpsilon(Ref *pSender, cocos2d::ui::Slider::EventType type);
    void updateLabel(const cocos2d::Sprite* sp, const cocos2d::PolygonInfo &pinfo);
};

class SpritePolygonTest3 : public SpritePolygonTestSlider
{
public:
    CREATE_FUNC(SpritePolygonTest3);
    SpritePolygonTest3();
};
class SpritePolygonTest4 : public SpritePolygonTestSlider
{
public:
    CREATE_FUNC(SpritePolygonTest4);
    SpritePolygonTest4();
};


#endif /* defined(__cocos2d_tests__SpritePolygonTest__) */
