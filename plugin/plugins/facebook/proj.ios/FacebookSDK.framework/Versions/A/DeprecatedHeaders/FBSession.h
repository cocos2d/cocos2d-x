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

#import <Accounts/Accounts.h>
#import <Foundation/Foundation.h>

#import "FBSDKMacros.h"

// up-front decl's
@class FBAccessTokenData;
@class FBSession;
@class FBSessionTokenCachingStrategy;

#define FB_SESSIONSTATETERMINALBIT (1 << 8)

#define FB_SESSIONSTATEOPENBIT (1 << 9)

/*
 * Constants used by NSNotificationCenter for active session notification
 */

/*! NSNotificationCenter name indicating that a new active session was set */
FBSDK_EXTERN NSString *const FBSessionDidSetActiveSessionNotification;

/*! NSNotificationCenter name indicating that an active session was unset */
FBSDK_EXTERN NSString *const FBSessionDidUnsetActiveSessionNotification;

/*! NSNotificationCenter name indicating that the active session is open */
FBSDK_EXTERN NSString *const FBSessionDidBecomeOpenActiveSessionNotification;

/*! NSNotificationCenter name indicating that there is no longer an open active session */
FBSDK_EXTERN NSString *const FBSessionDidBecomeClosedActiveSessionNotification;

/*!
 @typedef FBSessionState enum

 @abstract Passed to handler block each time a session state changes

 @discussion
 */
typedef NS_ENUM(NSUInteger, FBSessionState) {
    /*! One of two initial states indicating that no valid cached token was found */
    FBSessionStateCreated                   = 0,
    /*! One of two initial session states indicating that a cached token was loaded;
     when a session is in this state, a call to open* will result in an open session,
     without UX or app-switching*/
    FBSessionStateCreatedTokenLoaded        = 1,
    /*! One of three pre-open session states indicating that an attempt to open the session
     is underway*/
    FBSessionStateCreatedOpening            = 2,

    /*! Open session state indicating user has logged in or a cached token is available */
    FBSessionStateOpen                      = 1 | FB_SESSIONSTATEOPENBIT,
    /*! Open session state indicating token has been extended, or the user has granted additional permissions */
    FBSessionStateOpenTokenExtended         = 2 | FB_SESSIONSTATEOPENBIT,

    /*! Closed session state indicating that a login attempt failed */
    FBSessionStateClosedLoginFailed         = 1 | FB_SESSIONSTATETERMINALBIT, // NSError obj w/more info
    /*! Closed session state indicating that the session was closed, but the users token
     remains cached on the device for later use */
    FBSessionStateClosed                    = 2 | FB_SESSIONSTATETERMINALBIT, // "
};

/*! helper macro to test for states that imply an open session */
#define FB_ISSESSIONOPENWITHSTATE(state) (0 != (state & FB_SESSIONSTATEOPENBIT))

/*! helper macro to test for states that are terminal */
#define FB_ISSESSIONSTATETERMINAL(state) (0 != (state & FB_SESSIONSTATETERMINALBIT))

/*!
 @typedef FBSessionLoginBehavior enum

 @abstract
 Passed to open to indicate whether Facebook Login should allow for fallback to be attempted.

 @discussion
 Facebook Login authorizes the application to act on behalf of the user, using the user's
 Facebook account. Usually a Facebook Login will rely on an account maintained outside of
 the application, by the native Facebook application, the browser, or perhaps the device
 itself. This avoids the need for a user to enter their username and password directly, and
 provides the most secure and lowest friction way for a user to authorize the application to
 interact with Facebook. If a Facebook Login is not possible, a fallback Facebook Login may be
 attempted, where the user is prompted to enter their credentials in a web-view hosted directly
 by the application.

 The `FBSessionLoginBehavior` enum specifies whether to allow fallback, disallow fallback, or
 force fallback login behavior. Most applications will use the default, which attempts a normal
 Facebook Login, and only falls back if needed. In rare cases, it may be preferable to disallow
 fallback Facebook Login completely, or to force a fallback login.
 */
