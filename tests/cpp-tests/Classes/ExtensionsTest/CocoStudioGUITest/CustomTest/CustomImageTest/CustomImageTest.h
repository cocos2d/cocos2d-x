

#ifndef __TestCpp__CustomImageScene__
#define __TestCpp__CustomImageScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../../../testBasic.h"

class CustomImageLayer : public cocos2d::Layer
{
public:
    virtual void onEnter();
};

class CustomImageScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__TestCpp__CustomUIScene__) */
