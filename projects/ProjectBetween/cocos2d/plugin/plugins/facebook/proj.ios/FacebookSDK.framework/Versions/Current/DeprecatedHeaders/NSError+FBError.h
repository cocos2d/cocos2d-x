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

#import "FBError.h"

/*!
 @category NSError(FBError)

 @abstract
 Adds additional properties to NSError to provide more information for Facebook related errors.
 */
@interface NSError (FBError)

/*!
 @abstract
 Categorizes the error, if it is Facebook related, to simplify application mitigation behavior

 @discussion
 In general, in response to an error connecting to Facebook, an application should, retry the
 operation, request permissions, reconnect the application, or prompt the user to take an action.
 The error category can be used to understand the class of error received from Facebook.  For more infomation on this
 see https://developers.facebook.com/docs/reference/api/errors/
 */
@property (readonly) FBErrorCategory fberrorCategory;

/*!
 @abstract
 If YES indicates that a user action is required in order to successfully continue with the Facebook operation.

 @discussion
 In general if fberrorShouldNotifyUser is NO, then the application has a straightforward mitigation, such as
 retry the operation or request permissions from the user, etc. In some cases it is necessary for the user to
 take an action before the application continues to attempt a Facebook connection. For more infomation on this
 see https://developers.facebook.com/docs/reference/api/errors/
 */
@property (readonly) BOOL fberrorShouldNotifyUser;

/*!
 @abstract
 A message suitable for display to the user, describing a user action necessary to enable Facebook functionality.
 Not all Facebook errors yield a message suitable for user display; however in all cases where
 fberrorShouldNotifyUser is YES, this property returns a localizable message suitable for display.

 @see +[FBErrorUtility userMessageForError:]
 */
@property (readonly, copy) NSString *fberrorUserMessage;

/*!
 @abstract
 A short summary of this error suitable for display to the user.
 Not all Facebook errors yield a message/title suitable for user display;
 However in all cases when title is available, user should be notified.

 @see +[FBErrorUtility userTitleForError:]
 */
@property (readonly, copy) NSString *fberrorUserTitle;

/*!
 @abstract
 YES if this error is transient and may succeed if the initial action is retried as-is.
 Application may use this information to display a "Retry" button, if user should be notified about this error.
 */
@property (readonly) BOOL fberrorIsTransient;

@end
