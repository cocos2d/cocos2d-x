#include "TG3.h"
#include "[!output PROJECT_NAME]UnicodeScript_str.h"
#include "TCOM.h"
#include "TG3AppDllEntry.h"

// 提供IID的具体定义，在整个项目中只能包含一次
[! if CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE]
[! else]
#include "TCOM_Generic_DataType_IIDs.h"
#include "TCOM_Generic_Method_IIDs.h"
[! endif]
#include "TCOM_IIDs.h"

// 定义类工厂例子代码:
// class Texample_MethodClassFactory;    //仅仅为了代码编辑辅助工具正确显示
// TCOM_DECLARE_CLASS_FACTORY(Texample_MethodClassFactory);
// TCOM_IMPLEMENT_CLASS_FACTORY(Texample_MethodClassFactory,TexampleDataType);
// 应用根据给出的CLSID和ClassFactory接口IID返回ClassFactory的接口
// 返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_GetClassObject(TREFCLSID rclsid, TREFIID riid, LPVOID * ppv)
{
    HRESULT result = TCOM_S_E_ERROR;
    // 构造出TCOM对象例子
    //if (rclsid == TCLSID_example_Method)
    //{
    //  Texample_MethodClassFactory *pFactory = new Texample_MethodClassFactory();
    //  if(pFactory)
    //  {
    //      result = pFactory->QueryInterface(riid, ppv);
    //      if(TCOM_S_FAIL(result))
    //      {
    //          delete pFactory;
    //          TCOM_DecClsidInstanceRefCount();
    //      }
    //  }
    //}

    return result;
}

// 应用提供的把TCOM信息加入到注册表
// 返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_RegisterServer(void)
{
    TCOM_ApplicationRegister * pAppRegister = NULL; 
    pAppRegister = new TCOM_ApplicationRegister( AppName_[!output PROJECT_NAME] );
    if(pAppRegister == NULL)
    {
        return TCOM_S_E_ERROR;
    }

    // 注册例子：
    // pAppRegister->RegisterCLSID(TCLSID_example_Method, TCOM_CLSCTX_INPROC_SERVER); 
    // pAppRegister->RegisterDataType( TTID_TCOM_PlugIn_DataType); 
    // pAppRegister->RegisterMethod( TTID_TCOM_PlugIn_DataType, TIID_SYS_Method_Open, 
    // TCLSID_example_Method, TCOM_METHOD_MASK_NORMAL, AppName_example ); 
    if(pAppRegister)
    {
        delete pAppRegister;
        pAppRegister = NULL;
    }
    return TCOM_S_OK;
}

// 应用提供的把TCOM信息从注册表中删除
// 返回值：参考TCOM_S_系列宏定义
HRESULT TCOM_Srv_UnregisterServer(void)
{
    TCOM_ApplicationRegister * pAppRegister = NULL;
    pAppRegister = new TCOM_ApplicationRegister( AppName_[!output PROJECT_NAME] );
    if(pAppRegister == NULL)
    {
        return TCOM_S_E_ERROR;
    }

    // 注销例子
    // pAppRegister->UnregisterMethod(TTID_TCOM_PlugIn_DataType, TIID_SYS_Method_Open, TCLSID_example_Method);
    // pAppRegister->UnregisterDataType( TTID_TCOM_PlugIn_DataType );
    // pAppRegister->UnregisterCLSID(TCLSID_example_Method);
    if(pAppRegister)
    {
        delete pAppRegister;
        pAppRegister = NULL;
    }

    return TCOM_S_OK;
}
