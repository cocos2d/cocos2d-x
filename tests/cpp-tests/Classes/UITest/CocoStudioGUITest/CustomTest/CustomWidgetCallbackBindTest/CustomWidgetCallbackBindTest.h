

#ifndef __cocos2d_tests__CustomWidgetCallbackBindTest__
#define __cocos2d_tests__CustomWidgetCallbackBindTest__

#include "cocos2d.h"
#include "../../../../testBasic.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class CustomWidgetCallbackBindScene : public TestScene, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(cocos2d::Ref* pSender);

    virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName);
    virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
    virtual cocos2d::ui::Widget::ccWidgetEventCallback onLocateEventCallback(const std::string &callBackName);

    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void onClick(cocos2d::Ref* sender);
    void onEvent(cocos2d::Ref* sender, int eventType);
};

#endif /* defined(__cocos2d_tests__CustomWidgetCallbackBindTest__) */
