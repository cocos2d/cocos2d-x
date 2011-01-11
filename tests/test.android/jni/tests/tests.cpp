#include "tests.h"

#include <jni.h>
#include <android/log.h>

#include "AppDelegate.h"

using namespace cocos2d;

#define RESOURCE_PATH	"/data/app/org.cocos2dx.application-1.apk"

extern "C"
{
	
void initProgram(const char *apkPath)
{
	AppDelegate app;
	app.apkPath = apkPath;
	app.Run();
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h, jstring apkPath)
{
	const char *nativeString = env->GetStringUTFChars(apkPath, 0);


	__android_log_write(ANDROID_LOG_ERROR,"cocos2d-x", nativeString);

	cocos2d::CCXEGLView *view = new cocos2d::CCXEGLView();
 	view->setFrameWitdAndHeight(w, h);
 	cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

 	initProgram(nativeString);
	env->ReleaseStringUTFChars(apkPath, nativeString);
}

}
