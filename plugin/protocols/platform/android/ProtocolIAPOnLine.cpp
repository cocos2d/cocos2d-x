#include "ProtocolIAPOnLine.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "ProtocolIAPOnLine"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceIAPOL_nativePayFailedLocally(JNIEnv*  env, jobject thiz, jint ret, jstring msg)
	{
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		ProtocolIAPOnLine::payFailedLocally((EPayResult) ret, strMsg.c_str());
	}
}

LocalResultListener* ProtocolIAPOnLine::m_spListener = NULL;

ProtocolIAPOnLine::ProtocolIAPOnLine()
{
}

ProtocolIAPOnLine::~ProtocolIAPOnLine()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolIAPOnLine::init()
{
    return true;
}

void ProtocolIAPOnLine::initDeveloperInfo(TDeveloperInfo devInfo)
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

void ProtocolIAPOnLine::payForProduct(TProductInfo info)
{
    if (info.empty())
    {
        LOGD("The product info is empty!");
        return;
    }
    else
    {
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

void ProtocolIAPOnLine::setLocalResultListener(LocalResultListener* pListener)
{
	m_spListener = pListener;
}

void ProtocolIAPOnLine::payFailedLocally(EPayResult ret, const char* msg)
{
	if (m_spListener)
	{
		m_spListener->payFailedLocally(ret, msg);
	}
	else
	{
		LOGD("Local Result listener is null!");
	}
	LOGD("Pay failed locally : %d(%s)", (int) ret, msg);
}

const char* ProtocolIAPOnLine::getSDKVersion()
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

void ProtocolIAPOnLine::setDebugMode(bool debug)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", debug);
}

}} // namespace cocos2d { namespace plugin {
