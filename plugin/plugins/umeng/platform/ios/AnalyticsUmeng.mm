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
#include "AnalyticsUmeng.h"
#include "MobClick.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsUmeng)

#define LOG_MAX_LENGTH          (16 * 1024)

static bool s_bDebugable = false;
void UmengLogD(const char * pszFormat, ...) {
    if (s_bDebugable) {
        printf("AnalyticsUmeng : ");
        char szBuf[LOG_MAX_LENGTH];
        
        va_list ap;
        va_start(ap, pszFormat);
        vsnprintf(szBuf, LOG_MAX_LENGTH, pszFormat, ap);
        va_end(ap);
        printf("%s", szBuf);
        printf("\n");
    }
}

AnalyticsUmeng::~AnalyticsUmeng()
{
}

bool AnalyticsUmeng::init()
{
	return true;
}

/** Start a new session. */
void AnalyticsUmeng::startSession(const char* appKey)
{
    if (NULL == appKey || strlen(appKey) == 0) {
        UmengLogD("appkey is invalid!");
        return;
    }
    NSString* pKey = [NSString stringWithUTF8String:appKey];
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:pKey];
}

/** Stop a session. only worked on android */
void AnalyticsUmeng::stopSession()
{
}

/** Set whether needs to output logs to console.*/
void AnalyticsUmeng::setDebugMode(bool debug)
{
    s_bDebugable = debug;
    [MobClick setLogEnabled:debug];
}

/** Set the timeout for expiring a session. */
void AnalyticsUmeng::setSessionContinueMillis(long millis)
{
    
}

/** log an error */
void AnalyticsUmeng::logError(const char* errorId, const char* message)
{
    
}

/** log an event. */
void AnalyticsUmeng::logEvent(const char* eventId, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid!");
        return;
    }

    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        [MobClick event:pId];
    } else {
        NSMutableDictionary* dict = [NSMutableDictionary dictionary];
        LogEventParamMap::iterator it;
        for (it = paramMap->begin(); it != paramMap->end(); it++) {
            std::string key = it->first;
            std::string value = it->second;
            NSString* pKey = [NSString stringWithUTF8String:key.c_str()];
            NSString* pValue = [NSString stringWithUTF8String:value.c_str()];
            [dict setObject:pValue forKey:pKey];
        }
        [MobClick event:pId attributes:dict];
    }
}

/** begin to log a timed event */
void AnalyticsUmeng::logTimedEventBegin(const char* eventId)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid!");
        return;
    }

    NSString* pEvent = [NSString stringWithUTF8String:eventId];
    [MobClick beginEvent:pEvent];
}

/** end a timed event */
void AnalyticsUmeng::logTimedEventEnd(const char* eventId)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid!");
        return;
    }

    NSString* pEvent = [NSString stringWithUTF8String:eventId];
    [MobClick endEvent:pEvent];
}

/** Whether to catch uncaught exceptions to server.*/
void AnalyticsUmeng::setCaptureUncaughtException(bool enabled)
{
    [MobClick setCrashReportEnabled:enabled];
}

const char* AnalyticsUmeng::getSDKVersion()
{
    return "UMeng no version info";
}

void AnalyticsUmeng::updateOnlineConfig()
{
	[MobClick updateOnlineConfig];
}

const char* AnalyticsUmeng::getConfigParams(const char* key)
{
    if (NULL == key || strlen(key) == 0) {
        UmengLogD("The key is invalid!");
        return "";
    }

    NSString* pKey = [NSString stringWithUTF8String:key];
	NSString* ret = [MobClick getConfigParams:pKey];
    const char* pRet = (nil == ret) ? NULL : [ret UTF8String];
    return pRet;
}

static AnalyticsUmeng::UmengReportPolicy s_defaultPolicy = AnalyticsUmeng::UmengReportPolicy::REALTIME;
void AnalyticsUmeng::setDefaultReportPolicy(UmengReportPolicy ePolicy)
{
	s_defaultPolicy = ePolicy;
}

void AnalyticsUmeng::logEventWithLabel(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == label) {
        [MobClick event:pId];
    } else {
        NSString* pLabel = [NSString stringWithUTF8String:label];
        [MobClick event:pId label:pLabel];
    }
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == label) {
        [MobClick event:pId durations:(int)duration];
    } else {
        NSString* pLabel = [NSString stringWithUTF8String:label];
        [MobClick event:pId label:pLabel durations:(int)duration];
    }
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

	NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        [MobClick event:pId durations:(int)duration];
    } else {
        NSMutableDictionary* dict = [NSMutableDictionary dictionary];
        LogEventParamMap::iterator it;
        for (it = paramMap->begin(); it != paramMap->end(); it++) {
            std::string key = it->first;
            std::string value = it->second;
            NSString* pKey = [NSString stringWithUTF8String:key.c_str()];
            NSString* pValue = [NSString stringWithUTF8String:value.c_str()];
            [dict setObject:pValue forKey:pKey];
        }
        [MobClick event:pId attributes:dict durations:(int)duration];
    }
}

void AnalyticsUmeng::logTimedEventWithLabelBegin(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == label) {
        [MobClick beginEvent:pId];
    } else {
        NSString* pLabel = [NSString stringWithUTF8String:label];
        [MobClick beginEvent:pId label:pLabel];
    }
}

void AnalyticsUmeng::logTimedEventWithLabelEnd(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

	NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == label) {
        [MobClick endEvent:pId];
    } else {
        NSString* pLabel = [NSString stringWithUTF8String:label];
        [MobClick endEvent:pId label:pLabel];
    }
}

void AnalyticsUmeng::logTimedKVEventBegin(const char* eventId, const char* label, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

	NSString* pId = [NSString stringWithUTF8String:eventId];
    NSString* primary = [NSString stringWithUTF8String:label];
    if (NULL == paramMap || NULL == label) {
        [MobClick beginEvent:pId];
    } else {
        NSMutableDictionary* dict = [NSMutableDictionary dictionary];
        LogEventParamMap::iterator it;
        for (it = paramMap->begin(); it != paramMap->end(); it++) {
            std::string key = it->first;
            std::string value = it->second;
            NSString* pKey = [NSString stringWithUTF8String:key.c_str()];
            NSString* pValue = [NSString stringWithUTF8String:value.c_str()];
            [dict setObject:pValue forKey:pKey];
        }
        [MobClick beginEvent:pId primarykey:primary attributes:dict];
    }
}

void AnalyticsUmeng::logTimedKVEventEnd(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

	NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == label) {
        [MobClick endEvent:pId];
    } else {
        NSString* primary = [NSString stringWithUTF8String:label];
        [MobClick endEvent:pId primarykey:primary];
    }
}

void AnalyticsUmeng::startSession(const char* appKey, UmengReportPolicy policy, const char* channelId)
{
    if (NULL == appKey || strlen(appKey) == 0) {
        UmengLogD("appKey is invalid");
        return;
    }

    NSString* key = [NSString stringWithUTF8String:appKey];
    NSString* channel = [NSString stringWithUTF8String:channelId];
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:key reportPolicy:(ReportPolicy)policy channelId:channel];
}

void AnalyticsUmeng::checkUpdate()
{
    [MobClick checkUpdate];
}

}} // namespace cocos2d { namespace plugin {
