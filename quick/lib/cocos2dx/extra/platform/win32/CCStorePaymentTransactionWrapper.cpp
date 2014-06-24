#include "store/CCStorePaymentTransactionWrapper.h"

NS_CC_EXTRA_BEGIN

StorePaymentTransactionWrapper* StorePaymentTransactionWrapper::createWithTransaction(void* transactionObj)
{
    StorePaymentTransactionWrapper* transaction = new StorePaymentTransactionWrapper();
    transaction->m_transactionObj = transactionObj;
    return transaction;
}

StorePaymentTransactionWrapper::~StorePaymentTransactionWrapper(void)
{

}

NS_CC_EXTRA_END