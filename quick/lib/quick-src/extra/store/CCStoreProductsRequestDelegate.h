
#ifndef __CC_EXTENSION_CCSTORE_PRODUCTS_REQUEST_DELEGATE_H_
#define __CC_EXTENSION_CCSTORE_PRODUCTS_REQUEST_DELEGATE_H_

#include "cocos2dx_extra.h"

NS_CC_EXTRA_BEGIN

static const int CCStoreProductsRequestErrorPreviousRequestNotCompleted = -2;
static const int CCStoreProductsRequestErrorCancelled = -1;

class StoreProductsRequestDelegate
{
public:
    virtual void requestProductsCompleted(Vector<StoreProduct*>& products,
                                          vector<std::string*>& invalidProductsId) = 0;
    virtual void requestProductsFailed(int errorCode, const char* errorString) = 0;
};

NS_CC_EXTRA_END

#endif // __CC_EXTENSION_CCSTORE_PRODUCTS_REQUEST_DELEGATE_H_
