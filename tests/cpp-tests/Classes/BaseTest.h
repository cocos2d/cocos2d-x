/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef _CPPTESTS_BASETEST_H__
#define _CPPTESTS_BASETEST_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"

class TestSuite;

/**
 * Each test case should inherit from TestCase, and add to a TestSuite object.
 */
class TestCase : public cocos2d::Scene
{
public:
    /** TestCase test type.*/
    enum class Type
    {
        /** For testing whether test case not crash.*/
        ROBUSTNESS,
        /**
         * For check the correctness of regular test cases. 
         * A test case passes only if the actual output equal to the expected output.
         */
        UNIT,
        /** @warning The test type is not achieved.*/
        GRAPHICAL_STATIC,
        /** @note It's mean the test case need test manually.*/
        MANUAL
    };
    TestCase();
    ~TestCase();

    virtual std::string title() const { return ""; }
    virtual std::string subtitle() const { return ""; }

    /** Returns the test type, the default type is Type::ROBUSTNESS.*/
    virtual Type getTestType() const;
    /** Returns the time the test case needs.*/
    virtual float getDuration() const;


    /** Returns the expected output.*/
    virtual std::string getExpectedOutput() const { return ""; }
    /** Returns the actual output.*/
    virtual std::string getActualOutput() const { return ""; }

    /** Callback functions.*/
    virtual void restartTestCallback(cocos2d::Ref* sender);
    virtual void nextTestCallback(cocos2d::Ref* sender);
    virtual void priorTestCallback(cocos2d::Ref* sender);
    virtual void onBackCallback(cocos2d::Ref* sender);

    /**
     * You should NEVER call this method, unless you know what you are doing.
     */
    void setTestSuite(TestSuite* testSuite);
    TestSuite* getTestSuite() const { return _testSuite; }

    /** Returns the run time of test case.*/
    float getRunTime() const { return _runTime; }

    /**
     * You should NEVER call this method, unless you know what you are doing.
     */
    void setTestCaseName(const std::string& name) { _testCaseName = name; }
    std::string getTestCaseName() const { return _testCaseName; }

    virtual void onEnter() override;
CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;

protected:
    cocos2d::MenuItemImage* _priorTestItem;
    cocos2d::MenuItemImage* _restartTestItem;
    cocos2d::MenuItemImage* _nextTestItem;

    cocos2d::Label* _titleLabel;
    cocos2d::Label* _subtitleLabel;

private:
    TestSuite* _testSuite;
    float _runTime;
    std::string _testCaseName;
};

/**
 * A TestBase object stores the following information about a test:
 * - A pointer to the parent test(TestList or TestSuite).
 * - Array of children test names.
 * - A flag to indicate whether the test is a TestList object.
 *
 * @note You should not inherit from TestBase directly.
 */
class TestBase : public cocos2d::Ref
{
public:
    virtual ~TestBase();

    /** Backs up one level. */
    void backsUpOneLevel();

    virtual void runThisTest() {}

    bool isTestList() { return _isTestList; }

    ssize_t getChildTestCount() { return _childTestNames.size(); }

    /**
    * You should NEVER call this method.
    */
    void setTestParent(TestBase* parent) { _parentTest = parent; }
    TestBase* getTestParent() { return _parentTest; }

    void setTestName(const std::string& testName) { _testName = testName; }
    std::string getTestName() const { return _testName; }
protected:
    TestBase();

    std::string _testName;
    TestBase* _parentTest;
    bool _isTestList;
    std::vector<std::string> _childTestNames;
};

class TestController;

/**
* TestSuite correspond to a group of test cases.
* @note Each test case should add to a TestSuite object. 
*/
class TestSuite : public TestBase
{
public:
    void addTestCase(const std::string& testName, std::function<cocos2d::Scene*()> callback);

    virtual void restartCurrTest();
    virtual void enterNextTest();
    virtual void enterPreviousTest();

    int getCurrTestIndex() { return _currTestIndex; }
    virtual void runThisTest() override;

private:
    std::vector<std::function<cocos2d::Scene*()>> _testCallbacks;

    int _currTestIndex;
    friend class TestController;
};

/**
 * An instance of TestList is a means for displaying hierarchical lists of TestSuite.
 */
class TestList : public TestBase, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    TestList();

    void addTest(const std::string& testName, std::function<TestBase*()> callback);

    virtual void runThisTest() override;


    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;

    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override{}
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) override{}

private:
    std::vector<std::function<TestBase*()>> _testCallbacks;
    bool _cellTouchEnabled;
    bool _shouldRestoreTableOffset;
    cocos2d::Vec2 _tableOffset;
    friend class TestController;
};


#define ADD_TEST(__className__) addTest( #__className__, [](){ return new (std::nothrow) __className__;} );

#define ADD_TEST_CASE(__className__) addTestCase( #__className__, [](){ return __className__::create();} );

#define DEFINE_TEST_LIST(__className__) class __className__  : public TestList { public: __className__();}

#define DEFINE_TEST_SUITE(__className__) class __className__  : public TestSuite { public: __className__();}


/**
 * BaseTest is retained for compatibility with older versions.
 * @warning It should soon be removed. 
 */
class BaseTest : public cocos2d::Layer
{
public:
    virtual std::string title() const { return ""; }
    virtual std::string subtitle() const{ return ""; }

    virtual void restartCallback(cocos2d::Ref* sender) {}
    virtual void nextCallback(cocos2d::Ref* sender){}
    virtual void backCallback(cocos2d::Ref* sender){}

    virtual void onEnter() override{}
    virtual void onExit() override{}
};

#endif /* defined(_CPPTESTS_BASETEST_H__) */
