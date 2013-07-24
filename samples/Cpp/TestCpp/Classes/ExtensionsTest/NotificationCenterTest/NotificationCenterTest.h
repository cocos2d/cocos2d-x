#ifndef __NOTIFICATIONCENTERTEST_H__
#define __NOTIFICATIONCENTERTEST_H__

#include "cocos2d.h"

class NotificationCenterTest : public cc::Layer
{
public:
    NotificationCenterTest();
    void toExtensionsMainLayer(cc::Object* sender);
    void toggleSwitch(cc::Object *sender);
    void connectToSwitch(cc::Object *sender);
    void doNothing(cc::Object *sender);
private:
    bool _showImage;
};

void runNotificationCenterTest();

#endif /* __NOTIFICATIONCENTERTEST_H__ */
