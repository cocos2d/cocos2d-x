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
#import "FBSession.h"

/*!

 @typedef NS_ENUM (NSUInteger, FBAppEventsFlushBehavior)

 @abstract
 Control when <FBAppEvents> sends log events to the server

 @discussion

 */
typedef NS_ENUM(NSUInteger, FBAppEventsFlushBehavior) {

    /*! Flush automatically: periodically (once a minute or every 100 logged events) and always at app reactivation. */
    FBAppEventsFlushBehaviorAuto = 0,

    /*! Only flush when the `flush` method is called. When an app is moved to background/terminated, the
     events are persisted and re-established at activation, but they will only be written with an
     explicit call to `flush`. */
    FBAppEventsFlushBehaviorExplicitOnly,

};

/*
 * Constant used by NSNotificationCenter for results of flushing AppEvents event logs
 */

/*! NSNotificationCenter name indicating a result of a failed log flush attempt */
FBSDK_EXTERN NSString *const FBAppEventsLoggingResultNotification;


// Predefined event names for logging events common to many apps.  Logging occurs through the `logEvent` family of methods on `FBAppEvents`.
// Common event parameters are provided in the `FBAppEventsParameterNames*` constants.

// General purpose

/*! Deprecated: use [FBAppEvents activateApp] instead. */
FBSDK_EXTERN NSString *const FBAppEventNameActivatedApp __attribute__ ((deprecated("use [FBAppEvents activateApp] instead")));

/*! Log this event when a user has completed registration with the app. */
FBSDK_EXTERN NSString *const FBAppEventNameCompletedRegistration;

/*! Log this event when a user has viewed a form of content in the app. */
FBSDK_EXTERN NSString *const FBAppEventNameViewedContent;

/*! Log this event when a user has performed a search within the app. */
FBSDK_EXTERN NSString *const FBAppEventNameSearched;

/*! Log this event when the user has rated an item in the app.  The valueToSum passed to logEvent should be the numeric rating. */
FBSDK_EXTERN NSString *const FBAppEventNameRated;

/*! Log this event when the user has completed a tutorial in the app. */
FBSDK_EXTERN NSString *const FBAppEventNameCompletedTutorial;

// Ecommerce related

/*! Log this event when the user has added an item to their cart.  The valueToSum passed to logEvent should be the item's price. */
FBSDK_EXTERN NSString *const FBAppEventNameAddedToCart;

/*! Log this event when the user has added an item to their wishlist.  The valueToSum passed to logEvent should be the item's price. */
FBSDK_EXTERN NSString *const FBAppEventNameAddedToWishlist;

/*! Log this event when the user has entered the checkout process.  The valueToSum passed to logEvent should be the total price in the cart. */
FBSDK_EXTERN NSString *const FBAppEventNameInitiatedCheckout;

/*! Log this event when the user has entered their payment info. */
FBSDK_EXTERN NSString *const FBAppEventNameAddedPaymentInfo;

/*! Deprecated: use [FBAppEvents logPurchase:currency:] or [FBAppEvents logPurchase:currency:parameters:] instead */
FBSDK_EXTERN NSString *const FBAppEventNamePurchased __attribute__ ((deprecated("use [FBAppEvents logPurchase:currency:] or [FBAppEvents logPurchase:currency:parameters:] instead")));

// Gaming related

/*! Log this event when the user has achieved a level in the app. */
FBSDK_EXTERN NSString *const FBAppEventNameAchievedLevel;

/*! Log this event when the user has unlocked an achievement in the app. */
FBSDK_EXTERN NSString *const FBAppEventNameUnlockedAchievement;

/*! Log this event when the user has spent app credits.  The valueToSum passed to logEvent should be the number of credits spent. */
FBSDK_EXTERN NSString *const FBAppEventNameSpentCredits;



// Predefined event name parameters for common additional information to accompany events logged through the `logEvent` family
// of methods on `FBAppEvents`.  Common event names are provided in the `FBAppEventName*` constants.

/*! Parameter key used to specify currency used with logged event.  E.g. "USD", "EUR", "GBP".  See ISO-4217 for specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217>. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameCurrency;

/*! Parameter key used to specify method user has used to register for the app, e.g., "Facebook", "email", "Twitter", etc */
FBSDK_EXTERN NSString *const FBAppEventParameterNameRegistrationMethod;

