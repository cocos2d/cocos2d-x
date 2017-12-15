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
#import <Foundation/Foundation.h>

#import "FBGraphObject.h"
#import "FBSDKMacros.h"

// up-front decl's
@class FBRequest;
@class FBRequestConnection;
@class FBSession;
@class UIImage;


/*!
 @attribute beta true

 @typedef FBRequestConnectionErrorBehavior enum

 @abstract Describes what automatic error handling behaviors to provide (if any).

 @discussion This is a bitflag enum that can be composed of different values.

 See FBError.h and FBErrorUtility.h for error category and user message details.
 */
typedef NS_ENUM(NSUInteger, FBRequestConnectionErrorBehavior) {
    /*! The default behavior of none */
    FBRequestConnectionErrorBehaviorNone                   = 0,

    /*! This will retry any requests whose error category is classified as `FBErrorCategoryRetry`.
     If the retry fails, the normal handler is invoked. */
    FBRequestConnectionErrorBehaviorRetry                  = 1,

    /*! This will automatically surface any SDK provided userMessage (at most one), after
     retry attempts, but before any reconnects are tried. The alert will have one button
     whose text can be localized with the key "FBE:AlertMessageButton".

     You should not display your own alert views in your request handler when specifying this
     behavior.
     */
    FBRequestConnectionErrorBehaviorAlertUser              = 2,

    /*! This will automatically reconnect a session if the request failed due to an invalid token
     that would otherwise close the session (such as an expired token or password change). Note
     this will NOT reconnect a session if the user had uninstalled the app, or if the user had
     disabled the app's slider in their privacy settings (in cases of iOS 6 system auth).
     If the session is reconnected, this will transition the session state to FBSessionStateTokenExtended
     which will invoke any state change handlers. Otherwise, the session is closed as normal.

     This behavior should not be used if the FBRequestConnection contains multiple
     session instances. Further, when this behavior is used, you must not request new permissions
     for the session until the connection is completed.

     Lastly, you should avoid using additional FBRequestConnections with the same session because
     that will be subject to race conditions.
     */
    FBRequestConnectionErrorBehaviorReconnectSession     = 4,
};

/*!
 Normally requests return JSON data that is parsed into a set of `NSDictionary`
 and `NSArray` objects.

 When a request returns a non-JSON response, that response is packaged in
 a `NSDictionary` using FBNonJSONResponseProperty as the key and the literal
 response as the value.
 */
FBSDK_EXTERN NSString *const FBNonJSONResponseProperty;

/*!
 @typedef FBRequestHandler

 @abstract
 A block that is passed to addRequest to register for a callback with the results of that
 request once the connection completes.

 @discussion
 Pass a block of this type when calling addRequest.  This will be called once
 the request completes.  The call occurs on the UI thread.

 @param connection      The `FBRequestConnection` that sent the request.

 @param result          The result of the request.  This is a translation of
 JSON data to `NSDictionary` and `NSArray` objects.  This
 is nil if there was an error.

 @param error           The `NSError` representing any error that occurred.

 */
typedef void (^FBRequestHandler)(FBRequestConnection *connection,
                                 id result,
                                 NSError *error);

/*!
 @protocol

 @abstract
 The `FBRequestConnectionDelegate` protocol defines the methods used to receive network
 activity progress information from a <FBRequestConnection>.
 */
@protocol FBRequestConnectionDelegate <NSObject>

@optional

/*!
 @method

 @abstract
 Tells the delegate the request connection will begin loading

 @discussion
 If the <FBRequestConnection> is created using one of the convenience factory methods prefixed with
 start, the object returned from the convenience method has already begun loading and this method
 will not be called when the delegate is set.

 @param connection    The request connection that is starting a network request
 @param isCached      YES if the request can be fulfilled using cached data, otherwise NO indicating
                      the result will require a network request.
 */
- (void)requestConnectionWillBeginLoading:(FBRequestConnection *)connection
                                fromCache:(BOOL)isCached;

/*!
 @method

 @abstract
 Tells the delegate the request connection finished loading

 @discussion
 If the request connection completes without a network error occuring then this method is called.
 Invocation of this method does not indicate success of every <FBRequest> made, only that the
 request connection has no further activity. Use the error argument passed to the FBRequestHandler
 block to determine success or failure of each <FBRequest>.

 This method is invoked after the completion handler for each <FBRequest>.

 @param connection    The request connection that successfully completed a network request
 @param isCached      YES if the request was fulfilled using cached data, otherwise NO indicating
                      a network request was completed.
 */
