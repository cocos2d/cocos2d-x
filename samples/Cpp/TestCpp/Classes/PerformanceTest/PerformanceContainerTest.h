/*
 *
 */
#ifndef __PERFORMANCE_CONTAINER_TEST_H__
#define __PERFORMANCE_CONTAINER_TEST_H__

#include "PerformanceTest.h"
#include "CCProfiling.h"

class ContainerBasicLayer : public PerformBasicLayer
{
public:
    ContainerBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);
    
    virtual void showCurrentTest();
};

class PerformanceContainerScene : public Scene
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
    int getQuantityOfNodes() { return quantityOfNodes; }
    void dumpProfilerInfo(float dt);
    
    // overrides
    virtual void update(float dt) override;
    
protected:
    char   _profilerName[256];
    int    lastRenderedCount;
    int    quantityOfNodes;
    int    currentQuantityOfNodes;
    unsigned int _type;
    std::vector<TestFunction> _testFunctions;
    
    MenuItemFont* _increase;
    MenuItemFont* _decrease;
    MenuItemFont* _startItem;
    MenuItemFont* _stopItem;
    MenuItemToggle* _toggle;
};

class TemplateVectorPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(TemplateVectorPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class ArrayPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(ArrayPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TemplateMapStringKeyPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(TemplateMapStringKeyPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DictionaryStringKeyPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(DictionaryStringKeyPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class TemplateMapIntKeyPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(TemplateMapIntKeyPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class DictionaryIntKeyPerfTest : public PerformanceContainerScene
{
public:
    CREATE_FUNC(DictionaryIntKeyPerfTest);
    
    virtual void generateTestFunctions() override;
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

void runContainerPerformanceTest();

#endif // __PERFORMANCE_CONTAINER_TEST_H__
