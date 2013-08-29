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
#import "AnalyticsFlurry.h"
#import "Flurry.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AnalyticsFlurry

@synthesize debug = __debug;

- (void) startSession: (NSString*) appKey
{
    [Flurry startSession:appKey];
}

- (void) stopSession
{
    OUTPUT_LOG(@"Flurry stopSession in flurry not available on iOS");
}

- (void) setSessionContinueMillis: (long) millis
{
    OUTPUT_LOG(@"Flurry setSessionContinueMillis invoked(%ld)", millis);
    int seconds = (int)(millis / 1000);
    [Flurry setSessionContinueSeconds:seconds];
}

- (void) setCaptureUncaughtException: (BOOL) isEnabled
{
    OUTPUT_LOG(@"Flurry setCaptureUncaughtException in flurry not available on iOS");
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    OUTPUT_LOG(@"Flurry setDebugMode invoked(%d)", isDebugMode);
    self.debug = isDebugMode;
    [Flurry setDebugLogEnabled:isDebugMode];
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
    OUTPUT_LOG(@"Flurry logError invoked(%@, %@)", errorId, message);
    NSString* msg = nil;
    if (nil == message) {
        msg = @"";
    } else {
        msg = message;
    }
    [Flurry logError:errorId message:msg exception:nil];
}

- (void) logEvent: (NSString*) eventId
{
    OUTPUT_LOG(@"Flurry logEvent invoked(%@)", eventId);
    [Flurry logEvent:eventId];
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"Flurry logEventWithParams invoked (%@, %@)", eventId, [paramMap debugDescription]);
    [Flurry logEvent:eventId withParameters:paramMap];
}

- (void) logTimedEventBegin: (NSString*) eventId
{
    OUTPUT_LOG(@"Flurry logTimedEventBegin invoked (%@)", eventId);
    [Flurry logEvent:eventId timed:YES];
}

- (void) logTimedEventEnd: (NSString*) eventId
{
    OUTPUT_LOG(@"Flurry logTimedEventEnd invoked (%@)", eventId);
    [Flurry endTimedEvent:eventId withParameters:nil];
}

- (NSString*) getSDKVersion
{
    return @"4.2.1";
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

- (void) setAge: (NSNumber*) age
{
    int nAge = [age integerValue];
    OUTPUT_LOG(@"Flurry setAge invoked (%d)", nAge);
    [Flurry setAge:nAge];
}

- (void) setGender: (NSNumber*) gender
{
    OUTPUT_LOG(@"Flurry setGender invoked (%@)", gender);
    int nValue = [gender intValue];
    NSString* strGender;
    if (nValue == 1) {
        strGender = @"m";
    } else {
        strGender = @"f";
    }
    [Flurry setGender:strGender];
}

- (void) setUserId: (NSString*) userId
{
    OUTPUT_LOG(@"Flurry setUserId invoked (%@)", userId);
    [Flurry setUserID:userId];
}

- (void) setUseHttps: (NSNumber*) enabled
{
    BOOL bEnabled = [enabled boolValue];
    OUTPUT_LOG(@"Flurry setUseHttps invoked (%@)", enabled);
    [Flurry setSecureTransportEnabled:bEnabled];
}

- (void) logPageView
{
    OUTPUT_LOG(@"Flurry logPageView invoked");
    [Flurry logPageView];
}

- (void) setVersionName: (NSString*) versionName
{
    OUTPUT_LOG(@"Flurry setVersionName invoked (%@)", versionName);
    [Flurry setAppVersion:versionName];
}

- (void) logTimedEventBeginWithParams: (NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"Flurry logTimedEventBeginWithParams invoked (%@)", [paramMap debugDescription]);
    NSString* eventId = (NSString*) [paramMap objectForKey:@"Param1"];
    NSMutableDictionary* params = (NSMutableDictionary*) [paramMap objectForKey:@"Param2"];
    if (params) {
        [Flurry logEvent:eventId withParameters:paramMap timed:YES];
    } else {
        [Flurry logEvent:eventId timed:YES];
    }
}

- (void) logTimedEventEndWithParams: (NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"Flurry logTimedEventEndWithParams invoked (%@)", [paramMap debugDescription]);
    NSString* eventId = (NSString*) [paramMap objectForKey:@"Param1"];
    NSMutableDictionary* params = (NSMutableDictionary*) [paramMap objectForKey:@"Param2"];
    [Flurry endTimedEvent:eventId withParameters:params];
}

@end
