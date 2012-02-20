/*
 * FlurryAnalyticsXJNI.cpp
 *
 *  Created on: Feb 10, 2012
 *      Author: dmitrymatyukhin
 */




#include "FlurryAnalyticsXJNI.h"
#include "platform/android/jni/JniHelper.h"

#include <android/log.h>
#include <jni.h>
#if 0
#define  LOG_TAG    "FlurryAnalyticsXJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

using namespace cocos2d;

extern "C"
{
	void jsetAppVersion(const char *version) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "setVersionName", "(Ljava/lang/String;)V"))
		{
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(version);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	const char* jgetFlurryAgentVersion() {
	    return NULL;
	}

	void jsetShowErrorInLogEnabled(bool value) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "setLogEnabled", "(Z)V"))
		{
			return;
		}


		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, value);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void jsetDebugLogEnabled(bool value) {
		// TODO: probably setLogLevel should be called, but no idea what values correspond to debug level
	}

	void jsetSessionContinueSeconds(int seconds) {
		// TODO:
	}

	void jsetSecureTransportEnabled(bool value) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "setUseHttps", "(Z)V"))
		{
			return;
		}


		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, value);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	/*
	 start session, attempt to send saved sessions to server
	 */
//	void jstartSession(const char *apiKey) {
		// TODO: better to start session in java code in onStart and onStop
//	}

	/*
	 log events or errors after session has started
	 */
	void jlogEvent1(const char *eventName) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "logEvent", "(Ljava/lang/String;)V"))
		{
			LOGD("Could not find static method");
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(eventName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void jlogEvent3(const char *eventName, CCStringToStringDictionary *parameters) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "logEvent", "(Ljava/lang/String;Ljava/util/Map;)V"))
		{
			LOGD("Could not find static method");
			return;
		}

		jclass mapClass = methodInfo.env->FindClass("java/util/HashMap");
		if(mapClass == NULL)
		{
			methodInfo.env->DeleteLocalRef(methodInfo.classID);
		    return;
		}

		jmethodID init = methodInfo.env->GetMethodID(mapClass, "<init>", "()V");
		jobject hashMap = methodInfo.env->NewObject(mapClass, init);

		jmethodID put = methodInfo.env->GetMethodID(mapClass, "put",
		            "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

		std::vector<std::string> keys = parameters->allKeys();
		std::vector<std::string>::iterator it;
		for (it = keys.begin(); it != keys.end(); ++it)
		{
	        CCString* value = parameters->objectForKey(*it);

	        jstring stringKey = methodInfo.env->NewStringUTF((*it).c_str());
	        jstring stringValue = methodInfo.env->NewStringUTF(value->toStdString().c_str());

		    methodInfo.env->CallObjectMethod(hashMap, put, stringKey, stringValue);

		    methodInfo.env->DeleteLocalRef(stringKey);
		    methodInfo.env->DeleteLocalRef(stringValue);
		}


		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, mapClass);
		methodInfo.env->DeleteLocalRef(mapClass);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

	}

	void jlogError(const char *errorID, const char *message) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "logError", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
		{
			LOGD("Could not find static method");
			return;
		}

		jstring stringError = methodInfo.env->NewStringUTF(errorID);
		jstring stringMessage = methodInfo.env->NewStringUTF(message);
		jstring stringClass = methodInfo.env->NewStringUTF("JNI");
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringError, stringMessage, stringClass);
		methodInfo.env->DeleteLocalRef(stringError);
		methodInfo.env->DeleteLocalRef(stringMessage);
		methodInfo.env->DeleteLocalRef(stringClass);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	/*
	 start or end timed events
	 */
	void jlogEvent4(const char *eventName, bool timed) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "logEvent", "(Ljava/lang/String;Z)V"))
		{
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(eventName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, timed);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void jlogEvent5(const char *eventName, CCStringToStringDictionary *parameters, bool timed) {
		// TODO:
	}

	void jendTimedEvent(const char *eventName, CCStringToStringDictionary * parameters) {
		// TODO:
	}

	/*
	 set user info
	 */
	void jsetUserID(const char *userID) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "setUserId", "(Ljava/lang/String;)V"))
		{
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(userID);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void jsetAge(int age) {
		// TODO:
	}

	void jsetGender(const char *gender) {
		// TODO:

	}

	/*
	 set location information
	 */
	void jsetLatitude(double latitude, double longitude, float horizontalAccuracy, float verticalAccuracy) {
		// TODO:
	}

	/*
	 optional session settings that can be changed after start session
	 */
	void jsetSessionReportsOnCloseEnabled(bool sendSessionReportsOnClose) {
		// TODO:
	}

	void jsetSessionReportsOnPauseEnabled(bool setSessionReportsOnPauseEnabled) {
		// TODO:
	}

	void jsetEventLoggingEnabled(bool value) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "com/flurry/android/FlurryAgent", "setLogEvents", "(Z)V"))
		{
			return;
		}


		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, value);

		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
}
