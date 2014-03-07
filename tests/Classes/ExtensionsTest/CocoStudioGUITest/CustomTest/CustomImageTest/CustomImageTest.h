

#ifndef __TestCpp__CustomImageScene__
#define __TestCpp__CustomImageScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../../../testBasic.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CustomImageLayer : public Layer
{
public:
    virtual void onEnter();
};

class CustomImageScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__TestCpp__CustomUIScene__) */
