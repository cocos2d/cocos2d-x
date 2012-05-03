/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2012 NetGragon

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

#ifndef __CCCONTROL_DEFINE_H__
#define __CCCONTROL_DEFINE_H__

NS_CC_EXT_BEGIN

typedef enum
{
    PARENT_CENTER,
    VERTICAL_TOP,
    VERTICAL_BOTTOM,
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT,
    ABS_WITH_PIXEL,
    ABS_WITH_PERCENT,
    REF_PREV_X_INC,
    REF_PREV_X_DEC,
    REF_PREV_Y_INC,
    REF_PREV_Y_DEC,
    REL_FLOW
} LAYOUT_TYPE;

typedef struct
{
    LAYOUT_TYPE t;
    union
    {
        float pixel_val;
        float percent_val;
    } val;
} LayoutParamVal;

typedef struct
{
    LayoutParamVal val_x;
    LayoutParamVal val_y;
    float          padding;
    bool           wrap;
} LayoutParam;

NS_CC_EXT_END

#endif /* __CCCONTROL_DEFINE_H__ */
