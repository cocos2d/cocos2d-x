/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "CCFileUtils-android.h"
#include "android/asset_manager_jni.h"
#include "deprecated/CCString.h"
#include "Java_org_cocos2dx_lib_Cocos2dxHelper.h"

#include "base/ccUTF8.h"

#define  LOG_TAG    "Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"
#define  EDITBOX_CLASS_NAME "org/cocos2dx/lib/Cocos2dxEditBoxHelper"

static EditTextCallback s_editTextCallback = nullptr;
static void* s_ctx = nullptr;

using namespace cocos2d;
using namespace std;

string g_apkPath;

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(JNIEnv*  env, jobject thiz, jstring apkPath) {
        g_apkPath = JniHelper::jstring2string(apkPath);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetContext(JNIEnv*  env, jobject thiz, jobject context, jobject assetManager) {
        JniHelper::setClassLoaderFrom(context);
        FileUtilsAndroid::setassetmanager(AAssetManager_fromJava(env, assetManager));
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jobject obj, jbyteArray text) {
        jsize  size = env->GetArrayLength(text);

        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* buffer = (char*)malloc(size+1);
            if (buffer != nullptr) {
                memcpy(buffer, data, size);
                buffer[size] = '\0';
                // pass data to edittext's delegate
                if (s_editTextCallback) s_editTextCallback(buffer, s_ctx);
                free(buffer);
            }
            env->ReleaseByteArrayElements(text, data, 0);
        } else {
            if (s_editTextCallback) s_editTextCallback("", s_ctx);
        }
    }

}

const char * getApkPath() {
    return g_apkPath.c_str();
}

void showDialogJNI(const char * message, const char * title) {
    if (!message) {
        return;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1;

        if (!title) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(title);
        }

        jstring stringArg2 = t.env->NewStringUTF(message);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void terminateProcessJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "terminateProcess", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string getPackageNameJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxPackageName", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}

std::string getFileDirectoryJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxWritablePath", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    return ret;
}

std::string getCurrentLanguageJNI() {
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    return ret;
}

void enableAccelerometerJni() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setAccelerometerIntervalJni(float interval) {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setAccelerometerInterval", "(F)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, interval);
        t.env->DeleteLocalRef(t.classID);
    }
}

void disableAccelerometerJni() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setKeepScreenOnJni(bool value) {
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setKeepScreenOn", "(Z)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
        
        t.env->DeleteLocalRef(t.classID);
    }
}

void vibrateJni(float duration) {
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "vibrate", "(F)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, duration);
        
        t.env->DeleteLocalRef(t.classID);
    }
}

extern bool openURLJNI(const char* url) {
    JniMethodInfo t;
    
    bool ret = false;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "openURL", "(Ljava/lang/String;)Z")) {
        jstring stringArg = t.env->NewStringUTF(url);
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
    return ret;
}

