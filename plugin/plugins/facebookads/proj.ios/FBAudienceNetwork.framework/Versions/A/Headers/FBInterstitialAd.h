/*
 * Copyright 2010-present Facebook.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#import "FBAdView.h"

@protocol FBInterstitialAdDelegate;

/*!
 @class FBInterstitialAd

 @abstract A modal view controller to represent a Facebook interstitial ad. This
 is a full-screen ad shown in your application.

 */
@interface FBInterstitialAd : UIViewController <FBAdViewDelegate>

/*!
 @property
 @abstract Typed access to the id of the ad placement.
 */
@property (nonatomic, copy, readonly) NSString *placementID;
/*!
 @property
 @abstract the delegate
 */
@property (nonatomic, weak) id<FBInterstitialAdDelegate> delegate;

/*!
 @method

 @abstract
 This is a method to initialize an FBInterstitialAd matching the given placement id.

 @param placementID The id of the ad placement. You can create your placement id from Facebook developers page.
 */
- (instancetype)initWithPlacementID:(NSString *)placementID;
/*!
 @method

 @abstract
 Returns true if the interstitial ad has been successfully loaded.

 @discussion You should check `isAdValid` before trying to show the ad.
 */
- (BOOL)isAdValid;
/*!
 @method

 @abstract
 Begins loading the FBInterstitialAd content.

 @discussion You can implement `interstitialAdDidLoad:` and `interstitialAd:didFailWithError:` methods
 of `FBInterstitialAdDelegate` if you would like to be notified as loading succeeds or fails.
 */
- (void)loadAd;
/*!
 @method

 @abstract
 Presents the interstitial ad modally from the specified view controller.

 @param rootViewController The view controller that will be used to present the interstitial ad.

 @discussion You can implement `interstitialAdDidClick:`, `interstitialAdWillClose:` and `interstitialAdWillClose`
 methods of `FBInterstitialAdDelegate` if you would like to stay informed for thoses events
 */
- (BOOL)showAdFromRootViewController:(UIViewController *)rootViewController;

@end

/*!
 @protocol

 @abstract
 The methods declared by the FBInterstitialAdDelegate protocol allow the adopting delegate to respond
 to messages from the FBInterstitialAd class and thus respond to operations such as whether the
 interstitial ad has been loaded, user has clicked or closed the interstitial.
 */
@protocol FBInterstitialAdDelegate <NSObject>

@optional

/*!
 @method

 @abstract
 Sent after an ad in the FBInterstitialAd object is clicked. The appropriate app store view or
 app browser will be launched.

 @param interstitialAd An FBInterstitialAd object sending the message.
 */
- (void)interstitialAdDidClick:(FBInterstitialAd *)interstitialAd;
/*!
 @method

 @abstract
 Sent after an FBInterstitialAd object has been dismissed from the screen, returning control
 to your application.

 @param interstitialAd An FBInterstitialAd object sending the message.
 */
- (void)interstitialAdDidClose:(FBInterstitialAd *)interstitialAd;
/*!
 @method

 @abstract
 Sent immediately before an FBInterstitialAd object will be dismissed from the screen.

 @param interstitialAd An FBInterstitialAd object sending the message.
 */
- (void)interstitialAdWillClose:(FBInterstitialAd *)interstitialAd;
/*!
 @method

 @abstract
 Sent when an FBInterstitialAd successfully loads an ad.

 @param interstitialAd An FBInterstitialAd object sending the message.
 */
- (void)interstitialAdDidLoad:(FBInterstitialAd *)interstitialAd;
/*!
 @method

 @abstract
 Sent when an FBInterstitialAd failes to load an ad.

 @param interstitialAd An FBInterstitialAd object sending the message.
 @param error An error object containing details of the error.
 */
- (void)interstitialAd:(FBInterstitialAd *)interstitialAd didFailWithError:(NSError *)error;

@end
