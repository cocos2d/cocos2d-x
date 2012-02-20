//
//  FlurryX.h
//  MathsHudriks
//
//  Created by Dmitry Matyukhin on 24/01/2012.
//  Copyright 2012 Fancygames. All rights reserved.
//

#ifndef MathsHudriks_FlurryX_cpp
#define MathsHudriks_FlurryX_cpp

#include "cocos2d.h"
#include "CCMutableDictionary.h"
#include "CCString.h"

class FlurryAnalyticsX
{
public:
    /*
     optional sdk settings that should be called before start session
     */
    static void setAppVersion(const char *version);		// override the app version
    static const char* getFlurryAgentVersion();			// get the Flurry Agent version number
    static void setShowErrorInLogEnabled(bool value);	// default is NO
    static void setDebugLogEnabled(bool value);			// generate debug logs for Flurry support, default is NO
    static void setSessionContinueSeconds(int seconds); // default is 10 seconds
    static void setSecureTransportEnabled(bool value); // set data to be sent over SSL, default is NO
    
    /*
     start session, attempt to send saved sessions to server 
     */
    static void startSession(const char *apiKey);
    
    /*
     log events or errors after session has started
     */
    static void logEvent(const char *eventName);
    static void logEvent(const char *eventName, const char *paramName, const char* paramValue);
    static void logEvent(const char *eventName, cocos2d::CCStringToStringDictionary *parameters);
    static void logError(const char *errorID, const char *message);
    
    /* 
     start or end timed events
     */
    static void logEvent(const char *eventName, bool timed);
    static void logEvent(const char *eventName, cocos2d::CCStringToStringDictionary *parameters, bool timed);
    static void endTimedEvent(const char *eventName, cocos2d::CCStringToStringDictionary * parameters);	// non-nil parameters will update the parameters
    
    /*
     set user info
     */
    static void setUserID(const char *userID);	// user's id in your system
    static void setAge(int age);				// user's age in years
    static void setGender(const char *gender);	// user's gender m or f
    
    /*
     set location information
     */
    static void setLatitude(double latitude, double longitude, float horizontalAccuracy, float verticalAccuracy);
    
    /*
     optional session settings that can be changed after start session
     */
    static void setSessionReportsOnCloseEnabled(bool sendSessionReportsOnClose);	// default is YES
    static void setSessionReportsOnPauseEnabled(bool setSessionReportsOnPauseEnabled);	// default is NO
    static void setEventLoggingEnabled(bool value);	
};

#endif // MathsHudriks_FlurryX_cpp
