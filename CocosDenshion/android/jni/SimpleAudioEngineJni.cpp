#include "SimpleAudioEngineJni.h"
#include <android/log.h>

#define  LOG_TAG    "libSimpleAudioEngine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
{
	static JavaVM *gJavaVM = 0;
	static jclass classOfCocos2dxActivity = 0;
	JNIEnv *env = 0;

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		gJavaVM = vm;

		LOGI("JNI_OnLoad");

		LOGI("JNI_OnLoad ok");

		return JNI_VERSION_1_4;
	}

	static jmethodID getMethodID(const char *methodName, const char *paramCode)
	{
		jmethodID ret = 0;

		LOGI("getMethodID");

		// get jni environment and java class for Cocos2dxActivity
		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		{
			LOGE("Failed to get the environment using GetEnv()");
			return 0;
		}

		if (gJavaVM->AttachCurrentThread(&env, 0) < 0)
		{
			LOGE("Failed to get the environment using AttachCurrentThread()");
			return 0;
		}

		classOfCocos2dxActivity = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
		if (! classOfCocos2dxActivity)
		{
			LOGE("Failed to find class of org/cocos2dx/lib/Cocos2dxActivity");
			return 0;
		}

		if (env != 0 && classOfCocos2dxActivity != 0)
		{
			ret = env->GetStaticMethodID(classOfCocos2dxActivity, methodName, paramCode);
			LOGI("after GetStaticMethodID");
		}

		if (ret)
		{
			LOGI("get method id of %s ok", methodName);
		}

		return ret;
	}

	void playBackgroundMusicJNI(const char *path, bool isLoop)
	{
		// void playBackgroundMusic(String,boolean)
		jmethodID playBackgroundMusicMethodID = getMethodID("playBackgroundMusic", "(Ljava/lang/String;Z)V");

		if (playBackgroundMusicMethodID)
		{
			jstring StringArg = env->NewStringUTF(path);
			env->CallStaticVoidMethod(classOfCocos2dxActivity, playBackgroundMusicMethodID, StringArg, isLoop);
			//env->ReleaseStringUTFChars(StringArg, path);
		}
	}
}
