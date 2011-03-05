
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

//�ṩ��DLLʵ���ߵ��õĺ�����������ȫ�ּ�¼ʵ����ClassFactory�����õĴ�����
//����������Ӱ��DLL�Ƿ���ܱ����ڴ���ж�أ�������ʵ�����ڲ�ʵ�ּ�����ͬʱ����ȫ�ּ�����
//����DLL���п��ܻ���ʵ�������ڵ�ʱ��ϵͳ�Զ�ǿ��ж��

//DLLȫ��ʹ�ã����Ӷ���ʵ�������ô���
Int32 TCOM_AddClsidInstanceRefCount();

//DLLȫ��ʹ�ã����ٶ���ʵ�������ô���
Int32 TCOM_DecClsidInstanceRefCount();

//DLLȫ��ʹ�ã�����ClassFactory��Locked�Ĵ���
Int32 TCOM_AddCalssFactoryLockedCount();

//DLLȫ��ʹ�ã�����ClassFactory��Locked�Ĵ���
Int32 TCOM_DecCalssFactoryLockedCount();


//Ӧ��DLL��֧��TCOM��ʱ���ṩ����������ʹ�õĺ���

//Ӧ�ø��ݸ�����CLSID��ClassFactory�ӿ�IID����ClassFactory�Ľӿ�
//����ֵ���ο�TCOM_S_ϵ�к궨��
HRESULT TCOM_Srv_GetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv);

//Ӧ���ṩ�İ�TCOM��Ϣ���뵽ע���
//����ֵ���ο�TCOM_S_ϵ�к궨��
HRESULT TCOM_Srv_RegisterServer(void);

//Ӧ���ṩ�İ�TCOM��Ϣ��ע�����ɾ��
//����ֵ���ο�TCOM_S_ϵ�к궨��
HRESULT TCOM_Srv_UnregisterServer(void);

#endif  //__TCOM_SUPPORT__

#endif  //__TG3_APP_DLL_ENTRY_H__