// functions for UserDefault
bool getBoolForKeyJNI(const char* key, bool defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBoolForKey", "(Ljava/lang/String;Z)Z")) {
        jstring stringArg = t.env->NewStringUTF(key);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

int getIntegerForKeyJNI(const char* key, int defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getIntegerForKey", "(Ljava/lang/String;I)I")) {
        jstring stringArg = t.env->NewStringUTF(key);
        jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

float getFloatForKeyJNI(const char* key, float defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getFloatForKey", "(Ljava/lang/String;F)F")) {
        jstring stringArg = t.env->NewStringUTF(key);
        jfloat ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

double getDoubleForKeyJNI(const char* key, double defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDoubleForKey", "(Ljava/lang/String;D)D")) {
        jstring stringArg = t.env->NewStringUTF(key);
        jdouble ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

std::string getStringForKeyJNI(const char* key, const char* defaultValue)
{
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getStringForKey", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
        jstring stringArg1 = t.env->NewStringUTF(key);
        jstring stringArg2 = t.env->NewStringUTF(defaultValue);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, stringArg2);
        ret = JniHelper::jstring2string(str);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(str);
        
        return ret;
    }
    
    return defaultValue;
}

void setBoolForKeyJNI(const char* key, bool value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBoolForKey", "(Ljava/lang/String;Z)V")) {
        jstring stringArg = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setIntegerForKeyJNI(const char* key, int value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setIntegerForKey", "(Ljava/lang/String;I)V")) {
        jstring stringArg = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setFloatForKeyJNI(const char* key, float value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFloatForKey", "(Ljava/lang/String;F)V")) {
        jstring stringArg = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setDoubleForKeyJNI(const char* key, double value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDoubleForKey", "(Ljava/lang/String;D)V")) {
        jstring stringArg = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setStringForKeyJNI(const char* key, const char* value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setStringForKey", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(key);
        jstring stringArg2 = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
    }
}

void deleteValueForKeyJNI(const char* key)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "deleteValueForKey", "(Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(key);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
}

int addEditBoxJNI(int left, int top, int width, int height, float scaleX){
    JniMethodInfo t;

    int ret = -1;
    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "createEditBox", "(IIIIF)I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID, left, top, width, height, scaleX);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

void removeEditBoxJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "removeEditBox", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setEditBoxViewRectJNI(int index, int left, int top, int width, int height)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setEditBoxViewRect", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, left, top, width, height);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setMaxLengthJNI(int index, int maxLength)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setMaxLength", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, maxLength);
        t.env->DeleteLocalRef(t.classID);
    }
}

void openEditBoxKeyboardJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "openKeyboard", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void closeEditBoxKeyboardJNI(int index)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "closeKeyboard", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setVisibleEditBoxJNI(int index, bool visibility)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setVisible", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, visibility);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setReturnTypeEditBoxJNI(int index, int returnType)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setReturnType", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, returnType);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setInputFlagEditBoxJNI(int index, int returnType)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setInputFlag", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, returnType);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setInputModeEditBoxJNI(int index, int inputMode)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setInputMode", "(II)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, inputMode);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setTextEditBoxJNI(int index, const char* text)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setText", "(ILjava/lang/String;)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText);
        t.env->DeleteLocalRef(stringText);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setFontEditBoxJNI(int index, const char* fontName, float fontSize)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setFont", "(ILjava/lang/String;F)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,fontName);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText, fontSize);

        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringText);
    }
}

void setFontColorEditBoxJNI(int index, int red, int green, int blue, int alpha)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setFontColor", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, red, green, blue, alpha);

        t.env->DeleteLocalRef(t.classID);
    }
}

void setPlaceHolderTextEditBoxJNI(int index, const char* text)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setPlaceHolderText", "(ILjava/lang/String;)V")) {
        jstring stringText = StringUtils::newStringUTFJNI(t.env,text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, stringText);

        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringText);
    }

}

void setPlaceHolderTextColorEditBoxJNI(int index, int red, int green, int blue, int alpha)
{
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, EDITBOX_CLASS_NAME, "setPlaceHolderTextColor", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,index, red, green, blue, alpha);

        t.env->DeleteLocalRef(t.classID);
    }
}

void conversionEncodingJNI(const char* src, int byteSize, const char* fromCharset, char* dst, const char* newCharset)
{
    JniMethodInfo methodInfo;

    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "conversionEncoding", "([BLjava/lang/String;Ljava/lang/String;)[B")) {
        jbyteArray strArray = methodInfo.env->NewByteArray(byteSize);
        methodInfo.env->SetByteArrayRegion(strArray, 0, byteSize, reinterpret_cast<const jbyte*>(src));

        jstring stringArg1 = methodInfo.env->NewStringUTF(fromCharset);
        jstring stringArg2 = methodInfo.env->NewStringUTF(newCharset);

        jbyteArray newArray = (jbyteArray)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, strArray, stringArg1, stringArg2);
        jsize theArrayLen = methodInfo.env->GetArrayLength(newArray);
        methodInfo.env->GetByteArrayRegion(newArray, 0, theArrayLen, (jbyte*)dst);

        methodInfo.env->DeleteLocalRef(strArray);
        methodInfo.env->DeleteLocalRef(stringArg1);
        methodInfo.env->DeleteLocalRef(stringArg2);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
