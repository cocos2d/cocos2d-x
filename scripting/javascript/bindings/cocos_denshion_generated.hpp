
#ifndef __cocos_denshion_generated__h
#define __cocos_denshion_generated__h

#include "ScriptingCore.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
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

class S_SimpleAudioEngine : public CocosDenshion::SimpleAudioEngine
{
	JSObject *m_jsobj;
public:
	static JSClass *jsClass;
	static JSObject *jsObject;

	enum {
		kBackgroundMusicVolume = 1,
		kEffectsVolume
	};

	static JSBool jsConstructor(JSContext *cx, uint32_t argc, jsval *vp);
	static void jsFinalize(JSContext *cx, JSObject *obj);
	static JSBool jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val);
	static JSBool jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val);
	static void jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name);
	static JSBool jssharedEngine(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsend(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspreloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsplayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsresumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsrewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jswillPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsisBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsplayEffect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspauseEffect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsresumeEffect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsresumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopEffect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsstopAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jspreloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool jsunloadEffect(JSContext *cx, uint32_t argc, jsval *vp);

};

#endif