typedef NS_ENUM(NSUInteger, FBSessionLoginBehavior) {
    /*! Attempt Facebook Login, ask user for credentials if necessary */
    FBSessionLoginBehaviorWithFallbackToWebView      = 0,
    /*! Attempt Facebook Login, no direct request for credentials will be made */
    FBSessionLoginBehaviorWithNoFallbackToWebView    = 1,
    /*! Only attempt WebView Login; ask user for credentials */
    FBSessionLoginBehaviorForcingWebView             = 2,
    /*! Attempt Facebook Login, prefering system account and falling back to fast app switch if necessary */
    FBSessionLoginBehaviorUseSystemAccountIfPresent  = 3,
    /*! Attempt only to login with Safari */
    FBSessionLoginBehaviorForcingSafari = 4,
};

/*!
 @typedef FBSessionDefaultAudience enum

 @abstract
 Passed to open to indicate which default audience to use for sessions that post data to Facebook.

 @discussion
 Certain operations such as publishing a status or publishing a photo require an audience. When the user
 grants an application permission to perform a publish operation, a default audience is selected as the
 publication ceiling for the application. This enumerated value allows the application to select which
 audience to ask the user to grant publish permission for.
 */
typedef NS_ENUM(NSUInteger, FBSessionDefaultAudience) {
    /*! No audience needed; this value is useful for cases where data will only be read from Facebook */
    FBSessionDefaultAudienceNone                = 0,
    /*! Indicates that only the user is able to see posts made by the application */
    FBSessionDefaultAudienceOnlyMe              = 10,
    /*! Indicates that the user's friends are able to see posts made by the application */
    FBSessionDefaultAudienceFriends             = 20,
    /*! Indicates that all Facebook users are able to see posts made by the application */
    FBSessionDefaultAudienceEveryone            = 30,
};

/*!
 @typedef FBSessionLoginType enum

 @abstract
 Used as the type of the loginType property in order to specify what underlying technology was used to
 login the user.

 @discussion
 The FBSession object is an abstraction over five distinct mechanisms. This enum allows an application
 to test for the mechanism used by a particular instance of FBSession. Usually the mechanism used for a
 given login does not matter, however for certain capabilities, the type of login can impact the behavior
 of other Facebook functionality.
 */
typedef NS_ENUM(NSUInteger, FBSessionLoginType) {
    /*! A login type has not yet been established */
    FBSessionLoginTypeNone                      = 0,
    /*! A system integrated account was used to log the user into the application */
    FBSessionLoginTypeSystemAccount             = 1,
    /*! The Facebook native application was used to log the user into the application */
    FBSessionLoginTypeFacebookApplication       = 2,
    /*! Safari was used to log the user into the application */
    FBSessionLoginTypeFacebookViaSafari         = 3,
    /*! A web view was used to log the user into the application */
    FBSessionLoginTypeWebView                   = 4,
    /*! A test user was used to create an open session */
    FBSessionLoginTypeTestUser                  = 5,
};

/*!
 @typedef

 @abstract Block type used to define blocks called by <FBSession> for state updates
 @discussion See https://developers.facebook.com/docs/technical-guides/iossdk/errors/
 for error handling best practices.

 Requesting additional permissions inside this handler (such as by calling
 `requestNewPublishPermissions`) should be avoided because it is a poor user
 experience and its behavior may vary depending on the login type. You should
 request the permissions closer to the operation that requires it (e.g., when
 the user performs some action).
 */
typedef void (^FBSessionStateHandler)(FBSession *session,
                                      FBSessionState status,
                                      NSError *error);

/*!
 @typedef

 @abstract Block type used to define blocks called by <[FBSession requestNewReadPermissions:completionHandler:]>
 and <[FBSession requestNewPublishPermissions:defaultAudience:completionHandler:]>.

 @discussion See https://developers.facebook.com/docs/technical-guides/iossdk/errors/
 for error handling best practices.

 Requesting additional permissions inside this handler (such as by calling
 `requestNewPublishPermissions`) should be avoided because it is a poor user
 experience and its behavior may vary depending on the login type. You should
 request the permissions closer to the operation that requires it (e.g., when
 the user performs some action).
 */
typedef void (^FBSessionRequestPermissionResultHandler)(FBSession *session,
                                                        NSError *error);

