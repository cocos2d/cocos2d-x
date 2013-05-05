#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "platform/android/jni/JniHelper.h"
#include "cocoa/CCString.h"
#include "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.h"
#include "jsapi.h"

#define  LOG_TAG    "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  SOCKET_CLASS_NAME "org/cocos2dx/cocosplayer/CocosPlayerSocket"
#define  MAIN_CLASS_NAME "org/cocos2dx/cocosplayer/CocosPlayer"
#define  STREAM_CLASS_NAME "org/cocos2dx/cocosplayer/CCBStreamHandler"

using namespace cocos2d;
using namespace std;

const int SCREEN_ORIENTATION_PORTRAIT = 1;
const int SCREEN_ORIENTATION_LANDSCAPE = 0;

extern "C" {
   void updatePairing(const char *code) {
       int pairingCode = 0;
       if(strcmp(code, "Auto") == 0) {
	   pairingCode = -1;
       } else {
	   pairingCode = atoi(code);
       }
       JniMethodInfo t;
       if (JniHelper::getStaticMethodInfo(t, SOCKET_CLASS_NAME, "setPairingCode", "(I)V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID, pairingCode);
	  t.env->DeleteLocalRef(t.classID);
       }
   }

  void setOrientationJNI(int orient) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, MAIN_CLASS_NAME, "setOrientation", "(I)V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID, orient);
	  t.env->DeleteLocalRef(t.classID);
        }    
	handle_set_orient(orient == SCREEN_ORIENTATION_PORTRAIT);
  }

  void runJSApp() {
    handle_ccb_run();
    setOrientationJNI(SCREEN_ORIENTATION_PORTRAIT);
  }
  

   void cleanCacheDirJNI() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, SOCKET_CLASS_NAME, "cleanCache", "()V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID);
	  t.env->DeleteLocalRef(t.classID);
        }
   }

  void setDeviceResolutionJNI(const char *res) {
      JniMethodInfo t;
      if (JniHelper::getStaticMethodInfo(t, STREAM_CLASS_NAME, "setDeviceResolution", "(Ljava/lang/String;)V")) {
	  jstring stringArg1 = t.env->NewStringUTF(res);
	  t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
	  t.env->DeleteLocalRef(stringArg1);
	  t.env->DeleteLocalRef(t.classID);
      }
  }


  void sendLogMsg(const char *res) {
      JniMethodInfo t;
      if (JniHelper::getStaticMethodInfo(t, SOCKET_CLASS_NAME, "sendLog", "(Ljava/lang/String;)V")) {
	  jstring stringArg1 = t.env->NewStringUTF(res);
	  t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
	  t.env->DeleteLocalRef(stringArg1);
	  t.env->DeleteLocalRef(t.classID);
      }
  }

  const char *getCCBDirectoryPath() {
      return "";
  }

  void resetCocosApp() {
  }
}
