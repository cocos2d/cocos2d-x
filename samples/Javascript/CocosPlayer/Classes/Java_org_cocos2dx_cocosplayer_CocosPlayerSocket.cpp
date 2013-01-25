#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "platform/android/jni/JniHelper.h"
#include "cocoa/CCString.h"
#include "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.h"

#define  LOG_TAG    "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  SOCKET_CLASS_NAME "org/cocos2dx/cocosplayer/CocosPlayerSocket"
#define  HELPER_CLASS_NAME "org/cocos2dx/cocosplayer/CCBFileUtilsHelper"

using namespace cocos2d;
using namespace std;

extern "C" {
   void setPairingCodeJNI(int code) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, SOCKET_CLASS_NAME, "setPairingCode", "(I)V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID, code);
	  t.env->DeleteLocalRef(t.classID);
        }
    }

   void cleanCacheDirJNI() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "cleanCache", "()V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID);
	  t.env->DeleteLocalRef(t.classID);
        }
    }
}