/*! Parameter key used to specify a generic content type/family for the logged event, e.g. "music", "photo", "video".  Options to use will vary based upon what the app is all about. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameContentType;

/*! Parameter key used to specify an ID for the specific piece of content being logged about.  Could be an EAN, article identifier, etc., depending on the nature of the app. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameContentID;

/*! Parameter key used to specify the string provided by the user for a search operation. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameSearchString;

/*! Parameter key used to specify whether the activity being logged about was successful or not.  `FBAppEventParameterValueYes` and `FBAppEventParameterValueNo` are good canonical values to use for this parameter. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameSuccess;

/*! Parameter key used to specify the maximum rating available for the `FBAppEventNameRate` event.  E.g., "5" or "10". */
FBSDK_EXTERN NSString *const FBAppEventParameterNameMaxRatingValue;

/*! Parameter key used to specify whether payment info is available for the `FBAppEventNameInitiatedCheckout` event.  `FBAppEventParameterValueYes` and `FBAppEventParameterValueNo` are good canonical values to use for this parameter. */
FBSDK_EXTERN NSString *const FBAppEventParameterNamePaymentInfoAvailable;

/*! Parameter key used to specify how many items are being processed for an `FBAppEventNameInitiatedCheckout` or `FBAppEventNamePurchased` event. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameNumItems;

/*! Parameter key used to specify the level achieved in a `FBAppEventNameAchieved` event. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameLevel;

/*! Parameter key used to specify a description appropriate to the event being logged.  E.g., the name of the achievement unlocked in the `FBAppEventNameAchievementUnlocked` event. */
FBSDK_EXTERN NSString *const FBAppEventParameterNameDescription;



// Predefined values to assign to event parameters that accompany events logged through the `logEvent` family
// of methods on `FBAppEvents`.  Common event parameters are provided in the `FBAppEventParameterName*` constants.

/*! Yes-valued parameter value to be used with parameter keys that need a Yes/No value */
FBSDK_EXTERN NSString *const FBAppEventParameterValueYes;

/*! No-valued parameter value to be used with parameter keys that need a Yes/No value */
FBSDK_EXTERN NSString *const FBAppEventParameterValueNo;


/*!
 
 @class FBAppEvents

 @abstract
 Client-side event logging for specialized application analytics available through Facebook App Insights
 and for use with Facebook Ads conversion tracking and optimization.

 @discussion
 The `FBAppEvents` static class has a few related roles:

 + Logging predefined and application-defined events to Facebook App Insights with a
 numeric value to sum across a large number of events, and an optional set of key/value
 parameters that define "segments" for this event (e.g., 'purchaserStatus' : 'frequent', or
 'gamerLevel' : 'intermediate')

 + Logging events to later be used for ads optimization around lifetime value.

 + Methods that control the way in which events are flushed out to the Facebook servers.

 Here are some important characteristics of the logging mechanism provided by `FBAppEvents`:

 + Events are not sent immediately when logged.  They're cached and flushed out to the Facebook servers
   in a number of situations:
   - when an event count threshold is passed (currently 100 logged events).
   - when a time threshold is passed (currently 60 seconds).
   - when an app has gone to background and is then brought back to the foreground.

 + Events will be accumulated when the app is in a disconnected state, and sent when the connection is
   restored and one of the above 'flush' conditions are met.

 + The `FBAppEvents` class in thread-safe in that events may be logged from any of the app's threads.

 + The developer can set the `flushBehavior` on `FBAppEvents` to force the flushing of events to only
 occur on an explicit call to the `flush` method.

 + The developer can turn on console debug output for event logging and flushing to the server by using
 the `FBLoggingBehaviorAppEvents` value in `[FBSettings setLoggingBehavior:]`.

 Some things to note when logging events:

 + There is a limit on the number of unique event names an app can use, on the order of 300.
 + There is a limit to the number of unique parameter names in the provided parameters that can
 be used per event, on the order of 25.  This is not just for an individual call, but for all
 invocations for that eventName.
 + Event names and parameter names (the keys in the NSDictionary) must be between 2 and 40 characters, and
 must consist of alphanumeric characters, _, -, or spaces.
 + The length of each parameter value can be no more than on the order of 100 characters.

 */
@interface FBAppEvents : NSObject

/*
 * Basic event logging
 */

/*!
 
 @method

 @abstract
 Log an event with just an eventName.

 @param eventName   The name of the event to record.  Limitations on number of events and name length
 are given in the `FBAppEvents` documentation.

 */
+ (void)logEvent:(NSString *)eventName;

/*!
 
 @method

 @abstract
 Log an event with an eventName and a numeric value to be aggregated with other events of this name.

 @param eventName   The name of the event to record.  Limitations on number of events and name length
 are given in the `FBAppEvents` documentation.  Common event names are provided in `FBAppEventName*` constants.

 @param valueToSum  Amount to be aggregated into all events of this eventName, and App Insights will report
 the cumulative and average value of this amount.
 */
+ (void)logEvent:(NSString *)eventName
      valueToSum:(double)valueToSum;


