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
#include "MyShareManager.h"
#include "PluginManager.h"
#include "cocos2d.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyShareManager* MyShareManager::s_pManager = NULL;

MyShareManager::MyShareManager()
: s_pRetListener(NULL)
, s_pTwitter(NULL)
, s_pWeibo(NULL)
{

}

MyShareManager::~MyShareManager()
{
	unloadSharePlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
		s_pRetListener = NULL;
	}
}

MyShareManager* MyShareManager::getInstance()
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
		s_pManager = NULL;
	}
	PluginManager::end();
}

void MyShareManager::loadSharePlugin()
{
	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyShareResult();
	}

	{
		// init twitter plugin
		s_pTwitter = dynamic_cast<ProtocolShare*>(PluginManager::getInstance()->loadPlugin("ShareTwitter"));
		if (NULL != s_pTwitter)
		{
			TShareDeveloperInfo pTwitterInfo;

			/* Warning: must set your twiiter dev info here */
			// pTwitterInfo["TwitterKey"] = "your consumerkey";
			// pTwitterInfo["TwitterSecret"] = "your consumersecret";

			if (pTwitterInfo.empty())
			{
				char msg[256] = { 0 };
				sprintf(msg, "Developer info is empty. PLZ fill your twitter info in %s(nearby line %d)", __FILE__, __LINE__);
				MessageBox(msg, "Twitter Warning");
			}
			s_pTwitter->setDebugMode(true);
			s_pTwitter->configDeveloperInfo(pTwitterInfo);
			s_pTwitter->setResultListener(s_pRetListener);
		}
	}

	{
		s_pWeibo = dynamic_cast<ProtocolShare*>(PluginManager::getInstance()->loadPlugin("ShareWeibo"));
		if (NULL != s_pWeibo)
		{
			TShareDeveloperInfo pWeiboInfo;
			// pWeiboInfo["WeiboAppKey"] = "your app key";
            // pWeiboInfo["WeiboAppSecret"] = "your app secret";
			// pWeiboInfo["WeiboRedirectUrl"] = "your redirect url";

			if (pWeiboInfo.empty())
			{
				char msg[256] = { 0 };
				sprintf(msg, "Developer info is empty. PLZ fill your weibo info in %s(nearby line %d)", __FILE__, __LINE__);
				MessageBox(msg, "Weibo Warning");
			}

			s_pWeibo->setDebugMode(true);
			s_pWeibo->configDeveloperInfo(pWeiboInfo);
			s_pWeibo->setResultListener(s_pRetListener);
		}
	}
}

void MyShareManager::unloadSharePlugin()
{
	if (s_pTwitter)
	{
		PluginManager::getInstance()->unloadPlugin("ShareTwitter");
		s_pTwitter = NULL;
	}

	if (s_pWeibo)
	{
		PluginManager::getInstance()->unloadPlugin("ShareWeibo");
		s_pWeibo = NULL;
	}
}

void MyShareManager::shareByMode(TShareInfo info, MyShareMode mode)
{
	ProtocolShare* pShare = NULL;
	switch(mode)
	{
	case eTwitter:
		pShare = s_pTwitter;
		break;
	case eWeibo:
		pShare = s_pWeibo;
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
    MessageBox(msg, shareStatus);
}
