#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include <android_native_app_glue.h>
#include "PluginUtils.h"

#include "cocos2d.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (struct android_app* app) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
    PluginJniHelper::setJavaVM(app->activity->vm);
    PluginJniHelper::setClassLoaderFrom(app->activity->clazz);
    cocos2d::plugin::PluginUtils::initPluginWrapper(app);
}
