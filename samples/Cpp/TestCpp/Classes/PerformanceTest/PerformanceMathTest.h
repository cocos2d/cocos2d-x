/*
 *
 */
#ifndef __PERFORMANCE_MATH_TEST_H__
#define __PERFORMANCE_MATH_TEST_H__

#include "PerformanceTest.h"
#include "CCProfiling.h"

class MathBasicLayer : public PerformBasicLayer
{
public:
    MathBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void showCurrentTest();
};

class PerformceMathScene : public Scene
{
public:
    virtual void initPerformanceScene();
    virtual std::string title();
    virtual std::string subtitle();
    

    const char* profilerName();
    void updateProfilerName();

    // for the profiler
    virtual const char* testName() = 0;

    void updateTestLabel();

    void dumpProfilerInfo(float dt);

    // overrides
    virtual void onExitTransitionDidStart() override;
    virtual void onEnterTransitionDidFinish() override;

protected:
    char   _profilerName[256];
    int    lastRenderedCount;
    
};

class MatMultiplyTest : public PerformceMathScene
{
public:
    virtual void initPerformanceScene();
    virtual void update(float dt);
    virtual const char* testName();
    
    CREATE_FUNC(MatMultiplyTest);

    std::string title();
    std::string subtitle();
};

class MatVec4MultiplyTest : public PerformceMathScene
{
public:
    virtual void initPerformanceScene();
    virtual void update(float dt);
    virtual const char* testName();
    
    CREATE_FUNC(MatVec4MultiplyTest);
    
    std::string title();
    std::string subtitle();
};

class Vec3CrossTest : public PerformceMathScene
{
public:
    virtual void initPerformanceScene();
    virtual void update(float dt);
    virtual const char* testName();
    
    CREATE_FUNC(Vec3CrossTest);
    
    std::string title();
    std::string subtitle();
};

class Mat4AddTest : public PerformceMathScene
{
public:
    virtual void initPerformanceScene();
    virtual void update(float dt);
    virtual const char* testName();
    
    CREATE_FUNC(Mat4AddTest);
    
    std::string title();
    std::string subtitle();
};

class Vec4AddTest : public PerformceMathScene
{
public:
    virtual void initPerformanceScene();
    virtual void update(float dt);
    virtual const char* testName();
    
    CREATE_FUNC(Vec4AddTest);
    
    std::string title();
    std::string subtitle();
};


void runMathPerformanceTest();

#endif // __PERFORMANCE_MATH_TEST_H__
