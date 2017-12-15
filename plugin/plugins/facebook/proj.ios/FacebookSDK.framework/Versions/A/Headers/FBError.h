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

/*!
 The NSError domain of all errors returned by the Facebook SDK.
*/
FBSDK_EXTERN NSString *const FacebookSDKDomain;

/*!
 The NSError domain of all errors surfaced by the Facebook SDK that
 were returned by the Facebook Application
 */
FBSDK_EXTERN NSString *const FacebookNativeApplicationDomain;

/*!
 The key in the userInfo NSDictionary of NSError where you can find
 the inner NSError (if any).
*/
FBSDK_EXTERN NSString *const FBErrorInnerErrorKey;

/*!
 The key in the userInfo NSDictionary of NSError for the parsed JSON response
 from the server. In case of a batch, includes the JSON for a single FBRequest.
*/
FBSDK_EXTERN NSString *const FBErrorParsedJSONResponseKey;

/*!
 The key in the userInfo NSDictionary of NSError indicating
 the HTTP status code of the response (if any).
*/
FBSDK_EXTERN NSString *const FBErrorHTTPStatusCodeKey;

/*!
 @typedef NS_ENUM (NSUInteger, FBErrorCode)
 @abstract Error codes returned by the Facebook SDK in NSError.

 @discussion
 These are valid only in the scope of FacebookSDKDomain.
 */
typedef NS_ENUM(NSInteger, FBErrorCode) {
    /*!
     Like nil for FBErrorCode values, represents an error code that
     has not been initialized yet.
     */
    FBErrorInvalid = 0,

    /*! The operation failed because it was cancelled. */
    FBErrorOperationCancelled,

    /*! A login attempt failed */
    FBErrorLoginFailedOrCancelled,

    /*! The graph API returned an error for this operation. */
    FBErrorRequestConnectionApi,

    /*!
     The operation failed because the server returned an unexpected
     response.  You can get this error if you are not using the most
     recent SDK, or if you set your application's migration settings
     incorrectly for the version of the SDK you are using.

     If this occurs on the current SDK with proper app migration
     settings, you may need to try changing to one request per batch.
     */
    FBErrorProtocolMismatch,

    /*! Non-success HTTP status code was returned from the operation. */
    FBErrorHTTPError,

    /*! An endpoint that returns a binary response was used with FBRequestConnection.
     Endpoints that return image/jpg, etc. should be accessed using NSURLRequest */
    FBErrorNonTextMimeTypeReturned,

    /*! An error occurred while trying to display a native dialog */
    FBErrorDialog,

    /*! An error occurred using the FBAppEvents class */
    FBErrorAppEvents,

    /*! An error occurred related to an iOS API call */
    FBErrorSystemAPI,

    /*!
     The application had its applicationDidBecomeActive: method called while waiting
     on a response from the native Facebook app for a pending FBAppCall.
     */
    FBErrorAppActivatedWhilePendingAppCall,

    /*!
     The application had its openURL: method called from a source that was not a
     Facebook app and with a URL that was intended for the AppBridge
     */
    FBErrorUntrustedURL,

    /*!
     The URL passed to FBAppCall, was not able to be parsed
     */
    FBErrorMalformedURL,

    /*!
     The operation failed because the session is currently busy reconnecting.
    */
    FBErrorSessionReconnectInProgess,

    /*!
     Reserved for future use.
    */
    FBErrorOperationDisallowedForRestrictedTreatment,
};

/*!
 @typedef NS_ENUM (NSUInteger, FBNativeApplicationErrorCode)
 @abstract Error codes returned by the Facebook SDK in NSError.

 @discussion
 These are valid only in the scope of FacebookNativeApplicationDomain.
 */
