/** @file AgentManager.h
 */


#ifndef __CCX_AGENTMANAGER_H__
#define __CCX_AGENTMANAGER_H__

#include "PluginManager.h"
#include "ProtocolIAP.h"
#include "ProtocolAnalytics.h"
#include "ProtocolShare.h"
#include "ProtocolAds.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "ProtocolPush.h"
#include <map>
#include <string>
namespace anysdk { namespace framework {

/**   
 *  @class  AgentManager  
 */
class AgentManager
{
public:
	virtual ~AgentManager();
    /**
     @brief Get singleton of AgentManager
     */

    static AgentManager* getInstance();
    /**
     @brief Destory the instance of AgentManager
     */
    static void end();
    
    /**
    @breif the init of AgentManager
    @param the appKey of plugin-x
    @param the appSecret of plugin-x
    @param the privateKey of plugin-x
    @param the url of oauthLoginServer
    @warning Must invoke this interface before loadALLPlugin
    */
    void init(std::string appKey,std::string appSecret,std::string privateKey,std::string oauthLoginServer);

    /**
     @brief load the plugins
     */
    void loadALLPlugin();
    /**
     @brief unload the plugins
     */
    void unloadALLPlugin();
    
    /**
     @brief Get Analytics plugin
     @return  if Analytics plugin exist ,return value is Analytics plugin.
     	 	  else return value is null pointer.
     */
    ProtocolAnalytics* getAnalyticsPlugin(){return _pAnalytics;};

    /**
     @brief Get User plugin
     @return  if User plugin exist ,return value is User plugin.
     	 	  else return value is null pointer.
     */
    ProtocolUser* getUserPlugin(){return _pUser;};

    /**
     @brief Get IAP plugin
     @return  if IAP plugin exist ,return value is IAP plugin.
     	 	  else return value is null pointer.
     */
    std::map<std::string , ProtocolIAP*>* getIAPPlugin(){return &_pluginsIAPMap;};

    /**
     @brief Get Share plugin
     @return  if Share plugin exist ,return value is Share plugin.
     	 	  else return value is null pointer.
     */
    ProtocolShare* getSharePlugin(){return _pShare;};

    /**
     @brief Get Social plugin
     @return  if Social plugin exist ,return value is Social plugin.
     	 	  else return value is null pointer.
     */
    ProtocolSocial* getSocialPlugin(){return _pSocial;};

    /**
     @brief Get Ads plugin
     @return  if Ads plugin exist ,return value is Ads plugin.
     	 	  else return value is null pointer.
     */
    ProtocolAds* getAdsPlugin(){return _pAds;};
    
    /**
     @brief Get Push plugin
     @return  if Push plugin exist ,return value is Push plugin.
     	 	  else return value is null pointer.
     */
    ProtocolPush* getPushPlugin(){return _pPush;};

    /**
     @brief Get channel ID
     @return  return value is channel ID.
     */
    std::string getChannelId();

    /**
     @brief Get custom param
     @return  return value is custom param for channel.
     */
    std::string getCustomParam();





protected:
    void setDebugMode(bool flag);
    std::string getFileData(const char* pFileName);
    void loadPlugin(const char* nodeName,int type);
    

private:
    AgentManager(void);
    
    // Analytics plugins
    ProtocolAnalytics* _pAnalytics;

    // user plugins
    ProtocolUser* _pUser;

    // IAP plugins
    //    ProtocolIAP* _pIAP;
    std::map<std::string , ProtocolIAP*> _pluginsIAPMap;

    // Share plugins
    ProtocolShare* _pShare;

    // Social plugins
    ProtocolSocial* _pSocial;

    // Ads plugins
    ProtocolAds* _pAds;
    
    // Push plugins
    ProtocolPush* _pPush;

};

}} //namespace anysdk { namespace framework {

#endif /* __CCX_AGENTMANAGER_H__ */
