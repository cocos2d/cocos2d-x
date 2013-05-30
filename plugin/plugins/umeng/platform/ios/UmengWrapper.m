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
#import "UmengWrapper.h"
#import "MobClick.h"

@implementation UmengWrapper

- (void) startSession: (NSString*) appKey
{
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:appKey];
}

- (void) stopSession
{
    NSLog(@"stopSession in umeng not available on iOS");
}

- (void) setSessionContinueMillis: (NSNumber*) millis
{
    NSLog(@"setSessionContinueMillis in umeng not available on iOS");
}

- (void) setCaptureUncaughtException: (NSNumber*) isEnabled
{
    BOOL bEnabled = [isEnabled boolValue];
    [MobClick setCrashReportEnabled:bEnabled];
}

- (void) setDebugMode: (NSNumber*) isDebugMode
{
    BOOL bDebug = [isDebugMode boolValue];
    [MobClick setLogEnabled:bDebug];
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
    NSLog(@"logError in umeng not available on iOS");
}

- (void) logEvent: (NSString*) eventId
{
    [MobClick event:eventId];
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    [MobClick event:eventId attributes:paramMap];
}

- (void) logTimedEventBegin: (NSString*) eventId
{
    [MobClick beginEvent:eventId];
}

- (void) logTimedEventEnd: (NSString*) eventId
{
    [MobClick endEvent:eventId];
}

- (NSString*) getSDKVersion
{
    return @"UMeng no version info";
}

- (void) updateOnlineConfig
{
    [MobClick updateOnlineConfig];
}

- (NSString*) getConfigParams: (NSString*) key
{
    return [MobClick getConfigParams:key];
}

- (void) logEvent: (NSString*) eventId withLabel:(NSString*) label
{
    [MobClick event:eventId label:label];
}

- (void) logEvent: (NSString*) eventId withDuration: (NSNumber*) duration withLabel:(NSString*) label
{
    long numDur = [duration longValue];
    if (! label) {
        [MobClick event:eventId durations:numDur];
    } else {
        [MobClick event:eventId label:label durations:numDur];
    }
}

- (void) logEvent: (NSString*) eventId withDuration:(NSNumber*) duration withParam:(NSMutableDictionary*) paramMap
{
    long numDur = [duration longValue];
    if (! paramMap) {
        [MobClick event:eventId durations:(int)numDur];
    } else {
        [MobClick event:eventId attributes:paramMap durations:(int)numDur];
    }
}

- (void) logTimedEventBegin: (NSString*) eventId withLabel:(NSString*) label
{
    if (! label) {
        [MobClick beginEvent:eventId];
    } else {
        [MobClick beginEvent:eventId label:label];
    }
}

- (void) logTimedEventEnd: (NSString*) eventId withLabel:(NSString*) label
{
    if (! label) {
        [MobClick endEvent:eventId];
    } else {
        [MobClick endEvent:eventId label:label];
    }
}

- (void) logTimedKVEventBegin: (NSString*) eventId withLabel:(NSString*) label withParam:(NSMutableDictionary*) paramMap
{
    if (! label || ! paramMap) {
        [MobClick beginEvent:eventId];
    } else {
        [MobClick beginEvent:eventId primarykey:label attributes:paramMap];
    }
}

- (void) logTimedKVEventEnd: (NSString*) eventId withLabel:(NSString*) label
{
    if (! label) {
        [MobClick endEvent:eventId];
    } else {
        [MobClick endEvent:eventId primarykey:label];
    }
}

- (void) startSession: (NSString*) appKey withPolicy:(NSNumber*) policy withChannel:(NSString*) channelId
{
    int nPolicy = [policy intValue];
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:appKey reportPolicy:(ReportPolicy)nPolicy channelId:channelId];
}

- (void) checkUpdate
{
    [MobClick checkUpdate];
}

@end
