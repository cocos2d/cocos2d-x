
#ifndef __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_WRAPPER_H_
#define __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_WRAPPER_H_

#include "cocos2dx_extra.h"
#include "cocos2d.h"

NS_CC_EXTRA_BEGIN

class StorePaymentTransactionWrapper
{
public:
    static StorePaymentTransactionWrapper* createWithTransaction(void* transactionObj);
    ~StorePaymentTransactionWrapper(void);
    
    void* getTransactionObj(void)
    {
        return m_transactionObj;
    }
    
private:
    StorePaymentTransactionWrapper(void)
    : m_transactionObj(NULL)
    {
    }
    
    void* m_transactionObj;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_WRAPPER_H_
