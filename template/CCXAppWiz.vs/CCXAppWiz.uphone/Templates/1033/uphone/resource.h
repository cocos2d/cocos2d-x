#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "[!output PROJECT_NAME]UnicodeScript_str.h";

[! if CCX_USE_UI_RESOURCE]
#include  "[!output PROJECT_NAME]_res_c.h"
#include "cocos2d.h"

const T_ResourceInfo ResInfo[] =
{
    { "CloseNormal",    COCOST_ID_BITMAP_CloseNormal },
    { "CloseSelected",  COCOST_ID_BITMAP_CloseSelected },
};
[! endif]


#endif  // __RESOURCE_H__
