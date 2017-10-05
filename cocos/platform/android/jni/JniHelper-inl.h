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
    template <class Ty> class ArgumentWrapper {
        Ty _arg;

    public:
        explicit ArgumentWrapper(JNIEnv*, Ty arg) : _arg(arg) { }

        inline Ty get() const { return _arg; };
    };

    template <> class ArgumentWrapper<const char*> {
        JNIEnv* _env;
        jstring _str;

        ArgumentWrapper(const ArgumentWrapper&) = delete;
        ArgumentWrapper(ArgumentWrapper&&) = delete;
        ArgumentWrapper& operator=(const ArgumentWrapper&) = delete;
        ArgumentWrapper& operator=(ArgumentWrapper&&) = delete;

    public:
        ~ArgumentWrapper() {
            _env->DeleteLocalRef(_str);
        }

        explicit ArgumentWrapper(JNIEnv* env, const char* str) : _env(env) {
            _str = StringUtils::newStringUTFJNI(_env, str != nullptr ? str : "");
        }

        explicit ArgumentWrapper(JNIEnv* env, const std::string& str) : _env(env) {
            _str = StringUtils::newStringUTFJNI(_env, str.c_str());
        }

        inline jstring get() const { return _str; };
    };

    //
    // ArgumentConverter
    //
    template <class Ty> struct ArgumentConverter { typedef Ty Type; };

    template <> struct ArgumentConverter<std::string> { typedef const char* Type; };
    template <size_t Size> struct ArgumentConverter<char [Size]> { typedef const char* Type; };
    template <size_t Size> struct ArgumentConverter<const char [Size]> { typedef const char* Type; };

    template <class Ty> struct ArgumentConverter<const Ty> :ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<Ty&> :ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<const Ty&> :ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<Ty&&> :ArgumentConverter<Ty> { };

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
    template <class Seq1, class... SeqN>
    struct SequenceConcatenator;

    template <char... Chars>
    struct SequenceConcatenator<CharSequence<Chars...> > {
        typedef CharSequence<Chars...> Result;
    };

    template <char... Chars1, char...Chars2>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...> > {
        typedef CharSequence<Chars1..., Chars2...> Result;
    };

    template <char... Chars1, char...Chars2, class ... Rest>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...>, Rest...> {
        typedef typename SequenceConcatenator<CharSequence<Chars1..., Chars2...>, Rest...>::Result Result;
    };

    //
    // SignatureImpl
    //
    template <class Ty1, class... TyN> struct SignatureImpl {
        typedef typename SequenceConcatenator<typename SignatureImpl<Ty1>::Sequence,
            typename SignatureImpl<TyN...>::Sequence>::Result Sequence;
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
    template <size_t Size> struct SignatureImpl<char [Size]> : SignatureImpl<char*> { };
    template <size_t Size> struct SignatureImpl<const char [Size]> : SignatureImpl<char*> { };

    template <> struct SignatureImpl<std::string> : SignatureImpl<char*> { };

    template <class Ty> struct SignatureImpl<std::vector<Ty> > {
        typedef typename SequenceConcatenator<CharSequence<'['>,
            typename SignatureImpl<Ty>::Sequence>::Result Sequence;
    };

    template <class Ty> struct SignatureImpl<const Ty> : SignatureImpl<Ty> { };
    template <class Ty> struct SignatureImpl<Ty&> : SignatureImpl<Ty> { };
    template <class Ty> struct SignatureImpl<const Ty&> : SignatureImpl<Ty> { };
    template <class Ty> struct SignatureImpl<Ty&&> : SignatureImpl<Ty> { };

    //
    // SignatureParser
    // parses signature during compiling time
    //
    template <class Ty> struct SignatureParser;

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
    // MethodWrapper
    // wrap CallStaticXXXMethodV GetXXXArrayElements ReleaseXXXArrayElements
    //
    template <class Ret> struct MethodWrapper;

    template <> struct MethodWrapper<bool> {
        static bool callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return JNI_TRUE == env->CallStaticBooleanMethodV(clazz, methodID, args);
        }

        typedef jbooleanArray ArrayType;
        typedef jboolean ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetBooleanArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseBooleanArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<uint8_t> {
        static uint8_t callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticByteMethodV(clazz, methodID, args);
        }
        typedef jbyteArray ArrayType;
        typedef jbyte ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetByteArrayElements(arr, isCopy);
        }

        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseByteArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<uint16_t> {
        static uint16_t callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticCharMethodV(clazz, methodID, args);
        }

        typedef jcharArray ArrayType;
        typedef jchar ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetCharArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseCharArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<short> {
        static short callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticShortMethodV(clazz, methodID, args);
        }

        typedef jshortArray ArrayType;
        typedef jshort ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetShortArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseShortArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<int> {
        static int callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticIntMethodV(clazz, methodID, args);
        }

        typedef jintArray ArrayType;
        typedef jint ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetIntArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseIntArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<long> {
        static long callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return static_cast<long>(env->CallStaticLongMethodV(clazz, methodID, args));
        }

        typedef jlongArray ArrayType;
        typedef jlong ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetLongArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseLongArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<int64_t> {
        static int64_t callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticLongMethodV(clazz, methodID, args);
        }

        typedef jlongArray ArrayType;
        typedef jlong ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetLongArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseLongArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<float> {
        static float callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticFloatMethodV(clazz, methodID, args);
        }

        typedef jfloatArray ArrayType;
        typedef jfloat ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetFloatArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseFloatArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<double> {
        static double callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticDoubleMethodV(clazz, methodID, args);
        }

        typedef jdoubleArray ArrayType;
        typedef jdouble ElementType;
        static ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            env->GetDoubleArrayElements(arr, isCopy);
        }
        static void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseDoubleArrayElements(arr, elems, mode);
        }
    };

    template <> struct MethodWrapper<void> {
        static void callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            env->CallStaticVoidMethodV(clazz, methodID, args);
        }
    };

    template <> struct MethodWrapper<std::string> {
        static std::string callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            jstring jret = (jstring)env->CallStaticObjectMethodV(clazz, methodID, args);
            LocalRefWrapper temp(env, jret);
            return StringUtils::getStringUTFCharsJNI(env, jret);
        }
    };

    template <class Ty> struct MethodWrapper<std::vector<Ty> > {
        static std::vector<Ty> callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            std::vector<Ty> ret;

            typedef MethodWrapper<Ty> ElemWrapper;
            auto jarr = (typename ElemWrapper::ArrayType)env->CallStaticObjectMethodV(clazz, methodID, args);
            JniHelperDetail::LocalRefWrapper arr(env, jarr);

            jsize len = env->GetArrayLength(jarr);
            ret.reserve(len);
            if (len > 0) {
                auto elems = ElemWrapper::getArrayElements(env, jarr, nullptr);
                for (jsize i = 0; i < len; ++i) {
                    ret.push_back(elems[i]);
                }
                ElemWrapper::releaseArrayElements(env, jarr, elems, 0);
            }

            return ret;
        }
    };

    //
    // MethodInvoker
    //
    template <class Ret> struct MethodInvoker {
        static Ret callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            Ret ret = MethodWrapper<Ret>::callStatic(env, clazz, methodID, args);
            va_end(args);
            return ret;
        }
    };

    // va_end is necessary, but it is not allowed to declare a variable of type void
    template <> struct MethodInvoker<void> {
        static void callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            MethodWrapper<void>::callStatic(env, clazz, methodID, args);
            va_end(args);
        }
    };
}

NS_CC_END

#endif // __ANDROID_JNI_HELPER_INL_H__
