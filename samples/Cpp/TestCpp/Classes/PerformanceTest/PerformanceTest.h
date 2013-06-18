#ifndef __PERFORMANCE_TEST_H__
#define __PERFORMANCE_TEST_H__

#include "../testBasic.h"

class PerformanceMainLayer : public CCLayer
{
public:
    virtual void onEnter();
};

class PerformBasicLayer : public CCLayer
{
public:
    PerformBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void onEnter();

    virtual void restartCallback(CCObject* pSender);
    virtual void nextCallback(CCObject* pSender);
    virtual void backCallback(CCObject* pSender);
    virtual void showCurrentTest() = 0;

    virtual void toMainLayer(CCObject* pSender);

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
