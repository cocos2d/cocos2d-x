//
//  PerformanceEventDispatcherTest.h

#ifndef __PERFORMANCE_EVENTDISPATCHER_TEST_H__
#define __PERFORMANCE_EVENTDISPATCHER_TEST_H__

#include "PerformanceTest.h"

class EventDispatcherBasicLayer : public PerformBasicLayer
{
public:
    EventDispatcherBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    
    virtual void showCurrentTest();
};

class PerformanceEventDispatcherScene : public Scene
{
public:
    static const int TAG_TITLE = 100;
    static const int TAG_SUBTITLE = 101;
    
    struct TestFunction
    {
        const char* name;
        std::function<void()> func;
    };
    
    virtual void initWithQuantityOfNodes(unsigned int nNodes);
    virtual void generateTestFunctions() = 0;
    
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void updateQuantityOfNodes();
    
    const char* profilerName();
    void updateProfilerName();
    
    // for the profiler
    virtual const char* testName();
    void updateQuantityLabel();
    int getQuantityOfNodes() { return _quantityOfNodes; }
    void dumpProfilerInfo(float dt);
    
    // overrides
    virtual void update(float dt) override;
    
protected:
    char   _profilerName[256];
    int    _lastRenderedCount;
    int    _quantityOfNodes;
    int    _currentQuantityOfNodes;
    unsigned int _type;
    std::vector<TestFunction> _testFunctions;
    std::vector<Node*> _nodes;
    std::vector<EventListener*> _fixedPriorityListeners;
    MenuItemFont* _increase;
    MenuItemFont* _decrease;
    MenuItemFont* _startItem;
    MenuItemFont* _stopItem;
    MenuItemToggle* _toggle;
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
    std::vector<EventListener*> _customListeners;
};

void runEventDispatcherPerformanceTest();

#endif /* defined(__PERFORMANCE_EVENTDISPATCHER_TEST_H__) */
