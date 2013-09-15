/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* JS::Value implementation. */

#ifndef js_Value_h___
#define js_Value_h___

#include "mozilla/Attributes.h"
#include "mozilla/FloatingPoint.h"
#include "mozilla/Likely.h"

#include <limits> /* for std::numeric_limits */

#include "js/Anchor.h"
#include "js/RootingAPI.h"
#include "js/Utility.h"

namespace JS { class Value; }

/* JS::Value can store a full int32_t. */
#define JSVAL_INT_BITS          32
#define JSVAL_INT_MIN           ((int32_t)0x80000000)
#define JSVAL_INT_MAX           ((int32_t)0x7fffffff)

/*
 * Try to get jsvals 64-bit aligned. We could almost assert that all values are
 * aligned, but MSVC and GCC occasionally break alignment.
 */
#if defined(__GNUC__) || defined(__xlc__) || defined(__xlC__)
# define JSVAL_ALIGNMENT        __attribute__((aligned (8)))
#elif defined(_MSC_VER)
  /*
   * Structs can be aligned with MSVC, but not if they are used as parameters,
   * so we just don't try to align.
   */
# define JSVAL_ALIGNMENT
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# define JSVAL_ALIGNMENT
#elif defined(__HP_cc) || defined(__HP_aCC)
# define JSVAL_ALIGNMENT
#endif

#if JS_BITS_PER_WORD == 64
# define JSVAL_TAG_SHIFT 47
#endif

/*
 * We try to use enums so that printing a jsval_layout in the debugger shows
 * nice symbolic type tags, however we can only do this when we can force the
 * underlying type of the enum to be the desired size.
 */
#if defined(__cplusplus) && !defined(__SUNPRO_CC) && !defined(__xlC__)

#if defined(_MSC_VER)
# define JS_ENUM_HEADER(id, type)              enum id : type
# define JS_ENUM_FOOTER(id)
#else
# define JS_ENUM_HEADER(id, type)              enum id
# define JS_ENUM_FOOTER(id)                    __attribute__((packed))
#endif

/* Remember to propagate changes to the C defines below. */
JS_ENUM_HEADER(JSValueType, uint8_t)
{
    JSVAL_TYPE_DOUBLE              = 0x00,
    JSVAL_TYPE_INT32               = 0x01,
    JSVAL_TYPE_UNDEFINED           = 0x02,
    JSVAL_TYPE_BOOLEAN             = 0x03,
    JSVAL_TYPE_MAGIC               = 0x04,
    JSVAL_TYPE_STRING              = 0x05,
    JSVAL_TYPE_NULL                = 0x06,
    JSVAL_TYPE_OBJECT              = 0x07,

    /* These never appear in a jsval; they are only provided as an out-of-band value. */
    JSVAL_TYPE_UNKNOWN             = 0x20,
    JSVAL_TYPE_MISSING             = 0x21
} JS_ENUM_FOOTER(JSValueType);

JS_STATIC_ASSERT(sizeof(JSValueType) == 1);

#if JS_BITS_PER_WORD == 32

/* Remember to propagate changes to the C defines below. */
JS_ENUM_HEADER(JSValueTag, uint32_t)
{
    JSVAL_TAG_CLEAR                = 0xFFFFFF80,
    JSVAL_TAG_INT32                = JSVAL_TAG_CLEAR | JSVAL_TYPE_INT32,
    JSVAL_TAG_UNDEFINED            = JSVAL_TAG_CLEAR | JSVAL_TYPE_UNDEFINED,
    JSVAL_TAG_STRING               = JSVAL_TAG_CLEAR | JSVAL_TYPE_STRING,
    JSVAL_TAG_BOOLEAN              = JSVAL_TAG_CLEAR | JSVAL_TYPE_BOOLEAN,
    JSVAL_TAG_MAGIC                = JSVAL_TAG_CLEAR | JSVAL_TYPE_MAGIC,
    JSVAL_TAG_NULL                 = JSVAL_TAG_CLEAR | JSVAL_TYPE_NULL,
    JSVAL_TAG_OBJECT               = JSVAL_TAG_CLEAR | JSVAL_TYPE_OBJECT
} JS_ENUM_FOOTER(JSValueTag);

JS_STATIC_ASSERT(sizeof(JSValueTag) == 4);

#elif JS_BITS_PER_WORD == 64

/* Remember to propagate changes to the C defines below. */
JS_ENUM_HEADER(JSValueTag, uint32_t)
{
    JSVAL_TAG_MAX_DOUBLE           = 0x1FFF0,
    JSVAL_TAG_INT32                = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_INT32,
    JSVAL_TAG_UNDEFINED            = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_UNDEFINED,
    JSVAL_TAG_STRING               = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_STRING,
    JSVAL_TAG_BOOLEAN              = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_BOOLEAN,
    JSVAL_TAG_MAGIC                = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_MAGIC,
    JSVAL_TAG_NULL                 = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_NULL,
    JSVAL_TAG_OBJECT               = JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_OBJECT
} JS_ENUM_FOOTER(JSValueTag);

JS_STATIC_ASSERT(sizeof(JSValueTag) == sizeof(uint32_t));

