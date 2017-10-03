/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include <vector>
#include <functional>
#include "platform/CCPlatformMacros.h"
#include "math/Vec3.h"

NS_CC_BEGIN

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

class CC_DLL JniHelper
{
public:
    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static jobject getActivity();

    static bool setClassLoaderFrom(jobject activityInstance);
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode);
    static bool getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode);

    static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;
    static std::function<void()> classloaderCallback;

    template <typename... Ts>
    static void callStaticVoidMethod(const char* className, 
                                     const char* methodName, 
                                     const Ts& ...xs) {
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            t.env->CallStaticVoidMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
    }

    template <typename... Ts>
    static bool callStaticBooleanMethod(const char* className, 
                                        const char* methodName, 
                                        const Ts& ...xs) {
        jboolean jret = JNI_FALSE;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            jret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return (jret == JNI_TRUE);
    }

    template <typename... Ts>
    static int callStaticIntMethod(const char* className, 
                                   const char* methodName, 
                                   const Ts& ...xs) {
        jint ret = 0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")I";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            ret = t.env->CallStaticIntMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return ret;
    }

    template <typename... Ts>
    static float callStaticFloatMethod(const char* className, 
                                       const char* methodName, 
                                       const Ts& ...xs) {
        jfloat ret = 0.0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")F";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return ret;
    }

    template <typename... Ts>
    static float* callStaticFloatArrayMethod(const char* className, 
                                       const char* methodName, 
                                       const Ts& ...xs) {
        static float ret[32];
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")[F";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            jfloatArray array = (jfloatArray) t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len <= 32) {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                if (elems) {
                    memcpy(ret, elems, sizeof(float) * len);
                    t.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
            return &ret[0];
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return nullptr;
    }

    template <typename... Ts>
    static Vec3 callStaticVec3Method(const char* className, 
                                       const char* methodName, 
                                       const Ts& ...xs) {
        Vec3 ret;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")[F";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            jfloatArray array = (jfloatArray) t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            jsize len = t.env->GetArrayLength(array);
            if (len == 3) {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                ret.x = elems[0];
                ret.y = elems[1];
                ret.z = elems[2];
                t.env->ReleaseFloatArrayElements(array, elems, 0);
            }
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return ret;
    }

    template <typename... Ts>
    static double callStaticDoubleMethod(const char* className, 
                                         const char* methodName, 
                                         const Ts& ...xs) {
        jdouble ret = 0.0;
        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")D";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return ret;
    }

    template <typename... Ts>
    static std::string callStaticStringMethod(const char* className, 
                                              const char* methodName, 
                                              const Ts& ...xs) {
        std::string ret;

        cocos2d::JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
        if (cocos2d::JniHelper::getStaticMethodInfo(t, className, methodName, signature.c_str())) {
            std::vector<jobject> localRefs;
            localRefs.reserve(sizeof...(xs));
            jstring jret = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t.env, xs)...);
            ret = cocos2d::JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env, localRefs);
        } else {
            reportError(className, methodName, signature.c_str());
        }
        return ret;
    }

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);

    static JavaVM* _psJavaVM;
    
    static jobject _activity;

    static jstring convert(std::vector<jobject>& localRefs, JNIEnv* env, const char* x);

    static jstring convert(std::vector<jobject>& localRefs, JNIEnv* env, const std::string& x);

    template <typename T>
    static T convert(std::vector<jobject>& localRefs, JNIEnv* env, const T& x) {
        return x;
    }

    static void deleteLocalRefs(JNIEnv* env, std::vector<jobject>& localRefs);

    static std::string getJNISignature() {
        return "";
    }

    static std::string getJNISignature(bool) {
        return "Z";
    }

    static std::string getJNISignature(char) {
        return "C";
    }

    static std::string getJNISignature(short) {
        return "S";
    }

    static std::string getJNISignature(int) {
        return "I";
    }

    static std::string getJNISignature(long) {
        return "J";
    }

    static std::string getJNISignature(float) {
        return "F";
    }

    static std::string getJNISignature(double) {
        return "D";
    }

    static std::string getJNISignature(const char*) {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(const std::string&) {
        return "Ljava/lang/String;";
    }

    template <typename T>
    static std::string getJNISignature(const T& x) {
        // This template should never be instantiated
        static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }

    template <typename T, typename... Ts>
    static std::string getJNISignature(const T& x, const Ts& ...xs) {
        return getJNISignature(x) + getJNISignature(xs...);
    }

    static void reportError(const char* className, const char* methodName, const char* signature);
};

NS_CC_END

#endif // __ANDROID_JNI_HELPER_H__
