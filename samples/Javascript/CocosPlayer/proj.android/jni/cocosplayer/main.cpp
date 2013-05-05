#include "AppDelegate.h"
#include "PlayerStatus.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "CCEventType.h"
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
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    
    else
    {
      /*
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
	CCTextureCache::reloadAllTextures();
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
	CCDirector::sharedDirector()->setGLDefaultValues(); 
      */
    }
}

  JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnScreenSizeChanged(JNIEnv* env, jobject thiz, jint w, jint h)
  {
    //    handle_set_orient(w, h);
  }

  void Java_org_cocos2dx_lib_Cocos2dxGLSurfaceView_nativeRunCCB(JNIEnv*  env, jobject thiz)
  {
    handle_ccb_run();
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeRunCCB(JNIEnv*  env, jobject thiz)
  {
    LOGD("INSIDE JNI RUN CALL %d %d", gettid(), getpid());
    handle_ccb_run();
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeStopCCB(JNIEnv*  env, jobject thiz)
  {
    LOGD("INSIDE JNI STOP CALL");
    setOrientationJNI(1);
    handle_ccb_stop();
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeRunScript(JNIEnv*  env, jobject thiz, jstring jsString)
  {

    std::string scriptStr;
    if (!jsString) {
      return;
    }

    const char *s = env->GetStringUTFChars(jsString,NULL);
    scriptStr = s;
    env->ReleaseStringUTFChars(jsString,s);
    jsval out;
    handle_eval_script(scriptStr.c_str(), &out);
    LOGD("INSIDE JNI RUN SCRIPT CALL");
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeConnectionStatus(JNIEnv*  env, jobject thiz, jstring jMsg) {
    
    std::string msg;
    if (!jMsg) {
      return;
    }
    
    const char *s = env->GetStringUTFChars(jMsg,NULL);
    msg = s;
    env->ReleaseStringUTFChars(jMsg,s);
    handle_set_status(msg.c_str());
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeStatus(JNIEnv*  env, jobject thiz, jstring jMsg)
  {
    std::string msg;
    if (!jMsg) {
      return;
    }
    
    const char *s = env->GetStringUTFChars(jMsg,NULL);
    msg = s;
    env->ReleaseStringUTFChars(jMsg,s);
    handle_set_message(msg.c_str());
  }


  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeConnected(JNIEnv*  env, jobject thiz)
  {
    handle_connected();
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeDisconnected(JNIEnv*  env, jobject thiz)
  {
    handle_disconnected();
  }

  void Java_org_cocos2dx_cocosplayer_CocosPlayerSocket_nativeSetOrientation(JNIEnv*  env, jobject thiz, jboolean isPortrait)
  {
    LOGD("INSIDE SET ORIENTATION CALL");
    handle_set_orient((bool)isPortrait);
  }
}
