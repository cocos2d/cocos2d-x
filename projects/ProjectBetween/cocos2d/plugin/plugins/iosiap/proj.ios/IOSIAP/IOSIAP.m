/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "IOSIAP.h"
#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation IOSIAP
@synthesize debug,_isServerMode;
NSSet * _productIdentifiers;
NSArray *_productArray;
bool _isAddObserver = false;
//productsRequest;
SKProductsRequest * _productsRequest;
//productTransation
NSArray * _transactionArray;

-(void) configDeveloperInfo: (NSMutableDictionary*) cpInfo{
}
- (void) payForProduct: (NSMutableDictionary*) cpInfo{
    NSString * pid = [cpInfo objectForKey:@"productId"];
    SKProduct *skProduct = [self getProductById:pid];
    if(skProduct){
        SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:skProduct];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
        OUTPUT_LOG(@"add PaymentQueue");
    }
}
- (void) setDebugMode: (BOOL) _debug{
    self.debug = _debug;
}
- (NSString*) getSDKVersion{
    return @"1.0";
}

- (NSString*) getPluginVersion{
    return @"1.0";
}

/*------------------------IAP functions-------------------------------*/
-(void)setServerMode{
    _isServerMode = true;
}
-(void)requestProducts:(NSString*) paramMap{
    [self setDebug:true];
    if(!_isAddObserver){
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        _isAddObserver = true;
    }
    NSArray *producIdArray = [paramMap componentsSeparatedByString:@","];
    _productIdentifiers = [[NSSet alloc] initWithArray:producIdArray];
    OUTPUT_LOG(@"param is %@",_productIdentifiers);
    _productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers];
    _productsRequest.delegate = self;
    [_productsRequest start];

}
-(NSString *)parseProductToString:(NSArray *) products{
    return @"1";
}
-(SKProduct *)getProductById:(NSString *)productid{
    for (SKProduct * skProduct in _productArray) {
        if([skProduct.productIdentifier isEqualToString:productid]){
            return skProduct;
        }
    }
    return NULL;
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    OUTPUT_LOG(@"Failed to load list of products.");
     [IAPWrapper onRequestProduct:self withRet:RequestFail withProducts:NULL];
    _productsRequest = nil;
}

//SKProductsRequestDelegate needed
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    _productArray = response.products;
    NSArray * skProducts = response.products;
    for (SKProduct * skProduct in skProducts) {
        OUTPUT_LOG(@"Found product: %@ %@ %0.2f",
              skProduct.productIdentifier,
              skProduct.localizedTitle,
              skProduct.price.floatValue);
    }
    [IAPWrapper onRequestProduct:self withRet:RequestSuccees withProducts:skProducts];
}

//SKPaymentTransactionObserver needed
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions{
    _transactionArray = transactions;
    for (SKPaymentTransaction * transaction in transactions) {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
            default:
                break;
        }
    };
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    NSString *receipt = nil;
    if(_isServerMode){
        if (floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_6_1) {
            // iOS 6.1 or earlier.
            // Use SKPaymentTransaction's transactionReceipt.
            receipt = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];

        } else {
            // iOS 7 or later.
            NSURL *receiptURL = [[NSBundle mainBundle] appStoreReceiptURL];
            NSData *recData = [[NSData dataWithContentsOfURL:receiptURL] base64EncodedDataWithOptions:0];
            receipt = [[NSString alloc] initWithData:recData encoding:NSUTF8StringEncoding];
            if (!receipt) {
                receipt = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];
            }
        }
        [IAPWrapper onPayResult:self withRet:PaymentTransactionStatePurchased withMsg:receipt];
    }else{
        [self finishTransaction: transaction.payment.productIdentifier];
        [IAPWrapper onPayResult:self withRet:PaymentTransactionStatePurchased withMsg:@""];
    }
    
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    OUTPUT_LOG(@"restoreTransaction...");
    [self finishTransaction:transaction.payment.productIdentifier];
    [IAPWrapper onPayResult:self withRet:PaymentTransactionStateRestored withMsg:@""];
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    OUTPUT_LOG(@"failedTransaction...");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        OUTPUT_LOG(@"Transaction error: %@", transaction.error.localizedDescription);
        [[[UIAlertView alloc] initWithTitle:@"支付结果" message:transaction.error.localizedDescription delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil] show];
    }
    
    [self finishTransaction:transaction.payment.productIdentifier];
    [IAPWrapper onPayResult:self withRet:PaymentTransactionStateFailed withMsg:@""];
}

- (void)restoreCompletedTransactions {
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

-(void) finishTransaction:(NSString *)productId{
    SKPaymentTransaction *transaction = [self getTranscationByProductId:productId];
    if(transaction){
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
}
-(SKPaymentTransaction *) getTranscationByProductId:(NSString *)productId{
    for(SKPaymentTransaction *tran in _transactionArray){
        if([tran.payment.productIdentifier isEqualToString:productId]){
            return tran;
        }
    }
    return NULL;
}
- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length {
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] ;
}
@end
