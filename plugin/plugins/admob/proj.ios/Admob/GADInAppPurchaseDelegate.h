//
//  GADInAppPurchaseDelegate.h
//  Google AdMob Ads SDK
//
//  Copyright 2013 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADModules.h"

@class GADInAppPurchase;

/// In-app purchase (IAP) delegate protocol.
@protocol GADInAppPurchaseDelegate<NSObject>

/// Called when the user clicks on the buy button of an IAP ad. After the receiver handles the
/// purchase, it must call the purchase object's reportPurchaseStatus: method.
- (void)didReceiveInAppPurchase:(GADInAppPurchase *)purchase;

@end
