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
#import "FBLinkShareParams.h"
#import "FBOpenGraphActionParams.h"
#import "FBPhotoParams.h"

@class FBSession;
@protocol FBOpenGraphAction;

/*!
 @typedef FBNativeDialogResult enum

 @abstract
 Passed to a handler to indicate the result of a dialog being displayed to the user.
 */
typedef NS_ENUM(NSUInteger, FBOSIntegratedShareDialogResult) {
    /*! Indicates that the dialog action completed successfully. */
    FBOSIntegratedShareDialogResultSucceeded = 0,
    /*! Indicates that the dialog action was cancelled (either by the user or the system). */
    FBOSIntegratedShareDialogResultCancelled = 1,
    /*! Indicates that the dialog could not be shown (because not on ios6 or ios6 auth was not used). */
    FBOSIntegratedShareDialogResultError = 2
};

/*!
 @typedef

 @abstract Defines a handler that will be called in response to the native share dialog
 being displayed.
 */
typedef void (^FBOSIntegratedShareDialogHandler)(FBOSIntegratedShareDialogResult result, NSError *error);

/*!
 @typedef FBDialogAppCallCompletionHandler

 @abstract
 A block that when passed to a method in FBDialogs is called back
 with the results of the AppCall for that dialog.

 @discussion
 This will be called on the UI thread, once the AppCall completes.

 @param call      The `FBAppCall` that was completed.

 @param results     The results of the AppCall for the dialog. This parameters is present
 purely for convenience, and is the exact same value as call.dialogData.results.

 @param error       The `NSError` representing any error that occurred. This parameters is
 present purely for convenience, and is the exact same value as call.error.

 */
typedef void (^FBDialogAppCallCompletionHandler)(
                                                 FBAppCall *call,
                                                 NSDictionary *results,
                                                 NSError *error);

/*!
 @class FBDialogs

 @abstract
 Provides methods to display native (i.e., non-Web-based) dialogs to the user.

 @discussion
 If you are building an app with a urlSchemeSuffix, you should also set the appropriate
 plist entry. See `[FBSettings defaultUrlSchemeSuffix]`.
 */
@interface FBDialogs : NSObject

#pragma mark - OSIntegratedShareDialog

/*!
 @abstract
 Presents a dialog that allows the user to share a status update that may include
 text, images, or URLs. This dialog is only available on iOS 6.0 and above. The
 current active session returned by [FBSession activeSession] will be used to determine
 whether the dialog will be displayed. If a session is active, it must be open and the
 login method used to authenticate the user must be native iOS 6.0 authentication.
 If no session active, then whether the call succeeds or not will depend on
 whether Facebook integration has been configured.

 @param viewController  The view controller which will present the dialog.

 @param initialText The text which will initially be populated in the dialog. The user
 will have the opportunity to edit this text before posting it. May be nil.

 @param image  A UIImage that will be attached to the status update. May be nil.

 @param url    An NSURL that will be attached to the status update. May be nil.

 @param handler A handler that will be called when the dialog is dismissed, or if an error
 occurs. May be nil.

 @return YES if the dialog was presented, NO if not (in the case of a NO result, the handler
 will still be called, with an error indicating the reason the dialog was not displayed)
 */
+ (BOOL)presentOSIntegratedShareDialogModallyFrom:(UIViewController *)viewController
                                      initialText:(NSString *)initialText
                                            image:(UIImage *)image
                                              url:(NSURL *)url
                                          handler:(FBOSIntegratedShareDialogHandler)handler;

/*!
 @abstract
 Presents a dialog that allows the user to share a status update that may include
 text, images, or URLs. This dialog is only available on iOS 6.0 and above. The
 current active session returned by [FBSession activeSession] will be used to determine
 whether the dialog will be displayed. If a session is active, it must be open and the
 login method used to authenticate the user must be native iOS 6.0 authentication.
 If no session active, then whether the call succeeds or not will depend on
 whether Facebook integration has been configured.

 @param viewController  The view controller which will present the dialog.

 @param initialText The text which will initially be populated in the dialog. The user
 will have the opportunity to edit this text before posting it. May be nil.

 @param images  An array of UIImages that will be attached to the status update. May
 be nil.

 @param urls    An array of NSURLs that will be attached to the status update. May be nil.

 @param handler A handler that will be called when the dialog is dismissed, or if an error
 occurs. May be nil.

 @return YES if the dialog was presented, NO if not (in the case of a NO result, the handler
 will still be called, with an error indicating the reason the dialog was not displayed)
 */
+ (BOOL)presentOSIntegratedShareDialogModallyFrom:(UIViewController *)viewController
                                      initialText:(NSString *)initialText
                                           images:(NSArray *)images
                                             urls:(NSArray *)urls
                                          handler:(FBOSIntegratedShareDialogHandler)handler;

