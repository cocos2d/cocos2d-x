#ifndef __PERFORMANCE_TEST_H__
#define __PERFORMANCE_TEST_H__

#include "../testBasic.h"

class PerformanceMainLayer : public Layer
{
public:
    virtual void onEnter();
    
    bool onTouchBegan(Touch* touches, Event  *event);
    void onTouchMoved(Touch* touches, Event  *event);
    
    void onMouseScroll(Event *event);
protected:
    Point _beginPos;
    Menu* _itemMenu;
};

class PerformBasicLayer : public Layer
{
public:
    PerformBasicLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0);

    virtual void onEnter() override;

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
