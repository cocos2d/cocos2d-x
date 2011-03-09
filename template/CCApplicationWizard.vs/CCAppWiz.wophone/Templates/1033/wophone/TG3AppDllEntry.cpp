
#include "ssGlobal.h"
#include "ssTsd.h"
#include "TG3_Type.h"
#include <stdio.h>
#include "TCOM.h"
#include "ssAppMgr.h"
#include "TG3AppDllEntry.h"

#ifdef __TCOM_SUPPORT__

#ifdef __cplusplus
extern "C" {
#endif

    //实现TCOM所需要的DLL函数

    //DLL提供的获取指定CLSID的指定接口
    SS_EXPORT HRESULT TDllGetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv);

    //DLL提供的查询DLL能否被Unload
    SS_EXPORT HRESULT TDllCanUnloadNow(void);

    //DLL提供的把DLL的TCOM信息加入到注册表
    SS_EXPORT HRESULT TDllRegisterServer(void);

    //DLL提供的把DLL的TCOM信息从注册表中删除
    SS_EXPORT HRESULT TDllUnregisterServer(void);

#ifdef __cplusplus
}
#endif

#ifdef __TCOM_OUTPUT_DEBUG_INFO__
#include <stdio.h>
#endif

//TCOM实现中需要用到的函数和数据

//实例对象被引用的次数
static Int32 __TCOM_ClsidInstanceRefCount;

//ClassFactory被Locked的次数
static Int32 __TCOM_CalssFactoryLockedCount;

//做必要的初始化
static Int32 __TCOM_Init()
{
    __TCOM_ClsidInstanceRefCount = 0;
    __TCOM_CalssFactoryLockedCount = 0;
    return 0;
}

//做必要的清除工作
static Int32 __TCOM_DeInit()
{
    return 0;
}

//DLL全局使用：增加对象实例被引用次数
Int32 TCOM_AddClsidInstanceRefCount()
{
    __TCOM_ClsidInstanceRefCount++;
#ifdef __TCOM_OUTPUT_DEBUG_INFO__
    SS_printf("[TCOM_SYSTEM] TCOM_AddClsidInstanceRefCount: address: %p, value: %d.\n",
		&__TCOM_ClsidInstanceRefCount, __TCOM_ClsidInstanceRefCount);
#endif
    if(__TCOM_ClsidInstanceRefCount <= 0)
	{
        return 0;
	}
    return __TCOM_ClsidInstanceRefCount;
}

//DLL全局使用：减少对象实例被引用次数
Int32 TCOM_DecClsidInstanceRefCount()
{
    __TCOM_ClsidInstanceRefCount--;
#ifdef __TCOM_OUTPUT_DEBUG_INFO__
    SS_printf("[TCOM_SYSTEM] TCOM_DecClsidInstanceRefCount: address: %p, value: %d.\n",
		&__TCOM_ClsidInstanceRefCount, __TCOM_ClsidInstanceRefCount);
#endif
    if(__TCOM_ClsidInstanceRefCount <= 0)
	{
        return 0;
	}
    return __TCOM_ClsidInstanceRefCount;
}

//DLL全局使用：增加ClassFactory被Locked的次数
Int32 TCOM_AddCalssFactoryLockedCount()
{
    __TCOM_CalssFactoryLockedCount++;
#ifdef __TCOM_OUTPUT_DEBUG_INFO__
    SS_printf("[TCOM_SYSTEM] TCOM_AddCalssFactoryLockedCount: address: %p, value: %d.\n",
		&__TCOM_CalssFactoryLockedCount, __TCOM_CalssFactoryLockedCount);
#endif
    if(__TCOM_CalssFactoryLockedCount <= 0)
	{
        return 0;
	}
    return __TCOM_CalssFactoryLockedCount;
}

//DLL全局使用：减少ClassFactory被Locked的次数
Int32 TCOM_DecCalssFactoryLockedCount()
{
    __TCOM_CalssFactoryLockedCount--;
#ifdef __TCOM_OUTPUT_DEBUG_INFO__
    SS_printf("[TCOM_SYSTEM] TCOM_DecCalssFactoryLockedCount: address: %p, value: %d.\n",
		&__TCOM_CalssFactoryLockedCount, __TCOM_CalssFactoryLockedCount);
#endif
    if(__TCOM_CalssFactoryLockedCount <= 0)
	{
        return 0;
	}
    return __TCOM_CalssFactoryLockedCount;
}

//实现TCOM所需要的DLL函数

//DLL提供的获取指定CLSID的指定接口
SS_EXPORT HRESULT TDllGetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv)
{
    return TCOM_Srv_GetClassObject(rclsid, riid, ppv);
}

//DLL提供的查询DLL能否被Unload
SS_EXPORT HRESULT TDllCanUnloadNow(void)
{
#ifdef __TCOM_OUTPUT_DEBUG_INFO__
    SS_printf("[TCOM_SYSTEM] TDllCanUnloadNow: address1: %p, address2: %p, value1: %d, value2: %d.\n",
		&__TCOM_ClsidInstanceRefCount, &__TCOM_CalssFactoryLockedCount, __TCOM_ClsidInstanceRefCount,
		__TCOM_CalssFactoryLockedCount);
#endif
    if((__TCOM_ClsidInstanceRefCount <= 0) && (__TCOM_CalssFactoryLockedCount <= 0))
        return TCOM_S_TRUE;
    return TCOM_S_FALSE;
}

//DLL提供的把DLL的TCOM信息加入到注册表
SS_EXPORT HRESULT TDllRegisterServer(void)
{
    return TCOM_Srv_RegisterServer();
}

//DLL提供的把DLL的TCOM信息从注册表中删除
SS_EXPORT HRESULT TDllUnregisterServer(void)
{
    return  TCOM_Srv_UnregisterServer();
}

#endif  //__TCOM_SUPPORT__

#ifdef _WIN32

#ifndef SS_MAKEDLL
    #error Error!!! SS_MAKEDLL Must defined!
#endif

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//进程加载动态库进行的操作
#ifdef __TCOM_SUPPORT__
        __TCOM_Init();
#endif
		break;
	case DLL_THREAD_ATTACH:
		//线程加载动态库进行的操作
		break;
	case DLL_THREAD_DETACH:
		//线程卸载动态库进行的操作
		break;
	case DLL_PROCESS_DETACH:
		//进程卸载动态库进行的操作
#ifdef __TCOM_SUPPORT__
        __TCOM_DeInit();
#endif
		break;
	}
	return TRUE;
}
#else   //linux

#ifndef SS_SHARED
    #error Error!!! SS_SHARED Must defined!
#endif

void __attribute((constructor)) TG3_Dll_Attach()
{
    //进程加载动态库进行的操作
#ifdef __TCOM_SUPPORT__
    __TCOM_Init();
#endif
}

void __attribute((destructor)) TG3_Dll_Detach()
{
    //进程卸载动态库进行的操作
#ifdef __TCOM_SUPPORT__
    __TCOM_DeInit();
#endif
}

#endif

//如果不是作为TG3的动态库应用，请在VC项目中和TMK3文件中定义  __TG3_PURE_DLL__ 宏
#ifndef __TG3_PURE_DLL__

//动态库应用使用的统一导出名字的入口函数
SS_EXPORT Int32 TDllTG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	Int32 retValue;

	//初始化TCOM
	TCoInitialize(NULL);

	retValue = TG3AppMain(pAppID, nCmd, pCmdParam);

	//释放TCOM
	TCoUninitialize();

	return retValue;
}

#endif