JS_ENUM_HEADER(JSValueShiftedTag, uint64_t)
{
    JSVAL_SHIFTED_TAG_MAX_DOUBLE   = ((((uint64_t)JSVAL_TAG_MAX_DOUBLE) << JSVAL_TAG_SHIFT) | 0xFFFFFFFF),
    JSVAL_SHIFTED_TAG_INT32        = (((uint64_t)JSVAL_TAG_INT32)      << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_UNDEFINED    = (((uint64_t)JSVAL_TAG_UNDEFINED)  << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_STRING       = (((uint64_t)JSVAL_TAG_STRING)     << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_BOOLEAN      = (((uint64_t)JSVAL_TAG_BOOLEAN)    << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_MAGIC        = (((uint64_t)JSVAL_TAG_MAGIC)      << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_NULL         = (((uint64_t)JSVAL_TAG_NULL)       << JSVAL_TAG_SHIFT),
    JSVAL_SHIFTED_TAG_OBJECT       = (((uint64_t)JSVAL_TAG_OBJECT)     << JSVAL_TAG_SHIFT)
} JS_ENUM_FOOTER(JSValueShiftedTag);

JS_STATIC_ASSERT(sizeof(JSValueShiftedTag) == sizeof(uint64_t));

#endif

#else  /* defined(__cplusplus) */

typedef uint8_t JSValueType;
#define JSVAL_TYPE_DOUBLE            ((uint8_t)0x00)
#define JSVAL_TYPE_INT32             ((uint8_t)0x01)
#define JSVAL_TYPE_UNDEFINED         ((uint8_t)0x02)
#define JSVAL_TYPE_BOOLEAN           ((uint8_t)0x03)
#define JSVAL_TYPE_MAGIC             ((uint8_t)0x04)
#define JSVAL_TYPE_STRING            ((uint8_t)0x05)
#define JSVAL_TYPE_NULL              ((uint8_t)0x06)
#define JSVAL_TYPE_OBJECT            ((uint8_t)0x07)
#define JSVAL_TYPE_UNKNOWN           ((uint8_t)0x20)

#if JS_BITS_PER_WORD == 32

typedef uint32_t JSValueTag;
#define JSVAL_TAG_CLEAR              ((uint32_t)(0xFFFFFF80))
#define JSVAL_TAG_INT32              ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_INT32))
#define JSVAL_TAG_UNDEFINED          ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_UNDEFINED))
#define JSVAL_TAG_STRING             ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_STRING))
#define JSVAL_TAG_BOOLEAN            ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_BOOLEAN))
#define JSVAL_TAG_MAGIC              ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_MAGIC))
#define JSVAL_TAG_NULL               ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_NULL))
#define JSVAL_TAG_OBJECT             ((uint32_t)(JSVAL_TAG_CLEAR | JSVAL_TYPE_OBJECT))

#elif JS_BITS_PER_WORD == 64

typedef uint32_t JSValueTag;
#define JSVAL_TAG_MAX_DOUBLE         ((uint32_t)(0x1FFF0))
#define JSVAL_TAG_INT32              (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_INT32)
#define JSVAL_TAG_UNDEFINED          (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_UNDEFINED)
#define JSVAL_TAG_STRING             (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_STRING)
#define JSVAL_TAG_BOOLEAN            (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_BOOLEAN)
#define JSVAL_TAG_MAGIC              (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_MAGIC)
#define JSVAL_TAG_NULL               (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_NULL)
#define JSVAL_TAG_OBJECT             (uint32_t)(JSVAL_TAG_MAX_DOUBLE | JSVAL_TYPE_OBJECT)

typedef uint64_t JSValueShiftedTag;
#define JSVAL_SHIFTED_TAG_MAX_DOUBLE ((((uint64_t)JSVAL_TAG_MAX_DOUBLE) << JSVAL_TAG_SHIFT) | 0xFFFFFFFF)
#define JSVAL_SHIFTED_TAG_INT32      (((uint64_t)JSVAL_TAG_INT32)      << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_UNDEFINED  (((uint64_t)JSVAL_TAG_UNDEFINED)  << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_STRING     (((uint64_t)JSVAL_TAG_STRING)     << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_BOOLEAN    (((uint64_t)JSVAL_TAG_BOOLEAN)    << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_MAGIC      (((uint64_t)JSVAL_TAG_MAGIC)      << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_NULL       (((uint64_t)JSVAL_TAG_NULL)       << JSVAL_TAG_SHIFT)
#define JSVAL_SHIFTED_TAG_OBJECT     (((uint64_t)JSVAL_TAG_OBJECT)     << JSVAL_TAG_SHIFT)

#endif  /* JS_BITS_PER_WORD */
#endif  /* defined(__cplusplus) && !defined(__SUNPRO_CC) */

#define JSVAL_LOWER_INCL_TYPE_OF_OBJ_OR_NULL_SET        JSVAL_TYPE_NULL
#define JSVAL_UPPER_EXCL_TYPE_OF_PRIMITIVE_SET          JSVAL_TYPE_OBJECT
#define JSVAL_UPPER_INCL_TYPE_OF_NUMBER_SET             JSVAL_TYPE_INT32
#define JSVAL_LOWER_INCL_TYPE_OF_PTR_PAYLOAD_SET        JSVAL_TYPE_MAGIC

#if JS_BITS_PER_WORD == 32

#define JSVAL_TYPE_TO_TAG(type)      ((JSValueTag)(JSVAL_TAG_CLEAR | (type)))

#define JSVAL_LOWER_INCL_TAG_OF_OBJ_OR_NULL_SET         JSVAL_TAG_NULL
#define JSVAL_UPPER_EXCL_TAG_OF_PRIMITIVE_SET           JSVAL_TAG_OBJECT
#define JSVAL_UPPER_INCL_TAG_OF_NUMBER_SET              JSVAL_TAG_INT32
#define JSVAL_LOWER_INCL_TAG_OF_GCTHING_SET             JSVAL_TAG_STRING

#elif JS_BITS_PER_WORD == 64

#define JSVAL_PAYLOAD_MASK           0x00007FFFFFFFFFFFLL
#define JSVAL_TAG_MASK               0xFFFF800000000000LL
#define JSVAL_TYPE_TO_TAG(type)      ((JSValueTag)(JSVAL_TAG_MAX_DOUBLE | (type)))
#define JSVAL_TYPE_TO_SHIFTED_TAG(type) (((uint64_t)JSVAL_TYPE_TO_TAG(type)) << JSVAL_TAG_SHIFT)

#define JSVAL_LOWER_INCL_TAG_OF_OBJ_OR_NULL_SET         JSVAL_TAG_NULL
#define JSVAL_UPPER_EXCL_TAG_OF_PRIMITIVE_SET           JSVAL_TAG_OBJECT
#define JSVAL_UPPER_INCL_TAG_OF_NUMBER_SET              JSVAL_TAG_INT32
#define JSVAL_LOWER_INCL_TAG_OF_GCTHING_SET             JSVAL_TAG_STRING

#define JSVAL_LOWER_INCL_SHIFTED_TAG_OF_OBJ_OR_NULL_SET  JSVAL_SHIFTED_TAG_NULL
#define JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_PRIMITIVE_SET    JSVAL_SHIFTED_TAG_OBJECT
#define JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_NUMBER_SET       JSVAL_SHIFTED_TAG_UNDEFINED
#define JSVAL_LOWER_INCL_SHIFTED_TAG_OF_GCTHING_SET      JSVAL_SHIFTED_TAG_STRING

#endif /* JS_BITS_PER_WORD */

typedef enum JSWhyMagic
{
    JS_ELEMENTS_HOLE,            /* a hole in a native object's elements */
    JS_NATIVE_ENUMERATE,         /* indicates that a custom enumerate hook forwarded
                                  * to JS_EnumerateState, which really means the object can be
                                  * enumerated like a native object. */
    JS_NO_ITER_VALUE,            /* there is not a pending iterator value */
    JS_GENERATOR_CLOSING,        /* exception value thrown when closing a generator */
    JS_NO_CONSTANT,              /* compiler sentinel value */
    JS_THIS_POISON,              /* used in debug builds to catch tracing errors */
    JS_ARG_POISON,               /* used in debug builds to catch tracing errors */
    JS_SERIALIZE_NO_NODE,        /* an empty subnode in the AST serializer */
    JS_LAZY_ARGUMENTS,           /* lazy arguments value on the stack */
    JS_OPTIMIZED_ARGUMENTS,      /* optimized-away 'arguments' value */
    JS_IS_CONSTRUCTING,          /* magic value passed to natives to indicate construction */
    JS_OVERWRITTEN_CALLEE,       /* arguments.callee has been overwritten */
    JS_FORWARD_TO_CALL_OBJECT,   /* args object element stored in call object */
    JS_BLOCK_NEEDS_CLONE,        /* value of static block object slot */
    JS_HASH_KEY_EMPTY,           /* see class js::HashableValue */
    JS_ION_ERROR,                /* error while running Ion code */
    JS_ION_BAILOUT,              /* status code to signal EnterIon will OSR into Interpret */
    JS_GENERIC_MAGIC             /* for local use */
} JSWhyMagic;

#if defined(IS_LITTLE_ENDIAN)
# if JS_BITS_PER_WORD == 32
typedef union jsval_layout
{
    uint64_t asBits;
    struct {
        union {
            int32_t        i32;
            uint32_t       u32;
            JSBool         boo;
            JSString       *str;
            JSObject       *obj;
            void           *ptr;
            JSWhyMagic     why;
            size_t         word;
            uintptr_t      uintptr;
        } payload;
        JSValueTag tag;
    } s;
    double asDouble;
    void *asPtr;
} JSVAL_ALIGNMENT jsval_layout;
# elif JS_BITS_PER_WORD == 64
typedef union jsval_layout
{
    uint64_t asBits;
#if (!defined(_WIN64) && defined(__cplusplus))
    /* MSVC does not pack these correctly :-( */
    struct {
        uint64_t           payload47 : 47;
        JSValueTag         tag : 17;
    } debugView;
#endif
    struct {
        union {
            int32_t        i32;
            uint32_t       u32;
            JSWhyMagic     why;
        } payload;
    } s;
    double asDouble;
    void *asPtr;
    size_t asWord;
    uintptr_t asUIntPtr;
} JSVAL_ALIGNMENT jsval_layout;
# endif  /* JS_BITS_PER_WORD */
#else   /* defined(IS_LITTLE_ENDIAN) */
# if JS_BITS_PER_WORD == 32
typedef union jsval_layout
{
    uint64_t asBits;
    struct {
        JSValueTag tag;
        union {
            int32_t        i32;
            uint32_t       u32;
            JSBool         boo;
            JSString       *str;
            JSObject       *obj;
            void           *ptr;
            JSWhyMagic     why;
            size_t         word;
            uintptr_t      uintptr;
        } payload;
    } s;
    double asDouble;
    void *asPtr;
} JSVAL_ALIGNMENT jsval_layout;
# elif JS_BITS_PER_WORD == 64
typedef union jsval_layout
{
    uint64_t asBits;
    struct {
        JSValueTag         tag : 17;
        uint64_t           payload47 : 47;
    } debugView;
    struct {
        uint32_t           padding;
        union {
            int32_t        i32;
            uint32_t       u32;
            JSWhyMagic     why;
            uintptr_t      word;
        } payload;
    } s;
    double asDouble;
    void *asPtr;
    size_t asWord;
    uintptr_t asUIntPtr;
} JSVAL_ALIGNMENT jsval_layout;
# endif /* JS_BITS_PER_WORD */
#endif  /* defined(IS_LITTLE_ENDIAN) */

JS_STATIC_ASSERT(sizeof(jsval_layout) == 8);

#if JS_BITS_PER_WORD == 32

/*
 * N.B. GCC, in some but not all cases, chooses to emit signed comparison of
 * JSValueTag even though its underlying type has been forced to be uint32_t.
 * Thus, all comparisons should explicitly cast operands to uint32_t.
 */

static inline jsval_layout
BUILD_JSVAL(JSValueTag tag, uint32_t payload)
{
    jsval_layout l;
    l.asBits = (((uint64_t)(uint32_t)tag) << 32) | payload;
    return l;
}

static inline JSBool
JSVAL_IS_DOUBLE_IMPL(jsval_layout l)
{
    return (uint32_t)l.s.tag <= (uint32_t)JSVAL_TAG_CLEAR;
}

static inline jsval_layout
DOUBLE_TO_JSVAL_IMPL(double d)
{
    jsval_layout l;
    l.asDouble = d;
    MOZ_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static inline JSBool
JSVAL_IS_INT32_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_INT32;
}

static inline int32_t
JSVAL_TO_INT32_IMPL(jsval_layout l)
{
    return l.s.payload.i32;
}

static inline jsval_layout
INT32_TO_JSVAL_IMPL(int32_t i)
{
    jsval_layout l;
    l.s.tag = JSVAL_TAG_INT32;
    l.s.payload.i32 = i;
    return l;
}

static inline JSBool
JSVAL_IS_NUMBER_IMPL(jsval_layout l)
{
    JSValueTag tag = l.s.tag;
    MOZ_ASSERT(tag != JSVAL_TAG_CLEAR);
    return (uint32_t)tag <= (uint32_t)JSVAL_UPPER_INCL_TAG_OF_NUMBER_SET;
}

static inline JSBool
JSVAL_IS_UNDEFINED_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_UNDEFINED;
}

static inline JSBool
JSVAL_IS_STRING_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_STRING;
}

static inline jsval_layout
STRING_TO_JSVAL_IMPL(JSString *str)
{
    jsval_layout l;
    MOZ_ASSERT(str);
    l.s.tag = JSVAL_TAG_STRING;
    l.s.payload.str = str;
    return l;
}

static inline JSString *
JSVAL_TO_STRING_IMPL(jsval_layout l)
{
    return l.s.payload.str;
}

static inline JSBool
JSVAL_IS_BOOLEAN_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_BOOLEAN;
}

static inline JSBool
JSVAL_TO_BOOLEAN_IMPL(jsval_layout l)
{
    return l.s.payload.boo;
}

static inline jsval_layout
BOOLEAN_TO_JSVAL_IMPL(JSBool b)
{
    jsval_layout l;
    MOZ_ASSERT(b == JS_TRUE || b == JS_FALSE);
    l.s.tag = JSVAL_TAG_BOOLEAN;
    l.s.payload.boo = b;
    return l;
}

static inline JSBool
JSVAL_IS_MAGIC_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_MAGIC;
}

static inline JSBool
JSVAL_IS_OBJECT_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_OBJECT;
}

