
#ifndef __TG3_APP_DLL_ENTRY_H__
#define __TG3_APP_DLL_ENTRY_H__

#ifndef __cplusplus
    #error This file need C++ support
#endif

#if TG3_APP_ENTRY_MINIMUM_VERSION > 200
#error Please replace TG3AppDllEntry.h and TG3AppDllEntry.cpp to newest version!
#endif

#ifdef __TCOM_SUPPORT__

#include "TCOM.h"

//提供给DLL实现者调用的函数，用于在全局记录实例和ClassFactory被引用的次数，
//这两个计数影响DLL是否可能被从内存中卸载，请大家在实例中内部实现计数的同时更新全局计数，
//否则DLL很有可能会在实例还存在的时候被系统自动强制卸载

//DLL全局使用：增加对象实例被引用次数
Int32 TCOM_AddClsidInstanceRefCount();

//DLL全局使用：减少对象实例被引用次数
Int32 TCOM_DecClsidInstanceRefCount();

//DLL全局使用：增加ClassFactory被Locked的次数
Int32 TCOM_AddCalssFactoryLockedCount();

//DLL全局使用：减少ClassFactory被Locked的次数
Int32 TCOM_DecCalssFactoryLockedCount();


//应用DLL在支持TCOM的时候提供给导出函数使用的函数

//应用根据给出的CLSID和ClassFactory接口IID返回ClassFactory的接口
//返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_GetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv);

//应用提供的把TCOM信息加入到注册表
//返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_RegisterServer(void);

//应用提供的把TCOM信息从注册表中删除
//返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_UnregisterServer(void);

#endif  //__TCOM_SUPPORT__

#endif  //__TG3_APP_DLL_ENTRY_H__



