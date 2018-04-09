/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#import "AdsFacebook.h"
#import "AdsWrapper.h"


#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation AdsFacebook

@synthesize debug = __debug;
@synthesize strPublishID = __PublishID;
@synthesize testDeviceIDs = __TestDeviceIDs;

- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo
{
    self.strPublishID = (NSString*) [devInfo objectForKey:@"FacebookAdID"];
}

- (void) showAds: (NSMutableDictionary*) info position:(int) pos
{
    if (self.strPublishID == nil ||
        [self.strPublishID length] == 0) {
        OUTPUT_LOG(@"configDeveloperInfo() not correctly invoked in FBAd!");
        return;
    }
    
    if (self.debug){
        
        // The hash ID is printed to console when running on a device.
        //[self addTestDevice:@"Your device Hash ID"];
    }
    
    NSString* strType = [info objectForKey:@"FBAdType"];
    int type = [strType intValue];
    switch (type) {
        case kTypeBanner:
        {
            NSString* strSize = [info objectForKey:@"FBAdSizeEnum"];
            int sizeEnum = [strSize intValue];
            [self showBanner:sizeEnum atPos:pos];
            break;
        }
        case kTypeInterstitial:
            [self loadInterstial];
            break;
        default:
            OUTPUT_LOG(@"The value of 'FBAdType' is wrong (should be 1 or 2)");
            break;
    }
}

- (void) hideAds: (NSMutableDictionary*) info
{
    NSString* strType = [info objectForKey:@"FBAdType"];
    int type = [strType intValue];
    switch (type)
    {
        case kTypeBanner:
        {
            if (nil != self.bannerView) {
                [self.bannerView removeFromSuperview];
                self.bannerView = nil;
            }
            break;
        }
        case kTypeInterstitial:
            OUTPUT_LOG(@"Now not support full screen view in FBAd");
            break;
        default:
            OUTPUT_LOG(@"The value of 'FBAdType' is wrong (should be 1 or 2)");
            break;
    }
}

- (void) queryPoints
{
    OUTPUT_LOG(@"FBAd not support query points!");
}

- (void) spendPoints: (int) points
{
    OUTPUT_LOG(@"FBAd not support spend points!");
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    self.debug = isDebugMode;
}

- (NSString*) getSDKVersion
{
    return @"3.17.1";
}

- (NSString*) getPluginVersion
{
    return @"1.0";
}

- (void) showBanner:(int)sizeEnum atPos:(int)pos
{
    FBAdSize size = kFBAdSize320x50;
    switch (sizeEnum)
    {
        case kSizeDefault:
            size = kFBAdSize320x50;
            break;

        case kSizeHeightFixed:
        case kSizeInterstital:
        {
            BOOL isIPAD = ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad);
            size = (isIPAD) ? kFBAdSizeHeight90Banner : kFBAdSizeHeight50Banner;
        }
            break;
        default:
            break;
    }
    
    if (nil != self.bannerView) {
        [self.bannerView removeFromSuperview];
        self.bannerView = nil;
    }
    
    
    // Create a banner's ad view with a unique placement ID (generate your own on the Facebook app settings).
    // Use different ID for each ad placement in your app.
    self.bannerView = [[FBAdView alloc] initWithPlacementID:self.strPublishID
                                                     adSize:size
                                         rootViewController:[AdsWrapper getCurrentRootViewController]];
    
    
    // Set a delegate to get notified on changes or when the user interact with the ad.
    self.bannerView.delegate = self;
    
    // When testing on a device, add its hashed ID to force test ads.
    [FBAdSettings addTestDevices:self.testDeviceIDs];
    
    // Initiate a request to load an ad.
    [self.bannerView loadAd];
    
    [AdsWrapper addAdView:self.bannerView atPos:pos];
}

- (void) loadInterstial
{
    // Create the interstitial unit with a placement ID (generate your own on the Facebook app settings).
    // Use different ID for each ad placement in your app.
    self.interstitialView = [[FBInterstitialAd alloc] initWithPlacementID:self.strPublishID];
    
    // Set a delegate to get notified on changes or when the user interact with the ad.
    self.interstitialView.delegate = self;
    
    [FBAdSettings addTestDevices:self.testDeviceIDs];
    
    // Initiate the request to load the ad.
    [self.interstitialView loadAd];
}

- (void) showInterstitial
{
    if (!self.interstitialView || !self.interstitialView.isAdValid)
    {
        // Ad not ready to present.
        OUTPUT_LOG(@"Ad not loaded.");
        
    } else {
        
        // Ad is ready, present it!
        [self.interstitialView showAdFromRootViewController:[AdsWrapper getCurrentRootViewController]];
        [AdsWrapper onAdsResult:self withRet:kAdsShown withMsg:@"Ads is shown!"];

    }

}

- (void) addTestDevice: (NSString*) deviceID
{
    if (nil == self.testDeviceIDs) {
        self.testDeviceIDs = [[NSMutableArray alloc] init];
    }
    [self.testDeviceIDs addObject:deviceID];
}


#pragma mark - FBViewAdDelegate implementation

- (void)adViewDidClick:(FBAdView *)adView
{
    OUTPUT_LOG(@"Ad was clicked.");
}

- (void)adViewDidFinishHandlingClick:(FBAdView *)adView
{
    OUTPUT_LOG(@"Ad did finish click handling.");
}

- (void)adViewDidLoad:(FBAdView *)adView
{
    OUTPUT_LOG(@"Ad was loaded.");
    
    // Now that the ad was loaded, show the view in case it was hidden before.
    adView.hidden = NO;
    [AdsWrapper onAdsResult:self withRet:kAdsReceived withMsg:@"Ad request received success!"];
}

- (void)adView:(FBAdView *)adView didFailWithError:(NSError *)error
{
    OUTPUT_LOG(@"Ad failed to load with error: %@", error);
    
    // Hide the unit since no ad is shown.
    adView.hidden = YES;
    [AdsWrapper onAdsResult:self withRet:kUnknownError withMsg:error.localizedDescription];

}

#pragma mark - FBInterstitialAdDelegate implementation

- (void)interstitialAdDidLoad:(FBInterstitialAd *)interstitialAd
{
    OUTPUT_LOG(@"Interstitial ad was loaded. Can present now.");
    
    [AdsWrapper onAdsResult:self withRet:kAdsReceived withMsg:@"Interstitial Ad request received success!"];
    [self showInterstitial];
}

- (void)interstitialAd:(FBInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
    OUTPUT_LOG(@"Interstitial failed to load with error: %@", error.description);
    [AdsWrapper onAdsResult:self withRet:kUnknownError withMsg:error.description];

}

- (void)interstitialAdDidClick:(FBInterstitialAd *)interstitialAd
{
    OUTPUT_LOG(@"Interstitial was clicked.");
}

- (void)interstitialAdDidClose:(FBInterstitialAd *)interstitialAd
{
    OUTPUT_LOG(@"Interstitial closed.");
    
    // Optional, Cleaning up.
    self.interstitialView = nil;
    
    [AdsWrapper onAdsResult:self withRet:kAdsDismissed withMsg:@"Interstitial Ad is dismissed!"];

}

- (void)interstitialAdWillClose:(FBInterstitialAd *)interstitialAd
{
    OUTPUT_LOG(@"Interstitial will close.");
}


@end
