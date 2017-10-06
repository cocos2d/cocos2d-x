/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2015 Victor Komarov
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

#include <type_traits>
#include "base/ccUTF8.h"

NS_CC_BEGIN

template <class Ty> struct CStyleArrayWrapper {
    explicit CStyleArrayWrapper(const Ty *e, size_t s) : elem(e), size(s) { }
    const Ty *elem;
    size_t size;
};

template <class Ty>
inline CStyleArrayWrapper<Ty> makeCStyleArray(const Ty *e, size_t s) {
    return CStyleArrayWrapper<Ty>(e, s);
}

struct LocalRefWrapper {
    explicit LocalRefWrapper(JNIEnv* env, jobject obj) : _env(env), _obj(obj) { }
    ~LocalRefWrapper() { _env->DeleteLocalRef(_obj); }
    inline jobject get() const { return _obj; }

private:
    LocalRefWrapper(const LocalRefWrapper&) = delete;
    LocalRefWrapper(LocalRefWrapper&&) = delete;
    LocalRefWrapper& operator=(const LocalRefWrapper&) = delete;
    LocalRefWrapper& operator=(LocalRefWrapper&&) = delete;

protected:
    JNIEnv* _env;
    jobject _obj;
};

namespace JniHelperDetail {

    //
    // CharSequence
    //
    template <char... Chars>
    struct CharSequence {
        static const char value[sizeof...(Chars) + 1];
    };

    template <char... Chars>
    const char CharSequence<Chars...>::value[sizeof...(Chars) + 1] = {
        Chars..., '\0'
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

    template <char... Chars1, char... Chars2>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...> > {
        typedef CharSequence<Chars1..., Chars2...> Result;
    };

    template <char... Chars1, char... Chars2, class... Rest>
    struct SequenceConcatenator<CharSequence<Chars1...>, CharSequence<Chars2...>, Rest...> {
        typedef typename SequenceConcatenator<CharSequence<Chars1..., Chars2...>, Rest...>::Result Result;
    };

    // IntegralConverter
    template <size_t Bytes, bool IsSigned> struct IntegralConverter;

    // jboolean: unsigned 8 bits
    template <> struct IntegralConverter<1, false> {
        typedef CharSequence<'Z'> Signature;
        typedef jbooleanArray ArrayType;
        typedef jboolean ElementType;

        static inline jboolean callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticBooleanMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetBooleanArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseBooleanArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewBooleanArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetBooleanArrayRegion(arr, start, len, buf);
        }
    };

