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
//  PerformanceCallbackTest.h

#ifndef __PERFORMANCE_CALLBACK_TEST_H__
#define __PERFORMANCE_CALLBACK_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceCallbackTests);

class PerformanceCallbackScene : public TestCase
{
public:
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) {};
    
    void dumpProfilerInfo(float dt);
protected:
    
    std::string _profileName;
    int _placeHolder; // To avoid compiler optimization
    static const int LOOP_COUNT = 10000;
};

class SimulateNewSchedulerCallbackPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(SimulateNewSchedulerCallbackPerfTest);
    
    // overrides
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 100; };
    
    void simulateSchedulePerFrame(const std::function<void(float)>& callback)
    {
        _callback = callback;
    }
    
    template <class T>
    void simulateScheduleUpdate(T* target)
    {
        target->simulateSchedulePerFrame([target](float dt){
            target->update(dt);
        });
    }
    
private:
    std::function<void(float)> _callback;
};


// InvokeMemberFunctionPerfTest
class InvokeMemberFunctionPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(InvokeMemberFunctionPerfTest);
    
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 200; };
    
private:
    cocos2d::Node* _target;
    cocos2d::SEL_SCHEDULE _selector;
};

// InvokeStdFunctionPerfTest
class InvokeStdFunctionPerfTest : public PerformanceCallbackScene
{
public:
    CREATE_FUNC(InvokeStdFunctionPerfTest);
    
    // overrides
    virtual void onEnter() override;
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    virtual void onUpdate(float dt) override;
    
    virtual void update(float dt) override { _placeHolder = 100; };
private:
    std::function<void(float)> _callback;
};

#endif /* __PERFORMANCE_CALLBACK_TEST_H__ */
