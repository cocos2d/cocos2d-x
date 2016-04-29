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

#import <UIKit/UIKit.h>

#import "FBSession.h"
#import "FBViewController.h"

/*!
 @protocol

 @abstract
 The `FBUserSettingsDelegate` protocol defines the methods called by a <FBUserSettingsViewController>.
 */
@protocol FBUserSettingsDelegate <FBViewControllerDelegate>

@optional

/*!
 @abstract
 Called when the view controller will log the user out in response to a button press.

 @param sender          The view controller sending the message.
 */
- (void)loginViewControllerWillLogUserOut:(id)sender;

/*!
 @abstract
 Called after the view controller logged the user out in response to a button press.

 @param sender          The view controller sending the message.
 */
- (void)loginViewControllerDidLogUserOut:(id)sender;

/*!
 @abstract
 Called when the view controller will log the user in in response to a button press.
 Note that logging in can fail for a number of reasons, so there is no guarantee that this
 will be followed by a call to loginViewControllerDidLogUserIn:. Callers wanting more granular
 notification of the session state changes can use KVO or the NSNotificationCenter to observe them.

 @param sender          The view controller sending the message.
 */
- (void)loginViewControllerWillAttemptToLogUserIn:(id)sender;

/*!
 @abstract
 Called after the view controller successfully logged the user in in response to a button press.

 @param sender          The view controller sending the message.
 */
- (void)loginViewControllerDidLogUserIn:(id)sender;

/*!
 @abstract
 Called if the view controller encounters an error while trying to log a user in.

 @param sender          The view controller sending the message.
 @param error           The error encountered.
 @discussion See https://developers.facebook.com/docs/technical-guides/iossdk/errors/
 for error handling best practices.
 */
- (void)loginViewController:(id)sender receivedError:(NSError *)error;

@end


/*!
 @class FBUserSettingsViewController

 @abstract
 The `FBUserSettingsViewController` class provides a user interface exposing a user's
 Facebook-related settings. Currently, this is limited to whether they are logged in or out
 of Facebook.

 Because of the size of some graphics used in this view, its resources are packaged as a separate
 bundle. In order to use `FBUserSettingsViewController`, drag the `FBUserSettingsViewResources.bundle`
 from the SDK directory into your Xcode project.
 */
@interface FBUserSettingsViewController : FBViewController

/*!
 @abstract
 The permissions to request if the user logs in via this view.
 */
@property (nonatomic, copy) NSArray *permissions __attribute__((deprecated));

/*!
 @abstract
 The read permissions to request if the user logs in via this view.

 @discussion
 Note, that if read permissions are specified, then publish permissions should not be specified.
 */
@property (nonatomic, copy) NSArray *readPermissions;

/*!
 @abstract
 The publish permissions to request if the user logs in via this view.

 @discussion
 Note, that a defaultAudience value of FBSessionDefaultAudienceOnlyMe, FBSessionDefaultAudienceEveryone, or
 FBSessionDefaultAudienceFriends should be set if publish permissions are specified. Additionally, when publish
 permissions are specified, then read should not be specified.
 */
@property (nonatomic, copy) NSArray *publishPermissions;

/*!
 @abstract
 The default audience to use, if publish permissions are requested at login time.
 */
@property (nonatomic, assign) FBSessionDefaultAudience defaultAudience;

@end

