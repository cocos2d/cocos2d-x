/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkTypes_DEFINED
#define SkTypes_DEFINED

#include "SkPreConfig.h"
#include "SkUserConfig.h"
#include "SkPostConfig.h"

#ifndef SK_IGNORE_STDINT_DOT_H
    #include <stdint.h>
#endif

#include <stdio.h>

/** \file SkTypes.h
*/

/** See SkGraphics::GetVersion() to retrieve these at runtime
 */
#define SKIA_VERSION_MAJOR  1
#define SKIA_VERSION_MINOR  0
#define SKIA_VERSION_PATCH  0

/*
    memory wrappers to be implemented by the porting layer (platform)
*/

/** Called internally if we run out of memory. The platform implementation must
    not return, but should either throw an exception or otherwise exit.
*/
extern void  sk_out_of_memory(void);
/** Called internally if we hit an unrecoverable error.
    The platform implementation must not return, but should either throw
    an exception or otherwise exit.
*/
extern void  sk_throw(void);

enum {
    SK_MALLOC_TEMP  = 0x01, //!< hint to sk_malloc that the requested memory will be freed in the scope of the stack frame
    SK_MALLOC_THROW = 0x02  //!< instructs sk_malloc to call sk_throw if the memory cannot be allocated.
};
/** Return a block of memory (at least 4-byte aligned) of at least the
    specified size. If the requested memory cannot be returned, either
    return null (if SK_MALLOC_TEMP bit is clear) or call sk_throw()
    (if SK_MALLOC_TEMP bit is set). To free the memory, call sk_free().
*/
SK_API extern void* sk_malloc_flags(size_t size, unsigned flags);
/** Same as sk_malloc(), but hard coded to pass SK_MALLOC_THROW as the flag
*/
SK_API extern void* sk_malloc_throw(size_t size);
/** Same as standard realloc(), but this one never returns null on failure. It will throw
    an exception if it fails.
*/
extern void* sk_realloc_throw(void* buffer, size_t size);
/** Free memory returned by sk_malloc(). It is safe to pass null.
*/
SK_API extern void  sk_free(void*);

// bzero is safer than memset, but we can't rely on it, so... sk_bzero()
static inline void sk_bzero(void* buffer, size_t size) {
    memset(buffer, 0, size);
}

///////////////////////////////////////////////////////////////////////

#define SK_INIT_TO_AVOID_WARNING    = 0

#ifndef SkDebugf
    SK_API void SkDebugf(const char format[], ...);
#endif

#ifdef SK_DEBUG
    #define SkASSERT(cond)              SK_DEBUGBREAK(cond)
    #define SkDEBUGCODE(code)           code
    #define SkDECLAREPARAM(type, var)   , type var
    #define SkPARAM(var)                , var
//  #define SkDEBUGF(args       )       SkDebugf##args
    #define SkDEBUGF(args       )       SkDebugf args
    #define SkAssertResult(cond)        SkASSERT(cond)
#else
    #define SkASSERT(cond)
    #define SkDEBUGCODE(code)
    #define SkDEBUGF(args)
    #define SkDECLAREPARAM(type, var)
    #define SkPARAM(var)

    // unlike SkASSERT, this guy executes its condition in the non-debug build
    #define SkAssertResult(cond)        cond
#endif

namespace {

template <bool>
struct SkCompileAssert {
};

}  // namespace

#define SK_COMPILE_ASSERT(expr, msg) \
    typedef SkCompileAssert<(bool(expr))> msg[bool(expr) ? 1 : -1]

///////////////////////////////////////////////////////////////////////

/**
 *  Fast type for signed 8 bits. Use for parameter passing and local variables,
 *  not for storage.
 */
typedef int S8CPU;

/**
 *  Fast type for unsigned 8 bits. Use for parameter passing and local
 *  variables, not for storage
 */
typedef unsigned U8CPU;

/**
 *  Fast type for signed 16 bits. Use for parameter passing and local variables,
 *  not for storage
 */
typedef int S16CPU;

/**
 *  Fast type for unsigned 16 bits. Use for parameter passing and local
 *  variables, not for storage
 */
typedef unsigned U16CPU;

/**
 *  Meant to be faster than bool (doesn't promise to be 0 or 1,
 *  just 0 or non-zero
 */
typedef int SkBool;

/**
 *  Meant to be a small version of bool, for storage purposes. Will be 0 or 1
 */
typedef uint8_t SkBool8;

#ifdef SK_DEBUG
    SK_API int8_t      SkToS8(long);
    SK_API uint8_t     SkToU8(size_t);
    SK_API int16_t     SkToS16(long);
    SK_API uint16_t    SkToU16(size_t);
    SK_API int32_t     SkToS32(long);
    SK_API uint32_t    SkToU32(size_t);
