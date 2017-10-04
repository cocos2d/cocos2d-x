/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2017 Jeff Wang

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
#ifndef __ANDROID_JNI_HELPER_INL_H__
#define __ANDROID_JNI_HELPER_INL_H__

#include "base/ccUTF8.h"

NS_CC_BEGIN

namespace JniHelperDetail {
    struct LocalRefWrapper {
        explicit LocalRefWrapper(JNIEnv* env, jobject obj) : _env(env), _obj(obj) { }
        ~LocalRefWrapper() { _env->DeleteLocalRef(_obj); }

    private:
        LocalRefWrapper(const LocalRefWrapper&) = delete;
        LocalRefWrapper(LocalRefWrapper&&) = delete;
        LocalRefWrapper& operator=(const LocalRefWrapper&) = delete;
        LocalRefWrapper& operator=(LocalRefWrapper&&) = delete;

        JNIEnv* _env;
        jobject _obj;
    };

    //
    // ArgumentWrapper
    //
    template <class T> class ArgumentWrapper {
        T _arg;
    public:
        explicit ArgumentWrapper(JNIEnv*, T arg) : _arg(arg) { }
        inline T get() const { return _arg; };
    };

    template <> class ArgumentWrapper<const char*> {
        JNIEnv* _env;
        jstring _str;

        ArgumentWrapper(const ArgumentWrapper&) = delete;
        ArgumentWrapper(ArgumentWrapper&&) = delete;
        ArgumentWrapper& operator=(const ArgumentWrapper&) = delete;
        ArgumentWrapper& operator=(ArgumentWrapper&&) = delete;

        inline void set(const char *str) {
            _str = StringUtils::newStringUTFJNI(_env, str ? str : "");
        }

    public:
        ~ArgumentWrapper() { _env->DeleteLocalRef(_str); }
        explicit ArgumentWrapper(JNIEnv* env, const char* str) : _env(env) { set(str); }
        explicit ArgumentWrapper(JNIEnv* env, const std::string& str) : _env(env) { set(str.c_str()); }

        inline jstring get() const { return _str; };
    };

    //
    // ArgumentTypeConverter
    //
    template <class T> struct ArgumentTypeConverter {
        typedef T Type;
    };

    template <> struct ArgumentTypeConverter<std::string> {
        typedef const char* Type;
    };

    template <size_t N> struct ArgumentTypeConverter<char [N]> : ArgumentTypeConverter<std::string> { };
    template <size_t N> struct ArgumentTypeConverter<const char [N]> : ArgumentTypeConverter<std::string> { };

    template <class T> struct ArgumentTypeConverter<const T> :ArgumentTypeConverter<T> { };
    template <class T> struct ArgumentTypeConverter<T&> :ArgumentTypeConverter<T> { };
    template <class T> struct ArgumentTypeConverter<const T&> :ArgumentTypeConverter<T> { };
    template <class T> struct ArgumentTypeConverter<T&&> :ArgumentTypeConverter<T> { };

    //
    // CharSequence
    //
    template <char... Chars>
    struct CharSequence {
        static const char value[sizeof...(Chars) + 1];
    };

    template <char... Chars>
    const char CharSequence<Chars...>::value[sizeof...(Chars) + 1] = {
        Chars...,
    };

    //
    // SequenceConcatenator
    //
    template <class Seq, class... Seqs>
    struct SequenceConcatenator;

    template <char... Chars>
    struct SequenceConcatenator<CharSequence<Chars...> > {
        typedef CharSequence<Chars...> Result;
    };

    template <char... Chars1, char...Chars2>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...> > {
        typedef CharSequence<Chars1..., Chars2...> Result;
    };

    template <char... Chars1, char...Chars2, class ... Seq>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...>, Seq...> {
        typedef typename SequenceConcatenator<CharSequence<Chars1..., Chars2...>, Seq...>::Result Result;
    };

    //
    // JNISignature
    //
    template <class T, class... Ts> struct JNISignature {
        typedef typename SequenceConcatenator<typename JNISignature<T>::Sequence, typename JNISignature<Ts...>::Sequence>::Result Sequence;
    };

    template <> struct JNISignature<bool> {
        typedef CharSequence<'Z'> Sequence;
    };

