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

    virtual void restartCallback(Object* sender);
    virtual void nextCallback(Object* sender);
    virtual void backCallback(Object* sender);
    virtual void showCurrentTest();
};

class SpriteMainScene : public Scene
{
public:
    virtual ~SpriteMainScene();
    virtual std::string title() const;

    void initWithSubTest(int nSubTest, int nNodes);
    void updateNodes();

    void testNCallback(Object* sender);
    void onIncrease(Object* sender);
    void onDecrease(Object* sender);

    virtual void doTest(Sprite* sprite) = 0;

    int getSubTestNum() { return subtestNumber; }
    int getNodesNum() { return quantityNodes; }
    
    virtual void onEnter();
    virtual void onExit();
    void  updateAutoTest(float dt);
    void  onAutoTest(Object* sender);
private:
    void  dumpProfilerFPS();
    void  beginAutoTest();
    void  endAutoTest();
    void  nextAutoTest();
    void  finishAutoTest();
    void  autoShowSpriteTests(int curCase, int subTest,int nodes);
public:
    static bool _s_autoTest;
    static int  _s_nSpriteCurCase;
protected:
    int            lastRenderedCount;
    int            quantityNodes;
    SubTest        *_subTest;
    int            subtestNumber;
    std::vector<float> _vecFPS;
    int            _executeTimes;
    static const  int MAX_AUTO_TEST_TIMES  = 25;
    static const  int MAX_SPRITE_TEST_CASE = 7;
    static const  int MAX_SUB_TEST_NUMS    = 9;
    static const  int AUTO_TEST_NODE_NUM1  = 500;
    static const  int AUTO_TEST_NODE_NUM2  = 1500;
};

class SpritePerformTest1 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest2 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest3 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest4 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest5 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest6 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

class SpritePerformTest7 : public SpriteMainScene
{
public:
    virtual void doTest(Sprite* sprite);
    virtual std::string title() const override;
};

void runSpriteTest();

#endif
