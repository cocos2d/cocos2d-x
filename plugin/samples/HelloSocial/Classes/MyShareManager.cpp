#include "MyShareManager.h"
#include "PluginManager.h"
#include "cocos2d.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyShareManager* MyShareManager::s_pManager = NULL;

MyShareManager::MyShareManager()
: s_pRetListener(NULL)
, s_pTwitter(NULL)
{

}

MyShareManager::~MyShareManager()
{
	unloadSocialPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
	}
}

MyShareManager* MyShareManager::sharedManager()
{
	if (s_pManager == NULL) {
		s_pManager = new MyShareManager();
	}
	return s_pManager;
}

void MyShareManager::purgeManager()
{
	if (s_pManager)
	{
		delete s_pManager;
	}
}

void MyShareManager::loadSocialPlugin()
{
	{
		// init twitter plugin
		s_pTwitter = dynamic_cast<SocialTwitter*>(PluginManager::getInstance()->loadPlugin("SocialTwitter"));
		TSocialDevInfo pTwitterInfo;

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
		s_pTwitter->initDeveloperInfo(pTwitterInfo);
	}

	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyShareResult();
		ProtocolSocial::setResultListener(s_pRetListener);
	}
}

void MyShareManager::unloadSocialPlugin()
{
	if (s_pTwitter)
	{
		PluginManager::getInstance()->unloadPlugin("SocialTwitter");
		s_pTwitter = NULL;
	}
}

void MyShareManager::shareByMode(TShareInfo info, MyShareMode mode)
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

void MyShareResult::shareResult(EShareResult ret, const char* msg)
{
    char shareStatus[1024] = { 0 };
    sprintf(shareStatus, "Share %s", (ret == eShareSuccess)? "Successed" : "Failed");
    CCMessageBox(msg, shareStatus);
}
