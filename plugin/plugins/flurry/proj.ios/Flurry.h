//
//  Flurry.h
//  Flurry iOS Analytics Agent
//
//  Copyright 2009-2012 Flurry, Inc. All rights reserved.
//	
//	Methods in this header file are for use with Flurry Analytics

#import <UIKit/UIKit.h>

/*!
 *  @brief Provides all available methods for defining and reporting Analytics from use
 *  of your app.
 * 
 *  Set of methods that allow developers to capture detailed, aggregate information
 *  regarding the use of their app by end users.
 *  
 *  @note This class provides methods necessary for correct function of FlurryAds.h.
 *  For information on how to use Flurry's Ads SDK to
 *  attract high-quality users and monetize your user base see <a href="http://support.flurry.com/index.php?title=Publishers">Support Center - Publishers</a>.
 *  
 *  @author 2009 - 2012 Flurry, Inc. All Rights Reserved.
 *  @version 4.0.0
 * 
 */
@interface Flurry : NSObject {
}

/** @name Pre-Session Calls
 *  Optional sdk settings that should be called before start session. 
 */
//@{

/*!
 *  @brief Explicitly specifies the App Version that Flurry will use to group Analytics data.
 *  @since 2.7
 *
 *  This is an optional method that overrides the App Version Flurry uses for reporting. Flurry will
 *  use the CFBundleVersion in your info.plist file when this method is not invoked.
 *
 *  @note There is a maximum of 605 versions allowed for a single app. \n
 *  This method must be called prior to invoking #startSession:.
 *
 *  @param version The custom version name.
 */

+ (void)setAppVersion:(NSString *)version;

/*!
 *  @brief Retrieves the Flurry Agent Build Version.
 *  @since 2.7
 *
 *  This is an optional method that retrieves the Flurry Agent Version the app is running under. 
 *  It is most often used if reporting an unexpected behavior of the SDK to <a href="mailto:iphonesupport@flurry.com">
 *  Flurry Support</a>
 *
 *  @note This method must be called prior to invoking #startSession:. \n
 *  FAQ for the iPhone SDK is located at <a href="http://wiki.flurry.com/index.php?title=IPhone_FAQ">
 *  Support Center - iPhone FAQ</a>.
 *
 *  @see #setDebugLogEnabled: for information on how to view debugging information on your console.
 *
 *  @return The agent version of the Flurry SDK.
 *
 */
+ (NSString *)getFlurryAgentVersion;

/*!
 *  @brief Displays an exception in the debug log if thrown during a Session.
 *  @since 2.7
 *
 *  This is an optional method that augments the debug logs with exceptions that occur during the session.
 *  You must both capture exceptions to Flurry and set debug logging to enabled for this method to
 *  display information to the console. The default setting for this method is @c NO.
 *
 *  @note This method must be called prior to invoking #startSession:.
 *
 *  @see #setDebugLogEnabled: for information on how to view debugging information on your console. \n
 *  #logError:message:exception: for details on logging exceptions. \n
 *  #logError:message:error: for details on logging errors.
 *
 *  @param value @c YES to show errors in debug logs, @c NO to omit errors in debug logs.
 */
+ (void)setShowErrorInLogEnabled:(BOOL)value;

/*!
 *  @brief Generates debug logs to console.
 *  @since 2.7
 *
 *  This is an optional method that displays debug information related to the Flurry SDK.
 *  display information to the console. The default setting for this method is @c NO.
 *
 *  @note This method must be called prior to invoking #startSession:.
 *
 *  @param value @c YES to show debug logs, @c NO to omit debug logs.
 *
 */
+ (void)setDebugLogEnabled:(BOOL)value;	

/*!
 *  @brief Set the timeout for expiring a Flurry session.
 *  @since 2.7
 * 
 *  This is an optional method that sets the time the app may be in the background before 
 *  starting a new session upon resume.  The default value for the session timeout is 10 
 *  seconds in the background.
 * 
 *  @note This method must be called prior to invoking #startSession:.
 * 
 *  @param seconds The time in seconds to set the session timeout to.
 */
