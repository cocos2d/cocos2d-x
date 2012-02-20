/*
 * FlurryAnalyticsXJNI.h
 *
 *  Created on: Feb 10, 2012
 *      Author: dmitrymatyukhin
 */

#ifndef FLURRYANALYTICSXJNI_H_
#define FLURRYANALYTICSXJNI_H_


#include <jni.h>
#include "cocos2d.h"

extern "C"
{
/*
	 optional sdk settings that should be called before start session
	 */
	extern void jsetAppVersion(const char *version);		// override the app version
	extern const char* jgetFlurryAgentVersion();			// get the Flurry Agent version number
	extern void jsetShowErrorInLogEnabled(bool value);	// default is NO
	extern void jsetDebugLogEnabled(bool value);			// generate debug logs for Flurry support, default is NO
	extern void jsetSessionContinueSeconds(int seconds); // default is 10 seconds
	extern void jsetSecureTransportEnabled(bool value); // set data to be sent over SSL, default is NO

	/*
	 start session, attempt to send saved sessions to server
	 */
//	extern void startSession(const char *apiKey);

	/*
	 log events or errors after session has started
	 */
	extern void jlogEvent1(const char *eventName);
	extern void jlogEvent3(const char *eventName, cocos2d::CCStringToStringDictionary *parameters);
	extern void jlogError(const char *errorID, const char *message);

	/*
	 start or end timed events
	 */
	extern void jlogEvent4(const char *eventName, bool timed);
	extern void jlogEvent5(const char *eventName, cocos2d::CCStringToStringDictionary *parameters, bool timed);
	extern void jendTimedEvent(const char *eventName, cocos2d::CCStringToStringDictionary * parameters);	// non-nil parameters will update the parameters

	/*
	 set user info
	 */
	extern void jsetUserID(const char *userID);	// user's id in your system
	extern void jsetAge(int age);				// user's age in years
	extern void jsetGender(const char *gender);	// user's gender m or f

	/*
	 set location information
	 */
	extern void jsetLatitude(double latitude, double longitude, float horizontalAccuracy, float verticalAccuracy);

	/*
	 optional session settings that can be changed after start session
	 */
	extern void jsetSessionReportsOnCloseEnabled(bool sendSessionReportsOnClose);	// default is YES
	extern void jsetSessionReportsOnPauseEnabled(bool setSessionReportsOnPauseEnabled);	// default is NO
	extern void jsetEventLoggingEnabled(bool value);

}



#endif /* FLURRYANALYTICSXJNI_H_ */
