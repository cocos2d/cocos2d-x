//
//  GADRequest.h
//  Google AdMob Ads SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#import "GADModules.h"

@protocol GADAdNetworkExtras;

/// Constant for getting test ads on the simulator using the testDevices method.
#define GAD_SIMULATOR_ID @"Simulator"

/// Genders to help deliver more relevant ads.
typedef NS_ENUM(NSInteger, GADGender) {
  kGADGenderUnknown,  ///< Unknown gender.
  kGADGenderMale,     ///< Male gender.
  kGADGenderFemale    ///< Female gender.
};

/// Specifies optional parameters for ad requests.
@interface GADRequest : NSObject<NSCopying>

/// Creates an autoreleased GADRequest.
+ (GADRequest *)request;

#pragma mark Additional Parameters For Ad Networks

/// Ad networks may have additional parameters they accept. To pass these parameters to them, create
/// the ad network extras object for that network, fill in the parameters, and register it here. The
/// ad network should have a header defining the interface for the 'extras' object to create. All
/// networks will have access to the basic settings you've set in this GADRequest (gender, birthday,
/// testing mode, etc.). If you register an extras object that is the same class as one you have
/// registered before, the previous extras will be overwritten.
- (void)registerAdNetworkExtras:(id<GADAdNetworkExtras>)extras;

/// Get the network extras defined for an ad network.
- (id<GADAdNetworkExtras>)adNetworkExtrasFor:(Class<GADAdNetworkExtras>)aClass;

/// Unsets the extras for an ad network. |clazz| is the class which represents that network's extras
/// type.
- (void)removeAdNetworkExtrasFor:(Class<GADAdNetworkExtras>)aClass;

/// Extras sent to the mediation server (if using Mediation). For future use.
@property(nonatomic, copy) NSDictionary *mediationExtras;

#pragma mark Collecting SDK Information

/// Returns the version of the SDK.
+ (NSString *)sdkVersion;

#pragma mark Testing

/// Add the device's identifier into this array for testing purposes.
@property(nonatomic, copy) NSArray *testDevices;

#pragma mark User Information

/// The user's gender may be used to deliver more relevant ads.
@property(nonatomic, assign) GADGender gender;

/// The user's birthday may be used to deliver more relevant ads.
@property(nonatomic, strong) NSDate *birthday;
- (void)setBirthdayWithMonth:(NSInteger)m day:(NSInteger)d year:(NSInteger)y;

/// The user's current location may be used to deliver more relevant ads. However do not use Core
/// Location just for advertising, make sure it is used for more beneficial reasons as well. It is
/// both a good idea and part of Apple's guidelines.
- (void)setLocationWithLatitude:(CGFloat)latitude
                      longitude:(CGFloat)longitude
                       accuracy:(CGFloat)accuracyInMeters;

/// When Core Location isn't available but the user's location is known supplying it here may
/// deliver more relevant ads. It can be any free-form text such as @"Champs-Elysees Paris" or
/// @"94041 US".
- (void)setLocationWithDescription:(NSString *)locationDescription;

/// [Optional] This method allows you to specify whether you would like your app to be treated as
/// child-directed for purposes of the Children’s Online Privacy Protection Act (COPPA),
/// http:///business.ftc.gov/privacy-and-security/childrens-privacy.
///
/// If you call this method with YES, you are indicating that your app should be treated as
/// child-directed for purposes of the Children’s Online Privacy Protection Act (COPPA). If you call
/// this method with NO, you are indicating that your app should not be treated as child-directed
/// for purposes of the Children’s Online Privacy Protection Act (COPPA). If you do not call this
/// method, ad requests will include no indication of how you would like your app treated with
/// respect to COPPA.
///
/// By setting this method, you certify that this notification is accurate and you are authorized to
/// act on behalf of the owner of the app. You understand that abuse of this setting may result in
/// termination of your Google account.
///
/// It may take some time for this designation to be fully implemented in applicable Google
/// services. This designation will only apply to ad requests for which you have set this method.
- (void)tagForChildDirectedTreatment:(BOOL)childDirectedTreatment;

#pragma mark Contextual Information

/// A keyword is a word or phrase describing the current activity of the user such as @"Sports
/// Scores". Each keyword is an NSString in the NSArray. To clear the keywords set this to nil.
@property(nonatomic, strong) NSMutableArray *keywords;

/// Convenience method for adding keywords one at a time such as @"Sports Scores" and then
/// @"Football".
- (void)addKeyword:(NSString *)keyword;

#pragma mark - Deprecated Methods

/// Accesses the additionalParameters for the "GoogleAdmob" ad network. Please use
/// -registerAdNetworkExtras: method above and pass an instance of GADAdMobExtras instead.
@property(nonatomic, copy) NSDictionary *additionalParameters __attribute__((
    deprecated(" use registerAdNetworkExtras: and pass an instance of GADAdMobExtras.")));

/// This property has been deprecated with the latest SDK releases. Please use testDevices.
@property(nonatomic, assign, getter=isTesting) BOOL testing
    __attribute__((deprecated(" use the testDevices property.")));

@end