/*!
 @typedef

 @abstract Block type used to define blocks called by <[FBSession reauthorizeWithPermissions]>.

 @discussion You should use the preferred FBSessionRequestPermissionHandler typedef rather than
 this synonym, which has been deprecated.
 */
typedef FBSessionRequestPermissionResultHandler FBSessionReauthorizeResultHandler __attribute__((deprecated));

/*!
 @typedef

 @abstract Block type used to define blocks called for system credential renewals.
 @discussion
 */
typedef void (^FBSessionRenewSystemCredentialsHandler)(ACAccountCredentialRenewResult result, NSError *error) ;

/*!
 @class FBSession

 @abstract
 The `FBSession` object is used to authenticate a user and manage the user's session. After
 initializing a `FBSession` object the Facebook App ID and desired permissions are stored.
 Opening the session will initiate the authentication flow after which a valid user session
 should be available and subsequently cached. Closing the session can optionally clear the
 cache.

 If an  <FBRequest> request requires user authorization then an `FBSession` object should be used.


 @discussion
 Instances of the `FBSession` class provide notification of state changes in the following ways:

 1. Callers of certain `FBSession` methods may provide a block that will be called
 back in the course of state transitions for the session (e.g. login or session closed).

 2. The object supports Key-Value Observing (KVO) for property changes.
 */
@interface FBSession : NSObject

/*!
 @methodgroup Creating a session
 */

/*!
 @method

 @abstract
 Returns a newly initialized Facebook session with default values for the parameters
 to <initWithAppID:permissions:urlSchemeSuffix:tokenCacheStrategy:>.
 */
- (instancetype)init;

/*!
 @method

 @abstract
 Returns a newly initialized Facebook session with the specified permissions and other
 default values for parameters to <initWithAppID:permissions:urlSchemeSuffix:tokenCacheStrategy:>.

 @param permissions  An array of strings representing the permissions to request during the
 authentication flow.

 @discussion
 It is required that any single permission request request (including initial log in) represent read-only permissions
 or publish permissions only; not both. The permissions passed here should reflect this requirement.

 */
- (instancetype)initWithPermissions:(NSArray *)permissions;

/*!
 @method

 @abstract
 Following are the descriptions of the arguments along with their
 defaults when ommitted.

 @param permissions  An array of strings representing the permissions to request during the
 authentication flow.
 @param appID  The Facebook App ID for the session. If nil is passed in the default App ID will be obtained from a call to <[FBSession defaultAppID]>. The default is nil.
 @param urlSchemeSuffix  The URL Scheme Suffix to be used in scenarious where multiple iOS apps use one Facebook App ID. A value of nil indicates that this information should be pulled from [FBSettings defaultUrlSchemeSuffix]. The default is nil.
 @param tokenCachingStrategy Specifies a key name to use for cached token information in NSUserDefaults, nil
 indicates a default value of @"FBAccessTokenInformationKey".

 @discussion
 It is required that any single permission request request (including initial log in) represent read-only permissions
 or publish permissions only; not both. The permissions passed here should reflect this requirement.
 */
- (instancetype)initWithAppID:(NSString *)appID
                  permissions:(NSArray *)permissions
              urlSchemeSuffix:(NSString *)urlSchemeSuffix
           tokenCacheStrategy:(FBSessionTokenCachingStrategy *)tokenCachingStrategy;

/*!
 @method

 @abstract
 Following are the descriptions of the arguments along with their
 defaults when ommitted.

 @param permissions  An array of strings representing the permissions to request during the
 authentication flow.
 @param defaultAudience  Most applications use FBSessionDefaultAudienceNone here, only specifying an audience when using reauthorize to request publish permissions.
 @param appID  The Facebook App ID for the session. If nil is passed in the default App ID will be obtained from a call to <[FBSession defaultAppID]>. The default is nil.
 @param urlSchemeSuffix  The URL Scheme Suffix to be used in scenarious where multiple iOS apps use one Facebook App ID. A value of nil indicates that this information should be pulled from [FBSettings defaultUrlSchemeSuffix]. The default is nil.
 @param tokenCachingStrategy Specifies a key name to use for cached token information in NSUserDefaults, nil
 indicates a default value of @"FBAccessTokenInformationKey".

 @discussion
 It is required that any single permission request request (including initial log in) represent read-only permissions
 or publish permissions only; not both. The permissions passed here should reflect this requirement. If publish permissions
 are used, then the audience must also be specified.
 */
