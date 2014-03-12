//
//  CustomParticleWidgetTest.h
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#ifndef __CustomUI__CustomParticleWidgetTest__
#define __CustomUI__CustomParticleWidgetTest__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../../../testBasic.h"

class CustomParticleWidgetLayer : public cocos2d::Layer
{
public:
    virtual void onEnter();
};

class CustomParticleWidgetScene : public cocos2d::Scene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__CustomUI__CustomParticleWidgetTest__) */
