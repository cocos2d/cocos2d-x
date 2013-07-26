#ifndef __PERFORMANCE_TEST_H__
#define __PERFORMANCE_TEST_H__

#include "../testBasic.h"

class PerformanceMainLayer : public Layer
{
public:
    virtual void onEnter();
};

class PerformBasicLayer : public Layer
{
public:
    PerformBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void onEnter();

    virtual void restartCallback(Object* sender);
    virtual void nextCallback(Object* sender);
    virtual void backCallback(Object* sender);
    virtual void showCurrentTest() = 0;

    virtual void toMainLayer(Object* sender);

protected:
    bool _controlMenuVisible;
    int  _maxCases;
    int  _curCase;
};

class PerformanceTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
