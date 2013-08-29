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
#include "ProtocolAds.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_AdsWrapper_nativeOnAdsResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg) {
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		std::string strClassName = PluginJniHelper::jstring2string(className);
		PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
		PluginUtils::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin ptr : %p", pPlugin);
		if (pPlugin != NULL)
		{
			PluginUtils::outputLog("ProtocolAds", "nativeOnAdsResult(), Get plugin name : %s", pPlugin->getPluginName());
			ProtocolAds* pAds = dynamic_cast<ProtocolAds*>(pPlugin);
			if (pAds != NULL)
			{
				pAds->onAdsResult((AdsResultCode) ret, strMsg.c_str());
			}
		}
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_AdsWrapper_nativeOnPlayerGetPoints(JNIEnv*  env, jobject thiz, jstring className, jint points) {
		std::string strClassName = PluginJniHelper::jstring2string(className);
		PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
		PluginUtils::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin ptr : %p", pPlugin);
		if (pPlugin != NULL)
		{
			PluginUtils::outputLog("ProtocolAds", "nativeOnPlayerGetPoints(), Get plugin name : %s", pPlugin->getPluginName());
			ProtocolAds* pAds = dynamic_cast<ProtocolAds*>(pPlugin);
			if (pAds != NULL)
			{
				pAds->onPlayerGetPoints(points);
			}
		}
	}
}

ProtocolAds::ProtocolAds()
: m_pListener(NULL)
{
}

ProtocolAds::~ProtocolAds()
{
}

void ProtocolAds::configDeveloperInfo(TAdsDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolAds", "The application info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "configDeveloperInfo"
    		, "(Ljava/util/Hashtable;)V"))
    	{
        	// generate the hashtable from map
        	jobject obj_Map = PluginUtils::createJavaMapObject(&devInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolAds::showAds(AdsType type, int sizeEnum, AdsPos pos)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;

	PluginUtils::outputLog("ProtocolAds", "Class name : %s", pData->jclassName.c_str());
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "showAds"
		, "(III)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, type, sizeEnum, pos);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolAds::hideAds(AdsType type)
{
	PluginUtils::callJavaFunctionWithName_oneParam(this, "hideAds", "(I)V", type);
}

void ProtocolAds::spendPoints(int points)
{
	PluginUtils::callJavaFunctionWithName_oneParam(this, "spendPoints", "(I)V", points);
}

void ProtocolAds::setAdsListener(AdsListener* pListener)
{
	m_pListener = pListener;
}

void ProtocolAds::onAdsResult(AdsResultCode code, const char* msg)
{
	PluginUtils::outputLog("ProtocolAds", "ProtocolAds::adsResult invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onAdsResult(code, msg);
	}
}

void ProtocolAds::onPlayerGetPoints(int points)
{
	PluginUtils::outputLog("ProtocolAds", "ProtocolAds::onPlayerGetPoints invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onPlayerGetPoints(this, points);
	}
}

}} // namespace cocos2d { namespace plugin {
