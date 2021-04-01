/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __PERFORMANCE_NODE_CHILDREN_TEST_H__
#define __PERFORMANCE_NODE_CHILDREN_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceNodeChildrenTests);

class NodeChildrenMainScene : public TestCase
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

    void dumpProfilerInfo(float dt);

    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;
protected:
    NodeChildrenMainScene();
    static int quantityOfNodes;
    char   _profilerName[256];
    int    lastRenderedCount;
    int    currentQuantityOfNodes;
    int    autoTestIndex;
};

class IterateSpriteSheet : public NodeChildrenMainScene
{
public:
    virtual ~IterateSpriteSheet();
    virtual void updateQuantityOfNodes();
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void update(float dt) = 0;
    virtual const char* testName();

protected:
    cocos2d::SpriteBatchNode    *batchNode;
};

class IterateSpriteSheetForLoop : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetForLoop);

    IterateSpriteSheetForLoop() {}
    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName() override;
};

class IterateSpriteSheetIterator : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetIterator);

    IterateSpriteSheetIterator() {}
    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class IterateSpriteSheetForEach : public IterateSpriteSheet
{
public:
    CREATE_FUNC(IterateSpriteSheetForEach);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};


class AddRemoveSpriteSheet : public NodeChildrenMainScene
{
public:
    virtual ~AddRemoveSpriteSheet();
    virtual void updateQuantityOfNodes()override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes)override;
    virtual void update(float dt)override = 0 ;
    virtual const char* testName()override;

protected:
    cocos2d::SpriteBatchNode    *batchNode;

#if CC_ENABLE_PROFILERS
    ProfilingTimer* _profilingTimer;
#endif
};

///

class CallFuncsSpriteSheetForEach : public IterateSpriteSheet
{
public:
    CREATE_FUNC(CallFuncsSpriteSheetForEach);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

///

class AddSprite : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(AddSprite);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class AddSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(AddSpriteSheet);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class GetSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(GetSpriteSheet);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class RemoveSprite : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(RemoveSprite);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class RemoveSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(RemoveSpriteSheet);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class ReorderSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(ReorderSpriteSheet);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
};

class SortAllChildrenSpriteSheet : public AddRemoveSpriteSheet
{
public:
    CREATE_FUNC(SortAllChildrenSpriteSheet);

    virtual void update(float dt) override;

    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual const char* testName()override;
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

#endif // __PERFORMANCE_NODE_CHILDREN_TEST_H__
