//
//  FlurryAds.h
//  Flurry iOS Analytics Agent
//
//  Copyright 2009-2013 Flurry, Inc. All rights reserved.
//	
//	Methods in this header file are for use by Flurry Publishers

#import <UIKit/UIKit.h>

typedef enum {
    BANNER_TOP    = 1,
    BANNER_BOTTOM = 2,
    FULLSCREEN    = 3,
} FlurryAdSize;

@protocol FlurryCustomAdNetwork;
@protocol FlurryCustomAdNetworkProperties;

/*!
 *  @brief Provides all available methods for displaying ads.
 * 
 *  Set of methods that allow publishers to configure, target, and deliver ads to their customers.
 *  
 *  @note This class depends on Flurry.h.
 *  For information on how to use Flurry's Ads SDK to
 *  attract high-quality users and monetize your user base see <a href="http://support.flurry.com/index.php?title=Publishers">Support Center - Publishers</a>.
 *  
 *  @author 2009 - 2013 Flurry, Inc. All Rights Reserved.
 *  @version 4.3.0
 * 
 */
@interface FlurryAds : NSObject {
}

/*!
 *  @brief Retrieves an ad for the given @c space.
 *  @since 4.1.0
 * 
 *  This method will attempt to retrieve ads for the given space from the Flurry server.
 * 
 *  @note The @c space simply represents the placement of the ad in your app and should be 
 *  unique for each placement. For example, if you are displaying a full screen ad on your 
 *  splash screen and after level completeion, you may have the following spaces 
 *  @c @"SPLASH_AD" and @c @"LEVEL_AD".
 * 
 *  @see #removeAdFromSpace: for details on manually removing an ad from a view. \n
 *  FlurryAdDelegate#spaceDidReceiveAd: for details on the notification of ads being received.
 *  FlurryAdDelegate#spaceDidFailToReceiveAd:error: for details on notification of failure to receive ads from this request.
 *  #displayAdForSpace: for details on displaying an available ad.
 *
 *  @code
 *  - (void)fetchAd:(NSString *)placement 
 {
    // Placement may be SPLASH_AD as noted above
    [FlurryAds fetchAdForSpace:placement view:self.view.frame size:FULLSCREEN]; 
 }
 
    // Show whenever delegate is invoked
 - (void) spaceDidReceiveAd:(NSString *)adSpace {
    // Received Ad
    [FlurryAds displayAdForSpace:adSpace];
 }
    // Alternatively, try to display at a certain point in the app
 - (void) levelComplete {
    if([FlurryAds adReadyForSpace:adSpace]) {
        [FlurryAds displayAdForSpace:adSpace];
    }
 }
 *  @endcode
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 *  @param frame The frame of the view that will be used for the ad container.
 *  @param size The default size of an ad space. This can be overriden on the server. See @c FlurryAdSize in the FlurryAds.h file for allowable values.
 */
+(void) fetchAdForSpace:(NSString*)space frame:(CGRect)frame size:(FlurryAdSize)size;

/*!
 *  @brief Returns if an ad is currently ready to display for a given @c space.
 *  @since 4.1.0
 * 
 *  This method will verify if there is an ad is currently available for this 
 *  user. If an ad is not available, you may call #fetchAdForSpace:view:size: to load a new ad.
 * 
 *  @note If this method returns YES, an ad will be available when you attempt to display an ad. However, it is still advisable to listen to the delegate FlurryAdsDelegate#spaceDidFailToRender:. \n
 The @c space simply represents the placement of the ad in your app and should be 
 *  unique for each placement. For example, if you are displaying a full screen ad on your 
 *  splash screen and after level completeion, you may have the following spaces 
 *  @c @"SPLASH_AD" and @c @"LEVEL_AD".
 * 
 *  @see #fetchAdForSpace:view:size: for details on retrieving an ad.\n
    #displayAdForSpace: for details on displaying the available ad.
 *
 *  @code
 *  - (void)showButtonForAd:(NSString *)placement 
 {
 // Placement may be SPLASH_AD as noted above
 if([FlurryAds adReadyForSpace:placement]) 
 {
 // Show button that ads are available.
 }
 }
 *  @endcode
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 *
 *  @return YES/NO to indicate if an ad is ready to be displayed.
 */