/*!
 @abstract
 Presents a dialog that allows the user to share a status update that may include
 text, images, or URLs. This dialog is only available on iOS 6.0 and above. An
 <FBSession> may be specified, or nil may be passed to indicate that the current
 active session should be used. If a session is specified (whether explicitly or by
 virtue of being the active session), it must be open and the login method used to
 authenticate the user must be native iOS 6.0 authentication. If no session is specified
 (and there is no active session), then whether the call succeeds or not will depend on
 whether Facebook integration has been configured.

 @param viewController  The view controller which will present the dialog.

 @param session     The <FBSession> to use to determine whether or not the user has been
 authenticated with iOS native authentication. If nil, then [FBSession activeSession]
 will be checked. See discussion above for the implications of nil or non-nil session.

 @param initialText The text which will initially be populated in the dialog. The user
 will have the opportunity to edit this text before posting it. May be nil.

 @param images  An array of UIImages that will be attached to the status update. May
 be nil.

 @param urls    An array of NSURLs that will be attached to the status update. May be nil.

 @param handler A handler that will be called when the dialog is dismissed, or if an error
 occurs. May be nil.

 @return YES if the dialog was presented, NO if not (in the case of a NO result, the handler
 will still be called, with an error indicating the reason the dialog was not displayed)
 */
+ (BOOL)presentOSIntegratedShareDialogModallyFrom:(UIViewController *)viewController
                                          session:(FBSession *)session
                                      initialText:(NSString *)initialText
                                           images:(NSArray *)images
                                             urls:(NSArray *)urls
                                          handler:(FBOSIntegratedShareDialogHandler)handler;

/*!
 @abstract Determines if the device is capable of presenting the OS integrated share dialog.

 @discussion This is the most basic check for capability for this feature.

 @see canPresentOSIntegratedShareDialogWithSession:
 */
+ (BOOL)canPresentOSIntegratedShareDialog;

/*!
 @abstract
 Determines whether a call to presentShareDialogModallyFrom: will successfully present
 a dialog. This is useful for applications that need to modify the available UI controls
 depending on whether the dialog is available on the current platform and for the current
 user.

 @param session     The <FBSession> to use to determine whether or not the user has been
 authenticated with iOS native authentication. If nil, then [FBSession activeSession]
 will be checked. See discussion above for the implications of nil or non-nil session.

 @return YES if the dialog would be presented for the session, and NO if not
 */
+ (BOOL)canPresentOSIntegratedShareDialogWithSession:(FBSession *)session;

#pragma mark - Native Share Dialog

/*!
 @abstract Determines if the device is capable of presenting the share dialog.

 @discussion This is the most basic check for capability for this feature.

 @see canPresentShareDialogWithOpenGraphActionParams:
 @see canPresentShareDialogWithParams:
 @see canPresentShareDialogWithPhotos:
 */
+ (BOOL)canPresentShareDialog;

/*!
 @abstract
 Determines whether a call to presentShareDialogWithOpenGraphActionParams:clientState:handler:
 will successfully present a dialog in the Facebook application. This is useful for applications
 that need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @param params The parameters for the FB share dialog.

 @return YES if the dialog would be presented, and NO if not

 @discussion A return value of YES here indicates that the corresponding
 presentShareDialogWithOpenGraphActionParams method will return a non-nil FBAppCall for
 the same params. And vice versa.
*/
+ (BOOL)canPresentShareDialogWithOpenGraphActionParams:(FBOpenGraphActionParams *)params;

/*!
 @abstract
 Determines whether a call to presentShareDialogWithTarget: will successfully
 present a dialog in the Facebook application. This is useful for applications that
 need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @param params The parameters for the FB share dialog.

 @return YES if the dialog would be presented, and NO if not

 @discussion A return value of YES here indicates that the corresponding
 presentShareDialogWithParams method will return a non-nil FBAppCall for the same
 params. And vice versa.
*/
+ (BOOL)canPresentShareDialogWithParams:(FBLinkShareParams *)params;

