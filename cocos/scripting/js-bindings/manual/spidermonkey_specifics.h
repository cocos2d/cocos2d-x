/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
#include "mozilla/Maybe.h"
#include <unordered_map>

// Probably we can get rid of this struct, but since a lot of code
// depends on it, we cannot remove it easily
typedef struct js_proxy {
    /** the native object. usually a pointer to cocos2d::Ref, but could be a pointer to another object */
    void *ptr;
    /** the JS object, as a heap object. Required by GC best practices */
    JS::Heap<JSObject*> obj;
    /** This is the raw pointer. The same as the "obj", but 'raw'. This is needed
     because under certain circumstances JS::RemoveRootObject will be called on "obj"
     and "obj" will became NULL. Which is not Ok if we need to use "obj" later for other stuff
     */
    JSObject* _jsobj;
} js_proxy_t;


class ScriptingRootHolder
{
public:
    ScriptingRootHolder(JS::PersistentRootedObject* ptr)
    {
        set(ptr);
    }
    
    void set(JS::PersistentRootedObject* k)
    {
        p = k;
    }
    
    JSObject* ref()
    {
        return *p;
    }
    
    JS::PersistentRootedObject* ptr()
    {
        return p;
    }
    
private:
    JS::PersistentRootedObject* p;
};

typedef struct js_type_class {
    JSClass *jsclass;
    ScriptingRootHolder proto;
    ScriptingRootHolder parentProto;
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


#define TEST_NATIVE_OBJECT(cx, native_obj) \
if (!native_obj) { \
    JS_ReportError(cx, "Invalid Native Object"); \
    return false; \
}

#endif
