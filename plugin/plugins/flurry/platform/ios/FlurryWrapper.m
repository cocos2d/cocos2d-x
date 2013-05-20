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
#import "FlurryWrapper.h"
#import "Flurry.h"

@implementation FlurryWrapper

- (void) startSession: (NSString*) appKey
{
    [Flurry startSession:appKey];
}

- (void) stopSession
{
    NSLog(@"stopSession in flurry not available on iOS");
}

- (void) setSessionContinueMillis: (NSNumber*) millis
{
    long lMillis = [millis longValue];
    int seconds = (int)(lMillis / 1000);
    [Flurry setSessionContinueSeconds:seconds];
}

- (void) setCaptureUncaughtException: (NSNumber*) isEnabled
{
    NSLog(@"setCaptureUncaughtException in flurry not available on iOS");
}

- (void) setDebugMode: (NSNumber*) isDebugMode
{
    BOOL bDebug = [isDebugMode boolValue];
    [Flurry setDebugLogEnabled:bDebug];
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
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
    [Flurry logEvent:eventId];
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    [Flurry logEvent:eventId withParameters:paramMap];
}

- (void) logTimedEventBegin: (NSString*) eventId
{
    [Flurry logEvent:eventId timed:YES];
}

- (void) logTimedEventEnd: (NSString*) eventId
{
    [Flurry endTimedEvent:eventId withParameters:nil];
}

- (NSString*) getSDKVersion
{
    return [Flurry getFlurryAgentVersion];
}

- (void) setAge: (NSNumber*) age
{
    int nAge = [age integerValue];
    [Flurry setAge:nAge];
}

- (void) setGender: (NSString*) gender
{
    [Flurry setGender:gender];
}

- (void) setUserId: (NSString*) userId
{
    [Flurry setUserID:userId];
}

- (void) logPageView
{
    [Flurry logPageView];
}

- (void) setVersionName: (NSString*) versionName
{
    [Flurry setAppVersion:versionName];
}

- (void) logTimedEventBegin: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    [Flurry logEvent:eventId withParameters:paramMap timed:YES];
}

- (void) logTimedEventEnd: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    [Flurry endTimedEvent:eventId withParameters:paramMap];
}

@end
