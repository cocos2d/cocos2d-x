#include "jsb_pluginx_flurry_auto.hpp"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_basic_conversions.h"
using namespace pluginx;
#include "AnalyticsFlurry.h"

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


JSClass  *jsb_AnalyticsFlurry_class;
JSObject *jsb_AnalyticsFlurry_prototype;

JSBool js_pluginx_flurry_AnalyticsFlurry_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::plugin::AnalyticsFlurry* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			LogEventParamMap* arg1;
			LogEventParamMap arg1_tmp;
			do {
				ok &= jsval_to_LogEventParamMap(cx, argv[1], &arg1);
				if (ok) { arg1_tmp = *arg1; delete arg1; arg1 = &arg1_tmp; } else { arg1 = NULL; }
			} while(0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->logTimedEventBegin(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->logTimedEventBegin(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_setUserId(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setUserId(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setGender(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::AnalyticsFlurry::Gender arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setGender(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_logPageView(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->logPageView();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setReportLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setReportLocation(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setAge(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setAge(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setVersionName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setVersionName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->stopSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_setUseHttps(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setUseHttps(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::plugin::AnalyticsFlurry* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			LogEventParamMap* arg1;
			LogEventParamMap arg1_tmp;
			do {
				ok &= jsval_to_LogEventParamMap(cx, argv[1], &arg1);
				if (ok) { arg1_tmp = *arg1; delete arg1; arg1 = &arg1_tmp; } else { arg1 = NULL; }
			} while(0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->logTimedEventEnd(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->logTimedEventEnd(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_pluginx_flurry_AnalyticsFlurry_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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
JSBool js_pluginx_flurry_AnalyticsFlurry_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cocos2d::plugin::AnalyticsFlurry* cobj = (cocos2d::plugin::AnalyticsFlurry *)(proxy ? proxy->ptr : NULL);
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


extern JSObject *jsb_ProtocolAnalytics_prototype;

void js_pluginx_flurry_AnalyticsFlurry_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AnalyticsFlurry)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JS_GET_NATIVE_PROXY(jsproxy, obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

//        cocos2d::plugin::AnalyticsFlurry *nobj = static_cast<cocos2d::plugin::AnalyticsFlurry *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
        
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

void js_register_pluginx_flurry_AnalyticsFlurry(JSContext *cx, JSObject *global) {
	jsb_AnalyticsFlurry_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_AnalyticsFlurry_class->name = "AnalyticsFlurry";
	jsb_AnalyticsFlurry_class->addProperty = JS_PropertyStub;
	jsb_AnalyticsFlurry_class->delProperty = JS_PropertyStub;
	jsb_AnalyticsFlurry_class->getProperty = JS_PropertyStub;
	jsb_AnalyticsFlurry_class->setProperty = JS_StrictPropertyStub;
	jsb_AnalyticsFlurry_class->enumerate = JS_EnumerateStub;
	jsb_AnalyticsFlurry_class->resolve = JS_ResolveStub;
	jsb_AnalyticsFlurry_class->convert = JS_ConvertStub;
	jsb_AnalyticsFlurry_class->finalize = js_pluginx_flurry_AnalyticsFlurry_finalize;
	jsb_AnalyticsFlurry_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("logTimedEventBegin", js_pluginx_flurry_AnalyticsFlurry_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUserId", js_pluginx_flurry_AnalyticsFlurry_setUserId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logError", js_pluginx_flurry_AnalyticsFlurry_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCaptureUncaughtException", js_pluginx_flurry_AnalyticsFlurry_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setGender", js_pluginx_flurry_AnalyticsFlurry_setGender, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logPageView", js_pluginx_flurry_AnalyticsFlurry_logPageView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginName", js_pluginx_flurry_AnalyticsFlurry_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setReportLocation", js_pluginx_flurry_AnalyticsFlurry_setReportLocation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_pluginx_flurry_AnalyticsFlurry_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logEvent", js_pluginx_flurry_AnalyticsFlurry_logEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSessionContinueMillis", js_pluginx_flurry_AnalyticsFlurry_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAge", js_pluginx_flurry_AnalyticsFlurry_setAge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_pluginx_flurry_AnalyticsFlurry_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setVersionName", js_pluginx_flurry_AnalyticsFlurry_setVersionName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startSession", js_pluginx_flurry_AnalyticsFlurry_startSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopSession", js_pluginx_flurry_AnalyticsFlurry_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setUseHttps", js_pluginx_flurry_AnalyticsFlurry_setUseHttps, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logTimedEventEnd", js_pluginx_flurry_AnalyticsFlurry_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_pluginx_flurry_AnalyticsFlurry_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_pluginx_flurry_AnalyticsFlurry_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_AnalyticsFlurry_prototype = JS_InitClass(
		cx, global,
		jsb_ProtocolAnalytics_prototype,
		jsb_AnalyticsFlurry_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "AnalyticsFlurry", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::AnalyticsFlurry> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_AnalyticsFlurry_class;
		p->proto = jsb_AnalyticsFlurry_prototype;
		p->parentProto = jsb_ProtocolAnalytics_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_pluginx_flurry(JSContext* cx, JSObject* obj) {
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

	js_register_pluginx_flurry_AnalyticsFlurry(cx, obj);
}

