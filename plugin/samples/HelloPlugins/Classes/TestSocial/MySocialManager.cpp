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
#include "MySocialManager.h"
#include "PluginManager.h"
#include "cocos2d.h"
#include "Configs.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MySocialManager* MySocialManager::s_pManager = NULL;

MySocialManager::MySocialManager()
: _pNd91(NULL)
{

}

MySocialManager::~MySocialManager()
{
    unloadPlugins();
}

MySocialManager* MySocialManager::getInstance()
{
    if (s_pManager == NULL) {
        s_pManager = new MySocialManager();
    }
    return s_pManager;
}

void MySocialManager::purgeManager()
{
    if (s_pManager)
    {
        delete s_pManager;
        s_pManager = NULL;
    }
    PluginManager::end();
}

void MySocialManager::loadPlugins()
{
    {
        _pNd91 = dynamic_cast<ProtocolSocial*>(PluginManager::getInstance()->loadPlugin("SocialNd91"));
        if (NULL != _pNd91)
        {
            TSocialDeveloperInfo pNdInfo;
            pNdInfo["Nd91AppId"] = ND91_APPID;
            pNdInfo["Nd91AppKey"] = ND91_APPKEY;
            pNdInfo["Nd91Orientation"] = ND91_ORIENTATION;
            if (pNdInfo.empty()) {
                char msg[256] = { 0 };
                sprintf(msg, "Developer info is empty. PLZ fill your Nd91 info in %s(nearby line %d)", __FILE__, __LINE__);
                MessageBox(msg, "Nd91 Warning");
            }
            _pNd91->configDeveloperInfo(pNdInfo);
            _pNd91->setDebugMode(true);
            _pNd91->setListener(this);
        }
    }
}

void MySocialManager::submitScore(MySocialMode mode, const char* leaderboardID, long score)
{
    ProtocolSocial* pSocial = NULL;
    switch (mode)
    {
    case eNd91:
        pSocial = _pNd91;
        break;
    default:
        break;
    }

    if (NULL != pSocial)
    {
        pSocial->submitScore(leaderboardID, score);
    }
}

void MySocialManager::showLeaderboard(MySocialMode mode, const char* leaderboardID)
{
    ProtocolSocial* pSocial = NULL;
    switch (mode)
    {
    case eNd91:
        pSocial = _pNd91;
        break;
    default:
        break;
    }

    if (NULL != pSocial)
    {
        pSocial->showLeaderboard(leaderboardID);
    }
}

void MySocialManager::unlockAchievement(MySocialMode mode, TAchievementInfo info)
{
    ProtocolSocial* pSocial = NULL;
    switch (mode)
    {
    case eNd91:
        pSocial = _pNd91;
        break;
    default:
        break;
    }

    if (NULL != pSocial)
    {
        pSocial->unlockAchievement(info);
    }
}

void MySocialManager::showAchievement(MySocialMode mode)
{
    ProtocolSocial* pSocial = NULL;
    switch (mode)
    {
    case eNd91:
        pSocial = _pNd91;
        break;
    default:
        break;
    }

    if (NULL != pSocial)
    {
        pSocial->showAchievements();
    }
}

void MySocialManager::unloadPlugins()
{
    if (_pNd91)
    {
        PluginManager::getInstance()->unloadPlugin("SocialNd91");
        _pNd91 = NULL;
    }
}

void MySocialManager::onSocialResult(SocialRetCode code, const char* msg)
{
    char socialStatus[1024] = { 0 };
    sprintf(socialStatus, "Social code %d", code);
    MessageBox(msg, socialStatus);
}
