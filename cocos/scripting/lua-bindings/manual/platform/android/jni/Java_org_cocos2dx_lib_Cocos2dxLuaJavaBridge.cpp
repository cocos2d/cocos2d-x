
#include "Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge.h"

#include <android/log.h>

#include "CCLuaJavaBridge.h"

#include "base/ccUTF8.h"

#define  LOG_TAG    "Cocos2dxLuaJavaBridge_java"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaFunctionWithString
  (JNIEnv *env, jclass cls, jint functionId, jstring value)
{
    std::string strValue = cocos2d::StringUtils::getStringUTFCharsJNI(env, value);
    int ret = LuaJavaBridge::callLuaFunctionById(functionId, strValue.c_str());
    return ret;
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaGlobalFunctionWithString
  (JNIEnv *env, jclass cls, jstring luaFunctionName, jstring value)
{
    std::string functionNameStr = cocos2d::StringUtils::getStringUTFCharsJNI(env, luaFunctionName);
    std::string valueStr = cocos2d::StringUtils::getStringUTFCharsJNI(env, value);
    
    int ret = LuaJavaBridge::callLuaGlobalFunction(functionNameStr.c_str(), valueStr.c_str());
    return ret;
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_retainLuaFunction
  (JNIEnv *env, jclass cls, jint luaFunctionId)
{
    return LuaJavaBridge::retainLuaFunctionById(luaFunctionId);
}

JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_releaseLuaFunction
  (JNIEnv *env, jclass cls, jint luaFunctionId)
{
    return LuaJavaBridge::releaseLuaFunctionById(luaFunctionId);
}

} // extern "C"
