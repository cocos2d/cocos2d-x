//
// Android only
//

#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "platform/android/jni/JniHelper.h"
#include "cocoa/CCString.h"
#include "TestHelperJNI.h"
#include "jsapi.h"

#define  LOG_TAG    "Java_org_cocos2dx_cocosplayer_CocosPlayerSocket.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  MAIN_CLASS_NAME "org/cocos2dx/testjavascript/TestJavascript"

using namespace cocos2d;
using namespace std;

extern "C" {
  void closeActivityJNI() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, MAIN_CLASS_NAME, "switchAndKillActivityTest", "()V")) {
	  t.env->CallStaticVoidMethod(t.classID, t.methodID);
	  t.env->DeleteLocalRef(t.classID);
        }
  }
}
