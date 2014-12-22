/** @file ProtocolSocial.h
 */
#ifndef  __CCX_PROTOCOL_SOCIAL_H__
#define  __CCX_PROTOCOL_SOCIAL_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {
/// \typedef std::map<std::string, std::string> TSocialDeveloperInfo
/// typedef TSocialDeveloperInfo.
typedef std::map<std::string, std::string> TSocialDeveloperInfo;
/// \typedef std::map<std::string, std::string> TAchievementInfo
/// typedef TAchievementInfo.
typedef std::map<std::string, std::string> TAchievementInfo;
/** @brief SocialRetCode enum, with inline docs */
typedef enum
{
    // code for leaderboard feature
	kScoreSubmitSucceed =1,/**< enum value is callback of succeeding in submiting. */
    kScoreSubmitfail,/**< enum value is callback of failing to submit . */

    // code for achievement feature
    kAchUnlockSucceed,/**< enum value is callback of succeeding in unlocking. */
    kAchUnlockFail,/**< enum value is callback of failing to  unlock. */

    kSocialSignInSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignInFail,/**< enum value is callback of failing to  login. */

    kSocialSignOutSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignOutFail,/**< enum value is callback of failing to  login. */


} SocialRetCode;
/**   
 *@class  SocialListener
 *@brief the interface of social callback  
 */
class SocialListener
{
public:
	/**   
	 *@brief the interface of social callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onSocialResult(SocialRetCode code, const char* msg) = 0;
};

/**   
 *@class  ProtocolSocial
 *@brief the interface of social  
 */
class ProtocolSocial : public PluginProtocol
{
public:

    /**
     @brief user signIn
     */
	virtual void signIn() = 0;

    /**
     @brief user signOut
     */
	virtual void signOut() = 0;

    /**
     @brief submit the score
     @param leaderboardID
     @param the score
     */
	virtual void submitScore(const char* leadboardID, long score) = 0;
     /**
      @brief show the id of Leaderboard page
      @param leaderboardID
      */
	virtual void showLeaderboard(const char* leaderboardID) = 0;

    /**
     @brief methods of achievement feature
     @param the info of achievement
     */
    virtual void unlockAchievement(TAchievementInfo achInfo) = 0;
    /**
     @brief show the page of achievements
     */
    virtual void showAchievements() = 0;
    /**
     @brief set pListener The callback object for user result
     @param the listener
     */
    virtual void setListener(SocialListener* listener)  = 0;
    /**
     @brief get pListener The callback object for social result
     @return the listener
     */
    virtual SocialListener* getListener() = 0;

};

}} // namespace anysdk { namespace framework {

#endif   /* ----- #ifndef __CCX_PROTOCOL_SOCIAL_H__ ----- */
