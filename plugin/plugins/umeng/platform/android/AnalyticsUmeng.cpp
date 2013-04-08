#include "AnalyticsUmeng.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"
#if 1
#define  LOG_TAG    "AnalyticsUmeng"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsUmeng)

AnalyticsUmeng::~AnalyticsUmeng()
{
	LOGD("AnalyticsUmeng destructor");
}

bool AnalyticsUmeng::init()
{
    return PluginUtils::initJavaPlugin(this, "org.cocos2dx.plugin.AnalyticsUmeng");
}

void AnalyticsUmeng::updateOnlineConfig()
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;
	LOGD("update online 01");
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "updateOnlineConfig"
        , "()V"))
    {
    	LOGD("update online 02");
        t.env->CallVoidMethod(pData->jobj, t.methodID);
        LOGD("update online 03");
        t.env->DeleteLocalRef(t.classID);
        LOGD("update online 04");
    }
}

const char* AnalyticsUmeng::getConfigParams(const char* key)
{
	static std::string ret = "";
	return_val_if_fails(key != NULL && strlen(key) > 0, "");
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "getConfigParams"
		, "(Ljava/lang/String;)Ljava/lang/String;"))
	{
		jstring jstrKey = t.env->NewStringUTF(key);
		jstring jstr = (jstring)t.env->CallObjectMethod(pData->jobj, t.methodID, jstrKey);
		ret = PluginJniHelper::jstring2string(jstr);
		LOGD("ret = %s", ret.c_str());
		t.env->DeleteLocalRef(jstrKey);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret.c_str();
}

void AnalyticsUmeng::setDefaultReportPolicy(UmengReportPolicy ePolicy)
{
	return_if_fails(ePolicy == REALTIME 
		         || ePolicy == BATCH_AT_LAUNCH
		         || ePolicy == DAILY
		         || ePolicy == WIFIONLY );
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

    LOGD("data : %p", pData);
    LOGD("class name : %s", pData->jclassName.c_str());
	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "setDefaultReportPolicy"
		, "(I)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, (jint)ePolicy);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithLabel(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logEventWithLabel"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logEventWithDuration"
		, "(Ljava/lang/String;ILjava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, duration, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, LogEventParamMap* paramMap /* = NULL */)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (paramMap == NULL)
	{
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "logEventWithDuration"
			, "(Ljava/lang/String;I)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, duration);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	else
	{
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "logEventWithDuration"
			, "(Ljava/lang/String;ILjava/util/Hashtable;)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			jobject jparamMap= PluginUtils::createJavaMapObject(t, paramMap);
			t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, duration, jparamMap);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(jparamMap);
			t.env->DeleteLocalRef(t.classID);
		}
	}

}

void AnalyticsUmeng::logTimedEventWithLabelBegin(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logTimedEventWithLabelBegin"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedEventWithLabelEnd(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logTimedEventWithLabelEnd"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedKVEventBegin(const char* eventId, const char* label, LogEventParamMap* paramMap)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logTimedKVEventBegin"
		, "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Hashtable;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		jobject jparamMap= PluginUtils::createJavaMapObject(t, paramMap);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jlabel, jparamMap);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(jparamMap);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedKVEventEnd(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);
	
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);

	PluginJniMethodInfo t;
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "logTimedKVEventEnd"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

/** interface for ios */
void AnalyticsUmeng::startSession(const char* appKey, UmengReportPolicy policy, const char* channelId)
{
    startSession(appKey);
}

void AnalyticsUmeng::checkUpdate()
{
    
}

/** override methods of base class */
/** Start a new session. */
void AnalyticsUmeng::startSession(const char* appKey)
{
    ProtocolAnalytics::startSession(appKey);
}

/** Stop a session. */
void AnalyticsUmeng::stopSession()
{
    ProtocolAnalytics::stopSession();
}

/** Set the timeout for expiring a session. */
void AnalyticsUmeng::setSessionContinueMillis(long millis)
{
    ProtocolAnalytics::setSessionContinueMillis(millis);
}

/** Whether to catch uncaught exceptions to server.*/
void AnalyticsUmeng::setCaptureUncaughtException(bool enabled)
{
    ProtocolAnalytics::setCaptureUncaughtException(enabled);
}

const char* AnalyticsUmeng::getSDKVersion()
{
    return ProtocolAnalytics::getSDKVersion();
}

/** Set whether needs to output logs to console.*/
void AnalyticsUmeng::setDebugMode(bool debug)
{
    ProtocolAnalytics::setDebugMode(debug);
}

/** log an error */
void AnalyticsUmeng::logError(const char* errorId, const char* message)
{
    ProtocolAnalytics::logError(errorId, message);
}

/** log an event. */
void AnalyticsUmeng::logEvent(const char* eventId, LogEventParamMap* paramMap)
{
    ProtocolAnalytics::logEvent(eventId, paramMap);
}

/** begin to log a timed event */
void AnalyticsUmeng::logTimedEventBegin(const char* eventId)
{
    ProtocolAnalytics::logTimedEventBegin(eventId);
}

/** end a timed event */
void AnalyticsUmeng::logTimedEventEnd(const char* eventId)
{
    ProtocolAnalytics::logTimedEventEnd(eventId);
}

}} // namespace cocos2d { namespace plugin {
