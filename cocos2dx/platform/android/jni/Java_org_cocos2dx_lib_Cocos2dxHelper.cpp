#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "cocoa/CCString.h"
#include "Java_org_cocos2dx_lib_Cocos2dxHelper.h"


#define  LOG_TAG    "Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

static EditTextCallback s_pfEditTextCallback = NULL;
static void* s_ctx = NULL;

using namespace cocos2d;
using namespace std;

extern "C" {
    string g_apkPath;
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(JNIEnv*  env, jobject thiz, jstring apkPath) {
        g_apkPath = JniHelper::jstring2string(apkPath);
    }

    const char * getApkPath() {
        return g_apkPath.c_str();
    }

    void showDialogJNI(const char * pszMsg, const char * pszTitle) {
        if (!pszMsg) {
            return;
        }

        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring stringArg1;

            if (!pszTitle) {
                stringArg1 = t.env->NewStringUTF("");
            } else {
                stringArg1 = t.env->NewStringUTF(pszTitle);
            }

            jstring stringArg2 = t.env->NewStringUTF(pszMsg);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

            t.env->DeleteLocalRef(stringArg1);
            t.env->DeleteLocalRef(stringArg2);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void showEditTextDialogJNI(const char* pszTitle, const char* pszMessage, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback, void* ctx) {
        if (pszMessage == NULL) {
            return;
        }

        s_pfEditTextCallback = pfEditTextCallback;
        s_ctx = ctx;

        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showEditTextDialog", "(Ljava/lang/String;Ljava/lang/String;IIII)V")) {
            jstring stringArg1;

            if (!pszTitle) {
                stringArg1 = t.env->NewStringUTF("");
            } else {
                stringArg1 = t.env->NewStringUTF(pszTitle);
            }

            jstring stringArg2 = t.env->NewStringUTF(pszMessage);

            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, nInputMode, nInputFlag, nReturnType, nMaxLength);

            t.env->DeleteLocalRef(stringArg1);
            t.env->DeleteLocalRef(stringArg2);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jobject obj, jbyteArray text) {
        jsize  size = env->GetArrayLength(text);

        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* pBuf = (char*)malloc(size+1);
            if (pBuf != NULL) {
                memcpy(pBuf, data, size);
                pBuf[size] = '\0';
                // pass data to edittext's delegate
                if (s_pfEditTextCallback) s_pfEditTextCallback(pBuf, s_ctx);
                free(pBuf);
            }
            env->ReleaseByteArrayElements(text, data, 0);
        } else {
            if (s_pfEditTextCallback) s_pfEditTextCallback("", s_ctx);
        }
    }

    void terminateProcessJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "terminateProcess", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

   const char* getPackageNameJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxPackageName", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
            ret->autorelease();
            t.env->DeleteLocalRef(str);

            return ret->m_sString.c_str();
        }

        return 0;
    }

    const char * getFileDirectoryJNI() {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxWritablePath", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
            ret->autorelease();
            t.env->DeleteLocalRef(str);
            
            return ret->m_sString.c_str();
        }
        
        return 0;
    }

    const char* getCurrentLanguageJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
            ret->autorelease();
            t.env->DeleteLocalRef(str);

            return ret->m_sString.c_str();
        }

        return 0;
    }

    void enableAccelerometerJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAccelerometer", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void setAccelerometerIntervalJNI(float interval) {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setAccelerometerInterval", "(I)V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, interval);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void disableAccelerometerJNI() {
        JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAccelerometer", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    
    // functions for CCUserDefault
    bool getBoolForKeyJNI(const char* pKey)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBoolForKey", "(Ljava/lang/String;)Z")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
            
            return ret;
        }
        
        return false;
    }
    
    int getIntegerForKeyJNI(const char* pKey)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getIntegerForKey", "(Ljava/lang/String;)I")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, stringArg);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
            
            return ret;
        }
        
        return 0;
    }
    
    float getFloatForKeyJNI(const char* pKey)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getFloatForKey", "(Ljava/lang/String;)F")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            jfloat ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, stringArg);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
            
            return ret;
        }
        
        return 0;
    }
    
    double getDoubleForKeyJNI(const char* pKey)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDoubleForKey", "(Ljava/lang/String;)D")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            jdouble ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, stringArg);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
            
            return ret;
        }
        
        return 0;
    }
    
    const char* getStringForKeyJNI(const char* pKey)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getStringForKey", "(Ljava/lang/String;)Ljava/lang/String;")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg);
            CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
            ret->autorelease();
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
            t.env->DeleteLocalRef(str);
            
            return ret->getCString();
        }
        
        return 0;
    }
    
    void setBoolForKeyJNI(const char* pKey, bool value)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBoolForKey", "(Ljava/lang/String;Z)V")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
        }
    }
    
    void setIntegerForKeyJNI(const char* pKey, int value)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setIntegerForKey", "(Ljava/lang/String;I)V")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
        }
    }
    
    void setFloatForKeyJNI(const char* pKey, float value)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFloatForKey", "(Ljava/lang/String;F)V")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
        }
    }
    
    void setDoubleForKeyJNI(const char* pKey, double value)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDoubleForKey", "(Ljava/lang/String;D)V")) {
            jstring stringArg = t.env->NewStringUTF(pKey);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg);
        }
    }
    
    void setStringForKeyJNI(const char* pKey, const char* value)
    {
        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setStringForKeyKey", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring stringArg1 = t.env->NewStringUTF(pKey);
            jstring stringArg2 = t.env->NewStringUTF(value);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
            
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg1);
            t.env->DeleteLocalRef(stringArg2);
        }
    }
}
