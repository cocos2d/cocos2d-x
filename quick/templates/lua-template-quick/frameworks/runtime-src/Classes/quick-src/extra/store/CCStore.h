
#ifndef  __CC_EXTENSION_CCSTORE_H_
#define  __CC_EXTENSION_CCSTORE_H_

#include "cocos2dx_extra.h"
#include "store/CCStoreProduct.h"
#include "store/CCStorePaymentTransaction.h"
#include "store/CCStoreTransactionObserver.h"
#include "store/CCStoreProductsRequestDelegate.h"

NS_CC_EXTRA_BEGIN

typedef bool CCStoreIsSandbox;

typedef std::map<const std::string, StorePaymentTransaction*> StorePaymentTransactions;
typedef StorePaymentTransactions::iterator                    StorePaymentTransactionsIterator;

class Store: public StoreTransactionObserver
#if CC_LUA_ENGINE_ENABLED > 0
, public StoreProductsRequestDelegate
#endif
{
public:
    static Store* sharedStore(void);
    static void purgeSharedStore(void);
    
    ~Store(void);
    
    void postInitWithTransactionObserver(StoreTransactionObserver* observer);
#if CC_LUA_ENGINE_ENABLED > 0
    void postInitWithTransactionListenerLua(cocos2d::LUA_FUNCTION listener);
#endif
    
    bool canMakePurchases(void);
    
    void loadProducts(Vector<std::string>& productsId, StoreProductsRequestDelegate* delegate);
#if CC_LUA_ENGINE_ENABLED > 0
    void loadProductsLua(cocos2d::LUA_TABLE __LUA_TABLE__, cocos2d::LUA_FUNCTION callback);
#endif
    void cancelLoadProducts(void);
    bool isProductLoaded(const char* productId);
    bool purchase(const char* productId);
    void restore(void);
    void finishTransaction(StorePaymentTransaction *transaction);
#if CC_LUA_ENGINE_ENABLED > 0
    void finishTransactionLua(const char* transactionIdentifier);
#endif

    CCStoreReceiptVerifyMode getReceiptVerifyMode(void);
    void setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox = true);
    const char* getReceiptVerifyServerUrl(void);
    void setReceiptVerifyServerUrl(const char* url);
    
#pragma mark -
#pragma mark delegates
    
    virtual void transactionCompleted(StorePaymentTransaction* transaction);
    virtual void transactionFailed(StorePaymentTransaction* transaction);
    virtual void transactionRestored(StorePaymentTransaction* transaction);
    
#if CC_LUA_ENGINE_ENABLED > 0
    virtual void requestProductsCompleted(Vector<StoreProduct*>& products, vector<std::string*>& invalidProductsId);
    virtual void requestProductsFailed(int errorCode, const char* errorString);
#endif
    
private:
    Store(void)
    : m_observer(NULL)
#if CC_LUA_ENGINE_ENABLED > 0
    , m_listener(0)
    , m_loadProductsCallback(0)
#endif
    , m_isLoadProductsLuaNotCompleted(false)
    {
    }
    bool init(void);
    
    static Store*             s_sharedStore;
    StoreTransactionObserver* m_observer;
#if CC_LUA_ENGINE_ENABLED > 0
    cocos2d::LUA_FUNCTION       m_listener;
    cocos2d::LUA_FUNCTION       m_loadProductsCallback;
#endif
    bool                        m_isLoadProductsLuaNotCompleted;
    StorePaymentTransactions  m_transactions;
    
#if CC_LUA_ENGINE_ENABLED > 0
    void passStorePaymentTransactionToLuaListener(StorePaymentTransaction* transaction);
#endif
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_H_