+(BOOL) adReadyForSpace:(NSString*)space;

/*!
 *  @brief Display an ad for the given @c space.
 *  @since 4.1.0
 * 
 *  This method will display an ad if one is ready for display on the device.
 * 
 *  @note The @c space simply represents the placement of the ad in your app and should be 
 *  unique for each placement. Only one ad will show at a time for any given ad space. For example, if you are displaying a full screen ad on your 
 *  splash screen and after level completeion, you may have the following spaces 
 *  @c @"SPLASH_AD" and @c @"LEVEL_AD".
 * 
 *  @see #fetchAdForSpace:view:size: for details on retrieving an ad.\n
    #adReadyForSpace: for details on verifying is an ad is ready to be displayed. \n
 *  #removeAdFromSpace: for details on manually removing an ad from a view. \n
 *  FlurryAdDelegate#spaceShouldDisplay:forType: for details on controlling whether an ad will display immediately before it is set to be rendered to the user.
 *  FlurryAdDelegate#spaceDidFailToRender:error: for details on notification of error in rendering an ad for this request.
 *
 *  @code
 *  - (void)showFullscreenAd:(NSString *)placement 
 {
 // Placement may be SPLASH_AD as noted above
 if([FlurryAds adReadyForSpace:placement])
 {
    [FlurryAds displayAdForSpace:placement onView:view];
 }
 }
 *  @endcode
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  @param view The view to place the ad. The view frame should be identical to the view frame passed in #fetchAdForSpace:frame:size. Note view is not used for interstitials.
 *  be splash screen for SPLASH_AD.
 */
+ (void)displayAdForSpace:(NSString*)space onView:(UIView *)view;

/*!
 *  @brief Display an ad for the given interstitial @c space.
 *  @since 4.2.2
 * 
 *  This method will display an interstitial ad if one is ready for display on the device for specified UIViewController instance
 * 
 *  @note The @c space simply represents the placement of the ad in your app and should be 
 *  unique for each placement. Only one ad will show at a time for any given ad space. For example, if you are displaying a full screen ad on your 
 *  splash screen and after level completeion, you may have the following spaces 
 *  @c @"SPLASH_AD" and @c @"LEVEL_AD".
 * 
 *  @see #fetchAdForSpace:view:size: for details on retrieving an ad.\n
    #adReadyForSpace: for details on verifying is an ad is ready to be displayed. \n
 *  #removeAdFromSpace: for details on manually removing an ad from a view. \n
 *  FlurryAdDelegate#spaceShouldDisplay:forType: for details on controlling whether an ad will display immediately before it is set to be rendered to the user.
 *  FlurryAdDelegate#spaceDidFailToRender:error: for details on notification of error in rendering an ad for this request.
 *
 *  @code
 * in UIViewController based class:
 *  - (void)showFullscreenAd:(NSString *)placement 
 {
 // Placement may be SPLASH_AD as noted above
 if([FlurryAds adReadyForSpace:placement])
 {
    [FlurryAds displayAdForSpace:placement modallyForViewController:self];
 }
 }
 *  @endcode
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  @param viewController The viewController to show the fullscreen ad modally.  
 *  Note this method should not be used for banners.
 */
 + (void)displayAdForSpace:(NSString*)space modallyForViewController:(UIViewController *)viewController;