static inline JSBool
JSVAL_IS_PRIMITIVE_IMPL(jsval_layout l)
{
    return (uint32_t)l.s.tag < (uint32_t)JSVAL_UPPER_EXCL_TAG_OF_PRIMITIVE_SET;
}

static inline JSBool
JSVAL_IS_OBJECT_OR_NULL_IMPL(jsval_layout l)
{
    MOZ_ASSERT((uint32_t)l.s.tag <= (uint32_t)JSVAL_TAG_OBJECT);
    return (uint32_t)l.s.tag >= (uint32_t)JSVAL_LOWER_INCL_TAG_OF_OBJ_OR_NULL_SET;
}

static inline JSObject *
JSVAL_TO_OBJECT_IMPL(jsval_layout l)
{
    return l.s.payload.obj;
}

static inline jsval_layout
OBJECT_TO_JSVAL_IMPL(JSObject *obj)
{
    jsval_layout l;
    MOZ_ASSERT(obj);
    l.s.tag = JSVAL_TAG_OBJECT;
    l.s.payload.obj = obj;
    return l;
}

static inline JSBool
JSVAL_IS_NULL_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_NULL;
}

static inline jsval_layout
PRIVATE_PTR_TO_JSVAL_IMPL(void *ptr)
{
    jsval_layout l;
    MOZ_ASSERT(((uint32_t)ptr & 1) == 0);
    l.s.tag = (JSValueTag)0;
    l.s.payload.ptr = ptr;
    MOZ_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static inline void *
JSVAL_TO_PRIVATE_PTR_IMPL(jsval_layout l)
{
    return l.s.payload.ptr;
}

static inline JSBool
JSVAL_IS_GCTHING_IMPL(jsval_layout l)
{
    /* gcc sometimes generates signed < without explicit casts. */
    return (uint32_t)l.s.tag >= (uint32_t)JSVAL_LOWER_INCL_TAG_OF_GCTHING_SET;
}

static inline void *
JSVAL_TO_GCTHING_IMPL(jsval_layout l)
{
    return l.s.payload.ptr;
}

static inline JSBool
JSVAL_IS_TRACEABLE_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_STRING || l.s.tag == JSVAL_TAG_OBJECT;
}

