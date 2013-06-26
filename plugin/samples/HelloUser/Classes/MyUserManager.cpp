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
#include "MyUserManager.h"
#include "PluginManager.h"
#include "cocos2d.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyUserManager* MyUserManager::s_pManager = NULL;

MyUserManager::MyUserManager()
: _retListener(NULL)
, _qh360(NULL)
{

}

MyUserManager::~MyUserManager()
{
	unloadPlugin();
	if (_retListener)
	{
		delete _retListener;
		_retListener = NULL;
	}
}

MyUserManager* MyUserManager::sharedManager()
{
	if (s_pManager == NULL) {
		s_pManager = new MyUserManager();
	}
	return s_pManager;
}

void MyUserManager::purgeManager()
{
	if (s_pManager)
	{
		delete s_pManager;
		s_pManager = NULL;
	}
	PluginManager::end();
}

void MyUserManager::loadPlugin()
{
	if (_retListener == NULL)
	{
		_retListener = new MyUserActionResult();
	}

	{
		// init qh360 plugin
		_qh360 = dynamic_cast<ProtocolUser*>(PluginManager::getInstance()->loadPlugin("UserQH360"));
		if (NULL != _qh360)
		{
		    _qh360->setDebugMode(true);
			_qh360->setActionListener(_retListener);
		}
	}
}

void MyUserManager::unloadPlugin()
{
	if (_qh360)
	{
		PluginManager::getInstance()->unloadPlugin("UserQH360");
		_qh360 = NULL;
	}
}

void MyUserManager::loginByMode(MyUserMode mode)
{
	ProtocolUser* pUser = NULL;
	switch(mode)
	{
	case kQH360:
		pUser = _qh360;
		break;
	default:
		break;
	}

	if (pUser) {
	    pUser->login();
	}
}

void MyUserManager::logoutByMode(MyUserMode mode)
{
    ProtocolUser* pUser = NULL;
    switch(mode)
    {
    case kQH360:
        pUser = _qh360;
        break;
    default:
        break;
    }

    if (pUser) {
        pUser->logout();
    }
}

void MyUserActionResult::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
    char userStatus[1024] = { 0 };
    switch (code)
    {
    case kLoginSucceed:
    case kLoginFailed:
        sprintf(userStatus, "User of \"%s\" login %s", pPlugin->getPluginName(), (code == kLoginSucceed)? "Successed" : "Failed");
        break;
    case kLogoutSucceed:
        sprintf(userStatus, "User of \"%s\" logout", pPlugin->getPluginName());
        break;
    default:
        break;
    }
    MessageBox(msg, userStatus);

    // get session ID
    std::string sessionID = pPlugin->getSessionID();
    CCLog("User Session ID of plugin %s is : %s", pPlugin->getPluginName(), sessionID.c_str());
}
