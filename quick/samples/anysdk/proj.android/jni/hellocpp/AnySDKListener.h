#ifndef _ANYSDK_LISTENER_H_
#define _ANYSDK_LISTENER_H_

#include "AgentManager.h"
#include "ProtocolAds.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolPush.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"

namespace anysdk { namespace framework {

class AdsListenerLua : public AdsListener
{
public:
	AdsListenerLua();
	~AdsListenerLua();

	/**
     *@brief The advertisement request result
     *@param the id of callback
	 *@param the information of callback
     */
    virtual void onAdsResult(AdsResultCode code, const char* msg);
    
    /**
    @brief Player get points from advertisement(For example: Tapjoy)
    @param points The point number player has got.
    @param pAdsPlugin  The plugin which the player get points. Used to spend the points.
    */
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points);

    int m_luaFunction;
};

class PayResultListenerLua : public PayResultListener
{
public:
	PayResultListenerLua();
	~PayResultListenerLua();

	/**   
	 *@brief the interface of pay callback 
	 *@param the id of callback
	 *@param the information of callback
	 *@param the info of pay
	 */
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info);

    int m_luaFunction;

};

class PushActionListenerLua : public PushActionListener
{
public:
	PushActionListenerLua();
	~PushActionListenerLua();

	/**   
	 *@brief the interface of Push callback 
	 *@param the adatper of plugin
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg);

    int m_luaFunction;
};

class ShareResultListenerLua : public ShareResultListener
{
public:
	ShareResultListenerLua();
	~ShareResultListenerLua();
	
	/**   
	 *@brief the interface of share callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onShareResult(ShareResultCode ret, const char* msg);

    int m_luaFunction;
};

class SocialListenerLua : public SocialListener
{
public:
	SocialListenerLua();
	~SocialListenerLua();
	
	/**   
	 *@brief the interface of social callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onSocialResult(SocialRetCode code, const char* msg);

    int m_luaFunction;
};

class UserActionListenerLua : public UserActionListener
{
public:
	UserActionListenerLua();
	~UserActionListenerLua();
	
	/**   
	 *@brief the interface of user callback 
	 *@param the adatper of plugin
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);

    int m_luaFunction;
};

class AnySDKListener
{
public:
    virtual ~AnySDKListener();

    /**
     @brief Get singleton of AnySDKListener
     */
    static AnySDKListener* getInstance();

    /*
     @brief reglua listener, typedef (*luaFunction)(const char* protocalName, const char* jsonStr)  
    */
    void callLuaFunction(int luaFunction, const char* protocolName, const char* jsonStr);

    void setAdListener(int luaFunction, ProtocolAds* ads = NULL);
    void setIAPListener(int luaFunction, ProtocolIAP* iap = NULL);
    void setPushListener(int luaFunction, ProtocolPush* push = NULL);
    void setShareListener(int luaFunction, ProtocolShare* share = NULL);
    void setSocialListener(int luaFunction, ProtocolSocial* social = NULL);
    void setUserListener(int luaFunction, ProtocolUser* user = NULL);

private:
	AnySDKListener();

	void releaseLuaFunction(int luaFunction);

	AdsListenerLua* m_listenerAds;
	PayResultListenerLua* m_listenerIAP;
	PushActionListenerLua* m_listenerPush;
	ShareResultListenerLua* m_listenerShare;
	SocialListenerLua* m_listenerSocial;
	UserActionListenerLua* m_listenerUser;

	static AnySDKListener* gInstance;
};

}}

#endif //_ANYSDK_WRAPPER_H_
