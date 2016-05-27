/*
 * Copyright (c) 2012 Zynga Inc.
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
#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/js_bindings_core.h"

// cocos2d + chipmunk registration files
#include "scripting/js-bindings/manual/chipmunk/js_bindings_chipmunk_registration.h"

#include "base/ccMacros.h"
#include "base/uthash.h"

//#pragma mark - Hash

typedef struct _hashJSObject
{
    JSObject            *jsObject;
    void                *proxy;
    UT_hash_handle      hh;
} tHashJSObject;

static tHashJSObject *hash = NULL;
static tHashJSObject *reverse_hash = NULL;

//#pragma mark JSBCore - Helper free functions
static void reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    fprintf(stderr, "%s:%u:%s\n",
            report->filename ? report->filename : "<no filename=\"filename\">",
            (unsigned int) report->lineno,
            message);
};


// Hash of JSObject -> proxy
void* jsb_get_proxy_for_jsobject(JSObject *obj)
{
    tHashJSObject *element = NULL;
    HASH_FIND_PTR(hash, &obj, element);

    if( element )
        return element->proxy;
    return NULL;
}

void jsb_set_proxy_for_jsobject(void *proxy, JSObject *obj)
{
    CCASSERT( !jsb_get_proxy_for_jsobject(obj), "Already added. abort");

//  printf("Setting proxy for: %p - %p (%s)\n", obj, proxy, [[proxy description] UTF8String] );

    tHashJSObject *element = (tHashJSObject*) malloc( sizeof( *element ) );

    // XXX: Do not retain it here.
//  [proxy retain];
    element->proxy = proxy;
    element->jsObject = obj;

    HASH_ADD_PTR( hash, jsObject, element );
}

void jsb_del_proxy_for_jsobject(JSObject *obj)
{
    tHashJSObject *element = NULL;
    HASH_FIND_PTR(hash, &obj, element);
    if( element ) {
        HASH_DEL(hash, element);
        free(element);
    }
}

//#pragma mark Proxy -> JSObject

// Reverse hash: Proxy -> JSObject
JSObject* jsb_get_jsobject_for_proxy(void *proxy)
{
    tHashJSObject *element = NULL;
    HASH_FIND_PTR(reverse_hash, &proxy, element);

    if( element )
        return element->jsObject;
    return NULL;
}

void jsb_set_jsobject_for_proxy(JSObject *jsobj, void* proxy)
{
    CCASSERT( !jsb_get_jsobject_for_proxy(proxy), "Already added. abort");

    tHashJSObject *element = (tHashJSObject*) malloc( sizeof( *element ) );

    element->proxy = proxy;
    element->jsObject = jsobj;

    HASH_ADD_PTR( reverse_hash, proxy, element );
}

void jsb_del_jsobject_for_proxy(void* proxy)
{
    tHashJSObject *element = NULL;
    HASH_FIND_PTR(reverse_hash, &proxy, element);
    if( element ) {
        HASH_DEL(reverse_hash, element);
        free(element);
    }
}

//#pragma mark


//#pragma mark "C" proxy functions

struct jsb_c_proxy_s* jsb_get_c_proxy_for_jsobject( JSObject *jsobj )
{
    struct jsb_c_proxy_s *proxy = (struct jsb_c_proxy_s *) JS_GetPrivate(jsobj);

    return proxy;
}

void jsb_del_c_proxy_for_jsobject( JSObject *jsobj )
{
    struct jsb_c_proxy_s *proxy = (struct jsb_c_proxy_s *) JS_GetPrivate(jsobj);
    CCASSERT(proxy, "Invalid proxy for JSObject");
    JS_SetPrivate(jsobj, NULL);

    free(proxy);
}

void jsb_set_c_proxy_for_jsobject( JSObject *jsobj, void *handle, unsigned long flags)
{
    struct jsb_c_proxy_s *proxy = (struct jsb_c_proxy_s*) malloc(sizeof(*proxy));
    CCASSERT(proxy, "No memory for proxy");

    proxy->handle = handle;
    proxy->flags = flags;
    proxy->jsobj = jsobj;

    JS_SetPrivate(jsobj, proxy);
}


//#pragma mark Do Nothing - Callbacks

bool JSB_do_nothing(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setUndefined();
    return true;
}