+ (void)setSessionContinueSeconds:(int)seconds;

/*!
 *  @brief Send data over a secure transport.
 *  @since 3.0
 * 
 *  This is an optional method that sends data over an SSL connection when enabled. The
 *  default value is @c NO.
 * 
 *  @note This method must be called prior to invoking #startSession:.
 * 
 *  @param value @c YES to send data over secure connection.
 */
+ (void)setSecureTransportEnabled:(BOOL)value;

//@}

/*!
 *  @brief Start a Flurry session for the project denoted by @c apiKey.
 *  @since 2.6
 * 
 *  This method serves as the entry point to Flurry Analytics collection.  It must be
 *  called in the scope of @c applicationDidFinishLaunching.  The session will continue 
 *  for the period the app is in the foreground until your app is backgrounded for the 
 *  time specified in #setSessionContinueSeconds:. If the app is resumed in that period
 *  the session will continue, otherwise a new session will begin.
 * 
 *  @note If testing on a simulator, please be sure to send App to background via home
 *  button. Flurry depends on the iOS lifecycle to be complete for full reporting.
 * 
 * @see #setSessionContinueSeconds: for details on setting a custom session timeout.
 *
 * @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
 {
 // Optional Flurry startup methods
 [Flurry startSession:@"YOUR_API_KEY"];
 // ....
 }
 * @endcode
 * 
 * @param apiKey The API key for this project.
 */

+ (void)startSession:(NSString *)apiKey;

/** @name Event and Error Logging
 *  Methods for reporting custom events and errors during the session. 
 */
//@{

/*!
 *  @brief Records a custom event specified by @c eventName.
 *  @since 2.8.4
 * 
 *  This method allows you to specify custom events within your app.  As a general rule
 *  you should capture events related to user navigation within your app, any action 
 *  around monetization, and other events as they are applicable to tracking progress
 *  towards your business goals. 
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  Where applicable, you should make a concerted effort to use timed events with
 *  parameters (#logEvent:withParameters:timed:) or events with parameters 
 *  (#logEvent:withParameters:). This provides valuable information around the time the user
 *  spends within an action (e.g. - time spent on a level or viewing a page) or characteristics
 *  of an action (e.g. - Buy Event that has a Parameter of Widget with Value Golden Sword).
 * 
 *  @see #logEvent:withParameters: for details on storing events with parameters. \n
 *  #logEvent:timed: for details on storing timed events. \n
 *  #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)interestingAppAction 
 {
 [Flurry logEvent:@"Interesting_Action"];
 // Perform interesting action
 }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 */
+ (void)logEvent:(NSString *)eventName;

/*!
 *  @brief Records a custom parameterized event specified by @c eventName with @c parameters.
 *  @since 2.8.4
 * 
 *  This method overrides #logEvent to allow you to associate parameters with an event. Parameters
 *  are extremely valuable as they allow you to store characteristics of an action. For example,
 *  if a user purchased an item it may be helpful to know what level that user was on.
 *  By setting this parameter you will be able to view a distribution of levels for the purcahsed
 *  event on the <a href="http://dev.flurry.com">Flurrly Dev Portal</a>.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  A maximum of 10 parameter names may be associated with any event. Sending
 *  over 10 parameter names with a single event will result in no parameters being logged
 *  for that event. You may specify an infinite number of Parameter values. For example,
 *  a Search Box would have 1 parameter name (e.g. - Search Box) and many values, which would
 *  allow you to see what values users look for the most in your app. \n
 *  Where applicable, you should make a concerted effort to use timed events with
 *  parameters (#logEvent:withParameters:timed:). This provides valuable information 
 *  around the time the user spends within an action (e.g. - time spent on a level or 
 *  viewing a page).
 * 
 *  @see #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)userPurchasedSomethingCool 
 {
 NSDictionary *params =
 [NSDictionary dictionaryWithObjectsAndKeys:@"Cool Item", // Parameter Value
 @"Item Purchased", // Parameter Name
 nil];
 [Flurry logEvent:@"Something Cool Purchased" withParameters:params];
 // Give user cool item
 }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters A map containing Name-Value pairs of parameters.
 */
