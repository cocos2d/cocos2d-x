/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A higher-order macro for enumerating all JSProtoKey values. */

#ifndef jsprototypes_h___
#define jsprototypes_h___

#include "jsversion.h"

/*
 * Enumerator codes in the second column must not change -- they are part of
 * the JS XDR API.  Also note the symbols in the third column are extern "C";
 * clients should use extern "C" {} as appropriate when using this macro.
 */

#define JS_FOR_EACH_PROTOTYPE(macro) \
    macro(Null,                   0,     js_InitNullClass) \
    macro(Object,                 1,     js_InitObjectClass) \
    macro(Function,               2,     js_InitFunctionClass) \
    macro(Array,                  3,     js_InitArrayClass) \
    macro(Boolean,                4,     js_InitBooleanClass) \
    macro(JSON,                   5,     js_InitJSONClass) \
    macro(Date,                   6,     js_InitDateClass) \
    macro(Math,                   7,     js_InitMathClass) \
    macro(Number,                 8,     js_InitNumberClass) \
    macro(String,                 9,     js_InitStringClass) \
    macro(RegExp,                10,     js_InitRegExpClass) \
    macro(XML,                   11,     js_InitXMLClass) \
    macro(Namespace,             12,     js_InitNamespaceClass) \
    macro(QName,                 13,     js_InitQNameClass) \
    macro(Error,                 14,     js_InitExceptionClasses) \
    macro(InternalError,         15,     js_InitExceptionClasses) \
    macro(EvalError,             16,     js_InitExceptionClasses) \
    macro(RangeError,            17,     js_InitExceptionClasses) \
    macro(ReferenceError,        18,     js_InitExceptionClasses) \
    macro(SyntaxError,           19,     js_InitExceptionClasses) \
    macro(TypeError,             20,     js_InitExceptionClasses) \
    macro(URIError,              21,     js_InitExceptionClasses) \
    macro(Iterator,              22,     js_InitIteratorClasses) \
    macro(StopIteration,         23,     js_InitIteratorClasses) \
    macro(ArrayBuffer,           24,     js_InitTypedArrayClasses) \
    macro(Int8Array,             25,     js_InitTypedArrayClasses) \
    macro(Uint8Array,            26,     js_InitTypedArrayClasses) \
    macro(Int16Array,            27,     js_InitTypedArrayClasses) \
    macro(Uint16Array,           28,     js_InitTypedArrayClasses) \
    macro(Int32Array,            29,     js_InitTypedArrayClasses) \
    macro(Uint32Array,           30,     js_InitTypedArrayClasses) \
    macro(Float32Array,          31,     js_InitTypedArrayClasses) \
    macro(Float64Array,          32,     js_InitTypedArrayClasses) \
    macro(Uint8ClampedArray,     33,     js_InitTypedArrayClasses) \
    macro(Proxy,                 34,     js_InitProxyClass) \
    macro(AnyName,               35,     js_InitNullClass) \
    macro(WeakMap,               36,     js_InitWeakMapClass) \
    macro(Map,                   37,     js_InitMapClass) \
    macro(Set,                   38,     js_InitSetClass) \
    macro(DataView,              39,     js_InitTypedArrayClasses) \
    macro(ParallelArray,         40,     js_InitParallelArrayClass) \
    macro(Intl,                  41,     js_InitIntlClass) \

#endif /* jsprototypes_h___ */