    template <> struct JNISignature<uint8_t> {
        typedef CharSequence<'B'> Sequence;
    };

    template <> struct JNISignature<uint16_t> {
        typedef CharSequence<'C'> Sequence;
    };

    template <> struct JNISignature<short> {
        typedef CharSequence<'S'> Sequence;
    };

    template <> struct JNISignature<int> {
        typedef CharSequence<'I'> Sequence;
    };

    template <> struct JNISignature<long> {
        typedef CharSequence<'J'> Sequence;
    };

    template <> struct JNISignature<int64_t> {
        typedef CharSequence<'J'> Sequence;
    };

    template <> struct JNISignature<float> {
        typedef CharSequence<'F'> Sequence;
    };

    template <> struct JNISignature<double> {
        typedef CharSequence<'D'> Sequence;
    };

    template <> struct JNISignature<void> {
        typedef CharSequence<'V'> Sequence;
    };

    template <> struct JNISignature<char*> {
        typedef CharSequence<'L', 'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g', ';'> Sequence;
    };
    template <> struct JNISignature<const char*> : JNISignature<char*> { };
    template <size_t N> struct JNISignature<char [N]> : JNISignature<char*> { };
    template <size_t N> struct JNISignature<const char [N]> : JNISignature<char*> { };

    template <> struct JNISignature<std::string> : JNISignature<char*> { };

    template <class T> struct JNISignature<std::vector<T> > {
        typedef typename SequenceConcatenator<CharSequence<'['>, typename JNISignature<T>::Sequence>::Result Sequence;
    };

    template <class T> struct JNISignature<const T> : JNISignature<T> { };
    template <class T> struct JNISignature<T&> : JNISignature<T> { };
    template <class T> struct JNISignature<const T&> : JNISignature<T> { };
    template <class T> struct JNISignature<T&&> : JNISignature<T> { };

    //
    // SignatureGetter
    //
    template <class T> struct SignatureGetter;

    template <class Ret, class... Args> struct SignatureGetter<Ret (Args...)> {
        typedef typename SequenceConcatenator<CharSequence<'('>,
            typename JNISignature<Args...>::Sequence,
            CharSequence<')'>,
            typename JNISignature<Ret>::Sequence>::Result SignatureSequence;
    };

    template<class Ret> struct SignatureGetter<Ret ()> {
        typedef typename SequenceConcatenator<CharSequence<'(', ')'>,
            typename JNISignature<Ret>::Sequence>::Result SignatureSequence;
    };

    //
    // MethodInvokerImpl
    //
    template <class T> struct MethodInvokerImpl { };

    template <> struct MethodInvokerImpl<bool> {
        static bool staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return JNI_TRUE == env->CallStaticBooleanMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<uint8_t> {
        static uint8_t staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticByteMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<uint16_t> {
        static uint16_t staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticCharMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<short> {
        static short staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticShortMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<int> {
        static int staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticIntMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<long> {
        static long staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return static_cast<long>(env->CallStaticLongMethodV(clazz, methodID, args));
        }
    };

    template <> struct MethodInvokerImpl<int64_t> {
        static int64_t staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticLongMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<float> {
        static float staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticFloatMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<double> {
        static double staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticDoubleMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<void> {
        static void staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            env->CallStaticVoidMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodInvokerImpl<std::string> {
        static std::string staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            jstring jret = (jstring)env->CallStaticObjectMethodV(clazz, methodID, args);
            LocalRefWrapper temp(env, jret);
            return StringUtils::getStringUTFCharsJNI(env, jret);
        }
    };

    template <> struct MethodInvokerImpl<const char *> : MethodInvokerImpl<std::string> { };

    //
    // MethodInvoker
    //
    template <class Ret>
    struct MethodInvoker {
        static Ret staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            Ret ret = MethodInvokerImpl<Ret>::staticInvoke(env, clazz, methodID, args);
            va_end(args);
            return ret;
        }
    };

    template <>
    struct MethodInvoker<void> {
        static void staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            MethodInvokerImpl<void>::staticInvoke(env, clazz, methodID, args);
            va_end(args);
        }
    };
}

NS_CC_END

#endif // __ANDROID_JNI_HELPER_INL_H__
