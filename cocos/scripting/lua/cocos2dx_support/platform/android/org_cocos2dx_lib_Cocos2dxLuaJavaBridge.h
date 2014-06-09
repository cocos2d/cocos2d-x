
#include <jni.h>

#ifndef __JAVA_ORG_COCOS2DX_LIB_LUAJAVABRIDGE_H_
#define __JAVA_ORG_COCOS2DX_LIB_LUAJAVABRIDGE_H_

extern "C" {

/*
 * Class:     Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge
 * Method:    callLuaFunctionWithString
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaFunctionWithString
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge
 * Method:    callLuaGlobalFunctionWithString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_callLuaGlobalFunctionWithString
  (JNIEnv *env, jclass, jstring, jstring);

/*
 * Class:     Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge
 * Method:    retainLuaFunction
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_retainLuaFunction
  (JNIEnv *env, jclass, jint);

/*
 * Class:     Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge
 * Method:    releaseLuaFunction
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_cocos2dx_lib_Cocos2dxLuaJavaBridge_releaseLuaFunction
  (JNIEnv *env, jclass, jint);

} // extern "C"

#endif // __JAVA_ORG_COCOS2DX_LIB_LUAJAVABRIDGE_H_
