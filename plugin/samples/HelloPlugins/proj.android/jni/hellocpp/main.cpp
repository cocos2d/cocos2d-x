#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{
    
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);
    PluginJniHelper::setJavaVM(vm);  // for plugins
    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!Director::sharedDirector()->getOpenGLView())
    {
        EGLView *view = EGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        Application::sharedApplication()->run();
    }
    /*
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
          
        ShaderCache::sharedShaderCache()->reloadDefaultShaders();
        TextureCache::reloadAllTextures();
        NotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        Director::sharedDirector()->setGLDefaultValues(); 
    }
     */
}

}
