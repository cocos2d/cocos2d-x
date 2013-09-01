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
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

class NodeChildrenMainScene : public CCScene
{
public:
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual std::string title();
    virtual std::string subtitle();
    virtual void updateQuantityOfNodes() = 0;
    virtual const char* testName() = 0;
    const char * profilerName();
    void updateProfilerName();
    
    void onDecrease(CCObject* pSender);
    void onIncrease(CCObject* pSender);
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
    CCSpriteBatchNode    *batchNode;
};

class IterateSpriteSheetFastEnum : public IterateSpriteSheet
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

class CallFuncsSpriteSheetCMacro : public IterateSpriteSheet
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
    CCSpriteBatchNode    *batchNode;

#if CC_ENABLE_PROFILERS
    CCProfilingTimer* _profilingTimer;
#endif
};

class GetSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(float dt);
    
    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

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
    void initWithQuantityOfNodes(unsigned int nodes);

    virtual void update(float dt);
    void updateQuantityOfNodes();
    virtual std::string title();
    virtual std::string subtitle();
    virtual const char* testName();
};

void runNodeChildrenTest();

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
