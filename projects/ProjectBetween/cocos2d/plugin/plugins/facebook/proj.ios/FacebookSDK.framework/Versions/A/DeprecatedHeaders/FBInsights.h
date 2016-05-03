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

#import "FBSDKMacros.h"
#import "FBSession.h"

/*!
 @typedef FBInsightsFlushBehavior enum

 @abstract This enum has been deprecated in favor of FBAppEventsFlushBehavior.
 */
__attribute__ ((deprecated("use FBAppEventsFlushBehavior instead")))
typedef NS_ENUM(NSUInteger, FBInsightsFlushBehavior) {
    FBInsightsFlushBehaviorAuto __attribute__ ((deprecated("use FBAppEventsFlushBehaviorAuto instead"))),
    FBInsightsFlushBehaviorExplicitOnly __attribute__ ((deprecated("use FBAppEventsFlushBehaviorExplicitOnly instead"))),
};

FBSDK_EXTERN NSString *const FBInsightsLoggingResultNotification __attribute__((deprecated));

/*!
 @class FBInsights

 @abstract This class has been deprecated in favor of FBAppEvents.
 */
__attribute__ ((deprecated("Use the FBAppEvents class instead")))
@interface FBInsights : NSObject

+ (NSString *)appVersion __attribute__((deprecated));
+ (void)setAppVersion:(NSString *)appVersion __attribute__((deprecated("use [FBSettings setAppVersion] instead")));

+ (void)logPurchase:(double)purchaseAmount currency:(NSString *)currency __attribute__((deprecated("use [FBAppEvents logPurchase] instead")));
+ (void)logPurchase:(double)purchaseAmount currency:(NSString *)currency parameters:(NSDictionary *)parameters __attribute__((deprecated("use [FBAppEvents logPurchase] instead")));
+ (void)logPurchase:(double)purchaseAmount currency:(NSString *)currency parameters:(NSDictionary *)parameters session:(FBSession *)session __attribute__((deprecated("use [FBAppEvents logPurchase] instead")));

+ (void)logConversionPixel:(NSString *)pixelID valueOfPixel:(double)value __attribute__((deprecated));
+ (void)logConversionPixel:(NSString *)pixelID valueOfPixel:(double)value session:(FBSession *)session __attribute__((deprecated));

+ (FBInsightsFlushBehavior)flushBehavior __attribute__((deprecated("use [FBAppEvents flushBehavior] instead")));
+ (void)setFlushBehavior:(FBInsightsFlushBehavior)flushBehavior __attribute__((deprecated("use [FBAppEvents setFlushBehavior] instead")));

+ (void)flush __attribute__((deprecated("use [FBAppEvents flush] instead")));

@end