/*!
 *  @brief [Deprecated] Check if an ad is available for the given @c space.
 *  @since 4.0.0
 *  @deprecated
 * 
 *  [Deprecated] This method will verify with the Flurry server if an ad is currently available for this 
 *  user. If an ad is not available, we recommend not providing the user the 
 *  option to view. For example, you may have a button that reads "See other great apps!".
 *  That button should only be displayed if this method returns YES.
 * 
 *  @note This method has been deprecated. 
 * 
 *  @see #fetchAdForSpace:view:size: for replacement method.\n
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 *  @param view The UIView in your app that the ad will be placed as a subview. Note: for fullscreen ads, this view is not used as a container, but the size of the view may still be used for determining what types of ads will fit in this space.
 *  @param size The default size of an ad space. This can be overriden on the server. See @c FlurryAdSize in the FlurryAds.h file for allowable values.
 *  @param timeout The maximum amount of time to wait for the server to return a result. Set this to 0 to check the cache and return immediately.
 *
 *  @return YES/NO to indicate if an ad is available.
 */
+(BOOL) isAdAvailableForSpace:(NSString*)space view:(UIView *)view size:(FlurryAdSize)size timeout:(int64_t)timeout __attribute__ ((deprecated));

/*!
 *  @brief [Deprecated] Display an ad for the given @c space.
 *  @since 4.0.0
 *  @deprecated
 * 
 *  [Deprecated] This method will display an ad if one is available from the Flurry server for this 
 *  user.
 * 
 *  @note This method has been deprecated.
 * 
 *  @see #fetchAndDisplayAdForSpace:view:size:timeout: for replacement method
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 *  @param view The UIView in your app that the ad will be placed as a subview. Note: for fullscreen ads, this view is not used as a container, but the size of the view may still be used for determining what types of ads will fit in this space.
 *  @param size The default size of an ad space. This can be overriden on the server. See @c FlurryAdSize in the FlurryAds.h file for allowable values.
 *  @param timeout The maximum amount of time to wait for the server to return a valid ad. Set this to 0 to display an ad in the background (e.g. - for showing banners).
 *
 *  @return YES/NO to indicate if an ad is available.
 */
+ (BOOL)showAdForSpace:(NSString*)space view:(UIView *)viewContainer size:(FlurryAdSize)size timeout:(int64_t)timeout __attribute__ ((deprecated));

/*!
 *  @brief Fetch and Display an ad for the given @c space.
 *  @since 4.0.0
 *
 *  This method will display an ad if one is available from the Flurry server for this
 *  user.
 *
 *  @note If this method returns YES, an ad is available for the space within @c timeout. \n
 *  This is a blocking method that allows you to change the user experience based on availability of an ad. If you would like to display an ad asynchronously, just set timeout to 0. This is useful in the case of banners for instance where the user should not wait for its display. If you are loading async with timeout set to 0, ignore the return value of this method and rely exclusively on the relevant delegate methods listed below\n
 *  The @c space simply represents the placement of the ad in your app and should be
 *  unique for each placement. Only one ad will show at a time for any given ad space. For example, if you are displaying a full screen ad on your
 *  splash screen and after level completeion, you may have the following spaces
 *  @c @"SPLASH_AD" and @c @"LEVEL_AD".
 *
 *  @see #adReadyForSpace: for details on verifying is an ad is ready to be displayed. \n
 *  #removeAdFromSpace: for details on manually removing an ad from a view. \n
 *  FlurryAdDelegate#spaceDidReceiveAd: for details on the notification of ads being received.
 *  FlurryAdDelegate#spaceDidFailToReceiveAd:error: for details on notification of failure to receive ads from this request.
 *  FlurryAdDelegate#spaceShouldDisplay:forType: for details on controlling whether an ad will display immediately before it is set to be rendered to the user.
 *  FlurryAdDelegate#spaceDidFailToRender:error: for details on notification of error in rendering an ad for this request.
 *
 *  @code
 *  - (void)showFullscreenAd:(NSString *)placement
 {
 // Placement may be SPLASH_AD as noted above
 [FlurryAds fetchAndDisplayAdForSpace:placement view:self.view size:FULLSCREEN timeout:3000];
 
 }
 
 - (void)viewWillAppear:(BOOL)animated
 {
 // Show a banner whenever this view appears
 // Display banner ad completely asyncrhonously by providing timeout == 0
 [FlurryAds fetchAndDisplayAdForSpace:@"VIEW_XYZ_BANNER_AD" view:self.view size:BANNER_BOTTOM timeout:0];
 }
 *  @endcode
 *
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 *  @param view The UIView in your app that the ad will be placed as a subview. Note: for fullscreen ads, this view is not used as a container, but the size of the view may still be used for determining what types of ads will fit in this space.
 *  @param size The default size of an ad space. This can be overriden on the server. See @c FlurryAdSize in the FlurryAds.h file for allowable values.
 */
