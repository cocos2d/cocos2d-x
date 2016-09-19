/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 
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
/// @cond DO_NOT_SHOW

#include "platform/CCPlatformMacros.h"
#include "ui/UIWidget.h"
#include "ui/UILayout.h"
#include "ui/UIListView.h"
#include "ui/UILoadingBar.h"
#include "ui/UIPageView.h"
#include "ui/UIRichText.h"

NS_CC_BEGIN

namespace ui {
    
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_ABSOLUTE = Widget::PositionType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::PositionType POSITION_PERCENT = Widget::PositionType::PERCENT;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_ABSOLUTE = Widget::SizeType::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Widget::SizeType SIZE_PERCENT = Widget::SizeType::PERCENT;
CC_DEPRECATED_ATTRIBUTE const Widget::TextureResType UI_TEX_TYPE_LOCAL = Widget::TextureResType::LOCAL;
CC_DEPRECATED_ATTRIBUTE const Widget::TextureResType UI_TEX_TYPE_PLIST = Widget::TextureResType::PLIST;
CC_DEPRECATED_ATTRIBUTE const Widget::BrightStyle BRIGHT_NONE = Widget::BrightStyle::NONE;
CC_DEPRECATED_ATTRIBUTE const Widget::BrightStyle BRIGHT_NORMAL = Widget::BrightStyle::NORMAL;
CC_DEPRECATED_ATTRIBUTE const Widget::BrightStyle BRIGHT_HIGHLIGHT = Widget::BrightStyle::HIGHLIGHT;
CC_DEPRECATED_ATTRIBUTE const Layout::ClippingType LAYOUT_CLIPPING_STENCIL = Layout::ClippingType::STENCIL;
CC_DEPRECATED_ATTRIBUTE const Layout::ClippingType LAYOUT_CLIPPING_SCISSOR = Layout::ClippingType::SCISSOR;
CC_DEPRECATED_ATTRIBUTE const Layout::Type LAYOUT_ABSOLUTE = Layout::Type::ABSOLUTE;
CC_DEPRECATED_ATTRIBUTE const Layout::Type LAYOUT_LINEAR_VERTICAL = Layout::Type::VERTICAL;
CC_DEPRECATED_ATTRIBUTE const Layout::Type LAYOUT_LINEAR_HORIZONTAL = Layout::Type::HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const Layout::Type LAYOUT_RELATIVE = Layout::Type::VERTICAL;
CC_DEPRECATED_ATTRIBUTE const Layout::BackGroundColorType LAYOUT_COLOR_NONE = Layout::BackGroundColorType::NONE;
CC_DEPRECATED_ATTRIBUTE const Layout::BackGroundColorType LAYOUT_COLOR_SOLID = Layout::BackGroundColorType::SOLID;
CC_DEPRECATED_ATTRIBUTE const Layout::BackGroundColorType LAYOUT_COLOR_GRADIENT
                                                        = Layout::BackGroundColorType::GRADIENT;
CC_DEPRECATED_ATTRIBUTE const LayoutParameter::Type LAYOUT_PARAMETER_NONE = LayoutParameter::Type::NONE;
CC_DEPRECATED_ATTRIBUTE const LayoutParameter::Type LAYOUT_PARAMETER_LINEAR = LayoutParameter::Type::LINEAR;
CC_DEPRECATED_ATTRIBUTE const LayoutParameter::Type LAYOUT_PARAMETER_RELATIVE = LayoutParameter::Type::RELATIVE;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_NONE
    = LinearLayoutParameter::LinearGravity::NONE;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_LEFT
    = LinearLayoutParameter::LinearGravity::LEFT;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_TOP
    = LinearLayoutParameter::LinearGravity::TOP;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_RIGHT
    = LinearLayoutParameter::LinearGravity::RIGHT;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_BOTTOM
    = LinearLayoutParameter::LinearGravity::BOTTOM;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_CENTER_VERTICAL
    = LinearLayoutParameter::LinearGravity::CENTER_VERTICAL;
CC_DEPRECATED_ATTRIBUTE const LinearLayoutParameter::LinearGravity LINEAR_GRAVITY_CENTER_HORIZONTAL
    = LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL;
    
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_NONE
    = RelativeLayoutParameter::RelativeAlign::NONE;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_TOP_LEFT
    = RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_TOP_CENTER_HORIZONTAL
    = RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_TOP_RIGHT
    = RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_LEFT_CENTER_VERTICAL
    = RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_CENTER_IN_PARENT
    = RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_RIGHT_CENTER_VERTICAL
    = RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_LEFT_BOTTOM
    = RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_BOTTOM_CENTER_HORIZONTAL
    = RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_ALIGN_PARENT_RIGHT_BOTTOM
    = RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_ABOVE_LEFTALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_LEFTALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_ABOVE_CENTER
    = RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_ABOVE_RIGHTALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_RIGHTALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_LEFT_OF_TOPALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_TOPALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_LEFT_OF_CENTER
    = RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_LEFT_OF_BOTTOMALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_BOTTOMALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_RIGHT_OF_TOPALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_RIGHT_OF_CENTER
    = RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_RIGHT_OF_BOTTOMALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_BOTTOMALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_BELOW_LEFTALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_LEFTALIGN;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_BELOW_CENTER
    = RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER;
CC_DEPRECATED_ATTRIBUTE const RelativeLayoutParameter::RelativeAlign RELATIVE_LOCATION_BELOW_RIGHTALIGN
    = RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_RIGHTALIGN;

CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_LEFT = ListView::Gravity::LEFT;
CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_RIGHT = ListView::Gravity::RIGHT;
CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_CENTER_HORIZONTAL = ListView::Gravity::CENTER_HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_TOP = ListView::Gravity::TOP;
CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_BOTTOM = ListView::Gravity::BOTTOM;
CC_DEPRECATED_ATTRIBUTE const ListView::Gravity LISTVIEW_GRAVITY_CENTER_VERTICAL = ListView::Gravity::CENTER_VERTICAL;
CC_DEPRECATED_ATTRIBUTE const LoadingBar::Direction LoadingBarTypeLeft =  LoadingBar::Direction::LEFT;
CC_DEPRECATED_ATTRIBUTE const LoadingBar::Direction LoadingBarTypeRight =  LoadingBar::Direction::RIGHT;
CC_DEPRECATED_ATTRIBUTE const PageView::TouchDirection PAGEVIEW_TOUCHLEFT =  PageView::TouchDirection::LEFT;
CC_DEPRECATED_ATTRIBUTE const PageView::TouchDirection PAGEVIEW_TOUCHRIGHT =  PageView::TouchDirection::RIGHT;
CC_DEPRECATED_ATTRIBUTE const RichElement::Type RICH_TEXT =  RichElement::Type::TEXT;
CC_DEPRECATED_ATTRIBUTE const RichElement::Type RICH_IMAGE =  RichElement::Type::IMAGE;
CC_DEPRECATED_ATTRIBUTE const RichElement::Type RICH_CUSTOM =  RichElement::Type::CUSTOM;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction SCROLLVIEW_DIR_NONE =  ScrollView::Direction::NONE;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction SCROLLVIEW_DIR_VERTICAL =  ScrollView::Direction::VERTICAL;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction SCROLLVIEW_DIR_HORIZONTAL =  ScrollView::Direction::HORIZONTAL;
CC_DEPRECATED_ATTRIBUTE const ScrollView::Direction SCROLLVIEW_DIR_BOTH =  ScrollView::Direction::BOTH;

    
CC_DEPRECATED_ATTRIBUTE typedef Widget::TextureResType TextureResType;
CC_DEPRECATED_ATTRIBUTE typedef Widget::PositionType   PositionType;
CC_DEPRECATED_ATTRIBUTE typedef Widget::SizeType SizeType;
CC_DEPRECATED_ATTRIBUTE typedef Widget::BrightStyle BrightStyle;
CC_DEPRECATED_ATTRIBUTE typedef Layout::ClippingType LayoutClippingType;
CC_DEPRECATED_ATTRIBUTE typedef Layout::Type LayoutType;
CC_DEPRECATED_ATTRIBUTE typedef Layout::BackGroundColorType LayoutBackGroundColorType;
CC_DEPRECATED_ATTRIBUTE typedef LayoutParameter::Type LayoutParameterType;
CC_DEPRECATED_ATTRIBUTE typedef LinearLayoutParameter::LinearGravity LinearGravity;
CC_DEPRECATED_ATTRIBUTE typedef RelativeLayoutParameter::RelativeAlign RelativeAlign;
CC_DEPRECATED_ATTRIBUTE typedef ListView::Gravity ListViewGravity;
CC_DEPRECATED_ATTRIBUTE typedef LoadingBar::Direction LoadingBarType;
CC_DEPRECATED_ATTRIBUTE typedef PageView::TouchDirection PVTouchDir;
CC_DEPRECATED_ATTRIBUTE typedef RichElement::Type RichElementType;
CC_DEPRECATED_ATTRIBUTE typedef ScrollView::Direction SCROLLVIEW_DIR;
CC_DEPRECATED_ATTRIBUTE extern const Margin MarginZero;


}


NS_CC_END

/// @endcond
#endif
