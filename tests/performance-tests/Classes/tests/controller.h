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

#ifndef _CPPTESTS_CONTROLLER_H__
#define _CPPTESTS_CONTROLLER_H__

#include <condition_variable>
#include <string>
#include <thread>

class TestList;
class TestSuite;
class TestCase;

namespace cocos2d
{
    class Director;
    class Touch;
    class Event;
    class EventListenerTouchOneByOne;
}

class TestController
{
public:
    static TestController* getInstance();
    static void destroyInstance();

    ~TestController();

    void startAutoTest();
    void stopAutoTest();

    void handleCrash();

    void onEnterBackground();
    void onEnterForeground();

    bool blockTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    void setCurrTestSuite(TestSuite* testSuite) { _testSuite = testSuite; }
    TestSuite* getCurrTestSuite() { return _testSuite; }
private:
    TestController();

    void traverseThreadFunc();

    void traverseTestList(TestList* testList);
    void traverseTestSuite(TestSuite* testSuite);
    bool checkTest(TestCase* testCase);

    void logEx(const char * format, ...);

    bool _stopAutoTest;
    bool _isRunInBackground;

    TestList* _rootTestList;
    TestSuite* _testSuite;

    std::thread _autoTestThread;

    std::condition_variable _sleepCondition;
    std::unique_lock<std::mutex>* _sleepUniqueLock;

    cocos2d::Director* _director;

    std::string _logIndentation;
};

#endif