/*!
 
 @method

 @abstract
 Log an event with an eventName and a set of key/value pairs in the parameters dictionary.
 Parameter limitations are described above.

 @param eventName   The name of the event to record.  Limitations on number of events and name construction
 are given in the `FBAppEvents` documentation.  Common event names are provided in `FBAppEventName*` constants.

 @param parameters  Arbitrary parameter dictionary of characteristics. The keys to this dictionary must
 be NSString's, and the values are expected to be NSString or NSNumber.  Limitations on the number of
 parameters and name construction are given in the `FBAppEvents` documentation.  Commonly used parameter names
 are provided in `FBAppEventParameterName*` constants.
 */
+ (void)logEvent:(NSString *)eventName
      parameters:(NSDictionary *)parameters;

/*!
 
 @method

 @abstract
 Log an event with an eventName, a numeric value to be aggregated with other events of this name,
 and a set of key/value pairs in the parameters dictionary.

 @param eventName   The name of the event to record.  Limitations on number of events and name construction
 are given in the `FBAppEvents` documentation.  Common event names are provided in `FBAppEventName*` constants.

 @param valueToSum  Amount to be aggregated into all events of this eventName, and App Insights will report
 the cumulative and average value of this amount.

 @param parameters  Arbitrary parameter dictionary of characteristics. The keys to this dictionary must
 be NSString's, and the values are expected to be NSString or NSNumber.  Limitations on the number of
 parameters and name construction are given in the `FBAppEvents` documentation.  Commonly used parameter names
 are provided in `FBAppEventParameterName*` constants.

 */
+ (void)logEvent:(NSString *)eventName
      valueToSum:(double)valueToSum
      parameters:(NSDictionary *)parameters;


/*!
 
 @method

 @abstract
 Log an event with an eventName, a numeric value to be aggregated with other events of this name,
 and a set of key/value pairs in the parameters dictionary.  Providing session lets the developer
 target a particular <FBSession>.  If nil is provided, then `[FBSession activeSession]` will be used.

 @param eventName   The name of the event to record.  Limitations on number of events and name construction
 are given in the `FBAppEvents` documentation.  Common event names are provided in `FBAppEventName*` constants.

 @param valueToSum  Amount to be aggregated into all events of this eventName, and App Insights will report
 the cumulative and average value of this amount.  Note that this is an NSNumber, and a value of `nil` denotes
 that this event doesn't have a value associated with it for summation.

 @param parameters  Arbitrary parameter dictionary of characteristics. The keys to this dictionary must
 be NSString's, and the values are expected to be NSString or NSNumber.  Limitations on the number of
 parameters and name construction are given in the `FBAppEvents` documentation.  Commonly used parameter names
 are provided in `FBAppEventParameterName*` constants.

 @param session     <FBSession> to direct the event logging to, and thus be logged with whatever user (if any)
 is associated with that <FBSession>.
 */
+ (void)logEvent:(NSString *)eventName
      valueToSum:(NSNumber *)valueToSum
      parameters:(NSDictionary *)parameters
         session:(FBSession *)session;


/*
 * Purchase logging
 */

/*!
 
 @method

 @abstract
 Log a purchase of the specified amount, in the specified currency.

 @param purchaseAmount    Purchase amount to be logged, as expressed in the specified currency.  This value
                          will be rounded to the thousandths place (e.g., 12.34567 becomes 12.346).

 @param currency          Currency, is denoted as, e.g. "USD", "EUR", "GBP".  See ISO-4217 for
 specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217>.

 @discussion              This event immediately triggers a flush of the `FBAppEvents` event queue, unless the `flushBehavior` is set
 to `FBAppEventsFlushBehaviorExplicitOnly`.

 */
+ (void)logPurchase:(double)purchaseAmount
           currency:(NSString *)currency;

/*!
 
 @method

 @abstract
 Log a purchase of the specified amount, in the specified currency, also providing a set of
 additional characteristics describing the purchase.

 @param purchaseAmount  Purchase amount to be logged, as expressed in the specified currency.This value
                        will be rounded to the thousandths place (e.g., 12.34567 becomes 12.346).

 @param currency        Currency, is denoted as, e.g. "USD", "EUR", "GBP".  See ISO-4217 for
 specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217>.

 @param parameters      Arbitrary parameter dictionary of characteristics. The keys to this dictionary must
 be NSString's, and the values are expected to be NSString or NSNumber.  Limitations on the number of
 parameters and name construction are given in the `FBAppEvents` documentation.  Commonly used parameter names
 are provided in `FBAppEventParameterName*` constants.

 @discussion              This event immediately triggers a flush of the `FBAppEvents` event queue, unless the `flushBehavior` is set
 to `FBAppEventsFlushBehaviorExplicitOnly`.

 */
