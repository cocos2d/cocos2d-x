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
#import "AdsFlurry.h"
#import "Flurry.h"
#import "FlurryAds.h"
#import "AdsWrapper.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AdsFlurry

@synthesize debug = __debug;


#pragma mark Interfaces for ProtocolAds impl

- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo
{
    NSString* appKey = [devInfo objectForKey:@"FlurryAppKey"];
    if (appKey) {
        [Flurry startSession:appKey];
    }

    [FlurryAds initialize:[AdsWrapper getCurrentRootViewController]];
    [FlurryAds setAdDelegate:self];
}

- (void) showAds: (NSMutableDictionary*) info position:(int) pos
{
    NSString* strSpaceID = [info objectForKey:@"FlurryAdsID"];
    if (! strSpaceID || [strSpaceID length] == 0) {
        OUTPUT_LOG(@"Value of 'FlurryAdsID' should not be empty");
        return;
    }

    NSString* strSize = [info objectForKey:@"FlurryAdsSize"];
    int size = [strSize intValue];
    if (size != 1 && size != 2 && size != 3) {
        OUTPUT_LOG(@"Value of 'FlurryAdsSize' should be one of '1', '2', '3' ");
        return;
    }

    UIViewController* controller = [AdsWrapper getCurrentRootViewController];
    if (controller) {
        [FlurryAds fetchAndDisplayAdForSpace:strSpaceID view:controller.view size:size];
    }
}

- (void) hideAds: (NSMutableDictionary*) info
{
    NSString* strSpaceID = [info objectForKey:@"FlurryAdsID"];
    if (! strSpaceID || [strSpaceID length] == 0) {
        OUTPUT_LOG(@"Value of 'FlurryAdsID' should not be empty");
        return;
    }

    [FlurryAds removeAdFromSpace:strSpaceID];
}

- (void) queryPoints
{
    
}

- (void) spendPoints: (int) points
{
    
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    OUTPUT_LOG(@"Flurry setDebugMode invoked(%d)", isDebugMode);
    self.debug = isDebugMode;
    [Flurry setDebugLogEnabled:isDebugMode];

    if (self.debug) {
        [FlurryAds enableTestAds:YES]; 
    }
}

- (NSString*) getSDKVersion
{
    return @"4.2.1";
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

#pragma mark Interfaces for FlurryAdDelegate impl

- (void) spaceDidReceiveAd:(NSString*)adSpace
{
    [AdsWrapper onAdsResult:self withRet:kAdsReceived  withMsg:@"Ads of flurry received"];
}

- (void) spaceDidFailToReceiveAd:(NSString*)adSpace error:(NSError *)error
{
    NSString* strMsg = [[error userInfo] objectForKey:@"NSLocalizedDescription"];
    if (! strMsg) {
        strMsg = @"Failed to receive ads";
    }
    [AdsWrapper onAdsResult:self withRet:kUnknownError withMsg:strMsg];
}

- (BOOL) spaceShouldDisplay:(NSString*)adSpace interstitial:(BOOL)interstitial
{
    [AdsWrapper onAdsResult:self withRet:kAdsShown withMsg:@"Ads will be shown"];
    return YES;
}

- (void) spaceWillDismiss:(NSString *)adSpace
{
    [AdsWrapper onAdsResult:self withRet:kAdsDismissed withMsg:@"Ads will be dismissed"];
}

@end
