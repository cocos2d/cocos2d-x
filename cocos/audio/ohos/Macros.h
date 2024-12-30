/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011 Zynga Inc.
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <cstdint> // To include uint8_t, uint16_t and so on.

#include <cassert>
#define CC_ASSERT(cond) assert(cond)

#define CC_AUDIO_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
#if defined(CC_STATIC)
#define CC_DLL
#else
#if defined(_USRDLL)
#define CC_DLL __declspec(dllexport)
#else /* use a DLL library */
#define CC_DLL __declspec(dllimport)
#endif
#endif
#else
#define CC_DLL
#endif

/** @def CC_DEGREES_TO_RADIANS
 converts degrees to radians
 */
#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__)*0.01745329252f) // PI / 180

/** @def CC_RADIANS_TO_DEGREES
 converts radians to degrees
 */
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__)*57.29577951f) // PI * 180

#ifndef FLT_EPSILON
#define FLT_EPSILON 1.192092896e-07F
#endif // FLT_EPSILON

/**
Helper macros which converts 4-byte little/big endian
integral number to the machine native number representation

It should work same as apples CFSwapInt32LittleToHost(..)
*/

/// when define returns true it means that our architecture uses big endian
#define CC_HOST_IS_BIG_ENDIAN           (bool)(*(unsigned short *)"\0\xff" < 0x100)
#define CC_SWAP32(i)                    ((i & 0x000000ff) << 24 | (i & 0x0000ff00) << 8 | (i & 0x00ff0000) >> 8 | (i & 0xff000000) >> 24)
#define CC_SWAP16(i)                    ((i & 0x00ff) << 8 | (i & 0xff00) >> 8)
#define CC_SWAP_INT32_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true) ? CC_SWAP32(i) : (i))
#define CC_SWAP_INT16_LITTLE_TO_HOST(i) ((CC_HOST_IS_BIG_ENDIAN == true) ? CC_SWAP16(i) : (i))
#define CC_SWAP_INT32_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true) ? (i) : CC_SWAP32(i))
#define CC_SWAP_INT16_BIG_TO_HOST(i)    ((CC_HOST_IS_BIG_ENDIAN == true) ? (i) : CC_SWAP16(i))

// new callbacks based on C++11
#define CC_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define CC_CALLBACK_2(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CC_CALLBACK_3(__selector__, __target__, ...) std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

// Generic macros

#define CC_BREAK_IF(cond) \
    if (cond) break

/** @def CC_DEPRECATED_ATTRIBUTE
* Only certain compilers support __attribute__((deprecated)).
*/
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define CC_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define CC_DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#define CC_DEPRECATED_ATTRIBUTE
#endif

/** @def CC_DEPRECATED(...)
* Macro to mark things deprecated as of a particular version
* can be used with arbitrary parameters which are thrown away.
* e.g. CC_DEPRECATED(4.0) or CC_DEPRECATED(4.0, "not going to need this anymore") etc.
*/
#define CC_DEPRECATED(...) CC_DEPRECATED_ATTRIBUTE

#ifdef __GNUC__
#define CC_UNUSED __attribute__((unused))
#else
#define CC_UNUSED
#endif

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/** @def CC_FORMAT_PRINTF(formatPos, argPos)
 * Only certain compiler support __attribute__((format))
 *
 * @param formatPos 1-based position of format string argument.
 * @param argPos    1-based position of first format-dependent argument.
 */
#if defined(__GNUC__) && (__GNUC__ >= 4)
#define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
#if __has_attribute(format)
        #define CC_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
    #else
        #define CC_FORMAT_PRINTF(formatPos, argPos)
    #endif // __has_attribute(format)
#else
#define CC_FORMAT_PRINTF(formatPos, argPos)
#endif

// Initial compiler-related stuff to set.
#define CC_COMPILER_MSVC  1
#define CC_COMPILER_CLANG 2
#define CC_COMPILER_GNUC  3

// CPU Architecture
#define CC_CPU_UNKNOWN 0
#define CC_CPU_X86     1
#define CC_CPU_PPC     2
#define CC_CPU_ARM     3
#define CC_CPU_MIPS    4

// 32-bits or 64-bits CPU
#define CC_CPU_ARCH_32 1
#define CC_CPU_ARCH_64 2

// Mode
#define CC_MODE_DEBUG   1
#define CC_MODE_RELEASE 2

