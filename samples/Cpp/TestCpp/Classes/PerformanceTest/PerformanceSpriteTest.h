#ifndef __PERFORMANCE_SPRITE_TEST_H__
#define __PERFORMANCE_SPRITE_TEST_H__

#include "PerformanceTest.h"

class SubTest
{
public:
    ~SubTest();
    void removeByTag(int tag);
    Sprite* createSpriteWithTag(int tag);
    void initWithSubTest(int nSubTest, Node* parent);

protected:
    int                    subtestNumber;
    SpriteBatchNode    *batchNode;
    Node*             parent;
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

class SpriteMainScene : public Scene
{
public:
    virtual ~SpriteMainScene();
    virtual std::string title();

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();

    void testNCallback(Object* pSender);
    void onIncrease(Object* pSender);
    void onDecrease(Object* pSender);

    virtual void doTest(Sprite* sprite) = 0;

    int getSubTestNum() { return subtestNumber; }
    int getNodesNum() { return quantityNodes; }

protected:
    int            lastRenderedCount;
    int            quantityNodes;
    SubTest        *_subTest;
    int            subtestNumber;
};

class SpritePerformTest1 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest2 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest3 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest4 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest5 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest6 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

class SpritePerformTest7 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title();
};

void runSpriteTest();

#endif