+ (void)logPurchase:(double)purchaseAmount
           currency:(NSString *)currency
         parameters:(NSDictionary *)parameters;

/*!
 
 @method

 @abstract
 Log a purchase of the specified amount, in the specified currency, also providing a set of
 additional characteristics describing the purchase, as well as an <FBSession> to log to.

 @param purchaseAmount  Purchase amount to be logged, as expressed in the specified currency.This value
                        will be rounded to the thousandths place (e.g., 12.34567 becomes 12.346).

 @param currency        Currency, is denoted as, e.g. "USD", "EUR", "GBP".  See ISO-4217 for
 specific values.  One reference for these is <http://en.wikipedia.org/wiki/ISO_4217>.

 @param parameters      Arbitrary parameter dictionary of characteristics. The keys to this dictionary must
 be NSString's, and the values are expected to be NSString or NSNumber.  Limitations on the number of
 parameters and name construction are given in the `FBAppEvents` documentation.  Commonly used parameter names
 are provided in `FBAppEventParameterName*` constants.

 @param session         <FBSession> to direct the event logging to, and thus be logged with whatever user (if any)
 is associated with that <FBSession>.  A value of `nil` will use `[FBSession activeSession]`.

 @discussion            This event immediately triggers a flush of the `FBAppEvents` event queue, unless the `flushBehavior` is set
 to `FBAppEventsFlushBehaviorExplicitOnly`.

 */
+ (void)logPurchase:(double)purchaseAmount
           currency:(NSString *)currency
         parameters:(NSDictionary *)parameters
            session:(FBSession *)session;

/*!
 @method

 @abstract This method has been replaced by [FBSettings limitEventAndDataUsage] */
+ (BOOL)limitEventUsage __attribute__ ((deprecated("use [FBSettings limitEventAndDataUsage] instead")));

/*!
 @method
 
 @abstract This method has been replaced by [FBSettings setLimitEventUsage] */
+ (void)setLimitEventUsage:(BOOL)limitEventUsage __attribute__ ((deprecated("use [FBSettings setLimitEventAndDataUsage] instead")));

/*!
 
 @method

 @abstract
 Notifies the events system that the app has launched and, when appropriate, logs an "activated app" event.  Should typically be placed in the
 app delegates' `applicationDidBecomeActive:` method.

 This method also takes care of logging the event indicating the first time this app has been launched, which, among other things, is used to
 track user acquisition and app install ads conversions.

 @discussion
 `activateApp` will not log an event on every app launch, since launches happen every time the app is backgrounded and then foregrounded.
 "activated app" events will be logged when the app has not been active for more than 60 seconds.  This method also causes a "deactivated app"
 event to be logged when sessions are "completed", and these events are logged with the session length, with an indication of how much
 time has elapsed between sessions, and with the number of background/foreground interruptions that session had.  This data
 is all visible in your app's App Events Insights.
 */
+ (void)activateApp;

/*
 * Control over event batching/flushing
 */

/*!
 
 @method

 @abstract
 Get the current event flushing behavior specifying when events are sent back to Facebook servers.
 */
+ (FBAppEventsFlushBehavior)flushBehavior;

/*!
 
 @method

 @abstract
 Set the current event flushing behavior specifying when events are sent back to Facebook servers.

 @param flushBehavior   The desired `FBAppEventsFlushBehavior` to be used.
 */
+ (void)setFlushBehavior:(FBAppEventsFlushBehavior)flushBehavior;

/*!
 @method

 @abstract
 Set the 'override' App ID for App Event logging.

 @discussion
 In some cases, apps want to use one Facebook App ID for login and social presence and another
 for App Event logging.  (An example is if multiple apps from the same company share an app ID for login, but
 want distinct logging.)  By default, this value is `nil`, and defers to the `FacebookLoggingOverrideAppID`
 plist value.  If that's not set, the default App ID set via [FBSettings setDefaultAppID]
 or in the `FacebookAppID` plist entry.

 This should be set before any other calls are made to `FBAppEvents`.  Thus, you should set it in your application
 delegate's `application:didFinishLaunchingWithOptions:` delegate.

 @param appID The Facebook App ID to be used for App Event logging.
 */
+ (void)setLoggingOverrideAppID:(NSString *)appID;

/*!
 @method

 @abstract
 Get the 'override' App ID for App Event logging.

 @discussion
 @see `setLoggingOverrideAppID:`

 */
+ (NSString *)loggingOverrideAppID;


/*!
 
 @method

 @abstract
 Explicitly kick off flushing of events to Facebook.  This is an asynchronous method, but it does initiate an immediate
 kick off.  Server failures will be reported through the NotificationCenter with notification ID `FBAppEventsLoggingResultNotification`.
 */
+ (void)flush;

@end
