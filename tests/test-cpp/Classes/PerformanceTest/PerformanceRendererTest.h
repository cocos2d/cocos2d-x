//
//  PerformanceRendererTest.h
//  cocos2d_samples
//
//  Created by Huabing on 1/10/14.
//
//

#ifndef __PERFORMANCE_RENDERER_TEST_H__
#define __PERFORMANCE_RENDERER_TEST_H__

#include "PerformanceTest.h"

class RenderTestLayer : public PerformBasicLayer
{
    
public:
    RenderTestLayer();
    virtual ~RenderTestLayer();
    
    virtual void onEnter() override;
    virtual void showCurrentTest() override;
public:
    static Scene* scene();
};

void runRendererTest();
#endif
