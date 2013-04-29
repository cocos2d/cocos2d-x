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
#ifndef __CCX_IAP_ND91_H__
#define __CCX_IAP_ND91_H__

#include "ProtocolIAP.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

class IAPNd91 : public ProtocolIAP
{
	PLUGIN_REGISTER_DECL(IAPNd91)
public:
    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief config the developer info
    @param devInfo This parameter is the info of developer, must contains key:
    		Nd91AppId           The app id of nd91
    		Nd91AppKey          The app key of nd91
    		Nd91Orientation		The orientation of your app(use value : portrait, landscape, auto)
    							default value is portrait
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    virtual void configDeveloperInfo(TIAPDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
            Nd91ProductId       The product id of product for nd91
            Nd91ProductCount    The product number will buy(1--10000, default value 1)
            Nd91OriginalPrice   The original price of product(default value is same with productPrice)
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

    virtual ~IAPNd91();
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_IAP_ND91_H__ */
