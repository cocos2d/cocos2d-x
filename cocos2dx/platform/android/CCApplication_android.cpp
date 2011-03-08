#include "CCApplication.h"

#include "CCDirector.h"
#include "CCEGLView.h"
#include "Cocos2dJni.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "CCApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
        // Initialize instance and cocos2d.
        if (! initInstance() || ! applicationDidFinishLaunching())
        {
                return 0;
        }
	
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
    jmethodID ret = 0;
	JNIEnv *env = 0;
	jclass classOfCocos2dxRenderer = 0;

	if (! gJavaVM)
	{
		LOGD("have not java vm");
		return;
	}

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

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
    return orientation;
}

void CCApplication::statusBarFrame(CCRect * rect)
{
    if (rect)
    {
        // android doesn't have status bar.
        *rect = CCRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

NS_CC_END;
