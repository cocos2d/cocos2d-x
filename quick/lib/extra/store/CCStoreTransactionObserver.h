
#ifndef __CC_EXTENSION_CCSTORE_TRANSACTION_OBSERVER_H_
#define __CC_EXTENSION_CCSTORE_TRANSACTION_OBSERVER_H_

#include "cocos2dx_extra.h"
#include "store/CCStorePaymentTransaction.h"

NS_CC_EXTRA_BEGIN

class StoreTransactionObserver
{
public:
    virtual void transactionCompleted(StorePaymentTransaction* transaction) = 0;
    virtual void transactionFailed(StorePaymentTransaction* transaction) = 0;
    virtual void transactionRestored(StorePaymentTransaction* transaction) = 0;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_TRANSACTION_OBSERVER_H_
