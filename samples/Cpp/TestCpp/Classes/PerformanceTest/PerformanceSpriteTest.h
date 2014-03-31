#ifndef __PERFORMANCE_SPRITE_TEST_H__
#define __PERFORMANCE_SPRITE_TEST_H__

#include "PerformanceTest.h"

class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    CCSprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, CCNode* parent);

protected:
    int                    subtestNumber;
    CCNode                 *_parentNode;
};

class SpriteMenuLayer : public PerformBasicLayer
{
public:
    SpriteMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        : PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void showCurrentTest();
};

class SpriteMainScene : public CCScene
{
public:
    virtual ~SpriteMainScene();
    virtual std::string title();

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();

    void testNCallback(CCObject* pSender);
    void onIncrease(CCObject* pSender);
    void onDecrease(CCObject* pSender);

    virtual void doTest(CCSprite* sprite) = 0;

    int getSubTestNum() { return subtestNumber; }
    int getNodesNum() { return quantityNodes; }

protected:
    int            lastRenderedCount;
    int            quantityNodes;
    SubTest        *m_pSubTest;
    int            subtestNumber;
};

class SpritePerformTest1 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest2 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest3 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest4 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest5 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest6 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

class SpritePerformTest7 : public SpriteMainScene
{
public:
    virtual void doTest(CCSprite* sprite);
    virtual std::string title();
};

void runSpriteTest();

#endif
