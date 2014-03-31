

#ifndef __TestCpp__CustomImageScene__
#define __TestCpp__CustomImageScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../../../testBasic.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CustomImageLayer : public CCLayer
{
public:
    virtual void onEnter();
};

class CustomImageScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(CCObject* pSender);
};

#endif /* defined(__TestCpp__CustomUIScene__) */
