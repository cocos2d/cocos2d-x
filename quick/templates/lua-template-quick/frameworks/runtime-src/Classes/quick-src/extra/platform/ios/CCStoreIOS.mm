
#import "platform/ios/CCStoreIOS.h"
#import "platform/ios/CCStoreReceiptVerifyRequestIOS.h"
#import "platform/ios/json/SBJSON.h"

#include "crypto/CCCrypto.h"
#include <string>

#ifndef utf8cstr
#define utf8cstr(nsstr) (nsstr ? [nsstr cStringUsingEncoding:NSUTF8StringEncoding] : "")
#endif

@implementation StoreIOS

static StoreIOS *s_sharedStore;
static const char* const APPSTORE_RECEIPT_VERIFY_URL = "https://buy.itunes.apple.com/verifyReceipt";
static const char* const SANDBOX_RECEIPT_VERIFY_URL = "https://sandbox.itunes.apple.com/verifyReceipt";

@synthesize isSandbox = isSandbox_;
@synthesize receiptVerifyMode = receiptVerifyMode_;
@synthesize receiptVerifyServerUrl = receiptVerifyServerUrl_;

#pragma mark -
#pragma mark init

+ (StoreIOS *)sharedStore
{
    if (!s_sharedStore)
    {
        s_sharedStore = [[StoreIOS alloc] init];
    }
    return s_sharedStore;
}

+ (void) purgeSharedStore
{
    if (s_sharedStore)
    {
        [s_sharedStore release];
    }
}

- (id)init
{
    self = [super init];
    if (self)
    {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        loadedProducts_ = [NSMutableDictionary dictionaryWithCapacity:50];
        [loadedProducts_ retain];
        receiptVerifyMode_ = CCStoreReceiptVerifyModeNone;
    }
    return self;
}

- (void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [loadedProducts_ release];
    [productRequest_ release];
    [super dealloc];
    s_sharedStore = NULL;
}

- (void)postInitWithTransactionObserver:(StoreTransactionObserver *)observer
{
    transactionObserver_ = observer;
}

#pragma mark -
#pragma mark Making a Purchase

- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}

- (void)purchase:(SKProduct *)product
{
    CCLOG("[CCStore_obj] purchase() pid: %s", utf8cstr(product.productIdentifier));
    [[SKPaymentQueue defaultQueue] addPayment:[SKPayment paymentWithProduct:product]];
}

