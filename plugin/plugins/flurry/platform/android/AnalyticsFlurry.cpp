#include "AnalyticsFlurry.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "AnalyticsFlurry"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsFlurry)

AnalyticsFlurry::~AnalyticsFlurry()
{
	LOGD("AnalyticsFlurry destructor");
}

bool AnalyticsFlurry::init()
{
	return PluginUtils::initJavaPlugin(this, "org.cocos2dx.plugin.AnalyticsFlurry");
}

void AnalyticsFlurry::setReportLocation(bool enabled)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setReportLocation"
		, "(Z)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, enabled);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::logPageView()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logPageView"
		, "()V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setVersionName(const char* versionName)
{
	return_if_fails(versionName != NULL && strlen(versionName) > 0);
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setVersionName"
		, "(Ljava/lang/String;)V"))
	{
		jstring jversionName = t.env->NewStringUTF(versionName);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jversionName);
		t.env->DeleteLocalRef(jversionName);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setAge(int age)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setAge"
		, "(I)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, age);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setGender(Gender gender)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setGender"
		, "(B)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, (jbyte)gender);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUserId(const char* userId)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	return_if_fails(userId != NULL && strlen(userId) > 0);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setUserId"
		, "(Ljava/lang/String;)V"))
	{
		jstring juserId = t.env->NewStringUTF(userId);
		t.env->CallVoidMethod(pData->jobj, t.methodID, juserId);
		t.env->DeleteLocalRef(juserId);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::setUseHttps(bool useHttps)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t; 
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setUseHttps"
		, "(Z)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, useHttps);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId)
{
	ProtocolAnalytics::logTimedEventBegin(eventId);
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId, LogEventParamMap* paramMap)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	
	if (paramMap == NULL)
	{
		ProtocolAnalytics::logTimedEventBegin(eventId);
	}
	else
	{
		PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		PluginJniMethodInfo t;
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "logTimedEventBegin"
			, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			jobject jparamMap= PluginUtils::createJavaMapObject(t, paramMap);
			t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jparamMap);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(jparamMap);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

/** override methods of base class */
/** Start a new session. */
void AnalyticsFlurry::startSession(const char* appKey)
{
    ProtocolAnalytics::startSession(appKey);
}

/** Stop a session. */
void AnalyticsFlurry::stopSession()
{
    ProtocolAnalytics::stopSession();
}

/** Set the timeout for expiring a session. */
void AnalyticsFlurry::setSessionContinueMillis(long millis)
{
    ProtocolAnalytics::setSessionContinueMillis(millis);
}

/** Whether to catch uncaught exceptions to server.*/
void AnalyticsFlurry::setCaptureUncaughtException(bool enabled)
{
    ProtocolAnalytics::setCaptureUncaughtException(enabled);
}

const char* AnalyticsFlurry::getSDKVersion()
{
    return ProtocolAnalytics::getSDKVersion();
}

/** Set whether needs to output logs to console.*/
void AnalyticsFlurry::setDebugMode(bool debug)
{
    ProtocolAnalytics::setDebugMode(debug);
}

/** log an error */
void AnalyticsFlurry::logError(const char* errorId, const char* message)
{
    ProtocolAnalytics::logError(errorId, message);
}

/** log an event. */
void AnalyticsFlurry::logEvent(const char* eventId, LogEventParamMap* paramMap)
{
    ProtocolAnalytics::logEvent(eventId, paramMap);
}

/** end a timed event */
void AnalyticsFlurry::logTimedEventEnd(const char* eventId)
{
    ProtocolAnalytics::logTimedEventEnd(eventId);
}

void AnalyticsFlurry::logTimedEventEnd(const char* eventId, LogEventParamMap* paramMap)
{
	ProtocolAnalytics::logTimedEventEnd(eventId);
}

}} // namespace cocos2d { namespace plugin {
