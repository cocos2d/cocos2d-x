
#import <StoreKit/StoreKit.h>

#include "store/CCStore.h"
#include "store/CCStoreProductsRequestDelegate.h"

USING_NS_CC_EXTRA;

class CCStoreReceiptVerifyRequestIOS;

@interface StoreIOS : NSObject < SKPaymentTransactionObserver, SKProductsRequestDelegate >
{
    CCStoreIsSandbox isSandbox_;
    CCStoreReceiptVerifyMode receiptVerifyMode_;
    NSString *receiptVerifyServerUrl_;

    StoreTransactionObserver *transactionObserver_;
    StoreProductsRequestDelegate *productRequestDelegate_;
    NSMutableDictionary *loadedProducts_;
    SKProductsRequest *productRequest_;
}

@property (nonatomic, assign) CCStoreIsSandbox isSandbox;
@property (nonatomic, assign) CCStoreReceiptVerifyMode receiptVerifyMode;
@property (nonatomic, retain) NSString *receiptVerifyServerUrl;

#pragma mark -
#pragma mark init

+ (StoreIOS *)sharedStore;
+ (void)purgeSharedStore;
- (id)init;
- (void)postInitWithTransactionObserver:(StoreTransactionObserver *)observer;

#pragma mark -
#pragma mark Making a Purchase

- (BOOL)canMakePurchases;
- (void)purchase:(SKProduct *)product;
- (void)restore;
- (void)finishTransaction:(SKPaymentTransaction *)transaction;

#pragma mark -
#pragma mark Retrieving Product Information

- (void)requestProductData:(NSSet *)productsId andDelegate:(StoreProductsRequestDelegate *)delegate;
- (void)cancelRequestProductData;
- (BOOL)isProductLoaded:(NSString *)productId;
- (SKProduct *)getProduct:(NSString *)productId;
- (void)cleanCachedProducts;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

#pragma mark -
#pragma mark Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void)transactionCompleted:(SKPaymentTransaction *)transaction andReceiptVerifyStatus:(int)receiptVerifyStatus;
- (void)transactionFailed:(SKPaymentTransaction *)transaction andReceiptVerifyStatus:(int)receiptVerifyStatus;
- (void)transactionRestored:(SKPaymentTransaction *)transaction andReceiptVerifyStatus:(int)receiptVerifyStatus;

#pragma mark -
#pragma mark Verifying Store Receipts

- (void)verifyTransactionReceipt:(SKPaymentTransaction *)transaction;

/* CCStoreReceiptVerifyRequestIOS */
- (void)verifyReceiptRequestFinished:(CCStoreReceiptVerifyRequestIOS *)handler;
- (void)verifyReceiptRequestFailed:(CCStoreReceiptVerifyRequestIOS *)handler;

#pragma mark -
#pragma mark helper

- (StorePaymentTransaction *)createStorePaymentTransaction:(SKPaymentTransaction *)transaction
                                        andReceiptVerifyStatus:(int)receiptVerifyStatus;

@end
