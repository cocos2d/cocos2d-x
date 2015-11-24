/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __SPIDERMONKEY_SPECIFICS_H__
#define __SPIDERMONKEY_SPECIFICS_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "uthash.h"
#include <unordered_map>

typedef struct js_proxy {
    void *ptr;
    JS::Heap<JSObject*> obj;
    UT_hash_handle hh;
} js_proxy_t;

extern js_proxy_t *_native_js_global_ht;
extern js_proxy_t *_js_native_global_ht;

typedef struct js_type_class {
    JSClass *jsclass;
    JS::Heap<JSObject*> proto;
    JS::Heap<JSObject*> parentProto;
} js_type_class_t;

extern std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;

template< typename DERIVED >
class TypeTest
{
public:
    static const char* s_name()
    {
        // return id unique for DERIVED
        // ALWAYS VALID BUT STRING, NOT INT - BUT VALID AND CROSS-PLATFORM/CROSS-VERSION COMPATIBLE
        // AS FAR AS YOU KEEP THE CLASS NAME
        return typeid( DERIVED ).name();
    }
};


#define JS_NEW_PROXY(p, native_obj, js_obj) \
do { \
    p = (js_proxy_t *)malloc(sizeof(js_proxy_t)); \
    assert(p); \
    js_proxy_t* native_obj##js_obj##tmp = NULL; \
    HASH_FIND_PTR(_native_js_global_ht, &native_obj, native_obj##js_obj##tmp); \
    assert(!native_obj##js_obj##tmp); \
    p->ptr = native_obj; \
    p->obj = js_obj; \
    HASH_ADD_PTR(_native_js_global_ht, ptr, p); \
    p = (js_proxy_t *)malloc(sizeof(js_proxy_t)); \
    assert(p); \
    native_obj##js_obj##tmp = NULL; \
    HASH_FIND_PTR(_js_native_global_ht, &js_obj, native_obj##js_obj##tmp); \
    assert(!native_obj##js_obj##tmp); \
    p->ptr = native_obj; \
    p->obj = js_obj; \
    HASH_ADD_PTR(_js_native_global_ht, obj, p); \
} while(0) \

#define JS_GET_PROXY(p, native_obj) \
do { \
    HASH_FIND_PTR(_native_js_global_ht, &native_obj, p); \
} while (0)

#define JS_GET_NATIVE_PROXY(p, js_obj) \
do { \
    HASH_FIND_PTR(_js_native_global_ht, &js_obj, p); \
} while (0)

#define JS_REMOVE_PROXY(nproxy, jsproxy) \
do { \
    if (nproxy) { HASH_DEL(_native_js_global_ht, nproxy); free(nproxy); } \
    if (jsproxy) { HASH_DEL(_js_native_global_ht, jsproxy); free(jsproxy); } \
} while (0)

#define TEST_NATIVE_OBJECT(cx, native_obj) \
if (!native_obj) { \
    JS_ReportError(cx, "Invalid Native Object"); \
    return false; \
}

#endif
