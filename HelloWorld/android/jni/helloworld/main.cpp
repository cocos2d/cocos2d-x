#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	JniHelper::setJavaVM(vm);

	return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView())
    {
	cocos2d::CCEGLView *view = &cocos2d::CCEGLView::sharedOpenGLView();
        view->setFrameWidthAndHeight(w, h);
        // if you want to run in WVGA with HVGA resource, set it
        // view->create(480, 320);  Please change it to (320, 480) if you're in portrait mode.
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

        AppDelegate *pAppDelegate = new AppDelegate();
        cocos2d::CCApplication::sharedApplication().run();
    }
    else
    {
        cocos2d::CCTextureCache::reloadAllTextures();
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

}
