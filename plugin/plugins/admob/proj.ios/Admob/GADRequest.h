//
//  GADRequest.h
//  Google AdMob Ads SDK
//
//  Copyright 2011 Google Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

@protocol GADAdNetworkExtras;

// Constant for getting test ads on the simulator using the testDevices method.
#define GAD_SIMULATOR_ID @"Simulator"

// Genders to help deliver more relevant ads.
typedef enum {
  kGADGenderUnknown,
  kGADGenderMale,
  kGADGenderFemale
} GADGender;

// Specifies optional parameters for ad requests.
@interface GADRequest : NSObject <NSCopying>

// Creates an autoreleased GADRequest.
+ (GADRequest *)request;

#pragma mark Additional Parameters For Ad Networks

// Ad networks may have additional parameters they accept. To pass these
// parameters to them, create the ad network extras object for that network,
// fill in the parameters, and register it here. The ad network should have a
// header defining the interface for the 'extras' object to create. All
// networks will have access to the basic settings you've set in this GADRequest
// (gender, birthday, testing mode, etc.). If you register an extras object
// that is the same class as one you have registered before, the previous
// extras will be overwritten.
- (void)registerAdNetworkExtras:(id<GADAdNetworkExtras>)extras;

// Get the network extras defined for an ad network.
- (id<GADAdNetworkExtras>)adNetworkExtrasFor:(Class<GADAdNetworkExtras>)clazz;

// Unsets the extras for an ad network. |clazz| is the class which represents
// that network's extras type.
- (void)removeAdNetworkExtrasFor:(Class<GADAdNetworkExtras>)clazz;

// Extras sent to the mediation server (if using Mediation). For future use.
@property (nonatomic, retain) NSDictionary *mediationExtras;

#pragma mark Collecting SDK Information

// Returns the version of the SDK.
+ (NSString *)sdkVersion;

#pragma mark Testing

// Add the device's identifier into this array for testing purposes.
@property (nonatomic, retain) NSArray *testDevices;

#pragma mark User Information

// The user's gender may be used to deliver more relevant ads.
@property (nonatomic, assign) GADGender gender;

// The user's birthday may be used to deliver more relevant ads.
@property (nonatomic, retain) NSDate *birthday;
- (void)setBirthdayWithMonth:(NSInteger)m day:(NSInteger)d year:(NSInteger)y;

// The user's current location may be used to deliver more relevant ads.
// However do not use Core Location just for advertising, make sure it is used
// for more beneficial reasons as well.  It is both a good idea and part of
// Apple's guidelines.
- (void)setLocationWithLatitude:(CGFloat)latitude longitude:(CGFloat)longitude
                       accuracy:(CGFloat)accuracyInMeters;

// When Core Location isn't available but the user's location is known supplying
// it here may deliver more relevant ads.  It can be any free-form text such as
// @"Champs-Elysees Paris" or @"94041 US".
- (void)setLocationWithDescription:(NSString *)locationDescription;

#pragma mark Contextual Information

// A keyword is a word or phrase describing the current activity of the user
// such as @"Sports Scores".  Each keyword is an NSString in the NSArray.  To
// clear the keywords set this to nil.
@property (nonatomic, retain) NSMutableArray *keywords;

// Convenience method for adding keywords one at a time such as @"Sports Scores"
// and then @"Football".
- (void)addKeyword:(NSString *)keyword;

#pragma mark -
#pragma mark Deprecated Methods

// Accesses the additionalParameters for the "GoogleAdmob" ad network. Please
// use -registerAdNetworkExtras: method above and pass an instance of
// GADAdMobExtras instead.
@property (nonatomic, retain) NSDictionary *additionalParameters;

// This property has been deprecated with the latest SDK releases. Please use
// testDevices.
@property (nonatomic, getter=isTesting) BOOL testing;

@end
