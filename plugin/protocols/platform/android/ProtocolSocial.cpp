/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

namespace cocos2d { namespace plugin {

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_SocialWrapper_nativeOnSocialResult(JNIEnv*  env, jobject thiz, jstring className, jint ret, jstring msg)
    {
        std::string strMsg = PluginJniHelper::jstring2string(msg);
        std::string strClassName = PluginJniHelper::jstring2string(className);
        PluginProtocol* pPlugin = PluginUtils::getPluginPtr(strClassName);
        PluginUtils::outputLog("ProtocolSocial", "nativeOnSocialResult(), Get plugin ptr : %p", pPlugin);
        if (pPlugin != NULL)
        {
            PluginUtils::outputLog("ProtocolSocial", "nativeOnSocialResult(), Get plugin name : %s", pPlugin->getPluginName());
            ProtocolSocial* pSocial = dynamic_cast<ProtocolSocial*>(pPlugin);
            if (pSocial != NULL)
            {
                SocialListener* pListener = pSocial->getListener();
                if (NULL != pListener)
                {
                    pListener->onSocialResult((SocialRetCode) ret, strMsg.c_str());
                }
                else
                {
                	ProtocolSocial::ProtocolSocialCallback callback = pSocial->getCallback();
                	if (callback)
					{
						callback(ret, strMsg);
					}
                }
            }
        }
    }

}

ProtocolSocial::ProtocolSocial()
: _listener(NULL)
{
}

ProtocolSocial::~ProtocolSocial()
{
}

void ProtocolSocial::configDeveloperInfo(TSocialDeveloperInfo devInfo)
{
    if (devInfo.empty())
    {
        PluginUtils::outputLog("ProtocolSocial", "The developer info is empty!");
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

void ProtocolSocial::submitScore(const char* leadboardID, long score)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "submitScore"
        , "(Ljava/lang/String;J)V"))
    {
        jstring strID = PluginUtils::getEnv()->NewStringUTF(leadboardID);

        // invoke java method
        t.env->CallVoidMethod(pData->jobj, t.methodID, strID, score);
        t.env->DeleteLocalRef(strID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ProtocolSocial::submitScore(const char* leadboardID, long score, ProtocolSocialCallback cb)
{
	_callback = cb;
	submitScore(leadboardID, score);
}

void ProtocolSocial::showLeaderboard(const char* leaderboardID)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "showLeaderboard"
        , "(Ljava/lang/String;)V"))
    {
        jstring strID = PluginUtils::getEnv()->NewStringUTF(leaderboardID);

        // invoke java method
        t.env->CallVoidMethod(pData->jobj, t.methodID, strID);
        t.env->DeleteLocalRef(strID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void ProtocolSocial::unlockAchievement(TAchievementInfo achInfo)
{
    if (achInfo.empty())
    {
        PluginUtils::outputLog("ProtocolSocial", "The achievement info is empty!");
        return;
    }
    else
    {
        PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , "unlockAchievement"
            , "(Ljava/util/Hashtable;)V"))
        {
            // generate the hashtable from map
            jobject obj_Map = PluginUtils::createJavaMapObject(&achInfo);

            // invoke java method
            t.env->CallVoidMethod(pData->jobj, t.methodID, obj_Map);
            t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void ProtocolSocial::unlockAchievement(TAchievementInfo achInfo, ProtocolSocialCallback cb)
{
	_callback = cb;
	unlockAchievement(achInfo);
}

void ProtocolSocial::showAchievements()
{
    PluginUtils::callJavaFunctionWithName(this, "showAchievements");
}

}} // namespace cocos2d { namespace plugin {
