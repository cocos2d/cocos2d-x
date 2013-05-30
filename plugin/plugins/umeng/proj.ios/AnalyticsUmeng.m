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
#import "AnalyticsUmeng.h"
#import "MobClick.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AnalyticsUmeng

@synthesize debug = __debug;

- (void) startSession: (NSString*) appKey
{
    OUTPUT_LOG(@"Umeng startSession invoked");
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:appKey];
}

- (void) stopSession
{
    OUTPUT_LOG(@"Umeng stopSession in umeng not available on iOS");
}

- (void) setSessionContinueMillis: (long) millis
{
    OUTPUT_LOG(@"Umeng setSessionContinueMillis in umeng not available on iOS");
}

- (void) setCaptureUncaughtException: (BOOL) isEnabled
{
    OUTPUT_LOG(@"Umeng setCaptureUncaughtException invoked");
    [MobClick setCrashReportEnabled:isEnabled];
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    OUTPUT_LOG(@"Umeng setDebugMode invoked");
    self.debug = isDebugMode;
    [MobClick setLogEnabled:isDebugMode];
}

- (void) logError: (NSString*) errorId withMsg:(NSString*) message
{
    OUTPUT_LOG(@"logError in umeng not available on iOS");
}

- (void) logEvent: (NSString*) eventId
{
    OUTPUT_LOG(@"Umeng logEvent invoked");
    [MobClick event:eventId];
}

- (void) logEvent: (NSString*) eventId withParam:(NSMutableDictionary*) paramMap
{
    OUTPUT_LOG(@"Umeng logEventWithParam invoked");
    [MobClick event:eventId attributes:paramMap];
}

- (void) logTimedEventBegin: (NSString*) eventId
{
    OUTPUT_LOG(@"Umeng logTimedEventBegin invoked");
    [MobClick beginEvent:eventId];
}

- (void) logTimedEventEnd: (NSString*) eventId
{
    OUTPUT_LOG(@"Umeng logTimedEventEnd invoked");
    [MobClick endEvent:eventId];
}

- (NSString*) getSDKVersion
{
    return @"2.2.0";
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

- (void) updateOnlineConfig
{
    OUTPUT_LOG(@"Umeng updateOnlineConfig invoked");
    [MobClick updateOnlineConfig];
}

- (NSString*) getConfigParams: (NSString*) key
{
    OUTPUT_LOG(@"Umeng getConfigParams invoked (%@)", key);
    return [MobClick getConfigParams:key];
}

- (void) logEventWithLabel: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logEventWithLabel invoked (%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSString* label = (NSString*) [params objectForKey:@"Param2"];
    if (label) {
        [MobClick event:eventId label:label];
    } else {
        [MobClick event:eventId];
    }
}

- (void) logEventWithDuration: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logEventWithDuration invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSNumber* duration = (NSNumber*) [params objectForKey:@"Param2"];
    long numDur = [duration longValue];
    [MobClick event:eventId durations:numDur];
}

- (void) logEventWithDurationLabel:(NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logEventWithDurationLabel invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSNumber* duration = (NSNumber*) [params objectForKey:@"Param2"];
    NSString* label = (NSString*) [params objectForKey:@"Param3"];
    long numDur = [duration longValue];

    if (! label) {
        [MobClick event:eventId durations:numDur];
    } else {
        [MobClick event:eventId label:label durations:numDur];
    }
}

- (void) logEventWithDurationParams: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logEventWithDurationParams invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSNumber* duration = (NSNumber*) [params objectForKey:@"Param2"];
    NSMutableDictionary* paramMap = (NSMutableDictionary*) [params objectForKey:@"Param3"];
    long numDur = [duration longValue];

    if (! paramMap) {
        [MobClick event:eventId durations:numDur];
    } else {
        [MobClick event:eventId attributes:paramMap durations:numDur];
    }
}

- (void) logTimedEventWithLabelBegin: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logTimedEventWithLabelBegin invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSString* label = (NSString*) [params objectForKey:@"Param2"];

    if (! label) {
        [MobClick beginEvent:eventId];
    } else {
        [MobClick beginEvent:eventId label:label];
    }
}

- (void) logTimedEventWithLabelEnd: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logTimedEventWithLabelEnd invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSString* label = (NSString*) [params objectForKey:@"Param2"];

    if (! label) {
        [MobClick endEvent:eventId];
    } else {
        [MobClick endEvent:eventId label:label];
    }
}

- (void) logTimedKVEventBegin: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logTimedKVEventBegin invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSString* label = (NSString*) [params objectForKey:@"Param2"];
    NSMutableDictionary* paramMap = (NSMutableDictionary*) [params objectForKey:@"Param3"];

    if (! label || ! paramMap) {
        [MobClick beginEvent:eventId];
    } else {
        [MobClick beginEvent:eventId primarykey:label attributes:paramMap];
    }
}

- (void) logTimedKVEventEnd: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng logTimedKVEventEnd invoked(%@)", [params debugDescription]);
    NSString* eventId = (NSString*) [params objectForKey:@"Param1"];
    NSString* label = (NSString*) [params objectForKey:@"Param2"];

    if (! label) {
        [MobClick endEvent:eventId];
    } else {
        [MobClick endEvent:eventId primarykey:label];
    }
}

- (void) startSessionWithParams: (NSMutableDictionary*) params
{
    OUTPUT_LOG(@"Umeng startSessionWithParams invoked(%@)", [params debugDescription]);
    NSString* appKey = (NSString*) [params objectForKey:@"Param1"];
    NSNumber* policy = (NSNumber*) [params objectForKey:@"Param2"];
    NSString* channelId = (NSString*) [params objectForKey:@"Param3"];

    int nPolicy = [policy intValue];
    [[MobClick class] performSelector:@selector(setWrapperType:wrapperVersion:) withObject:@"Cocos2d-x" withObject:@"1.0"];
    [MobClick startWithAppkey:appKey reportPolicy:(ReportPolicy)nPolicy channelId:channelId];
}

- (void) checkUpdate
{
    OUTPUT_LOG(@"Umeng checkUpdate invoked");
    [MobClick checkUpdate];
}

@end
