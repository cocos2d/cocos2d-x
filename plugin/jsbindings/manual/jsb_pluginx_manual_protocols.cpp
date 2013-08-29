#include "jsb_pluginx_manual_protocols.h"
#include "jsb_pluginx_basic_conversions.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include <string>
#include <vector>
#include "PluginProtocol.h"

using namespace pluginx;

JSClass  *jsb_PluginParam_class;
JSObject *jsb_PluginParam_prototype;

JSBool js_pluginx_protocols_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	cocos2d::plugin::PluginParam* cobj = NULL;

    do {
        if (argc == 2) {
            int arg0;
            ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
            if (!ok) { ok = JS_TRUE; break; }

            switch (arg0)
            {
            case cocos2d::plugin::PluginParam::kParamTypeInt:
                {
                    int arg1;
                    ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
                    if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeFloat:
                {
                   	double arg1;
        			ok &= JS_ValueToNumber(cx, argv[1], &arg1);
        			if (ok) { 
            			float tempArg = arg1;
            			cobj = new cocos2d::plugin::PluginParam(tempArg);
                    }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeBool:
                {
                    JSBool arg1;
        			ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
        			if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeString:
                {
                    const char* arg1;
        			std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        			if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeStringMap:
                {
           	        StringMap arg1;
            		ok &= jsval_to_StringMap(cx, argv[1], &arg1);
			        if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            default:
                break;
            }
            if (!ok || NULL == cobj) { ok = JS_TRUE; break; }

            TypeTest<cocos2d::plugin::PluginParam> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t *proxy;
			JS_NEW_PROXY(proxy, cobj, obj);
        }
    } while (0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}


void js_pluginx_protocols_PluginParam_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginParam)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JS_GET_NATIVE_PROXY(jsproxy, obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

    cocos2d::plugin::PluginParam *nobj = static_cast<cocos2d::plugin::PluginParam *>(nproxy->ptr);
    if (nobj)
        delete nobj;

        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

static JSBool js_pluginx_protocols_PluginParam_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::plugin::PluginParam *nobj = new cocos2d::plugin::PluginParam();
    js_proxy_t* p;
    JS_NEW_PROXY(p, nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_pluginx_protocols_PluginParam(JSContext *cx, JSObject *global) {
	jsb_PluginParam_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginParam_class->name = "PluginParam";
	jsb_PluginParam_class->addProperty = JS_PropertyStub;
	jsb_PluginParam_class->delProperty = JS_PropertyStub;
	jsb_PluginParam_class->getProperty = JS_PropertyStub;
	jsb_PluginParam_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginParam_class->enumerate = JS_EnumerateStub;
	jsb_PluginParam_class->resolve = JS_ResolveStub;
	jsb_PluginParam_class->convert = JS_ConvertStub;
	jsb_PluginParam_class->finalize = js_pluginx_protocols_PluginParam_finalize;
	jsb_PluginParam_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	JSFunctionSpec *funcs = NULL;

	JSFunctionSpec *st_funcs = NULL;

	jsb_PluginParam_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginParam_class,
		js_pluginx_protocols_PluginParam_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginParam> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginParam_class;
		p->proto = jsb_PluginParam_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

JSBool js_pluginx_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
     jsval *argv = JS_ARGV(cx, vp);
 	if (argc > 0) {
 	    std::string strName;
 	    ok &= jsval_to_std_string(cx, argv[0], &strName);
 		std::vector<cocos2d::plugin::PluginParam*> params;
 		uint32_t i = 1;
 		while (i < argc) {
 			js_proxy_t *proxy;
 			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
            if (tmpObj == NULL)
                break;

 			JS_GET_NATIVE_PROXY(proxy, tmpObj);
 			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
 			JS_TEST_NATIVE_OBJECT(cx, item)
 			params.push_back(item);
 			i++;
 		}
 
         JSObject *obj = JS_THIS_OBJECT(cx, vp);
         js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
         cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
         cobj->callFuncWithParam(strName.c_str(), params);
 
         JS_SET_RVAL(cx, vp, JSVAL_VOID);
 		return JS_TRUE;
 	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_pluginx_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
    jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, argv[0], &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
            if (tmpObj == NULL)
                break;

			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        const char* ret = cobj->callStringFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_pluginx_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
    jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, argv[0], &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
            if (tmpObj == NULL)
                break;

			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        int ret = cobj->callIntFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_pluginx_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
    jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, argv[0], &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
            if (tmpObj == NULL)
                break;

			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        float ret = cobj->callFloatFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_pluginx_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSBool ok = JS_TRUE;
    jsval *argv = JS_ARGV(cx, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, argv[0], &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[i]);
            if (tmpObj == NULL)
                break;

			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        bool ret = cobj->callBoolFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
