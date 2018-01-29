/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __cocos2d_tests__SpritePolygonTest__

#include "../BaseTest.h"
#include "ui/CocosGUI.h"

DEFINE_TEST_SUITE(SpritePolygonTest);

class SpritePolygonTestCase : public TestCase
{
protected:
    std::string _title;
    std::string _subtitle;
    bool _isDebugDraw;
    bool _isNeedDebugMenu;
    cocos2d::Vector<cocos2d::DrawNode* > _drawNodes;
    virtual std::string title() const override {return _title;};
    virtual std::string subtitle() const override {return _subtitle;};
    virtual bool init() override;
    virtual void onEnter()override;
    virtual void onExit()override;
    SpritePolygonTestCase();
    ~SpritePolygonTestCase();
    void updateDrawNode();
};

class SpritePolygonTestDemo : public SpritePolygonTestCase
{
protected:
    cocos2d::Sprite* _polygonSprite;
    cocos2d::Sprite* _normalSprite;
    virtual bool init() override;
    virtual void initSprites(){};
    void initTouches();
};

class SpritePolygonTest1 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest1);
    SpritePolygonTest1();
    void initSprites() override;
};

class SpritePolygonTest2 : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTest2);
    SpritePolygonTest2();
    virtual void initSprites() override;
};

class SpritePolygonTestSlider : public SpritePolygonTestCase
{
protected:
    cocos2d::Label *_epsilonLabel;
    int _tagIndex;
    cocos2d::Sprite* makeSprite(const std::string& filename, const cocos2d::Vec2& pos);
    virtual bool init() override;
    void initSliders();
    virtual void initSprites(){};
    void makeSprites(const std::string* list, const int count, const float y);
    void changeEpsilon(Ref *pSender, cocos2d::ui::Slider::EventType type);
    void updateLabel(const cocos2d::Sprite* sp, const cocos2d::PolygonInfo &pinfo);
};

class SpritePolygonTest3 : public SpritePolygonTestSlider
{
public:
    CREATE_FUNC(SpritePolygonTest3);
    SpritePolygonTest3();
    void initSprites() override;
};

class SpritePolygonTest4 : public SpritePolygonTestSlider
{
public:
    CREATE_FUNC(SpritePolygonTest4);
    SpritePolygonTest4();
    void initSprites() override;
};

class SpritePolygonTest5 : public SpritePolygonTestCase
{
public:
    CREATE_FUNC(SpritePolygonTest5);
    SpritePolygonTest5();
protected:
    virtual bool init() override;
    void initTouch();
    void loadDefaultSprites();
    void addSpritePolygon(const cocos2d::Vec2& pos);
    void update(float dt)override;
private:
    cocos2d::PolygonInfo _polygonInfo;
    int _tagIndex;
};

class SpritePolygonPerformance : public SpritePolygonTestCase
{
public:
    CREATE_FUNC(SpritePolygonPerformance);
    SpritePolygonPerformance();
protected:
    int _spriteCount;
    int _vertCount;
    int _triCount;
    int _pixelCount;
    float _elapsedTime;
    cocos2d::Label * _perfLabel;
    int _continuousLowDt;
    float _continuousHighDtTime;
    float _waitingTime;

    int _posX;
    int _posY;
    int _leftX;
    int _rightX;
    bool goRight;
    bool ended;
    
    float prevDt;
    
    unsigned int _incVert;
    unsigned int _incTri;
    unsigned int _incPix;

    void updateLabel();
    virtual void update(float dt)override;
    virtual bool init() override;
    virtual Node* makeSprite();
    void incrementStats();
    virtual void initIncrementStats(){};
};

class SpritePolygonPerformanceTestDynamic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePolygonPerformanceTestDynamic);
    SpritePolygonPerformanceTestDynamic();
protected:
    cocos2d::Sprite* makeSprite() override;
    cocos2d::PolygonInfo _pinfo;
    virtual void initIncrementStats() override;
};

class SpritePerformanceTestDynamic : public SpritePolygonPerformance
{
public:
    CREATE_FUNC(SpritePerformanceTestDynamic);
    SpritePerformanceTestDynamic();
protected:
    virtual cocos2d::Sprite* makeSprite() override;
    virtual void initIncrementStats() override;
};

class SpritePolygonTestNoCrash : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTestNoCrash);
    SpritePolygonTestNoCrash();
    virtual void initSprites() override;
};

class SpritePolygonTestTPIsland : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTestTPIsland);
    SpritePolygonTestTPIsland();
    virtual void initSprites() override;
};

class SpritePolygonTestAutoPolyIsland : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTestAutoPolyIsland);
    SpritePolygonTestAutoPolyIsland();
    virtual void initSprites() override;
};

class SpritePolygonTestFrameAnim : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(SpritePolygonTestFrameAnim);
    SpritePolygonTestFrameAnim();
    virtual void initSprites() override;
};

class Issue14017Test : public SpritePolygonTestDemo
{
public:
    CREATE_FUNC(Issue14017Test);
    Issue14017Test();
    virtual void initSprites() override;
};

#endif /* defined(__cocos2d_tests__SpritePolygonTest__) */
