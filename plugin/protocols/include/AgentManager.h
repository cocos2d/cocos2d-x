/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __AGENTMANAGER_H__
#define __AGENTMANAGER_H__

#include <functional>
#include <string>
#include <map>

#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolUser.h"

namespace cocos2d{namespace plugin{

class ProtocolUser;
class ProtocolAnalytics;

class AgentManager{
public:
	virtual ~AgentManager();
	static AgentManager* getInstance();
	static void destroyInstance();
	virtual bool initWithConfigureFile();
	virtual bool init(std::map<std::string, std::string>& conf);
	virtual void purge();

	inline ProtocolUser* getUserPlugin()
	{
		return pUser;
	}

	inline ProtocolShare* getSharePlugin()
	{
		return pShare;
	}

	inline ProtocolSocial* getSocialPlugin()
	{
		return pSocial;
	}

	inline ProtocolAds* getAdsPlugin()
	{
		return pAds;
	}

	inline ProtocolAnalytics* getAnalyticsPlugin()
	{
		return pAnalytics;
	}

	inline ProtocolIAP* getIAPPlugin()
	{
		return pIAP;
	}

protected:
	AgentManager();
	std::map<std::string, std::string> getPluginConfigure();

	ProtocolUser *pUser;
	ProtocolShare *pShare;
	ProtocolSocial *pSocial;
	ProtocolAds *pAds;
	ProtocolAnalytics *pAnalytics;
	ProtocolIAP *pIAP;
};
}}
#endif
