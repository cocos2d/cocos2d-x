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
#include "PluginFactory.h"
#include "PluginUtils.h"
#include "PluginJniHelper.h"
#include "ProtocolAds.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolShare.h"
#include "ProtocolUser.h"
#include "ProtocolSocial.h"

namespace cocos2d { namespace plugin {

enum {
	kPluginAds = 1,
	kPluginAnalytics,
	kPluginIAP,
	kPluginShare,
	kPluginUser,
	kPluginSocial,
};

#define ANDROID_PLUGIN_PACKAGE_PREFIX			"org/cocos2dx/plugin/"

static PluginFactory* s_pFactory = NULL;

PluginFactory::PluginFactory()
{

}

PluginFactory::~PluginFactory()
{

}

PluginFactory* PluginFactory::getInstance()
{
	if (NULL == s_pFactory)
	{
		s_pFactory = new PluginFactory();
	}

	return s_pFactory;
}

void PluginFactory::purgeFactory()
{
	if (NULL != s_pFactory)
	{
		delete s_pFactory;
		s_pFactory = NULL;
	}
}

/** create the plugin by name */
PluginProtocol* PluginFactory::createPlugin(const char* name)
{
	PluginProtocol* pRet = NULL;
	do
	{
		if (name == NULL || strlen(name) == 0) break;

		std::string jClassName = ANDROID_PLUGIN_PACKAGE_PREFIX;
		jClassName.append(name);
		PluginUtils::outputLog("PluginFactory", "Java class name of plugin %s is : %s", name, jClassName.c_str());

		PluginJniMethodInfo t;
		if (! PluginJniHelper::getStaticMethodInfo(t
			, "org/cocos2dx/plugin/PluginWrapper"
			, "initPlugin"
			, "(Ljava/lang/String;)Ljava/lang/Object;"))
		{
			PluginUtils::outputLog("PluginFactory", "Can't find method initPlugin in class org.cocos2dx.plugin.PluginWrapper");
			break;
		}

		jstring clsName = t.env->NewStringUTF(jClassName.c_str());
		jobject jObj = t.env->CallStaticObjectMethod(t.classID, t.methodID, clsName);
		t.env->DeleteLocalRef(clsName);
		t.env->DeleteLocalRef(t.classID);
		if (jObj == NULL)
		{
			PluginUtils::outputLog("PluginFactory", "Can't find java class %s", jClassName.c_str());
			break;
		}

		if (! PluginJniHelper::getStaticMethodInfo(t
			, "org/cocos2dx/plugin/PluginWrapper"
			, "getPluginType"
			, "(Ljava/lang/Object;)I"))
		{
			PluginUtils::outputLog("PluginFactory", "Can't find method getPluginType in class org.cocos2dx.plugin.PluginWrapper");
			break;
		}
		int curType = t.env->CallStaticIntMethod(t.classID, t.methodID, jObj);
		t.env->DeleteLocalRef(t.classID);
		PluginUtils::outputLog("PluginFactory", "The type of plugin %s is : %d", name, curType);

		switch (curType)
		{
		case kPluginAds:
			pRet = new ProtocolAds();
			break;
		case kPluginAnalytics:
			pRet = new ProtocolAnalytics();
			break;
		case kPluginIAP:
			pRet = new ProtocolIAP();
			break;
		case kPluginShare:
			pRet = new ProtocolShare();
			break;
		case kPluginUser:
		    pRet = new ProtocolUser();
		    break;
		case kPluginSocial:
		    pRet = new ProtocolSocial();
		    break;
		default:
			break;
		}

		if (pRet != NULL)
		{
			pRet->setPluginName(name);
			PluginUtils::initJavaPlugin(pRet, jObj, jClassName.c_str());
		}
	} while(0);

	return pRet;
}

}} //namespace cocos2d { namespace plugin {
