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
#ifndef __PERFORMANCE_CONTAINER_TEST_H__
#define __PERFORMANCE_CONTAINER_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceContainerTests);

class PerformanceContainerScene : public TestCase
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
    
    void switchTestType(unsigned int index);
    void updateStatus();
    const char* profilerName();
    void updateProfilerName();
    
    // for the profiler
    virtual const char* testName();
    void updateQuantityLabel();
    int getQuantityOfNodes() { return quantityOfNodes; }
    void dumpProfilerInfo(float dt);
    
    // overrides
    virtual void update(float dt) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
protected:
    static int quantityOfNodes;

    char   _profilerName[256];
    int    lastRenderedCount;
    int    currentQuantityOfNodes;
    unsigned int _type;
    std::vector<TestFunction> _testFunctions;
    std::string _typePrefix;
    
    cocos2d::MenuItemFont* _increase;
    cocos2d::MenuItemFont* _decrease;
    cocos2d::MenuItemFont* _startItem;
    cocos2d::MenuItemFont* _stopItem;
    cocos2d::MenuItemToggle* _toggle;

    int autoTestCountIndex;
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

#endif // __PERFORMANCE_CONTAINER_TEST_H__
