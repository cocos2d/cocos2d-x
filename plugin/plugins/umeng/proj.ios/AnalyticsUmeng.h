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
#import "InterfaceAnalytics.h"

@interface AnalyticsUmeng : NSObject <InterfaceAnalytics>
{
}

@property BOOL debug;

/**
 interfaces of protocol : InterfaceAnalytics
 */
- (void) startSession: (NSString*) appKey;
- (void) stopSession;
- (void) setSessionContinueMillis: (long) millis;
- (void) setCaptureUncaughtException: (BOOL) isEnabled;
- (void) setDebugMode: (BOOL) isDebugMode;
- (void) logError: (NSString*) errorId withMsg:(NSString*) message;
- (void) logEvent: (NSString*) eventId;
- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap;
- (void) logTimedEventBegin: (NSString*) eventId;
- (void) logTimedEventEnd: (NSString*) eventId;
- (NSString*) getSDKVersion;
- (NSString*) getPluginVersion;

/**
 interfaces of umeng SDK
 */
- (void) updateOnlineConfig;
- (NSString*) getConfigParams: (NSString*) key;

/**
 @brief logEvent with label. 
 @param params The dictionary include eventId & label
                get eventId with key 'Param1' from dictionary
                get label with key 'Param2' from dictionary
 */
- (void) logEventWithLabel: (NSMutableDictionary*) params;

/**
 @brief logEvent with duration.
 @param params The dictionary include eventId & duration
                 get eventId with key 'Param1' from dictionary
                 get duration with key 'Param2' from dictionary
 */
- (void) logEventWithDuration: (NSMutableDictionary*) params;

/**
 @brief logEvent with duration & label.
 @param params The dictionary include eventId & duration & label
                 get eventId with key 'Param1' from dictionary
                 get duration with key 'Param2' from dictionary
                 get label with key 'Param3' from dictionary
 */
- (void) logEventWithDurationLabel: (NSMutableDictionary*) params;

/**
 @brief logEvent with duration & attributes.
 @param params The dictionary include eventId & duration & attributes
                 get eventId with key 'Param1' from dictionary
                 get duration with key 'Param2' from dictionary
                 get attributes with key 'Param3' from dictionary
 */
- (void) logEventWithDurationParams: (NSMutableDictionary*) params;

/**
 @brief log timed event begin with label.
 @param params The dictionary include eventId & label
                 get eventId with key 'Param1' from dictionary
                 get label with key 'Param2' from dictionary
 */
- (void) logTimedEventWithLabelBegin: (NSMutableDictionary*) params;

/**
 @brief log timed event end with label.
 @param params The dictionary include eventId & label
                 get eventId with key 'Param1' from dictionary
                 get label with key 'Param2' from dictionary
 */
- (void) logTimedEventWithLabelEnd: (NSMutableDictionary*) params;

/**
 @brief log timed KV event with label & attributes.
 @param params The dictionary include eventId & label & attributes
                 get eventId with key 'Param1' from dictionary
                 get label with key 'Param2' from dictionary
                 get attributes with key 'Param3' from dictionary
 */
- (void) logTimedKVEventBegin: (NSMutableDictionary*) params;

/**
 @brief log timed KV event end with label.
 @param params The dictionary include eventId & label
                 get eventId with key 'Param1' from dictionary
                 get label with key 'Param2' from dictionary
 */
- (void) logTimedKVEventEnd: (NSMutableDictionary*) params;

/**
 @brief start session with policy & channelId.
 @param params The dictionary include appKey & policy & channelId
                 get appKey with key 'Param1' from dictionary
                 get policy(NSNumber*) with key 'Param2' from dictionary
                 get channelId with key 'Param3' from dictionary
 */
- (void) startSessionWithParams: (NSMutableDictionary*) params;
- (void) checkUpdate;

@end