- (instancetype)initWithAppID:(NSString *)appID
                  permissions:(NSArray *)permissions
              defaultAudience:(FBSessionDefaultAudience)defaultAudience
              urlSchemeSuffix:(NSString *)urlSchemeSuffix
           tokenCacheStrategy:(FBSessionTokenCachingStrategy *)tokenCachingStrategy;

// instance readonly properties

/*! @abstract Indicates whether the session is open and ready for use. */
@property (readonly) BOOL isOpen;

/*! @abstract Detailed session state */
@property (readonly) FBSessionState state;

/*! @abstract Identifies the Facebook app which the session object represents. */
@property (readonly, copy) NSString *appID;

/*! @abstract Identifies the URL Scheme Suffix used by the session. This is used when multiple iOS apps share a single Facebook app ID. */
@property (readonly, copy) NSString *urlSchemeSuffix;

/*! @abstract The access token for the session object.
 @discussion Deprecated. Use the `accessTokenData` property. */
@property(readonly, copy) NSString *accessToken
__attribute__((deprecated));

/*! @abstract The expiration date of the access token for the session object.
 @discussion Deprecated. Use the `accessTokenData` property. */
@property(readonly, copy) NSDate *expirationDate
__attribute__((deprecated));

/*! @abstract The permissions granted to the access token during the authentication flow. */
@property (readonly, copy) NSArray *permissions;

/*! @abstract Specifies the login type used to authenticate the user.
 @discussion Deprecated. Use the `accessTokenData` property. */
@property(readonly) FBSessionLoginType loginType
__attribute__((deprecated));

/*! @abstract Gets the FBAccessTokenData for the session */
@property (readonly, copy) FBAccessTokenData *accessTokenData;

/*!
 @abstract
 Returns a collection of permissions that have been declined by the user for this
 given session instance.

 @discussion
 A "declined" permission is one that had been requested but was either skipped or removed by
 the user during the login flow. Note that once the permission has been granted (either by
 requesting again or detected by a permissions refresh), it will be removed from this collection.
 */
@property (readonly, copy) NSArray *declinedPermissions;

/*!
 @methodgroup Instance methods
 */

/*!
 @method

 @abstract Opens a session for the Facebook.

 @discussion
 A session may not be used with <FBRequest> and other classes in the SDK until it is open. If, prior
 to calling open, the session is in the <FBSessionStateCreatedTokenLoaded> state, then no UX occurs, and
 the session becomes available for use. If the session is in the <FBSessionStateCreated> state, prior
 to calling open, then a call to open causes login UX to occur, either via the Facebook application
 or via mobile Safari.

 Open may be called at most once and must be called after the `FBSession` is initialized. Open must
 be called before the session is closed. Calling an open method at an invalid time will result in
 an exception. The open session methods may be passed a block that will be called back when the session
 state changes. The block will be released when the session is closed.

 @param handler A block to call with the state changes. The default is nil.
 */
- (void)openWithCompletionHandler:(FBSessionStateHandler)handler;

/*!
 @method

 @abstract Logs a user on to Facebook.

 @discussion
 A session may not be used with <FBRequest> and other classes in the SDK until it is open. If, prior
 to calling open, the session is in the <FBSessionStateCreatedTokenLoaded> state, then no UX occurs, and
 the session becomes available for use. If the session is in the <FBSessionStateCreated> state, prior
 to calling open, then a call to open causes login UX to occur, either via the Facebook application
 or via mobile Safari.

 The method may be called at most once and must be called after the `FBSession` is initialized. It must
 be called before the session is closed. Calling the method at an invalid time will result in
 an exception. The open session methods may be passed a block that will be called back when the session
 state changes. The block will be released when the session is closed.

 @param behavior Controls whether to allow, force, or prohibit Facebook Login or Inline Facebook Login. The default
 is to allow Facebook Login, with fallback to Inline Facebook Login.
 @param handler A block to call with session state changes. The default is nil.
 */
