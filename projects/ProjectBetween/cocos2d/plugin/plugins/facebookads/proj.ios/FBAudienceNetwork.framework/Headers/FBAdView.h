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

#import <StoreKit/StoreKit.h>
#import <UIKit/UIKit.h>

@protocol FBAdViewDelegate;

/*!
 @typedef FBAdSize

 @abstract
 Represents the ad size.
 */
typedef struct FBAdSize {
  CGSize size;
} FBAdSize;

/*!
 @abstract Represents the fixed banner ad size - 320pt by 50pt.
 */
extern FBAdSize const kFBAdSize320x50;

/*!
 @abstract Represents the flexible banner ad size, where banner width depends on
 its container width, and banner height is fixed as 50pt.
 */
extern FBAdSize const kFBAdSizeHeight50Banner;

/*!
 @abstract Represents the flexible banner ad size, where banner width depends on
 its container width, and banner height is fixed as 90pt.
 */
extern FBAdSize const kFBAdSizeHeight90Banner;

/*!
 @abstract Represents the interstitial ad size.
 */
extern FBAdSize const kFBAdSizeInterstital;

/*!
 @class FBAdView

 @abstract A customized UIView to represent a Facebook ad (a.k.a. banner ad).
 */
@interface FBAdView : UIView <UIWebViewDelegate>

/*!
 @method

 @abstract
 This is a method to initialize an FBAdView matching the given placement id.

 @param placementID The id of the ad placement. You can create your placement id from Facebook developers page.
 @param adSize The size of the ad; for example, kFBAdSizeHeight50Banner or kFBAdSizeHeight90Banner.
 @param rootViewController The view controller that will be used to present the ad and the app store view.
 */
- (instancetype)initWithPlacementID:(NSString *)placementID
                             adSize:(FBAdSize)adSize
                 rootViewController:(UIViewController *)viewController;

/*!
 @method

 @abstract
 Begins loading the FBAdView content.

 @discussion You can implement `adViewDidLoad:` and `adView:didFailWithError:` methods
 of `FBAdViewDelegate` if you would like to be notified as loading succeeds or fails.
 */
- (void)loadAd;

/*!
 @property
 @abstract Typed access to the id of the ad placement.
 */
@property (nonatomic, copy, readonly) NSString *placementID;
/*!
 @property
 @abstract Typed access to the app's root view controller.
 */
@property (nonatomic, weak, readonly) UIViewController *rootViewController;
/*!
 @property
 @abstract the delegate
 */
@property (nonatomic, weak) id<FBAdViewDelegate> delegate;

@end

/*!
 @protocol

 @abstract
 The methods declared by the FBAdViewDelegate protocol allow the adopting delegate to respond
 to messages from the FBAdView class and thus respond to operations such as whether the ad has
 been loaded, the person has clicked the ad.
 */
@protocol FBAdViewDelegate <NSObject>

@optional

/*!
 @method

 @abstract
 Sent after an ad has been clicked by the person.

 @param adView An FBAdView object sending the message.
 */
- (void)adViewDidClick:(FBAdView *)adView;
/*!
 @method

 @abstract
 When an ad is clicked, the modal view will be presented. And when the user finishes the
 interaction with the modal view and dismiss it, this message will be sent, returning control
 to the application.

 @param adView An FBAdView object sending the message.
 */
- (void)adViewDidFinishHandlingClick:(FBAdView *)adView;
/*!
 @method

 @abstract
 Sent when an ad has been successfully loaded.

 @param adView An FBAdView object sending the message.
 */
- (void)adViewDidLoad:(FBAdView *)adView;
/*!
 @method

 @abstract
 Sent after an FBAdView fails to load the ad.

 @param adView An FBAdView object sending the message.
 @param error An error object containing details of the error.
 */
- (void)adView:(FBAdView *)adView didFailWithError:(NSError *)error;

/*!
 @method

 @abstract
 Asks the delegate for a view controller to present modal content, such as the in-app
 browser that can appear when an ad is clicked.

 @return A view controller that is used to present modal content.
 */
- (UIViewController *)viewControllerForPresentingModalView;

@end

