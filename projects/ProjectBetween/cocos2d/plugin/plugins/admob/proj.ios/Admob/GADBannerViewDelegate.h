//
//  GADBannerViewDelegate.h
//  Google AdMob Ads SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADModules.h"

@class GADRequestError;
@class GADBannerView;

/// Delegate for receiving state change messages from a GADBannerView such as ad requests
/// succeeding/failing or when an ad has been clicked.
@protocol GADBannerViewDelegate<NSObject>

@optional

#pragma mark Ad Request Lifecycle Notifications

/// Called when an ad request loaded an ad. This is a good opportunity to add this view to the
/// hierarchy if it has not been added yet. If the ad was received as a part of the server-side auto
/// refreshing, you can examine the hasAutoRefreshed property of the view.
- (void)adViewDidReceiveAd:(GADBannerView *)view;

/// Called when an ad request failed. Normally this is because no network connection was available
/// or no ads were available (i.e. no fill). If the error was received as a part of the server-side
/// auto refreshing, you can examine the hasAutoRefreshed property of the view.
- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error;

#pragma mark Click-Time Lifecycle Notifications

/// Called just before presenting the user a full screen view, such as a browser, in response to
/// clicking on an ad. Use this opportunity to stop animations, time sensitive interactions, etc.
///
/// Normally the user looks at the ad, dismisses it, and control returns to your application by
/// calling adViewDidDismissScreen:. However if the user hits the Home button or clicks on an App
/// Store link your application will end. On iOS 4.0+ the next method called will be
/// applicationWillResignActive: of your UIViewController
/// (UIApplicationWillResignActiveNotification). Immediately after that adViewWillLeaveApplication:
/// is called.
- (void)adViewWillPresentScreen:(GADBannerView *)adView;

/// Called just before dismissing a full screen view.
- (void)adViewWillDismissScreen:(GADBannerView *)adView;

/// Called just after dismissing a full screen view. Use this opportunity to restart anything you
/// may have stopped as part of adViewWillPresentScreen:.
- (void)adViewDidDismissScreen:(GADBannerView *)adView;

/// Called just before the application will background or terminate because the user clicked on an
/// ad that will launch another application (such as the App Store). The normal
/// UIApplicationDelegate methods, like applicationDidEnterBackground:, will be called immediately
/// before this.
- (void)adViewWillLeaveApplication:(GADBannerView *)adView;

@end
