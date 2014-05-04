//
//  CCEventListenerFocus.h
//  cocos2d_libs
//
//  Created by guanghui on 5/4/14.
//
//

#ifndef __cocos2d_libs__CCEventListenerFocus__
#define __cocos2d_libs__CCEventListenerFocus__

#include "CCEventListener.h"


NS_CC_BEGIN

namespace ui {
    class Widget;
}

class EventListenerFocus : public EventListener
{
public:
    static const std::string LISTENER_ID;
    static EventListenerFocus* create();
    
    virtual ~EventListenerFocus();
    
    /// Overrides
    virtual EventListenerFocus* clone() override;
    virtual bool checkAvailable() override;
    //
    
public:
    std::function<void(ui::Widget*, ui::Widget*)> onFocusChanged;
    
private:
    EventListenerFocus();
    bool init();
    
    
    friend class EventDispatcher;
};



NS_CC_END

#endif /* defined(__cocos2d_libs__CCEventListenerFocus__) */
