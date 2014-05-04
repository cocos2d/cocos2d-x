//
//  CCEventFocus.cpp
//  cocos2d_libs
//
//  Created by guanghui on 5/4/14.
//
//

#include "CCEventFocus.h"

NS_CC_BEGIN


EventFocus::EventFocus(ui::Widget *widgetLoseFocus, ui::Widget* widgetGetFocus)
:Event(Type::FOCUS),
_widgetLoseFocus(widgetLoseFocus),
_widgetGetFocus(widgetGetFocus)
{
    
}




NS_CC_END