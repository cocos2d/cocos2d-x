/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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
#ifndef  __CCX_PROTOCOL_SOCIAL_H__
#define  __CCX_PROTOCOL_SOCIAL_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace cocos2d { namespace plugin {

typedef std::map<std::string, std::string> TSocialDeveloperInfo;
typedef std::map<std::string, std::string> TAchievementInfo;

typedef enum
{
    // code for leaderboard feature
    SCORE_SUBMIT_SUCCESS = 1,
    SCORE_SUBMIT_FAILED,

    // code for achievement feature
    ACH_UNLOCK_SUCCESS,
    ACH_UNLOCK_FAILED,

} SocialRetCode;

class SocialListener
{
public:
    virtual void onSocialResult(SocialRetCode code, const char* msg) = 0;
};

class ProtocolSocial : public PluginProtocol
{
public:
    ProtocolSocial();
    virtual ~ProtocolSocial();

    /**
    @brief config the share developer info
    @param devInfo This parameter is the info of developer,
           different plugin have different format
    @warning Must invoke this interface before other interfaces.
             And invoked only once.
    */
    void configDeveloperInfo(TSocialDeveloperInfo devInfo);

    /**
     * @brief methods of leaderboard feature
     */
    void submitScore(const char* leadboardID, long score);
    void showLeaderboard(const char* leaderboardID);

    /**
     * @brief methods of achievement feature
     */
    void unlockAchievement(TAchievementInfo achInfo);
    void showAchievements();

    inline void setListener(SocialListener* listener) {
        _listener = listener;
    }

    inline SocialListener* getListener()
    {
        return _listener;
    }

protected:
    SocialListener* _listener;
};

}} // namespace cocos2d { namespace plugin {

#endif   /* ----- #ifndef __CCX_PROTOCOL_SOCIAL_H__ ----- */
