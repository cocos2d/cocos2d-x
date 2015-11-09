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
