/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla SpiderMonkey JavaScript 1.9 code, released
 * June 30, 2010
 *
 * The Initial Developer of the Original Code is
 *   the Mozilla Corporation.
 *
 * Contributor(s):
 *   Luke Wagner <lw@mozilla.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef jsvalimpl_h__
#define jsvalimpl_h__

/*
 * Implementation details for js::Value in jsapi.h.
 */

#include "mozilla/FloatingPoint.h"

#include "js/Utility.h"

JS_BEGIN_EXTERN_C

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

#define JSVAL_LOWER_INCL_SHIFTED_TAG_OF_OBJ_OR_NULL_SET  JSVAL_SHIFTED_TAG_NULL
#define JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_PRIMITIVE_SET    JSVAL_SHIFTED_TAG_OBJECT
#define JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_NUMBER_SET       JSVAL_SHIFTED_TAG_UNDEFINED
#define JSVAL_LOWER_INCL_SHIFTED_TAG_OF_GCTHING_SET      JSVAL_SHIFTED_TAG_STRING

#endif /* JS_BITS_PER_WORD */

typedef enum JSWhyMagic
{
    JS_ARRAY_HOLE,               /* a hole in a dense array */
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
    JS_UNASSIGNED_ARGUMENTS,     /* the initial value of callobj.arguments */
    JS_OPTIMIZED_ARGUMENTS,      /* optimized-away 'arguments' value */
    JS_IS_CONSTRUCTING,          /* magic value passed to natives to indicate construction */
    JS_OVERWRITTEN_CALLEE,       /* arguments.callee has been overwritten */
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
        } payload;
    } s;
    double asDouble;
    void *asPtr;
    size_t asWord;
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