typedef NS_ENUM(NSUInteger, FBNativeApplicationErrorCode) {
    /*! A general error in processing an FBAppCall, without a known cause. Unhandled exceptions are a good example */
    FBAppCallErrorUnknown = 1,

    /*! The FBAppCall cannot be processed for some reason */
    FBAppCallErrorUnsupported = 2,

    /*! The FBAppCall is for a method that does not exist (or is turned off) */
    FBAppCallErrorUnknownMethod = 3,

    /*! The FBAppCall cannot be processed at the moment, but can be retried at a later time. */
    FBAppCallErrorServiceBusy = 4,

    /*! Share was called in the native Facebook app with incomplete or incorrect arguments */
    FBShareErrorInvalidParam = 100,

    /*! A server error occurred while calling Share in the native Facebook app. */
    FBShareErrorServer = 102,

    /*! An unknown error occurred while calling Share in the native Facebook app. */
    FBShareErrorUnknown = 103,

    /*! Disallowed from calling Share in the native Facebook app. */
    FBShareErrorDenied = 104,
};

/*!
 @typedef NS_ENUM (NSInteger, FBErrorCategory)

 @abstract Indicates the Facebook SDK classification for the error

 @discussion
 */
typedef NS_ENUM(NSInteger, FBErrorCategory) {
    /*! Indicates that the error category is invalid and likely represents an error that
     is unrelated to Facebook or the Facebook SDK */
    FBErrorCategoryInvalid                      = 0,
    /*! Indicates that the error may be authentication related but the application should retry the operation.
     This case may involve user action that must be taken, and so the application should also test
     the fberrorShouldNotifyUser property and if YES display fberrorUserMessage to the user before retrying.*/
    FBErrorCategoryRetry          = 1,
    /*! Indicates that the error is authentication related and the application should reopen the session */
    FBErrorCategoryAuthenticationReopenSession  = 2,
    /*! Indicates that the error is permission related */
    FBErrorCategoryPermissions                  = 3,
    /*! Indicates that the error implies that the server had an unexpected failure or may be temporarily down */
    FBErrorCategoryServer                       = 4,
    /*! Indicates that the error results from the server throttling the client */
    FBErrorCategoryThrottling                   = 5,
    /*! Indicates the user cancelled the operation */
    FBErrorCategoryUserCancelled                = 6,
    /*! Indicates that the error is Facebook-related but is uncategorizable, and likely newer than the
     current version of the SDK */
    FBErrorCategoryFacebookOther                = -1,
    /*! Indicates that the error is an application error resulting in a bad or malformed request to the server. */
    FBErrorCategoryBadRequest                   = -2,
};

/*!
 The key in the userInfo NSDictionary of NSError where you can find
 the inner NSError (if any).
 */
FBSDK_EXTERN NSString *const FBErrorInnerErrorKey;

/*!
 The key in the userInfo NSDictionary of NSError where you can find
 the session associated with the error (if any).
*/
FBSDK_EXTERN NSString *const FBErrorSessionKey;

/*!
 The key in the userInfo NSDictionary of NSError that points to the URL
 that caused an error, in its processing by FBAppCall.
 */
FBSDK_EXTERN NSString *const FBErrorUnprocessedURLKey;

/*!
 The key in the userInfo NSDictionary of NSError for unsuccessful
 logins (error.code equals FBErrorLoginFailedOrCancelled). If present,
 the value will be one of the constants prefixed by FBErrorLoginFailedReason*.
*/
FBSDK_EXTERN NSString *const FBErrorLoginFailedReason;

/*!
 The key in the userInfo NSDictionary of NSError for unsuccessful
 logins (error.code equals FBErrorLoginFailedOrCancelled). If present,
 the value indicates an original login error code wrapped by this error.
 This is only used in the web dialog login flow.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedOriginalErrorCode;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates the user
 cancelled a web dialog auth.
*/
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonInlineCancelledValue;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates the user
 did not cancel a web dialog auth.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonInlineNotCancelledValue;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates the user
 cancelled a non-iOS 6 SSO (either Safari or Facebook App) login.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonUserCancelledValue;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates the user
 cancelled an iOS system login.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonUserCancelledSystemValue;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates an error
 condition. You may inspect the rest of userInfo for other data.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonOtherError;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates the app's
 slider in iOS 6 (device Settings -> Privacy -> Facebook {app}) has
 been disabled.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonSystemDisallowedWithoutErrorValue;

/*!
 A value that may appear in an NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key for login failures. Indicates an error
 has occurred when requesting Facebook account acccess in iOS 6 that was
 not `FBErrorLoginFailedReasonSystemDisallowedWithoutErrorValue` nor
 a user cancellation.
 */
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonSystemError;
FBSDK_EXTERN NSString *const FBErrorLoginFailedReasonUnitTestResponseUnrecognized;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key when requesting new permissions fails. Indicates
 the request for new permissions has failed because the session was closed.
 */
