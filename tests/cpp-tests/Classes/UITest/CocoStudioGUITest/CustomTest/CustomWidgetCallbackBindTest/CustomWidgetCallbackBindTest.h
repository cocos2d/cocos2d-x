

#ifndef __cocos2d_tests__CustomWidgetCallbackBindTest__
#define __cocos2d_tests__CustomWidgetCallbackBindTest__

#include "cocos2d.h"
#include "../../../../testBasic.h"

class CustomWidgetCallbackBindScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__cocos2d_tests__CustomWidgetCallbackBindTest__) */
