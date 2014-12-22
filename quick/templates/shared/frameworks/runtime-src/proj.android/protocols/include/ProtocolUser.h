/** @file ProtocolUser.h
 */
#ifndef __CCX_PROTOCOL_USER_H__
#define __CCX_PROTOCOL_USER_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TUserDeveloperInfo
/// typedef TUserDeveloperInfo.
typedef std::map<std::string, std::string> TUserDeveloperInfo;
/** @brief Plugin_type enum, with inline docs */
typedef enum
{
	kInitSuccess = 0,/**< enum value is callback of succeeding in initing sdk. */
	kInitFail,/**< enum  value is callback of failing to init sdk. */
    kLoginSuccess,/**< enum value is callback of succeeding in login.*/
    kLoginNetworkError,/**< enum value is callback of network error*/
    kLoginNoNeed,/**< enum value is callback of no need login.*/
    kLoginFail,/**< enum value is callback of failing to login. */
    kLoginCancel,/**< enum value is callback of canceling to login. */
    kLogoutSuccess,/**< enum value is callback of succeeding in logout. */
    kLogoutFail,/**< enum value is callback of failing to logout. */
    kPlatformEnter,/**< enum value is callback after enter platform. */
    kPlatformBack,/**< enum value is callback after exit antiAddiction. */
    kPausePage,/**< enum value is callback after exit pause page. */
    kExitPage,/**< enum value is callback after exit exit page. */
    kAntiAddictionQuery,/**< enum value is callback after querying antiAddiction. */
    kRealNameRegister,/**< enum value is callback after registering realname. */
    kAccountSwitchSuccess,/**< enum alue is callback of succeeding in switching account. */
    kAccountSwitchFail,/**< enum value is callback of failing to switch account. */
    kOpenShop,/**< enum value is callback of open the shop. */


} UserActionResultCode;
/** @brief ToolBarPlace enum, with inline docs */
typedef enum
{
    kToolBarTopLeft = 1,/**< enum the toolbar is at topleft. */
    kToolBarTopRight,/**< enum the toolbar is at topright. */
    kToolBarMidLeft,/**< enum the toolbar is at midleft. */
    kToolBarMidRight,/**< enum the toolbar is at midright. */
    kToolBarBottomLeft,/**< enum the toolbar is at bottomleft. */
    kToolBarBottomRight,/**< enum the toolbar is at bottomright. */
} ToolBarPlace;

class ProtocolUser;
/**   
 *@class  UserActionListener
 *@brief the interface of user callback  
 */
class UserActionListener
{
public:
	/**   
	 *@brief the interface of user callback 
	 *@param the adatper of plugin
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) = 0;
};
/**   
 *  @class  ProtocolUser  
 */
class ProtocolUser : public PluginProtocol
{
public:


    /**
     @brief User login
     */
    virtual  void login() = 0 ;

    /**
     @brief User login
     	 	if the process of logining need to know  the param of server_id ,
     	 	you can use the function
     	 	and if you must change oauthloginserver, you can add the param of oauthLoginServer
     @param server_id
     @param oauthLoginServer
    */
     virtual  void login(std::string server_id, std::string oauthLoginServer = "") = 0 ;


    /**
     @brief Check whether the user logined or not
     @return If user logined, return value is true;
             else return value is false.
     */
    virtual bool isLogined() = 0 ;

    /**
     @brief Get session ID
     @return If user logined, return value is userID;
             else return value is empty string.
     */
    virtual std::string getUserID() = 0 ;
    /**
     @brief set the result listener
     @param pListener The callback object for user result
     */
    virtual void setActionListener(UserActionListener* listener) = 0 ;
    /**
     @brief get pListener The callback object for user result
     @return the listener
     */
    virtual  UserActionListener* getActionListener() = 0 ;

    /**
     @brief Check function the plugin support or not
     @param the name of plugin
     @return if the function support ,return true
     	 	 else retur false
     */
    virtual bool isFunctionSupported(std::string functionName) = 0 ;
    /**
     @brief get plugin id
     @return the plugin id
     */
	virtual std::string getPluginId() = 0 ;



};

}} // namespace anysdk { namespace framework {

#endif /* __CCX_PROTOCOL_USER_H__ */
