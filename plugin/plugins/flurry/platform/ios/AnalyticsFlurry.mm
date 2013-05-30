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
#include "AnalyticsFlurry.h"
#include "Flurry.h"
#include "PluginUtilsIOS.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsFlurry)

#define LOG_MAX_LENGTH          (16 * 1024)

static bool s_bDebugable = false;
void FlurryLogD(const char * pszFormat, ...)
{
    if (s_bDebugable) {
        printf("AnalyticsFlurry : ");
        char szBuf[LOG_MAX_LENGTH];
        
        va_list ap;
        va_start(ap, pszFormat);
        vsnprintf(szBuf, LOG_MAX_LENGTH, pszFormat, ap);
        va_end(ap);
        printf("%s", szBuf);
        printf("\n");
    }
}

AnalyticsFlurry::~AnalyticsFlurry()
{
}

bool AnalyticsFlurry::init()
{
    return PluginUtilsIOS::initOCPlugin(this, "FlurryWrapper");
}

/** override methods of base class */
/** Start a new session. */
void AnalyticsFlurry::startSession(const char* appKey)
{
    ProtocolAnalytics::startSession(appKey);
}

/** Stop a session. 
 only worked on android
*/
void AnalyticsFlurry::stopSession()
{
    ProtocolAnalytics::stopSession();
}

/** Set whether needs to output logs to console.*/
void AnalyticsFlurry::setDebugMode(bool debug)
{
    s_bDebugable = debug;
    ProtocolAnalytics::setDebugMode(debug);
}
    
/** Set the timeout for expiring a session. */
void AnalyticsFlurry::setSessionContinueMillis(long millis)
{
    ProtocolAnalytics::setSessionContinueMillis(millis);
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

void AnalyticsFlurry::logTimedEventBegin(const char* eventId)
{
    ProtocolAnalytics::logTimedEventBegin(eventId);
}

/** end a timed event */
void AnalyticsFlurry::logTimedEventEnd(const char* eventId)
{
    ProtocolAnalytics::logTimedEventEnd(eventId);
}

/** Whether to catch uncaught exceptions to server.
 only worked on android
 */
void AnalyticsFlurry::setCaptureUncaughtException(bool enabled)
{
    ProtocolAnalytics::setCaptureUncaughtException(enabled);
}

const char* AnalyticsFlurry::getSDKVersion()
{
    return ProtocolAnalytics::getSDKVersion();
}

void AnalyticsFlurry::setAge(int age)
{
    NSNumber* numAge = [NSNumber numberWithInt:age];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setAge:", numAge);
}

void AnalyticsFlurry::setGender(Gender gender)
{
    NSString* ret = @"m";
    if (gender == FEMALE) {
        ret = @"f";
    }
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setGender:", ret);
}

void AnalyticsFlurry::setUserId(const char* userId)
{
    if (NULL == userId || strlen(userId) == 0) {
        FlurryLogD("userId is invalid");
        return;
    }
    NSString* pUserID = [NSString stringWithUTF8String:userId];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setUserId:", pUserID);
}

void AnalyticsFlurry::logPageView()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "logPageView");
}

void AnalyticsFlurry::setVersionName(const char* versionName)
{
    NSString* pVer = [NSString stringWithUTF8String:versionName];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setVersionName:", pVer);
}

/**
 @warning only worked on android
 */
void AnalyticsFlurry::setUseHttps(bool useHttps)
{
    FlurryLogD("setUseHttps in flurry not available on iOS");
}

/**
 @warning only worked on android
 */
void AnalyticsFlurry::setReportLocation(bool enabled)
{
    FlurryLogD("setReportLocation in flurry not available on iOS");
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }

    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        this->logTimedEventBegin(eventId);
    } else {
        NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        if (pData) {
            id pOCObj = pData->obj;
            SEL selector = NSSelectorFromString(@"logTimedEventBegin:withParam:");
            if ([pOCObj respondsToSelector:selector]) {
                [pOCObj performSelector:selector withObject:pId withObject:dict];
            }
        }
    }
}
    
void AnalyticsFlurry::logTimedEventEnd(const char* eventId, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }
    
    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        this->logTimedEventEnd(eventId);
    } else {
        NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        if (pData) {
            id pOCObj = pData->obj;
            SEL selector = NSSelectorFromString(@"logTimedEventEnd:withParam:");
            if ([pOCObj respondsToSelector:selector]) {
                [pOCObj performSelector:selector withObject:pId withObject:dict];
            }
        }
    }
}

}} // namespace cocos2d { namespace plugin {
