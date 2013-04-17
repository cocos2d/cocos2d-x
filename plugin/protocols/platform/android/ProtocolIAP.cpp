#include "ProtocolIAP.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "ProtocolIAP"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceIAP_nativePayResult(JNIEnv*  env, jobject thiz, jint ret, jstring msg)
	{
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		ProtocolIAP::payResult((EPayResult) ret, strMsg.c_str());
	}
}

bool ProtocolIAP::m_bPaying = false;
PayResultListener* ProtocolIAP::m_pListener = NULL;
TProductInfo ProtocolIAP::m_curInfo;

ProtocolIAP::ProtocolIAP()
{
}

ProtocolIAP::~ProtocolIAP()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolIAP::init()
{
    return true;
}

void ProtocolIAP::initDeveloperInfo(TDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        LOGD("The developer info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "initDeveloperInfo"
    		, "(Ljava/util/Hashtable;)V"))
    	{
        	// generate the hashtable from map
        	jobject obj_Map = PluginUtils::createJavaMapObject(t, &devInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolIAP::payForProduct(TProductInfo info)
{
    if (m_bPaying)
    {
        LOGD("Now is paying");
        return;
    }

    if (info.empty())
    {
        if (NULL != m_pListener)
        {
            payResult(ePayFail, "Product info error");
        }
        LOGD("The product info is empty!");
        return;
    }
    else
    {
        m_bPaying = true;
        m_curInfo = info;

        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		PluginJniMethodInfo t;
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "payForProduct"
			, "(Ljava/util/Hashtable;)V"))
		{
			// generate the hashtable from map
			jobject obj_Map = PluginUtils::createJavaMapObject(t, &info);

			// invoke java method
			t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
			t.env->DeleteLocalRef(obj_Map);
			t.env->DeleteLocalRef(t.classID);
		}
    }
}

void ProtocolIAP::setResultListener(PayResultListener* pListener)
{
	m_pListener = pListener;
}

void ProtocolIAP::payResult(EPayResult ret, const char* msg)
{
    m_bPaying = false;
    if (m_pListener)
    {
    	m_pListener->payResult(ret, msg, m_curInfo);
    }
    else
    {
        LOGD("Result listener is null!");
    }
    m_curInfo.clear();
    LOGD("Pay result is : %d(%s)", (int) ret, msg);
}

const char* ProtocolIAP::getSDKVersion()
{
	std::string verName;

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "getSDKVersion"
		, "()Ljava/lang/String;"))
	{
		jstring ret = (jstring)(t.env->CallObjectMethod(pData->jobj, t.methodID));
		verName = PluginJniHelper::jstring2string(ret);
	}
	return verName.c_str();
}

void ProtocolIAP::setDebugMode(bool debug)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", debug);
}

}} // namespace cocos2d { namespace plugin {
