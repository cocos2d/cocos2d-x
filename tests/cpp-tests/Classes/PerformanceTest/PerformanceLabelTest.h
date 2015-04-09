#ifndef __PERFORMANCE_LABEL_TEST_H__
#define __PERFORMANCE_LABEL_TEST_H__

#include "PerformanceTest.h"

class LabelMenuLayer : public PerformBasicLayer
{
public:
    LabelMenuLayer(bool controlMenuVisible, int maxCases = 0, int curCase = 0)
        : PerformBasicLayer(controlMenuVisible, maxCases, curCase)
    {
    }

    virtual void restartCallback(cocos2d::Ref* sender) override;
    virtual void nextCallback(cocos2d::Ref* sender) override;
    virtual void backCallback(cocos2d::Ref* sender) override;
    virtual void showCurrentTest() override;
};

class LabelMainScene : public cocos2d::Scene
{
public:
    static const  int AUTO_TEST_NODE_NUM  = 20;

    virtual ~LabelMainScene();

    std::string title() const;
    void initWithSubTest(int nodes);
    void updateNodes();

    void onIncrease(cocos2d::Ref* sender);
    void onDecrease(cocos2d::Ref* sender);

    int getSubTestNum() { return 1; }
    int getNodesNum() { return _quantityNodes; }
    
    void  updateAutoTest(float dt);
    void  updateText(float dt);
    void  onAutoTest(cocos2d::Ref* sender);

    void  autoShowLabelTests(int curCase,int nodes);

    virtual void onEnter() override;
    virtual void onExit() override;

    static bool _s_autoTest;
    static int  _s_labelCurCase;

private:
    static const  int MAX_AUTO_TEST_TIMES  = 35;
    static const  int MAX_SUB_TEST_NUMS    = 5;
    

    void  dumpProfilerFPS();
    
    void  endAutoTest();
    void  nextAutoTest();
    void  finishAutoTest();
    
    cocos2d::Layer*         _labelContainer;
    cocos2d::Label*      _title;

    int            _lastRenderedCount;
    int            _quantityNodes;
    
    std::vector<float> _vecFPS;
    int            _executeTimes;

    float          _accumulativeTime;
};

void runLabelTest();

#endif
