
#ifndef __simple_native_generated__h
#define __simple_native_generated__h

#include "ScriptingCore.h"
#include "cocos2d.h"
#include "simple_class.h"
#include "cocos2d_generated.hpp"

using namespace cocos2d;

#define JSGET_PTRSHELL(type, cobj, jsobj) do { \
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(jsobj); \
	if (pt) { \
		cobj = (type *)pt->data; \
	} else { \
		cobj = NULL; \
	} \
} while (0)

#define MENU_ITEM_ACTION(klass) \
void klass::menuAction(cocos2d::CCObject *o) \
{ \
	if (m_jsobj) { \
		JSBool hasMethod; \
		JSContext *cx = ScriptingCore::getInstance().getGlobalContext(); \
		JS_HasProperty(cx, m_jsobj, "action", &hasMethod); \
		if (hasMethod == JS_TRUE) { \
			jsval callback, rval; \
			JS_GetProperty(cx, m_jsobj, "action", &callback); \
			JS_CallFunctionValue(cx, m_jsobj, callback, 0, 0, &rval); \
		} \
	} \
}

class S_AnotherClass : public SomeNamespace::AnotherClass
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_AnotherClass(JSObject *obj) : AnotherClass(), m_jsobj(obj) {};
	enum {
		kAPublicField = 1,
		kJustOneField
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsdoSomethingSimple(JSContext *cx, uint32_t argc, jsval *vp);

};

class S_SimpleNativeClass : public SimpleNativeClass
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	S_SimpleNativeClass(JSObject *obj) : SimpleNativeClass(), m_jsobj(obj) {};
	enum {
		kSomeField = 1,
		kSomeOtherField,
		kAnotherMoreComplexField
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jsdoSomeProcessing(JSContext *cx, uint32_t argc, jsval *vp);

};

void register_enums_simple_native_generated(JSObject *global);

#endif

