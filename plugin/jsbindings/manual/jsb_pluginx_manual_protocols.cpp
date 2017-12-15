#include "jsb_pluginx_manual_protocols.h"
#include "jsb_pluginx_basic_conversions.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include <string>
#include <vector>
#include "PluginProtocol.h"
#include "AgentManager.h"

using namespace pluginx;

JSClass  *jsb_PluginParam_class;
JSObject *jsb_PluginParam_prototype;

bool js_pluginx_protocols_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;

	JSObject *obj = NULL;
	cocos2d::plugin::PluginParam* cobj = NULL;

    do {
        if (argc == 2) {
            int arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }

            switch (arg0)
            {
            case cocos2d::plugin::PluginParam::kParamTypeInt:
                {
                    int arg1;
                    ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
                    if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeFloat:
                {
                   	double arg1;
        			ok &= JS::ToNumber(cx, args.get(1), &arg1);
        			if (ok) { 
            			float tempArg = arg1;
            			cobj = new cocos2d::plugin::PluginParam(tempArg);
                    }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeBool:
                {
                    bool arg1 = JS::ToBoolean(args.get(1));
        			cobj = new cocos2d::plugin::PluginParam(arg1);
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeString:
                {
                    const char* arg1;
        			std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        			if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            case cocos2d::plugin::PluginParam::kParamTypeStringMap:
                {
           	        StringMap arg1;
            		ok &= jsval_to_StringMap(cx, args.get(1), &arg1);
			        if (ok) { cobj = new cocos2d::plugin::PluginParam(arg1); }
                }
                break;
            default:
                break;
            }
            if (!ok || NULL == cobj) { ok = true; break; }

            TypeTest<cocos2d::plugin::PluginParam> t;
			js_type_class_t *typeClass;
			std::string typeName = t.s_name();
			auto typeMapIter = _js_global_type_map.find(typeName);
			assert(typeMapIter != _js_global_type_map.end());
            typeClass = typeMapIter->second;
			assert(typeClass);
            obj = JS_NewObject(cx, typeClass->jsclass, JS::RootedObject(cx, typeClass->proto), JS::RootedObject(cx, typeClass->parentProto));
			js_proxy_t *proxy;
			JS_NEW_PROXY(proxy, cobj, obj);
        }
    } while (0);

	if (cobj) {
		args.rval().set(OBJECT_TO_JSVAL(obj));
		return true;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return false;
}


void js_pluginx_protocols_PluginParam_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginParam)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        JS_GET_PROXY(nproxy, jsproxy->ptr);

    cocos2d::plugin::PluginParam *nobj = static_cast<cocos2d::plugin::PluginParam *>(nproxy->ptr);
    if (nobj)
        delete nobj;

        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

static bool js_pluginx_protocols_PluginParam_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::plugin::PluginParam *nobj = new cocos2d::plugin::PluginParam();
    js_proxy_t* p;
    JS_NEW_PROXY(p, nobj, obj);
    args.rval().setUndefined();
    return true;
}

void js_register_pluginx_protocols_PluginParam(JSContext *cx, JS::HandleObject global) {
	jsb_PluginParam_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginParam_class->name = "PluginParam";
	jsb_PluginParam_class->addProperty = JS_PropertyStub;
	jsb_PluginParam_class->delProperty = JS_DeletePropertyStub;
	jsb_PluginParam_class->getProperty = JS_PropertyStub;
	jsb_PluginParam_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginParam_class->enumerate = JS_EnumerateStub;
	jsb_PluginParam_class->resolve = JS_ResolveStub;
	jsb_PluginParam_class->convert = JS_ConvertStub;
	jsb_PluginParam_class->finalize = js_pluginx_protocols_PluginParam_finalize;
	jsb_PluginParam_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		JS_PS_END
	};

	JSFunctionSpec *funcs = NULL;

	JSFunctionSpec *st_funcs = NULL;

	jsb_PluginParam_prototype = JS_InitClass(
		cx, global,
        JS::NullPtr(), // parent proto
		jsb_PluginParam_class,
		js_pluginx_protocols_PluginParam_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	//bool found;
	//JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginParam> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    if (typeMapIter == _js_global_type_map.end())
    {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_PluginParam_class;
		p->proto = jsb_PluginParam_prototype;
		p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

bool js_pluginx_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginProtocol_callFuncWithParam : Invalid Native Object");
    
 	if (argc > 0) {
 	    std::string strName;
 	    ok &= jsval_to_std_string(cx, args.get(0), &strName);
 		std::vector<cocos2d::plugin::PluginParam*> params;
 		uint32_t i = 1;
 		while (i < argc) {
 			JSObject *tmpObj = args.get(1).toObjectOrNull();
            if (tmpObj == NULL)
                break;

            proxy = jsb_get_js_proxy(tmpObj);
 			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
 			JS_TEST_NATIVE_OBJECT(cx, item)
 			params.push_back(item);
 			i++;
 		}

        cobj->callFuncWithParam(strName.c_str(), params);
 
        args.rval().setUndefined();
 		return true;
 	}
    JS_ReportError(cx, "wrong number of arguments");
	return false;
}

bool js_pluginx_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, args.get(0), &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
            JSObject *tmpObj = args.get(i).toObjectOrNull();
            if (tmpObj == NULL)
                break;

			js_proxy_t *proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        std::string ret = cobj->callStringFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return false;
}

bool js_pluginx_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, args.get(0), &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
            JSObject *tmpObj = args.get(i).toObjectOrNull();
            if (tmpObj == NULL)
                break;

			js_proxy_t *proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        int ret = cobj->callIntFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return false;
}

bool js_pluginx_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, args.get(0), &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
            JSObject *tmpObj = args.get(i).toObjectOrNull();
            if (tmpObj == NULL)
                break;

			js_proxy_t *proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        float ret = cobj->callFloatFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		args.rval().set(jsret);
		return true;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return false;
}

bool js_pluginx_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	if (argc > 0) {
	    std::string strName;
	    ok &= jsval_to_std_string(cx, args.get(0), &strName);

		std::vector<cocos2d::plugin::PluginParam*> params;
		uint32_t i = 1;
		while (i < argc) {
            JSObject *tmpObj = args.get(i).toObjectOrNull();
            if (tmpObj == NULL)
                break;

			js_proxy_t *proxy = jsb_get_js_proxy(tmpObj);
			cocos2d::plugin::PluginParam* item = (cocos2d::plugin::PluginParam*)(proxy ? proxy->ptr : NULL);
			JS_TEST_NATIVE_OBJECT(cx, item)
			params.push_back(item);
			i++;
		}

        JSObject *obj = JS_THIS_OBJECT(cx, vp);
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
        bool ret = cobj->callBoolFuncWithParam(strName.c_str(), params);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		args.rval().set(jsret);
		return true;
	}
    JS_ReportError(cx, "wrong number of arguments");
	return false;
}
