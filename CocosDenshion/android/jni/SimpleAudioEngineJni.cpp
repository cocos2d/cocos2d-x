#include "SimpleAudioEngineJni.h"
#include <android/log.h>

#define  LOG_TAG    "libSimpleAudioEngine"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


extern "C"
{
	static JavaVM *gJavaVM = 0;
	static jclass classOfCocos2dxActivity = 0;
	JNIEnv *env = 0;

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		gJavaVM = vm;

		return JNI_VERSION_1_4;
	}

	static jmethodID getMethodID(const char *methodName, const char *paramCode)
	{
		jmethodID ret = 0;

		// get jni environment and java class for Cocos2dxActivity
		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		{
			LOGD("Failed to get the environment using GetEnv()");
			return 0;
		}

		if (gJavaVM->AttachCurrentThread(&env, 0) < 0)
		{
			LOGD("Failed to get the environment using AttachCurrentThread()");
			return 0;
		}

		classOfCocos2dxActivity = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
		if (! classOfCocos2dxActivity)
		{
			LOGD("Failed to find class of org/cocos2dx/lib/Cocos2dxActivity");
			return 0;
		}

		if (env != 0 && classOfCocos2dxActivity != 0)
		{
			ret = env->GetStaticMethodID(classOfCocos2dxActivity, methodName, paramCode);
		}

		if (! ret)
		{
			LOGD("get method id of %s error", methodName);
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

	void stopBackgroundMusicJNI()
	{
		// void stopBackgroundMusic()
		jmethodID stopBackgroundMusicMethodID = getMethodID("stopBackgroundMusic", "()V");

		if (stopBackgroundMusicMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, stopBackgroundMusicMethodID);
		}
	}

	void pauseBackgroundMusicJNI()
	{
		// void pauseBackgroundMusic()
		jmethodID pauseBackgroundMusicMethodID = getMethodID("pauseBackgroundMusic", "()V");

		if (pauseBackgroundMusicMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, pauseBackgroundMusicMethodID);
		}
	}

	void resumeBackgroundMusicJNI()
	{
		// void resumeBackgroundMusic()
		jmethodID resumeBackgroundMusicMethodID = getMethodID("resumeBackgroundMusic", "()V");

		if (resumeBackgroundMusicMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, resumeBackgroundMusicMethodID);
		}
	}

	void rewindBackgroundMusicJNI()
	{
		// void rewindBackgroundMusic()
		jmethodID rewindBackgroundMusicMethodID = getMethodID("rewindBackgroundMusic", "()V");

		if (rewindBackgroundMusicMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, rewindBackgroundMusicMethodID);
		}
	}

	bool isBackgroundMusicPlayingJNI()
	{
		// boolean rewindBackgroundMusic()
		jmethodID isBackgroundMusicPlayingMethodID = getMethodID("isBackgroundMusicPlaying", "()Z");
		jboolean ret = false;

		if (isBackgroundMusicPlayingMethodID)
		{
			ret = env->CallStaticBooleanMethod(classOfCocos2dxActivity, isBackgroundMusicPlayingMethodID);
		}

		return ret;
	}

	float getBackgroundMusicVolumeJNI()
	{
		// float getBackgroundMusicVolume()
		jmethodID getBackgroundMusicVolumeID = getMethodID("getBackgroundMusicVolume", "()F");
		jfloat ret = 0.0;

		if (getBackgroundMusicVolumeID)
		{
			ret = env->CallStaticFloatMethod(classOfCocos2dxActivity, getBackgroundMusicVolumeID);
		}

		return ret;
	}

	void setBackgroundMusicVolumeJNI(float volume)
	{
		// void setBackgroundMusicVolume()
		jmethodID setBackgroundMusicVolumeMethodID = getMethodID("setBackgroundMusicVolume", "(F)V");

		if (setBackgroundMusicVolumeMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, setBackgroundMusicVolumeMethodID, volume);
		}
	}

	unsigned int playEffectJNI(const char* path, bool bLoop)
	{
		int ret = 0;

		// int playEffect(String)
		jmethodID playEffectMethodID = getMethodID("playEffect", "(Ljava/lang/String;Z)I");

		if (playEffectMethodID)
		{
			jstring StringArg = env->NewStringUTF(path);
			ret = env->CallStaticIntMethod(classOfCocos2dxActivity, playEffectMethodID, StringArg, bLoop);
		}

		return (unsigned int)ret;
	}

	void stopEffectJNI(unsigned int nSoundId)
	{
		// void stopEffect(int)
		jmethodID stopEffectMethodID = getMethodID("stopEffect", "(I)V");

		if (stopEffectMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, stopEffectMethodID, (int)nSoundId);
		}
	}

	void endJNI()
	{
		// void end()
		jmethodID endMethodID = getMethodID("end", "()V");

		if (endMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, endMethodID);
		}
	}

	float getEffectsVolumeJNI()
	{
		// float getEffectsVolume()
		jmethodID getEffectsVolumeMethodID = getMethodID("getEffectsVolume", "()F");
		jfloat ret = -1.0;

		if (getEffectsVolumeMethodID)
		{
			ret = env->CallStaticFloatMethod(classOfCocos2dxActivity, getEffectsVolumeMethodID);
		}

		return ret;
	}

	void setEffectsVolumeJNI(float volume)
	{
		// void setEffectsVolume(float)
		jmethodID setEffectsVolumeMethodID = getMethodID("setEffectsVolume", "(F)V");

		if (setEffectsVolumeMethodID)
		{
			env->CallStaticVoidMethod(classOfCocos2dxActivity, setEffectsVolumeMethodID, volume);
		}
	}

	void preloadEffectJNI(const char *path)
	{
		// void preloadEffect(String)
		jmethodID preloadEffectMethodID = getMethodID("preloadEffect", "(Ljava/lang/String;)V");

		if (preloadEffectMethodID)
		{
			jstring StringArg = env->NewStringUTF(path);
			env->CallStaticVoidMethod(classOfCocos2dxActivity, preloadEffectMethodID, StringArg);
		}
	}

	void unloadEffectJNI(const char* path)
	{
		// void unloadEffect(String)
		jmethodID unloadEffectMethodID = getMethodID("unloadEffect", "(Ljava/lang/String;)V");

		if (unloadEffectMethodID)
		{
			jstring StringArg = env->NewStringUTF(path);
			env->CallStaticVoidMethod(classOfCocos2dxActivity, unloadEffectMethodID, StringArg);
		}
	}
}
