#ifndef _CONTROL_DEFINE_H_
#define _CONTROL_DEFINE_H_

namespace NdCxControl
{

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

}

#endif