+ (void)fetchAndDisplayAdForSpace:(NSString*)space view:(UIView *)viewContainer size:(FlurryAdSize)size;

/*!
 *  @brief Removes an ad for the given @c space.
 *  @since 4.0.0
 * 
 *  This method will remove an ad if one is currently displaying.
 * 
 *  @note The @c space simply represents the placement of the ad in your app and should be 
 *  unique for each placement. Only one ad will show at a time for any given ad space. 
 * 
 *  @see #isAdAvailableForSpace:view:size:timeout: for details on displaying an available ad. \n
 *  #removeAdFromSpace: for details on manually removing an ad from a view. \n
 *  FlurryAdDelegate#spaceShouldDisplay:forType: for details on controlling whether an ad will display immediately before it is set to be rendered to the user.
 *
 *  @code
 *  - (void)viewDidUnload 
    {
        // Remove a banner whenever this view dissapears
        [FlurryAds removeAdFromSpace:@"VIEW_XYZ_BANNER_AD"];
    }
 *  @endcode
 * 
 *  @param space The placement of an ad in your app, where placement may
 *  be splash screen for SPLASH_AD.
 */
+ (void) removeAdFromSpace:(NSString*)space;

/*!
 *  @brief Initializes the ad serving system.
 *  @since 4.0
 * 
 *  This method initializes the ad serving system and can be used to pre-cache ads from the server (this is done when ad spaces are configured on the server).
 * 
 *  @note This method must be called sometime after Flurry#startSession:.
 *
 *  @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
    {
        // Optional Flurry startup methods
        [Flurry startSession:@"YOUR_API_KEY"];
        [FlurryAds setAdDelegate:self];
        [FlurryAds initialize:myWindow.rootViewController];
 
        // ....
    }
 *  @endcode
 * 
 *  @param rvc The primary root view controller of your app.
 *
 */
+ (void) initialize: (UIViewController *)rvc;

/*!
 *  @brief Sets the object to receive various delegate methods.
 *  @since 4.0
 * 
 *  This method allows you to register an object that will receive 
 *  notifications at different phases of ad serving.
 * 
 *  @see FlurryAdDelegate.h for details on delegates available.
 *
 *  @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
    {
        // Optional Flurry startup methods
        [Flurry startSession:@"YOUR_API_KEY"];
        [FlurryAds setAdDelegate:self];
 
        // ....
    }
 *  @endcode
 * 
 *  @param delegate The object to receive notifications of various ad actions.
 *
 */
+ (void)setAdDelegate:(id)delegate;

/*!
 *  @brief Informs server to send test ads.
 *  @since 4.0
 * 
 *  This method allows you to request test ads from the server.  These ads do not generate revenue so it is CRITICAL this call is removed prior to app submission.
 * 
 *
 *  @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
    {
        // Optional Flurry startup methods
        [Flurry startSession:@"YOUR_API_KEY"];
        [FlurryAds enableTestAds:YES];
 
        // ....
    }
 *  @endcode
 * 
 *  @param enable YES to receive test ads to the device. Not including this method is equivalent to passing NO.
 *
 */
+ (void)enableTestAds:(BOOL)enable;

