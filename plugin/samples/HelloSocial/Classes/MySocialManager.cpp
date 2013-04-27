/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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

using namespace cocos2d::plugin;
using namespace cocos2d;

MySocialManager* MySocialManager::s_pManager = NULL;

MySocialManager::MySocialManager()
: s_pRetListener(NULL)
, s_pTwitter(NULL)
{

}

MySocialManager::~MySocialManager()
{
	unloadSocialPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
		s_pRetListener = NULL;
	}
}

MySocialManager* MySocialManager::sharedSocialManager()
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

void MySocialManager::loadSocialPlugin()
{
	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyShareResult();
	}

	{
		// init twitter plugin
		s_pTwitter = dynamic_cast<SocialTwitter*>(PluginManager::getInstance()->loadPlugin("SocialTwitter"));
		TSocialDeveloperInfo pTwitterInfo;

        /* Warning: must set your twiiter dev info here */
		// pTwitterInfo["TwitterKey"] = "your consumerkey";
        // pTwitterInfo["TwitterSecret"] = "your consumersecret";

		if (pTwitterInfo.empty())
		{
			char msg[256] = { 0 };
			sprintf(msg, "Developer info is empty. PLZ fill your twitter info in %s(nearby line %d)", __FILE__, __LINE__);
			CCMessageBox(msg, "Twitter Warning");
		}
		s_pTwitter->setDebugMode(true);
		s_pTwitter->configDeveloperInfo(pTwitterInfo);
		s_pTwitter->setResultListener(s_pRetListener);
	}
}

void MySocialManager::unloadSocialPlugin()
{
	if (s_pTwitter)
	{
		PluginManager::getInstance()->unloadPlugin("SocialTwitter");
		s_pTwitter = NULL;
	}
}

void MySocialManager::shareByMode(TShareInfo info, MyShareMode mode)
{
	ProtocolSocial* pShare = NULL;
	switch(mode)
	{
	case eTwitter:
		pShare = s_pTwitter;
		break;
	default:
		break;
	}

	if (pShare) {
		pShare->share(info);
	}
}

void MyShareResult::onShareResult(ShareResultCode ret, const char* msg)
{
    char shareStatus[1024] = { 0 };
    sprintf(shareStatus, "Share %s", (ret == kShareSuccess)? "Successed" : "Failed");
    CCMessageBox(msg, shareStatus);
}
