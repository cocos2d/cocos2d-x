#ifndef __SPIDERMONKEY_SPECIFICS_H__
#define __SPIDERMONKEY_SPECIFICS_H__

#include "jsapi.h"
#include "uthash.h"
#include <unordered_map>

typedef struct js_proxy {
	void *ptr;
	JSObject *obj;
	UT_hash_handle hh;
} js_proxy_t;

extern js_proxy_t *_native_js_global_ht;
extern js_proxy_t *_js_native_global_ht;

typedef struct js_type_class {
	JSClass *jsclass;
	JSObject *proto;
	JSObject *parentProto;
} js_type_class_t;

extern std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;

template< typename DERIVED >
class TypeTest
{
public:
	static const char* s_name()
	{
		// return id unique for DERIVED
		// ALWAYS VALID BUT STRING, NOT INT - BUT VALID AND CROSS-PLATFORM/CROSS-VERSION COMPATBLE
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
	return JS_FALSE; \
}

#endif
