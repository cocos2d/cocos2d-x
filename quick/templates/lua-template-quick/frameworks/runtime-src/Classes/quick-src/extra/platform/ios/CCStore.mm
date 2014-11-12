
#include "store/CCStore.h"

#import "platform/ios/CCStoreIOS.h"

#if CC_LUA_ENGINE_ENABLED > 0
extern "C" {
#include "lua.h"
}
#include "tolua_fix.h"
#endif

NS_CC_EXTRA_BEGIN

Store* Store::s_sharedStore = NULL;

Store* Store::sharedStore(void)
{
    if (!s_sharedStore)
    {
        s_sharedStore = new Store();
        s_sharedStore->init();
    }
    return s_sharedStore;
}

Store::~Store(void)
{
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_listener);
    }
#endif
    for (StorePaymentTransactionsIterator it = m_transactions.begin(); it != m_transactions.end(); ++it)
    {
        it->second->release();
    }
}

bool Store::init(void)
{
    return true;
}

void Store::purgeSharedStore(void)
{
    [StoreIOS purgeSharedStore];
    if (s_sharedStore)
    {
        delete s_sharedStore;
        s_sharedStore = NULL;
    }
}

void Store::postInitWithTransactionObserver(StoreTransactionObserver* observer)
{
    m_observer = observer;
    [[StoreIOS sharedStore] postInitWithTransactionObserver:this];
}

#if CC_LUA_ENGINE_ENABLED > 0
void Store::postInitWithTransactionListenerLua(LUA_FUNCTION listener)
{
    if (m_listener)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
    [[StoreIOS sharedStore] postInitWithTransactionObserver:this];
}
#endif

bool Store::canMakePurchases(void)
{
    return [[StoreIOS sharedStore] canMakePurchases];
}

void Store::loadProducts(Vector<std::string>& productsId, StoreProductsRequestDelegate* delegate)
{
    NSMutableSet* set = [NSMutableSet set];
    for (int i = 0; i < productsId.size(); ++i)
    {
        std::string productId = productsId.at(i);
        [set addObject:[NSString stringWithUTF8String: productId.c_str()]];
    }
    [[StoreIOS sharedStore] requestProductData:set andDelegate:delegate];
}

#if CC_LUA_ENGINE_ENABLED > 0
void Store::loadProductsLua(LUA_TABLE __LUA_TABLE__, LUA_FUNCTION callback)
{
    CC_UNUSED_PARAM(__LUA_TABLE__);
    if (m_isLoadProductsLuaNotCompleted) return;

    LuaEngine* engine = LuaEngine::getInstance();
    lua_State* L = engine->getLuaStack()->getLuaState();
    if (!lua_isfunction(L, -1) || !lua_istable(L, -2)) return;

    NSMutableSet* set = [NSMutableSet set];

                                                /* L: this table function */
    lua_pushnil(L);                             /* L: this table function query_key */
    /* lua_next() remove 'query_key', push 'next_key' */
    while (lua_next(L, -3) != 0)                /* L: this table function next_key value */
    {
        if (lua_isstring(L, -1))
        {
            const char* productId = lua_tostring(L, -1);
            if (productId)
            {
                [set addObject:[NSString stringWithUTF8String:productId]];
            }
        }
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);                          /* this table function next_key */
    }                                           /* this table function */

    m_isLoadProductsLuaNotCompleted = true;
    m_loadProductsCallback = callback;
    [[StoreIOS sharedStore] requestProductData:set andDelegate:this];
}
#endif

void Store::cancelLoadProducts(void)
{
    [[StoreIOS sharedStore] cancelRequestProductData];
}

bool Store::isProductLoaded(const char* productId)
{
    if (!productId) return false;
    return [[StoreIOS sharedStore] isProductLoaded:[NSString stringWithUTF8String:productId]];
}

bool Store::purchase(const char* productId)
{
    if (!productId) return false;
    SKProduct *product = [[StoreIOS sharedStore] getProduct:[NSString stringWithUTF8String:productId]];
    if (product)
    {
        [[StoreIOS sharedStore] purchase:product];
        return true;
    }
    return false;
}

void Store::restore(void)
{
    [[StoreIOS sharedStore] restore];
}

void Store::finishTransaction(StorePaymentTransaction *transaction)
{
    StorePaymentTransactionWrapper* wrapper = transaction->getTransactionWrapper();
    [[StoreIOS sharedStore] finishTransaction:(SKPaymentTransaction *)wrapper->getTransactionObj()];
    StorePaymentTransactionsIterator it = m_transactions.find(transaction->getTransactionIdentifier());
    if (it != m_transactions.end())
    {
        it->second->release();
        m_transactions.erase(it);
    }
}

