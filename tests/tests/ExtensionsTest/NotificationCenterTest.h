#ifndef __NOTIFICATIONCENTERTEST_H__
#define __NOTIFICATIONCENTERTEST_H__

#include "cocos2d.h"
#include "ExtensionsTest.h"

class NotificationCenterTest : public cocos2d::CCLayer
{
public:
    NotificationCenterTest();
    void toExtensionsMainLayer(cocos2d::CCObject* sender);
    void toggleSwitch(cocos2d::CCObject *sender);
    void connectToSwitch(cocos2d::CCObject *sender);
private:
    bool m_bShowImage;
};

void runNotificationCenterTest();

#endif /* __NOTIFICATIONCENTERTEST_H__ */