/*!
 @abstract
 Determines whether a call to presentShareDialogWithPhotoParams: will successfully
 present a dialog in the Facebook application. This is useful for applications that
 need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @return YES if the dialog would be presented, and NO if not

 @discussion A return value of YES here indicates that the corresponding
 presentShareDialogWithPhotoParams method will return a non-nil FBAppCall.
*/
+ (BOOL)canPresentShareDialogWithPhotos;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share a status
 update that may include text, images, or URLs. No session is required, and the app
 does not need to be authorized to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the FB share dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithParams:(FBLinkShareParams *)params
                                clientState:(NSDictionary *)clientState
                                    handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithLink:(NSURL *)link
                                  handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param name The name, or title associated with the link. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithLink:(NSURL *)link
                                     name:(NSString *)name
                                  handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param name The name, or title associated with the link. May be nil.

 @param caption The caption to be used with the link. May be nil.

 @param description The description associated with the link. May be nil.

 @param picture The link to a thumbnail to associate with the link. May be nil.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithLink:(NSURL *)link
                                     name:(NSString *)name
                                  caption:(NSString *)caption
                              description:(NSString *)description
                                  picture:(NSURL *)picture
                              clientState:(NSDictionary *)clientState
                                  handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the FB share dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithPhotoParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithPhotoParams:(FBPhotoParams *)params
                                     clientState:(NSDictionary *)clientState
                                         handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param photos An NSArray containing UIImages to be shared. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithPhotoParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithPhotos:(NSArray *)photos
                                       handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to share the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param photos An NSArray containing UIImages to be shared.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithPhotoParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithPhotos:(NSArray *)photos
                                clientState:(NSDictionary *)clientState
                                    handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to publish an Open
 Graph action. No session is required, and the app does not need to be authorized to call
 this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the Open Graph action dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithOpenGraphActionParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithOpenGraphActionParams:(FBOpenGraphActionParams *)params
                                               clientState:(NSDictionary *)clientState
                                                   handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to publish the
 supplied Open Graph action. No session is required, and the app does not need to be
 authorized to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param action The Open Graph action to be published. May not be nil.

 @param actionType the fully-specified Open Graph action type of the action (e.g.,
 my_app_namespace:my_action).

 @param previewPropertyName the name of the property on the action that represents the
 primary Open Graph object associated with the action; this object will be displayed in the
 preview portion of the share dialog.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithOpenGraphActionParams method is also returning YES for the same params.
 */+ (FBAppCall *)presentShareDialogWithOpenGraphAction:(id<FBOpenGraphAction>)action
                                             actionType:(NSString *)actionType
                                    previewPropertyName:(NSString *)previewPropertyName
                                                handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook application that allows the user to publish the
 supplied Open Graph action. No session is required, and the app does not need to be
 authorized to call this.

 Note that this will perform an app switch to the Facebook app, and will cause the
 current app to be suspended. When the share is complete, the Facebook app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param action The Open Graph action to be published. May not be nil.

 @param actionType the fully-specified Open Graph action type of the action (e.g.,
 my_app_namespace:my_action).

 @param previewPropertyName the name of the property on the action that represents the
 primary Open Graph object associated with the action; this object will be displayed in the
 preview portion of the share dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentShareDialogWithOpenGraphActionParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentShareDialogWithOpenGraphAction:(id<FBOpenGraphAction>)action
                                          actionType:(NSString *)actionType
                                 previewPropertyName:(NSString *)previewPropertyName
                                         clientState:(NSDictionary *)clientState
                                             handler:(FBDialogAppCallCompletionHandler)handler;

#pragma mark - Message Dialog

/*!
 @abstract Determines if the device is capable of presenting the message dialog.

 @discussion This is the most basic check for capability for this feature.

 @see canPresentMessageDialogWithOpenGraphActionParams:
 @see canPresentMessageDialogWithParams:
 @see canPresentMessageDialogWithPhotos:
 */
+ (BOOL)canPresentMessageDialog;

/*!
 @abstract
 Determines whether a call to `presentMessageDialogWithOpenGraphActionParams:...` will
 successfully present a dialog in the Facebook Messenger app. This is useful for applications
 that need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @param params the dialog parameters

 @return YES if the dialog would be presented, and NO if not
*/
+ (BOOL)canPresentMessageDialogWithOpenGraphActionParams:(FBOpenGraphActionParams *)params;

/*!
 @abstract
 Determines whether a call to `presentMessageDialogWithParams:...` will successfully
 present a dialog in the Facebook Messenger app. This is useful for applications that
 need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @param params the dialog parameters

 @return YES if the dialog would be presented, and NO if not
*/
+ (BOOL)canPresentMessageDialogWithParams:(FBLinkShareParams *)params;

