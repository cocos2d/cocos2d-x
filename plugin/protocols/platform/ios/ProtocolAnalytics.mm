/****************************************************************************
 Copyright (c) 2012+2013 cocos2d+x.org
 
 http://www.cocos2d+x.org
 
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
#import  "InterfaceAnalytics.h"
#include "PluginUtilsIOS.h"

namespace cocos2d { namespace plugin {

ProtocolAnalytics::ProtocolAnalytics()
{
}

ProtocolAnalytics::~ProtocolAnalytics()
{
    PluginUtilsIOS::erasePluginOCData(this);
}

bool ProtocolAnalytics::init()
{
    return true;
}

/**
 @brief Start a new session.
 @param appKey The identity of the application.
 */
void ProtocolAnalytics::startSession(const char* appKey)
{
    NSString* pStrKey = [NSString stringWithUTF8String:appKey];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "startSession:", pStrKey);
}

/**
 @brief Stop a session.
 @warning This interface only worked on android
 */
void ProtocolAnalytics::stopSession()
{
    PluginUtilsIOS::callOCFunctionWithName(this, "stopSession");
}

/**
 @brief Set whether needs to output logs to console.
 @param debug if true debug mode enabled, or debug mode disabled.
 @note It must be invoked before calling startSession.
 */
void ProtocolAnalytics::setDebugMode(bool debug)
{
    NSNumber* bDebug = [NSNumber numberWithBool:debug];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setDebugMode:", bDebug);
}

/**
 @brief Set the timeout for expiring a session.
 @param millis In milliseconds as the unit of time.
 @note It must be invoked before calling startSession.
 */
void ProtocolAnalytics::setSessionContinueMillis(long millis)
{
    NSNumber* lMillis = [NSNumber numberWithLong:millis];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setSessionContinueMillis:", lMillis);
}

/**
 @brief log an error
 @param errorId The identity of error
 @param message Extern message for the error
 */
void ProtocolAnalytics::logError(const char* errorId, const char* message)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (! pData) {
        return;
    }
    
    id pOCObj = pData->obj;
    SEL selector = NSSelectorFromString(@"logError:withMsg:");
    if ([pOCObj respondsToSelector:selector]) {
        
        NSString* strErrID = [NSString stringWithUTF8String:errorId];
        NSString* strMsg = [NSString stringWithUTF8String:message];
        [pOCObj logError:strErrID withMsg:strMsg];
        NSLog(@"logError withMsg in OC class invoked!");
    }
}

/**
 @brief log an event.
 @param eventId The identity of event
 @param paramMap Extern parameters of the event, use NULL if not needed.
 */
void ProtocolAnalytics::logEvent(const char* eventId, LogEventParamMap* paramMap)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (! pData) {
        return;
    }
    
    id pOCObj = pData->obj;
    NSString* strEventID = [NSString stringWithUTF8String:eventId];

    if (paramMap == NULL) {
        PluginUtilsIOS::callOCFunctionWithName_Object(this, "logEvent:", strEventID);
        NSLog(@"logEvent(no paramsters) in OC class invoked!");
    } else {
        SEL selector = NSSelectorFromString(@"logEvent:withParam:");
        if ([pOCObj respondsToSelector:selector]) {

            NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
            [pOCObj logEvent:strEventID withParam:dict];
            NSLog(@"logEvent(with parameters) in OC class invoked!");
        }
    }
}

/**
 @brief Track an event begin.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventBegin(const char* eventId)
{
    NSString* pStrID = [NSString stringWithUTF8String:eventId];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "logTimedEventBegin:", pStrID);
}

/**
 @brief Track an event end.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventEnd(const char* eventId)
{
    NSString* pStrID = [NSString stringWithUTF8String:eventId];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "logTimedEventEnd:", pStrID);
}

/**
 @brief Whether to catch uncaught exceptions to server.
 @warning This interface only worked on android.
 */
void ProtocolAnalytics::setCaptureUncaughtException(bool enabled)
{
    NSNumber* bEnable = [NSNumber numberWithBool:enabled];
    PluginUtilsIOS::callOCFunctionWithName_Object(this, "setCaptureUncaughtException:", bEnable);
}

const char* ProtocolAnalytics::getSDKVersion()
{
    const char* pRet = "";

    do {
        PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
        if (! pData) break;

        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"getSDKVersion");
        if ([pOCObj respondsToSelector:selector]) {
            NSString* strRet = [pOCObj performSelector:selector];
            pRet = [strRet UTF8String];
        }
    } while (0);

    return pRet;
}

}} //namespace cocos2d { namespace plugin {
