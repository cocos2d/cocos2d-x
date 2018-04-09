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

#import "FBAccessTokenData.h"
#import "FBAppLinkData.h"
#import "FBDialogsData.h"
#import "FBSession.h"

@class FBAppCall;

/*!
 @typedef FBAppCallHandler

 @abstract
 A block that is passed to performAppCall to register for a callback with the results
 of that AppCall

 @discussion
 Pass a block of this type when calling performAppCall.  This will be called on the UI
 thread, once the AppCall completes.

 @param call      The `FBAppCall` that was completed.

 */
typedef void (^FBAppCallHandler)(FBAppCall *call);

/*!
 @typedef FBAppLinkFallbackHandler

 @abstract
 See `+openDeferredAppLink`.
 */
typedef void (^FBAppLinkFallbackHandler)(NSError *error);

/*!
 @class FBAppCall

 @abstract
 The FBAppCall object is used to encapsulate state when the app performs an
 action that requires switching over to the native Facebook app, or when the app
 receives an App Link.

 @discussion
 - Each FBAppCall instance will have a unique ID
 - This object is passed into an FBAppCallHandler for context
 - dialogData will be present if this AppCall is for a Native Dialog
 - appLinkData will be present if this AppCall is for an App Link
 - accessTokenData will be present if this AppCall contains an access token.
 */
@interface FBAppCall : NSObject

/*! @abstract The ID of this FBAppCall instance */
@property (nonatomic, readonly) NSString *ID;

/*! @abstract Error that occurred in processing this AppCall */
@property (nonatomic, readonly) NSError *error;

/*! @abstract Data related to a Dialog AppCall */
@property (nonatomic, readonly) FBDialogsData *dialogData;

/*! @abstract Data for native app link */
@property (nonatomic, readonly) FBAppLinkData *appLinkData;

/*! @abstract Access Token that was returned in this AppCall */
@property (nonatomic, readonly) FBAccessTokenData *accessTokenData;

/*!
 @abstract
 Returns an FBAppCall instance from a url, if applicable. Otherwise, returns nil.

 @param url The url.

 @return an FBAppCall instance if the url is valid; nil otherwise.

 @discussion This is typically used for App Link URLs.
 */
+ (FBAppCall *)appCallFromURL:(NSURL *)url;

/*!
 @abstract
 Compares the receiving FBAppCall to the passed in FBAppCall

 @param appCall the other FBAppCall to compare to.

 @return YES if the AppCalls can be considered to be the same; NO if otherwise.
 */
- (BOOL)isEqualToAppCall:(FBAppCall *)appCall;

/*!
 @abstract
 Call this method from the [UIApplicationDelegate application:openURL:sourceApplication:annotation:] method
 of the AppDelegate for your app. It should be invoked for the proper processing of responses during interaction
 with the native Facebook app or as part of SSO authorization flow.

 @param url The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param sourceApplication The sourceApplication as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @return YES if the url was intended for the Facebook SDK, NO if not.
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication;

/*!
 @abstract
 Call this method from the [UIApplicationDelegate application:openURL:sourceApplication:annotation:] method
 of the AppDelegate for your app. It should be invoked for the proper processing of responses during interaction
 with the native Facebook app or as part of SSO authorization flow.

 @param url The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param sourceApplication The sourceApplication as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param handler Optional handler that gives the app the opportunity to do some further processing on urls
 that the SDK could not completely process. A fallback handler is not a requirement for such a url to be considered
 handled. The fallback handler, if specified, is only ever called sychronously, before the method returns.

 @return YES if the url was intended for the Facebook SDK, NO if not.
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
      fallbackHandler:(FBAppCallHandler)handler;

/*!
 @abstract
 Call this method from the [UIApplicationDelegate application:openURL:sourceApplication:annotation:] method
 of the AppDelegate for your app. It should be invoked for the proper processing of responses during interaction
 with the native Facebook app or as part of SSO authorization flow.

 @param url The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param sourceApplication The sourceApplication as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param session If this url is being sent back to this app as part of SSO authorization flow, then pass in the
 session that was being opened. A nil value defaults to FBSession.activeSession

 @return YES if the url was intended for the Facebook SDK, NO if not.
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
          withSession:(FBSession *)session;

/*!
 @abstract
 Call this method from the [UIApplicationDelegate application:openURL:sourceApplication:annotation:] method
 of the AppDelegate for your app. It should be invoked for the proper processing of responses during interaction
 with the native Facebook app or as part of SSO authorization flow.

 @param url The URL as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param sourceApplication The sourceApplication as passed to [UIApplicationDelegate application:openURL:sourceApplication:annotation:].

 @param session If this url is being sent back to this app as part of SSO authorization flow, then pass in the
 session that was being opened. A nil value defaults to FBSession.activeSession

 @param handler Optional handler that gives the app the opportunity to do some further processing on urls
 that the SDK could not completely process. A fallback handler is not a requirement for such a url to be considered
 handled. The fallback handler, if specified, is only ever called sychronously, before the method returns.

 @return YES if the url was intended for the Facebook SDK, NO if not.
 */
+ (BOOL)handleOpenURL:(NSURL *)url
    sourceApplication:(NSString *)sourceApplication
          withSession:(FBSession *)session
      fallbackHandler:(FBAppCallHandler)handler;

/*!
 @abstract
 Call this method when the application's applicationDidBecomeActive: is invoked.
 This ensures proper state management of any pending FBAppCalls or pending login flow for the
 FBSession.activeSession. If any pending FBAppCalls are found, their registered callbacks
 will be invoked with appropriate state
 */
+ (void)handleDidBecomeActive;

/*!
 @abstract
 Call this method when the application's applicationDidBecomeActive: is invoked.
 This ensures proper state management of any pending FBAppCalls or a pending open for the
 passed in FBSession. If any pending FBAppCalls are found, their registered callbacks will
 be invoked with appropriate state

 @param session Session that is currently being used. Any pending calls to open will be cancelled.
 If no session is provided, then the activeSession (if present) is used.
 */
+ (void)handleDidBecomeActiveWithSession:(FBSession *)session;

/*!
 @abstract
 Call this method from the main thread to fetch deferred applink data. This may require
 a network round trip. If successful, [+UIApplication openURL:] is invoked  with the link
 data. Otherwise, the fallbackHandler will be dispatched to the main thread.

 @param fallbackHandler the handler to be invoked if applink data could not be opened.

 @discussion the fallbackHandler may contain an NSError instance to capture any errors. In the
 common case where there simply was no app link data, the NSError instance will be nil.

 This method should only be called from a location that occurs after any launching URL has
 been processed (e.g., you should call this method from your application delegate's applicationDidBecomeActive:)
 to avoid duplicate invocations of openURL:.

 If you must call this from the delegate's didFinishLaunchingWithOptions: you should
 only do so if the application is not being launched by a URL. For example,

 if (launchOptions[UIApplicationLaunchOptionsURLKey] == nil) {
 [FBAppCall openDeferredAppLink:^(NSError *error) {
 // ....
 }
 }
 */
+ (void)openDeferredAppLink:(FBAppLinkFallbackHandler)fallbackHandler;

@end



