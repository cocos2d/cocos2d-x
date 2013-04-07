#include "jsb_cocos2dx_other_auto.hpp"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_basic_conversions.h"
using namespace pluginx;
#include "cocos2d.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_CCApplicationProtocol_class;
JSObject *jsb_CCApplicationProtocol_prototype;

JSBool js_cocos2dx_other_CCApplicationProtocol_getTargetPlatform(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplicationProtocol* cobj = (cocos2d::CCApplicationProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::TargetPlatform ret = cobj->getTargetPlatform();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_other_CCApplicationProtocol_getCurrentLanguage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplicationProtocol* cobj = (cocos2d::CCApplicationProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::ccLanguageType ret = cobj->getCurrentLanguage();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_other_CCApplicationProtocol_setAnimationInterval(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplicationProtocol* cobj = (cocos2d::CCApplicationProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setAnimationInterval(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}



void js_cocos2dx_other_CCApplicationProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JS_GET_NATIVE_PROXY(jsproxy, obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

//        cocos2d::CCApplicationProtocol *nobj = static_cast<cocos2d::CCApplicationProtocol *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

void js_register_cocos2dx_other_CCApplicationProtocol(JSContext *cx, JSObject *global) {
	jsb_CCApplicationProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCApplicationProtocol_class->name = "ApplicationProtocol";
	jsb_CCApplicationProtocol_class->addProperty = JS_PropertyStub;
	jsb_CCApplicationProtocol_class->delProperty = JS_PropertyStub;
	jsb_CCApplicationProtocol_class->getProperty = JS_PropertyStub;
	jsb_CCApplicationProtocol_class->setProperty = JS_StrictPropertyStub;
	jsb_CCApplicationProtocol_class->enumerate = JS_EnumerateStub;
	jsb_CCApplicationProtocol_class->resolve = JS_ResolveStub;
	jsb_CCApplicationProtocol_class->convert = JS_ConvertStub;
	jsb_CCApplicationProtocol_class->finalize = js_cocos2dx_other_CCApplicationProtocol_finalize;
	jsb_CCApplicationProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("getTargetPlatform", js_cocos2dx_other_CCApplicationProtocol_getTargetPlatform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrentLanguage", js_cocos2dx_other_CCApplicationProtocol_getCurrentLanguage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAnimationInterval", js_cocos2dx_other_CCApplicationProtocol_setAnimationInterval, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_CCApplicationProtocol_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCApplicationProtocol_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ApplicationProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::CCApplicationProtocol> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCApplicationProtocol_class;
		p->proto = jsb_CCApplicationProtocol_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCApplication_class;
JSObject *jsb_CCApplication_prototype;

JSBool js_cocos2dx_other_CCApplication_getTargetPlatform(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplication* cobj = (cocos2d::CCApplication *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::TargetPlatform ret = cobj->getTargetPlatform();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_other_CCApplication_setAnimationInterval(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplication* cobj = (cocos2d::CCApplication *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		double arg0;
		ok &= JS_ValueToNumber(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setAnimationInterval(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_cocos2dx_other_CCApplication_getCurrentLanguage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::CCApplication* cobj = (cocos2d::CCApplication *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::ccLanguageType ret = cobj->getCurrentLanguage();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_cocos2dx_other_CCApplication_sharedApplication(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::CCApplication* ret = cocos2d::CCApplication::sharedApplication();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCApplication>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}



extern JSObject *jsb_CCApplicationProtocol_prototype;

void js_cocos2dx_other_CCApplication_finalize(JSFreeOp *fop, JSObject *obj) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JS_GET_NATIVE_PROXY(jsproxy, obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

//        cocos2d::CCApplication *nobj = static_cast<cocos2d::CCApplication *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

void js_register_cocos2dx_other_CCApplication(JSContext *cx, JSObject *global) {
	jsb_CCApplication_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCApplication_class->name = "Application";
	jsb_CCApplication_class->addProperty = JS_PropertyStub;
	jsb_CCApplication_class->delProperty = JS_PropertyStub;
	jsb_CCApplication_class->getProperty = JS_PropertyStub;
	jsb_CCApplication_class->setProperty = JS_StrictPropertyStub;
	jsb_CCApplication_class->enumerate = JS_EnumerateStub;
	jsb_CCApplication_class->resolve = JS_ResolveStub;
	jsb_CCApplication_class->convert = JS_ConvertStub;
	jsb_CCApplication_class->finalize = js_cocos2dx_other_CCApplication_finalize;
	jsb_CCApplication_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("getTargetPlatform", js_cocos2dx_other_CCApplication_getTargetPlatform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAnimationInterval", js_cocos2dx_other_CCApplication_setAnimationInterval, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrentLanguage", js_cocos2dx_other_CCApplication_getCurrentLanguage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("getInstance", js_cocos2dx_other_CCApplication_sharedApplication, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCApplication_prototype = JS_InitClass(
		cx, global,
		jsb_CCApplicationProtocol_prototype,
		jsb_CCApplication_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Application", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::CCApplication> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCApplication_class;
		p->proto = jsb_CCApplication_prototype;
		p->parentProto = jsb_CCApplicationProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_cocos2dx_other(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_cocos2dx_other_CCApplicationProtocol(cx, obj);
	js_register_cocos2dx_other_CCApplication(cx, obj);
}

