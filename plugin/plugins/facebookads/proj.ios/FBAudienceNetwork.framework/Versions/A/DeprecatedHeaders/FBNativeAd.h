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

#import "FBAdImage.h"
#import "FBAdView.h"

@class FBAdRequest;
@protocol FBNativeAdDelegate;

/*!
 @class FBNativeAd

 @abstract
 The FBNativeAd represents ad metadata to allow you to construct custom ad views.
 See the NativeAdSample in the sample apps section of the Audience Network framework.
 */
@class FBNativeAd;

/*!
 @typedef FBNativeAdCompletionHandler

 @abstract
 The completion handler invoked when the ad is clicked.
 */
typedef void (^FBNativeAdCompletionHandler)(FBNativeAd *nativeAd);

@interface FBNativeAd : NSObject

/*!
 @property
 @abstract Typed access to the id of the ad placement.
 */
@property (nonatomic, copy, readonly) NSString *placementID;
/*!
 @property
 @abstract Typed access to the ad star rating. See `FBAdStarRating` for details.
 */
@property (nonatomic, assign, readonly) struct FBAdStarRating starRating;
/*!
 @property
 @abstract Typed access to the ad title.
 */
@property (nonatomic, copy, readonly) NSString *title;
/*!
 @property
 @abstract Typed access to the ad social context, for example "Over half a million users".
 */
@property (nonatomic, copy, readonly) NSString *socialContext;
/*!
 @property
 @abstract Typed access to the call to action phrase of the ad, for example "Install Now".
 */
@property (nonatomic, copy, readonly) NSString *callToAction;
/*!
 @property
 @abstract Typed access to the ad icon. See `FBAdImage` for details.
 */
@property (nonatomic, strong, readonly) FBAdImage *icon;
/*!
 @property
 @abstract Typed access to the ad cover image creative. See `FBAdImage` for details.
 */
@property (nonatomic, strong, readonly) FBAdImage *coverImage;
/*!
 @property
 @abstract Typed access to the body text, usually a longer description of the ad.
 */
@property (nonatomic, copy, readonly) NSString *body;
/*!
 @property
 @abstract the delegate
 */
@property (nonatomic, weak) id<FBNativeAdDelegate> delegate;

/* initialize an instance of FBNative Ad with a placement ID and a view controller */
/*!
 @method

 @abstract
 This is a method to initialize a FBNativeAd object matching the given placement id.

 @param placementID The id of the ad placement. You can create your placement id from Facebook developers page.
 */
- (instancetype)initWithPlacementID:(NSString *)placementID;

/*!
 @method

 @abstract
 This is a method to associate a FBNativeAd with the UIView you will use to display the native ads.

 @param view The UIView you created to render all the native ads data elements.
 @param viewController The UIViewController that will be used to present SKStoreProductViewController
 (iTunes Store product information).

 @discussion The whole area of the UIView will be clickable.
 */
- (void)registerViewForInteraction:(UIView *)view
                withViewController:(UIViewController *)viewController;

/*!
 @method

 @abstract
 This is a method to associate FBNativeAd with the UIView you will use to display the native ads
 and set clickable areas.

 @param view The UIView you created to render all the native ads data elements.
 @param viewController The UIViewController that will be used to present SKStoreProductViewController
 (iTunes Store product information).
 @param clickableViews An array of UIView you created to render the native ads data element, e.g.
 CallToAction button, Icon image, which you want to specify as clickable.
 */
- (void)registerViewForInteraction:(UIView *)view
                withViewController:(UIViewController *)viewController
                withClickableViews:(NSArray *)clickableViews;

/*!
 @method

 @abstract
 This is a method to disconnect a FBNativeAd with the UIView you used to display the native ads.
 */
- (void)unregisterView;

/*!
 @method

 @abstract
 Begins loading the FBNativeAd content.

 @discussion You can implement `nativeAdDidLoad:` and `nativeAd:didFailWithError:` methods
 of `FBNativeAdDelegate` if you would like to be notified as loading succeeds or fails.
 */
- (void)loadAd;

/*!
 @method

 @abstract
 Call isAdValid to check whether native ad is valid & internal consistent prior rendering using its properties. If
 rendering is done as part of the loadAd callback, it is guarantee to be consistent
 */
- (BOOL)isAdValid;

@end

/*!
 @protocol

 @abstract
 The methods declared by the FBNativeAdDelegate protocol allow the adopting delegate to respond to messages
 from the FBNativeAd class and thus respond to operations such as whether the native ad has been loaded.
 */
@protocol FBNativeAdDelegate <NSObject>

/*!
 @method

 @abstract
 Sent when an FBNativeAd has been successfully loaded.

 @param nativeAd An FBNativeAd object sending the message.
 */
- (void)nativeAdDidLoad:(FBNativeAd *)nativeAd;
/*!
 @method

 @abstract
 Sent when an FBNativeAd is failed to load.

 @param nativeAd An FBNativeAd object sending the message.
 @param error An error object containing details of the error.
 */
- (void)nativeAd:(FBNativeAd *)nativeAd didFailWithError:(NSError *)error;

/*!
 @method

 @abstract
 Sent after an ad has been clicked by the person.

 @param nativeAd An FBNativeAd object sending the message.
 */
- (void)nativeAdDidClick:(FBNativeAd *)nativeAd;
/*!
 @method

 @abstract
 When an ad is clicked, the modal view will be presented. And when the user finishes the
 interaction with the modal view and dismiss it, this message will be sent, returning control
 to the application.

 @param nativeAd An FBNativeAd object sending the message.
 */
- (void)nativeAdDidFinishHandlingClick:(FBNativeAd *)nativeAd;

@end

