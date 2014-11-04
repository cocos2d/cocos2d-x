
#include "store/CCStorePaymentTransactionWrapper.h"
#import <StoreKit/StoreKit.h>

NS_CC_EXTRA_BEGIN

StorePaymentTransactionWrapper* StorePaymentTransactionWrapper::createWithTransaction(void* transactionObj)
{
    StorePaymentTransactionWrapper* transaction = new StorePaymentTransactionWrapper();
    transaction->m_transactionObj = transactionObj;
    [(SKPaymentTransaction *)transactionObj retain];
    return transaction;
}

StorePaymentTransactionWrapper::~StorePaymentTransactionWrapper(void)
{
    [(SKPaymentTransaction *)m_transactionObj release];
}

NS_CC_EXTRA_END

