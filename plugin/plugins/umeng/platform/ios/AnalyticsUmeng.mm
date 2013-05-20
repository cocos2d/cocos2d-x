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
#include "PluginUtilsIOS.h"

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
	return PluginUtilsIOS::initOCPlugin(this, "UmengWrapper");
}

/** Start a new session. */
void AnalyticsUmeng::startSession(const char* appKey)
{
    ProtocolAnalytics::startSession(appKey);
}

/** Stop a session. only worked on android */
void AnalyticsUmeng::stopSession()
{
    ProtocolAnalytics::stopSession();
}

/** Set whether needs to output logs to console.*/
void AnalyticsUmeng::setDebugMode(bool debug)
{
    s_bDebugable = debug;
    ProtocolAnalytics::setDebugMode(debug);
}

/** Set the timeout for expiring a session. */
void AnalyticsUmeng::setSessionContinueMillis(long millis)
{
    ProtocolAnalytics::setSessionContinueMillis(millis);
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

/** Whether to catch uncaught exceptions to server.*/
void AnalyticsUmeng::setCaptureUncaughtException(bool enabled)
{
    ProtocolAnalytics::setCaptureUncaughtException(enabled);
}

const char* AnalyticsUmeng::getSDKVersion()
{
    return ProtocolAnalytics::getSDKVersion();
}

void AnalyticsUmeng::updateOnlineConfig()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "updateOnlineConfig");
}

const char* AnalyticsUmeng::getConfigParams(const char* key)
{
    NSString* strKey = [NSString stringWithUTF8String:key];
    return [[MobClick getConfigParams:strKey] UTF8String];
    
    
    if (NULL == key || strlen(key) == 0) {
        UmengLogD("The key is invalid!");
        return "";
    }

    NSString* pKey = [NSString stringWithUTF8String:key];
    NSString* ret = nil;
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"getConfigParams:");
        if ([pOCObj respondsToSelector:selector]) {
            ret = [pOCObj performSelector:selector withObject:pKey];
        }
    }

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

    NSString* strEvent = [NSString stringWithUTF8String:eventId];
    NSString* strLabel = [NSString stringWithUTF8String:label];
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"logEvent:withLabel:");
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:strEvent withObject:strLabel];
        }
    }
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    do {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        
        if (! pData) break;
        
        id pOCObj = pData->obj;
        NSString* className = [NSString stringWithUTF8String:pData->className.c_str()];
        SEL selector = NSSelectorFromString(@"logEvent:withDuration:withLabel:");
        
        if (! [pOCObj respondsToSelector:selector]) {
            break;
        }
        
        NSString* strEventId = [NSString stringWithUTF8String:eventId];
        NSString* strLabel   = [NSString stringWithUTF8String:label];
        NSNumber* numDur     = [NSNumber numberWithLong:duration];

        NSMethodSignature *sig= [NSClassFromString(className) instanceMethodSignatureForSelector:selector];
        NSInvocation *invocation=[NSInvocation invocationWithMethodSignature:sig];
        [invocation setTarget:pOCObj];
        [invocation setSelector:selector];
        [invocation setArgument:&strEventId atIndex:2];
        [invocation setArgument:&numDur atIndex:3];
        [invocation setArgument:&strLabel atIndex:4];
        [invocation retainArguments];
        [invocation invoke];
    } while (0);
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    do {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        
        if (! pData) break;
        
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"logEvent:withDuration:withParam:");
        
        if (! [pOCObj respondsToSelector:selector]) {
            break;
        }

        NSString* strEventId = [NSString stringWithUTF8String:eventId];
        NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
        NSNumber* numDur     = [NSNumber numberWithLong:duration];

        NSMethodSignature *sig = [[pOCObj class] instanceMethodSignatureForSelector:selector];
        NSInvocation *invocation =[NSInvocation invocationWithMethodSignature:sig];
        
        [invocation setSelector:selector];
        [invocation setTarget:pOCObj];
        [invocation setArgument:&strEventId atIndex:2];
        [invocation setArgument:&numDur atIndex:3];
        [invocation setArgument:&dict atIndex:4];
        [invocation retainArguments];
        [invocation invoke];
    } while (0);
}

