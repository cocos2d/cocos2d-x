/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __UILAYOUTDEFINE_H__
#define __UILAYOUTDEFINE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class UIMargin
{
public:
    float left;
    float top;
    float right;
    float bottom;
    
public:
    UIMargin();
    UIMargin(float l, float t, float r, float b);
    UIMargin(const UIMargin& other);
    UIMargin& operator= (const UIMargin& other);
    void setMargin(float l, float t, float r, float b);
    bool equals(const UIMargin& target) const;
};


typedef enum
{
    LINEAR_GRAVITY_NONE,
    LINEAR_GRAVITY_LEFT,
    LINEAR_GRAVITY_TOP,
    LINEAR_GRAVITY_RIGHT,
    LINEAR_GRAVITY_BOTTOM,
    LINEAR_GRAVITY_CENTER_VERTICAL,
    LINEAR_GRAVITY_CENTER_HORIZONTAL
}UILinearGravity;

typedef enum
{
    RELATIVE_ALIGN_PARENT_NONE,
    RELATIVE_ALIGN_PARENT_LEFT,
    RELATIVE_ALIGN_PARENT_TOP,
    RELATIVE_ALIGN_PARENT_RIGHT,
    RELATIVE_ALIGN_PARENT_BOTTOM,
    RELATIVE_CENTER_IN_PARENT,
    RELATIVE_CENTER_HORIZONTAL,
    RELATIVE_CENTER_VERTICAL,
    RELATIVE_LOCATION_LEFT_OF,
    RELATIVE_LOCATION_RIGHT_OF,
    RELATIVE_LOCATION_ABOVE,
    RELATIVE_LOCATION_BELOW
}UIRelativeAlign;

typedef enum
{
    RELATIVE_ALIGN_WIDGET_NONE,
    RELATIVE_ALIGN_WIDGET_LEFT,
    RELATIVE_ALIGN_WIDGET_TOP,
    RELATIVE_ALIGN_WIDGET_RIGHT,
    RELATIVE_ALIGN_WIDGET_BOTTOM
}UIRelativeAlignWidget;

NS_CC_EXT_END

#endif /* defined(__UILayoutDefine__) */
