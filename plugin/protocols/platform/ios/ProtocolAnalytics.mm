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

/**
 @brief Start a new session.
 @param appKey The identity of the application.
 */
void ProtocolAnalytics::startSession(const char* appKey)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        NSString* pStrKey = [NSString stringWithUTF8String:appKey];
        [curObj startSession:pStrKey];
    }
}

/**
 @brief Stop a session.
 @warning This interface only worked on android
 */
void ProtocolAnalytics::stopSession()
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        [curObj stopSession];
    }
}

/**
 @brief Set the timeout for expiring a session.
 @param millis In milliseconds as the unit of time.
 @note It must be invoked before calling startSession.
 */
void ProtocolAnalytics::setSessionContinueMillis(long millis)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        [curObj setSessionContinueMillis:millis];
    }
}

/**
 @brief log an error
 @param errorId The identity of error
 @param message Extern message for the error
 */
void ProtocolAnalytics::logError(const char* errorId, const char* message)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        NSString* pError = [NSString stringWithUTF8String:errorId];
        NSString* pMsg = [NSString stringWithUTF8String:message];
        [curObj logError:pError withMsg:pMsg];
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
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        NSString* pId = [NSString stringWithUTF8String:eventId];
        NSMutableDictionary* dict = PluginUtilsIOS::createDictFromMap(paramMap);
        [curObj logEvent:pId withParam:dict];
    }
}

/**
 @brief Track an event begin.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventBegin(const char* eventId)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        NSString* pEvent = [NSString stringWithUTF8String:eventId];
        [curObj logTimedEventBegin:pEvent];
    }
}

/**
 @brief Track an event end.
 @param eventId The identity of event
 */
void ProtocolAnalytics::logTimedEventEnd(const char* eventId)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        NSString* pEvent = [NSString stringWithUTF8String:eventId];
        [curObj logTimedEventEnd:pEvent];
    }
}

/**
 @brief Whether to catch uncaught exceptions to server.
 @warning This interface only worked on android.
 */
void ProtocolAnalytics::setCaptureUncaughtException(bool enabled)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    assert(pData != NULL);
    
    id ocObj = pData->obj;
    if ([ocObj conformsToProtocol:@protocol(InterfaceAnalytics)]) {
        NSObject<InterfaceAnalytics>* curObj = ocObj;
        [curObj setCaptureUncaughtException:enabled];
    }
}

}} //namespace cocos2d { namespace plugin {