void AnalyticsUmeng::logTimedEventWithLabelBegin(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    NSString* strEvent = [NSString stringWithUTF8String:eventId];
    NSString* strLabel = [NSString stringWithUTF8String:label];
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"logTimedEventBegin:withLabel:");
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:strEvent withObject:strLabel];
        }
    }
}

void AnalyticsUmeng::logTimedEventWithLabelEnd(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    NSString* strEvent = [NSString stringWithUTF8String:eventId];
    NSString* strLabel = [NSString stringWithUTF8String:label];
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"logTimedEventEnd:withLabel:");
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:strEvent withObject:strLabel];
        }
    }
}

void AnalyticsUmeng::logTimedKVEventBegin(const char* eventId, const char* label, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

    do {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        
        if (! pData) break;
        
        id pOCObj = pData->obj;
        NSString* className = [NSString stringWithUTF8String:pData->className.c_str()];
        SEL selector = NSSelectorFromString(@"logTimedKVEventBegin:withLabel:withParam:");
        
        if (! [pOCObj respondsToSelector:selector]) {
            break;
        }
        
        NSString* strEventId = [NSString stringWithUTF8String:eventId];
        NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
        NSString* strLabel     = [NSString stringWithUTF8String:label];

        NSMethodSignature *sig= [NSClassFromString(className) instanceMethodSignatureForSelector:selector];
        NSInvocation *invocation=[NSInvocation invocationWithMethodSignature:sig];
        [invocation setTarget:pOCObj];
        [invocation setSelector:selector];
        [invocation setArgument:&strEventId atIndex:2];
        [invocation setArgument:&strLabel atIndex:3];
        [invocation setArgument:&dict atIndex:4];
        [invocation retainArguments];
        [invocation invoke];
    } while (0);
}

void AnalyticsUmeng::logTimedKVEventEnd(const char* eventId, const char* label)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        UmengLogD("eventId is invalid");
        return;
    }

	NSString* strEvent = [NSString stringWithUTF8String:eventId];
    NSString* strLabel = [NSString stringWithUTF8String:label];
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"logTimedKVEventEnd:withLabel:");
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:strEvent withObject:strLabel];
        }
    }
}

void AnalyticsUmeng::startSession(const char* appKey, UmengReportPolicy policy, const char* channelId)
{
    if (NULL == appKey || strlen(appKey) == 0) {
        UmengLogD("appKey is invalid");
        return;
    }

    do {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        
        if (! pData) break;
        
        id pOCObj = pData->obj;
        NSString* className = [NSString stringWithUTF8String:pData->className.c_str()];
        SEL selector = NSSelectorFromString(@"logTimedKVEventBegin:withLabel:withParam:");
        
        if (! [pOCObj respondsToSelector:selector]) {
            break;
        }
        
        NSString* strKey     = [NSString stringWithUTF8String:appKey];
        NSNumber* numPolicy  = [NSNumber numberWithInt:policy];
        NSString* strChannel = [NSString stringWithUTF8String:channelId];
        
        NSMethodSignature *sig= [NSClassFromString(className) instanceMethodSignatureForSelector:selector];
        NSInvocation *invocation=[NSInvocation invocationWithMethodSignature:sig];
        [invocation setTarget:pOCObj];
        [invocation setSelector:selector];
        [invocation setArgument:&strKey atIndex:2];
        [invocation setArgument:&numPolicy atIndex:3];
        [invocation setArgument:&strChannel atIndex:4];
        [invocation retainArguments];
        [invocation invoke];
    } while (0);
}

void AnalyticsUmeng::checkUpdate()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "checkUpdate");
}

}} // namespace cocos2d { namespace plugin {
