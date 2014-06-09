
#include "org_cocos2dx_lib_Cocos2dxLuaJavaBridge.h"

#include <android/log.h>

#include "CCLuaJavaBridge.h"

#define  LOG_TAG    "Cocos2dxLuaJavaBridge_java"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaFunctionWithString
  (JNIEnv *env, jclass cls, jint functionId, jstring value)
{
    const char *value_ = env->GetStringUTFChars(value, 0);
    int ret = CCLuaJavaBridge::callLuaFunctionById(functionId, value_);
    env->ReleaseStringUTFChars(value, value_);
    return ret;
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaGlobalFunctionWithString
  (JNIEnv *env, jclass cls, jstring luaFunctionName, jstring value)
{
    const char *luaFunctionName_ = env->GetStringUTFChars(luaFunctionName, 0);
    const char *value_ = env->GetStringUTFChars(value, 0);
    int ret = CCLuaJavaBridge::callLuaGlobalFunction(luaFunctionName_, value_);
    env->ReleaseStringUTFChars(luaFunctionName, luaFunctionName_);
    env->ReleaseStringUTFChars(value, value_);
    return ret;
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_retainLuaFunction
  (JNIEnv *env, jclass cls, jint luaFunctionId)
{
    return CCLuaJavaBridge::retainLuaFunctionById(luaFunctionId);
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_releaseLuaFunction
  (JNIEnv *env, jclass cls, jint luaFunctionId)
{
    return CCLuaJavaBridge::releaseLuaFunctionById(luaFunctionId);
}

} // extern "C"
