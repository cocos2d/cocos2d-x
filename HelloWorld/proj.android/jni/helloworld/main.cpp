#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "CCEventType.h"
#include <jni.h>
#include <android/log.h>

#include "HelloWorldScene.h"

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
        view->setFrameSize(w, h);
        // if you want to run in WVGA with HVGA resource, set it
        // view->setDesignResolutionSize(480, 320);  Please change it to (320, 480) if you're in portrait mode.
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

        AppDelegate *pAppDelegate = new AppDelegate();
        cocos2d::CCApplication::sharedApplication().run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        cocos2d::CCTextureCache::reloadAllTextures();
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}
