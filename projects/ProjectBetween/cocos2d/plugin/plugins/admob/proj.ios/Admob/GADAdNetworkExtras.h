//
//  GADAdNetworkExtras.h
//  Google Ads iOS SDK
//
//  Copyright (c) 2012 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADModules.h"

/// An object implementing this protocol contains information set by the publisher on the client
/// device for a particular ad network.
///
/// Ad networks should create an 'extras' object implementing this protocol for their publishers to
/// use.
@protocol GADAdNetworkExtras<NSObject>
@end