- (void)openWithBehavior:(FBSessionLoginBehavior)behavior
       completionHandler:(FBSessionStateHandler)handler;

/*!
 @method

 @abstract Imports an existing access token and opens the session with it.

 @discussion
 The method attempts to open the session using an existing access token. No UX will occur. If
 successful, the session with be in an Open state and the method will return YES; otherwise, NO.

 The method may be called at most once and must be called after the `FBSession` is initialized (see below).
 It must be called before the session is closed. Calling the method at an invalid time will result in
 an exception. The open session methods may be passed a block that will be called back when the session
 state changes. The block will be released when the session is closed.

 The initialized session must not have already been initialized from a cache (for example, you could use
 the `[FBSessionTokenCachingStrategy nullCacheInstance]` instance).

 @param accessTokenData The token data. See `FBAccessTokenData` for construction methods.
 @param handler A block to call with session state changes. The default is nil.
 */
- (BOOL)openFromAccessTokenData:(FBAccessTokenData *)accessTokenData completionHandler:(FBSessionStateHandler) handler;

/*!
 @abstract
 Closes the local in-memory session object, but does not clear the persisted token cache.
 */
- (void)close;

/*!
 @abstract
 Closes the in-memory session, and clears any persisted cache related to the session.
 */
- (void)closeAndClearTokenInformation;

/*!
 @abstract
 Reauthorizes the session, with additional permissions.

 @param permissions An array of strings representing the permissions to request during the
 authentication flow. A value of nil indicates basic permissions. The default is nil.
 @param behavior Controls whether to allow, force, or prohibit Facebook Login. The default
 is to allow Facebook Login and fall back to Inline Facebook Login if needed.
 @param handler A block to call with session state changes. The default is nil.

 @discussion Methods and properties that specify permissions without a read or publish
 qualification are deprecated; use of a read-qualified or publish-qualified alternative is preferred
 (e.g. reauthorizeWithReadPermissions or reauthorizeWithPublishPermissions)
 */