static inline uint32_t
JSVAL_TRACE_KIND_IMPL(jsval_layout l)
{
    return (uint32_t)(JSBool)JSVAL_IS_STRING_IMPL(l);
}

static inline JSBool
JSVAL_IS_SPECIFIC_INT32_IMPL(jsval_layout l, int32_t i32)
{
    return l.s.tag == JSVAL_TAG_INT32 && l.s.payload.i32 == i32;
}

static inline JSBool
JSVAL_IS_SPECIFIC_BOOLEAN(jsval_layout l, JSBool b)
{
    return (l.s.tag == JSVAL_TAG_BOOLEAN) && (l.s.payload.boo == b);
}

static inline jsval_layout
MAGIC_TO_JSVAL_IMPL(JSWhyMagic why)
{
    jsval_layout l;
    l.s.tag = JSVAL_TAG_MAGIC;
    l.s.payload.why = why;
    return l;
}

static inline JSBool
JSVAL_SAME_TYPE_IMPL(jsval_layout lhs, jsval_layout rhs)
{
    JSValueTag ltag = lhs.s.tag, rtag = rhs.s.tag;
    return ltag == rtag || (ltag < JSVAL_TAG_CLEAR && rtag < JSVAL_TAG_CLEAR);
}

static inline JSValueType
JSVAL_EXTRACT_NON_DOUBLE_TYPE_IMPL(jsval_layout l)
{
    uint32_t type = l.s.tag & 0xF;
    MOZ_ASSERT(type > JSVAL_TYPE_DOUBLE);
    return (JSValueType)type;
}

#elif JS_BITS_PER_WORD == 64

static inline jsval_layout
BUILD_JSVAL(JSValueTag tag, uint64_t payload)
{
    jsval_layout l;
    l.asBits = (((uint64_t)(uint32_t)tag) << JSVAL_TAG_SHIFT) | payload;
    return l;
}

static inline JSBool
JSVAL_IS_DOUBLE_IMPL(jsval_layout l)
{
    return l.asBits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE;
}

static inline jsval_layout
DOUBLE_TO_JSVAL_IMPL(double d)
{
    jsval_layout l;
    l.asDouble = d;
    MOZ_ASSERT(l.asBits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE);
    return l;
}

static inline JSBool
JSVAL_IS_INT32_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_INT32;
}

static inline int32_t
JSVAL_TO_INT32_IMPL(jsval_layout l)
{
    return (int32_t)l.asBits;
}

static inline jsval_layout
INT32_TO_JSVAL_IMPL(int32_t i32)
{
    jsval_layout l;
    l.asBits = ((uint64_t)(uint32_t)i32) | JSVAL_SHIFTED_TAG_INT32;
    return l;
}

static inline JSBool
JSVAL_IS_NUMBER_IMPL(jsval_layout l)
{
    return l.asBits < JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_NUMBER_SET;
}

static inline JSBool
JSVAL_IS_UNDEFINED_IMPL(jsval_layout l)
{
    return l.asBits == JSVAL_SHIFTED_TAG_UNDEFINED;
}

static inline JSBool
JSVAL_IS_STRING_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_STRING;
}

static inline jsval_layout
STRING_TO_JSVAL_IMPL(JSString *str)
{
    jsval_layout l;
    uint64_t strBits = (uint64_t)str;
    MOZ_ASSERT(str);
    MOZ_ASSERT((strBits >> JSVAL_TAG_SHIFT) == 0);
    l.asBits = strBits | JSVAL_SHIFTED_TAG_STRING;
    return l;
}

static inline JSString *
JSVAL_TO_STRING_IMPL(jsval_layout l)
{
    return (JSString *)(l.asBits & JSVAL_PAYLOAD_MASK);
}

static inline JSBool
JSVAL_IS_BOOLEAN_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_BOOLEAN;
}

static inline JSBool
JSVAL_TO_BOOLEAN_IMPL(jsval_layout l)
{
    return (JSBool)l.asBits;
}

static inline jsval_layout
BOOLEAN_TO_JSVAL_IMPL(JSBool b)
{
    jsval_layout l;
    MOZ_ASSERT(b == JS_TRUE || b == JS_FALSE);
    l.asBits = ((uint64_t)(uint32_t)b) | JSVAL_SHIFTED_TAG_BOOLEAN;
    return l;
}

