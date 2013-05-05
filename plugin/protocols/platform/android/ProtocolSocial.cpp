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
#include "ProtocolSocial.h"
#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginUtils.h"
#include "PluginJavaData.h"

#if 1
#define  LOG_TAG    "ProtocolSocial"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

extern "C" {
	JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_InterfaceSocial_nativeOnShareResult(JNIEnv*  env, jobject thiz, jobject obj, jint ret, jstring msg)
	{
		std::string strMsg = PluginJniHelper::jstring2string(msg);
		PluginProtocol* pPlugin = PluginUtils::getPluginPtr(obj);
		LOGD("nativeOnShareResult(), Get plugin ptr : %p", pPlugin);
		if (pPlugin != NULL)
		{
			LOGD("nativeOnShareResult(), Get plugin name : %s", pPlugin->getPluginName());
			ProtocolSocial* pSocial = dynamic_cast<ProtocolSocial*>(pPlugin);
			if (pSocial != NULL)
			{
				pSocial->onShareResult((ShareResultCode) ret, strMsg.c_str());
			}
		}
	}
}

ProtocolSocial::ProtocolSocial()
: m_pListener(NULL)
{
}

ProtocolSocial::~ProtocolSocial()
{
    PluginUtils::erasePluginJavaData(this);
}

bool ProtocolSocial::init()
{
    return true;
}

void ProtocolSocial::configDeveloperInfo(TSocialDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        LOGD("The developer info is empty!");
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
        	jobject obj_Map = PluginUtils::createJavaMapObject(t, &devInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolSocial::share(TShareInfo info)
{
    if (info.empty())
    {
        if (NULL != m_pListener)
        {
            onShareResult(kShareFail, "Share info error");
        }
        LOGD("The Share info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
		PluginJniMethodInfo t;
		if (PluginJniHelper::getMethodInfo(t
			, pData->jclassName.c_str()
			, "share"
			, "(Ljava/util/Hashtable;)V"))
		{
			// generate the hashtable from map
			jobject obj_Map = PluginUtils::createJavaMapObject(t, &info);

			// invoke java method
			t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
			t.env->DeleteLocalRef(obj_Map);
			t.env->DeleteLocalRef(t.classID);
		}
    }
}

void ProtocolSocial::setResultListener(ShareResultListener* pListener)
{
	m_pListener = pListener;
}

void ProtocolSocial::onShareResult(ShareResultCode ret, const char* msg)
{
    if (m_pListener)
    {
    	m_pListener->onShareResult(ret, msg);
    }
    else
    {
        LOGD("Result listener is null!");
    }
    LOGD("Share result is : %d(%s)", (int) ret, msg);
}

const char* ProtocolSocial::getSDKVersion()
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

void ProtocolSocial::setDebugMode(bool debug)
{
	PluginUtils::callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", debug);
}

}} // namespace cocos2d { namespace plugin {
