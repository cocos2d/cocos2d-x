
#include "store/CCStorePaymentTransaction.h"

NS_CC_EXTRA_BEGIN

StorePaymentTransaction*
StorePaymentTransaction::transactionWithState(StorePaymentTransactionWrapper* transactionWapper,
                                                CCStorePaymentTransactionState state,
                                                const char* transactionId,
                                                const char* productId,
                                                int quantity,
                                                double dateTime,
                                                int receiptDataLength,
                                                const void* receiptData,
                                                int errorCode,
                                                const char* errorDescription,
                                                StorePaymentTransaction* originalTransaction,
                                                CCStoreReceiptVerifyMode receiptVerifyMode,
                                                CCStoreReceiptVerifyStatus receiptVerifyStatus)
{
    StorePaymentTransaction* transaction = new StorePaymentTransaction();
    transaction->initWithState(transactionWapper,
                               state,
                               transactionId,
                               productId,
                               quantity,
                               dateTime,
                               receiptDataLength,
                               receiptData,
                               errorCode,
                               errorDescription,
                               originalTransaction,
                               receiptVerifyMode,
                               receiptVerifyStatus);
    transaction->autorelease();
    return transaction;
}

StorePaymentTransaction::~StorePaymentTransaction(void)
{
    CC_SAFE_RELEASE(m_originalTransaction);
    if (m_receiptData)
    {
        free(m_receiptData);
    }
    if (m_transactionWapper)
    {
        delete m_transactionWapper;
    }
    
    CCLOG("~~ StorePaymentTransaction::~StorePaymentTransaction()");
}

bool StorePaymentTransaction::initWithState(StorePaymentTransactionWrapper* transactionWapper,
                                              CCStorePaymentTransactionState state,
                                              const char* transactionId,
                                              const char* productId,
                                              int quantity,
                                              double dateTime,
                                              int receiptDataLength,
                                              const void* receiptData,
                                              int errorCode,
                                              const char* errorDescription,
                                              StorePaymentTransaction* originalTransaction,
                                              CCStoreReceiptVerifyMode receiptVerifyMode,
                                              CCStoreReceiptVerifyStatus receiptVerifyStatus)
{
    m_transactionWapper = transactionWapper;
    m_transactionState = state;
    m_transactionIdentifier = transactionId;
    m_productIdentifier = productId;
    m_quantity = quantity;
    m_dateTime = dateTime;
    m_receiptDataLength = receiptDataLength;
    if (receiptDataLength > 0)
    {
        m_receiptData = malloc(receiptDataLength + 1);
        memset(m_receiptData, 0, receiptDataLength + 1);
        memcpy(m_receiptData, receiptData, receiptDataLength);
    }
    else
    {
        m_receiptData = NULL;
    }
    m_errorCode = errorCode;
    m_errorDescription = errorDescription ? errorDescription : "";
    m_originalTransaction = originalTransaction;
    if (m_originalTransaction)
    {
        m_originalTransaction->retain();
    }
    
    m_receiptVerifyMode = receiptVerifyMode;
    m_receiptVerifyStatus = receiptVerifyStatus;
    
    return true;
}

#if CC_LUA_ENGINE_ENABLED > 0
const LuaValueDict StorePaymentTransaction::convertToLuaTable(void)
{
    LuaValueDict transaction_;
    
    transaction_["state"] = LuaValue::stringValue(CCStorePaymentTransactionStateNames[m_transactionState]);
    transaction_["transactionIdentifier"] = LuaValue::stringValue(m_transactionIdentifier);
    transaction_["productIdentifier"] = LuaValue::stringValue(m_productIdentifier);
    transaction_["quantity"] = LuaValue::intValue(m_quantity);
    transaction_["date"] = LuaValue::floatValue(m_dateTime);
    transaction_["errorCode"] = LuaValue::intValue(m_errorCode);
    transaction_["errorString"] = LuaValue::stringValue(m_errorDescription);
    transaction_["receiptVerifyMode"] = LuaValue::intValue(m_receiptVerifyMode);
    transaction_["receiptVerifyStatus"] = LuaValue::intValue(m_receiptVerifyStatus);
    
    if (m_receiptDataLength > 0)
    {
        // http://stackoverflow.com/questions/11242667/how-to-parse-apples-iap-receipt-mal-formatted-json
        transaction_["receipt"] = LuaValue::stringValue((const char*)(m_receiptData));
    }
    
    if (m_originalTransaction)
    {
        const LuaValueDict originalTransaction_ = m_originalTransaction->convertToLuaTable();
        transaction_["originalTransaction"] = LuaValue::dictValue(originalTransaction_);
    }
    
    return transaction_;
}
#endif

NS_CC_EXTRA_END
