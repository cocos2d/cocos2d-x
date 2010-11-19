#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "[!output PROJECT_NAME]UnicodeScript_str.h";
[! if CCX_USE_UI_RESOURCE]

#include  "[!output PROJECT_NAME_LOWER]_res_def.h"
extern const AppResourceEntry [!output PROJECT_NAME]ResourceEntry;
[! endif]

#include "cocos2d.h"

const T_ResourceInfo ResInfo[] =
{
    { "CloseNormal.png",    [! if CCX_USE_UI_RESOURCE][!output PRO_NAME_PREFIX]_ID_BITMAP_CloseNormal[! else]0[! endif] },
    { "CloseSelected.png",  [! if CCX_USE_UI_RESOURCE][!output PRO_NAME_PREFIX]_ID_BITMAP_CloseSelected[! else]0[! endif] },
};

#endif  // __RESOURCE_H__