// Compiler type and version recognition
#if defined(_MSC_VER)
#define CC_COMPILER CC_COMPILER_MSVC
#elif defined(__clang__)
#define CC_COMPILER CC_COMPILER_CLANG
#elif defined(__GNUC__)
#define CC_COMPILER CC_COMPILER_GNUC
#else
#error "Unknown compiler. Abort!"
#endif

#if INTPTR_MAX == INT32_MAX
#define CC_CPU_ARCH CC_CPU_ARCH_32
#else
#define CC_CPU_ARCH CC_CPU_ARCH_64
#endif

#if defined(__arm64__) || defined(__aarch64__)
#define CC_ARCH_ARM64 1
#else
#define CC_ARCH_ARM64 0
#endif

// CC_HAS_ARM64_FP16 set to 1 if the architecture provides an IEEE compliant ARM fp16 type
#if CC_ARCH_ARM64
#ifndef CC_HAS_ARM64_FP16
        #if defined(__ARM_FP16_FORMAT_IEEE)
            #define CC_HAS_ARM64_FP16 1
        #else
            #define CC_HAS_ARM64_FP16 0
        #endif
    #endif
#endif

// CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC set to 1 if the architecture supports Neon vector intrinsics for fp16.
#if CC_ARCH_ARM64
#ifndef CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC
        #if defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)
            #define CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC 1
        #else
            #define CC_HAS_ARM64_FP16_VECTOR_ARITHMETIC 0
        #endif
    #endif
#endif

// CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC set to 1 if the architecture supports Neon scalar intrinsics for fp16.
#if CC_ARCH_ARM64
#ifndef CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC
        #if defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
            #define CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC 1
        #else
            #define CC_HAS_ARM64_FP16_SCALAR_ARITHMETIC 0
        #endif
    #endif
#endif

// Disable MSVC warning
#if (CC_COMPILER == CC_COMPILER_MSVC)
#pragma warning(disable : 4251 4275 4819)
    #ifndef _CRT_SECURE_NO_DEPRECATE
        #define _CRT_SECURE_NO_DEPRECATE
    #endif
    #ifndef _SCL_SECURE_NO_DEPRECATE
        #define _SCL_SECURE_NO_DEPRECATE
    #endif
#endif

#define CC_CACHELINE_SIZE 64

#if (CC_COMPILER == CC_COMPILER_MSVC)
// MSVC ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS() \
        __pragma(warning(push, 0))

    #define CC_ENABLE_WARNINGS() \
        __pragma(warning(pop))
#elif (CC_COMPILER == CC_COMPILER_GNUC)
// GCC ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS()                               \
        _Pragma("GCC diagnostic push")                          \
            _Pragma("GCC diagnostic ignored \"-Wall\"")         \
                _Pragma("clang diagnostic ignored \"-Wextra\"") \
                    _Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

    #define CC_ENABLE_WARNINGS() \
        _Pragma("GCC diagnostic pop")
#elif (CC_COMPILER == CC_COMPILER_CLANG)
// CLANG ENABLE/DISABLE WARNING DEFINITION
    #define CC_DISABLE_WARNINGS()                               \
        _Pragma("clang diagnostic push")                        \
            _Pragma("clang diagnostic ignored \"-Wall\"")       \
                _Pragma("clang diagnostic ignored \"-Wextra\"") \
                    _Pragma("clang diagnostic ignored \"-Wtautological-compare\"")

    #define CC_ENABLE_WARNINGS() \
        _Pragma("clang diagnostic pop")
#endif

#define CC_DISALLOW_ASSIGN(TypeName)                \
    TypeName &operator=(const TypeName &) = delete; \
    TypeName &operator=(TypeName &&) = delete;

#define CC_DISALLOW_COPY_MOVE_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete;       \
    TypeName(TypeName &&) = delete;            \
    CC_DISALLOW_ASSIGN(TypeName)

#if (CC_COMPILER == CC_COMPILER_MSVC)
#define CC_ALIGN(N)        __declspec(align(N))
    #define CC_CACHE_ALIGN     __declspec(align(CC_CACHELINE_SIZE))
    #define CC_PACKED_ALIGN(N) __declspec(align(N))

    #define CC_ALIGNED_DECL(type, var, alignment) __declspec(align(alignment)) type var

    #define CC_READ_COMPILER_BARRIER()  _ReadBarrier()
    #define CC_WRITE_COMPILER_BARRIER() _WriteBarrier()
    #define CC_COMPILER_BARRIER()       _ReadWriteBarrier()

    #define CC_READ_MEMORY_BARRIER()  MemoryBarrier()
    #define CC_WRITE_MEMORY_BARRIER() MemoryBarrier()
    #define CC_MEMORY_BARRIER()       MemoryBarrier()

    #define CC_CPU_READ_MEMORY_BARRIER() \
        do {                             \
            __asm { lfence}               \
        } while (0)
    #define CC_CPU_WRITE_MEMORY_BARRIER() \
        do {                              \
            __asm { sfence}                \
        } while (0)
    #define CC_CPU_MEMORY_BARRIER() \
        do {                        \
            __asm { mfence}          \
        } while (0)