/*!
 *  @brief Sets a dictionary of key/value pairs, which will be transmitted to Flurry servers when a user clicks on an ad.
 *  @since 4.0.0
 * 
 *  UserCookies allow the developer to specify information on a user executing an ad action. There is one UserCookie object, and on each ad click that UserCookie is transmitted to the Flurry servers. The UserCookie key/value pairs will be transmitted back to the developer via the app callback if one is set. This is useful for rewarded inventory, to identify which of your users should be rewarded when a reward callback is sent.
 * 
 *  @note Calling this method with a nil or empty dictionary has no effect. Calling this method a second time with a valid dictionary will replace the previous entries. To clear previously set userCookies, you must call #clearUserCookies.
 *  @see #clearUserCookies for details on removing user cookies set through this method.
 *
 *  @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
    {
        // Optional Flurry startup methods
        [Flurry startSession:@"YOUR_API_KEY"];
 
        NSDictionary *cookies =
            [NSDictionary dictionaryWithObjectsAndKeys:@"xyz123", // Parameter Value
            @"UserCharacterId", // Parameter Name
            nil];
        [FlurryAds setUserCookies:cookies];
 
        // ....
    }
 *  @endcode
 * 
 *  @param userCookies The information about the user executing ad actions. Note: do not transmit personally identifiable information in the user cookies.
 */
+ (void) setUserCookies:(NSDictionary *) userCookies;

/*!
 *  @brief Removes a previously set dictionary of key/value pairs.
 *  @since 4.0.0
 * 
 *  This method removes information from the one UserCookie object.
 * 
 *  @see #setUserCookies: for details on setting user cookies.
 *
 */
+ (void) clearUserCookies;

/*!
 *  @brief Sets a dictionary of key/value pairs, which will be transmitted to Flurry servers when an ad is requested.
 *  @since 4.0.0
 * 
 *  Keywords allow the developer to specify information on a user executing an ad action for the purposes of targeting.  There is one keywords object that is transmitted to the Flurry servers on each ad request. If corresponding keywords are matched on the ad server, a subset of targeted ads will be delivered. This allows partners to supply information they track internally, which is not available to Flurry's targeting system.
 * 
 *  @note Calling this method with a nil or empty dictionary has no effect. Calling this method a second time with a valid dictionary will replace the previous entries. To clear previously set keywords, you must call #clearKeywords.
 *  @see #clearKeywords for details on removing keywords set through this method.
 *
 *  @code
 *  - (void)applicationDidFinishLaunching:(UIApplication *)application 
    {
        // Optional Flurry startup methods
        [Flurry startSession:@"YOUR_API_KEY"];
 
        // Specify that user loves vacations
        NSDictionary *keywords =
            [NSDictionary dictionaryWithObjectsAndKeys:@"vacation", // Parameter Value
            @"UserPreference", // Parameter Name
            nil];
            [FlurryAds setKeywords:keywords];
 
 // ....
 }
 *  @endcode
 * 
 *  @param keywords The information about the user to be used in targeting an ad. Note: do not transmit personally identifiable information in keywords.
 */
+ (void) setKeywordsForTargeting:(NSDictionary*) keywords;

/*!
 *  @brief Removes a previously set dictionary of key/value pairs.
 *  @since 4.0.0
 * 
 *  This method removes information from the one keywords object.
 * 
 *  @see #setKeywords: for details on setting keywords.
 *
 */
+ (void) clearKeywords;

/*!
 *  @brief Method to add a custom ad network to be served through the standard Flurry ad system.
 *  @since 4.0.0
 * 
 *  This method adds a network with the necessary publisher supplied properties to the Flurry sdk.
 * 
 *  @see @c FlurryCustomAdNetwork and @c FlurryCustomAdNetworkProperties for details.
 *
 */
+ (void) addCustomAdNetwork:(Class<FlurryCustomAdNetwork>)adNetworkClass withProperties:(id<FlurryCustomAdNetworkProperties>)adNetworkProperties;


@end