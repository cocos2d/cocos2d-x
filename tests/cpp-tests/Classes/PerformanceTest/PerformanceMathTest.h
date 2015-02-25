#ifndef __PERFORMANCE_MATH_TEST_H__
#define __PERFORMANCE_MATH_TEST_H__

#include "PerformanceTest.h"

class PerformanceMathLayer : public PerformBasicLayer
{
public:
    PerformanceMathLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0):
    PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    , _loopCount(1000)
    , _stepCount(500)
    , _profileName("")
    {
        
    }
    
    virtual void onEnter() override;
    virtual void restartCallback(Ref* sender);
    virtual void nextCallback(Ref* sender);
    virtual void backCallback(Ref* sender);
    
    virtual void showCurrentTest() {}
    
    virtual std::string title() const { return "Math Performance Test"; }
    virtual std::string subtitle() const { return "PerformanceMathLayer subTitle"; }
    
    void addLoopCount(Ref* sender);
    void subLoopCount(Ref* sender);
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
    PerformanceMathLayer1(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0):
    PerformanceMathLayer(bControlMenuVisible, nMaxCases, nCurCase)
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
    PerformanceMathLayer2(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0):
    PerformanceMathLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
        _profileName = "profile_MatTransformVec4";
    }
    
    virtual void doPerformanceTest(float dt) override;
    
    virtual std::string subtitle() const { return "Mat4 TransformVec4"; }
    
};

void runMathPerformanceTest();

#endif //__PERFORMANCE_MATH_TEST_H__
