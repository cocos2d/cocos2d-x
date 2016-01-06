#ifndef __PERFORMANCE_LABEL_TEST_H__
#define __PERFORMANCE_LABEL_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceLabelTests);

class LabelMainScene : public TestCase
{
public:
    CREATE_FUNC(LabelMainScene);

    virtual ~LabelMainScene();

    std::string title() const override;
    virtual bool init() override;
    void updateNodes();

    void onIncrease(cocos2d::Ref* sender);
    void onDecrease(cocos2d::Ref* sender);
    void updateText(float dt);

    virtual void onEnter() override;
    virtual void onExit() override;
    void beginStat(float dt);
    void endStat(float dt);
    void doAutoTest();

    virtual void nextTestCallback(cocos2d::Ref* sender) override;
    virtual void priorTestCallback(cocos2d::Ref* sender) override;

private:
    cocos2d::Layer* _labelContainer;

    int   _lastRenderedCount;
    int   _quantityNodes;
    float _accumulativeTime;

    bool  isStating;
    int   autoTestIndex;
    int   statCount;
    float totalStatTime;
    float minFrameRate;
    float maxFrameRate;
};

#endif
