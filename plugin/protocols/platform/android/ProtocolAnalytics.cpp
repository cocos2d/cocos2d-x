#include "ProtocolAnalytics.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "ProtocolAnalytics"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

static void callJavaFunctionWithName_string_map(ProtocolAnalytics* thiz, const char* funcName, const char* keyParam, LogEventParamMap* paramMap)
{
	return_if_fails(funcName != NULL && strlen(funcName) > 0);
	return_if_fails(keyParam != NULL);

    PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);

	PluginJniMethodInfo t;
    if (NULL == paramMap)
    {
    	if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, funcName
    		, "(Ljava/lang/String;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(t.classID);
    	}
    }
    else
    {
    	if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, funcName
    		, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		jobject obj_Map = PluginUtils::createJavaMapObject(t, paramMap);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, obj_Map);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
    	}
    }
}

ProtocolAnalytics::ProtocolAnalytics()
{
}

ProtocolAnalytics::~ProtocolAnalytics()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolAnalytics::init()
{
    return true;
}

void ProtocolAnalytics::startSession(const char* appKey)
{
	callJavaFunctionWithName_string_map(this, "startSession", appKey, NULL);
}

void ProtocolAnalytics::stopSession()
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "stopSession"
        , "()V"))
    {
        t.env->CallVoidMethod(pData->jobj, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ProtocolAnalytics::setSessionContinueMillis(long millis)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setSessionContinueMillis", "(I)V", millis);
}

void ProtocolAnalytics::setCaptureUncaughtException(bool isEnabled)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setCaptureUncaughtException", "(Z)V", isEnabled);
}

void ProtocolAnalytics::setDebugMode(bool isDebugMode)
{
    PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", isDebugMode);
}

void ProtocolAnalytics::logError(const char* errorId, const char* message)
{
	return_if_fails(errorId != NULL && strlen(errorId) > 0);
	return_if_fails(message != NULL && strlen(message) > 0);

    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logError"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jerrorId = t.env->NewStringUTF(errorId);
		jstring jmessage = t.env->NewStringUTF(message);

		t.env->CallVoidMethod(pData->jobj, t.methodID, jerrorId, jmessage);
		t.env->DeleteLocalRef(jerrorId);
		t.env->DeleteLocalRef(jmessage);
		t.env->DeleteLocalRef(t.classID);
	}
}

const char* ProtocolAnalytics::getSDKVersion()
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

void ProtocolAnalytics::logEvent(const char* eventId, LogEventParamMap* pParams/* = NULL */)
{
	callJavaFunctionWithName_string_map(this, "logEvent", eventId, pParams);
}

void ProtocolAnalytics::logTimedEventBegin(const char* eventId)
{
	callJavaFunctionWithName_string_map(this, "logTimedEventBegin", eventId, NULL);
}

void ProtocolAnalytics::logTimedEventEnd(const char* eventId)
{
	callJavaFunctionWithName_string_map(this, "logTimedEventEnd", eventId, NULL);
}

}} //namespace cocos2d { namespace plugin {
