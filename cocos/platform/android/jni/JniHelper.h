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
#include "JniHelper-inl.h"

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

    template <typename Ret, typename... Args>
    static Ret callStaticMethod(const char* className, const char* methodName, const Args& ...args) {
        typedef typename JniHelperDetail::SignatureGetter<Ret (Args...)>::SignatureSequence SignatureSequence;
        const char* signature = SignatureSequence::value;

        JniMethodInfo t;
        if (getStaticMethodInfo(t, className, methodName, signature)) {
            JniHelperDetail::LocalRefWrapper clazz(t.env, t.classID);
            return JniHelperDetail::MethodInvoker<Ret>::staticInvoke(t.env, t.classID, t.methodID, JniHelperDetail::ArgumentWrapper<Args>(t.env, args).get()...);
        }
        else {
            reportError(className, methodName, signature);
        }
        return Ret();
    }

    template <typename... Args>
    static float* callStaticFloatArrayMethod(const char* className, const char* methodName, const Args& ...args) {
        typedef typename JniHelperDetail::SignatureGetter<std::vector<float> (Args...)>::SignatureSequence SignatureSequence;
        const char* signature = SignatureSequence::value;

        static float ret[32];
        JniMethodInfo t;
        if (getStaticMethodInfo(t, className, methodName, signature)) {
            JniHelperDetail::LocalRefWrapper clazz(t.env, t.classID);
            jfloatArray array = (jfloatArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, JniHelperDetail::ArgumentWrapper<Args>(t.env, args).get()...);
            JniHelperDetail::LocalRefWrapper arr(t.env, array);
            jsize len = t.env->GetArrayLength(array);
            if (len <= 32) {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                if (elems) {
                    memcpy(ret, elems, sizeof(float) * len);
                    t.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            return &ret[0];
        } else {
            reportError(className, methodName, signature);
        }
        return nullptr;
    }

    template <typename... Args>
    static Vec3 callStaticVec3Method(const char* className, const char* methodName, const Args& ...args) {
        typedef typename JniHelperDetail::SignatureGetter<std::vector<float> (Args...)>::SignatureSequence SignatureSequence;
        const char* signature = SignatureSequence::value;

        Vec3 ret;
        JniMethodInfo t;
        if (getStaticMethodInfo(t, className, methodName, signature)) {
            JniHelperDetail::LocalRefWrapper clazz(t.env, t.classID);
            jfloatArray array = (jfloatArray) t.env->CallStaticObjectMethod(t.classID, t.methodID, JniHelperDetail::ArgumentWrapper<Args>(t.env, args).get()...);
            JniHelperDetail::LocalRefWrapper arr(t.env, array);
            jsize len = t.env->GetArrayLength(array);
            if (len == 3) {
                jfloat* elems = t.env->GetFloatArrayElements(array, 0);
                ret.x = elems[0];
                ret.y = elems[1];
                ret.z = elems[2];
                t.env->ReleaseFloatArrayElements(array, elems, 0);
            }
        } else {
            reportError(className, methodName, signature);
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

    static void reportError(const char* className, const char* methodName, const char* signature);
};

NS_CC_END

#endif // __ANDROID_JNI_HELPER_H__
