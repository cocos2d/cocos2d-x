#include "tests.h"

#include <jni.h>
#include <android/log.h>

#include "AppDelegate.h"

using namespace cocos2d;

#define RESOURCE_PATH	"/data/app/org.cocos2dx.tests-1.apk"

extern "C"
{
	
void initProgram()
{
	AppDelegate app;
	app.Run();
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
	cocos2d::CCXEGLView *view = new cocos2d::CCXEGLView();
 	view->setFrameWitdAndHeight(w, h);
 	cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);
 		
 	initProgram();
}

}
