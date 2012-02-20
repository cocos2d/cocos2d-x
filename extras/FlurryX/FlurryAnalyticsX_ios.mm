//
//  FlurryX.cpp
//  MathsHudriks
//
//  Created by Dmitry Matyukhin on 24/01/2012.
//  Copyright 2012 Fancygames. All rights reserved.
//

#import "FlurryAnalyticsX.h"
#import "FlurryAnalytics.h"

using namespace cocos2d;

inline NSString* CStrToNSString(const char* string) {
    return [NSString stringWithCString:string encoding:NSUTF8StringEncoding];
}

NSDictionary* CCDictionaryToNSDictionary(CCStringToStringDictionary* dictionary) {
    if ( !dictionary ) {
        return NULL;
    }

    NSMutableDictionary* result = [NSMutableDictionary dictionary];
	std::vector<std::string> keys = dictionary->allKeys();
	std::vector<std::string>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
        CCString* value = dictionary->objectForKey(*it);
        [result setObject: CStrToNSString(value->toStdString().c_str()) 
                   forKey: CStrToNSString((*it).c_str())];
	}

    return result;
}

void FlurryAnalyticsX::setAppVersion(const char *version) {
    [FlurryAnalytics setAppVersion:CStrToNSString( version )];
}

const char* FlurryAnalyticsX::getFlurryAgentVersion() {
    return [[FlurryAnalytics getFlurryAgentVersion] cStringUsingEncoding:NSUTF8StringEncoding];
}

void FlurryAnalyticsX::setShowErrorInLogEnabled(bool value) {
    [FlurryAnalytics setShowErrorInLogEnabled:value];
}

void FlurryAnalyticsX::setDebugLogEnabled(bool value) {
    [FlurryAnalytics setDebugLogEnabled:value];
}

void FlurryAnalyticsX::setSessionContinueSeconds(int seconds) {
    [FlurryAnalytics setSessionContinueSeconds:seconds];
}

void FlurryAnalyticsX::setSecureTransportEnabled(bool value) {
    [FlurryAnalytics setSecureTransportEnabled:value];
}

/*
 start session, attempt to send saved sessions to server 
 */
void FlurryAnalyticsX::startSession(const char *apiKey) {
    [FlurryAnalytics startSession:CStrToNSString( apiKey) ];
}

/*
 log events or errors after session has started
 */
void FlurryAnalyticsX::logEvent(const char *eventName) {
    [FlurryAnalytics logEvent:CStrToNSString( eventName )];
}

void FlurryAnalyticsX::logEvent(const char *eventName, const char *paramName, const char* paramValue) {
    CCStringToStringDictionary* params = new CCStringToStringDictionary();
    CCString* value = new CCString( paramValue );
    std::string strKey = paramName;
    params->setObject(value, strKey);
    
    FlurryAnalyticsX::logEvent( eventName, params );
    
    CC_SAFE_RELEASE_NULL( value );
    CC_SAFE_RELEASE_NULL( params );
    
}

void FlurryAnalyticsX::logEvent(const char *eventName, CCStringToStringDictionary *parameters) {
    [FlurryAnalytics logEvent:CStrToNSString( eventName ) withParameters:CCDictionaryToNSDictionary(parameters)];
}

void FlurryAnalyticsX::logError(const char *errorID, const char *message) {
    [FlurryAnalytics logError:CStrToNSString( errorID ) message:CStrToNSString( message ) exception:nil];
}

/* 
 start or end timed events
 */
void FlurryAnalyticsX::logEvent(const char *eventName, bool timed) {
    [FlurryAnalytics logEvent:CStrToNSString( eventName ) timed:timed];    
}

void FlurryAnalyticsX::logEvent(const char *eventName, CCStringToStringDictionary *parameters, bool timed) {
        [FlurryAnalytics logEvent:CStrToNSString( eventName ) withParameters:CCDictionaryToNSDictionary(parameters) timed:timed];
}

void FlurryAnalyticsX::endTimedEvent(const char *eventName, CCStringToStringDictionary * parameters) {
    [FlurryAnalytics endTimedEvent:CStrToNSString( eventName) withParameters:CCDictionaryToNSDictionary(parameters)];
}

/*
 set user info
 */
void FlurryAnalyticsX::setUserID(const char *userID) {
    [FlurryAnalytics setUserID:CStrToNSString( userID )];
}

void FlurryAnalyticsX::setAge(int age) {
    [FlurryAnalytics setAge:age];
}

void FlurryAnalyticsX::setGender(const char *gender) {
    [FlurryAnalytics setGender:CStrToNSString( gender )];
}

/*
 set location information
 */
void FlurryAnalyticsX::setLatitude(double latitude, double longitude, float horizontalAccuracy, float verticalAccuracy) {
    [FlurryAnalytics setLatitude:latitude longitude:longitude horizontalAccuracy:horizontalAccuracy verticalAccuracy:verticalAccuracy];
}

/*
 optional session settings that can be changed after start session
 */
void FlurryAnalyticsX::setSessionReportsOnCloseEnabled(bool sendSessionReportsOnClose) {
    [FlurryAnalytics setSessionReportsOnCloseEnabled:sendSessionReportsOnClose];
}

void FlurryAnalyticsX::setSessionReportsOnPauseEnabled(bool setSessionReportsOnPauseEnabled) {
    [FlurryAnalytics setSessionReportsOnPauseEnabled:setSessionReportsOnPauseEnabled];
}

void FlurryAnalyticsX::setEventLoggingEnabled(bool value) {
    [FlurryAnalytics setEventLoggingEnabled:value];
}