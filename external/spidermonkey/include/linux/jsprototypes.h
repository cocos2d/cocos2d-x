/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A higher-order macro for enumerating all JSProtoKey values. */

#ifndef jsprototypes_h
#define jsprototypes_h

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
    macro(Error,                 11,     js_InitExceptionClasses) \
    macro(InternalError,         12,     js_InitExceptionClasses) \
    macro(EvalError,             13,     js_InitExceptionClasses) \
    macro(RangeError,            14,     js_InitExceptionClasses) \
    macro(ReferenceError,        15,     js_InitExceptionClasses) \
    macro(SyntaxError,           16,     js_InitExceptionClasses) \
    macro(TypeError,             17,     js_InitExceptionClasses) \
    macro(URIError,              18,     js_InitExceptionClasses) \
    macro(Iterator,              19,     js_InitIteratorClasses) \
    macro(StopIteration,         20,     js_InitIteratorClasses) \
    macro(ArrayBuffer,           21,     js_InitTypedArrayClasses) \
    macro(Int8Array,             22,     js_InitTypedArrayClasses) \
    macro(Uint8Array,            23,     js_InitTypedArrayClasses) \
    macro(Int16Array,            24,     js_InitTypedArrayClasses) \
    macro(Uint16Array,           25,     js_InitTypedArrayClasses) \
    macro(Int32Array,            26,     js_InitTypedArrayClasses) \
    macro(Uint32Array,           27,     js_InitTypedArrayClasses) \
    macro(Float32Array,          28,     js_InitTypedArrayClasses) \
    macro(Float64Array,          29,     js_InitTypedArrayClasses) \
    macro(Uint8ClampedArray,     30,     js_InitTypedArrayClasses) \
    macro(Proxy,                 31,     js_InitProxyClass) \
    macro(WeakMap,               32,     js_InitWeakMapClass) \
    macro(Map,                   33,     js_InitMapClass) \
    macro(Set,                   34,     js_InitSetClass) \
    macro(DataView,              35,     js_InitTypedArrayClasses) \
    macro(ParallelArray,         36,     js_InitParallelArrayClass) \
    macro(Intl,                  37,     js_InitIntlClass) \
    macro(TypedObject,           38,     js_InitTypedObjectDummy) \
    macro(GeneratorFunction,     39,     js_InitIteratorClasses) \

#endif /* jsprototypes_h */
