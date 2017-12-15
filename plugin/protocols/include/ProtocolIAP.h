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
#ifndef __CCX_PROTOCOL_IAP_H__
#define __CCX_PROTOCOL_IAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TIAPDeveloperInfo;
typedef std::map<std::string, std::string> TProductInfo;
typedef std::vector<TProductInfo> TProductList;
typedef enum 
{
    kPaySuccess = 0,
    kPayFail,
    kPayCancel,
    kPayTimeOut,
} PayResultCode;
    
typedef enum {
    RequestSuccees=0,
    RequestFail,
    RequestTimeout,
} IAPProductRequest;

class PayResultListener
{
public:
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info) = 0;
    virtual void onRequestProductsResult(IAPProductRequest ret, TProductList info){}
};

class ProtocolIAP : public PluginProtocol
{
public:
	ProtocolIAP();
	virtual ~ProtocolIAP();

	typedef std::function<void(int, std::string&)> ProtocolIAPCallback;

    /**
    @brief config the developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TIAPDeveloperInfo devInfo);

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    void payForProduct(TProductInfo info);
    void payForProduct(TProductInfo info, ProtocolIAPCallback cb);

    /**
    @deprecated
    @breif set the result listener
    @param pListener The callback object for pay result
    @wraning Must invoke this interface before payForProduct.
    */
    CC_DEPRECATED_ATTRIBUTE void setResultListener(PayResultListener* pListener);
    
    /**
    @deprecated
    @breif get the result listener
    */
    CC_DEPRECATED_ATTRIBUTE inline PayResultListener* getResultListener()
    {
        return _listener;
    }
    
    /**
    @brief pay result callback
    */
    void onPayResult(PayResultCode ret, const char* msg);

    /**
    @brief set callback function
    */
    inline void setCallback(ProtocolIAPCallback &cb)
    {
    	_callback = cb;
    }

    /**
    @brief get callback function
    */
    inline ProtocolIAPCallback getCallback()
    {
    	return _callback;
    }
protected:
    static bool _paying;

    TProductInfo _curInfo;
    PayResultListener* _listener;
    ProtocolIAPCallback _callback;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_IAP_H__ */
