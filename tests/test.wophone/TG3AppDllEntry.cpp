
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

    //ʵ��TCOM����Ҫ��DLL����

    //DLL�ṩ�Ļ�ȡָ��CLSID��ָ���ӿ�
    SS_EXPORT HRESULT TDllGetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv);

    //DLL�ṩ�Ĳ�ѯDLL�ܷ�Unload
    SS_EXPORT HRESULT TDllCanUnloadNow(void);

    //DLL�ṩ�İ�DLL��TCOM��Ϣ���뵽ע���
    SS_EXPORT HRESULT TDllRegisterServer(void);

    //DLL�ṩ�İ�DLL��TCOM��Ϣ��ע�����ɾ��
    SS_EXPORT HRESULT TDllUnregisterServer(void);

#ifdef __cplusplus
}
#endif

#ifdef __TCOM_OUTPUT_DEBUG_INFO__
#include <stdio.h>
#endif

//TCOMʵ������Ҫ�õ��ĺ���������

//ʵ���������õĴ���
static Int32 __TCOM_ClsidInstanceRefCount;

//ClassFactory��Locked�Ĵ���
static Int32 __TCOM_CalssFactoryLockedCount;

//����Ҫ�ĳ�ʼ��
static Int32 __TCOM_Init()
{
    __TCOM_ClsidInstanceRefCount = 0;
    __TCOM_CalssFactoryLockedCount = 0;
    return 0;
}

//����Ҫ���������
static Int32 __TCOM_DeInit()
{
    return 0;
}

//DLLȫ��ʹ�ã����Ӷ���ʵ�������ô���
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

//DLLȫ��ʹ�ã����ٶ���ʵ�������ô���
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

//DLLȫ��ʹ�ã�����ClassFactory��Locked�Ĵ���
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

//DLLȫ��ʹ�ã�����ClassFactory��Locked�Ĵ���
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

//ʵ��TCOM����Ҫ��DLL����

//DLL�ṩ�Ļ�ȡָ��CLSID��ָ���ӿ�
SS_EXPORT HRESULT TDllGetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv)
{
    return TCOM_Srv_GetClassObject(rclsid, riid, ppv);
}

//DLL�ṩ�Ĳ�ѯDLL�ܷ�Unload
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

//DLL�ṩ�İ�DLL��TCOM��Ϣ���뵽ע���
SS_EXPORT HRESULT TDllRegisterServer(void)
{
    return TCOM_Srv_RegisterServer();
}

//DLL�ṩ�İ�DLL��TCOM��Ϣ��ע�����ɾ��
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
		//���̼��ض�̬����еĲ���
#ifdef __TCOM_SUPPORT__
        __TCOM_Init();
#endif
		break;
	case DLL_THREAD_ATTACH:
		//�̼߳��ض�̬����еĲ���
		break;
	case DLL_THREAD_DETACH:
		//�߳�ж�ض�̬����еĲ���
		break;
	case DLL_PROCESS_DETACH:
		//����ж�ض�̬����еĲ���
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
    //���̼��ض�̬����еĲ���
#ifdef __TCOM_SUPPORT__
    __TCOM_Init();
#endif
}

void __attribute((destructor)) TG3_Dll_Detach()
{
    //����ж�ض�̬����еĲ���
#ifdef __TCOM_SUPPORT__
    __TCOM_DeInit();
#endif
}

#endif

//���������ΪTG3�Ķ�̬��Ӧ�ã�����VC��Ŀ�к�TMK3�ļ��ж���  __TG3_PURE_DLL__ ��
#ifndef __TG3_PURE_DLL__

//��̬��Ӧ��ʹ�õ�ͳһ�������ֵ���ں���
SS_EXPORT Int32 TDllTG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	Int32 retValue;

	//��ʼ��TCOM
	TCoInitialize(NULL);

	retValue = TG3AppMain(pAppID, nCmd, pCmdParam);

	//�ͷ�TCOM
	TCoUninitialize();

	return retValue;
}

#endif


