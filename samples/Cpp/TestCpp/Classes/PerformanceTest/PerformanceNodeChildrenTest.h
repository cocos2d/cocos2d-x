#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "PerformanceTest.h"
#include "support/CCProfiling.h"

class NodeChildrenMenuLayer : public PerformBasicLayer
{
public:
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
    virtual std::string title();
    virtual std::string subtitle();
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
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class IterateSpriteSheetIterator : public IterateSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class IterateSpriteSheetCArray : public IterateSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
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
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class CallFuncsSpriteSheetCMacro : public IterateSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

///

class AddSprite : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class GetSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class RemoveSprite : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class SortAllChildrenSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

class VisitSceneGraph : public NodeChildrenMainScene
{
public:
    void initWithQuantityOfNodes(unsigned int nodes) override;

    virtual void update(float dt) override;
    void updateQuantityOfNodes() override;
    virtual std::string title() override;
    virtual std::string subtitle() override;
    virtual const char* testName() override;
};

void runNodeChildrenTest();

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
