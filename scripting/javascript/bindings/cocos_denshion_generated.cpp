#include "cocos_denshion_generated.hpp"

JSClass* S_SimpleAudioEngine::jsClass = NULL;
JSObject* S_SimpleAudioEngine::jsObject = NULL;

JSBool S_SimpleAudioEngine::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_SimpleAudioEngine::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_SimpleAudioEngine *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_SimpleAudioEngine::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_SimpleAudioEngine *cobj; JSGET_PTRSHELL(S_SimpleAudioEngine, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kBackgroundMusicVolume:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getBackgroundMusicVolume(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEffectsVolume:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEffectsVolume(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_SimpleAudioEngine::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_SimpleAudioEngine *cobj; JSGET_PTRSHELL(S_SimpleAudioEngine, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kBackgroundMusicVolume:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setBackgroundMusicVolume(tmp); } while (0);
		break;
	case kEffectsVolume:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEffectsVolume(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_SimpleAudioEngine::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
{
	jsClass = (JSClass *)calloc(1, sizeof(JSClass));
	jsClass->name = name;
	jsClass->addProperty = JS_PropertyStub;
	jsClass->delProperty = JS_PropertyStub;
	jsClass->getProperty = JS_PropertyStub;
	jsClass->setProperty = JS_StrictPropertyStub;
	jsClass->enumerate = JS_EnumerateStub;
	jsClass->resolve = JS_ResolveStub;
	jsClass->convert = JS_ConvertStub;
	jsClass->finalize = jsFinalize;
	jsClass->flags = JSCLASS_HAS_PRIVATE;
		static JSPropertySpec properties[] = {
			{"backgroundMusicVolume", kBackgroundMusicVolume, JSPROP_PERMANENT | JSPROP_SHARED, S_SimpleAudioEngine::jsPropertyGet, S_SimpleAudioEngine::jsPropertySet},
			{"effectsVolume", kEffectsVolume, JSPROP_PERMANENT | JSPROP_SHARED, S_SimpleAudioEngine::jsPropertyGet, S_SimpleAudioEngine::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("preloadBackgroundMusic", S_SimpleAudioEngine::jspreloadBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("playBackgroundMusic", S_SimpleAudioEngine::jsplayBackgroundMusic, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopBackgroundMusic", S_SimpleAudioEngine::jsstopBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pauseBackgroundMusic", S_SimpleAudioEngine::jspauseBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resumeBackgroundMusic", S_SimpleAudioEngine::jsresumeBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("rewindBackgroundMusic", S_SimpleAudioEngine::jsrewindBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("willPlayBackgroundMusic", S_SimpleAudioEngine::jswillPlayBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isBackgroundMusicPlaying", S_SimpleAudioEngine::jsisBackgroundMusicPlaying, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("playEffect", S_SimpleAudioEngine::jsplayEffect, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pauseEffect", S_SimpleAudioEngine::jspauseEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pauseAllEffects", S_SimpleAudioEngine::jspauseAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resumeEffect", S_SimpleAudioEngine::jsresumeEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resumeAllEffects", S_SimpleAudioEngine::jsresumeAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopEffect", S_SimpleAudioEngine::jsstopEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopAllEffects", S_SimpleAudioEngine::jsstopAllEffects, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("preloadEffect", S_SimpleAudioEngine::jspreloadEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unloadEffect", S_SimpleAudioEngine::jsunloadEffect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedEngine", S_SimpleAudioEngine::jssharedEngine, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("end", S_SimpleAudioEngine::jsend, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_SimpleAudioEngine::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_SimpleAudioEngine::jssharedEngine(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		SimpleAudioEngine* ret = SimpleAudioEngine::sharedEngine();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_SimpleAudioEngine::jsClass, S_SimpleAudioEngine::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)ret;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
		} while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsend(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		SimpleAudioEngine::end();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jspreloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->preloadBackgroundMusic(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsplayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sb", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->playBackgroundMusic(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsstopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->stopBackgroundMusic(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jspauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->pauseBackgroundMusic();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsresumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->resumeBackgroundMusic();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsrewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->rewindBackgroundMusic();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jswillPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->willPlayBackgroundMusic();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsisBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->isBackgroundMusicPlaying();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsplayEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sb", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		unsigned int ret = self->playEffect(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jspauseEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->pauseEffect(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jspauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->pauseAllEffects();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsresumeEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->resumeEffect(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsresumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->resumeAllEffects();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsstopEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->stopEffect(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsstopAllEffects(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->stopAllEffects();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jspreloadEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->preloadEffect(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_SimpleAudioEngine::jsunloadEffect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_SimpleAudioEngine* self = NULL; JSGET_PTRSHELL(S_SimpleAudioEngine, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->unloadEffect(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

