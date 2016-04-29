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

@class FBFrictionlessRecipientCache;
@class FBSession;
@protocol FBWebDialogsDelegate;

/*!
 @typedef NS_ENUM (NSUInteger, FBWebDialogResult)

 @abstract
 Passed to a handler to indicate the result of a dialog being displayed to the user.

 @discussion Note `FBWebDialogResultDialogCompleted` is also used for cancelled operations.
*/
typedef NS_ENUM(NSUInteger, FBWebDialogResult) {
    /*! Indicates that the dialog action completed successfully. Note, that cancel operations represent completed dialog operations.
     The url argument may be used to distinguish between success and user-cancelled cases */
    FBWebDialogResultDialogCompleted = 0,
    /*! Indicates that the dialog operation was not completed. This occurs in cases such as the closure of the web-view using the X in the upper left corner. */
    FBWebDialogResultDialogNotCompleted
};

/*!
 @typedef

 @abstract Defines a handler that will be called in response to the web dialog
 being dismissed
 */
typedef void (^FBWebDialogHandler)(
    FBWebDialogResult result,
    NSURL *resultURL,
    NSError *error);

/*!
 @class FBWebDialogs

 @abstract
 Provides methods to display web based dialogs to the user.
*/
@interface FBWebDialogs : NSObject

/*!
 @abstract
 Presents a Facebook web dialog (https://developers.facebook.com/docs/reference/dialogs/ )
 such as feed or apprequest.

 @param session Represents the session to use for the dialog. May be nil, which uses
 the active session if present, or returns NO, if not.

 @param dialog Represents the dialog or method name, such as @"feed"

 @param parameters A dictionary of parameters to be passed to the dialog

 @param handler An optional handler that will be called when the dialog is dismissed. Note,
 that if the method returns NO, the handler is not called. May be nil.
 */
+ (void)presentDialogModallyWithSession:(FBSession *)session
                                 dialog:(NSString *)dialog
                             parameters:(NSDictionary *)parameters
                                handler:(FBWebDialogHandler)handler;

/*!
 @abstract
 Presents a Facebook web dialog (https://developers.facebook.com/docs/reference/dialogs/ )
 such as feed or apprequest.

 @param session Represents the session to use for the dialog. May be nil, which uses
 the active session if present, or returns NO, if not.

 @param dialog Represents the dialog or method name, such as @"feed"

 @param parameters A dictionary of parameters to be passed to the dialog

 @param handler An optional handler that will be called when the dialog is dismissed. Note,
 that if the method returns NO, the handler is not called. May be nil.

 @param delegate An optional delegate to allow for advanced processing of web based
 dialogs. See 'FBWebDialogsDelegate' for more details.
 */
+ (void)presentDialogModallyWithSession:(FBSession *)session
                                 dialog:(NSString *)dialog
                             parameters:(NSDictionary *)parameters
                                handler:(FBWebDialogHandler)handler
                               delegate:(id<FBWebDialogsDelegate>)delegate;

/*!
 @abstract
 Presents a Facebook apprequest dialog.

 @param session Represents the session to use for the dialog. May be nil, which uses
 the active session if present.

 @param message The required message for the dialog.

 @param title An optional title for the dialog.

 @param parameters A dictionary of additional parameters to be passed to the dialog. May be nil

 @param handler An optional handler that will be called when the dialog is dismissed. May be nil.
 */
+ (void)presentRequestsDialogModallyWithSession:(FBSession *)session
                                        message:(NSString *)message
                                          title:(NSString *)title
                                     parameters:(NSDictionary *)parameters
                                        handler:(FBWebDialogHandler)handler;

/*!
 @abstract
 Presents a Facebook apprequest dialog.

 @param session Represents the session to use for the dialog. May be nil, which uses
 the active session if present.

 @param message The required message for the dialog.

 @param title An optional title for the dialog.

 @param parameters A dictionary of additional parameters to be passed to the dialog. May be nil

 @param handler An optional handler that will be called when the dialog is dismissed. May be nil.

 @param friendCache An optional cache object used to enable frictionless sharing for a known set of friends. The
 cache instance should be preserved for the life of the session and reused for multiple calls to the present method.
 As the users set of friends enabled for frictionless sharing changes, this method auto-updates the cache.
 */
+ (void)presentRequestsDialogModallyWithSession:(FBSession *)session
                                        message:(NSString *)message
                                          title:(NSString *)title
                                     parameters:(NSDictionary *)parameters
                                        handler:(FBWebDialogHandler)handler
                                    friendCache:(FBFrictionlessRecipientCache *)friendCache;

/*!
 @abstract
 Presents a Facebook feed dialog.

 @param session Represents the session to use for the dialog. May be nil, which uses
 the active session if present.

 @param parameters A dictionary of additional parameters to be passed to the dialog. May be nil

 @param handler An optional handler that will be called when the dialog is dismissed. May be nil.
 */
+ (void)presentFeedDialogModallyWithSession:(FBSession *)session
                                 parameters:(NSDictionary *)parameters
                                    handler:(FBWebDialogHandler)handler;

@end

/*!
 @protocol

 @abstract
 The `FBWebDialogsDelegate` protocol enables the plugging of advanced behaviors into
 the presentation flow of a Facebook web dialog. Advanced uses include modification
 of parameters and application-level handling of links on the dialog. The
 `FBFrictionlessRequestFriendCache` class implements this protocol to add frictionless
 behaviors to a presentation of the request dialog.
 */
@protocol FBWebDialogsDelegate<NSObject>

@optional

/*!
 @abstract
 Called prior to the presentation of a web dialog

 @param dialog A string representing the method or dialog name of the dialog being presented.

 @param parameters A mutable dictionary of parameters which will be sent to the dialog.

 @param session The session object to use with the dialog.
 */
- (void)webDialogsWillPresentDialog:(NSString *)dialog
                         parameters:(NSMutableDictionary *)parameters
                            session:(FBSession *)session;

/*!
 @abstract
 Called when the user of a dialog clicks a link that would cause a transition away from the application.
 Your application may handle this method, and return NO if the URL handling will be performed by the application.

 @param dialog A string representing the method or dialog name of the dialog being presented.

 @param parameters A dictionary of parameters which were sent to the dialog.

 @param session The session object to use with the dialog.

 @param url The url in question, which will not be handled by the SDK if this method NO
 */
- (BOOL)webDialogsDialog:(NSString *)dialog
              parameters:(NSDictionary *)parameters
                 session:(FBSession *)session
     shouldAutoHandleURL:(NSURL *)url;

/*!
 @abstract
 Called when the dialog is about to be dismissed

 @param dialog A string representing the method or dialog name of the dialog being presented.

 @param parameters A dictionary of parameters which were sent to the dialog.

 @param session The session object to use with the dialog.

 @param result A pointer to a result, which may be read or changed by the handling method as needed

 @param url A pointer to a pointer to a URL representing the URL returned by the dialog, which may be read or changed by this mehthod

 @param error A pointer to a pointer to an error object which may be read or changed by this method as needed
 */
- (void)webDialogsWillDismissDialog:(NSString *)dialog
                         parameters:(NSDictionary *)parameters
                            session:(FBSession *)session
                             result:(FBWebDialogResult *)result
                                url:(NSURL **)url
                              error:(NSError **)error;

@end

