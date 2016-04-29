//
//  GADInAppPurchase.h
//  Google Mobile Ads SDK
//
//  Copyright 2013 Google Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GADModules.h"

/// Enum of the different statuses resulting from processing a purchase.
typedef NS_ENUM(NSInteger, GADInAppPurchaseStatus) {
  kGADInAppPurchaseStatusError = 0,          ///< Error occured while processing the purchase.
  kGADInAppPurchaseStatusSuccessful = 1,     ///< Purchase was completed successfully.
  kGADInAppPurchaseStatusCancel = 2,         ///< Purchase was cancelled by the user.
  kGADInAppPurchaseStatusInvalidProduct = 3  ///< Error occured while looking up the product.
};

/// The in-app purchase item to be purchased with the purchase flow handled by you, the
/// application developer.
/// Instances of this class are created and passed to your in-app purchase delegate when users click
/// a buy button. It is important to report the result of the purchase back to the SDK in order to
/// track metrics about the transaction.
@interface GADInAppPurchase : NSObject

/// The in-app purchase product ID.
@property(nonatomic, readonly, copy) NSString *productID;

/// The product quantity.
@property(nonatomic, readonly, assign) NSUInteger quantity;

/// The in-app purchase delegate object must call this method after handling the in-app purchase for
/// both successful and unsuccessful purchase attempts. This method reports ad conversion and
/// purchase status information to Google.
- (void)reportPurchaseStatus:(GADInAppPurchaseStatus)purchaseStatus;

@end
