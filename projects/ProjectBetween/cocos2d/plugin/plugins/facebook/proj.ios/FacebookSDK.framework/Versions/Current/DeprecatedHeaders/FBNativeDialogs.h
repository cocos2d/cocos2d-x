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

#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#import "FBAppCall.h"
#import "FBOpenGraphActionShareDialogParams.h"
#import "FBShareDialogParams.h"

@class FBSession;
@protocol FBOpenGraphAction;

// note that the following class and types are deprecated in favor of FBDialogs and its methods

/*!
 @typedef FBNativeDialogResult enum

 @abstract
 Please note that this enum and its related methods have been deprecated, please migrate your
 code to use `FBOSIntegratedShareDialogResult` and its related methods.
 */
typedef NS_ENUM(NSUInteger, FBNativeDialogResult) {
    /*! Indicates that the dialog action completed successfully. */
    FBNativeDialogResultSucceeded,
    /*! Indicates that the dialog action was cancelled (either by the user or the system). */
    FBNativeDialogResultCancelled,
    /*! Indicates that the dialog could not be shown (because not on ios6 or ios6 auth was not used). */
    FBNativeDialogResultError
}
__attribute__((deprecated));

/*!
 @typedef

 @abstract
 Please note that `FBShareDialogHandler` and its related methods have been deprecated, please migrate your
 code to use `FBOSIntegratedShareDialogHandler` and its related methods.
 */
typedef void (^FBShareDialogHandler)(FBNativeDialogResult result, NSError *error)
__attribute__((deprecated));

/*!
 @class FBNativeDialogs

 @abstract
 Please note that `FBNativeDialogs` has been deprecated, please migrate your
 code to use `FBDialogs`.
 */
@interface FBNativeDialogs : NSObject

/*!
 @abstract
 Please note that this method has been deprecated, please migrate your
 code to use `FBDialogs` and the related method `presentOSIntegratedShareDialogModallyFrom`.
 */
+ (BOOL)presentShareDialogModallyFrom:(UIViewController *)viewController
                          initialText:(NSString *)initialText
                                image:(UIImage *)image
                                  url:(NSURL *)url
                              handler:(FBShareDialogHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Please note that this method has been deprecated, please migrate your
 code to use `FBDialogs` and the related method `presentOSIntegratedShareDialogModallyFrom`.
 */
+ (BOOL)presentShareDialogModallyFrom:(UIViewController *)viewController
                          initialText:(NSString *)initialText
                               images:(NSArray *)images
                                 urls:(NSArray *)urls
                              handler:(FBShareDialogHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Please note that this method has been deprecated, please migrate your
 code to use `FBDialogs` and the related method `presentOSIntegratedShareDialogModallyFrom`.
 */
+ (BOOL)presentShareDialogModallyFrom:(UIViewController *)viewController
                              session:(FBSession *)session
                          initialText:(NSString *)initialText
                               images:(NSArray *)images
                                 urls:(NSArray *)urls
                              handler:(FBShareDialogHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Please note that this method has been deprecated, please migrate your
 code to use `FBDialogs` and the related method `canPresentOSIntegratedShareDialogWithSession`.
 */
+ (BOOL)canPresentShareDialogWithSession:(FBSession *)session __attribute__((deprecated));

@end