+ (void)logEvent:(NSString *)eventName withParameters:(NSDictionary *)parameters;

/*!
 *  @brief Records an app exception. Commonly used to catch unhandled exceptions.
 *  @since 2.7
 * 
 *  This method captures an exception for reporting to Flurry. We recommend adding an uncaught
 *  exception listener to capture any exceptions that occur during usage that is not
 *  anticipated by your app.
 * 
 *  @see #logError:message:error: for details on capturing errors.
 *
 *  @code
 *  - (void) uncaughtExceptionHandler(NSException *exception) 
 {
 [Flurry logError:@"Uncaught" message:@"Crash!" exception:exception];
 }
 
 - (void)applicationDidFinishLaunching:(UIApplication *)application 
 {
 NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
 [Flurry startSession:@"YOUR_API_KEY"];
 // ....
 }
 *  @endcode
 * 
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param exception The exception object to report.
 */
+ (void)logError:(NSString *)errorID message:(NSString *)message exception:(NSException *)exception;

/*!
 *  @brief Records an app error.
 *  @since 2.7
 * 
 *  This method captures an error for reporting to Flurry.
 * 
 *  @see #logError:message:exception: for details on capturing exceptions.
 *
 *  @code
 *  - (void) webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error 
 {
 [Flurry logError:@"WebView No Load" message:[error localizedDescription] error:error];
 }
 *  @endcode
 * 
 *  @param errorID Name of the error.
 *  @param message The message to associate with the error.
 *  @param error The error object to report.
 */
+ (void)logError:(NSString *)errorID message:(NSString *)message error:(NSError *)error;

/*!
 *  @brief Records a timed event specified by @c eventName.
 *  @since 2.8.4
 * 
 *  This method overrides #logEvent to allow you to capture the length of an event. This can
 *  be extremely valuable to understand the level of engagement with a particular action. For
 *  example, you can capture how long a user spends on a level or reading an article.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  Where applicable, you should make a concerted effort to use parameters with your timed 
 *  events (#logEvent:withParameters:timed:). This provides valuable information 
 *  around the characteristics of an action (e.g. - Buy Event that has a Parameter of Widget with 
 *  Value Golden Sword).
 * 
 *  @see #logEvent:withParameters:timed: for details on storing timed events with parameters. \n
 *  #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)startLevel 
 {
 [Flurry logEvent:@"Level Played" timed:YES];
 // Start user on level
 }
 
 - (void)endLevel 
 {
 [Flurry endTimedEvent:@"Level Played" withParameters:nil];
 // User done with level
 }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param timed Specifies the event will be timed.
 */
+ (void)logEvent:(NSString *)eventName timed:(BOOL)timed;

/*!
 *  @brief Records a custom parameterized timed event specified by @c eventName with @c parameters.
 *  @since 2.8.4
 * 
 *  This method overrides #logEvent to allow you to capture the length of an event with parameters. 
 *  This can be extremely valuable to understand the level of engagement with a particular action 
 *  and the characteristics associated with that action. For example, you can capture how long a user 
 *  spends on a level or reading an article. Parameters can be used to capture, for example, the
 *  author of an article or if something was purchased while on the level.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event.
 *
 *  @see #endTimedEvent:withParameters: for details on stopping a timed event and (optionally) updating 
 *  parameters.
 *
 *  @code
 *  - (void)startLevel 
 {
 NSDictionary *params =
 [NSDictionary dictionaryWithObjectsAndKeys:@"100", // Parameter Value
 @"Current Points", // Parameter Name
 nil];
 
 [Flurry logEvent:@"Level Played" withParameters:params timed:YES];
 // Start user on level
 }
 
 - (void)endLevel 
 {
 // User gained additional 100 points in Level
 NSDictionary *params =
 [NSDictionary dictionaryWithObjectsAndKeys:@"200", // Parameter Value
 @"Current Points", // Parameter Name
 nil];
 [Flurry endTimedEvent:@"Level Played" withParameters:params];
 // User done with level
 }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters A map containing Name-Value pairs of parameters.
 *  @param timed Specifies the event will be timed.
 */
