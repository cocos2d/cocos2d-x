/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
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
@brief config the developer info
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
void IAPAlipay::configDeveloperInfo(TIAPDeveloperInfo devInfo)
{
	ProtocolIAP::configDeveloperInfo(devInfo);
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
