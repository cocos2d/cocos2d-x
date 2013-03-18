/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2012 Zynga Inc.
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
#include "js_bindings_config.h"
#include "js_bindings_core.h"


// cocos2d + chipmunk registration files
#include "js_bindings_chipmunk_registration.h"


//#pragma mark - Hash

using namespace cocos2d;

typedef struct _hashJSObject
{
	JSObject			*jsObject;
	void				*proxy;
	UT_hash_handle		hh;
} tHashJSObject;

static tHashJSObject *hash = NULL;
static tHashJSObject *reverse_hash = NULL;

// Globals
char* JSB_association_proxy_key = NULL;

const char* JSB_version = "0.3-beta";


static void its_finalize(JSFreeOp *fop, JSObject *obj)
{
	CCLOGINFO("Finalizing global class");
}

static JSClass global_class = {
	"__global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub,
	JS_PropertyStub, JS_StrictPropertyStub,
	JS_EnumerateStub, JS_ResolveStub,
	JS_ConvertStub, its_finalize,
	JSCLASS_NO_OPTIONAL_MEMBERS
};

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
	HASH_FIND_INT(hash, &obj, element);
	
	if( element )
		return element->proxy;
	return NULL;
}

void jsb_set_proxy_for_jsobject(void *proxy, JSObject *obj)
{
	CCAssert( !jsb_get_proxy_for_jsobject(obj), "Already added. abort");
	
//	printf("Setting proxy for: %p - %p (%s)\n", obj, proxy, [[proxy description] UTF8String] );
	
	tHashJSObject *element = (tHashJSObject*) malloc( sizeof( *element ) );

	// XXX: Do not retain it here.
//	[proxy retain];
	element->proxy = proxy;
	element->jsObject = obj;

	HASH_ADD_INT( hash, jsObject, element );
}

void jsb_del_proxy_for_jsobject(JSObject *obj)
{
	tHashJSObject *element = NULL;
	HASH_FIND_INT(hash, &obj, element);
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
	HASH_FIND_INT(reverse_hash, &proxy, element);
	
	if( element )
		return element->jsObject;
	return NULL;
}

void jsb_set_jsobject_for_proxy(JSObject *jsobj, void* proxy)
{
	CCAssert( !jsb_get_jsobject_for_proxy(proxy), "Already added. abort");
	
	tHashJSObject *element = (tHashJSObject*) malloc( sizeof( *element ) );
	
	element->proxy = proxy;
	element->jsObject = jsobj;
	
	HASH_ADD_INT( reverse_hash, proxy, element );
}

void jsb_del_jsobject_for_proxy(void* proxy)
{
	tHashJSObject *element = NULL;
	HASH_FIND_INT(reverse_hash, &proxy, element);
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
	CCAssert(proxy, "Invalid proxy for JSObject");
	JS_SetPrivate(jsobj, NULL);
	
	free(proxy);
}

void jsb_set_c_proxy_for_jsobject( JSObject *jsobj, void *handle, unsigned long flags)
{
	struct jsb_c_proxy_s *proxy = (struct jsb_c_proxy_s*) malloc(sizeof(*proxy));
	CCAssert(proxy, "No memory for proxy");
	
	proxy->handle = handle;
	proxy->flags = flags;
	proxy->jsobj = jsobj;
	
	JS_SetPrivate(jsobj, proxy);
}


//#pragma mark Do Nothing - Callbacks

JSBool JSB_do_nothing(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}
