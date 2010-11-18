#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "[!output PROJECT_NAME]UnicodeScript_str.h";
[! if CCX_USE_UI_RESOURCE]

#include  "[!output PROJECT_NAME]_res_c.h"
[! endif]

#include "cocos2d.h"

const T_ResourceInfo ResInfo[] =
{
    { "CloseNormal.png",    [! if CCX_USE_UI_RESOURCE]COCOST_ID_BITMAP_CloseNormal[! else]0[! endif] },
    { "CloseSelected.png",  [! if CCX_USE_UI_RESOURCE]COCOST_ID_BITMAP_CloseSelected[! else]0[! endif] },
};

#endif  // __RESOURCE_H__