/*!
 @abstract
 Determines whether a call to `presentMessageDialogWithPhotos:...` will successfully
 present a dialog in the Facebook Messenger app. This is useful for applications that
 need to modify the available UI controls depending on whether the dialog is
 available on the current platform.

 @return YES if the dialog would be presented, and NO if not
*/
+ (BOOL)canPresentMessageDialogWithPhotos;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to publish an Open
 Graph action. No session is required, and the app does not need to be authorized to call
 this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the Open Graph action dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 `canPresentMessageDialogWithOpenGraphActionParams:` method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithOpenGraphActionParams:(FBOpenGraphActionParams *)params
                                                 clientState:(NSDictionary *)clientState
                                                     handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to publish the
 supplied Open Graph action. No session is required, and the app does not need to be
 authorized to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param action The Open Graph action to be published. May not be nil.

 @param actionType the fully-specified Open Graph action type of the action (e.g.,
 my_app_namespace:my_action).

 @param previewPropertyName the name of the property on the action that represents the
 primary Open Graph object associated with the action; this object will be displayed in the
 preview portion of the share dialog.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentMessageDialogWithOpenGraphActionParams method is also returning YES for the same params.
 */+ (FBAppCall *)presentMessageDialogWithOpenGraphAction:(id<FBOpenGraphAction>)action
                                               actionType:(NSString *)actionType
                                      previewPropertyName:(NSString *)previewPropertyName
                                                  handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to publish the
 supplied Open Graph action. No session is required, and the app does not need to be
 authorized to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param action The Open Graph action to be published. May not be nil.

 @param actionType the fully-specified Open Graph action type of the action (e.g.,
 my_app_namespace:my_action).

 @param previewPropertyName the name of the property on the action that represents the
 primary Open Graph object associated with the action; this object will be displayed in the
 preview portion of the share dialog.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentMessageDialogWithOpenGraphActionParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithOpenGraphAction:(id<FBOpenGraphAction>)action
                                            actionType:(NSString *)actionType
                                   previewPropertyName:(NSString *)previewPropertyName
                                           clientState:(NSDictionary *)clientState
                                               handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to send the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the Message Dialog

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.
 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 `canPresentMessageDialogWithPhotos` method is also returning YES.
 */
+ (FBAppCall *)presentMessageDialogWithPhotoParams:(FBPhotoParams *)params
                                       clientState:(NSDictionary *)clientState
                                           handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to send the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param photos An NSArray containing UIImages to be shared.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 `canPresentMessageDialogWithPhotos` method is also returning YES.
 */
+ (FBAppCall *)presentMessageDialogWithPhotos:(NSArray *)photos
                                      handler:(FBDialogAppCallCompletionHandler)handler;
/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to send the
 supplied photo(s). No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param photos An NSArray containing UIImages to be shared.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 `canPresentMessageDialogWithPhotos` method is also returning YES.
*/
+ (FBAppCall *)presentMessageDialogWithPhotos:(NSArray *)photos
                                  clientState:(NSDictionary *)clientState
                                      handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to share a status
 update that may include text, images, or URLs. No session is required, and the app
 does not need to be authorized to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param params The parameters for the Message Dialog. The "friends" and "place" properties
 will be ignored as the Facebook Messenger app does not support tagging.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 `canPresentMessageDialogWithParams:` method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithParams:(FBLinkShareParams *)params
                                  clientState:(NSDictionary *)clientState
                                      handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentMessageDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithLink:(NSURL *)link
                                    handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param name The name, or title associated with the link. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentMessageDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithLink:(NSURL *)link
                                       name:(NSString *)name
                                    handler:(FBDialogAppCallCompletionHandler)handler;

/*!
 @abstract
 Presents a dialog in the Facebook Messenger app that allows the user to share the
 supplied link. No session is required, and the app does not need to be authorized
 to call this.

 Note that this will perform an app switch to the Messenger app, and will cause the
 current app to be suspended. When the share is complete, the Messenger app will redirect
 to a url of the form "fb{APP_ID}://" that the application must handle. The app should
 then call [FBAppCall handleOpenURL:sourceApplication:fallbackHandler:] to trigger
 the appropriate handling. Note that FBAppCall will first try to call the completion
 handler associated with this method, but since during an app switch, the calling app
 may be suspended or killed, the app must also give a fallbackHandler to the
 handleOpenURL: method in FBAppCall.

 @param link The URL link to be attached to the post.

 @param name The name, or title associated with the link. May be nil.

 @param caption The caption to be used with the link. May be nil.

 @param description The description associated with the link. May be nil.

 @param picture The link to a thumbnail to associate with the link. May be nil.

 @param clientState An NSDictionary that's passed through when the completion handler
 is called. This is useful for the app to maintain state about the share request that
 was made so as to have appropriate action when the handler is called. May be nil.

 @param handler A completion handler that may be called when the status update is
 complete. May be nil. If non-nil, the handler will always be called asynchronously.

 @return An FBAppCall object that will also be passed into the provided
 FBAppCallCompletionHandler.

 @discussion A non-nil FBAppCall object is only returned if the corresponding
 canPresentMessageDialogWithParams method is also returning YES for the same params.
 */
+ (FBAppCall *)presentMessageDialogWithLink:(NSURL *)link
                                       name:(NSString *)name
                                    caption:(NSString *)caption
                                description:(NSString *)description
                                    picture:(NSURL *)picture
                                clientState:(NSDictionary *)clientState
                                    handler:(FBDialogAppCallCompletionHandler)handler;

@end