#if CC_LUA_ENGINE_ENABLED > 0
void Store::finishTransactionLua(const char* transactionIdentifier)
{
    for (StorePaymentTransactionsIterator it = m_transactions.begin(); it != m_transactions.end(); ++it)
    {
        CCLOG("[Store] finishTransactionLua() exists tid: %s", it->first.c_str());
    }

    StorePaymentTransactionsIterator it = m_transactions.find(transactionIdentifier);
    if (it != m_transactions.end())
    {
        finishTransaction(it->second);
    }
    else
    {
        CCLOG("[Store] ERR, finishTransactionLua() invalid tid: %s", transactionIdentifier);
    }
}
#endif

CCStoreReceiptVerifyMode Store::getReceiptVerifyMode(void)
{
    return [StoreIOS sharedStore].receiptVerifyMode;
}

void Store::setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox)
{
    [StoreIOS sharedStore].receiptVerifyMode = mode;
    [StoreIOS sharedStore].isSandbox = isSandbox;
}

const char* Store::getReceiptVerifyServerUrl(void)
{
    return [[StoreIOS sharedStore].receiptVerifyServerUrl cStringUsingEncoding:NSUTF8StringEncoding];
}

void Store::setReceiptVerifyServerUrl(const char* url)
{
    [StoreIOS sharedStore].receiptVerifyServerUrl = [NSString stringWithUTF8String:url];
}

#pragma mark -
#pragma mark delegates

void Store::transactionCompleted(StorePaymentTransaction* transaction)
{
    m_transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (m_observer)
    {
        m_observer->transactionCompleted(transaction);
    }
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        passStorePaymentTransactionToLuaListener(transaction);
    }
#endif
}

void Store::transactionFailed(StorePaymentTransaction* transaction)
{
    m_transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (m_observer)
    {
        m_observer->transactionFailed(transaction);
    }
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        passStorePaymentTransactionToLuaListener(transaction);
    }
#endif
}

void Store::transactionRestored(StorePaymentTransaction* transaction)
{
    m_transactions[transaction->getTransactionIdentifier()] = transaction;
    transaction->retain();

    if (m_observer)
    {
        m_observer->transactionRestored(transaction);
    }
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        passStorePaymentTransactionToLuaListener(transaction);
    }
#endif
}

#if CC_LUA_ENGINE_ENABLED > 0
void Store::requestProductsCompleted(Vector<StoreProduct*>& products, vector<std::string*>& invalidProductsId)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    LuaValueDict event;
    LuaValueArray products_;

    for (int i = 0; i < products.size(); ++i)
    {
        StoreProduct* product = static_cast<StoreProduct*>(products.at(i));
        LuaValueDict product_;
        product_["productIdentifier"]    = LuaValue::stringValue(product->getProductIdentifier());
        product_["localizedTitle"]       = LuaValue::stringValue(product->getLocalizedTitle());
        product_["localizedDescription"] = LuaValue::stringValue(product->getLocalizedDescription());
        product_["priceLocale"]          = LuaValue::stringValue(product->getPriceLocale());
        product_["price"]                = LuaValue::floatValue(product->getPrice());
        products_.push_back(LuaValue::dictValue(product_));
    }
    event["products"] = LuaValue::arrayValue(products_);

    if (invalidProductsId.size()>0)
    {
        LuaValueArray invalidProductsId_;
        for (int i = 0; i < invalidProductsId.size(); ++i)
        {
            std::string *ccid = invalidProductsId.at(i);
            invalidProductsId_.push_back(LuaValue::stringValue(ccid->c_str()));
        }
        event["invalidProductsId"] = LuaValue::arrayValue(invalidProductsId_);
    }

    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(m_loadProductsCallback, 1);

    m_loadProductsCallback = 0;
    m_isLoadProductsLuaNotCompleted = false;
}

void Store::requestProductsFailed(int errorCode, const char* errorString)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    LuaValueDict event;
    event["errorCode"] = LuaValue::intValue(errorCode);
    event["errorString"] = LuaValue::stringValue(errorString);

    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(m_loadProductsCallback, 1);

    m_loadProductsCallback = 0;
    m_isLoadProductsLuaNotCompleted = false;
}
#endif

#pragma mark -
#pragma mark helper

#if CC_LUA_ENGINE_ENABLED > 0
void Store::passStorePaymentTransactionToLuaListener(StorePaymentTransaction* transaction)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

    LuaValueDict event;
    event["transaction"] = LuaValue::dictValue(transaction->convertToLuaTable());

    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(m_listener, 1);
}
#endif

NS_CC_EXTRA_END
