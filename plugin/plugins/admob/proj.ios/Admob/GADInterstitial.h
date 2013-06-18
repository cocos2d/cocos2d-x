//
//  GADInterstitial.h
//  Google AdMob Ads SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "GADInterstitialDelegate.h"
#import "GADRequest.h"
#import "GADRequestError.h"

// An interstitial ad.  This is a full-screen advertisement shown at natural
// transition points in your application such as between game levels or news
// stories.
//
// Interstitials are shown sparingly.  Expect low to no fill.
@interface GADInterstitial : NSObject

#pragma mark Pre-Request

// Required value created in the AdSense website.  Create a new ad unit for
// every unique placement of an ad in your application.  Set this to the ID
// assigned for this placement.  Ad units are important for targeting and stats.
// Example values for different request types:
//   AdMob: a0123456789ABCD
//     DFP: /0123/ca-pub-0123456789012345/my-ad-identifier
// AdSense: ca-mb-app-pub-0123456789012345/my-ad-identifier
@property (nonatomic, copy) NSString *adUnitID;

// Optional delegate object that receives state change notifications from this
// GADInterstitalAd.  Remember to nil the delegate before deallocating this
// object.
@property (nonatomic, assign) NSObject<GADInterstitialDelegate> *delegate;

#pragma mark Making an Ad Request

// Makes an interstitial ad request.  Additional targeting options can be
// supplied with a request object.  Only one interstitial request is allowed at
// a time.
//
// This is best to do several seconds before the interstitial is needed to
// preload its content.  Then when transitioning between view controllers show
// the interstital with presentFromViewController.
- (void)loadRequest:(GADRequest *)request;

#pragma mark Request at Application Launch

// The |window| will be shown with the |image| displayed until either the
// |request| interstitial is shown or a timeout occurs.  The delegate will
// receive an interstitialDidDismissScreen: callback to indicate that your app
// should continue when the interstitial has finished.
- (void)loadAndDisplayRequest:(GADRequest *)request
                  usingWindow:(UIWindow *)window
                 initialImage:(UIImage *)image;

#pragma mark Post-Request

// Returns YES if the interstitial is ready to be displayed.  The delegate's
// interstitialAdDidReceiveAd: will be called when this switches from NO to YES.
@property (nonatomic, readonly) BOOL isReady;

// Returns YES if the interstitial object has already shown an interstitial.
// Note that an interstitial object can only be used once even with different
// requests.
@property (nonatomic, readonly) BOOL hasBeenUsed;

// Presents the interstitial ad which takes over the entire screen until the
// user dismisses it.  This has no effect unless isReady returns YES and/or the
// delegate's interstitialDidReceiveAd: has been received.
//
// Set rootViewController to the current view controller at the time this method
// is called.  If your application does not use view controllers pass in nil and
// your views will be removed from the window to show the interstitial and
// restored when done.  After the interstitial has been removed, the delegate's
// interstitialDidDismissScreen: will be called.
- (void)presentFromRootViewController:(UIViewController *)rootViewController;

@end
