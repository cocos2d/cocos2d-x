//
//  GADAdMobExtras.h
//  Google Ads iOS SDK
//
//  Copyright (c) 2012 Google Inc. All rights reserved.
//
//  The additional parameters publishers may send to the AdMob network.
//

#import <Foundation/Foundation.h>

#import "GADAdNetworkExtras.h"

@interface GADAdMobExtras : NSObject <GADAdNetworkExtras>

@property (nonatomic, retain) NSDictionary *additionalParameters;

@end
