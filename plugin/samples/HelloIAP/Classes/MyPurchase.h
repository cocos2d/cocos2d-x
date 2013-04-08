#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "IAPAlipay.h"
#include "IAPNd91.h"

class MyPurchaseResult : public cocos2d::plugin::PayResultListener
{
public:
	virtual void payResult(cocos2d::plugin::EPayResult ret, const char* msg, cocos2d::plugin::TProductInfo info);
};

class MyPurchase
{
public:
	static MyPurchase* sharedPurchase();
    static void purgePurchase();

    typedef enum {
    	eNoneMode = 0,
    	eAlipay,
    	eND91,
    } MyPayMode;

	void unloadIAPPlugin();
    void loadIAPPlugin();
    void payByMode(cocos2d::plugin::TProductInfo info, MyPayMode mode);

private:
    MyPurchase();
    virtual ~MyPurchase();

    static MyPurchase* s_pPurchase;

    cocos2d::plugin::IAPAlipay* s_pAlipay;
    cocos2d::plugin::IAPNd91* s_pNd91;
    MyPurchaseResult* s_pRetListener;
};

#endif // __MY_PURCHASE_H__
