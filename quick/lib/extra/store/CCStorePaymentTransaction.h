
#ifndef __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_H_
#define __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_H_

#include "cocos2dx_extra.h"
#include "store/CCStorePaymentTransactionWrapper.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

NS_CC_EXTRA_BEGIN

typedef enum {
    CCStoreReceiptVerifyModeNone = 0,
    CCStoreReceiptVerifyModeDevice = 1,
    CCStoreReceiptVerifyModeServer
} CCStoreReceiptVerifyMode;

static const int CCStoreReceiptVerifyStatusUnknownError = -5;
static const int CCStoreReceiptVerifyStatusInvalidReceipt = -4;
static const int CCStoreReceiptVerifyStatusRequestFailed = -3;
static const int CCStoreReceiptVerifyStatusInvalidResult = -2;
static const int CCStoreReceiptVerifyStatusNone = -1;
static const int CCStoreReceiptVerifyStatusOK = 0;
typedef int CCStoreReceiptVerifyStatus;

typedef enum {
    CCStorePaymentTransactionStateNull = 0,
    CCStorePaymentTransactionStatePurchasing = 1,
    CCStorePaymentTransactionStatePurchased,
    CCStorePaymentTransactionStateFailed,
    CCStorePaymentTransactionStateRestored,
    CCStorePaymentTransactionStateCancelled,
} CCStorePaymentTransactionState;    

static const char* const CCStorePaymentTransactionStateNames[] = {
    "unknown",
    "purchasing",
    "purchased",
    "failed",
    "restored",
    "cancelled"
};

class StorePaymentTransaction : public cocos2d::Ref
{
public:
    static StorePaymentTransaction* transactionWithState(StorePaymentTransactionWrapper* transactionWapper,
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
                                                           CCStoreReceiptVerifyStatus receiptVerifyStatus);
    ~StorePaymentTransaction(void);
    
    StorePaymentTransactionWrapper* getTransactionWrapper(void)
    {
        return m_transactionWapper;
    }
    
    CCStorePaymentTransactionState getTransactionState(void)
    {
        return m_transactionState;
    }
    
    const std::string& getTransactionIdentifier(void)
    {
        return m_transactionIdentifier;
    }
    
    const std::string& getProductIdentifier(void)
    {
        return m_productIdentifier;
    }
    
    int getQuantity(void)
    {
        return m_quantity;
    }
    
    double getDateTime(void)
    {
        return m_dateTime;
    }
    
    int getReceiptDataLength(void)
    {
        return m_receiptDataLength;
    }
    
    const void* const getReceiptData(void)
    {
        return m_receiptData;
    }
    
    int getErrorCode(void)
    {
        return m_errorCode;
    }
    
    const std::string& getErrorDescription(void)
    {
        return m_errorDescription;
    }
    
    StorePaymentTransaction* getOriginalTransaction(void)
    {
        return m_originalTransaction;
    }
        
    CCStoreReceiptVerifyMode getReceiptVerifyMode(void)
    {
        return m_receiptVerifyMode;
    }
    
    int getReceiptVerifyStatus(void)
    {
        return m_receiptVerifyStatus;
    }
    
#if CC_LUA_ENGINE_ENABLED > 0
    const cocos2d::LuaValueDict convertToLuaTable(void);
#endif
    
private:
    StorePaymentTransaction(void) {}
    
    bool initWithState(StorePaymentTransactionWrapper *transactionWapper,
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
                       CCStoreReceiptVerifyStatus receiptVerifyStatus);
    
    StorePaymentTransactionWrapper*   m_transactionWapper;
    CCStorePaymentTransactionState      m_transactionState;
    std::string                         m_transactionIdentifier;
    std::string                         m_productIdentifier;
    int                                 m_quantity;
    double                              m_dateTime;
    int                                 m_receiptDataLength;
    void*                               m_receiptData;
    int                                 m_errorCode;
    std::string                         m_errorDescription;
    StorePaymentTransaction*          m_originalTransaction;
    CCStoreReceiptVerifyMode            m_receiptVerifyMode;
    CCStoreReceiptVerifyStatus          m_receiptVerifyStatus;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_PAYMENT_TRANSACTION_H_
