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
    // ArgumentConverter
    //
    template <class T> struct ArgumentConverter { typedef T Type; };

    template <> struct ArgumentConverter<std::string> { typedef const char* Type; };
    template <size_t N> struct ArgumentConverter<char [N]> { typedef const char* Type; };
    template <size_t N> struct ArgumentConverter<const char [N]> { typedef const char* Type; };

    template <class T> struct ArgumentConverter<const T> :ArgumentConverter<T> { };
    template <class T> struct ArgumentConverter<T&> :ArgumentConverter<T> { };
    template <class T> struct ArgumentConverter<const T&> :ArgumentConverter<T> { };
    template <class T> struct ArgumentConverter<T&&> :ArgumentConverter<T> { };

    //
    // CharSequence
    //
    template <char... Chars>
    struct CharSequence { static const char value[sizeof...(Chars) + 1]; };

    template <char... Chars>
    const char CharSequence<Chars...>::value[sizeof...(Chars) + 1] = {
        Chars...,
    };

    //
    // SequenceConcatenator
    //
    template <class Seq, class... Seqs> struct SequenceConcatenator;

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
    // SignatureImpl
    //
    template <class T, class... Ts> struct SignatureImpl {
        typedef typename SequenceConcatenator<typename SignatureImpl<T>::Sequence,
            typename SignatureImpl<Ts...>::Sequence>::Result Sequence;
    };

    template <> struct SignatureImpl<bool> { typedef CharSequence<'Z'> Sequence; };
    template <> struct SignatureImpl<uint8_t> { typedef CharSequence<'B'> Sequence; };
    template <> struct SignatureImpl<uint16_t> { typedef CharSequence<'C'> Sequence; };
    template <> struct SignatureImpl<short> { typedef CharSequence<'S'> Sequence; };
    template <> struct SignatureImpl<int> { typedef CharSequence<'I'> Sequence; };
    template <> struct SignatureImpl<long> { typedef CharSequence<'J'> Sequence; };
    template <> struct SignatureImpl<int64_t> { typedef CharSequence<'J'> Sequence; };
    template <> struct SignatureImpl<float> { typedef CharSequence<'F'> Sequence; };
    template <> struct SignatureImpl<double> { typedef CharSequence<'D'> Sequence; };
    template <> struct SignatureImpl<void> { typedef CharSequence<'V'> Sequence; };
    template <> struct SignatureImpl<char*> {
        typedef CharSequence<'L', 'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g', ';'> Sequence;
    };
    template <> struct SignatureImpl<const char*> : SignatureImpl<char*> { };
    template <size_t N> struct SignatureImpl<char [N]> : SignatureImpl<char*> { };
    template <size_t N> struct SignatureImpl<const char [N]> : SignatureImpl<char*> { };

    template <> struct SignatureImpl<std::string> : SignatureImpl<char*> { };

    template <class T> struct SignatureImpl<std::vector<T> > {
        typedef typename SequenceConcatenator<CharSequence<'['>,
            typename SignatureImpl<T>::Sequence>::Result Sequence;
    };

    template <class T> struct SignatureImpl<const T> : SignatureImpl<T> { };
    template <class T> struct SignatureImpl<T&> : SignatureImpl<T> { };
    template <class T> struct SignatureImpl<const T&> : SignatureImpl<T> { };
    template <class T> struct SignatureImpl<T&&> : SignatureImpl<T> { };

    //
    // SignatureParser
    //
    template <class T> struct SignatureParser;

    template <class Ret, class... Args> struct SignatureParser<Ret (Args...)> {
        typedef typename SequenceConcatenator<CharSequence<'('>,
            typename SignatureImpl<Args...>::Sequence,
            CharSequence<')'>,
            typename SignatureImpl<Ret>::Sequence>::Result Result;
    };

    template <class Ret> struct SignatureParser<Ret ()> {
        typedef typename SequenceConcatenator<CharSequence<'(', ')'>,
            typename SignatureImpl<Ret>::Sequence>::Result Result;
    };

    //
    // MethodInvokerImpl
    //
    template <class Ret> struct MethodInvokerImpl;

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

    //
    // MethodInvoker
    //
    template <class Ret> struct MethodInvoker {
        static Ret staticInvoke(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            Ret ret = MethodInvokerImpl<Ret>::staticInvoke(env, clazz, methodID, args);
            va_end(args);
            return ret;
        }
    };

    template <> struct MethodInvoker<void> {
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
