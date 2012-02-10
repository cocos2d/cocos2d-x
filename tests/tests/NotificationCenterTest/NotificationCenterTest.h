#ifndef __NOTIFICATIONCENTERTEST_H__
#define __NOTIFICATIONCENTERTEST_H__

#include "cocos2d.h"
#include "../testBasic.h"
#include "platform/platform.h"

class NotificationCenterTest : public CCLayer
{
public:
    NotificationCenterTest();
    void toggleSwitch(cocos2d::CCObject *sender);
    void connectToSwitch(cocos2d::CCObject *sender);
private:
    bool m_bShowImage;
};

class NotificationCenterTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* __NOTIFICATIONCENTERTEST_H__ */
