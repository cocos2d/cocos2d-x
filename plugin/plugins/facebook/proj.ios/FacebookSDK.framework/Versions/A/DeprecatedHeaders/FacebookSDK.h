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

// core
#import "FBAccessTokenData.h"
#import "FBAppCall.h"
#import "FBAppEvents.h"
#import "FBCacheDescriptor.h"
#import "FBDialogs.h"
#import "FBError.h"
#import "FBErrorUtility.h"
#import "FBFrictionlessRecipientCache.h"
#import "FBFriendPickerViewController.h"
#import "FBGraphLocation.h"
#import "FBGraphObject.h"           // + design summary for graph component-group
#import "FBGraphPlace.h"
#import "FBGraphUser.h"
#import "FBInsights.h"
#import "FBLikeControl.h"
#import "FBLoginView.h"
#import "FBNativeDialogs.h"         // deprecated, use FBDialogs.h
#import "FBOpenGraphAction.h"
#import "FBOpenGraphActionShareDialogParams.h"
#import "FBOpenGraphObject.h"
#import "FBPlacePickerViewController.h"
#import "FBProfilePictureView.h"
#import "FBRequest.h"
#import "FBSession.h"
#import "FBSessionTokenCachingStrategy.h"
#import "FBSettings.h"
#import "FBShareDialogParams.h"
#import "FBShareDialogPhotoParams.h"
#import "FBTaggableFriendPickerViewController.h"
#import "FBUserSettingsViewController.h"
#import "FBWebDialogs.h"
#import "NSError+FBError.h"

/*!
 @header

 @abstract  Library header, import this to import all of the public types
            in the Facebook SDK

 @discussion

////////////////////////////////////////////////////////////////////////////////


 Summary: this header summarizes the structure and goals of the Facebook SDK for iOS.
 Goals:
 * Leverage and work well with modern features of iOS (e.g. blocks, ARC, etc.)
 * Patterned after best of breed iOS frameworks (e.g. naming, pattern-use, etc.)
 * Common integration experience is simple & easy to describe
 * Factored to enable a growing list of scenarios over time

 Notes on approaches:
 1. We use a key scenario to drive prioritization of work for a given update
 2. We are building-atop and refactoring, rather than replacing, existing iOS SDK releases
 3. We use take an incremental approach where we can choose to maintain as little or as much compatibility with the existing SDK needed
    a) and so we will be developing to this approach
    b) and then at push-time for a release we will decide when/what to break
         on a feature by feature basis
 4. Some light but critical infrastructure is needed to support both the goals
    and the execution of this change (e.g. a build/package/deploy process)

 Design points:
 We will move to a more object-oriented approach, in order to facilitate the
 addition of a different class of objects, such as controls and visual helpers
 (e.g. FBLikeView, FBPersonView), as well as sub-frameworks to enable scenarios
 such (e.g. FBOpenGraphEntity, FBLocalEntityCache, etc.)

 As we add features, it will no longer be appropriate to host all functionality
 in the Facebook class, though it will be maintained for some time for migration
 purposes. Instead functionality lives in related collections of classes.

 <pre>
 @textblock

               *------------* *----------*  *----------------* *---*
  Scenario --> |FBPersonView| |FBLikeView|  | FBPlacePicker  | | F |
               *------------* *----------*  *----------------* | a |
               *-------------------*  *----------*  *--------* | c |
 Component --> |   FBGraphObject   |  | FBDialog |  | FBView | | e |
               *-------------------*  *----------*  *--------* | b |
               *---------* *---------* *---------------------* | o |
      Core --> |FBSession| |FBRequest| |Utilities (e.g. JSON)| | o |
               *---------* *---------* *---------------------* * k *

 @/textblock
 </pre>

 The figure above describes three layers of functionality, with the existing
 Facebook on the side as a helper proxy to a subset of the overall SDK. The
 layers loosely organize the SDK into *Core Objects* necessary to interface
 with Facebook, higher-level *Framework Components* that feel like natural
 extensions to existing frameworks such as UIKit and Foundation, but which
 surface behavior broadly applicable to Facebook, and finally the
 *Scenario Objects*, which provide deeper turn-key capibilities for useful
 mobile scenarios.

 Use example (low barrier use case):

 <pre>
 @textblock

// log on to Facebook
[FBSession sessionOpenWithPermissions:nil
                    completionHandler:^(FBSession *session,
                                        FBSessionState status,
                                        NSError *error) {
                        if (session.isOpen) {
                            // request basic information for the user
                            [FBRequestConnection startWithGraphPath:@"me"
                                                  completionHandler:^void(FBRequestConnection *request,
                                                                          id result,
                                                                          NSError *error) {
                                                      if (!error) {
                                                          // get json from result
                                                      }
                                                  }];
                        }
                    }];
 @/textblock
 </pre>

 */

#define FB_IOS_SDK_VERSION_STRING @"3.18"
#define FB_IOS_SDK_TARGET_PLATFORM_VERSION @"v2.1"

