//
//  UIDeprecated.h
//  cocos2d_libs
//
//  Created by guanghui on 5/8/14.
//
//

#ifndef cocos2d_libs_UIDeprecated_h
#define cocos2d_libs_UIDeprecated_h

#include "base/CCPlatformMacros.h"
#include "UIWidget.h"

NS_CC_BEGIN

namespace ui {
   
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_ABSOLUTE = Widget::PositionType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_PERCENT = Widget::PositionType::PERCENT;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_ABSOLUTE = Widget::SizeType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_PERCENT = Widget::SizeType::PERCENT;


}


NS_CC_END

#endif
