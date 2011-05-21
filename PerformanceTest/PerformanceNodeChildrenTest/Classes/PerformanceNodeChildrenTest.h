#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "cocos2d.h"
#include "support/CCProfiling.h"

#if ! CC_ENABLE_PROFILERS
#error CC_ENABLE_PROFILERS must be enabled. Edit ccConfig.h
#endif

enum {
    kMaxNodes = 15000,
    kNodesIncrease = 500,
};

class NodeChildrenMainScene : public cocos2d::CCScene
{
public:
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual std::string title();
    virtual std::string subtitle();
    virtual void updateQuantityOfNodes() = 0;

    void onDecrease(cocos2d::CCObject* pSender);
    void onIncrease(cocos2d::CCObject* pSender);
    void updateQuantityLabel();

    void restartCallback(cocos2d::CCObject* pSender);
    void nextCallback(cocos2d::CCObject* pSender);
    void backCallback(cocos2d::CCObject* pSender);
    void showCurrentTest();

    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

protected:
    int	lastRenderedCount;
    int	quantityOfNodes;
    int	currentQuantityOfNodes;
};

class IterateSpriteSheet : public NodeChildrenMainScene
{
public:
    ~IterateSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(cocos2d::ccTime dt) = 0;
    virtual std::string profilerName();

protected:
    cocos2d::CCSpriteBatchNode	*batchNode;
    cocos2d::CCProfilingTimer    *_profilingTimer;
};

class IterateSpriteSheetCArray : public IterateSpriteSheet
{
public:
    virtual void update(cocos2d::ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual std::string profilerName();
};

class AddRemoveSpriteSheet : public NodeChildrenMainScene
{
public:
    ~AddRemoveSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(cocos2d::ccTime dt) = 0;
    virtual std::string profilerName();

protected:
    cocos2d::CCSpriteBatchNode	*batchNode;
    cocos2d::CCProfilingTimer* _profilingTimer;
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(cocos2d::ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual std::string profilerName();
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(cocos2d::ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual std::string profilerName();
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    virtual void update(cocos2d::ccTime dt);

    virtual std::string title();
    virtual std::string subtitle();
    virtual std::string profilerName();
};

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
