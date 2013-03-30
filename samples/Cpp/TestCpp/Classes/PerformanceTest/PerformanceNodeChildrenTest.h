#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "PerformanceTest.h"
#include "support/CCProfiling.h"

class NodeChildrenMenuLayer : public PerformBasicLayer
{
public:
    NodeChildrenMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    virtual void showCurrentTest();
};

class NodeChildrenMainScene : public CCScene
{
public:
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual std::string title();
    virtual std::string subtitle();
    virtual void updateQuantityOfNodes() = 0;

    void onDecrease(CCObject* pSender);
    void onIncrease(CCObject* pSender);
    void updateQuantityLabel();

    int getQuantityOfNodes() { return quantityOfNodes; }

protected:
    int    lastRenderedCount;
    int    quantityOfNodes;
    int    currentQuantityOfNodes;
};

class IterateSpriteSheet : public NodeChildrenMainScene
{
public:
    ~IterateSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(float dt) = 0;
    virtual const char* profilerName();

protected:
    CCSpriteBatchNode    *batchNode;
};

class IterateSpriteSheetFastEnum : public IterateSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* profilerName();
};

class IterateSpriteSheetCArray : public IterateSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* profilerName();
};

class AddRemoveSpriteSheet : public NodeChildrenMainScene
{
public:
    ~AddRemoveSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(float dt) = 0;
    virtual const char* profilerName();

protected:
    CCSpriteBatchNode    *batchNode;

#if CC_ENABLE_PROFILERS
    CCProfilingTimer* _profilingTimer;
#endif
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* profilerName();
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* profilerName();
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* profilerName();
};

void runNodeChildrenTest();

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