+ (void)logEvent:(NSString *)eventName withParameters:(NSDictionary *)parameters timed:(BOOL)timed;

/*!
 *  @brief Ends a timed event specified by @c eventName and optionally updates parameters with @c parameters.
 *  @since 2.8.4
 * 
 *  This method ends an existing timed event.  If parameters are provided, this will overwrite existing
 *  parameters with the same name or create new parameters if the name does not exist in the parameter
 *  map set by #logEvent:withParameters:timed:.
 * 
 *  @note You should not pass private or confidential information about your users in a
 *  custom event. \n
 *  If the app is backgrounded prior to ending a timed event, the Flurry SDK will automatically
 *  end the timer on the event. \n 
 *  #endTimedEvent:withParameters: is ignored if called on a previously
 *  terminated event.
 *
 *  @see #logEvent:withParameters:timed: for details on starting a timed event with parameters.
 *
 *  @code
 *  - (void)startLevel 
 {
 NSDictionary *params =
 [NSDictionary dictionaryWithObjectsAndKeys:@"100", // Parameter Value
 @"Current Points", // Parameter Name
 nil];
 
 [Flurry logEvent:@"Level Played" withParameters:params timed:YES];
 // Start user on level
 }
 
 - (void)endLevel 
 {
 // User gained additional 100 points in Level
 NSDictionary *params =
 [NSDictionary dictionaryWithObjectsAndKeys:@"200", // Parameter Value
 @"Current Points", // Parameter Name
 nil];
 [Flurry endTimedEvent:@"Level Played" withParameters:params];
 // User done with level
 }
 *  @endcode
 * 
 *  @param eventName Name of the event. For maximum effectiveness, we recommend using a naming scheme
 *  that can be easily understood by non-technical people in your business domain.
 *  @param parameters A map containing Name-Value pairs of parameters.
 */
+ (void)endTimedEvent:(NSString *)eventName withParameters:(NSDictionary *)parameters;	// non-nil parameters will update the parameters

//@}


/** @name Page View Methods
 *  Count page views. 
 */
//@{

/*!
 *  @brief Automatically track page views on a @c UINavigationController or @c UITabBarController.
 *  @since 2.7
 * 
 *  This method increments the page view count for a session based on traversing a UINavigationController
 *  or UITabBarController. The page view count is only a counter for the number of transitions in your
 *  app. It does not associate a name with the page count. To associate a name with a count of occurences
 *  see #logEvent:.
 * 
 *  @note Please make sure you assign the Tab and Navigation controllers to the view controllers before
 *  passing them to this method.
 *
 *  @see #logPageView for details on explictly incrementing page view count.
 *
 *  @code
 * -(void) trackViewsFromTabBar:(UITabBarController*) tabBar 
 {
 [Flurry logAllPageViews:tabBar];
 }
 *  @endcode
 * 
 *  @param target The navigation or tab bar controller.
 */
+ (void)logAllPageViews:(id)target;		

/*!
 *  @brief Explicitly track a page view during a session.
 *  @since 2.7
 * 
 *  This method increments the page view count for a session when invoked. It does not associate a name
 *  with the page count. To associate a name with a count of occurences see #logEvent:.
 *
 *  @see #logAllPageViews for details on automatically incrementing page view count based on user
 *  traversing navigation or tab bar controller.
 *
 *  @code
 *  -(void) trackView 
 {
 [Flurry logPageView];
 }
 *  @endcode
 *
 */
+ (void)logPageView;

//@}

/** @name User Info
 *  Methods to set user information. 
 */
//@{

