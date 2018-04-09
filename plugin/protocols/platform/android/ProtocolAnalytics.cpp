/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "ProtocolAnalytics.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

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
    		jobject obj_Map = PluginUtils::createJavaMapObject(paramMap);
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
	PluginUtils::callJavaFunctionWithName_oneParam(this, "setSessionContinueMillis", "(I)V", millis);
}

void ProtocolAnalytics::setCaptureUncaughtException(bool isEnabled)
{
	PluginUtils::callJavaFunctionWithName_oneParam(this, "setCaptureUncaughtException", "(Z)V", isEnabled);
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
