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

#ifndef __PERFORMANCE_MATH_TEST_H__
#define __PERFORMANCE_MATH_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceMathTests);

class PerformanceMathLayer : public TestCase
{
public:
    PerformanceMathLayer()
    : _loopCount(1000)
    , _stepCount(500)
    , _profileName("")
    {
        
    }
    
    virtual void onEnter() override;
    
    virtual std::string title() const override{ return "Math Performance Test"; }
    virtual std::string subtitle() const override{ return "PerformanceMathLayer subTitle"; }
    
    void addLoopCount(cocos2d::Ref* sender);
    void subLoopCount(cocos2d::Ref* sender);
protected:
    virtual void doPerformanceTest(float dt) {};
    
    void dumpProfilerInfo(float dt);
    void updateLoopLabel();
protected:
    int autoTestIndex;
    int _loopCount;
    int _stepCount;
    std::string _profileName;
};

class PerformanceMathLayer1 : public PerformanceMathLayer
{
public:
    CREATE_FUNC(PerformanceMathLayer1);

    PerformanceMathLayer1()
    {
        _profileName = "Mat4*Mat4";
    }
    
    virtual void doPerformanceTest(float dt) override;
    
    virtual std::string subtitle() const override{ return "Mat4 * Mat4"; }
private:
};

class PerformanceMathLayer2 : public PerformanceMathLayer
{
public:
    CREATE_FUNC(PerformanceMathLayer2);

    PerformanceMathLayer2()
    {
        _profileName = "MatTransformVec4";
    }
    
    virtual void doPerformanceTest(float dt) override;
    
    virtual std::string subtitle() const override{ return "Mat4 TransformVec4"; }
    
};

#endif //__PERFORMANCE_MATH_TEST_H__
