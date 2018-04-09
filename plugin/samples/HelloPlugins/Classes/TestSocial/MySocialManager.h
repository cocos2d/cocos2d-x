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
#ifndef __MY_SOCIAL_MANAGER_H__
#define __MY_SOCIAL_MANAGER_H__

#include "ProtocolSocial.h"

class MySocialManager : public cocos2d::plugin::SocialListener
{
public:
    static MySocialManager* getInstance();
    static void purgeManager();

    typedef enum {
        eNoneMode = 0,
        eNd91,
    } MySocialMode;

    void unloadPlugins();
    void loadPlugins();

    void submitScore(MySocialMode mode, const char* leaderboardID, long score);
    void showLeaderboard(MySocialMode mode, const char* leaderboardID);
    void unlockAchievement(MySocialMode mode, cocos2d::plugin::TAchievementInfo info);
    void showAchievement(MySocialMode mode);

    virtual void onSocialResult(cocos2d::plugin::SocialRetCode code, const char* msg);

private:
    MySocialManager();
    virtual ~MySocialManager();

    static MySocialManager* s_pManager;

    cocos2d::plugin::ProtocolSocial* _pNd91;
};

#endif // __MY_SOCIAL_MANAGER_H__
