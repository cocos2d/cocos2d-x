#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>

using namespace cocos2d;

#define IMG_PATH        "assets"
#define RESOURCE_PATH	"/data/app/org.cocos2dx.application-1.apk"

extern "C"
{

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
	cocos2d::CCXEGLView *view = new cocos2d::CCXEGLView();
 	view->setFrameWitdAndHeight(w, h);
 	cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);
 	
 	CCFileUtils::setResourcePath(RESOURCE_PATH);
	CCFileUtils::setRelativePath(IMG_PATH);
 		
 	AppDelegate app;
 	app.Run();
}

}