#else
    #define SkToS8(x)   ((int8_t)(x))
    #define SkToU8(x)   ((uint8_t)(x))
    #define SkToS16(x)  ((int16_t)(x))
    #define SkToU16(x)  ((uint16_t)(x))
    #define SkToS32(x)  ((int32_t)(x))
    #define SkToU32(x)  ((uint32_t)(x))
#endif

/** Returns 0 or 1 based on the condition
*/
#define SkToBool(cond)  ((cond) != 0)

#define SK_MaxS16   32767
#define SK_MinS16   -32767
#define SK_MaxU16   0xFFFF
#define SK_MinU16   0
#define SK_MaxS32   0x7FFFFFFF
#define SK_MinS32   0x80000001
#define SK_MaxU32   0xFFFFFFFF
#define SK_MinU32   0
#define SK_NaN32    0x80000000

/** Returns true if the value can be represented with signed 16bits
 */
static inline bool SkIsS16(long x) {
    return (int16_t)x == x;
}

/** Returns true if the value can be represented with unsigned 16bits
 */
static inline bool SkIsU16(long x) {
    return (uint16_t)x == x;
}

//////////////////////////////////////////////////////////////////////////////
#ifndef SK_OFFSETOF
    #define SK_OFFSETOF(type, field)    ((char*)&(((type*)1)->field) - (char*)1)
#endif

/** Returns the number of entries in an array (not a pointer)
*/
#define SK_ARRAY_COUNT(array)       (sizeof(array) / sizeof(array[0]))

/** Returns x rounded up to a multiple of 2
*/
#define SkAlign2(x)     (((x) + 1) >> 1 << 1)
/** Returns x rounded up to a multiple of 4
*/
#define SkAlign4(x)     (((x) + 3) >> 2 << 2)

typedef uint32_t SkFourByteTag;
#define SkSetFourByteTag(a, b, c, d)    (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

/** 32 bit integer to hold a unicode value
*/
typedef int32_t SkUnichar;
/** 32 bit value to hold a millisecond count
*/
typedef uint32_t SkMSec;
/** 1 second measured in milliseconds
*/
#define SK_MSec1 1000
/** maximum representable milliseconds
*/
#define SK_MSecMax 0x7FFFFFFF
/** Returns a < b for milliseconds, correctly handling wrap-around from 0xFFFFFFFF to 0
*/
#define SkMSec_LT(a, b)     ((int32_t)(a) - (int32_t)(b) < 0)
/** Returns a <= b for milliseconds, correctly handling wrap-around from 0xFFFFFFFF to 0
*/
#define SkMSec_LE(a, b)     ((int32_t)(a) - (int32_t)(b) <= 0)

/****************************************************************************
    The rest of these only build with C++
*/
#ifdef __cplusplus

/** Faster than SkToBool for integral conditions. Returns 0 or 1
*/
static inline int Sk32ToBool(uint32_t n) {
    return (n | (0-n)) >> 31;
}

template <typename T> inline void SkTSwap(T& a, T& b) {
    T c(a);
    a = b;
    b = c;
}

static inline int32_t SkAbs32(int32_t value) {
#ifdef SK_CPU_HAS_CONDITIONAL_INSTR
    if (value < 0)
        value = -value;
    return value;
#else
    int32_t mask = value >> 31;
    return (value ^ mask) - mask;
#endif
}

static inline int32_t SkMax32(int32_t a, int32_t b) {
    if (a < b)
        a = b;
    return a;
}

static inline int32_t SkMin32(int32_t a, int32_t b) {
    if (a > b)
        a = b;
    return a;
}

static inline int32_t SkSign32(int32_t a) {
    return (a >> 31) | ((unsigned) -a >> 31);
}

static inline int32_t SkFastMin32(int32_t value, int32_t max) {
#ifdef SK_CPU_HAS_CONDITIONAL_INSTR
    if (value > max)
        value = max;
    return value;
#else
    int diff = max - value;
    // clear diff if it is negative (clear if value > max)
    diff &= (diff >> 31);
    return value + diff;
#endif
}

/** Returns signed 32 bit value pinned between min and max, inclusively
*/
static inline int32_t SkPin32(int32_t value, int32_t min, int32_t max) {
#ifdef SK_CPU_HAS_CONDITIONAL_INSTR
    if (value < min)
        value = min;
    if (value > max)
        value = max;
#else
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
#endif
    return value;
}

static inline uint32_t SkSetClearShift(uint32_t bits, bool cond,
                                       unsigned shift) {
    SkASSERT((int)cond == 0 || (int)cond == 1);
    return (bits & ~(1 << shift)) | ((int)cond << shift);
}

static inline uint32_t SkSetClearMask(uint32_t bits, bool cond,
                                      uint32_t mask) {
    return cond ? bits | mask : bits & ~mask;
}

///////////////////////////////////////////////////////////////////////////////

/** Use to combine multiple bits in a bitmask in a type safe way.
 */
