#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "PerformanceTest.h"

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
    int	lastRenderedCount;
    int	quantityOfNodes;
    int	currentQuantityOfNodes;
};

class IterateSpriteSheet : public NodeChildrenMainScene
{
public:
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(ccTime dt) = 0;

protected:
    CCSpriteBatchNode	*batchNode;
    //CCProfilingTimer    *_profilingTimer;
};

class IterateSpriteSheetFastEnum : public IterateSpriteSheet
{
public:
    virtual void update(ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class IterateSpriteSheetCArray : public IterateSpriteSheet
{
public:
    virtual void update(ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class AddRemoveSpriteSheet : public NodeChildrenMainScene
{
public:
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(ccTime dt) = 0;

protected:
    CCSpriteBatchNode	*batchNode;
    //CCProfilingTimer* _profilingTimer;
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
};

void runNodeChildrenTest();

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
