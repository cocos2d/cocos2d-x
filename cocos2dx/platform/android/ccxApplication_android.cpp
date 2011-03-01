#include "ccxApplication.h"

#include "CCDirector.h"
#include "CCXEGLView.h"
#include "Cocos2dJni.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "ccxApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
ccxApplication * ccxApplication::sm_pSharedApplication = 0;

ccxApplication::ccxApplication()
{
    CCX_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

ccxApplication::~ccxApplication()
{
    CCX_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int ccxApplication::run()
{
        // Initialize instance and cocos2d.
        if (! initInstance() || ! applicationDidFinishLaunching())
        {
                return 0;
        }
	
	return -1;
}

void ccxApplication::setAnimationInterval(double interval)
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

ccxApplication::Orientation ccxApplication::setOrientation(Orientation orientation)
{
    return orientation;
}

void ccxApplication::statusBarFrame(CGRect * rect)
{
    if (rect)
    {
        // android doesn't have status bar.
        *rect = CGRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
ccxApplication& ccxApplication::sharedApplication()
{
    CCX_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

NS_CC_END;
