#include "CCApplication_android.h"
#include "CCImage_android.h"
#include "CCEGLView_android.h"
#include "CCDirector.h"
#include "Cocos2dJni.h"

#include <GLES/glext.h>
#include <android/log.h>

#define  LOG_TAG    "Application android"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace   cocos2d {
	static CCApplication *s_pApplication;

    CCApplication::CCApplication()
    {
    	s_pApplication = this;
    }

    CCApplication::~CCApplication()
    {
        
    }

	ccDeviceOrientation CCApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
    {
		return eOritation;
    }

    CCRect CCApplication::statusBarFrame()
    {
        CCRect rc;
        return rc;
    }
    
    void CCApplication::Run()
    {
    	applicationDidFinishLaunching();
    }

	void CCApplication::setAnimationInterval(double interval)
	{
		jmethodID ret = 0;
		JNIEnv *env = 0;
		jclass classOfCocos2dxRenderer = 0;

		// get jni environment and java class for Cocos2dxActivity
		if (gJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
		{
			LOGD("Failed to get the environment using GetEnv()");
			return;
		}

		if (gJavaVM->AttachCurrentThread(&env, 0) < 0)
		{
			LOGD("Failed to get the environment using AttachCurrentThread()");
			return;
		}

		classOfCocos2dxRenderer = env->FindClass("org/cocos2dx/lib/Cocos2dxRenderer");
		if (! classOfCocos2dxRenderer)
		{
			LOGD("Failed to find class of org/cocos2dx/lib/Cocos2dxRenderer");
			return;
		}

		if (env != 0 && classOfCocos2dxRenderer != 0)
		{
			ret = env->GetStaticMethodID(classOfCocos2dxRenderer, "setAnimationInterval", "(D)V");
			
			if (ret != 0)
			{
			        env->CallStaticVoidMethod(classOfCocos2dxRenderer, ret, interval);
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCApplication * CCApplication::sharedApplication()
	{
		return s_pApplication;
	}
}
