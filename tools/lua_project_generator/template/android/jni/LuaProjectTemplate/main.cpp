#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;
using namespace cocos2d::extension;

extern "C"
{

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = &CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);
        // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
        // view->setDesignResolutionSize(480, 320);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication().run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();

        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}



}
