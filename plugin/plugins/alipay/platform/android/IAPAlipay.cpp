#include "IAPAlipay.h"
#include "PluginUtils.h"

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(IAPAlipay)

IAPAlipay::~IAPAlipay()
{
}

/**
@brief plugin initialization
*/
bool IAPAlipay::init()
{
	return PluginUtils::initJavaPlugin(this, "org.cocos2dx.plugin.IAPAlipay");
}

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
void IAPAlipay::initDeveloperInfo(TDeveloperInfo devInfo)
{
	ProtocolIAP::initDeveloperInfo(devInfo);
}

/**
@brief pay for product
@param info The info of product, must contains key:
		productName         The name of product
		productPrice        The price of product(must can be parse to float)
		productDesc         The description of product
@warning For different plugin, the parameter should have other keys to pay.
		 Look at the manual of plugins.
*/
void IAPAlipay::payForProduct(TProductInfo info)
{
	ProtocolIAP::payForProduct(info);
}

const char* IAPAlipay::getSDKVersion()
{
	return ProtocolIAP::getSDKVersion();
}

void IAPAlipay::setDebugMode(bool debug)
{
	ProtocolIAP::setDebugMode(debug);
}

}} // namespace cocos2d { namespace plugin {