    // jbyte: signed 8 bits
    template <> struct IntegralConverter<1, true> {
        typedef CharSequence<'B'> Signature;
        typedef jbyteArray ArrayType;
        typedef jbyte ElementType;

        static inline jbyte callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticByteMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetByteArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseByteArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewByteArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetByteArrayRegion(arr, start, len, buf);
        }
    };

    // jchar: unsigned 16 bits
    template <> struct IntegralConverter<2, false> {
        typedef CharSequence<'C'> Signature;
        typedef jcharArray ArrayType;
        typedef jchar ElementType;

        static inline jchar callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticCharMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetCharArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseCharArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewCharArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetCharArrayRegion(arr, start, len, buf);
        }
    };

    // jshort: signed 16 bits
    template <> struct IntegralConverter<2, true> {
        typedef CharSequence<'S'> Signature;
        typedef jshortArray ArrayType;
        typedef jshort ElementType;

        static inline jshort callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticShortMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetShortArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseShortArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewShortArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetShortArrayRegion(arr, start, len, buf);
        }
    };

    // jint signed 32 bits
    // unsigned 32 bits not defined in jni
    template <bool IsSigned> struct IntegralConverter<4, IsSigned> {
        typedef CharSequence<'I'> Signature;
        typedef jintArray ArrayType;
        typedef jint ElementType;

        static inline jint callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticIntMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetIntArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseIntArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewIntArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetIntArrayRegion(arr, start, len, buf);
        }
    };

    // jlong: signed 64 bits
    // unsigned 64 bits not defined in jni
    template <bool IsSigned> struct IntegralConverter<8, IsSigned> {
        typedef CharSequence<'J'> Signature;
        typedef jlongArray ArrayType;
        typedef jlong ElementType;

        static inline jlong callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticLongMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetLongArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseLongArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewLongArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetLongArrayRegion(arr, start, len, buf);
        }
    };

    // FloatConverter
    template <size_t Bytes> struct FloatConverter;

    // jfloat: 32-bit IEEE 754
    template <> struct FloatConverter<4> {
        typedef CharSequence<'F'> Signature;
        typedef jfloatArray ArrayType;
        typedef jfloat ElementType;

        static inline jfloat callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticFloatMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetFloatArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseFloatArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewFloatArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetFloatArrayRegion(arr, start, len, buf);
        }
    };

    // jdouble: 64-bit IEEE 754
    template <> struct FloatConverter<8> {
        typedef CharSequence<'D'> Signature;
        typedef jdoubleArray ArrayType;
        typedef jdouble ElementType;

        static inline jdouble callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return env->CallStaticDoubleMethodV(clazz, methodID, args);
        }
        static inline ElementType* getArrayElements(JNIEnv* env, ArrayType arr, jboolean* isCopy) {
            return env->GetDoubleArrayElements(arr, isCopy);
        }
        static inline void releaseArrayElements(JNIEnv* env, ArrayType arr, ElementType* elems, jint mode) {
            env->ReleaseDoubleArrayElements(arr, elems, mode);
        }
        static inline ArrayType newArray(JNIEnv* env, jsize length) {
            return env->NewDoubleArray(length);
        }
        static inline void setArrayRegion(JNIEnv* env, ArrayType arr, jsize start, jsize len, const ElementType* buf) {
            env->SetDoubleArrayRegion(arr, start, len, buf);
        }
    };

    //
    // TypeConverter
    // typedefs Signature ArrayType ElementType;
    // wraps CallStaticXXXMethodV GetXXXArrayElements ReleaseXXXArrayElements newXXXArray SetXXXArrayRegion
    //
    template <class Ret> struct TypeConverter;

    template <> struct TypeConverter<void> {
        typedef CharSequence<'V'> Signature;

        static inline void callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            env->CallStaticVoidMethodV(clazz, methodID, args);
        }
    };

    template <> struct TypeConverter<bool> : IntegralConverter<1, false> {
        static inline bool callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            return JNI_TRUE == env->CallStaticBooleanMethodV(clazz, methodID, args);
        }
    };
    template <> struct TypeConverter<char> : IntegralConverter<1, true> { };
    template <> struct TypeConverter<signed char> : IntegralConverter<1, true> { };
    template <> struct TypeConverter<unsigned char> : IntegralConverter<1, true> { };
    template <> struct TypeConverter<signed short> : IntegralConverter<sizeof(signed short), true> { };
    template <> struct TypeConverter<unsigned short> : IntegralConverter<sizeof(unsigned short), false> { };
    template <> struct TypeConverter<signed int> : IntegralConverter<sizeof(signed int), true> { };
    template <> struct TypeConverter<unsigned int> : IntegralConverter<sizeof(unsigned int), false> { };
    template <> struct TypeConverter<signed long> : IntegralConverter<sizeof(signed long), true> { };
    template <> struct TypeConverter<unsigned long> : IntegralConverter<sizeof(unsigned int), false> { };
    template <> struct TypeConverter<int64_t> : IntegralConverter<sizeof(int64_t), true> { };
    template <> struct TypeConverter<uint64_t> : IntegralConverter<sizeof(uint64_t), false>{};
    template <> struct TypeConverter<float> : FloatConverter<sizeof(float)> { };
    template <> struct TypeConverter<double> : FloatConverter<sizeof(double)> { };

    template <> struct TypeConverter<char*> {
        typedef CharSequence<'L', 'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g', ';'> Signature;
    };
    template <> struct TypeConverter<const char*> : TypeConverter<char*> { };
    template <size_t Size> struct TypeConverter<char [Size]> : TypeConverter<char*> { };
    template <size_t Size> struct TypeConverter<const char [Size]> : TypeConverter<char*> { };

    template <> struct TypeConverter<std::string> {
        typedef CharSequence<'L', 'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g', ';'> Signature;

        static std::string callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            LocalRefWrapper jret(env, env->CallStaticObjectMethodV(clazz, methodID, args));
            return StringUtils::getStringUTFCharsJNI(env, (jstring)jret.get());
        }
    };

    template <class Ty> struct TypeConverter<CStyleArrayWrapper<Ty> > {
        typedef typename SequenceConcatenator<CharSequence<'['>,
            typename TypeConverter<Ty>::Signature>::Result Signature;
    };

    template <class Ty> struct TypeConverter<std::vector<Ty> > : TypeConverter<CStyleArrayWrapper<Ty> > {
        static std::vector<Ty> callStaticMethodV(JNIEnv* env, jclass clazz, jmethodID methodID, va_list args) {
            typedef TypeConverter<Ty> ElemTypeWrapper;
            typedef typename ElemTypeWrapper::ArrayType ArrayType;
            LocalRefWrapper jarr(env, env->CallStaticObjectMethodV(clazz, methodID, args));
            jsize len = env->GetArrayLength((ArrayType)jarr.get());
            std::vector<Ty> ret(len);
            if (len > 0) {
                auto elems = ElemTypeWrapper::getArrayElements(env, (ArrayType)jarr.get(), nullptr);
                for (jsize i = 0; i < len; ++i) ret.push_back(elems[i]);
                ElemTypeWrapper::releaseArrayElements(env, (ArrayType)jarr.get(), elems, 0);
            }
            return ret;
        }
    };

    //
    // SignatureParser
    // parses signature during compiling time
    //
    template <class Ty> struct SignatureParser;

    template <class Ret, class... Args> struct SignatureParser<Ret (Args...)> {
        typedef typename SequenceConcatenator<CharSequence<'('>,
            typename TypeConverter<typename std::remove_reference<typename std::remove_const<Args>::type>::type>::Signature...,
            CharSequence<')'>,
            typename TypeConverter<Ret>::Signature>::Result Result;
    };

    //
    // MethodInvoker
    //
    template <class Ret> struct MethodInvoker {
        static Ret callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            Ret ret = TypeConverter<Ret>::callStaticMethodV(env, clazz, methodID, args);
            va_end(args);
            return ret;
        }
    };

    // specialization for void, because va_end is necessary, but it is not allowed to declare a variable of type void
    template <> struct MethodInvoker<void> {
        static void callStatic(JNIEnv* env, jclass clazz, jmethodID methodID, ...) {
            va_list args;
            va_start(args, methodID);
            TypeConverter<void>::callStaticMethodV(env, clazz, methodID, args);
            va_end(args);
        }
    };

    //
    // ArgumentWrapper
    //
    template <class Ty> class ArgumentWrapper {
        static_assert(std::is_arithmetic<Ty>::value, "ArgumentWrapper<Ty> : only arithmetic type supported");
        Ty _arg;

    public:
        explicit ArgumentWrapper(JNIEnv*, Ty arg) : _arg(arg) { }
        inline Ty get() const { return _arg; };
    };

    template <> class ArgumentWrapper<const char*> : LocalRefWrapper {
        ArgumentWrapper(const ArgumentWrapper&) = delete;
        ArgumentWrapper(ArgumentWrapper&&) = delete;
        ArgumentWrapper& operator=(const ArgumentWrapper&) = delete;
        ArgumentWrapper& operator=(ArgumentWrapper&&) = delete;

    public:
        explicit ArgumentWrapper(JNIEnv* env, const char* str)
            : LocalRefWrapper(env, StringUtils::newStringUTFJNI(env, str != nullptr ? str : "")) {
        }

        explicit ArgumentWrapper(JNIEnv* env, const std::string& str)
            : LocalRefWrapper(env, StringUtils::newStringUTFJNI(env, str.c_str())) {
        }

        inline jstring get() const { return (jstring)_obj; };
    };

    // convertArray, in case of sizeof(Ty) == sizeof(ElementType)
    template <class Ty>
    static typename std::enable_if<sizeof(Ty) == sizeof(typename TypeConverter<Ty>::ElementType), typename TypeConverter<Ty>::ArrayType>::type
        convertArray(JNIEnv* env, const Ty *elem, size_t size) {
        typedef typename TypeConverter<Ty>::ArrayType ArrayType;
        typedef typename TypeConverter<Ty>::ElementType ElementType;
        ArrayType ret = TypeConverter<ElementType>::newArray(env, size);
        TypeConverter<ElementType>::setArrayRegion(env, ret, 0, size, reinterpret_cast<const ElementType*>(elem));
        return ret;
    }

    // convertArray, in case of sizeof(Ty) != sizeof(ElementType)
    template <class Ty>
    static typename std::enable_if<sizeof(Ty) != sizeof(typename TypeConverter<Ty>::ElementType), typename TypeConverter<Ty>::ArrayType>::type
        convertArray(JNIEnv* env, const Ty *elem, size_t size) {
        typedef typename TypeConverter<Ty>::ArrayType ArrayType;
        typedef typename TypeConverter<Ty>::ElementType ElementType;
        ArrayType ret = TypeConverter<ElementType>::newArray(env, size);
        std::vector<ElementType> temp;
        temp.resize(size);
        for (size_t i = 0; i < size; ++i) { temp[i] = static_cast<ElementType>(elem[i]); }
        TypeConverter<ElementType>::setArrayRegion(env, ret, 0, size, temp.data());
        return ret;
    }

    template <class Ty> class ArgumentWrapper<std::vector<Ty> > : LocalRefWrapper {
        ArgumentWrapper(const ArgumentWrapper&) = delete;
        ArgumentWrapper(ArgumentWrapper&&) = delete;
        ArgumentWrapper& operator=(const ArgumentWrapper&) = delete;
        ArgumentWrapper& operator=(ArgumentWrapper&&) = delete;

    public:
        static_assert(std::is_arithmetic<Ty>::value, "ArgumentWrapper<std::vector<Ty> > : only arithmetic elements supported");

        typedef typename TypeConverter<Ty>::ArrayType ArrayType;
        typedef typename TypeConverter<Ty>::ElementType ElementType;

        explicit ArgumentWrapper(JNIEnv* env, const std::vector<Ty>& vec)
            : LocalRefWrapper(env, convertArray(env, vec.data(), vec.size())) {
        }
        explicit ArgumentWrapper(JNIEnv* env, const CStyleArrayWrapper<Ty>& arr)
            : LocalRefWrapper(env, convertArray(env, arr.elem, arr.size)) {
        }
        inline ArrayType get() const { return (ArrayType)_obj; };
    };

    //
    // ArgumentConverter
    //
    template <class Ty> struct ArgumentConverter { typedef Ty Type; };

    template <> struct ArgumentConverter<std::string> { typedef const char* Type; };
    template <size_t Size> struct ArgumentConverter<char [Size]> { typedef const char* Type; };
    template <size_t Size> struct ArgumentConverter<const char [Size]> { typedef const char* Type; };

    template <class Ty> struct ArgumentConverter<CStyleArrayWrapper<Ty> > : ArgumentConverter<std::vector<Ty> > { };

    template <class Ty> struct ArgumentConverter<const Ty> : ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<Ty&> : ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<const Ty&> : ArgumentConverter<Ty> { };
    template <class Ty> struct ArgumentConverter<Ty&&> : ArgumentConverter<Ty> { };
}

NS_CC_END

#endif // __ANDROID_JNI_HELPER_INL_H__