static JS_ALWAYS_INLINE jsval_layout
BUILD_JSVAL(JSValueTag tag, uint32_t payload)
{
    jsval_layout l;
    l.asBits = (((uint64_t)(uint32_t)tag) << 32) | payload;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_DOUBLE_IMPL(jsval_layout l)
{
    return (uint32_t)l.s.tag <= (uint32_t)JSVAL_TAG_CLEAR;
}

static JS_ALWAYS_INLINE jsval_layout
DOUBLE_TO_JSVAL_IMPL(double d)
{
    jsval_layout l;
    l.asDouble = d;
    JS_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_INT32_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_INT32;
}

static JS_ALWAYS_INLINE int32_t
JSVAL_TO_INT32_IMPL(jsval_layout l)
{
    return l.s.payload.i32;
}

static JS_ALWAYS_INLINE jsval_layout
INT32_TO_JSVAL_IMPL(int32_t i)
{
    jsval_layout l;
    l.s.tag = JSVAL_TAG_INT32;
    l.s.payload.i32 = i;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_NUMBER_IMPL(jsval_layout l)
{
    JSValueTag tag = l.s.tag;
    JS_ASSERT(tag != JSVAL_TAG_CLEAR);
    return (uint32_t)tag <= (uint32_t)JSVAL_UPPER_INCL_TAG_OF_NUMBER_SET;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_UNDEFINED_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_UNDEFINED;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_STRING_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_STRING;
}

static JS_ALWAYS_INLINE jsval_layout
STRING_TO_JSVAL_IMPL(JSString *str)
{
    jsval_layout l;
    JS_ASSERT(str);
    l.s.tag = JSVAL_TAG_STRING;
    l.s.payload.str = str;
    return l;
}

static JS_ALWAYS_INLINE JSString *
JSVAL_TO_STRING_IMPL(jsval_layout l)
{
    return l.s.payload.str;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_BOOLEAN_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_BOOLEAN;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_TO_BOOLEAN_IMPL(jsval_layout l)
{
    return l.s.payload.boo;
}

static JS_ALWAYS_INLINE jsval_layout
BOOLEAN_TO_JSVAL_IMPL(JSBool b)
{
    jsval_layout l;
    JS_ASSERT(b == JS_TRUE || b == JS_FALSE);
    l.s.tag = JSVAL_TAG_BOOLEAN;
    l.s.payload.boo = b;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_MAGIC_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_MAGIC;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_OBJECT_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_OBJECT;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_PRIMITIVE_IMPL(jsval_layout l)
{
    return (uint32_t)l.s.tag < (uint32_t)JSVAL_UPPER_EXCL_TAG_OF_PRIMITIVE_SET;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_OBJECT_OR_NULL_IMPL(jsval_layout l)
{
    JS_ASSERT((uint32_t)l.s.tag <= (uint32_t)JSVAL_TAG_OBJECT);
    return (uint32_t)l.s.tag >= (uint32_t)JSVAL_LOWER_INCL_TAG_OF_OBJ_OR_NULL_SET;
}

static JS_ALWAYS_INLINE JSObject *
JSVAL_TO_OBJECT_IMPL(jsval_layout l)
{
    return l.s.payload.obj;
}

static JS_ALWAYS_INLINE jsval_layout
OBJECT_TO_JSVAL_IMPL(JSObject *obj)
{
    jsval_layout l;
    JS_ASSERT(obj);
    l.s.tag = JSVAL_TAG_OBJECT;
    l.s.payload.obj = obj;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_NULL_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_NULL;
}

static JS_ALWAYS_INLINE jsval_layout
PRIVATE_PTR_TO_JSVAL_IMPL(void *ptr)
{
    jsval_layout l;
    JS_ASSERT(((uint32_t)ptr & 1) == 0);
    l.s.tag = (JSValueTag)0;
    l.s.payload.ptr = ptr;
    JS_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static JS_ALWAYS_INLINE void *
JSVAL_TO_PRIVATE_PTR_IMPL(jsval_layout l)
{
    return l.s.payload.ptr;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_GCTHING_IMPL(jsval_layout l)
{
    /* gcc sometimes generates signed < without explicit casts. */
    return (uint32_t)l.s.tag >= (uint32_t)JSVAL_LOWER_INCL_TAG_OF_GCTHING_SET;
}

static JS_ALWAYS_INLINE void *
JSVAL_TO_GCTHING_IMPL(jsval_layout l)
{
    return l.s.payload.ptr;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_TRACEABLE_IMPL(jsval_layout l)
{
    return l.s.tag == JSVAL_TAG_STRING || l.s.tag == JSVAL_TAG_OBJECT;
}

static JS_ALWAYS_INLINE uint32_t
JSVAL_TRACE_KIND_IMPL(jsval_layout l)
{
    return (uint32_t)(JSBool)JSVAL_IS_STRING_IMPL(l);
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_SPECIFIC_INT32_IMPL(jsval_layout l, int32_t i32)
{
    return l.s.tag == JSVAL_TAG_INT32 && l.s.payload.i32 == i32;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_SPECIFIC_BOOLEAN(jsval_layout l, JSBool b)
{
    return (l.s.tag == JSVAL_TAG_BOOLEAN) && (l.s.payload.boo == b);
}

static JS_ALWAYS_INLINE jsval_layout
MAGIC_TO_JSVAL_IMPL(JSWhyMagic why)
{
    jsval_layout l;
    l.s.tag = JSVAL_TAG_MAGIC;
    l.s.payload.why = why;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_SAME_TYPE_IMPL(jsval_layout lhs, jsval_layout rhs)
{
    JSValueTag ltag = lhs.s.tag, rtag = rhs.s.tag;
    return ltag == rtag || (ltag < JSVAL_TAG_CLEAR && rtag < JSVAL_TAG_CLEAR);
}

static JS_ALWAYS_INLINE jsval_layout
PRIVATE_UINT32_TO_JSVAL_IMPL(uint32_t ui)
{
    jsval_layout l;
    l.s.tag = (JSValueTag)0;
    l.s.payload.u32 = ui;
    JS_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static JS_ALWAYS_INLINE uint32_t
JSVAL_TO_PRIVATE_UINT32_IMPL(jsval_layout l)
{
    return l.s.payload.u32;
}

static JS_ALWAYS_INLINE JSValueType
JSVAL_EXTRACT_NON_DOUBLE_TYPE_IMPL(jsval_layout l)
{
    uint32_t type = l.s.tag & 0xF;
    JS_ASSERT(type > JSVAL_TYPE_DOUBLE);
    return (JSValueType)type;
}

#elif JS_BITS_PER_WORD == 64

static JS_ALWAYS_INLINE jsval_layout
BUILD_JSVAL(JSValueTag tag, uint64_t payload)
{
    jsval_layout l;
    l.asBits = (((uint64_t)(uint32_t)tag) << JSVAL_TAG_SHIFT) | payload;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_DOUBLE_IMPL(jsval_layout l)
{
    return l.asBits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE;
}

static JS_ALWAYS_INLINE jsval_layout
DOUBLE_TO_JSVAL_IMPL(double d)
{
    jsval_layout l;
    l.asDouble = d;
    JS_ASSERT(l.asBits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE);
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_INT32_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_INT32;
}

static JS_ALWAYS_INLINE int32_t
JSVAL_TO_INT32_IMPL(jsval_layout l)
{
    return (int32_t)l.asBits;
}

static JS_ALWAYS_INLINE jsval_layout
INT32_TO_JSVAL_IMPL(int32_t i32)
{
    jsval_layout l;
    l.asBits = ((uint64_t)(uint32_t)i32) | JSVAL_SHIFTED_TAG_INT32;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_NUMBER_IMPL(jsval_layout l)
{
    return l.asBits < JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_NUMBER_SET;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_UNDEFINED_IMPL(jsval_layout l)
{
    return l.asBits == JSVAL_SHIFTED_TAG_UNDEFINED;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_STRING_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_STRING;
}

static JS_ALWAYS_INLINE jsval_layout
STRING_TO_JSVAL_IMPL(JSString *str)
{
    jsval_layout l;
    uint64_t strBits = (uint64_t)str;
    JS_ASSERT(str);
    JS_ASSERT((strBits >> JSVAL_TAG_SHIFT) == 0);
    l.asBits = strBits | JSVAL_SHIFTED_TAG_STRING;
    return l;
}

static JS_ALWAYS_INLINE JSString *
JSVAL_TO_STRING_IMPL(jsval_layout l)
{
    return (JSString *)(l.asBits & JSVAL_PAYLOAD_MASK);
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_BOOLEAN_IMPL(jsval_layout l)
{
    return (uint32_t)(l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_BOOLEAN;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_TO_BOOLEAN_IMPL(jsval_layout l)
{
    return (JSBool)l.asBits;
}

static JS_ALWAYS_INLINE jsval_layout
BOOLEAN_TO_JSVAL_IMPL(JSBool b)
{
    jsval_layout l;
    JS_ASSERT(b == JS_TRUE || b == JS_FALSE);
    l.asBits = ((uint64_t)(uint32_t)b) | JSVAL_SHIFTED_TAG_BOOLEAN;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_MAGIC_IMPL(jsval_layout l)
{
    return (l.asBits >> JSVAL_TAG_SHIFT) == JSVAL_TAG_MAGIC;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_PRIMITIVE_IMPL(jsval_layout l)
{
    return l.asBits < JSVAL_UPPER_EXCL_SHIFTED_TAG_OF_PRIMITIVE_SET;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_OBJECT_IMPL(jsval_layout l)
{
    JS_ASSERT((l.asBits >> JSVAL_TAG_SHIFT) <= JSVAL_SHIFTED_TAG_OBJECT);
    return l.asBits >= JSVAL_SHIFTED_TAG_OBJECT;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_OBJECT_OR_NULL_IMPL(jsval_layout l)
{
    JS_ASSERT((l.asBits >> JSVAL_TAG_SHIFT) <= JSVAL_TAG_OBJECT);
    return l.asBits >= JSVAL_LOWER_INCL_SHIFTED_TAG_OF_OBJ_OR_NULL_SET;
}

static JS_ALWAYS_INLINE JSObject *
JSVAL_TO_OBJECT_IMPL(jsval_layout l)
{
    uint64_t ptrBits = l.asBits & JSVAL_PAYLOAD_MASK;
    JS_ASSERT((ptrBits & 0x7) == 0);
    return (JSObject *)ptrBits;
}

static JS_ALWAYS_INLINE jsval_layout
OBJECT_TO_JSVAL_IMPL(JSObject *obj)
{
    jsval_layout l;
    uint64_t objBits = (uint64_t)obj;
    JS_ASSERT(obj);
    JS_ASSERT((objBits >> JSVAL_TAG_SHIFT) == 0);
    l.asBits = objBits | JSVAL_SHIFTED_TAG_OBJECT;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_NULL_IMPL(jsval_layout l)
{
    return l.asBits == JSVAL_SHIFTED_TAG_NULL;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_GCTHING_IMPL(jsval_layout l)
{
    return l.asBits >= JSVAL_LOWER_INCL_SHIFTED_TAG_OF_GCTHING_SET;
}

static JS_ALWAYS_INLINE void *
JSVAL_TO_GCTHING_IMPL(jsval_layout l)
{
    uint64_t ptrBits = l.asBits & JSVAL_PAYLOAD_MASK;
    JS_ASSERT((ptrBits & 0x7) == 0);
    return (void *)ptrBits;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_TRACEABLE_IMPL(jsval_layout l)
{
    return JSVAL_IS_GCTHING_IMPL(l) && !JSVAL_IS_NULL_IMPL(l);
}

static JS_ALWAYS_INLINE uint32_t
JSVAL_TRACE_KIND_IMPL(jsval_layout l)
{
    return (uint32_t)(JSBool)!(JSVAL_IS_OBJECT_IMPL(l));
}

static JS_ALWAYS_INLINE jsval_layout
PRIVATE_PTR_TO_JSVAL_IMPL(void *ptr)
{
    jsval_layout l;
    uint64_t ptrBits = (uint64_t)ptr;
    JS_ASSERT((ptrBits & 1) == 0);
    l.asBits = ptrBits >> 1;
    JS_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static JS_ALWAYS_INLINE void *
JSVAL_TO_PRIVATE_PTR_IMPL(jsval_layout l)
{
    JS_ASSERT((l.asBits & 0x8000000000000000LL) == 0);
    return (void *)(l.asBits << 1);
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_SPECIFIC_INT32_IMPL(jsval_layout l, int32_t i32)
{
    return l.asBits == (((uint64_t)(uint32_t)i32) | JSVAL_SHIFTED_TAG_INT32);
}

static JS_ALWAYS_INLINE JSBool
JSVAL_IS_SPECIFIC_BOOLEAN(jsval_layout l, JSBool b)
{
    return l.asBits == (((uint64_t)(uint32_t)b) | JSVAL_SHIFTED_TAG_BOOLEAN);
}

static JS_ALWAYS_INLINE jsval_layout
MAGIC_TO_JSVAL_IMPL(JSWhyMagic why)
{
    jsval_layout l;
    l.asBits = ((uint64_t)(uint32_t)why) | JSVAL_SHIFTED_TAG_MAGIC;
    return l;
}

static JS_ALWAYS_INLINE JSBool
JSVAL_SAME_TYPE_IMPL(jsval_layout lhs, jsval_layout rhs)
{
    uint64_t lbits = lhs.asBits, rbits = rhs.asBits;
    return (lbits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE && rbits <= JSVAL_SHIFTED_TAG_MAX_DOUBLE) ||
           (((lbits ^ rbits) & 0xFFFF800000000000LL) == 0);
}

static JS_ALWAYS_INLINE jsval_layout
PRIVATE_UINT32_TO_JSVAL_IMPL(uint32_t ui)
{
    jsval_layout l;
    l.asBits = (uint64_t)ui;
    JS_ASSERT(JSVAL_IS_DOUBLE_IMPL(l));
    return l;
}

static JS_ALWAYS_INLINE uint32_t
JSVAL_TO_PRIVATE_UINT32_IMPL(jsval_layout l)
{
    JS_ASSERT((l.asBits >> 32) == 0);
    return (uint32_t)l.asBits;
}

static JS_ALWAYS_INLINE JSValueType
JSVAL_EXTRACT_NON_DOUBLE_TYPE_IMPL(jsval_layout l)
{
   uint64_t type = (l.asBits >> JSVAL_TAG_SHIFT) & 0xF;
   JS_ASSERT(type > JSVAL_TYPE_DOUBLE);
   return (JSValueType)type;
}

#endif  /* JS_BITS_PER_WORD */

static JS_ALWAYS_INLINE double
JS_CANONICALIZE_NAN(double d)
{
    if (JS_UNLIKELY(d != d)) {
        jsval_layout l;
        l.asBits = 0x7FF8000000000000LL;
        return l.asDouble;
    }
    return d;
}

JS_END_EXTERN_C

#ifdef __cplusplus
static jsval_layout JSVAL_TO_IMPL(JS::Value);
static JS::Value IMPL_TO_JSVAL(jsval_layout);
#endif

#endif /* jsvalimpl_h__ */
