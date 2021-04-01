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
