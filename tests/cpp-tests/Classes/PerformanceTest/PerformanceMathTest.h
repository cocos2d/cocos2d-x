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
    
    virtual std::string title() const { return "Math Performance Test"; }
    virtual std::string subtitle() const { return "PerformanceMathLayer subTitle"; }
    
    void addLoopCount(cocos2d::Ref* sender);
    void subLoopCount(cocos2d::Ref* sender);
protected:
    virtual void doPerformanceTest(float dt) {};
    
    void dumpProfilerInfo(float dt);
    void updateLoopLabel();
protected:
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
        _profileName = "profile_Mat4*Mat4";
    }
    
    virtual void doPerformanceTest(float dt) override;
    
    virtual std::string subtitle() const { return "Mat4 * Mat4"; }
private:
};

class PerformanceMathLayer2 : public PerformanceMathLayer
{
public:
    CREATE_FUNC(PerformanceMathLayer2);

    PerformanceMathLayer2()
    {
        _profileName = "profile_MatTransformVec4";
    }
    
    virtual void doPerformanceTest(float dt) override;
    
    virtual std::string subtitle() const { return "Mat4 TransformVec4"; }
    
};

#endif //__PERFORMANCE_MATH_TEST_H__