template <typename T>
T SkTBitOr(T a, T b) {
    return (T)(a | b);
}

/**
 *  Use to cast a pointer to a different type, and maintaining strict-aliasing
 */
template <typename Dst> Dst SkTCast(const void* ptr) {
    union {
        const void* src;
        Dst dst;
    } data;
    data.src = ptr;
    return data.dst;
}

//////////////////////////////////////////////////////////////////////////////

/** \class SkNoncopyable

SkNoncopyable is the base class for objects that may do not want to
be copied. It hides its copy-constructor and its assignment-operator.
*/
class SK_API SkNoncopyable {
public:
    SkNoncopyable() {}

private:
    SkNoncopyable(const SkNoncopyable&);
    SkNoncopyable& operator=(const SkNoncopyable&);
};

class SkAutoFree : SkNoncopyable {
public:
    SkAutoFree() : fPtr(NULL) {}
    explicit SkAutoFree(void* ptr) : fPtr(ptr) {}
    ~SkAutoFree() { sk_free(fPtr); }

    /** Return the currently allocate buffer, or null
    */
    void* get() const { return fPtr; }

    /** Assign a new ptr allocated with sk_malloc (or null), and return the
        previous ptr. Note it is the caller's responsibility to sk_free the
        returned ptr.
    */
    void* set(void* ptr) {
        void* prev = fPtr;
        fPtr = ptr;
        return prev;
    }

    /** Transfer ownership of the current ptr to the caller, setting the
        internal reference to null. Note the caller is reponsible for calling
        sk_free on the returned address.
    */
    void* detach() { return this->set(NULL); }

    /** Free the current buffer, and set the internal reference to NULL. Same
        as calling sk_free(detach())
    */
    void free() {
        sk_free(fPtr);
        fPtr = NULL;
    }

private:
    void* fPtr;
    // illegal
    SkAutoFree(const SkAutoFree&);
    SkAutoFree& operator=(const SkAutoFree&);
};

class SkAutoMalloc : public SkAutoFree {
public:
    explicit SkAutoMalloc(size_t size)
        : SkAutoFree(sk_malloc_flags(size, SK_MALLOC_THROW | SK_MALLOC_TEMP)) {}

    SkAutoMalloc(size_t size, unsigned flags)
        : SkAutoFree(sk_malloc_flags(size, flags)) {}
    SkAutoMalloc() {}

    void* alloc(size_t size,
                unsigned flags = (SK_MALLOC_THROW | SK_MALLOC_TEMP)) {
        sk_free(set(sk_malloc_flags(size, flags)));
        return get();
    }
};

/**
 *  Manage an allocated block of memory. If the requested size is <= kSize, then
 *  the allocation will come from the stack rather than the heap. This object
 *  is the sole manager of the lifetime of the block, so the caller must not
 *  call sk_free() or delete on the block.
 */
template <size_t kSize> class SkAutoSMalloc : SkNoncopyable {
public:
    /**
     *  Creates initially empty storage. get() returns a ptr, but it is to
     *  a zero-byte allocation. Must call realloc(size) to return an allocated
     *  block.
     */
    SkAutoSMalloc() {
        fPtr = fStorage;
    }

    /**
     *  Allocate a block of the specified size. If size <= kSize, then the
     *  allocation will come from the stack, otherwise it will be dynamically
     *  allocated.
     */
    explicit SkAutoSMalloc(size_t size) {
        fPtr = fStorage;
        this->realloc(size);
    }

    /**
     *  Free the allocated block (if any). If the block was small enought to
     *  have been allocated on the stack (size <= kSize) then this does nothing.
     */
    ~SkAutoSMalloc() {
        if (fPtr != (void*)fStorage) {
            sk_free(fPtr);
        }
    }

    /**
     *  Return the allocated block. May return non-null even if the block is
     *  of zero size. Since this may be on the stack or dynamically allocated,
     *  the caller must not call sk_free() on it, but must rely on SkAutoSMalloc
     *  to manage it.
     */
    void* get() const { return fPtr; }

    /**
     *  Return a new block of the requested size, freeing (as necessary) any
     *  previously allocated block. As with the constructor, if size <= kSize
     *  then the return block may be allocated locally, rather than from the
     *  heap.
     */
    void* realloc(size_t size) {
        if (fPtr != (void*)fStorage) {
            sk_free(fPtr);
        }

        if (size <= kSize) {
            fPtr = fStorage;
        } else {
            fPtr = sk_malloc_flags(size, SK_MALLOC_THROW | SK_MALLOC_TEMP);
        }
        return fPtr;
    }

private:
    void*       fPtr;
    uint32_t    fStorage[(kSize + 3) >> 2];
    // illegal
    SkAutoSMalloc(const SkAutoSMalloc&);
    SkAutoSMalloc& operator=(const SkAutoSMalloc&);
};

#endif /* C++ */

#endif

