#ifndef __cocos2d_tests__CustomWidgetCallbackBindTest__
#define __cocos2d_tests__CustomWidgetCallbackBindTest__

#include "../../../../BaseTest.h"

class CustomWidgetCallbackBindScene : public TestCase
{
public:
    CREATE_FUNC(CustomWidgetCallbackBindScene);

    virtual bool init() override;
    virtual std::string title() const override { return getTestCaseName(); }

    virtual void onExit() override;
};

#endif /* defined(__cocos2d_tests__CustomWidgetCallbackBindTest__) */
