#ifndef __NOTIFICATIONCENTERTEST_H__
#define __NOTIFICATIONCENTERTEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(NotificationCenterTests);

class NotificationCenterTest : public TestCase
{
public:
    CREATE_FUNC(NotificationCenterTest);

    NotificationCenterTest();
    ~NotificationCenterTest();
    
    void toggleSwitch(cocos2d::Ref *sender);
    void connectToSwitch(cocos2d::Ref *sender);
    void doNothing(cocos2d::Ref *sender);
};

#endif /* __NOTIFICATIONCENTERTEST_H__ */
