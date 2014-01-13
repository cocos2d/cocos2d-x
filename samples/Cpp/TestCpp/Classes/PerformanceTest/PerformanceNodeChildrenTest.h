#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "PerformanceTest.h"
#include "CCProfiling.h"

class NodeChildrenMenuLayer : public PerformBasicLayer
{
public:
    CREATE_FUNC(NodeChildrenMenuLayer);

    NodeChildrenMenuLayer();
    NodeChildrenMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    virtual void showCurrentTest();
    void dumpProfilerInfo(float dt);

    // overrides
    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;
};

class NodeChildrenMainScene : public Scene
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

protected:
    char   _profilerName[256];
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
    virtual const char* testName();

protected:
    SpriteBatchNode    *batchNode;
};

class IterateSpriteSheetForLoop : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetForLoop);

    IterateSpriteSheetForLoop() {}
    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class IterateSpriteSheetIterator : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetIterator);

    IterateSpriteSheetIterator() {}
    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class IterateSpriteSheetForEach : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetForEach);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};


class AddRemoveSpriteSheet : public NodeChildrenMainScene
{
public:
    ~AddRemoveSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(float dt) = 0;
    virtual const char* testName();

protected:
    SpriteBatchNode    *batchNode;

#if CC_ENABLE_PROFILERS
    ProfilingTimer* _profilingTimer;
#endif
};

///

class CallFuncsSpriteSheetForEach : public IterateSpriteSheet
{
public:
    CREATE_FUNC(CallFuncsSpriteSheetForEach);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

///

class AddSprite : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(AddSprite);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(AddSpriteSheet);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class GetSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(GetSpriteSheet);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class RemoveSprite : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(RemoveSprite);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(RemoveSpriteSheet);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(ReorderSpriteSheet);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class SortAllChildrenSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(SortAllChildrenSpriteSheet);

    virtual void update(float dt);

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName();
};

class VisitSceneGraph : public NodeChildrenMainScene
{
public:
    CREATE_FUNC(VisitSceneGraph);

    void initWithQuantityOfNodes(unsigned int nodes) override;

    virtual void update(float dt) override;
    void updateQuantityOfNodes() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName() override;
};

void runNodeChildrenTest();

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
