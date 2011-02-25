#include "Application.h"

#include "CCDirector.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "tests Application"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

static JavaVM *gJavaVM = NULL;

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	gJavaVM = vm;
	return JNI_VERSION_1_4;
}

USING_NS_CC;

Application::Application()
{

}

Application::~Application()
{

}

int Application::run()
{
	// Make sharedApplication work correctly.
	setSharedApplication(*(new Application()));

	// Initialize AppDelegate.
	if (! m_Delegate.applicationDidFinishLaunching())
	{
		return 0;
	}
}

bool Application::initInstance()
{
	return true;
}

void Application::setAnimationInterval(double interval)
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

Application::Orientation Application::setOrientation(Application::Orientation orientation)
{
	return orientation;
}

void Application::statusBarFrame(cocos2d::CGRect * rect)
{
	LOGD("statusBarFrame 0");

    if (rect)
    {
		LOGD("statusBarFrame 1");
        // Android doesn't have status bar.
        *rect = CGRectMake(0, 0, 0, 0);
		LOGD("statusBarFrame 2");
    }
}
