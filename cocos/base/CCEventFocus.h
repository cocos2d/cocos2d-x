//
//  CCEventFocus.h
//  cocos2d_libs
//
//  Created by guanghui on 5/4/14.
//
//

#ifndef __cocos2d_libs__CCEventFocus__
#define __cocos2d_libs__CCEventFocus__

#include "CCEvent.h"


NS_CC_BEGIN

namespace ui {
    class Widget;
}

class EventFocus : public Event
{
public:
    EventFocus(ui::Widget* widgetLoseFocus, ui::Widget* widgetGetFocus);
    
private:
    ui::Widget *_widgetGetFocus;
    ui::Widget *_widgetLoseFocus;
    
    friend class EventListenerFocus;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCEventFocus__) */