- (void)requestConnectionDidFinishLoading:(FBRequestConnection *)connection
                                fromCache:(BOOL)isCached;

/*!
 @method

 @abstract
 Tells the delegate the request connection failed with an error

 @discussion
 If the request connection fails with a network error then this method is called. The `error`
 argument specifies why the network connection failed. The `NSError` object passed to the
 FBRequestHandler block may contain additional information.

 This method is invoked after the completion handler for each <FBRequest> and only if a network
 request was made. If the request was fulfilled using cached data, this method is not called.

 @param connection    The request connection that successfully completed a network request
 @param error         The `NSError` representing the network error that occurred, if any. May be nil
                      in some circumstances. Consult the `NSError` for the <FBRequest> for reliable
                      failure information.
 */
- (void)requestConnection:(FBRequestConnection *)connection
         didFailWithError:(NSError *)error;

/*!
 @method

 @abstract
 Tells the delegate the request connection is going to retry some network operations

 @discussion
 If some <FBRequests> fail, <FBRequestConnection> may create a new instance to retry the failed
 requests. This method is called before the new instance is started. You must set the delegate
 property on `retryConnection` to continue to receive progress information. If a delegate is
 set on `retryConnection` then -requestConnectionWillBeginLoading: will be invoked.

 This method is invoked after the completion handler for each <FBRequest> and only if a network
 request was made. If the request was fulfilled using cached data, this method is not called.

 @param connection      The request connection that successfully completed a network request
 @param retryConnection The new request connection that will retry the failed <FBRequest>s
 */
- (void)     requestConnection:(FBRequestConnection *)connection
willRetryWithRequestConnection:(FBRequestConnection *)retryConnection;

/*!
 @method

 @abstract
 Tells the delegate how much data has been sent and is planned to send to the remote host

 @discussion
 The byte count arguments refer to the aggregated <FBRequest> objects, not a particular <FBRequest>.

 Like `NSURLConnection`, the values may change in unexpected ways if data needs to be resent.

 @param connection                The request connection transmitting data to a remote host
 @param bytesWritten              The number of bytes sent in the last transmission
 @param totalBytesWritten         The total number of bytes sent to the remote host
 @param totalBytesExpectedToWrite The total number of bytes expected to send to the remote host
 */
- (void)requestConnection:(FBRequestConnection *)connection
          didSendBodyData:(NSInteger)bytesWritten
        totalBytesWritten:(NSInteger)totalBytesWritten
totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite;

@end

/*!
 @class FBRequestConnection

 @abstract
 The `FBRequestConnection` represents a single connection to Facebook to service a request.

 @discussion
 The request settings are encapsulated in a reusable <FBRequest> object. The
 `FBRequestConnection` object encapsulates the concerns of a single communication
 e.g. starting a connection, canceling a connection, or batching requests.

 */
@interface FBRequestConnection : NSObject

/*!
 @methodgroup Creating a request
 */

/*!
 @method

 Calls <initWithTimeout:> with a default timeout of 180 seconds.
 */
- (instancetype)init;

/*!
 @method

 @abstract
 `FBRequestConnection` objects are used to issue one or more requests as a single
 request/response connection with Facebook.

 @discussion
 For a single request, the usual method for creating an `FBRequestConnection`
 object is to call one of the **start* ** methods on <FBRequest>. However, it is
 allowable to init an `FBRequestConnection` object directly, and call
 <addRequest:completionHandler:> to add one or more request objects to the
 connection, before calling start.

 Note that if requests are part of a batch, they must have an open
 FBSession that has an access token associated with it. Alternatively a default App ID
 must be set either in the plist or through an explicit call to <[FBSession defaultAppID]>.

 @param timeout         The `NSTimeInterval` (seconds) to wait for a response before giving up.
 */

- (instancetype)initWithTimeout:(NSTimeInterval)timeout;

// properties

/*!
 @abstract
 The request that will be sent to the server.

 @discussion
 This property can be used to create a `NSURLRequest` without using
 `FBRequestConnection` to send that request.  It is legal to set this property
 in which case the provided `NSMutableURLRequest` will be used instead.  However,
 the `NSMutableURLRequest` must result in an appropriate response.  Furthermore, once
 this property has been set, no more <FBRequest> objects can be added to this
 `FBRequestConnection`.
 */
@property (nonatomic, retain, readwrite) NSMutableURLRequest *urlRequest;

