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
        typedef typename JniHelperDetail::SignatureParser<Ret (Args...)>::Result SignatureSequence;
        const char* signature = SignatureSequence::value;

        JniMethodInfo t;
        if (getStaticMethodInfo(t, className, methodName, signature)) {
            JniHelperDetail::LocalRefWrapper clazz(t.env, t.classID);
            return JniHelperDetail::MethodInvoker<Ret>::callStatic(t.env, t.classID, t.methodID,
                JniHelperDetail::ArgumentWrapper<typename JniHelperDetail::ArgumentConverter<Args>::Type>(t.env, args).get()...);
        }
        else {
            reportError(className, methodName, signature);
            return Ret();
        }
    }

    template <typename... Args>
    static Vec3 callStaticVec3Method(const char* className, const char* methodName, const Args& ...args) {
        typedef typename JniHelperDetail::SignatureParser<std::vector<float> (Args...)>::Result SignatureSequence;
        const char* signature = SignatureSequence::value;

        Vec3 ret;
        JniMethodInfo t;
        if (getStaticMethodInfo(t, className, methodName, signature)) {
            JniHelperDetail::LocalRefWrapper clazz(t.env, t.classID);
            std::vector<float> arr = JniHelperDetail::MethodInvoker<std::vector<float> >::callStatic(t.env, t.classID, t.methodID,
                JniHelperDetail::ArgumentWrapper<typename JniHelperDetail::ArgumentConverter<Args>::Type>(t.env, args).get()...);
            if (arr.size() == 3) {
                ret.x = arr[0];
                ret.y = arr[1];
                ret.z = arr[2];
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
