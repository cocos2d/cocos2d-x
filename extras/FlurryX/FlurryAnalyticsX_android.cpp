//
//  FlurryAnalyticsX_android.cpp
//  MathsHudriks
//
//  Created by Dmitry Matyukhin on 30/01/2012.
//  Copyright (c) 2012 Fancygames. All rights reserved.
//

#include "FlurryAnalyticsX.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "jni/FlurryAnalyticsXJNI.h"
using namespace cocos2d;

void FlurryAnalyticsX::setAppVersion(const char *version) {
	jsetAppVersion(version);
}

const char* FlurryAnalyticsX::getFlurryAgentVersion() {
	return jgetFlurryAgentVersion();
}

void FlurryAnalyticsX::setShowErrorInLogEnabled(bool value) {
	jsetShowErrorInLogEnabled( value );
}

void FlurryAnalyticsX::setDebugLogEnabled(bool value) {
	jsetDebugLogEnabled( value );
}

void FlurryAnalyticsX::setSessionContinueSeconds(int seconds) {
	jsetSessionContinueSeconds(seconds);
}

void FlurryAnalyticsX::setSecureTransportEnabled(bool value) {
	jsetSecureTransportEnabled( value );
}

/*
 start session, attempt to send saved sessions to server 
 */
void FlurryAnalyticsX::startSession(const char *apiKey) {
	// FIX: Better start session in java
//	jstartSession(apiKey);
}

/*
 log events or errors after session has started
 */
void FlurryAnalyticsX::logEvent(const char *eventName) {
	jlogEvent1(eventName);
}

void FlurryAnalyticsX::logEvent(const char *eventName, const char *paramName, const char* paramValue) {
    CCStringToStringDictionary* params = new CCStringToStringDictionary();
    CCString* value = new CCString( paramValue );
    std::string strKey = paramName;
    params->setObject(value, strKey);

    logEvent( eventName, params );
    
    CC_SAFE_RELEASE_NULL( value );
    CC_SAFE_RELEASE_NULL( params );
}

void FlurryAnalyticsX::logEvent(const char *eventName, CCStringToStringDictionary *parameters) {
	jlogEvent3(eventName, parameters);
}

void FlurryAnalyticsX::logError(const char *errorID, const char *message) {
	jlogError(errorID, message);
}

/* 
 start or end timed events
 */
void FlurryAnalyticsX::logEvent(const char *eventName, bool timed) {
	jlogEvent4(eventName, timed);
}

void FlurryAnalyticsX::logEvent(const char *eventName, CCStringToStringDictionary *parameters, bool timed) {
	jlogEvent5(eventName, parameters, timed);
}

void FlurryAnalyticsX::endTimedEvent(const char *eventName, CCStringToStringDictionary * parameters) {
	jendTimedEvent(eventName, parameters);
}

/*
 set user info
 */
void FlurryAnalyticsX::setUserID(const char *userID) {
	jsetUserID(userID);
}

void FlurryAnalyticsX::setAge(int age) {
	jsetAge(age);
}

void FlurryAnalyticsX::setGender(const char *gender) {
	jsetGender(gender);
}

/*
 set location information
 */
void FlurryAnalyticsX::setLatitude(double latitude, double longitude, float horizontalAccuracy, float verticalAccuracy) {
	jsetLatitude(latitude, longitude, horizontalAccuracy, verticalAccuracy);
}

/*
 optional session settings that can be changed after start session
 */
void FlurryAnalyticsX::setSessionReportsOnCloseEnabled(bool sendSessionReportsOnClose) {
	jsetSessionReportsOnCloseEnabled(sendSessionReportsOnClose);
}

void FlurryAnalyticsX::setSessionReportsOnPauseEnabled(bool setSessionReportsOnPauseEnabled) {
	jsetSessionReportsOnPauseEnabled(setSessionReportsOnPauseEnabled);
}

void FlurryAnalyticsX::setEventLoggingEnabled(bool value) {
	jsetEventLoggingEnabled(value);
}


#endif
