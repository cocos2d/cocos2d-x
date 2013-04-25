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

#if 1
#define  LOG_TAG    "ProtocolAds"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceAds_nativeReceiveAd(JNIEnv*  env, jobject thiz) {
		ProtocolAds::receiveAd();
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceAds_nativePresentScreen(JNIEnv*  env, jobject thiz) {
		ProtocolAds::presentScreen();
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceAds_nativeFailedToReceiveAd(JNIEnv*  env, jobject thiz, jint ret, jstring msg) {
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		ProtocolAds::failedToReceiveAd((AdListener::EAdErrorCode) ret, strMsg.c_str());
	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceAds_nativeDismissScreen(JNIEnv*  env, jobject thiz) {
		ProtocolAds::dismissScreen();
	}
}

AdListener* ProtocolAds::m_pListener = NULL;

ProtocolAds::ProtocolAds()
{
}

ProtocolAds::~ProtocolAds()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolAds::init()
{
    return true;
}

void ProtocolAds::initAppInfo(TAppInfo appInfo)
{
    if (appInfo.empty())
    {
        LOGD("The application info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    	PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "initAppInfo"
    		, "(Ljava/util/Hashtable;)V"))
    	{
        	// generate the hashtable from map
        	jobject obj_Map = PluginUtils::createJavaMapObject(t, &appInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolAds::showBannerAd(EBannerPos pos, int size)
{
	PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
	PluginJniMethodInfo t;

	LOGD("Class name : %s", pData->jclassName.c_str());
	if (PluginJniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, "showBannerAd"
		, "(II)V"))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, pos, size);
		t.env->DeleteLocalRef(t.classID);
	}
}

void ProtocolAds::hideBannerAd()
{
	PluginUtils::callJavaFunctionWithName(this, "hideBannerAd");
}

const char* ProtocolAds::getSDKVersion()
{
    std::string verName;

    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "getSDKVersion"
        , "()Ljava/lang/String;"))
    {
        jstring ret = (jstring)(t.env->CallObjectMethod(pData->jobj, t.methodID));
        verName = PluginJniHelper::jstring2string(ret);
    }
    return verName.c_str();
}

void ProtocolAds::setDebugMode(bool debug)
{
    PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", debug);
}

void ProtocolAds::receiveAd()
{
	LOGD("ProtocolAds::receiveAd invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onReceiveAd();
	}
}

void ProtocolAds::presentScreen()
{
	LOGD("ProtocolAds::presentScreen invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onPresentScreen();
	}
}

void ProtocolAds::failedToReceiveAd(AdListener::EAdErrorCode code, const char* msg)
{
	LOGD("ProtocolAds::failedToReceiveAd invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onFailedToReceiveAd(code, msg);
	}
}

void ProtocolAds::dismissScreen()
{
	LOGD("ProtocolAds::dismissScreen invoked!");
	if (m_pListener != NULL)
	{
		m_pListener->onDismissScreen();
	}
}

}} // namespace cocos2d { namespace plugin {
