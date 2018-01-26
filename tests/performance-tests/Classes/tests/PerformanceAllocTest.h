/*
 *
 */
#ifndef __PERFORMANCE_ALLOC_TEST_H__
#define __PERFORMANCE_ALLOC_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceAllocTests);

class PerformceAllocScene : public TestCase
{
public:
    virtual bool init() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
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
    PerformceAllocScene();
    char   _profilerName[256];
    int    lastRenderedCount;
    static int quantityOfNodes;
    int    currentQuantityOfNodes;
    int    autoTestIndex;
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

#endif // __PERFORMANCE_ALLOC_TEST_H__
