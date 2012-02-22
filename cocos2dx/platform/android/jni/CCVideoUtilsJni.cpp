#include "CCVideoUtilsJni.h"

#include "CCDirector.h"
#include "platform/android/jni/JniHelper.h"
#include "CCApplication.h"
#include "CCFileUtils.h"

#include <android/log.h>
#include <jni.h>
#if 0
#define  LOG_TAG    "CCVideoUtilsJni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

using namespace cocos2d;

cocos2d::CCObject* g_videoTarget = NULL;
cocos2d::SEL_CallFuncN g_videoSelector = NULL;
cocos2d::CCNode* g_videoObject = NULL;

extern "C"
{
	void Java_org_cocos2dx_lib_Cocos2dxVideo_onVideoCompleted(JNIEnv*  env, jobject thiz) {
		if (g_videoTarget && g_videoSelector) {
			(g_videoTarget->*g_videoSelector)(g_videoObject);
		}
	}

	void playVideoJNI(const char *path, bool showControls, bool skipByTap, cocos2d::CCObject* pSelectorTarget,
			cocos2d::SEL_CallFuncN selector, cocos2d::CCNode* withObject)
	{
		JniMethodInfo methodInfo;

		g_videoTarget = pSelectorTarget;
		g_videoSelector = selector;
		g_videoObject = withObject;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxVideo", "playVideo", "(Ljava/lang/String;ZZ)V"))
		{
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(path);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, showControls, skipByTap);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}

	void openURLJNI(const char *url) {
		JniMethodInfo methodInfo;

		if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxVideo", "openURL", "(Ljava/lang/String;)V"))
		{
			return;
		}

		jstring stringArg = methodInfo.env->NewStringUTF(url);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
		methodInfo.env->DeleteLocalRef(stringArg);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
	}
}
