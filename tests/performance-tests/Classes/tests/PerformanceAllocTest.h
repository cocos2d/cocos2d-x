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
