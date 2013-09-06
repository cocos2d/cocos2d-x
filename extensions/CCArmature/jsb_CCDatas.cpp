#include "jsb_CCDatas.hpp"
#include "cocos2d_specifics.hpp"
#include "CCDatas.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
	if (_ccobj) {
		_ccobj->autorelease();
	}
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_CCBaseData_class;
JSObject *jsb_CCBaseData_prototype;

JSBool js_jsb_CCDatas_CCBaseData_getColor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBaseData* cobj = (cocos2d::extension::CCBaseData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		ccColor4B ret = cobj->getColor();
		jsval jsret;
		jsret = cccolor4b_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCBaseData_copy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBaseData* cobj = (cocos2d::extension::CCBaseData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCBaseData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCBaseData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->copy(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCBaseData_subtract(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBaseData* cobj = (cocos2d::extension::CCBaseData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		cocos2d::extension::CCBaseData* arg0;
		cocos2d::extension::CCBaseData* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCBaseData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::extension::CCBaseData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg1, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->subtract(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCBaseData_setColor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBaseData* cobj = (cocos2d::extension::CCBaseData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::ccColor4B arg0;
		ok &= jsval_to_cccolor4b(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setColor(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCBaseData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCBaseData* ret = cocos2d::extension::CCBaseData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCBaseData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCBaseData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCBaseData* cobj = new cocos2d::extension::CCBaseData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCBaseData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCBaseData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCBaseData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCBaseData)", obj);
}

static JSBool js_jsb_CCDatas_CCBaseData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCBaseData *nobj = new cocos2d::extension::CCBaseData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCBaseData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCBaseData(JSContext *cx, JSObject *global) {
	jsb_CCBaseData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCBaseData_class->name = "BaseData";
	jsb_CCBaseData_class->addProperty = JS_PropertyStub;
	jsb_CCBaseData_class->delProperty = JS_PropertyStub;
	jsb_CCBaseData_class->getProperty = JS_PropertyStub;
	jsb_CCBaseData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCBaseData_class->enumerate = JS_EnumerateStub;
	jsb_CCBaseData_class->resolve = JS_ResolveStub;
	jsb_CCBaseData_class->convert = JS_ConvertStub;
	jsb_CCBaseData_class->finalize = js_jsb_CCDatas_CCBaseData_finalize;
	jsb_CCBaseData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getColor", js_jsb_CCDatas_CCBaseData_getColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("copy", js_jsb_CCDatas_CCBaseData_copy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("subtract", js_jsb_CCDatas_CCBaseData_subtract, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setColor", js_jsb_CCDatas_CCBaseData_setColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCBaseData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCBaseData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCBaseData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCBaseData_class,
		js_jsb_CCDatas_CCBaseData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "BaseData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCBaseData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCBaseData_class;
		p->proto = jsb_CCBaseData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCDisplayData_class;
JSObject *jsb_CCDisplayData_prototype;

JSBool js_jsb_CCDatas_CCDisplayData_changeDisplayToTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		const char* ret = cocos2d::extension::CCDisplayData::changeDisplayToTexture(arg0);
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_jsb_CCDatas_CCDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCDisplayData* ret = cocos2d::extension::CCDisplayData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCDisplayData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCDisplayData* cobj = new cocos2d::extension::CCDisplayData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCDisplayData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCDisplayData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCDisplayData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCDisplayData)", obj);
}

static JSBool js_jsb_CCDatas_CCDisplayData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCDisplayData *nobj = new cocos2d::extension::CCDisplayData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCDisplayData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCDisplayData(JSContext *cx, JSObject *global) {
	jsb_CCDisplayData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCDisplayData_class->name = "DisplayData";
	jsb_CCDisplayData_class->addProperty = JS_PropertyStub;
	jsb_CCDisplayData_class->delProperty = JS_PropertyStub;
	jsb_CCDisplayData_class->getProperty = JS_PropertyStub;
	jsb_CCDisplayData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCDisplayData_class->enumerate = JS_EnumerateStub;
	jsb_CCDisplayData_class->resolve = JS_ResolveStub;
	jsb_CCDisplayData_class->convert = JS_ConvertStub;
	jsb_CCDisplayData_class->finalize = js_jsb_CCDatas_CCDisplayData_finalize;
	jsb_CCDisplayData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	JSFunctionSpec *funcs = NULL;

	static JSFunctionSpec st_funcs[] = {
		JS_FN("changeDisplayToTexture", js_jsb_CCDatas_CCDisplayData_changeDisplayToTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("create", js_jsb_CCDatas_CCDisplayData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCDisplayData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCDisplayData_class,
		js_jsb_CCDatas_CCDisplayData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "DisplayData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCDisplayData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCDisplayData_class;
		p->proto = jsb_CCDisplayData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCSpriteDisplayData_class;
JSObject *jsb_CCSpriteDisplayData_prototype;

JSBool js_jsb_CCDatas_CCSpriteDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCSpriteDisplayData* cobj = (cocos2d::extension::CCSpriteDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCSpriteDisplayData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCSpriteDisplayData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->copy(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCSpriteDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCSpriteDisplayData* cobj = (cocos2d::extension::CCSpriteDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setParam(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCSpriteDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCSpriteDisplayData* ret = cocos2d::extension::CCSpriteDisplayData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCSpriteDisplayData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCSpriteDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCSpriteDisplayData* cobj = new cocos2d::extension::CCSpriteDisplayData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCSpriteDisplayData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCSpriteDisplayData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCDisplayData_prototype;

void js_jsb_CCDatas_CCSpriteDisplayData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCSpriteDisplayData)", obj);
}

static JSBool js_jsb_CCDatas_CCSpriteDisplayData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCSpriteDisplayData *nobj = new cocos2d::extension::CCSpriteDisplayData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCSpriteDisplayData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCSpriteDisplayData(JSContext *cx, JSObject *global) {
	jsb_CCSpriteDisplayData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCSpriteDisplayData_class->name = "SpriteDisplayData";
	jsb_CCSpriteDisplayData_class->addProperty = JS_PropertyStub;
	jsb_CCSpriteDisplayData_class->delProperty = JS_PropertyStub;
	jsb_CCSpriteDisplayData_class->getProperty = JS_PropertyStub;
	jsb_CCSpriteDisplayData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCSpriteDisplayData_class->enumerate = JS_EnumerateStub;
	jsb_CCSpriteDisplayData_class->resolve = JS_ResolveStub;
	jsb_CCSpriteDisplayData_class->convert = JS_ConvertStub;
	jsb_CCSpriteDisplayData_class->finalize = js_jsb_CCDatas_CCSpriteDisplayData_finalize;
	jsb_CCSpriteDisplayData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("copy", js_jsb_CCDatas_CCSpriteDisplayData_copy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setParam", js_jsb_CCDatas_CCSpriteDisplayData_setParam, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCSpriteDisplayData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCSpriteDisplayData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCSpriteDisplayData_prototype = JS_InitClass(
		cx, global,
		jsb_CCDisplayData_prototype,
		jsb_CCSpriteDisplayData_class,
		js_jsb_CCDatas_CCSpriteDisplayData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "SpriteDisplayData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCSpriteDisplayData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCSpriteDisplayData_class;
		p->proto = jsb_CCSpriteDisplayData_prototype;
		p->parentProto = jsb_CCDisplayData_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCArmatureDisplayData_class;
JSObject *jsb_CCArmatureDisplayData_prototype;

JSBool js_jsb_CCDatas_CCArmatureDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureDisplayData* cobj = (cocos2d::extension::CCArmatureDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCArmatureDisplayData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCArmatureDisplayData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->copy(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCArmatureDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureDisplayData* cobj = (cocos2d::extension::CCArmatureDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setParam(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCArmatureDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCArmatureDisplayData* ret = cocos2d::extension::CCArmatureDisplayData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCArmatureDisplayData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCArmatureDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCArmatureDisplayData* cobj = new cocos2d::extension::CCArmatureDisplayData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCArmatureDisplayData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCArmatureDisplayData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCDisplayData_prototype;

void js_jsb_CCDatas_CCArmatureDisplayData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCArmatureDisplayData)", obj);
}

static JSBool js_jsb_CCDatas_CCArmatureDisplayData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCArmatureDisplayData *nobj = new cocos2d::extension::CCArmatureDisplayData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCArmatureDisplayData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCArmatureDisplayData(JSContext *cx, JSObject *global) {
	jsb_CCArmatureDisplayData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCArmatureDisplayData_class->name = "ArmatureDisplayData";
	jsb_CCArmatureDisplayData_class->addProperty = JS_PropertyStub;
	jsb_CCArmatureDisplayData_class->delProperty = JS_PropertyStub;
	jsb_CCArmatureDisplayData_class->getProperty = JS_PropertyStub;
	jsb_CCArmatureDisplayData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCArmatureDisplayData_class->enumerate = JS_EnumerateStub;
	jsb_CCArmatureDisplayData_class->resolve = JS_ResolveStub;
	jsb_CCArmatureDisplayData_class->convert = JS_ConvertStub;
	jsb_CCArmatureDisplayData_class->finalize = js_jsb_CCDatas_CCArmatureDisplayData_finalize;
	jsb_CCArmatureDisplayData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("copy", js_jsb_CCDatas_CCArmatureDisplayData_copy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setParam", js_jsb_CCDatas_CCArmatureDisplayData_setParam, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCArmatureDisplayData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCArmatureDisplayData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCArmatureDisplayData_prototype = JS_InitClass(
		cx, global,
		jsb_CCDisplayData_prototype,
		jsb_CCArmatureDisplayData_class,
		js_jsb_CCDatas_CCArmatureDisplayData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ArmatureDisplayData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCArmatureDisplayData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCArmatureDisplayData_class;
		p->proto = jsb_CCArmatureDisplayData_prototype;
		p->parentProto = jsb_CCDisplayData_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCParticleDisplayData_class;
JSObject *jsb_CCParticleDisplayData_prototype;

JSBool js_jsb_CCDatas_CCParticleDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCParticleDisplayData* cobj = (cocos2d::extension::CCParticleDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCParticleDisplayData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCParticleDisplayData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->copy(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCParticleDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCParticleDisplayData* cobj = (cocos2d::extension::CCParticleDisplayData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setParam(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCParticleDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCParticleDisplayData* ret = cocos2d::extension::CCParticleDisplayData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCParticleDisplayData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCParticleDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCParticleDisplayData* cobj = new cocos2d::extension::CCParticleDisplayData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCParticleDisplayData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCParticleDisplayData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCDisplayData_prototype;

void js_jsb_CCDatas_CCParticleDisplayData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCParticleDisplayData)", obj);
}

static JSBool js_jsb_CCDatas_CCParticleDisplayData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCParticleDisplayData *nobj = new cocos2d::extension::CCParticleDisplayData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCParticleDisplayData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCParticleDisplayData(JSContext *cx, JSObject *global) {
	jsb_CCParticleDisplayData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCParticleDisplayData_class->name = "ParticleDisplayData";
	jsb_CCParticleDisplayData_class->addProperty = JS_PropertyStub;
	jsb_CCParticleDisplayData_class->delProperty = JS_PropertyStub;
	jsb_CCParticleDisplayData_class->getProperty = JS_PropertyStub;
	jsb_CCParticleDisplayData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCParticleDisplayData_class->enumerate = JS_EnumerateStub;
	jsb_CCParticleDisplayData_class->resolve = JS_ResolveStub;
	jsb_CCParticleDisplayData_class->convert = JS_ConvertStub;
	jsb_CCParticleDisplayData_class->finalize = js_jsb_CCDatas_CCParticleDisplayData_finalize;
	jsb_CCParticleDisplayData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("copy", js_jsb_CCDatas_CCParticleDisplayData_copy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setParam", js_jsb_CCDatas_CCParticleDisplayData_setParam, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCParticleDisplayData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCParticleDisplayData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCParticleDisplayData_prototype = JS_InitClass(
		cx, global,
		jsb_CCDisplayData_prototype,
		jsb_CCParticleDisplayData_class,
		js_jsb_CCDatas_CCParticleDisplayData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ParticleDisplayData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCParticleDisplayData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCParticleDisplayData_class;
		p->proto = jsb_CCParticleDisplayData_prototype;
		p->parentProto = jsb_CCDisplayData_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCBoneData_class;
JSObject *jsb_CCBoneData_prototype;

JSBool js_jsb_CCDatas_CCBoneData_getDisplayData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBoneData* cobj = (cocos2d::extension::CCBoneData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCDisplayData* ret = cobj->getDisplayData(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCDisplayData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCBoneData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBoneData* cobj = (cocos2d::extension::CCBoneData *)(proxy ? proxy->ptr : NULL);
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
JSBool js_jsb_CCDatas_CCBoneData_addDisplayData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCBoneData* cobj = (cocos2d::extension::CCBoneData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCDisplayData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCDisplayData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addDisplayData(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCBoneData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCBoneData* ret = cocos2d::extension::CCBoneData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCBoneData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCBoneData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCBoneData* cobj = new cocos2d::extension::CCBoneData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCBoneData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCBoneData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCBaseData_prototype;

void js_jsb_CCDatas_CCBoneData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCBoneData)", obj);
}

static JSBool js_jsb_CCDatas_CCBoneData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCBoneData *nobj = new cocos2d::extension::CCBoneData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCBoneData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCBoneData(JSContext *cx, JSObject *global) {
	jsb_CCBoneData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCBoneData_class->name = "BoneData";
	jsb_CCBoneData_class->addProperty = JS_PropertyStub;
	jsb_CCBoneData_class->delProperty = JS_PropertyStub;
	jsb_CCBoneData_class->getProperty = JS_PropertyStub;
	jsb_CCBoneData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCBoneData_class->enumerate = JS_EnumerateStub;
	jsb_CCBoneData_class->resolve = JS_ResolveStub;
	jsb_CCBoneData_class->convert = JS_ConvertStub;
	jsb_CCBoneData_class->finalize = js_jsb_CCDatas_CCBoneData_finalize;
	jsb_CCBoneData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getDisplayData", js_jsb_CCDatas_CCBoneData_getDisplayData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_jsb_CCDatas_CCBoneData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addDisplayData", js_jsb_CCDatas_CCBoneData_addDisplayData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCBoneData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCBoneData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCBoneData_prototype = JS_InitClass(
		cx, global,
		jsb_CCBaseData_prototype,
		jsb_CCBoneData_class,
		js_jsb_CCDatas_CCBoneData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "BoneData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCBoneData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCBoneData_class;
		p->proto = jsb_CCBoneData_prototype;
		p->parentProto = jsb_CCBaseData_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCArmatureData_class;
JSObject *jsb_CCArmatureData_prototype;

JSBool js_jsb_CCDatas_CCArmatureData_addBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureData* cobj = (cocos2d::extension::CCArmatureData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCBoneData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCBoneData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addBoneData(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCArmatureData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureData* cobj = (cocos2d::extension::CCArmatureData *)(proxy ? proxy->ptr : NULL);
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
JSBool js_jsb_CCDatas_CCArmatureData_getBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureData* cobj = (cocos2d::extension::CCArmatureData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCBoneData* ret = cobj->getBoneData(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCBoneData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCArmatureData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCArmatureData* ret = cocos2d::extension::CCArmatureData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCArmatureData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCArmatureData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCArmatureData* cobj = new cocos2d::extension::CCArmatureData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCArmatureData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCArmatureData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCArmatureData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCArmatureData)", obj);
}

static JSBool js_jsb_CCDatas_CCArmatureData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCArmatureData *nobj = new cocos2d::extension::CCArmatureData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCArmatureData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCArmatureData(JSContext *cx, JSObject *global) {
	jsb_CCArmatureData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCArmatureData_class->name = "ArmatureData";
	jsb_CCArmatureData_class->addProperty = JS_PropertyStub;
	jsb_CCArmatureData_class->delProperty = JS_PropertyStub;
	jsb_CCArmatureData_class->getProperty = JS_PropertyStub;
	jsb_CCArmatureData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCArmatureData_class->enumerate = JS_EnumerateStub;
	jsb_CCArmatureData_class->resolve = JS_ResolveStub;
	jsb_CCArmatureData_class->convert = JS_ConvertStub;
	jsb_CCArmatureData_class->finalize = js_jsb_CCDatas_CCArmatureData_finalize;
	jsb_CCArmatureData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("addBoneData", js_jsb_CCDatas_CCArmatureData_addBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_jsb_CCDatas_CCArmatureData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBoneData", js_jsb_CCDatas_CCArmatureData_getBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCArmatureData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCArmatureData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCArmatureData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCArmatureData_class,
		js_jsb_CCDatas_CCArmatureData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ArmatureData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCArmatureData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCArmatureData_class;
		p->proto = jsb_CCArmatureData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCFrameData_class;
JSObject *jsb_CCFrameData_prototype;

JSBool js_jsb_CCDatas_CCFrameData_copy(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCFrameData* cobj = (cocos2d::extension::CCFrameData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCFrameData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCFrameData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->copy(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCFrameData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCFrameData* ret = cocos2d::extension::CCFrameData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCFrameData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCFrameData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCFrameData* cobj = new cocos2d::extension::CCFrameData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCFrameData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCFrameData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



extern JSObject *jsb_CCBaseData_prototype;

void js_jsb_CCDatas_CCFrameData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCFrameData)", obj);
}

static JSBool js_jsb_CCDatas_CCFrameData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCFrameData *nobj = new cocos2d::extension::CCFrameData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCFrameData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCFrameData(JSContext *cx, JSObject *global) {
	jsb_CCFrameData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCFrameData_class->name = "FrameData";
	jsb_CCFrameData_class->addProperty = JS_PropertyStub;
	jsb_CCFrameData_class->delProperty = JS_PropertyStub;
	jsb_CCFrameData_class->getProperty = JS_PropertyStub;
	jsb_CCFrameData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCFrameData_class->enumerate = JS_EnumerateStub;
	jsb_CCFrameData_class->resolve = JS_ResolveStub;
	jsb_CCFrameData_class->convert = JS_ConvertStub;
	jsb_CCFrameData_class->finalize = js_jsb_CCDatas_CCFrameData_finalize;
	jsb_CCFrameData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("copy", js_jsb_CCDatas_CCFrameData_copy, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCFrameData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCFrameData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCFrameData_prototype = JS_InitClass(
		cx, global,
		jsb_CCBaseData_prototype,
		jsb_CCFrameData_class,
		js_jsb_CCDatas_CCFrameData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "FrameData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCFrameData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCFrameData_class;
		p->proto = jsb_CCFrameData_prototype;
		p->parentProto = jsb_CCBaseData_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCMovementBoneData_class;
JSObject *jsb_CCMovementBoneData_prototype;

JSBool js_jsb_CCDatas_CCMovementBoneData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCMovementBoneData* cobj = (cocos2d::extension::CCMovementBoneData *)(proxy ? proxy->ptr : NULL);
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
JSBool js_jsb_CCDatas_CCMovementBoneData_getFrameData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCMovementBoneData* cobj = (cocos2d::extension::CCMovementBoneData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCFrameData* ret = cobj->getFrameData(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCFrameData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCMovementBoneData_addFrameData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCMovementBoneData* cobj = (cocos2d::extension::CCMovementBoneData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCFrameData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCFrameData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addFrameData(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCMovementBoneData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCMovementBoneData* ret = cocos2d::extension::CCMovementBoneData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCMovementBoneData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCMovementBoneData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCMovementBoneData* cobj = new cocos2d::extension::CCMovementBoneData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCMovementBoneData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCMovementBoneData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCMovementBoneData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCMovementBoneData)", obj);
}

static JSBool js_jsb_CCDatas_CCMovementBoneData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCMovementBoneData *nobj = new cocos2d::extension::CCMovementBoneData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCMovementBoneData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCMovementBoneData(JSContext *cx, JSObject *global) {
	jsb_CCMovementBoneData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCMovementBoneData_class->name = "MovementBoneData";
	jsb_CCMovementBoneData_class->addProperty = JS_PropertyStub;
	jsb_CCMovementBoneData_class->delProperty = JS_PropertyStub;
	jsb_CCMovementBoneData_class->getProperty = JS_PropertyStub;
	jsb_CCMovementBoneData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCMovementBoneData_class->enumerate = JS_EnumerateStub;
	jsb_CCMovementBoneData_class->resolve = JS_ResolveStub;
	jsb_CCMovementBoneData_class->convert = JS_ConvertStub;
	jsb_CCMovementBoneData_class->finalize = js_jsb_CCDatas_CCMovementBoneData_finalize;
	jsb_CCMovementBoneData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_jsb_CCDatas_CCMovementBoneData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFrameData", js_jsb_CCDatas_CCMovementBoneData_getFrameData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addFrameData", js_jsb_CCDatas_CCMovementBoneData_addFrameData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCMovementBoneData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCMovementBoneData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCMovementBoneData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCMovementBoneData_class,
		js_jsb_CCDatas_CCMovementBoneData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "MovementBoneData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCMovementBoneData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCMovementBoneData_class;
		p->proto = jsb_CCMovementBoneData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCMovementData_class;
JSObject *jsb_CCMovementData_prototype;

JSBool js_jsb_CCDatas_CCMovementData_getMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCMovementData* cobj = (cocos2d::extension::CCMovementData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCMovementBoneData* ret = cobj->getMovementBoneData(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCMovementBoneData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCMovementData_addMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCMovementData* cobj = (cocos2d::extension::CCMovementData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCMovementBoneData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCMovementBoneData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addMovementBoneData(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCMovementData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCMovementData* ret = cocos2d::extension::CCMovementData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCMovementData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCMovementData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCMovementData* cobj = new cocos2d::extension::CCMovementData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCMovementData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCMovementData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCMovementData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCMovementData)", obj);
}

static JSBool js_jsb_CCDatas_CCMovementData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCMovementData *nobj = new cocos2d::extension::CCMovementData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCMovementData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCMovementData(JSContext *cx, JSObject *global) {
	jsb_CCMovementData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCMovementData_class->name = "MovementData";
	jsb_CCMovementData_class->addProperty = JS_PropertyStub;
	jsb_CCMovementData_class->delProperty = JS_PropertyStub;
	jsb_CCMovementData_class->getProperty = JS_PropertyStub;
	jsb_CCMovementData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCMovementData_class->enumerate = JS_EnumerateStub;
	jsb_CCMovementData_class->resolve = JS_ResolveStub;
	jsb_CCMovementData_class->convert = JS_ConvertStub;
	jsb_CCMovementData_class->finalize = js_jsb_CCDatas_CCMovementData_finalize;
	jsb_CCMovementData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getMovementBoneData", js_jsb_CCDatas_CCMovementData_getMovementBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addMovementBoneData", js_jsb_CCDatas_CCMovementData_addMovementBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCMovementData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCMovementData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCMovementData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCMovementData_class,
		js_jsb_CCDatas_CCMovementData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "MovementData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCMovementData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCMovementData_class;
		p->proto = jsb_CCMovementData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCAnimationData_class;
JSObject *jsb_CCAnimationData_prototype;

JSBool js_jsb_CCDatas_CCAnimationData_getMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCAnimationData* cobj = (cocos2d::extension::CCAnimationData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCMovementData* ret = cobj->getMovement(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCMovementData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCAnimationData_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCAnimationData* cobj = (cocos2d::extension::CCAnimationData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getMovementCount();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCAnimationData_addMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCAnimationData* cobj = (cocos2d::extension::CCAnimationData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCMovementData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCMovementData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addMovement(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCAnimationData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCAnimationData* ret = cocos2d::extension::CCAnimationData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCAnimationData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCAnimationData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCAnimationData* cobj = new cocos2d::extension::CCAnimationData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCAnimationData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCAnimationData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCAnimationData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCAnimationData)", obj);
}

static JSBool js_jsb_CCDatas_CCAnimationData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCAnimationData *nobj = new cocos2d::extension::CCAnimationData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCAnimationData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCAnimationData(JSContext *cx, JSObject *global) {
	jsb_CCAnimationData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCAnimationData_class->name = "AnimationData";
	jsb_CCAnimationData_class->addProperty = JS_PropertyStub;
	jsb_CCAnimationData_class->delProperty = JS_PropertyStub;
	jsb_CCAnimationData_class->getProperty = JS_PropertyStub;
	jsb_CCAnimationData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCAnimationData_class->enumerate = JS_EnumerateStub;
	jsb_CCAnimationData_class->resolve = JS_ResolveStub;
	jsb_CCAnimationData_class->convert = JS_ConvertStub;
	jsb_CCAnimationData_class->finalize = js_jsb_CCDatas_CCAnimationData_finalize;
	jsb_CCAnimationData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getMovement", js_jsb_CCDatas_CCAnimationData_getMovement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMovementCount", js_jsb_CCDatas_CCAnimationData_getMovementCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addMovement", js_jsb_CCDatas_CCAnimationData_addMovement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCAnimationData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCAnimationData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCAnimationData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCAnimationData_class,
		js_jsb_CCDatas_CCAnimationData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "AnimationData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCAnimationData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCAnimationData_class;
		p->proto = jsb_CCAnimationData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCContourData_class;
JSObject *jsb_CCContourData_prototype;

JSBool js_jsb_CCDatas_CCContourData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCContourData* cobj = (cocos2d::extension::CCContourData *)(proxy ? proxy->ptr : NULL);
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
JSBool js_jsb_CCDatas_CCContourData_addVertex(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCContourData* cobj = (cocos2d::extension::CCContourData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCPoint* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::CCPoint*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addVertex(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCContourData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCContourData* ret = cocos2d::extension::CCContourData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCContourData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCContourData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCContourData* cobj = new cocos2d::extension::CCContourData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCContourData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCContourData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCContourData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCContourData)", obj);
}

static JSBool js_jsb_CCDatas_CCContourData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCContourData *nobj = new cocos2d::extension::CCContourData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCContourData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCContourData(JSContext *cx, JSObject *global) {
	jsb_CCContourData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCContourData_class->name = "ContourData";
	jsb_CCContourData_class->addProperty = JS_PropertyStub;
	jsb_CCContourData_class->delProperty = JS_PropertyStub;
	jsb_CCContourData_class->getProperty = JS_PropertyStub;
	jsb_CCContourData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCContourData_class->enumerate = JS_EnumerateStub;
	jsb_CCContourData_class->resolve = JS_ResolveStub;
	jsb_CCContourData_class->convert = JS_ConvertStub;
	jsb_CCContourData_class->finalize = js_jsb_CCDatas_CCContourData_finalize;
	jsb_CCContourData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("init", js_jsb_CCDatas_CCContourData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addVertex", js_jsb_CCDatas_CCContourData_addVertex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCContourData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCContourData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCContourData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCContourData_class,
		js_jsb_CCDatas_CCContourData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ContourData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCContourData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCContourData_class;
		p->proto = jsb_CCContourData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_CCTextureData_class;
JSObject *jsb_CCTextureData_prototype;

JSBool js_jsb_CCDatas_CCTextureData_getContourData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCTextureData* cobj = (cocos2d::extension::CCTextureData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::extension::CCContourData* ret = cobj->getContourData(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCContourData>(cx, ret);
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
JSBool js_jsb_CCDatas_CCTextureData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCTextureData* cobj = (cocos2d::extension::CCTextureData *)(proxy ? proxy->ptr : NULL);
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
JSBool js_jsb_CCDatas_CCTextureData_addContourData(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCTextureData* cobj = (cocos2d::extension::CCTextureData *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::extension::CCContourData* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg0 = (cocos2d::extension::CCContourData*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->addContourData(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_jsb_CCDatas_CCTextureData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCTextureData* ret = cocos2d::extension::CCTextureData::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCTextureData>(cx, ret);
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

JSBool js_jsb_CCDatas_CCTextureData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::extension::CCTextureData* cobj = new cocos2d::extension::CCTextureData();
		cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
		if (_ccobj) {
			_ccobj->autorelease();
		}
		TypeTest<cocos2d::extension::CCTextureData> t;
		js_type_class_t *typeClass;
		uint32_t typeId = t.s_id();
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
		assert(typeClass);
		JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		// link the native object with the javascript object
		js_proxy_t* p = jsb_new_proxy(cobj, obj);
		JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCTextureData");
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}




void js_jsb_CCDatas_CCTextureData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCTextureData)", obj);
}

static JSBool js_jsb_CCDatas_CCTextureData_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    cocos2d::extension::CCTextureData *nobj = new cocos2d::extension::CCTextureData();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    nobj->autorelease();
    JS_AddNamedObjectRoot(cx, &p->obj, "cocos2d::extension::CCTextureData");
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_jsb_CCDatas_CCTextureData(JSContext *cx, JSObject *global) {
	jsb_CCTextureData_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_CCTextureData_class->name = "TextureData";
	jsb_CCTextureData_class->addProperty = JS_PropertyStub;
	jsb_CCTextureData_class->delProperty = JS_PropertyStub;
	jsb_CCTextureData_class->getProperty = JS_PropertyStub;
	jsb_CCTextureData_class->setProperty = JS_StrictPropertyStub;
	jsb_CCTextureData_class->enumerate = JS_EnumerateStub;
	jsb_CCTextureData_class->resolve = JS_ResolveStub;
	jsb_CCTextureData_class->convert = JS_ConvertStub;
	jsb_CCTextureData_class->finalize = js_jsb_CCDatas_CCTextureData_finalize;
	jsb_CCTextureData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getContourData", js_jsb_CCDatas_CCTextureData_getContourData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_jsb_CCDatas_CCTextureData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("addContourData", js_jsb_CCDatas_CCTextureData_addContourData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_jsb_CCDatas_CCTextureData_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_jsb_CCDatas_CCTextureData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_CCTextureData_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_CCTextureData_class,
		js_jsb_CCDatas_CCTextureData_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "TextureData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::extension::CCTextureData> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_CCTextureData_class;
		p->proto = jsb_CCTextureData_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj) {
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

	js_register_jsb_CCDatas_CCContourData(cx, obj);
	js_register_jsb_CCDatas_CCMovementData(cx, obj);
	js_register_jsb_CCDatas_CCMovementBoneData(cx, obj);
	js_register_jsb_CCDatas_CCDisplayData(cx, obj);
	js_register_jsb_CCDatas_CCSpriteDisplayData(cx, obj);
	js_register_jsb_CCDatas_CCAnimationData(cx, obj);
	js_register_jsb_CCDatas_CCParticleDisplayData(cx, obj);
	js_register_jsb_CCDatas_CCBaseData(cx, obj);
	js_register_jsb_CCDatas_CCTextureData(cx, obj);
	js_register_jsb_CCDatas_CCFrameData(cx, obj);
	js_register_jsb_CCDatas_CCBoneData(cx, obj);
	js_register_jsb_CCDatas_CCArmatureData(cx, obj);
	js_register_jsb_CCDatas_CCArmatureDisplayData(cx, obj);
}

