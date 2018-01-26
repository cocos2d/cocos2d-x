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

//
//  PerformanceEventDispatcherTest.h

#ifndef __PERFORMANCE_EVENTDISPATCHER_TEST_H__
#define __PERFORMANCE_EVENTDISPATCHER_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceEventDispatcherTests);

class PerformanceEventDispatcherScene : public TestCase
{
public:
    static const int TAG_TITLE = 100;
    static const int TAG_SUBTITLE = 101;
    
    struct TestFunction
    {
        const char* name;
        std::function<void()> func;
    };
    
    virtual bool init() override;
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void generateTestFunctions() = 0;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void updateQuantityOfNodes();

    void updateStatus();
    void reset();
    void switchTestType(unsigned int index);
    const char* profilerName();
    void updateProfilerName();
    
    // for the profiler
    virtual const char* testName();
    void updateQuantityLabel();
    void dumpProfilerInfo(float dt);
    
    // overrides
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
protected:
    static int quantityOfNodes;

    char   _profilerName[256];
    int    _lastRenderedCount;
    int    _currentQuantityOfNodes;
    unsigned int _type;
    std::vector<TestFunction> _testFunctions;
    std::vector<Node*> _nodes;
    std::vector<cocos2d::EventListener*> _fixedPriorityListeners;
    cocos2d::MenuItemFont* _increase;
    cocos2d::MenuItemFont* _decrease;
    cocos2d::MenuItemFont* _startItem;
    cocos2d::MenuItemFont* _stopItem;
    cocos2d::MenuItemToggle* _toggle;

    int autoTestCountIndex;
};

class TouchEventDispatchingPerfTest : public PerformanceEventDispatcherScene
{
public:
    CREATE_FUNC(TouchEventDispatchingPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class KeyboardEventDispatchingPerfTest : public PerformanceEventDispatcherScene
{
public:
    CREATE_FUNC(KeyboardEventDispatchingPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CustomEventDispatchingPerfTest : public PerformanceEventDispatcherScene
{
public:
    CREATE_FUNC(CustomEventDispatchingPerfTest);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    
private:
    std::vector<cocos2d::EventListener*> _customListeners;
};

#endif /* defined(__PERFORMANCE_EVENTDISPATCHER_TEST_H__) */