FBSDK_EXTERN NSString *const FBErrorReauthorizeFailedReasonSessionClosed;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key when requesting new permissions fails. Indicates
 the request for new permissions has failed because the user cancelled.
 */
FBSDK_EXTERN NSString *const FBErrorReauthorizeFailedReasonUserCancelled;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key when requesting new permissions fails on
 iOS 6 with the Facebook account. Indicates the request for new permissions has
 failed because the user cancelled.
 */
FBSDK_EXTERN NSString *const FBErrorReauthorizeFailedReasonUserCancelledSystem;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorLoginFailedReason` key when requesting new permissions fails. Indicates
 the request for new permissions has failed because the request was
 for a different user than the original permission set.
 */
FBSDK_EXTERN NSString *const FBErrorReauthorizeFailedReasonWrongUser;

/*!
 The key in the userInfo NSDictionary of NSError for errors
 encountered with `FBDialogs` operations. (error.code equals FBErrorDialog).
 If present, the value will be one of the constants prefixed by FBErrorDialog *.
*/
FBSDK_EXTERN NSString *const FBErrorDialogReasonKey;

/*!
 A value that may appear in the NSError userInfo dictionary under the
`FBErrorDialogReasonKey` key. Indicates that a native dialog is not supported
 in the current OS.
*/
FBSDK_EXTERN NSString *const FBErrorDialogNotSupported;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorDialogReasonKey` key. Indicates that a native dialog cannot be
 displayed because it is not appropriate for the current session.
*/
FBSDK_EXTERN NSString *const FBErrorDialogInvalidForSession;

/*!
 A value that may appear in the NSError userInfo dictionary under the
 `FBErrorDialogReasonKey` key. Indicates that a native dialog cannot be
 displayed for some other reason.
 */
FBSDK_EXTERN NSString *const FBErrorDialogCantBeDisplayed;

/*!
 A value that may appear in the NSError userInfo ditionary under the
 `FBErrorDialogReasonKey` key. Indicates that a native dialog cannot be
 displayed because an Open Graph object that was passed was not configured
 correctly. The object must either (a) exist by having an 'id' or 'url' value;
 or, (b) configured for creation (by setting the 'type' value and
 provisionedForPost property)
*/
FBSDK_EXTERN NSString *const FBErrorDialogInvalidOpenGraphObject;

/*!
 A value that may appear in the NSError userInfo ditionary under the
 `FBErrorDialogReasonKey` key. Indicates that a native dialog cannot be
 displayed because the parameters for sharing an Open Graph action were
 not configured. The parameters must include an 'action', 'actionType', and
 'previewPropertyName'.
 */
FBSDK_EXTERN NSString *const FBErrorDialogInvalidOpenGraphActionParameters;

/*!
 A value that may appear in the NSError userInfo ditionary under the
 `FBErrorDialogReasonKey` key. Indicates that a native dialog cannot be
 displayed because the parameters for sharing a status update, link, or photo were
 not configured. The parameters must not include both 'photos' and a 'link'. */
FBSDK_EXTERN NSString *const FBErrorDialogInvalidShareParameters;

/*!
 A value that may appear in the NSError userInfo ditionary under the
 `FBErrorDialogReasonKey` key. Indicates that a like dialog cannot be
 displayed because the objectID parameter value is invalid.
 */
FBSDK_EXTERN NSString *const FBErrorDialogInvalidLikeObjectID;

/*!
 The key in the userInfo NSDictionary of NSError for errors
 encountered with `FBAppEvents` operations (error.code equals FBErrorAppEvents).
*/
FBSDK_EXTERN NSString *const FBErrorAppEventsReasonKey;

// Exception strings raised by the Facebook SDK

/*!
 This exception is raised by methods in the Facebook SDK to indicate
 that an attempted operation is invalid
 */
FBSDK_EXTERN NSString *const FBInvalidOperationException;

// Facebook SDK also raises exceptions the following common exceptions:
//  NSInvalidArgumentException

