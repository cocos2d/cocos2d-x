#include "ProtocolSocial.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "ProtocolSocial"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceSocial_nativeShareResult(JNIEnv*  env, jobject thiz, jint ret, jstring msg)
	{
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		ProtocolSocial::shareResult((EShareResult) ret, strMsg.c_str());
	}
}

bool ProtocolSocial::m_bSharing = false;
ShareResultListener* ProtocolSocial::m_pListener = NULL;
TShareInfo ProtocolSocial::m_curInfo;

ProtocolSocial::ProtocolSocial()
{
}

ProtocolSocial::~ProtocolSocial()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolSocial::init()
{
    return true;
}

void ProtocolSocial::initDeveloperInfo(TDeveloperInfo devInfo)
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

void ProtocolSocial::share(TShareInfo info)
{
    if (m_bSharing)
    {
        LOGD("Now is sharing");
        return;
    }

    if (info.empty())
    {
        if (NULL != m_pListener)
        {
            shareResult(eShareFail, "Share info error");
        }
        LOGD("The Share info is empty!");
        return;
    }
    else
    {
        m_bSharing = true;
        m_curInfo = info;

        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		PluginJniMethodInfo t;
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "share"
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

void ProtocolSocial::setResultListener(ShareResultListener* pListener)
{
	m_pListener = pListener;
}

void ProtocolSocial::shareResult(EShareResult ret, const char* msg)
{
    m_bSharing = false;
    if (m_pListener)
    {
    	m_pListener->shareResult(ret, msg, m_curInfo);
    }
    else
    {
        LOGD("Result listener is null!");
    }
    m_curInfo.clear();
    LOGD("Share result is : %d(%s)", (int) ret, msg);
}

const char* ProtocolSocial::getSDKVersion()
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

void ProtocolSocial::setDebugMode(bool debug)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", debug);
}

}} // namespace cocos2d { namespace plugin {
