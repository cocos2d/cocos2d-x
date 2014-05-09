/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef cocos2d_libs_UIDeprecated_h
#define cocos2d_libs_UIDeprecated_h

#include "base/CCPlatformMacros.h"
//#include "ui/UIWidget.h"

NS_CC_BEGIN

namespace ui {

   
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_ABSOLUTE = Widget::PositionType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_PERCENT = Widget::PositionType::PERCENT;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_ABSOLUTE = Widget::SizeType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_PERCENT = Widget::SizeType::PERCENT;
CC_DEPRECATED_ATTRIBUTE const Widget::TextureResType UI_TEX_TYPE_LOCAL = Widget::TextureResType::LOCAL;
CC_DEPRECATED_ATTRIBUTE const Widget::TextureResType UI_TEX_TYPE_PLIST = Widget::TextureResType::PLIST;
    
CC_DEPRECATED_ATTRIBUTE typedef Widget::TextureResType TextureResType;
CC_DEPRECATED_ATTRIBUTE typedef Widget::PositionType   PositionType;
CC_DEPRECATED_ATTRIBUTE typedef Widget::SizeType SizeType;



    

}


NS_CC_END

#endif
