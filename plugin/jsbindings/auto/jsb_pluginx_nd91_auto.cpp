#include "jsb_pluginx_nd91_auto.hpp"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_basic_conversions.h"
using namespace pluginx;
#include "IAPNd91.h"

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


JSClass  *jsb_IAPNd91_class;
JSObject *jsb_IAPNd91_prototype;

JSBool js_pluginx_nd91_IAPNd91_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TIAPDeveloperInfo arg0;
		ok &= jsval_to_TIAPDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPluginName();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPluginVersion();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->init();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TProductInfo arg0;
		ok &= jsval_to_TProductInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->payForProduct(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getSDKVersion();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_nd91_IAPNd91_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::IAPNd91* cobj = (cocos2d::plugin::IAPNd91 *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_ProtocolIAP_prototype;

void js_pluginx_nd91_IAPNd91_finalize(JSFreeOp *fop, JSObject *obj) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JS_GET_NATIVE_PROXY(jsproxy, obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

//        cocos2d::plugin::IAPNd91 *nobj = static_cast<cocos2d::plugin::IAPNd91 *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

void js_register_pluginx_nd91_IAPNd91(JSContext *cx, JSObject *global) {
	jsb_IAPNd91_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_IAPNd91_class->name = "IAPNd91";
	jsb_IAPNd91_class->addProperty = JS_PropertyStub;
	jsb_IAPNd91_class->delProperty = JS_PropertyStub;
	jsb_IAPNd91_class->getProperty = JS_PropertyStub;
	jsb_IAPNd91_class->setProperty = JS_StrictPropertyStub;
	jsb_IAPNd91_class->enumerate = JS_EnumerateStub;
	jsb_IAPNd91_class->resolve = JS_ResolveStub;
	jsb_IAPNd91_class->convert = JS_ConvertStub;
	jsb_IAPNd91_class->finalize = js_pluginx_nd91_IAPNd91_finalize;
	jsb_IAPNd91_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("configDeveloperInfo", js_pluginx_nd91_IAPNd91_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginName", js_pluginx_nd91_IAPNd91_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_pluginx_nd91_IAPNd91_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_pluginx_nd91_IAPNd91_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("payForProduct", js_pluginx_nd91_IAPNd91_payForProduct, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_pluginx_nd91_IAPNd91_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_pluginx_nd91_IAPNd91_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_IAPNd91_prototype = JS_InitClass(
		cx, global,
		jsb_ProtocolIAP_prototype,
		jsb_IAPNd91_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "IAPNd91", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::IAPNd91> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_IAPNd91_class;
		p->proto = jsb_IAPNd91_prototype;
		p->parentProto = jsb_ProtocolIAP_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_pluginx_nd91(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "plugin", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "plugin", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_pluginx_nd91_IAPNd91(cx, obj);
}