- (void)restore
{
    CCLOG("[CCStore_obj] restore()");
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)finishTransaction:(SKPaymentTransaction *)transaction
{
    CCLOG("[CCStore_obj] finishTransaction() tid: %s",  utf8cstr(transaction.transactionIdentifier));
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

#pragma mark -
#pragma mark Retrieving Product Information

- (void) requestProductData:(NSSet *)productsId andDelegate:(StoreProductsRequestDelegate *)delegate
{
    if (productRequest_)
    {
        delegate->requestProductsFailed(CCStoreProductsRequestErrorPreviousRequestNotCompleted,
                                        "CCStoreProductsRequestErrorPreviousRequestNotCompleted");
        return;
    }

#if COCOS2D_DEBUG > 0
    for (id productId in productsId)
    {
        CCLOG("[CCStore_obj] requestProductData() pid: %s", utf8cstr(productId));
    }
#endif

    productRequestDelegate_ = delegate;
    SKProductsRequest *request = [[SKProductsRequest alloc] initWithProductIdentifiers:productsId];
    request.delegate = self;
    [request autorelease];
    [request start];
    productRequest_ = request;
}

- (void)cancelRequestProductData
{
    if (productRequest_)
    {
        [productRequest_ cancel];
        productRequest_ = nil;
        productRequestDelegate_->requestProductsFailed(CCStoreProductsRequestErrorCancelled,
                                                       "CCStoreProductsRequestErrorCancelled");
        productRequestDelegate_ = nil;
    }
}

- (BOOL)isProductLoaded:(NSString *)productId
{
    return [loadedProducts_ objectForKey:productId] != nil;
}

- (SKProduct *)getProduct:(NSString *)productId
{
    return [loadedProducts_ objectForKey:productId];
}

- (void)cleanCachedProducts
{
    [loadedProducts_ removeAllObjects];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    Vector<StoreProduct*> ccproducts(response.products.count);
    for (int i = 0; i < response.products.count; ++i)
    {
        // cache loaded product
        SKProduct* product = [response.products objectAtIndex:i];
        [loadedProducts_ setObject:product forKey:product.productIdentifier];

        // convert SKProduct to StoreProduct
        StoreProduct* ccproduct = StoreProduct::productWithId(utf8cstr(product.productIdentifier),
                                                                  utf8cstr(product.localizedTitle),
                                                                  utf8cstr(product.localizedDescription),
                                                                  [product.price floatValue],
                                                                  utf8cstr(product.priceLocale.localeIdentifier));
        ccproducts.pushBack(ccproduct);
        CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() get pid: %s", utf8cstr(product.productIdentifier));
    }

    vector<std::string*> ccinvalidProductsId;
    if (response.invalidProductIdentifiers.count > 0)
    {
        ccinvalidProductsId.reserve(response.invalidProductIdentifiers.count);
        for (int i = 0; i < response.invalidProductIdentifiers.count; ++i)
        {
            NSString* productId = [response.invalidProductIdentifiers objectAtIndex:i];
            std::string *ccid = new std::string(utf8cstr(productId));
            ccinvalidProductsId.push_back(ccid);
            CCLOG("[CCStore_obj] productsRequestDidReceiveResponse() invalid pid: %s", utf8cstr(productId));
        }
    }

    request.delegate = nil;
    productRequest_ = nil;
    productRequestDelegate_->requestProductsCompleted(ccproducts, ccinvalidProductsId);
    productRequestDelegate_ = NULL;
    
    for (int i=0; i<ccinvalidProductsId.size(); i++) {
        delete ccinvalidProductsId.at(i);
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    request.delegate = nil;
    productRequest_ = nil;
    productRequestDelegate_->requestProductsFailed(error.code, utf8cstr(error.localizedDescription));
    productRequestDelegate_ = NULL;
}

#pragma mark -
#pragma mark Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (int i = 0; i < [transactions count]; ++i)
    {
        SKPaymentTransaction *transaction = [transactions objectAtIndex:i];
        if (transaction.transactionState != SKPaymentTransactionStatePurchasing)
        {
            CCLOG("[CCStore_obj] paymentQueueUpdatedTransactions() tid: %s",
                  utf8cstr(transaction.transactionIdentifier));
        }

        /**
         enum {
         SKPaymentTransactionStatePurchasing,
         SKPaymentTransactionStatePurchased,
         SKPaymentTransactionStateFailed,
         SKPaymentTransactionStateRestored
         };
         typedef NSInteger SKPaymentTransactionState;

         SKPaymentTransactionStatePurchasing:
         The transaction is being processed by the App Store.

         SKPaymentTransactionStatePurchased:
         The App Store successfully processed payment. Your application should provide
         the content the user purchased.

         SKPaymentTransactionStateFailed:
         The transaction failed. Check the error property to determine what happened.

         SKPaymentTransactionStateRestored:
         This transaction restores content previously purchased by the user.
         Read the originalTransaction property to obtain information about the original purchase.
         */
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                CCLOG("transaction '%s' SKPaymentTransactionStatePurchased",
                      [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                if (receiptVerifyMode_ != CCStoreReceiptVerifyModeNone)
                {
                    [self verifyTransactionReceipt:transaction];
                }
                else
                {
                    [self transactionCompleted:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusNone];
                }
                break;
            case SKPaymentTransactionStateFailed:
                CCLOG("transaction '%s' SKPaymentTransactionStateFailed",
                      [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                CCLOG("error: %s",
                      [[transaction.error localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
                [self transactionFailed:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusNone];
                break;
            case SKPaymentTransactionStateRestored:
                CCLOG("transaction '%s' SKPaymentTransactionStateRestored",
                      [transaction.transactionIdentifier cStringUsingEncoding:NSUTF8StringEncoding]);
                [self transactionRestored:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusNone];
                break;
        }
    }
}
- (void)transactionCompleted:(SKPaymentTransaction *)transaction
      andReceiptVerifyStatus:(int)receiptVerifyStatus
{
    transactionObserver_->transactionCompleted([self createStorePaymentTransaction:transaction
                                                              andReceiptVerifyStatus:receiptVerifyStatus]);
}

- (void)transactionFailed:(SKPaymentTransaction *)transaction
   andReceiptVerifyStatus:(int)receiptVerifyStatus
{
    transactionObserver_->transactionFailed([self createStorePaymentTransaction:transaction
                                                           andReceiptVerifyStatus:receiptVerifyStatus]);
}

- (void)transactionRestored:(SKPaymentTransaction *)transaction
     andReceiptVerifyStatus:(int)receiptVerifyStatus;
{
    transactionObserver_->transactionRestored([self createStorePaymentTransaction:transaction
                                                             andReceiptVerifyStatus:receiptVerifyStatus]);
}

#pragma mark -
#pragma mark Verifying Store Receipts

- (void)verifyTransactionReceipt:(SKPaymentTransaction *)transaction
{
    if (transaction.transactionState != SKPaymentTransactionStatePurchased) return;

    CCLOG("[CCStore_obj] verifyTransactionReceipt() tid: %s", utf8cstr(transaction.transactionIdentifier));

    // convert receipt to JSON string
    int length = [transaction.transactionReceipt length];
    char buffer[2 * length];
    int dataUsed = Crypto::encodeBase64((const char*)[transaction.transactionReceipt bytes], length, buffer, 2 * length);
    if (dataUsed <= 0)
    {
        [self transactionCompleted:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusUnknownError];
        return;
    }

    NSMutableDictionary* verifyData = [NSMutableDictionary dictionary];
    [verifyData setObject:[NSString stringWithUTF8String:buffer] forKey:@"receipt-data"];

    BOOL verifyOnServer = (receiptVerifyMode_ == CCStoreReceiptVerifyModeServer) && receiptVerifyServerUrl_ && ![receiptVerifyServerUrl_ isEqual:@""];
    if (verifyOnServer)
    {
        [verifyData setObject:isSandbox_ ? @"true" : @"false" forKey:@"receipt-issandbox"];
    }

    SBJsonWriter *writer = [[SBJsonWriter alloc] init];
    NSString *postData = [writer stringWithObject:verifyData];
    [writer release];

    // create request
    const char* url = NULL;
    if (verifyOnServer)
    {
        url = [receiptVerifyServerUrl_ UTF8String];
    }
    else
    {
        url = isSandbox_ ? SANDBOX_RECEIPT_VERIFY_URL : APPSTORE_RECEIPT_VERIFY_URL;
    }
    CCStoreReceiptVerifyRequestIOS* handler = CCStoreReceiptVerifyRequestIOS::create(self, transaction, url);

    handler->getRequest()->addRequestHeader("Content-Type: application/json");
    handler->getRequest()->setPOSTData([postData cStringUsingEncoding:NSUTF8StringEncoding]);
    handler->getRequest()->start();
}

- (void)verifyReceiptRequestFinished:(CCStoreReceiptVerifyRequestIOS *)handler
{
    SKPaymentTransaction* transaction = handler->getTransaction();
    const string responseString = handler->getRequest()->getResponseString();

    CCLOG("[CCStore_obj] verify receipt finished, pid: %s\n  response:\n%s\n\n",
          utf8cstr(transaction.payment.productIdentifier),
          responseString.c_str());

    // parser JSON string
    NSString* nsresponseString = [NSString stringWithCString:responseString.c_str() encoding:NSUTF8StringEncoding];
    SBJsonParser *parser = [[SBJsonParser alloc] init];
    NSDictionary *jsonData = [parser objectWithString:nsresponseString];
    [parser release];

    // check result
    if (jsonData == nil || [jsonData count] == 0)
    {
        // invalid JSON string
        [self transactionFailed:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusInvalidResult];
    }
    else if ([jsonData objectForKey:@"status"] && [[jsonData objectForKey:@"status"] intValue] == 0)
    {
        // status is ok, do more checks
        BOOL isValidReceipt = NO;
        /**
         AppStore receipt format, 2012-06-13:

         {
         "receipt":{
         "original_purchase_date_pst":"2012-06-12 20:06:51 America/Los_Angeles",
         "original_transaction_id":"1000000051068416",
         "original_purchase_date_ms":"1339556811043",
         "transaction_id":"1000000051068416",
         "quantity":"1",
         "product_id":"com.qeeplay.games.XXX.YYY",
         "bvrs":"0000",
         "purchase_date_ms":"1339556811043",
         "purchase_date":"2012-06-13 03:06:51 Etc/GMT",
         "original_purchase_date":"2012-06-13 03:06:51 Etc/GMT",
         "purchase_date_pst":"2012-06-12 20:06:51 America/Los_Angeles",
         "bid":"com.qeeplay.games.XXX",
         "item_id":"11111111"
         },
         "status":0
         }
         */
        do
        {
            NSDictionary *receiptData = [jsonData objectForKey:@"receipt"];
            if (receiptData == nil)
            {
                break;
            }

            // SKPaymentTransaction *transaction = transaction;
            NSString *transactionId = [receiptData objectForKey:@"transaction_id"];
            if (!transactionId || [transaction.transactionIdentifier compare:transactionId] != NSOrderedSame)
            {
                // check failed
                break;
            }

            NSString *productIdentifier = [receiptData objectForKey:@"product_id"];
            if (!productIdentifier || [transaction.payment.productIdentifier compare:productIdentifier] != NSOrderedSame)
            {
                break;
            }

            // receipt is valid
            isValidReceipt = YES;
        } while (NO);

        if (isValidReceipt)
        {
            [self transactionCompleted:transaction
                andReceiptVerifyStatus:CCStoreReceiptVerifyStatusOK];
        }
        else
        {
            [self transactionFailed:transaction
             andReceiptVerifyStatus:CCStoreReceiptVerifyStatusInvalidReceipt];
        }
    }
    else
    {
        [self transactionFailed:transaction
         andReceiptVerifyStatus:[[jsonData objectForKey:@"status"] intValue]];
    }
}

- (void)verifyReceiptRequestFailed:(CCStoreReceiptVerifyRequestIOS *)handler
{
    SKPaymentTransaction* transaction = handler->getTransaction();
    const string responseString = handler->getRequest()->getResponseString();

    CCLOG("[CCStore_obj] WARN, verify receipt failed(), pid: %s\n  response:\n%s\n\n",
          utf8cstr(transaction.payment.productIdentifier),
          responseString.c_str());

    [self transactionFailed:transaction andReceiptVerifyStatus:CCStoreReceiptVerifyStatusRequestFailed];
}


#pragma mark -
#pragma mark helper

- (StorePaymentTransaction *)createStorePaymentTransaction:(SKPaymentTransaction *)transaction
                                        andReceiptVerifyStatus:(int)receiptVerifyStatus
{
    StorePaymentTransactionWrapper* transactionWapper;
    transactionWapper = StorePaymentTransactionWrapper::createWithTransaction(transaction);

    const char *ccid        = utf8cstr(transaction.transactionIdentifier);
    const char *ccproductId = utf8cstr(transaction.payment.productIdentifier);
    int quantity            = transaction.payment.quantity;
    double dateTime         = [transaction.transactionDate timeIntervalSince1970];
    int receiptDataLength   = 0;
    const void *receiptData = NULL;
    int errorCode           = 0;
    const char *errorDescription = NULL;

    CCStorePaymentTransactionState ccstate = CCStorePaymentTransactionStateNull;
    switch (transaction.transactionState)
    {
        case SKPaymentTransactionStateFailed:
            errorCode = transaction.error.code;
            /**
             enum {
             SKErrorUnknown,
             SKErrorClientInvalid,       // client is not allowed to issue the request, etc.
             SKErrorPaymentCancelled,    // user cancelled the request, etc.
             SKErrorPaymentInvalid,      // purchase identifier was invalid, etc.
             SKErrorPaymentNotAllowed    // this device is not allowed to make the payment
             };
             */
            if (errorCode == SKErrorPaymentCancelled)
            {
                ccstate = CCStorePaymentTransactionStateCancelled;
            }
            else
            {
                ccstate = CCStorePaymentTransactionStateFailed;
            }
            errorDescription = utf8cstr(transaction.error.localizedDescription);
            break;
        case SKPaymentTransactionStatePurchased:
            ccstate = CCStorePaymentTransactionStatePurchased;
            receiptDataLength = transaction.transactionReceipt.length;
            receiptData = transaction.transactionReceipt.bytes;
            break;
        case SKPaymentTransactionStatePurchasing:
            ccstate = CCStorePaymentTransactionStatePurchasing;
            break;
        case SKPaymentTransactionStateRestored:
            ccstate = CCStorePaymentTransactionStateRestored;
    }

    if (transaction.originalTransaction)
    {
        StorePaymentTransaction *ccoriginalTransaction;
        ccoriginalTransaction = [self createStorePaymentTransaction:transaction.originalTransaction
                                               andReceiptVerifyStatus:CCStoreReceiptVerifyStatusNone];
        return StorePaymentTransaction::transactionWithState(transactionWapper,
                                                               ccstate,
                                                               ccid,
                                                               ccproductId,
                                                               quantity,
                                                               dateTime,
                                                               receiptDataLength,
                                                               receiptData,
                                                               errorCode,
                                                               errorDescription,
                                                               ccoriginalTransaction,
                                                               receiptVerifyMode_,
                                                               receiptVerifyStatus);
    }
    else
    {
        return StorePaymentTransaction::transactionWithState(transactionWapper,
                                                               ccstate,
                                                               ccid,
                                                               ccproductId,
                                                               quantity,
                                                               dateTime,
                                                               receiptDataLength,
                                                               receiptData,
                                                               errorCode,
                                                               errorDescription,
                                                               NULL,
                                                               receiptVerifyMode_,
                                                               receiptVerifyStatus);
    }
}

@end
