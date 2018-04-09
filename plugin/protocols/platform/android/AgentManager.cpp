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
 
#include <vector>

#include "AgentManager.h"
#include "PluginManager.h"
#include "ProtocolUser.h"
#include "ProtocolAnalytics.h"
#include "PluginUtils.h"

namespace cocos2d{ namespace plugin{

static AgentManager* s_AgentManager = nullptr;

AgentManager::AgentManager():pUser(nullptr), pShare(nullptr), pSocial(nullptr), pAds(nullptr), pAnalytics(nullptr), pIAP(nullptr)
{

}

AgentManager::~AgentManager()
{
	this->purge();
}

void AgentManager::purge()
{
	delete pUser;
	delete pShare;
	delete pSocial;
	delete pAds;
	delete pAnalytics;
	delete pIAP;
}

AgentManager* AgentManager::getInstance()
{
	if(nullptr == s_AgentManager)
	{
		s_AgentManager = new (std::nothrow) AgentManager();
		//s_AgentManager->init();
	}
	return s_AgentManager;
}

void AgentManager::destroyInstance()
{
	if(s_AgentManager)
	{
		delete s_AgentManager;
		s_AgentManager = nullptr;
	}
}

bool AgentManager::initWithConfigureFile()
{
	std::map<std::string, std::string> conf = getPluginConfigure();
	return init(conf);
}

bool AgentManager::init(std::map<std::string, std::string>& conf)
{
	if(conf.empty())
		return false;

	for(std::map<std::string, std::string>::iterator iter = conf.begin(); iter != conf.end(); ++iter)
	{
		std::string pluginName = iter->first;
		if("PluginUser" == pluginName)
		{
			pUser = dynamic_cast<ProtocolUser *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginShare" == pluginName)
		{
			pShare = dynamic_cast<ProtocolShare *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginSocial" == pluginName)
		{
			pSocial = dynamic_cast<ProtocolSocial *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginAds" == pluginName)
		{
			pAds = dynamic_cast<ProtocolAds *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginAnalytics" == pluginName)
		{
			pAnalytics = dynamic_cast<ProtocolAnalytics *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
		else if("PluginIAP" == pluginName)
		{
			pIAP = dynamic_cast<ProtocolIAP *>(PluginManager::getInstance()->loadPlugin(iter->second.c_str()));
		}
	}

	return true;
}

static std::vector<std::string> s_plugins = {"PluginUser", "PluginShare", "PluginSocial", "PluginAds", "PluginAnalytics", "PluginIAP"};

std::map<std::string, std::string> AgentManager::getPluginConfigure()
{
	std::map<std::string, std::string> configure;

	PluginJniMethodInfo t;
	JNIEnv* env = PluginUtils::getEnv();

	if(PluginJniHelper::getStaticMethodInfo(t, "org/cocos2dx/plugin/PluginWrapper", "getPluginConfigure", "()Ljava/util/Hashtable;"))
	{
		jobject jhashtable = t.env->CallStaticObjectMethod(t.classID, t.methodID);
		PluginJniMethodInfo tGetMethod;
		if(PluginJniHelper::getMethodInfo(tGetMethod, "java/util/Hashtable", "get", "(Ljava/lang/Object;)Ljava/lang/Object;"))
		{
			jstring jKey;
			jstring jValue;
			std::string stdValue;

			for(std::vector<std::string>::iterator iter = s_plugins.begin(); iter != s_plugins.end(); ++iter)
			{
				jKey = env->NewStringUTF((*iter).c_str());
				jValue = (jstring) (env->CallObjectMethod(jhashtable,tGetMethod.methodID,jKey));
				stdValue = PluginJniHelper::jstring2string(jValue);
				if(!stdValue.empty())
					configure.insert(std::make_pair(*iter, stdValue));
			}

			tGetMethod.env->DeleteLocalRef(jKey);
			tGetMethod.env->DeleteLocalRef(jValue);

		}
		env->DeleteLocalRef(jhashtable);
		env->DeleteLocalRef(tGetMethod.classID);
	}
	env->DeleteLocalRef(t.classID);
	return configure;
}

}}
