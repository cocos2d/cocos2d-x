#ifndef __CCX_PROTOCOL_IAP_H__
#define __CCX_PROTOCOL_IAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TDeveloperInfo;
typedef std::map<std::string, std::string> TProductInfo;

typedef enum 
{
    ePaySuccess = 0,
    ePayFail,
    ePayCancel,
    ePayTimeOut,
} EPayResult;

class PayResultListener
{
public:
    virtual void payResult(EPayResult ret, const char* msg, TProductInfo info) = 0;
};

class ProtocolIAP : public PluginProtocol
{
public:

    /**
    @brief plugin initialization
    */
    virtual bool init();

    /**
    @brief initialize the developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
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

    /**
    @breif set the result listener
    @param pListener The callback object for pay result
    @wraning Must invoke this interface before payForProduct.
    */
    static void setResultListener(PayResultListener* pListener);

    /**
    @brief pay result callback
    */
    static void payResult(EPayResult ret, const char* msg);

    virtual const char* getPluginVersion() { return "ProtocolIAP, v0.1.01 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
    ProtocolIAP();
public:
    virtual ~ProtocolIAP();

protected:
    static bool m_bPaying;
    static PayResultListener* m_pListener;
    static TProductInfo m_curInfo;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_IAP_H__ */
