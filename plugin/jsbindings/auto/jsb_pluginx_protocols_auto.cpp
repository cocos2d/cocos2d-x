#include "jsb_pluginx_protocols_auto.hpp"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_basic_conversions.h"
using namespace pluginx;
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_PluginProtocol_class;
JSObject *jsb_PluginProtocol_prototype;

JSBool js_pluginx_protocols_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_protocols_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginVersion();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSDKVersion();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
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



void js_pluginx_protocols_PluginProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::PluginProtocol *nobj = static_cast<cocos2d::plugin::PluginProtocol *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_PluginProtocol(JSContext *cx, JSObject *global) {
	jsb_PluginProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginProtocol_class->name = "PluginProtocol";
	jsb_PluginProtocol_class->addProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->delProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->getProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginProtocol_class->enumerate = JS_EnumerateStub;
	jsb_PluginProtocol_class->resolve = JS_ResolveStub;
	jsb_PluginProtocol_class->convert = JS_ConvertStub;
	jsb_PluginProtocol_class->finalize = js_pluginx_protocols_PluginProtocol_finalize;
	jsb_PluginProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getPluginName", js_pluginx_protocols_PluginProtocol_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_pluginx_protocols_PluginProtocol_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_pluginx_protocols_PluginProtocol_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_pluginx_protocols_PluginProtocol_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_PluginProtocol_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginProtocol_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginProtocol> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginProtocol_class;
		p->proto = jsb_PluginProtocol_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_PluginManager_class;
JSObject *jsb_PluginManager_prototype;

JSBool js_pluginx_protocols_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginManager* cobj = (cocos2d::plugin::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->unloadPlugin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginManager* cobj = (cocos2d::plugin::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::plugin::PluginProtocol* ret = cobj->loadPlugin(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::plugin::PluginProtocol>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::plugin::PluginManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_pluginx_protocols_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::plugin::PluginManager* ret = cocos2d::plugin::PluginManager::getInstance();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::plugin::PluginManager>(cx, ret);
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




void js_pluginx_protocols_PluginManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginManager)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::PluginManager *nobj = static_cast<cocos2d::plugin::PluginManager *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_PluginManager(JSContext *cx, JSObject *global) {
	jsb_PluginManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginManager_class->name = "PluginManager";
	jsb_PluginManager_class->addProperty = JS_PropertyStub;
	jsb_PluginManager_class->delProperty = JS_PropertyStub;
	jsb_PluginManager_class->getProperty = JS_PropertyStub;
	jsb_PluginManager_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginManager_class->enumerate = JS_EnumerateStub;
	jsb_PluginManager_class->resolve = JS_ResolveStub;
	jsb_PluginManager_class->convert = JS_ConvertStub;
	jsb_PluginManager_class->finalize = js_pluginx_protocols_PluginManager_finalize;
	jsb_PluginManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("unloadPlugin", js_pluginx_protocols_PluginManager_unloadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadPlugin", js_pluginx_protocols_PluginManager_loadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_pluginx_protocols_PluginManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_pluginx_protocols_PluginManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_PluginManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginManager_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginManager> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginManager_class;
		p->proto = jsb_PluginManager_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolAnalytics_class;
JSObject *jsb_ProtocolAnalytics_prototype;

JSBool js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logTimedEventBegin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		const char* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logError(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setCaptureUncaughtException(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		long arg0;
		ok &= jsval_to_long(cx, argv[0], (long *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setSessionContinueMillis(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logEvent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		LogEventParamMap* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		LogEventParamMap arg1_tmp;
		do {
			ok &= jsval_to_LogEventParamMap(cx, argv[1], &arg1);
			if (ok) { arg1_tmp = *arg1; delete arg1; arg1 = &arg1_tmp; } else { arg1 = NULL; }
		} while(0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logEvent(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->startSession(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->stopSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logTimedEventEnd(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAnalytics)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolAnalytics *nobj = static_cast<cocos2d::plugin::ProtocolAnalytics *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolAnalytics(JSContext *cx, JSObject *global) {
	jsb_ProtocolAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolAnalytics_class->name = "ProtocolAnalytics";
	jsb_ProtocolAnalytics_class->addProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->delProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->getProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolAnalytics_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolAnalytics_class->resolve = JS_ResolveStub;
	jsb_ProtocolAnalytics_class->convert = JS_ConvertStub;
	jsb_ProtocolAnalytics_class->finalize = js_pluginx_protocols_ProtocolAnalytics_finalize;
	jsb_ProtocolAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("logTimedEventBegin", js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logError", js_pluginx_protocols_ProtocolAnalytics_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCaptureUncaughtException", js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSessionContinueMillis", js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logEvent", js_pluginx_protocols_ProtocolAnalytics_logEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startSession", js_pluginx_protocols_ProtocolAnalytics_startSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopSession", js_pluginx_protocols_ProtocolAnalytics_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logTimedEventEnd", js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolAnalytics_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolAnalytics_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolAnalytics> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolAnalytics_class;
		p->proto = jsb_ProtocolAnalytics_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolIAP_class;
JSObject *jsb_ProtocolIAP_prototype;

JSBool js_pluginx_protocols_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_protocols_ProtocolIAP_onPayResult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::plugin::PayResultCode arg0;
		const char* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->onPayResult(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolIAP_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
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


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolIAP_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolIAP)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolIAP *nobj = static_cast<cocos2d::plugin::ProtocolIAP *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolIAP(JSContext *cx, JSObject *global) {
	jsb_ProtocolIAP_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolIAP_class->name = "ProtocolIAP";
	jsb_ProtocolIAP_class->addProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->delProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->getProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolIAP_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolIAP_class->resolve = JS_ResolveStub;
	jsb_ProtocolIAP_class->convert = JS_ConvertStub;
	jsb_ProtocolIAP_class->finalize = js_pluginx_protocols_ProtocolIAP_finalize;
	jsb_ProtocolIAP_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("payForProduct", js_pluginx_protocols_ProtocolIAP_payForProduct, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onPayResult", js_pluginx_protocols_ProtocolIAP_onPayResult, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolIAP_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolIAP_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolIAP_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolIAP", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolIAP> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolIAP_class;
		p->proto = jsb_ProtocolIAP_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolAds_class;
JSObject *jsb_ProtocolAds_prototype;

JSBool js_pluginx_protocols_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TAdsInfo arg0;
		ok &= jsval_to_TAdsInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->showAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		TAdsInfo arg0;
		cocos2d::plugin::ProtocolAds::AdsPos arg1;
		ok &= jsval_to_TAdsInfo(cx, argv[0], &arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->showAds(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TAdsInfo arg0;
		ok &= jsval_to_TAdsInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->hideAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->queryPoints();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->spendPoints(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAds_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TAdsDeveloperInfo arg0;
		ok &= jsval_to_TAdsDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolAds_getAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::plugin::AdsListener* ret = cobj->getAdsListener();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::plugin::AdsListener>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAds)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolAds *nobj = static_cast<cocos2d::plugin::ProtocolAds *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolAds(JSContext *cx, JSObject *global) {
	jsb_ProtocolAds_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolAds_class->name = "ProtocolAds";
	jsb_ProtocolAds_class->addProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->delProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->getProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolAds_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolAds_class->resolve = JS_ResolveStub;
	jsb_ProtocolAds_class->convert = JS_ConvertStub;
	jsb_ProtocolAds_class->finalize = js_pluginx_protocols_ProtocolAds_finalize;
	jsb_ProtocolAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showAds", js_pluginx_protocols_ProtocolAds_showAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hideAds", js_pluginx_protocols_ProtocolAds_hideAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("queryPoints", js_pluginx_protocols_ProtocolAds_queryPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("spendPoints", js_pluginx_protocols_ProtocolAds_spendPoints, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolAds_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAdsListener", js_pluginx_protocols_ProtocolAds_getAdsListener, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolAds_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolAds_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolAds> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolAds_class;
		p->proto = jsb_ProtocolAds_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolShare_class;
JSObject *jsb_ProtocolShare_prototype;

JSBool js_pluginx_protocols_ProtocolShare_onShareResult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::plugin::ShareResultCode arg0;
		const char* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->onShareResult(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TShareInfo arg0;
		ok &= jsval_to_TShareInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->share(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolShare_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TShareDeveloperInfo arg0;
		ok &= jsval_to_TShareDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolShare_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolShare)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolShare *nobj = static_cast<cocos2d::plugin::ProtocolShare *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolShare(JSContext *cx, JSObject *global) {
	jsb_ProtocolShare_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolShare_class->name = "ProtocolShare";
	jsb_ProtocolShare_class->addProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->delProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->getProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolShare_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolShare_class->resolve = JS_ResolveStub;
	jsb_ProtocolShare_class->convert = JS_ConvertStub;
	jsb_ProtocolShare_class->finalize = js_pluginx_protocols_ProtocolShare_finalize;
	jsb_ProtocolShare_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("onShareResult", js_pluginx_protocols_ProtocolShare_onShareResult, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("share", js_pluginx_protocols_ProtocolShare_share, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolShare_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolShare_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolShare_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolShare", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolShare> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolShare_class;
		p->proto = jsb_ProtocolShare_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolSocial_class;
JSObject *jsb_ProtocolSocial_prototype;

JSBool js_pluginx_protocols_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->showLeaderboard(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->showAchievements();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		long arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_long(cx, argv[1], (long *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->submitScore(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolSocial_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TSocialDeveloperInfo arg0;
		ok &= jsval_to_TSocialDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TAchievementInfo arg0;
		ok &= jsval_to_TAchievementInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->unlockAchievement(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolSocial_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolSocial)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolSocial *nobj = static_cast<cocos2d::plugin::ProtocolSocial *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolSocial(JSContext *cx, JSObject *global) {
	jsb_ProtocolSocial_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolSocial_class->name = "ProtocolSocial";
	jsb_ProtocolSocial_class->addProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->delProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->getProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolSocial_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolSocial_class->resolve = JS_ResolveStub;
	jsb_ProtocolSocial_class->convert = JS_ConvertStub;
	jsb_ProtocolSocial_class->finalize = js_pluginx_protocols_ProtocolSocial_finalize;
	jsb_ProtocolSocial_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showLeaderboard", js_pluginx_protocols_ProtocolSocial_showLeaderboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showAchievements", js_pluginx_protocols_ProtocolSocial_showAchievements, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("submitScore", js_pluginx_protocols_ProtocolSocial_submitScore, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolSocial_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("unlockAchievement", js_pluginx_protocols_ProtocolSocial_unlockAchievement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolSocial_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolSocial_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolSocial", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolSocial> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolSocial_class;
		p->proto = jsb_ProtocolSocial_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolUser_class;
JSObject *jsb_ProtocolUser_prototype;

JSBool js_pluginx_protocols_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isLogined();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolUser_logout(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->logout();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolUser_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		TUserDeveloperInfo arg0;
		ok &= jsval_to_TUserDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->login();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_protocols_ProtocolUser_getSessionID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSessionID();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_pluginx_protocols_ProtocolUser_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolUser)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

//        cocos2d::plugin::ProtocolUser *nobj = static_cast<cocos2d::plugin::ProtocolUser *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolUser(JSContext *cx, JSObject *global) {
	jsb_ProtocolUser_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolUser_class->name = "ProtocolUser";
	jsb_ProtocolUser_class->addProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->delProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->getProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolUser_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolUser_class->resolve = JS_ResolveStub;
	jsb_ProtocolUser_class->convert = JS_ConvertStub;
	jsb_ProtocolUser_class->finalize = js_pluginx_protocols_ProtocolUser_finalize;
	jsb_ProtocolUser_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("isLogined", js_pluginx_protocols_ProtocolUser_isLogined, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logout", js_pluginx_protocols_ProtocolUser_logout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolUser_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("login", js_pluginx_protocols_ProtocolUser_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSessionID", js_pluginx_protocols_ProtocolUser_getSessionID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolUser_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolUser_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolUser", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolUser> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolUser_class;
		p->proto = jsb_ProtocolUser_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_pluginx_protocols(JSContext* cx, JSObject* obj) {
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

	js_register_pluginx_protocols_PluginProtocol(cx, obj);
	js_register_pluginx_protocols_ProtocolUser(cx, obj);
	js_register_pluginx_protocols_ProtocolShare(cx, obj);
	js_register_pluginx_protocols_ProtocolIAP(cx, obj);
	js_register_pluginx_protocols_ProtocolSocial(cx, obj);
	js_register_pluginx_protocols_ProtocolAnalytics(cx, obj);
	js_register_pluginx_protocols_ProtocolAds(cx, obj);
	js_register_pluginx_protocols_PluginManager(cx, obj);
}