static inline JSBool
JSVAL_IS_MAGIC_IMPL(jsval_layout l)
{
    return (l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_MAGIC;
}

static inline JSBool
JSVAL_IS_PRIMITIVE_IMPL(jsval_layout l)
{
    return l.asBits < JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_PRIMITIVE_SET;
}

static inline JSBool
JSVAL_IS_OBJECT_IMPL(jsval_layout l)
{
    MOZ_ASSERT((l.asBits >> JSVAL_TAG_SHIFT) <= JSVAL_SHIFTED_TAG_OBJECT);
    return l.asBits >= JSVAL_SHIFTED_TAG_OBJECT;
}

static inline JSBool
JSVAL_IS_OBJECT_OR_NULL_IMPL(jsval_layout l)
{
    MOZ_ASSERT((l.asBits >> JSVAL_TAG_SHIFT) <= JSVAL_TAG_OBJECT);
    return l.asBits >= JSVAL_LOWER_INCL_SHIFTED_TAG_OF_OBJ_OR_NULL_SET;
}

static inline JSObject *
JSVAL_TO_OBJECT_IMPL(jsval_layout l)
{
    uint64_t ptrBits = l.asBits & JSVAL_PAYLOAD_MASK;
    MOZ_ASSERT((ptrBits & 0x7) == 0);
    return (JSObject *)ptrBits;
}

static inline jsval_layout
OBJECT_TO_JSVAL_IMPL(JSObject *obj)
{
    jsval_layout l;
    uint64_t objBits = (uint64_t)obj;
    MOZ_ASSERT(obj);
    MOZ_ASSERT((objBits >> JSVAL_TAG_SHIFT) == 0);
    l.asBits = objBits | JSVAL_SHIFTED_TAG_OBJECT;
    return l;
}

static inline JSBool
JSVAL_IS_NULL_IMPL(jsval_layout l)
{
    return l.asBits == JSVAL_SHIFTED_TAG_NULL;
}

static inline JSBool
JSVAL_IS_GCTHING_IMPL(jsval_layout l)
{
    return l.asBits >= JSVAL_LOWER_INCL_SHIFTED_TAG_OF_GCTHING_SET;
}

static inline void *
JSVAL_TO_GCTHING_IMPL(jsval_layout l)
{
    uint64_t ptrBits = l.asBits & JSVAL_PAYLOAD_MASK;
    MOZ_ASSERT((ptrBits & 0x7) == 0);
    return (void *)ptrBits;
}

static inline JSBool
JSVAL_IS_TRACEABLE_IMPL(jsval_layout l)
{
    return JSVAL_IS_GCTHING_IMPL(l) && !JSVAL_IS_NULL_IMPL(l);
}

static inline uint32_t
JSVAL_TRACE_KIND_IMPL(jsval_layout l)
{
    return (uint32_t)(JSBool)!(JSVAL_IS_OBJECT_IMPL(l));
}

static inline jsval_layout
PRIVATE_PTR_TO_JSVAL_IMPL(void *ptr)
{
    jsval_layout l;
    uint64_t ptrBits = (uint64_t)ptr;
    MOZ_ASSERT((ptrBits & 1) == 0);
    l.asBits = ptrBits >> 1;
    MOZ_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static inline void *
JSVAL_TO_PRIVATE_PTR_IMPL(jsval_layout l)
{
    MOZ_ASSERT((l.asBits & 0x8000000000000000LL) == 0);
    return (void *)(l.asBits << 1);
}

static inline JSBool
JSVAL_IS_SPECIFIC_INT32_IMPL(jsval_layout l, int32_t i32)
{
    return l.asBits == (((uint64_t)(uint32_t)i32) | JSVAL_SHIFTED_TAG_INT32);
}

static inline JSBool
JSVAL_IS_SPECIFIC_BOOLEAN(jsval_layout l, JSBool b)
{
    return l.asBits == (((uint64_t)(uint32_t)b) | JSVAL_SHIFTED_TAG_BOOLEAN);
}

static inline jsval_layout
MAGIC_TO_JSVAL_IMPL(JSWhyMagic why)
{
    jsval_layout l;
    l.asBits = ((uint64_t)(uint32_t)why) | JSVAL_SHIFTED_TAG_MAGIC;
    return l;
}

static inline JSBool
JSVAL_SAME_TYPE_IMPL(jsval_layout lhs, jsval_layout rhs)
{
    uint64_t lbits = lhs.asBits, rbits = rhs.asBits;
    return (lbits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE && rbits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE) ||
           (((lbits ^ rbits) & 0xFFFF800000000000LL) == 0);
}

static inline JSValueType
JSVAL_EXTRACT_NON_DOUBLE_TYPE_IMPL(jsval_layout l)
{
   uint64_t type = (l.asBits >> JSVAL_TAG_SHIFT) & 0xF;
   MOZ_ASSERT(type > JSVAL_TYPE_DOUBLE);
   return (JSValueType)type;
}

#endif  /* JS_BITS_PER_WORD */

static inline double
JS_CANONICALIZE_NAN(double d)
{
    if (MOZ_UNLIKELY(d != d)) {
        jsval_layout l;
        l.asBits = 0x7FF8000000000000LL;
        return l.asDouble;
    }
    return d;
}

static inline jsval_layout JSVAL_TO_IMPL(JS::Value v);
static inline JS::Value IMPL_TO_JSVAL(jsval_layout l);

namespace JS {

/*
 * JS::Value is the interface for a single JavaScript Engine value.  A few
 * general notes on JS::Value:
 *
 * - JS::Value has setX() and isX() members for X in
 *
 *     { Int32, Double, String, Boolean, Undefined, Null, Object, Magic }
 *
 *   JS::Value also contains toX() for each of the non-singleton types.
 *
 * - Magic is a singleton type whose payload contains a JSWhyMagic "reason" for
 *   the magic value. By providing JSWhyMagic values when creating and checking
 *   for magic values, it is possible to assert, at runtime, that only magic
 *   values with the expected reason flow through a particular value. For
 *   example, if cx->exception has a magic value, the reason must be
 *   JS_GENERATOR_CLOSING.
 *
 * - The JS::Value operations are preferred.  The JSVAL_* operations remain for
 *   compatibility; they may be removed at some point.  These operations mostly
 *   provide similar functionality.  But there are a few key differences.  One
 *   is that JS::Value gives null a separate type. Thus
 *
 *           JSVAL_IS_OBJECT(v) === v.isObjectOrNull()
 *       !JSVAL_IS_PRIMITIVE(v) === v.isObject()
 *
 *   Also, to help prevent mistakenly boxing a nullable JSObject* as an object,
 *   Value::setObject takes a JSObject&. (Conversely, Value::asObject returns a
 *   JSObject&.)  A convenience member Value::setObjectOrNull is provided.
 *
 * - JSVAL_VOID is the same as the singleton value of the Undefined type.
 *
 * - Note that JS::Value is 8 bytes on 32 and 64-bit architectures. Thus, on
 *   32-bit user code should avoid copying jsval/JS::Value as much as possible,
 *   preferring to pass by const Value &.
 */
class Value
{
  public:
    /*
     * N.B. the default constructor leaves Value unitialized. Adding a default
     * constructor prevents Value from being stored in a union.
     */

    /*** Mutators ***/

    void setNull() {
        data.asBits = BUILD_JSVAL(JSVAL_TAG_NULL, 0).asBits;
    }

    void setUndefined() {
        data.asBits = BUILD_JSVAL(JSVAL_TAG_UNDEFINED, 0).asBits;
    }

    void setInt32(int32_t i) {
        data = INT32_TO_JSVAL_IMPL(i);
    }

    int32_t &getInt32Ref() {
        MOZ_ASSERT(isInt32());
        return data.s.payload.i32;
    }

    void setDouble(double d) {
        data = DOUBLE_TO_JSVAL_IMPL(d);
    }

    double &getDoubleRef() {
        MOZ_ASSERT(isDouble());
        return data.asDouble;
    }

    void setString(JSString *str) {
        MOZ_ASSERT(!IsPoisonedPtr(str));
        data = STRING_TO_JSVAL_IMPL(str);
    }

    void setString(const JS::Anchor<JSString *> &str) {
        setString(str.get());
    }

    void setObject(JSObject &obj) {
        MOZ_ASSERT(!IsPoisonedPtr(&obj));
        data = OBJECT_TO_JSVAL_IMPL(&obj);
    }

    void setBoolean(bool b) {
        data = BOOLEAN_TO_JSVAL_IMPL(b);
    }

    void setMagic(JSWhyMagic why) {
        data = MAGIC_TO_JSVAL_IMPL(why);
    }

    bool setNumber(uint32_t ui) {
        if (ui > JSVAL_INT_MAX) {
            setDouble((double)ui);
            return false;
        } else {
            setInt32((int32_t)ui);
            return true;
        }
    }

    bool setNumber(double d) {
        int32_t i;
        if (mozilla::DoubleIsInt32(d, &i)) {
            setInt32(i);
            return true;
        }

        setDouble(d);
        return false;
    }

    void setObjectOrNull(JSObject *arg) {
        if (arg)
            setObject(*arg);
        else
            setNull();
    }

    void swap(Value &rhs) {
        uint64_t tmp = rhs.data.asBits;
        rhs.data.asBits = data.asBits;
        data.asBits = tmp;
    }

    /*** Value type queries ***/

    bool isUndefined() const {
        return JSVAL_IS_UNDEFINED_IMPL(data);
    }

    bool isNull() const {
        return JSVAL_IS_NULL_IMPL(data);
    }

    bool isNullOrUndefined() const {
        return isNull() || isUndefined();
    }

    bool isInt32() const {
        return JSVAL_IS_INT32_IMPL(data);
    }

    bool isInt32(int32_t i32) const {
        return JSVAL_IS_SPECIFIC_INT32_IMPL(data, i32);
    }

    bool isDouble() const {
        return JSVAL_IS_DOUBLE_IMPL(data);
    }

    bool isNumber() const {
        return JSVAL_IS_NUMBER_IMPL(data);
    }

    bool isString() const {
        return JSVAL_IS_STRING_IMPL(data);
    }

    bool isObject() const {
        return JSVAL_IS_OBJECT_IMPL(data);
    }

    bool isPrimitive() const {
        return JSVAL_IS_PRIMITIVE_IMPL(data);
    }

    bool isObjectOrNull() const {
        return JSVAL_IS_OBJECT_OR_NULL_IMPL(data);
    }

    bool isGCThing() const {
        return JSVAL_IS_GCTHING_IMPL(data);
    }

    bool isBoolean() const {
        return JSVAL_IS_BOOLEAN_IMPL(data);
    }

    bool isTrue() const {
        return JSVAL_IS_SPECIFIC_BOOLEAN(data, true);
    }

    bool isFalse() const {
        return JSVAL_IS_SPECIFIC_BOOLEAN(data, false);
    }

    bool isMagic() const {
        return JSVAL_IS_MAGIC_IMPL(data);
    }

    bool isMagic(JSWhyMagic why) const {
        MOZ_ASSERT_IF(isMagic(), data.s.payload.why == why);
        return JSVAL_IS_MAGIC_IMPL(data);
    }

    bool isMarkable() const {
        return JSVAL_IS_TRACEABLE_IMPL(data);
    }

    JSGCTraceKind gcKind() const {
        MOZ_ASSERT(isMarkable());
        return JSGCTraceKind(JSVAL_TRACE_KIND_IMPL(data));
    }

    JSWhyMagic whyMagic() const {
        MOZ_ASSERT(isMagic());
        return data.s.payload.why;
    }

    /*** Comparison ***/

    bool operator==(const Value &rhs) const {
        return data.asBits == rhs.data.asBits;
    }

    bool operator!=(const Value &rhs) const {
        return data.asBits != rhs.data.asBits;
    }

    friend inline bool SameType(const Value &lhs, const Value &rhs);

    /*** Extract the value's typed payload ***/

    int32_t toInt32() const {
        MOZ_ASSERT(isInt32());
        return JSVAL_TO_INT32_IMPL(data);
    }

    double toDouble() const {
        MOZ_ASSERT(isDouble());
        return data.asDouble;
    }

    double toNumber() const {
        MOZ_ASSERT(isNumber());
        return isDouble() ? toDouble() : double(toInt32());
    }

    JSString *toString() const {
        MOZ_ASSERT(isString());
        return JSVAL_TO_STRING_IMPL(data);
    }

    JSObject &toObject() const {
        MOZ_ASSERT(isObject());
        return *JSVAL_TO_OBJECT_IMPL(data);
    }

    JSObject *toObjectOrNull() const {
        MOZ_ASSERT(isObjectOrNull());
        return JSVAL_TO_OBJECT_IMPL(data);
    }

    void *toGCThing() const {
        MOZ_ASSERT(isGCThing());
        return JSVAL_TO_GCTHING_IMPL(data);
    }

    bool toBoolean() const {
        MOZ_ASSERT(isBoolean());
        return JSVAL_TO_BOOLEAN_IMPL(data);
    }

    uint32_t payloadAsRawUint32() const {
        MOZ_ASSERT(!isDouble());
        return data.s.payload.u32;
    }

    uint64_t asRawBits() const {
        return data.asBits;
    }

    JSValueType extractNonDoubleType() const {
        return JSVAL_EXTRACT_NON_DOUBLE_TYPE_IMPL(data);
    }

    /*
     * Private API
     *
     * Private setters/getters allow the caller to read/write arbitrary types
     * that fit in the 64-bit payload. It is the caller's responsibility, after
     * storing to a value with setPrivateX to read only using getPrivateX.
     * Privates values are given a type which ensures they are not marked.
     */

    void setPrivate(void *ptr) {
        data = PRIVATE_PTR_TO_JSVAL_IMPL(ptr);
    }

    void *toPrivate() const {
        MOZ_ASSERT(JSVAL_IS_DOUBLE_IMPL(data));
        return JSVAL_TO_PRIVATE_PTR_IMPL(data);
    }

    void setPrivateUint32(uint32_t ui) {
        MOZ_ASSERT(uint32_t(int32_t(ui)) == ui);
        setInt32(int32_t(ui));
    }

    uint32_t toPrivateUint32() const {
        return uint32_t(toInt32());
    }

    /*
     * An unmarked value is just a void* cast as a Value. Thus, the Value is
     * not safe for GC and must not be marked. This API avoids raw casts
     * and the ensuing strict-aliasing warnings.
     */

    void setUnmarkedPtr(void *ptr) {
        data.asPtr = ptr;
    }

    void *toUnmarkedPtr() const {
        return data.asPtr;
    }

    const size_t *payloadWord() const {
#if JS_BITS_PER_WORD == 32
        return &data.s.payload.word;
#elif JS_BITS_PER_WORD == 64
        return &data.asWord;
#endif
    }

    const uintptr_t *payloadUIntPtr() const {
#if JS_BITS_PER_WORD == 32
        return &data.s.payload.uintptr;
#elif JS_BITS_PER_WORD == 64
        return &data.asUIntPtr;
#endif
    }

#if !defined(_MSC_VER) && !defined(__sparc)
  // Value must be POD so that MSVC will pass it by value and not in memory
  // (bug 689101); the same is true for SPARC as well (bug 737344).  More
  // precisely, we don't want Value return values compiled as out params.
  private:
#endif

    jsval_layout data;

  private:
    void staticAssertions() {
        JS_STATIC_ASSERT(sizeof(JSValueType) == 1);
        JS_STATIC_ASSERT(sizeof(JSValueTag) == 4);
        JS_STATIC_ASSERT(sizeof(JSBool) == 4);
        JS_STATIC_ASSERT(sizeof(JSWhyMagic) <= 4);
        JS_STATIC_ASSERT(sizeof(Value) == 8);
    }

    friend jsval_layout (::JSVAL_TO_IMPL)(Value);
    friend Value (::IMPL_TO_JSVAL)(jsval_layout l);
};

inline bool
IsPoisonedValue(const Value &v)
{
    if (v.isString())
        return IsPoisonedPtr(v.toString());
    if (v.isObject())
        return IsPoisonedPtr(&v.toObject());
    return false;
}

/************************************************************************/

static inline Value
NullValue()
{
    Value v;
    v.setNull();
    return v;
}

static inline Value
UndefinedValue()
{
    Value v;
    v.setUndefined();
    return v;
}

static inline Value
Int32Value(int32_t i32)
{
    Value v;
    v.setInt32(i32);
    return v;
}

static inline Value
DoubleValue(double dbl)
{
    Value v;
    v.setDouble(dbl);
    return v;
}

static inline Value
StringValue(JSString *str)
{
    Value v;
    v.setString(str);
    return v;
}

static inline Value
BooleanValue(bool boo)
{
    Value v;
    v.setBoolean(boo);
    return v;
}

static inline Value
ObjectValue(JSObject &obj)
{
    Value v;
    v.setObject(obj);
    return v;
}

static inline Value
ObjectValueCrashOnTouch()
{
    Value v;
    v.setObject(*reinterpret_cast<JSObject *>(0x42));
    return v;
}

static inline Value
MagicValue(JSWhyMagic why)
{
    Value v;
    v.setMagic(why);
    return v;
}

static inline Value
NumberValue(float f)
{
    Value v;
    v.setNumber(f);
    return v;
}

static inline Value
NumberValue(double dbl)
{
    Value v;
    v.setNumber(dbl);
    return v;
}

static inline Value
NumberValue(int8_t i)
{
    return Int32Value(i);
}

static inline Value
NumberValue(uint8_t i)
{
    return Int32Value(i);
}

static inline Value
NumberValue(int16_t i)
{
    return Int32Value(i);
}

static inline Value
NumberValue(uint16_t i)
{
    return Int32Value(i);
}

static inline Value
NumberValue(int32_t i)
{
    return Int32Value(i);
}

static inline Value
NumberValue(uint32_t i)
{
    Value v;
    v.setNumber(i);
    return v;
}

namespace detail {

template <bool Signed>
class MakeNumberValue
{
  public:
    template<typename T>
    static inline Value create(const T t)
    {
        Value v;
        if (JSVAL_INT_MIN <= t && t <= JSVAL_INT_MAX)
            v.setInt32(int32_t(t));
        else
            v.setDouble(double(t));
        return v;
    }
};

template <>
class MakeNumberValue<false>
{
  public:
    template<typename T>
    static inline Value create(const T t)
    {
        Value v;
        if (t <= JSVAL_INT_MAX)
            v.setInt32(int32_t(t));
        else
            v.setDouble(double(t));
        return v;
    }
};

} // namespace detail

template <typename T>
static inline Value
NumberValue(const T t)
{
    MOZ_ASSERT(T(double(t)) == t, "value creation would be lossy");
    return detail::MakeNumberValue<std::numeric_limits<T>::is_signed>::create(t);
}

static inline Value
ObjectOrNullValue(JSObject *obj)
{
    Value v;
    v.setObjectOrNull(obj);
    return v;
}

static inline Value
PrivateValue(void *ptr)
{
    Value v;
    v.setPrivate(ptr);
    return v;
}

static inline Value
PrivateUint32Value(uint32_t ui)
{
    Value v;
    v.setPrivateUint32(ui);
    return v;
}

inline bool
SameType(const Value &lhs, const Value &rhs)
{
    return JSVAL_SAME_TYPE_IMPL(lhs.data, rhs.data);
}

} // namespace JS

/************************************************************************/

namespace js {

template <> struct RootMethods<const JS::Value>
{
    static JS::Value initial() { return JS::UndefinedValue(); }
    static ThingRootKind kind() { return THING_ROOT_VALUE; }
    static bool poisoned(const JS::Value &v) { return JS::IsPoisonedValue(v); }
};

template <> struct RootMethods<JS::Value>
{
    static JS::Value initial() { return JS::UndefinedValue(); }
    static ThingRootKind kind() { return THING_ROOT_VALUE; }
    static bool poisoned(const JS::Value &v) { return JS::IsPoisonedValue(v); }
};

template <class Outer> class MutableValueOperations;

/*
 * A class designed for CRTP use in implementing the non-mutating parts of the
 * Value interface in Value-like classes.  Outer must be a class inheriting
 * ValueOperations<Outer> with a visible extract() method returning the
 * const Value* abstracted by Outer.
 */
template <class Outer>
class ValueOperations
{
    friend class MutableValueOperations<Outer>;
    const JS::Value * value() const { return static_cast<const Outer*>(this)->extract(); }

  public:
    bool isUndefined() const { return value()->isUndefined(); }
    bool isNull() const { return value()->isNull(); }
    bool isBoolean() const { return value()->isBoolean(); }
    bool isTrue() const { return value()->isTrue(); }
    bool isFalse() const { return value()->isFalse(); }
    bool isNumber() const { return value()->isNumber(); }
    bool isInt32() const { return value()->isInt32(); }
    bool isDouble() const { return value()->isDouble(); }
    bool isString() const { return value()->isString(); }
    bool isObject() const { return value()->isObject(); }
    bool isMagic() const { return value()->isMagic(); }
    bool isMagic(JSWhyMagic why) const { return value()->isMagic(why); }
    bool isMarkable() const { return value()->isMarkable(); }
    bool isPrimitive() const { return value()->isPrimitive(); }
    bool isGCThing() const { return value()->isGCThing(); }

    bool isNullOrUndefined() const { return value()->isNullOrUndefined(); }
    bool isObjectOrNull() const { return value()->isObjectOrNull(); }

    bool toBoolean() const { return value()->toBoolean(); }
    double toNumber() const { return value()->toNumber(); }
    int32_t toInt32() const { return value()->toInt32(); }
    double toDouble() const { return value()->toDouble(); }
    JSString *toString() const { return value()->toString(); }
    JSObject &toObject() const { return value()->toObject(); }
    JSObject *toObjectOrNull() const { return value()->toObjectOrNull(); }
    void *toGCThing() const { return value()->toGCThing(); }

    JSValueType extractNonDoubleType() const { return value()->extractNonDoubleType(); }

    JSWhyMagic whyMagic() const { return value()->whyMagic(); }
};

/*
 * A class designed for CRTP use in implementing the mutating parts of the
 * Value interface in Value-like classes.  Outer must be a class inheriting
 * MutableValueOperations<Outer> with visible extractMutable() and extract()
 * methods returning the const Value* and Value* abstracted by Outer.
 */
template <class Outer>
class MutableValueOperations : public ValueOperations<Outer>
{
    JS::Value * value() { return static_cast<Outer*>(this)->extractMutable(); }

  public:
    void setNull() { value()->setNull(); }
    void setUndefined() { value()->setUndefined(); }
    void setInt32(int32_t i) { value()->setInt32(i); }
    void setDouble(double d) { value()->setDouble(d); }
    void setString(JSString *str) { value()->setString(str); }
    void setString(const JS::Anchor<JSString *> &str) { value()->setString(str); }
    void setObject(JSObject &obj) { value()->setObject(obj); }
    void setBoolean(bool b) { value()->setBoolean(b); }
    void setMagic(JSWhyMagic why) { value()->setMagic(why); }
    bool setNumber(uint32_t ui) { return value()->setNumber(ui); }
    bool setNumber(double d) { return value()->setNumber(d); }
    void setObjectOrNull(JSObject *arg) { value()->setObjectOrNull(arg); }
};

/*
 * Augment the generic Handle<T> interface when T = Value with type-querying
 * and value-extracting operations.
 */
template <>
class HandleBase<JS::Value> : public ValueOperations<JS::Handle<JS::Value> >
{
    friend class ValueOperations<JS::Handle<JS::Value> >;
    const JS::Value * extract() const {
        return static_cast<const JS::Handle<JS::Value>*>(this)->address();
    }
};

/*
 * Augment the generic MutableHandle<T> interface when T = Value with
 * type-querying, value-extracting, and mutating operations.
 */
template <>
class MutableHandleBase<JS::Value> : public MutableValueOperations<JS::MutableHandle<JS::Value> >
{
    friend class ValueOperations<JS::MutableHandle<JS::Value> >;
    const JS::Value * extract() const {
        return static_cast<const JS::MutableHandle<JS::Value>*>(this)->address();
    }

    friend class MutableValueOperations<JS::MutableHandle<JS::Value> >;
    JS::Value * extractMutable() {
        return static_cast<JS::MutableHandle<JS::Value>*>(this)->address();
    }
};

/*
 * Augment the generic Rooted<T> interface when T = Value with type-querying,
 * value-extracting, and mutating operations.
 */
template <>
class RootedBase<JS::Value> : public MutableValueOperations<JS::Rooted<JS::Value> >
{
    friend class ValueOperations<JS::Rooted<JS::Value> >;
    const JS::Value * extract() const {
        return static_cast<const JS::Rooted<JS::Value>*>(this)->address();
    }

    friend class MutableValueOperations<JS::Rooted<JS::Value> >;
    JS::Value * extractMutable() {
        return static_cast<JS::Rooted<JS::Value>*>(this)->address();
    }
};

} // namespace js

inline jsval_layout
JSVAL_TO_IMPL(JS::Value v)
{
    return v.data;
}

inline JS::Value
IMPL_TO_JSVAL(jsval_layout l)
{
    JS::Value v;
    v.data = l;
    return v;
}

namespace JS {

#ifndef __GNUC__
/*
 * The default assignment operator for |struct C| has the signature:
 *
 *   C& C::operator=(const C&)
 *
 * And in particular requires implicit conversion of |this| to type |C| for the
 * return value. But |volatile C| cannot thus be converted to |C|, so just
 * doing |sink = hold| as in the non-specialized version would fail to compile.
 * Do the assignment on asBits instead, since I don't think we want to give
 * jsval_layout an assignment operator returning |volatile jsval_layout|.
 */
template<>
inline Anchor<Value>::~Anchor()
{
    volatile uint64_t bits;
    bits = JSVAL_TO_IMPL(hold).asBits;
}
#endif

#ifdef DEBUG
namespace detail {

struct ValueAlignmentTester { char c; JS::Value v; };
MOZ_STATIC_ASSERT(sizeof(ValueAlignmentTester) == 16,
                  "JS::Value must be 16-byte-aligned");

struct LayoutAlignmentTester { char c; jsval_layout l; };
MOZ_STATIC_ASSERT(sizeof(LayoutAlignmentTester) == 16,
                  "jsval_layout must be 16-byte-aligned");

} // namespace detail
#endif /* DEBUG */

} // namespace JS

/*
 * JS::Value and jsval are the same type; jsval is the old name, kept around
 * for backwards compatibility along with all the JSVAL_* operations below.
 * jsval_layout is an implementation detail and should not be used externally.
 */
typedef JS::Value jsval;

MOZ_STATIC_ASSERT(sizeof(jsval_layout) == sizeof(JS::Value),
                  "jsval_layout and JS::Value must have identical layouts");

/************************************************************************/

static inline JSBool
JSVAL_IS_NULL(jsval v)
{
    return JSVAL_IS_NULL_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSBool
JSVAL_IS_VOID(jsval v)
{
    return JSVAL_IS_UNDEFINED_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSBool
JSVAL_IS_INT(jsval v)
{
    return JSVAL_IS_INT32_IMPL(JSVAL_TO_IMPL(v));
}

static inline int32_t
JSVAL_TO_INT(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_INT(v));
    return JSVAL_TO_INT32_IMPL(JSVAL_TO_IMPL(v));
}

static inline jsval
INT_TO_JSVAL(int32_t i)
{
    return IMPL_TO_JSVAL(INT32_TO_JSVAL_IMPL(i));
}

static inline JSBool
JSVAL_IS_DOUBLE(jsval v)
{
    return JSVAL_IS_DOUBLE_IMPL(JSVAL_TO_IMPL(v));
}

static inline double
JSVAL_TO_DOUBLE(jsval v)
{
    jsval_layout l;
    MOZ_ASSERT(JSVAL_IS_DOUBLE(v));
    l = JSVAL_TO_IMPL(v);
    return l.asDouble;
}

static inline jsval
DOUBLE_TO_JSVAL(double d)
{
    /*
     * This is a manually inlined version of:
     *    d = JS_CANONICALIZE_NAN(d);
     *    return IMPL_TO_JSVAL(DOUBLE_TO_JSVAL_IMPL(d));
     * because GCC from XCode 3.1.4 miscompiles the above code.
     */
    jsval_layout l;
    if (MOZ_UNLIKELY(d != d))
        l.asBits = 0x7FF8000000000000LL;
    else
        l.asDouble = d;
    return IMPL_TO_JSVAL(l);
}

static inline jsval
UINT_TO_JSVAL(uint32_t i)
{
    if (i <= JSVAL_INT_MAX)
        return INT_TO_JSVAL((int32_t)i);
    return DOUBLE_TO_JSVAL((double)i);
}

static inline JSBool
JSVAL_IS_NUMBER(jsval v)
{
    return JSVAL_IS_NUMBER_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSBool
JSVAL_IS_STRING(jsval v)
{
    return JSVAL_IS_STRING_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSString *
JSVAL_TO_STRING(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_STRING(v));
    return JSVAL_TO_STRING_IMPL(JSVAL_TO_IMPL(v));
}

static inline jsval
STRING_TO_JSVAL(JSString *str)
{
    return IMPL_TO_JSVAL(STRING_TO_JSVAL_IMPL(str));
}

static inline JSObject *
JSVAL_TO_OBJECT(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_OBJECT_OR_NULL_IMPL(JSVAL_TO_IMPL(v)));
    return JSVAL_TO_OBJECT_IMPL(JSVAL_TO_IMPL(v));
}

static inline jsval
OBJECT_TO_JSVAL(JSObject *obj)
{
    if (obj)
        return IMPL_TO_JSVAL(OBJECT_TO_JSVAL_IMPL(obj));
    return IMPL_TO_JSVAL(BUILD_JSVAL(JSVAL_TAG_NULL, 0));
}

static inline JSBool
JSVAL_IS_BOOLEAN(jsval v)
{
    return JSVAL_IS_BOOLEAN_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSBool
JSVAL_TO_BOOLEAN(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_BOOLEAN(v));
    return JSVAL_TO_BOOLEAN_IMPL(JSVAL_TO_IMPL(v));
}

static inline jsval
BOOLEAN_TO_JSVAL(JSBool b)
{
    return IMPL_TO_JSVAL(BOOLEAN_TO_JSVAL_IMPL(b));
}

static inline JSBool
JSVAL_IS_PRIMITIVE(jsval v)
{
    return JSVAL_IS_PRIMITIVE_IMPL(JSVAL_TO_IMPL(v));
}

static inline JSBool
JSVAL_IS_GCTHING(jsval v)
{
    return JSVAL_IS_GCTHING_IMPL(JSVAL_TO_IMPL(v));
}

static inline void *
JSVAL_TO_GCTHING(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_GCTHING(v));
    return JSVAL_TO_GCTHING_IMPL(JSVAL_TO_IMPL(v));
}

/* To be GC-safe, privates are tagged as doubles. */

static inline jsval
PRIVATE_TO_JSVAL(void *ptr)
{
    return IMPL_TO_JSVAL(PRIVATE_PTR_TO_JSVAL_IMPL(ptr));
}

static inline void *
JSVAL_TO_PRIVATE(jsval v)
{
    MOZ_ASSERT(JSVAL_IS_DOUBLE(v));
    return JSVAL_TO_PRIVATE_PTR_IMPL(JSVAL_TO_IMPL(v));
}

#endif /* js_Value_h___ */
