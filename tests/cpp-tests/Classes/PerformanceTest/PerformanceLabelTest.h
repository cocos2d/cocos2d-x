#ifndef __PERFORMANCE_LABEL_TEST_H__
#define __PERFORMANCE_LABEL_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceLabelTests);

class LabelMainScene : public TestCase
{
public:
    static const  int AUTO_TEST_NODE_NUM  = 20;

    CREATE_FUNC(LabelMainScene);

    virtual ~LabelMainScene();

    std::string title() const;
    virtual bool init() override;
    void updateNodes();

    void onIncrease(cocos2d::Ref* sender);
    void onDecrease(cocos2d::Ref* sender);

    int getSubTestNum() { return 1; }
    int getNodesNum() { return _quantityNodes; }
    
    void  updateAutoTest(float dt);
    void  updateText(float dt);
    void  onAutoTest(cocos2d::Ref* sender);

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void nextTestCallback(cocos2d::Ref* sender) override;
    virtual void priorTestCallback(cocos2d::Ref* sender) override;

    static bool _s_autoTest;
    static int  _s_labelCurCase;

private:
    static const  int MAX_AUTO_TEST_TIMES  = 35;
    static const  int MAX_SUB_TEST_NUMS    = 5;
    static int NODE_TEST_COUNT;

    void  dumpProfilerFPS();
    
    void  endAutoTest();
    void  nextAutoTest();
    void  finishAutoTest();
    
    cocos2d::Layer* _labelContainer;

    int            _lastRenderedCount;
    int            _quantityNodes;
    
    std::vector<float> _vecFPS;
    int            _executeTimes;

    float          _accumulativeTime;
};

#endif