#elif (CC_COMPILER == CC_COMPILER_GNUC) || (CC_COMPILER == CC_COMPILER_CLANG)
#define CC_ALIGN(N)        __attribute__((__aligned__((N))))
    #define CC_CACHE_ALIGN     __attribute__((__aligned__((CC_CACHELINE_SIZE))))
    #define CC_PACKED_ALIGN(N) __attribute__((packed, aligned(N)))

    #define CC_ALIGNED_DECL(type, var, alignment) type var __attribute__((__aligned__(alignment)))

    #define CC_READ_COMPILER_BARRIER()        \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_WRITE_COMPILER_BARRIER()       \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_COMPILER_BARRIER()             \
        do {                                  \
            __asm__ __volatile__(""           \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)

    #define CC_READ_MEMORY_BARRIER() \
        do {                         \
            __sync_synchronize();    \
        } while (0)
    #define CC_WRITE_MEMORY_BARRIER() \
        do {                          \
            __sync_synchronize();     \
        } while (0)
    #define CC_MEMORY_BARRIER()   \
        do {                      \
            __sync_synchronize(); \
        } while (0)

    #define CC_CPU_READ_MEMORY_BARRIER()      \
        do {                                  \
            __asm__ __volatile__("lfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_CPU_WRITE_MEMORY_BARRIER()     \
        do {                                  \
            __asm__ __volatile__("sfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)
    #define CC_CPU_MEMORY_BARRIER()           \
        do {                                  \
            __asm__ __volatile__("mfence"     \
                                 :            \
                                 :            \
                                 : "memory"); \
        } while (0)

#else
#error "Unsupported compiler!"
#endif

/* Stack-alignment
 If macro __CC_SIMD_ALIGN_STACK defined, means there requests
 special code to ensure stack align to a 16-bytes boundary.

 Note:
 This macro can only guarantee callee stack pointer (esp) align
 to a 16-bytes boundary, but not that for frame pointer (ebp).
 Because most compiler might use frame pointer to access to stack
 variables, so you need to wrap those alignment required functions
 with extra function call.
 */
#if defined(__INTEL_COMPILER)
// For intel's compiler, simply calling alloca seems to do the right
    // thing. The size of the allocated block seems to be irrelevant.
    #define CC_SIMD_ALIGN_STACK() _alloca(16)
    #define CC_SIMD_ALIGN_ATTRIBUTE

#elif (CC_CPU == CC_CPU_X86) && (CC_COMPILER == CC_COMPILER_GNUC || CC_COMPILER == CC_COMPILER_CLANG) && (CC_CPU_ARCH != CC_CPU_ARCH_64)
// mark functions with GCC attribute to force stack alignment to 16 bytes
    #define CC_SIMD_ALIGN_ATTRIBUTE __attribute__((force_align_arg_pointer))
#elif (CC_COMPILER == CC_COMPILER_MSVC)
// Fortunately, MSVC will align the stack automatically
    #define CC_SIMD_ALIGN_ATTRIBUTE
#else
#define CC_SIMD_ALIGN_ATTRIBUTE
#endif

// mode
#if (defined(_DEBUG) || defined(DEBUG)) && (CC_PLATFORM == CC_PLATFORM_WINDOWS)
#define CC_MODE CC_MODE_DEBUG
#else
#define CC_MODE CC_MODE_RELEASE
#endif

#define CC_TOSTR(s) #s

#if defined(__GNUC__) && __GNUC__ >= 4
#define CC_PREDICT_TRUE(x)  __builtin_expect(!!(x), 1)
    #define CC_PREDICT_FALSE(x) __builtin_expect(!!(x), 0)
#else
#define CC_PREDICT_TRUE(x)  (x)
#define CC_PREDICT_FALSE(x) (x)
#endif

#if defined(_MSC_VER)
#define CC_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define CC_FORCE_INLINE inline __attribute__((always_inline))
#else
#if defined(__cplusplus) || defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */
#define CC_FORCE_INLINE static inline
#elif
#define CC_FORCE_INLINE inline
#endif
#endif