/*!
 *  @brief Assign a unique id for a user in your app.
 *  @since 2.7
 * 
 *  @note Please be sure not to use this method to pass any private or confidential information
 *  about the user.
 *
 *  @param userID The app id for a user.
 */
+ (void)setUserID:(NSString *)userID;	

/*!
 *  @brief Set your user's age in years.
 *  @since 2.7
 * 
 *  Use this method to capture the age of your user. Only use this method if you collect this
 *  information explictly from your user (i.e. - there is no need to set a default value).
 *
 *  @note The age is aggregated across all users of your app and not available on a per user
 *  basis.
 *
 *  @param age Reported age of user.
 *
 */
+ (void)setAge:(int)age;

/*!
 *  @brief Set your user's gender.
 *  @since 2.7
 * 
 *  Use this method to capture the gender of your user. Only use this method if you collect this
 *  information explictly from your user (i.e. - there is no need to set a default value). Allowable
 *  values are @c @"M" or @c @"F"
 *
 *  @note The gender is aggregated across all users of your app and not available on a per user
 *  basis.
 *
 *  @param gender Reported gender of user.
 *
 */
+ (void)setGender:(NSString *)gender;	// user's gender m or f

//@}

/** @name Location Reporting
 *  Methods for setting location information. 
 */
//@{
/*!
 *  @brief Set the location of the session.
 *  @since 2.7
 * 
 *  Use information from the CLLocationManager to specify the location of the session. Flurry does not
 *  automatically track this information or include the CLLocation framework.
 *
 *  @note Only the last location entered is captured per session. \n
 *  Regardless of accuracy specified, the Flurry SDK will only report location at city level or higher. \n
 *  Location is aggregated across all users of your app and not available on a per user basis. \n
 *  This information should only be captured if it is germaine to the use of your app.
 *
 *  @code
 CLLocationManager *locationManager = [[CLLocationManager alloc] init];
 [locationManager startUpdatingLocation];
 
 CLLocation *location = locationManager.location;
 [Flurry setLatitude:location.coordinate.latitude
 longitude:location.coordinate.longitude
 horizontalAccuracy:location.horizontalAccuracy
 verticalAccuracy:location.verticalAccuracy];
 *  @endcode
 *  @param latitude The latitude.
 *  @param longitude The longitude.
 *  @param horizontalAccuracy The radius of uncertainty for the location in meters.
 *  @param verticalAccuracy The accuracy of the altitude value in meters.
 *
 */
+ (void)setLatitude:(double)latitude longitude:(double)longitude horizontalAccuracy:(float)horizontalAccuracy verticalAccuracy:(float)verticalAccuracy;

//@}

/** @name Session Reporting Calls
 *  Optional methods that can be called at any point to control session reporting. 
 */
//@{

/*!
 *  @brief Set session to report when app closes.
 *  @since 2.7
 * 
 *  Use this method report session data when the app is closed. The default value is @c YES.
 *
 *  @note This method is rarely invoked in iOS >= 3.2 due to the updated iOS lifecycle.
 *
 *  @see #setSessionReportsOnPauseEnabled:
 *
 *  @param sendSessionReportsOnClose YES to send on close, NO to omit reporting on close.
 *
 */
+ (void)setSessionReportsOnCloseEnabled:(BOOL)sendSessionReportsOnClose;	

/*!
 *  @brief Set session to report when app is sent to the background.
 *  @since 2.7
 * 
 *  Use this method report session data when the app is paused. The default value is @c NO.
 *
 *  @param setSessionReportsOnPauseEnabled YES to send on pause, NO to omit reporting on pause.
 *
 */
+ (void)setSessionReportsOnPauseEnabled:(BOOL)setSessionReportsOnPauseEnabled;

/*!
 *  @brief Enable custom event logging.
 *  @since 2.7
 * 
 *  Use this method to allow the capture of custom events. The default value is @c YES.
 *
 *  @param value YES to enable event logging, NO to stop custom logging.
 *
 */
+ (void)setEventLoggingEnabled:(BOOL)value;	

//@}

@end
