/** @file ProtocolIAP.h
 */
#ifndef __CCX_PROTOCOL_IAP_H__
#define __CCX_PROTOCOL_IAP_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TIAPDeveloperInfo
/// typedef TIAPDeveloperInfo.
typedef std::map<std::string, std::string> TIAPDeveloperInfo;
/// \typedef std::map<std::string, std::string> TProductInfo
/// typedef TProductInfo.
typedef std::map<std::string, std::string> TProductInfo;
/// typedef TProductsInfo.
typedef std::map<std::string, TProductInfo> AllProductsInfo;
/** @brief PayResultCode enum, with inline docs */
typedef enum 
{
    kPaySuccess = 0,/**< enum value is callback of succeeding in paying . */
    kPayFail,/**< enum value is callback of failing to pay . */
    kPayCancel,/**< enum value is callback of canceling to pay . */
    kPayNetworkError,/**< enum value is callback of network error . */
    kPayProductionInforIncomplete,/**< enum value is callback of incompleting info . */
	kPayInitSuccess,/**< enum value is callback of succeeding in initing sdk . */
	kPayInitFail,/**< enum value is callback of failing to init sdk . */
	kPayNowPaying,/**< enum value is callback of paying now . */
	kPayRechareSuccess,/**< enum value is callback of  succeeding in recharging. */
} PayResultCode;
/** @brief RequestResultCode enum, with inline docs */
typedef enum
{
    kRequestSuccess = 31000,/**< enum value is callback of succeeding in paying . */
    kRequestFail/**< enum value is callback of failing to pay . */
} RequestResultCode;
/**   
 *@class  PayResultListener
 *@brief the interface of pay callback  
 */
class PayResultListener
{
public:
	/**   
	 *@brief the interface of pay callback 
	 *@param the id of callback
	 *@param the information of callback
	 *@param the info of pay
     */
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info) = 0;
    /**
     *@brief the interface of request callback
     *@param the id of callback
     *@param the information of callback
     *@param the info of request product
     */
    virtual void onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info)  {}
};
/**   
 *@class  ProtocolIAP
 *@brief the interface of pay   
 */

class ProtocolIAP : public PluginProtocol
{
public:

    /**
    @brief pay for product
    @param info The info of product, must contains key:
            productName         The name of product
            productPrice        The price of product(must can be parse to float)
            productDesc         The description of product
    @warning For different plugin, the parameter should have other keys to pay.
             Look at the manual of plugins.
    */
    virtual void payForProduct(TProductInfo info) = 0;
    /**
     @brief get order id
     @return the order id
     */
    virtual std::string getOrderId() = 0;

    /**
    @breif set the result listener
    @param pListener The callback object for pay result
    @wraning Must invoke this interface before payForProduct.
    */
    virtual void setResultListener(PayResultListener* pListener) = 0;

    /**
     @brief get plugin id
     @return the plugin id
     */
	virtual std::string getPluginId() = 0 ;

	/**
     @brief change the state of paying
     @param the state
	*/

	static void resetPayState()
	{
		_paying = false;
	}
    static bool _paying;


};


}} // namespace anysdk { namespace framework {

#endif /* __CCX_PROTOCOL_IAP_H__ */
