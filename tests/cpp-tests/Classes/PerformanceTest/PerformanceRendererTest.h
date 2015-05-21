//
//  PerformanceRendererTest.h
//  cocos2d_samples
//
//  Created by Huabing on 1/10/14.
//
//

#ifndef __PERFORMANCE_RENDERER_TEST_H__
#define __PERFORMANCE_RENDERER_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceRenderTests);

class RenderPerformceTest : public TestCase
{
public:
    CREATE_FUNC(RenderPerformceTest);
    
    virtual void onEnter() override;
};

#endif
