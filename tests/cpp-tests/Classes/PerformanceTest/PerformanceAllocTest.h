/*
 *
 */
#ifndef __PERFORMANCE_ALLOC_TEST_H__
#define __PERFORMANCE_ALLOC_TEST_H__

#include "PerformanceTest.h"

class AllocBasicLayer : public PerformBasicLayer
{
public:
    AllocBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void showCurrentTest();
};

class PerformceAllocScene : public Scene
{
public:
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void updateQuantityOfNodes() = 0;

    const char* profilerName();
    void updateProfilerName();

    // for the profiler
    virtual const char* testName() = 0;

    void updateQuantityLabel();

    int getQuantityOfNodes() { return quantityOfNodes; }

    void dumpProfilerInfo(float dt);

    // overrides
    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;

protected:
    char   _profilerName[256];
    int    lastRenderedCount;
    int    quantityOfNodes;
    int    currentQuantityOfNodes;
};

class NodeCreateTest : public PerformceAllocScene
{
public:
    CREATE_FUNC(NodeCreateTest);

    virtual void updateQuantityOfNodes() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes) override;
    virtual void update(float dt) override;
    virtual const char* testName() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class NodeDeallocTest : public PerformceAllocScene
{
public:
    CREATE_FUNC(NodeDeallocTest);

    virtual void updateQuantityOfNodes() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes) override;
    virtual void update(float dt) override;
    virtual const char* testName() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteCreateEmptyTest : public PerformceAllocScene
{
public:
    CREATE_FUNC(SpriteCreateEmptyTest);

    virtual void updateQuantityOfNodes() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes) override;
    virtual void update(float dt) override;
    virtual const char* testName() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteCreateTest : public PerformceAllocScene
{
public:
    CREATE_FUNC(SpriteCreateTest);

    virtual void updateQuantityOfNodes() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes) override;
    virtual void update(float dt) override;
    virtual const char* testName() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class SpriteDeallocTest : public PerformceAllocScene
{
public:
    CREATE_FUNC(SpriteDeallocTest);

    virtual void updateQuantityOfNodes() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes) override;
    virtual void update(float dt) override;
    virtual const char* testName() override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


void runAllocPerformanceTest();

#endif // __PERFORMANCE_ALLOC_TEST_H__
