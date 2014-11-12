
#import <StoreKit/StoreKit.h>
#import "platform/ios/CCStoreIOS.h"

#include "base/CCRef.h"
#include "network/CCHTTPRequestDelegate.h"
#include "network/CCHTTPRequest.h"

USING_NS_CC_EXTRA;

class CCStoreReceiptVerifyRequestIOS : public cocos2d::Ref, public HTTPRequestDelegate
{
public:
    static CCStoreReceiptVerifyRequestIOS* create(StoreIOS* store,
                                                  SKPaymentTransaction* transaction,
                                                  const char* url);
    ~CCStoreReceiptVerifyRequestIOS(void);

    HTTPRequest* getRequest(void)
    {
        return m_request;
    }

    SKPaymentTransaction* getTransaction(void)
    {
        return m_transaction;
    }

    virtual void requestFinished(HTTPRequest* request);
    virtual void requestFailed(HTTPRequest* request);

private:
    bool init(StoreIOS* store,
              SKPaymentTransaction* transaction,
              const char* url);

    StoreIOS*             m_store;
    HTTPRequest*          m_request;
    SKPaymentTransaction*   m_transaction;
};
