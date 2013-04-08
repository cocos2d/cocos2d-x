#ifndef __CCX_IAP_ALIPAY_H__
#define __CCX_IAP_ALIPAY_H__

#include "ProtocolIAP.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class IAPAlipay : public ProtocolIAP
{
	PLUGIN_REGISTER_DECL(IAPAlipay)
public:
    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief initialize the developer info
    @param devInfo This parameter is the info of developer, must contains key:
    		AlipayPartner		The partner id of alipay account
			AlipaySeller		The seller id of alipay account
			AlipayRsaPrivate	The RSA private key of alipay account
			AlipayPublic		The public key of alipay account
			AlipayNotifyUrl		The notify url of developer (must not be empty)
			AlipayPluginName	The apk file name of Alipay (must not be empty)
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void initDeveloperInfo(TDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    virtual void payForProduct(TProductInfo info);

    /**
	 @brief Set whether needs to output logs to console.
	 @param debug if true debug mode enabled, or debug mode disabled.
	 */
	virtual void setDebugMode(bool debug);

    virtual const char* getPluginVersion() { return "v0.1.01"; };
    virtual const char* getSDKVersion();

    virtual ~IAPAlipay();
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_IAP_ALIPAY_H__ */