- (void)reauthorizeWithPermissions:(NSArray *)permissions
                          behavior:(FBSessionLoginBehavior)behavior
                 completionHandler:(FBSessionReauthorizeResultHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Reauthorizes the session, with additional permissions.

 @param readPermissions An array of strings representing the permissions to request during the
 authentication flow. A value of nil indicates basic permissions.

 @param handler A block to call with session state changes. The default is nil.

 @discussion This method is a deprecated alias of <[FBSession requestNewReadPermissions:completionHandler:]>. Consider
 using <[FBSession requestNewReadPermissions:completionHandler:]>, which is preferred for readability.
 */
- (void)reauthorizeWithReadPermissions:(NSArray *)readPermissions
                     completionHandler:(FBSessionReauthorizeResultHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Reauthorizes the session, with additional permissions.

 @param writePermissions An array of strings representing the permissions to request during the
 authentication flow.

 @param defaultAudience Specifies the audience for posts.

 @param handler A block to call with session state changes. The default is nil.

 @discussion This method is a deprecated alias of <[FBSession requestNewPublishPermissions:defaultAudience:completionHandler:]>.
 Consider using <[FBSession requestNewPublishPermissions:defaultAudience:completionHandler:]>, which is preferred for readability.
 */
- (void)reauthorizeWithPublishPermissions:(NSArray *)writePermissions
                          defaultAudience:(FBSessionDefaultAudience)defaultAudience
                        completionHandler:(FBSessionReauthorizeResultHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 Requests new or additional read permissions for the session.

 @param readPermissions An array of strings representing the permissions to request during the
 authentication flow. A value of nil indicates basic permissions.

 @param handler A block to call with session state changes. The default is nil.

 @discussion The handler, if non-nil, is called once the operation has completed or failed. This is in contrast to the
 state completion handler used in <[FBSession openWithCompletionHandler:]> (and other `open*` methods) which is called
 for each state-change for the session.
 */
- (void)requestNewReadPermissions:(NSArray *)readPermissions
                completionHandler:(FBSessionRequestPermissionResultHandler)handler;

/*!
 @abstract
 Requests new or additional write permissions for the session.

 @param writePermissions An array of strings representing the permissions to request during the
 authentication flow.

 @param defaultAudience Specifies the audience for posts.

 @param handler A block to call with session state changes. The default is nil.

 @discussion The handler, if non-nil, is called once the operation has completed or failed. This is in contrast to the
 state completion handler used in <[FBSession openWithCompletionHandler:]> (and other `open*` methods) which is called
 for each state-change for the session.
 */
- (void)requestNewPublishPermissions:(NSArray *)writePermissions
                     defaultAudience:(FBSessionDefaultAudience)defaultAudience
                   completionHandler:(FBSessionRequestPermissionResultHandler)handler;
/*!
 @abstract Refreshes the current permissions for the session.
 @param handler Called after completion of the refresh.
 @discussion This will update the sessions' permissions array from the server. This can be
  useful if you want to make sure the local permissions are up to date.
 */
- (void)refreshPermissionsWithCompletionHandler:(FBSessionRequestPermissionResultHandler)handler;

/*!
 @abstract
 A helper method that is used to provide an implementation for
 [UIApplicationDelegate application:openURL:sourceApplication:annotation:]. It should be invoked during
 the Facebook Login flow and will update the session information based on the incoming URL.

 @param url The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].
 */
- (BOOL)handleOpenURL:(NSURL *)url;

/*!
 @abstract
 A helper method that is used to provide an implementation for
 [UIApplicationDelegate applicationDidBecomeActive:] to properly resolve session state for
 the Facebook Login flow, specifically to support app-switch login.
 */
- (void)handleDidBecomeActive;

/*!
 @abstract
 Assign the block to be invoked for session state changes.

 @param stateChangeHandler the handler block.

 @discussion
 This will overwrite any state change handler that was already assigned. Typically,
 you should only use this setter if you were unable to assign a state change handler explicitly.
 One example of this is if you are not opening the session (e.g., using the `open*`)
 but still want to assign a `FBSessionStateHandler` block. This can happen when the SDK
 opens a session from an app link.
 */
- (void)setStateChangeHandler:(FBSessionStateHandler)stateChangeHandler;

/*!
 @abstract
 Returns true if the specified permission has been granted to this session.

 @param permission the permission to verify.

 @discussion
 This is a convenience helper for checking if `pemission` is inside the permissions array.
 */
- (BOOL)hasGranted:(NSString *)permission;

/*!
 @methodgroup Class methods
 */

/*!
 @abstract
 This is the simplest method for opening a session with Facebook. Using sessionOpen logs on a user,
 and sets the static activeSession which becomes the default session object for any Facebook UI widgets
 used by the application. This session becomes the active session, whether open succeeds or fails.

 Note, if there is not a cached token available, this method will present UI to the user in order to
 open the session via explicit login by the user.

 @param allowLoginUI    Sometimes it is useful to attempt to open a session, but only if
 no login UI will be required to accomplish the operation. For example, at application startup it may not
 be disirable to transition to login UI for the user, and yet an open session is desired so long as a cached
 token can be used to open the session. Passing NO to this argument, assures the method will not present UI
 to the user in order to open the session.

 @discussion
 Returns YES if the session was opened synchronously without presenting UI to the user. This occurs
 when there is a cached token available from a previous run of the application. If NO is returned, this indicates
 that the session was not immediately opened, via cache. However, if YES was passed as allowLoginUI, then it is
 possible that the user will login, and the session will become open asynchronously. The primary use for
 this return value is to switch-on facebook capabilities in your UX upon startup, in the case where the session
 is opened via cache.
 */
+ (BOOL)openActiveSessionWithAllowLoginUI:(BOOL)allowLoginUI;

/*!
 @abstract
 This is a simple method for opening a session with Facebook. Using sessionOpen logs on a user,
 and sets the static activeSession which becomes the default session object for any Facebook UI widgets
 used by the application. This session becomes the active session, whether open succeeds or fails.

 @param permissions     An array of strings representing the permissions to request during the
 authentication flow. A value of nil indicates basic permissions. A nil value specifies
 default permissions.

 @param allowLoginUI    Sometimes it is useful to attempt to open a session, but only if
 no login UI will be required to accomplish the operation. For example, at application startup it may not
 be desirable to transition to login UI for the user, and yet an open session is desired so long as a cached
 token can be used to open the session. Passing NO to this argument, assures the method will not present UI
 to the user in order to open the session.

 @param handler                 Many applications will benefit from notification when a session becomes invalid
 or undergoes other state transitions. If a block is provided, the FBSession
 object will call the block each time the session changes state.

 @discussion
 Returns true if the session was opened synchronously without presenting UI to the user. This occurs
 when there is a cached token available from a previous run of the application. If NO is returned, this indicates
 that the session was not immediately opened, via cache. However, if YES was passed as allowLoginUI, then it is
 possible that the user will login, and the session will become open asynchronously. The primary use for
 this return value is to switch-on facebook capabilities in your UX upon startup, in the case where the session
 is opened via cache.

 It is required that initial permissions requests represent read-only permissions only. If publish
 permissions are needed, you may use reauthorizeWithPermissions to specify additional permissions as
 well as an audience. Use of this method will result in a legacy fast-app-switch Facebook Login due to
 the requirement to separate read and publish permissions for newer applications. Methods and properties
 that specify permissions without a read or publish qualification are deprecated; use of a read-qualified
 or publish-qualified alternative is preferred.
 */
+ (BOOL)openActiveSessionWithPermissions:(NSArray *)permissions
                            allowLoginUI:(BOOL)allowLoginUI
                       completionHandler:(FBSessionStateHandler)handler
__attribute__((deprecated));

/*!
 @abstract
 This is a simple method for opening a session with Facebook. Using sessionOpen logs on a user,
 and sets the static activeSession which becomes the default session object for any Facebook UI widgets
 used by the application. This session becomes the active session, whether open succeeds or fails.

 @param readPermissions     An array of strings representing the read permissions to request during the
 authentication flow. It is not allowed to pass publish permissions to this method.

 @param allowLoginUI    Sometimes it is useful to attempt to open a session, but only if
 no login UI will be required to accomplish the operation. For example, at application startup it may not
 be desirable to transition to login UI for the user, and yet an open session is desired so long as a cached
 token can be used to open the session. Passing NO to this argument, assures the method will not present UI
 to the user in order to open the session.

 @param handler                 Many applications will benefit from notification when a session becomes invalid
 or undergoes other state transitions. If a block is provided, the FBSession
 object will call the block each time the session changes state.

 @discussion
 Returns true if the session was opened synchronously without presenting UI to the user. This occurs
 when there is a cached token available from a previous run of the application. If NO is returned, this indicates
 that the session was not immediately opened, via cache. However, if YES was passed as allowLoginUI, then it is
 possible that the user will login, and the session will become open asynchronously. The primary use for
 this return value is to switch-on facebook capabilities in your UX upon startup, in the case where the session
 is opened via cache.

 */
+ (BOOL)openActiveSessionWithReadPermissions:(NSArray *)readPermissions
                                allowLoginUI:(BOOL)allowLoginUI
                           completionHandler:(FBSessionStateHandler)handler;

/*!
 @abstract
 This is a simple method for opening a session with Facebook. Using sessionOpen logs on a user,
 and sets the static activeSession which becomes the default session object for any Facebook UI widgets
 used by the application. This session becomes the active session, whether open succeeds or fails.

 @param publishPermissions     An array of strings representing the publish permissions to request during the
 authentication flow.

 @param defaultAudience     Anytime an app publishes on behalf of a user, the post must have an audience (e.g. me, my friends, etc.)
 The default audience is used to notify the user of the cieling that the user agrees to grant to the app for the provided permissions.

 @param allowLoginUI    Sometimes it is useful to attempt to open a session, but only if
 no login UI will be required to accomplish the operation. For example, at application startup it may not
 be desirable to transition to login UI for the user, and yet an open session is desired so long as a cached
 token can be used to open the session. Passing NO to this argument, assures the method will not present UI
 to the user in order to open the session.

 @param handler                 Many applications will benefit from notification when a session becomes invalid
 or undergoes other state transitions. If a block is provided, the FBSession
 object will call the block each time the session changes state.

 @discussion
 Returns true if the session was opened synchronously without presenting UI to the user. This occurs
 when there is a cached token available from a previous run of the application. If NO is returned, this indicates
 that the session was not immediately opened, via cache. However, if YES was passed as allowLoginUI, then it is
 possible that the user will login, and the session will become open asynchronously. The primary use for
 this return value is to switch-on facebook capabilities in your UX upon startup, in the case where the session
 is opened via cache.

 */
+ (BOOL)openActiveSessionWithPublishPermissions:(NSArray *)publishPermissions
                                defaultAudience:(FBSessionDefaultAudience)defaultAudience
                                   allowLoginUI:(BOOL)allowLoginUI
                              completionHandler:(FBSessionStateHandler)handler;

/*!
 @abstract
 An application may get or set the current active session. Certain high-level components in the SDK
 will use the activeSession to set default session (e.g. `FBLoginView`, `FBFriendPickerViewController`)

 @discussion
 If sessionOpen* is called, the resulting `FBSession` object also becomes the activeSession. If another
 session was active at the time, it is closed automatically. If activeSession is called when no session
 is active, a session object is instatiated and returned; in this case open must be called on the session
 in order for it to be useable for communication with Facebook.
 */
+ (FBSession *)activeSession;

/*!
 @abstract
 An application may get or set the current active session. Certain high-level components in the SDK
 will use the activeSession to set default session (e.g. `FBLoginView`, `FBFriendPickerViewController`)

 @param session         The FBSession object to become the active session

 @discussion
 If an application prefers the flexibilility of directly instantiating a session object, an active
 session can be set directly.
 */
+ (FBSession *)setActiveSession:(FBSession *)session;

/*!
 @method

 @abstract Set the default Facebook App ID to use for sessions. The app ID may be
 overridden on a per session basis.

 @discussion This method has been deprecated in favor of [FBSettings setDefaultAppID].

 @param appID The default Facebook App ID to use for <FBSession> methods.
 */
+ (void)setDefaultAppID:(NSString *)appID __attribute__((deprecated));

/*!
 @method

 @abstract Get the default Facebook App ID to use for sessions. If not explicitly
 set, the default will be read from the application's plist. The app ID may be
 overridden on a per session basis.

 @discussion This method has been deprecated in favor of [FBSettings defaultAppID].
 */
+ (NSString *)defaultAppID __attribute__((deprecated));

/*!
 @method

 @abstract Set the default url scheme suffix to use for sessions. The url
 scheme suffix may be overridden on a per session basis.

 @discussion This method has been deprecated in favor of [FBSettings setDefaultUrlSchemeSuffix].

 @param urlSchemeSuffix The default url scheme suffix to use for <FBSession> methods.
 */
+ (void)setDefaultUrlSchemeSuffix:(NSString *)urlSchemeSuffix __attribute__((deprecated));

/*!
 @method

 @abstract Get the default url scheme suffix used for sessions.  If not
 explicitly set, the default will be read from the application's plist. The
 url scheme suffix may be overridden on a per session basis.

 @discussion This method has been deprecated in favor of [FBSettings defaultUrlSchemeSuffix].
 */
+ (NSString *)defaultUrlSchemeSuffix __attribute__((deprecated));

/*!
 @method

 @abstract Issues an asychronous renewCredentialsForAccount call to the device Facebook account store.

 @param handler The completion handler to call when the renewal is completed. The handler will be
 invoked on the main thread.

 @discussion This can be used to explicitly renew account credentials on iOS 6 devices and is provided
 as a convenience wrapper around `[ACAccountStore renewCredentialsForAccount:completion]`. Note the
 method will not issue the renewal call if the the Facebook account has not been set on the device, or
 if access had not been granted to the account (though the handler wil receive an error).

 This is safe to call (and will surface an error to the handler) on versions of iOS before 6 or if the user
 logged in via Safari or Facebook SSO.
 */
+ (void)renewSystemCredentials:(FBSessionRenewSystemCredentialsHandler)handler;
@end
