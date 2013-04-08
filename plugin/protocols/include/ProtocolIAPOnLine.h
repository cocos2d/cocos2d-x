#ifndef __CCX_PROTOCOL_IAP_ONLINE_H__
#define __CCX_PROTOCOL_IAP_ONLINE_H__

#include "ProtocolIAP.h"

namespace cocos2d { namespace plugin {

class LocalResultListener
{
public:
	virtual void payFailedLocally(EPayResult ret, const char* msg) = 0;
};

class ProtocolIAPOnLine : public PluginProtocol
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
            productPrice        The price of product
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
	@breif set the local result listener
	@param pListener The callback object for local result
	@wraning Must invoke this interface before payForProduct.
	*/
	static void setLocalResultListener(LocalResultListener* pListener);

	/**
	@brief pay failed locally callback
	*/
	static void payFailedLocally(EPayResult ret, const char* msg);

    virtual const char* getPluginVersion() { return "ProtocolIAPOnLine, v0.1.01 , subclass should override this interface!"; };
    virtual const char* getSDKVersion();
    virtual const char* getPluginName() = 0;

protected:
    ProtocolIAPOnLine();
public:
    virtual ~ProtocolIAPOnLine();

protected:
    static LocalResultListener* m_spListener;
};

}} // namespace cocos2d { namespace plugin {

#endif /* __CCX_PROTOCOL_IAP_ONLINE_H__ */
