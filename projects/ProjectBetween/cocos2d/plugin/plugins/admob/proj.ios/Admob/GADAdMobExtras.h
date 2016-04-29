//
//  GADAdMobExtras.h
//  Google Ads iOS SDK
//
//  Copyright (c) 2012 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADAdNetworkExtras.h"
#import "GADModules.h"

@interface GADAdMobExtras : NSObject<GADAdNetworkExtras>

/// The additional parameters publishers may send to the AdMob network.
@property(nonatomic, copy) NSDictionary *additionalParameters;

@end
