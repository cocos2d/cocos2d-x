#include "AnalyticsFlurry.h"
#include "Flurry.h"

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
    return true;
}

/** override methods of base class */
/** Start a new session. */
void AnalyticsFlurry::startSession(const char* appKey)
{
    if (NULL == appKey || strlen(appKey) == 0) {
        FlurryLogD("appkey is invalid!");
        return;
    }
    NSString* pKey = [NSString stringWithUTF8String:appKey];
    [Flurry startSession:pKey];
}

/** Stop a session. 
 only worked on android
*/
void AnalyticsFlurry::stopSession()
{
}

/** Set whether needs to output logs to console.*/
void AnalyticsFlurry::setDebugMode(bool debug)
{
    s_bDebugable = debug;
    [Flurry setDebugLogEnabled:debug];
}
    
/** Set the timeout for expiring a session. */
void AnalyticsFlurry::setSessionContinueMillis(long millis)
{
    int seconds = (int)(millis / 1000);
    [Flurry setSessionContinueSeconds:seconds];
}

/** log an error */
void AnalyticsFlurry::logError(const char* errorId, const char* message)
{
    if (NULL == errorId || strlen(errorId) == 0) {
        FlurryLogD("errorId is invalid!");
        return;
    }
    NSString* pId = [NSString stringWithUTF8String:errorId];
    NSString* msg = nil;
    if (NULL == message) {
        msg = @"";
    } else {
        msg = [NSString stringWithUTF8String:message];
    }
    [Flurry logError:pId message:msg exception:nil];
}

/** log an event. */
void AnalyticsFlurry::logEvent(const char* eventId, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }
    
    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        [Flurry logEvent:pId];
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
        [Flurry logEvent:pId withParameters:dict];
    }
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }
    NSString* pId = [NSString stringWithUTF8String:eventId];
    [Flurry logEvent:pId timed:YES];
}

/** end a timed event */
void AnalyticsFlurry::logTimedEventEnd(const char* eventId)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }
    NSString* pId = [NSString stringWithUTF8String:eventId];
    [Flurry endTimedEvent:pId withParameters:nil];
}

/** Whether to catch uncaught exceptions to server.
 only worked on android
 */
void AnalyticsFlurry::setCaptureUncaughtException(bool enabled)
{
}

const char* AnalyticsFlurry::getSDKVersion()
{
    NSString* ver = [Flurry getFlurryAgentVersion];
    return [ver UTF8String];
}

void AnalyticsFlurry::setAge(int age)
{
    [Flurry setAge:age];
}

void AnalyticsFlurry::setGender(Gender gender)
{
    NSString* ret = @"m";
    if (gender == FEMALE) {
        ret = @"f";
    }
    [Flurry setGender:ret];
}

void AnalyticsFlurry::setUserId(const char* userId)
{
    if (NULL == userId || strlen(userId) == 0) {
        FlurryLogD("userId is invalid");
        return;
    }
    NSString* pUserID = [NSString stringWithUTF8String:userId];
    [Flurry setUserID:pUserID];
}

void AnalyticsFlurry::logPageView()
{
    [Flurry logPageView];
}
    
void AnalyticsFlurry::setVersionName(const char* versionName)
{
    NSString* pVer = [NSString stringWithUTF8String:versionName];
    [Flurry setAppVersion:pVer];
}

/**
 @warning only worked on android
 */
void AnalyticsFlurry::setUseHttps(bool useHttps)
{
    
}

/**
 @warning only worked on android
 */
void AnalyticsFlurry::setReportLocation(bool enabled)
{
    
}

void AnalyticsFlurry::logTimedEventBegin(const char* eventId, LogEventParamMap* paramMap)
{
    if (NULL == eventId || strlen(eventId) == 0) {
        FlurryLogD("eventId is invalid!");
        return;
    }
    
    NSString* pId = [NSString stringWithUTF8String:eventId];
    if (NULL == paramMap) {
        [Flurry logEvent:pId timed:YES];
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
        [Flurry logEvent:pId withParameters:dict timed:YES];
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
        [Flurry endTimedEvent:pId withParameters:nil];
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
        [Flurry endTimedEvent:pId withParameters:dict];
    }
}

}} // namespace cocos2d { namespace plugin {