/*!
 @abstract
 The raw response that was returned from the server.  (readonly)

 @discussion
 This property can be used to inspect HTTP headers that were returned from
 the server.

 The property is nil until the request completes.  If there was a response
 then this property will be non-nil during the FBRequestHandler callback.
 */
@property (nonatomic, retain, readonly) NSHTTPURLResponse *urlResponse;

/*!
 @attribute beta true

 @abstract Set the automatic error handling behaviors.
 @discussion

 This must be set before any requests are added.

 When using retry behaviors, note the FBRequestConnection instance
 passed to the FBRequestHandler may be a different instance that the
 one the requests were originally started on.
 */
@property (nonatomic, assign) FBRequestConnectionErrorBehavior errorBehavior;

@property (nonatomic, assign) id<FBRequestConnectionDelegate> delegate;

/*!
 @methodgroup Adding requests
 */

/*!
 @method

 @abstract
 This method adds an <FBRequest> object to this connection.

 @discussion
 The completion handler is retained until the block is called upon the
 completion or cancellation of the connection.

 @param request       A request to be included in the round-trip when start is called.
 @param handler       A handler to call back when the round-trip completes or times out.
 The handler will be invoked on the main thread.
 */
- (void)addRequest:(FBRequest *)request
 completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 This method adds an <FBRequest> object to this connection.

 @discussion
 The completion handler is retained until the block is called upon the
 completion or cancellation of the connection. This request can be named
 to allow for using the request's response in a subsequent request.

 @param request         A request to be included in the round-trip when start is called.

 @param handler         A handler to call back when the round-trip completes or times out.
 The handler will be invoked on the main thread.

 @param name            An optional name for this request.  This can be used to feed
 the results of one request to the input of another <FBRequest> in the same
 `FBRequestConnection` as described in
 [Graph API Batch Requests]( https://developers.facebook.com/docs/reference/api/batch/ ).
 */
- (void)addRequest:(FBRequest *)request
 completionHandler:(FBRequestHandler)handler
    batchEntryName:(NSString *)name;

/*!
 @method

 @abstract
 This method adds an <FBRequest> object to this connection.

 @discussion
 The completion handler is retained until the block is called upon the
 completion or cancellation of the connection. This request can be named
 to allow for using the request's response in a subsequent request.

 @param request         A request to be included in the round-trip when start is called.

 @param handler         A handler to call back when the round-trip completes or times out.

 @param batchParameters The optional dictionary of parameters to include for this request
 as described in [Graph API Batch Requests]( https://developers.facebook.com/docs/reference/api/batch/ ).
 Examples include "depends_on", "name", or "omit_response_on_success".
 */
- (void)addRequest:(FBRequest *)request
 completionHandler:(FBRequestHandler)handler
   batchParameters:(NSDictionary *)batchParameters;

/*!
 @methodgroup Instance methods
 */

/*!
 @method

 @abstract
 This method starts a connection with the server and is capable of handling all of the
 requests that were added to the connection.

 @discussion
 Errors are reported via the handler callback, even in cases where no
 communication is attempted by the implementation of `FBRequestConnection`. In
 such cases multiple error conditions may apply, and if so the following
 priority (highest to lowest) is used:

 - `FBRequestConnectionInvalidRequestKey` -- this error is reported when an
 <FBRequest> cannot be encoded for transmission.

 - `FBRequestConnectionInvalidBatchKey`   -- this error is reported when any
 request in the connection cannot be encoded for transmission with the batch.
 In this scenario all requests fail.

 This method cannot be called twice for an `FBRequestConnection` instance.
 */
- (void)start;

/*!
 @method

 @abstract
 Signals that a connection should be logically terminated as the
 application is no longer interested in a response.

 @discussion
 Synchronously calls any handlers indicating the request was cancelled. Cancel
 does not guarantee that the request-related processing will cease. It
 does promise that  all handlers will complete before the cancel returns. A call to
 cancel prior to a start implies a cancellation of all requests associated
 with the connection.
 */
- (void)cancel;

/*!
 @method

 @abstract
 Overrides the default version for a batch request

 @discussion
 The SDK automatically prepends a version part, such as "v2.0" to API paths in order to simplify API versioning
 for applications. If you want to override the version part while using batch requests on the connection, call
 this method to set the version for the batch request.

 @param version   This is a string in the form @"v2.0" which will be used for the version part of an API path
 */
- (void)overrideVersionPartWith:(NSString *)version;

/*!
 @method

 @abstract
 Simple method to make a graph API request for user info (/me), creates an <FBRequest>
 then uses an <FBRequestConnection> object to start the connection with Facebook. The
 request uses the active session represented by `[FBSession activeSession]`.

 See <connectionWithSession:graphPath:parameters:HTTPMethod:completionHandler:>

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForMeWithCompletionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to make a graph API request for user friends (/me/friends), creates an <FBRequest>
 then uses an <FBRequestConnection> object to start the connection with Facebook. The
 request uses the active session represented by `[FBSession activeSession]`.

 See <connectionWithSession:graphPath:parameters:HTTPMethod:completionHandler:>

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForMyFriendsWithCompletionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to make a graph API post of a photo. The request
 uses the active session represented by `[FBSession activeSession]`.

 @param photo            A `UIImage` for the photo to upload.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForUploadPhoto:(UIImage *)photo
                           completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to make a graph API post of a status update. The request
 uses the active session represented by `[FBSession activeSession]`.

 @param message         The message to post.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForPostStatusUpdate:(NSString *)message
                                completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to make a graph API post of a status update. The request
 uses the active session represented by `[FBSession activeSession]`.

 @param message         The message to post.
 @param place           The place to checkin with, or nil. Place may be an fbid or a
 graph object representing a place.
 @param tags            Array of friends to tag in the status update, each element
 may be an fbid or a graph object representing a user.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForPostStatusUpdate:(NSString *)message
                                            place:(id)place
                                             tags:(id<NSFastEnumeration>)tags
                                completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Starts a request representing a Graph API call to the "search" endpoint
 for a given location using the active session.

 @discussion
 Simplifies starting a request to search for places near a coordinate.

 This method creates the necessary <FBRequest> object and initializes and
 starts an <FBRequestConnection> object. A successful Graph API call will
 return an array of <FBGraphPlace> objects representing the nearby locations.

 @param coordinate      The search coordinates.

 @param radius          The search radius in meters.

 @param limit           The maxiumum number of results to return.  It is
 possible to receive fewer than this because of the
 radius and because of server limits.

 @param searchText      The text to use in the query to narrow the set of places
 returned.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForPlacesSearchAtCoordinate:(CLLocationCoordinate2D)coordinate
                                           radiusInMeters:(NSInteger)radius
                                             resultsLimit:(NSInteger)limit
                                               searchText:(NSString *)searchText
                                        completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Starts a request representing the Graph API call to retrieve a Custom Audience "third party ID" for the app's Facebook user.
 Callers will send this ID back to their own servers, collect up a set to create a Facebook Custom Audience with,
 and then use the resultant Custom Audience to target ads.

 @param session    The FBSession to use to establish the user's identity for users logged into Facebook through this app.
 If `nil`, then the activeSession is used.

 @discussion
 This method will throw an exception if <[FBSettings defaultAppID]> is `nil`.  The appID won't be nil when the pList
 includes the appID, or if it's explicitly set.

 The JSON in the request's response will include an "custom_audience_third_party_id" key/value pair, with the value being the ID retrieved.
 This ID is an encrypted encoding of the Facebook user's ID and the invoking Facebook app ID.
 Multiple calls with the same user will return different IDs, thus these IDs cannot be used to correlate behavior
 across devices or applications, and are only meaningful when sent back to Facebook for creating Custom Audiences.

 The ID retrieved represents the Facebook user identified in the following way: if the specified session (or activeSession if the specified
 session is `nil`) is open, the ID will represent the user associated with the activeSession; otherwise the ID will represent the user logged into the
 native Facebook app on the device.  If there is no native Facebook app, no one is logged into it, or the user has opted out
 at the iOS level from ad tracking, then a `nil` ID will be returned.

 This method returns `nil` if either the user has opted-out (via iOS) from Ad Tracking, the app itself has limited event usage
 via the `[FBAppEvents setLimitEventUsage]` flag, or a specific Facebook user cannot be identified.

 @param handler The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForCustomAudienceThirdPartyID:(FBSession *)session
                                          completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to make a graph API request, creates an <FBRequest> object for HTTP GET,
 then uses an <FBRequestConnection> object to start the connection with Facebook. The
 request uses the active session represented by `[FBSession activeSession]`.

 See <connectionWithSession:graphPath:parameters:HTTPMethod:completionHandler:>

 @param graphPath        The Graph API endpoint to use for the request, for example "me".
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startWithGraphPath:(NSString *)graphPath
                          completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to delete an object using the graph API, creates an <FBRequest> object for
 HTTP DELETE, then uses an <FBRequestConnection> object to start the connection with Facebook.
 The request uses the active session represented by `[FBSession activeSession]`.

 @param object           The object to delete, may be an NSString or NSNumber representing an fbid or an NSDictionary with an id property
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForDeleteObject:(id)object
                            completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Simple method to post an object using the graph API, creates an <FBRequest> object for
 HTTP POST, then uses <FBRequestConnection> to start a connection with Facebook. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param graphPath        The Graph API endpoint to use for the request, for example "me".

 @param graphObject      An object or open graph action to post.

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.

 @discussion This method is typically used for posting an open graph action. If you are only
 posting an open graph object (without an action), consider using `startForPostOpenGraphObject:completionHandler:`
 */
+ (FBRequestConnection *)startForPostWithGraphPath:(NSString *)graphPath
                                       graphObject:(id<FBGraphObject>)graphObject
                                 completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Creates an `FBRequest` object for a Graph API call, instantiate an
 <FBRequestConnection> object, add the request to the newly created
 connection and finally start the connection. Use this method for
 specifying the request parameters and HTTP Method. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param graphPath        The Graph API endpoint to use for the request, for example "me".

 @param parameters       The parameters for the request. A value of nil sends only the automatically handled parameters, for example, the access token. The default is nil.

 @param HTTPMethod       The HTTP method to use for the request. A nil value implies a GET.

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startWithGraphPath:(NSString *)graphPath
                                 parameters:(NSDictionary *)parameters
                                 HTTPMethod:(NSString *)HTTPMethod
                          completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Creates an `FBRequest` for creating a user owned Open Graph object, instantiate a
 <FBRequestConnection> object, add the request to the newly created
 connection and finally start the connection. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param object           The Open Graph object to create. Some common expected fields include "title", "image", "url", etc.

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForPostOpenGraphObject:(id<FBOpenGraphObject>)object
                                   completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Creates an `FBRequest` for creating a user owned Open Graph object, instantiate a
 <FBRequestConnection> object, add the request to the newly created
 connection and finally start the connection. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param type             The fully-specified Open Graph object type (e.g., my_app_namespace:my_object_name)
 @param title            The title of the Open Graph object.
 @param image            The link to an image to be associated with the Open Graph object.
 @param url              The url to be associated with the Open Graph object.
 @param description      The description for the object.
 @param objectProperties Any additional properties for the Open Graph object.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForPostOpenGraphObjectWithType:(NSString *)type
                                                       title:(NSString *)title
                                                       image:(id)image
                                                         url:(id)url
                                                 description:(NSString *)description
                                            objectProperties:(NSDictionary *)objectProperties
                                           completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Creates an `FBRequest` for updating a user owned Open Graph object, instantiate a
 <FBRequestConnection> object, add the request to the newly created
 connection and finally start the connection. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param object           The Open Graph object to update the existing object with.

 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForUpdateOpenGraphObject:(id<FBOpenGraphObject>)object
                                     completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Creates an `FBRequest` for updating a user owned Open Graph object, instantiate a
 <FBRequestConnection> object, add the request to the newly created
 connection and finally start the connection. The request uses
 the active session represented by `[FBSession activeSession]`.

 @param objectId         The id of the Open Graph object to update.
 @param title            The updated title of the Open Graph object.
 @param image            The updated link to an image to be associated with the Open Graph object.
 @param url              The updated url to be associated with the Open Graph object.
 @param description      The object's description.
 @param objectProperties Any additional properties to update for the Open Graph object.
 @param handler          The handler block to call when the request completes with a success, error, or cancel action.
 */
+ (FBRequestConnection *)startForUpdateOpenGraphObjectWithId:(id)objectId
                                                       title:(NSString *)title
                                                       image:(id)image
                                                         url:(id)url
                                                 description:(NSString *)description
                                            objectProperties:(NSDictionary *)objectProperties
                                           completionHandler:(FBRequestHandler)handler;

/*!
 @method

 @abstract
 Starts a request connection to upload an image
 to create a staging resource. Staging resources allow you to post binary data
 such as images, in preparation for a post of an open graph object or action
 which references the image. The URI returned when uploading a staging resource
 may be passed as the value for the image property of an open graph object or action.

 @discussion
 This method simplifies the preparation of a Graph API call be creating the FBRequest
 object and starting the request connection with a single method

 @param image            A `UIImage` for the image to upload.
 @param handler          The handler block to call when the request completes.
 */
+ (FBRequestConnection *)startForUploadStagingResourceWithImage:(UIImage *)image
                                              completionHandler:(FBRequestHandler)handler;

@end
