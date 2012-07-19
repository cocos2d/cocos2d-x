#include "cocos2d_generated.hpp"

JSClass* S_CCTransitionMoveInL::jsClass = NULL;
JSObject* S_CCTransitionMoveInL::jsObject = NULL;

JSBool S_CCTransitionMoveInL::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionMoveInL::jsClass, S_CCTransitionMoveInL::jsObject, NULL);
	S_CCTransitionMoveInL *cobj = new S_CCTransitionMoveInL(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionMoveInL::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionMoveInL *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionMoveInL::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInL *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionMoveInL::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInL *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionMoveInL::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionMoveInL::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("action", S_CCTransitionMoveInL::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("easeActionWithAction", S_CCTransitionMoveInL::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionMoveInL::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionMoveInL::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionMoveInL::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionMoveInL::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionMoveInL::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
void S_CCTransitionMoveInL::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionMoveInL::onEnter();
}
JSBool S_CCTransitionMoveInL::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionMoveInL* ret = CCTransitionMoveInL::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionMoveInL::jsClass, S_CCTransitionMoveInL::jsObject, NULL);
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

JSClass* S_CCAnimate::jsClass = NULL;
JSObject* S_CCAnimate::jsObject = NULL;

JSBool S_CCAnimate::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAnimate::jsClass, S_CCAnimate::jsObject, NULL);
	S_CCAnimate *cobj = new S_CCAnimate(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAnimate::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAnimate *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAnimate::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimate *cobj; JSGET_PTRSHELL(S_CCAnimate, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAnimation:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimation::jsClass, S_CCAnimation::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getAnimation();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAnimate::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimate *cobj; JSGET_PTRSHELL(S_CCAnimate, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAnimation:
		do {
			CCAnimation* tmp; JSGET_PTRSHELL(CCAnimation, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setAnimation(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAnimate::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"animation", kAnimation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimate::jsPropertyGet, S_CCAnimate::jsPropertySet},
			{"origFrame", kOrigFrame, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimate::jsPropertyGet, S_CCAnimate::jsPropertySet},
			{"restoreOriginalFrame", kRestoreOriginalFrame, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimate::jsPropertyGet, S_CCAnimate::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAnimation", S_CCAnimate::jsinitWithAnimation, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCAnimate::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCAnimate::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCAnimate::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAnimation", S_CCAnimate::jsactionWithAnimation, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCAnimate::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAnimate::jsinitWithAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCAnimation* narg0; JSGET_PTRSHELL(CCAnimation, narg0, arg0);
		bool ret = self->initWithAnimation(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimate::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimate::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimate::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimate::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCAnimate::jsactionWithAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCAnimation* narg0; JSGET_PTRSHELL(CCAnimation, narg0, arg0);
		CCAnimate* ret = CCAnimate::actionWithAnimation(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimate::jsClass, S_CCAnimate::jsObject, NULL);
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

JSClass* S_CCFadeOutBLTiles::jsClass = NULL;
JSObject* S_CCFadeOutBLTiles::jsObject = NULL;

JSBool S_CCFadeOutBLTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeOutBLTiles::jsClass, S_CCFadeOutBLTiles::jsObject, NULL);
	S_CCFadeOutBLTiles *cobj = new S_CCFadeOutBLTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeOutBLTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeOutBLTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeOutBLTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutBLTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutBLTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeOutBLTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutBLTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutBLTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeOutBLTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("testFunc", S_CCFadeOutBLTiles::jstestFunc, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCFadeOutBLTiles::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFadeOutTRTiles::jsObject,jsClass,S_CCFadeOutBLTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeOutBLTiles::jstestFunc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutBLTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutBLTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		float ret = self->testFunc(*narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutBLTiles::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCFadeOutBLTiles* ret = CCFadeOutBLTiles::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeOutBLTiles::jsClass, S_CCFadeOutBLTiles::jsObject, NULL);
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

JSClass* S_CCProgressFromTo::jsClass = NULL;
JSObject* S_CCProgressFromTo::jsObject = NULL;

JSBool S_CCProgressFromTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCProgressFromTo::jsClass, S_CCProgressFromTo::jsObject, NULL);
	S_CCProgressFromTo *cobj = new S_CCProgressFromTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCProgressFromTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCProgressFromTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCProgressFromTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressFromTo *cobj; JSGET_PTRSHELL(S_CCProgressFromTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCProgressFromTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressFromTo *cobj; JSGET_PTRSHELL(S_CCProgressFromTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCProgressFromTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"to", kTo, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressFromTo::jsPropertyGet, S_CCProgressFromTo::jsPropertySet},
			{"from", kFrom, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressFromTo::jsPropertyGet, S_CCProgressFromTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCProgressFromTo::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCProgressFromTo::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCProgressFromTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCProgressFromTo::jsactionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCProgressFromTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCProgressFromTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressFromTo* self = NULL; JSGET_PTRSHELL(S_CCProgressFromTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		bool ret = self->initWithDuration(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressFromTo::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressFromTo* self = NULL; JSGET_PTRSHELL(S_CCProgressFromTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCProgressFromTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressFromTo* self = NULL; JSGET_PTRSHELL(S_CCProgressFromTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressFromTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressFromTo* self = NULL; JSGET_PTRSHELL(S_CCProgressFromTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressFromTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		CCProgressFromTo* ret = CCProgressFromTo::actionWithDuration(arg0, arg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCProgressFromTo::jsClass, S_CCProgressFromTo::jsObject, NULL);
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

JSClass* S_CCLayer::jsClass = NULL;
JSObject* S_CCLayer::jsObject = NULL;

JSBool S_CCLayer::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLayer::jsClass, S_CCLayer::jsObject, NULL);
	S_CCLayer *cobj = new S_CCLayer(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLayer::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLayer *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLayer::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayer *cobj; JSGET_PTRSHELL(S_CCLayer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kIsTouchEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isTouchEnabled()));
		break;
	case kIsAccelerometerEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isAccelerometerEnabled()));
		break;
	case kIsKeypadEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isKeypadEnabled()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLayer::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayer *cobj; JSGET_PTRSHELL(S_CCLayer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kIsTouchEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setTouchEnabled(tmp); } while (0);
		break;
	case kIsAccelerometerEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setAccelerometerEnabled(tmp); } while (0);
		break;
	case kIsKeypadEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setKeypadEnabled(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLayer::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"isTouchEnabled", kIsTouchEnabled, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayer::jsPropertyGet, S_CCLayer::jsPropertySet},
			{"isAccelerometerEnabled", kIsAccelerometerEnabled, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayer::jsPropertyGet, S_CCLayer::jsPropertySet},
			{"isKeypadEnabled", kIsKeypadEnabled, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayer::jsPropertyGet, S_CCLayer::jsPropertySet},
			{"scriptHandlerEntry", kScriptHandlerEntry, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayer::jsPropertyGet, S_CCLayer::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCLayer::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("didAccelerate", S_CCLayer::jsdidAccelerate, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("registerWithTouchDispatcher", S_CCLayer::jsregisterWithTouchDispatcher, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("registerScriptTouchHandler", S_CCLayer::jsregisterScriptTouchHandler, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unregisterScriptTouchHandler", S_CCLayer::jsunregisterScriptTouchHandler, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCLayer::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLayer::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayer* self = NULL; JSGET_PTRSHELL(S_CCLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCLayer::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCLayer::onEnter();
}
void S_CCLayer::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCLayer::onExit();
}
void S_CCLayer::onEnterTransitionDidFinish() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCLayer::onEnterTransitionDidFinish();
}
bool S_CCLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchBegan", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchBegan", &fval);
			pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			shell->flags = kPointerTemporary;
			shell->data = (void *)pTouch;
			JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
			JS_SetPrivate(tmp, shell);
			jsval arg = OBJECT_TO_JSVAL(tmp);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
			JSBool ret = false;
			JS_ValueToBoolean(cx, rval, &ret);
			return ret;
		}
	}
	return false;
}
void S_CCLayer::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchMoved", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchMoved", &fval);
			pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			shell->flags = kPointerTemporary;
			shell->data = (void *)pTouch;
			JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
			JS_SetPrivate(tmp, shell);
			jsval arg = OBJECT_TO_JSVAL(tmp);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
		}
	}
}
void S_CCLayer::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchEnded", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchEnded", &fval);
			pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			shell->flags = kPointerTemporary;
			shell->data = (void *)pTouch;
			JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
			JS_SetPrivate(tmp, shell);
			jsval arg = OBJECT_TO_JSVAL(tmp);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
		}
	}
}
void S_CCLayer::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchCancelled", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchCancelled", &fval);
			pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			shell->flags = kPointerTemporary;
			shell->data = (void *)pTouch;
			JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
			JS_SetPrivate(tmp, shell);
			jsval arg = OBJECT_TO_JSVAL(tmp);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
		}
	}
}
void S_CCLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchesBegan", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchesBegan", &fval);
			jsval *touches = new jsval[pTouches->count()];
			CCTouch *pTouch;
			CCSetIterator setIter;
			int i=0;
			for (setIter = pTouches->begin(); setIter != pTouches->end(); setIter++, i++) {
				pTouch = (CCTouch *)(*setIter);
				CCPoint pt = pTouch->locationInView();
				//CCTouch *touch = new CCTouch(pt.x, pt.y);
                CCTouch *touch = new CCTouch;
                touch->setTouchInfo(pTouch->getID(), pt.x, pt.y);
				pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				shell->flags = kPointerTemporary;
				shell->data = (void *)touch;
				JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
				JS_SetPrivate(tmp, shell);
				touches[i] = OBJECT_TO_JSVAL(tmp);
			}
			JSObject *array = JS_NewArrayObject(cx, pTouches->count(), touches);
			jsval arg = OBJECT_TO_JSVAL(array);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
			delete[] touches;
		}
	}
}
void S_CCLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchesMoved", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchesMoved", &fval);
			jsval *touches = new jsval[pTouches->count()];
			CCTouch *pTouch;
			CCSetIterator setIter;
			int i=0;
			for (setIter = pTouches->begin(); setIter != pTouches->end(); setIter++, i++) {
				pTouch = (CCTouch *)(*setIter);
				CCPoint pt = pTouch->locationInView();
				CCTouch *touch = new CCTouch;
                touch->setTouchInfo(pTouch->getID(), pt.x, pt.y);
				pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				shell->flags = kPointerTemporary;
				shell->data = (void *)touch;
				JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
				JS_SetPrivate(tmp, shell);
				touches[i] = OBJECT_TO_JSVAL(tmp);
			}
			JSObject *array = JS_NewArrayObject(cx, pTouches->count(), touches);
			jsval arg = OBJECT_TO_JSVAL(array);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
			delete[] touches;
		}
	}
}
void S_CCLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchesEnded", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchesEnded", &fval);
			jsval *touches = new jsval[pTouches->count()];
			CCTouch *pTouch;
			CCSetIterator setIter;
			int i=0;
			for (setIter = pTouches->begin(); setIter != pTouches->end(); setIter++, i++) {
				pTouch = (CCTouch *)(*setIter);
				CCPoint pt = pTouch->locationInView();
				CCTouch *touch = new CCTouch; //(pt.x, pt.y);
                touch->setTouchInfo(pTouch->getID(), pt.x, pt.y);
				pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				shell->flags = kPointerTemporary;
				shell->data = (void *)touch;
				JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
				JS_SetPrivate(tmp, shell);
				touches[i] = OBJECT_TO_JSVAL(tmp);
			}
			JSObject *array = JS_NewArrayObject(cx, pTouches->count(), touches);
			jsval arg = OBJECT_TO_JSVAL(array);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
			delete[] touches;
		}
	}
}
void S_CCLayer::ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "ccTouchesCancelled", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "ccTouchesCancelled", &fval);
			jsval *touches = new jsval[pTouches->count()];
			CCTouch *pTouch;
			CCSetIterator setIter;
			int i=0;
			for (setIter = pTouches->begin(); setIter != pTouches->end(); setIter++, i++) {
				pTouch = (CCTouch *)(*setIter);
				CCPoint pt = pTouch->locationInView();
				CCTouch *touch = new CCTouch; //(pt.x, pt.y);
                touch->setTouchInfo(pTouch->getID(), pt.x, pt.y);
				pointerShell_t *shell = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				shell->flags = kPointerTemporary;
				shell->data = (void *)touch;
				JSObject *tmp = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
				JS_SetPrivate(tmp, shell);
				touches[i] = OBJECT_TO_JSVAL(tmp);
			}
			JSObject *array = JS_NewArrayObject(cx, pTouches->count(), touches);
			jsval arg = OBJECT_TO_JSVAL(array);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &arg, &rval);
			delete[] touches;
		}
	}
}
JSBool S_CCLayer::jsdidAccelerate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayer* self = NULL; JSGET_PTRSHELL(S_CCLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCAcceleration* narg0; JSGET_PTRSHELL(CCAcceleration, narg0, arg0);
		self->didAccelerate(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayer::jsregisterWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayer* self = NULL; JSGET_PTRSHELL(S_CCLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->registerWithTouchDispatcher();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayer::jsregisterScriptTouchHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayer* self = NULL; JSGET_PTRSHELL(S_CCLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		int arg2;
		JSBool arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibib", &arg0, &arg1, &arg2, &arg3);
		self->registerScriptTouchHandler(arg0, arg1, arg2, arg3);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayer::jsunregisterScriptTouchHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayer* self = NULL; JSGET_PTRSHELL(S_CCLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unregisterScriptTouchHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCLayer::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCEaseBackInOut::jsClass = NULL;
JSObject* S_CCEaseBackInOut::jsObject = NULL;

JSBool S_CCEaseBackInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBackInOut::jsClass, S_CCEaseBackInOut::jsObject, NULL);
	S_CCEaseBackInOut *cobj = new S_CCEaseBackInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBackInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBackInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBackInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackInOut *cobj; JSGET_PTRSHELL(S_CCEaseBackInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBackInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackInOut *cobj; JSGET_PTRSHELL(S_CCEaseBackInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBackInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBackInOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseBackInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBackInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBackInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBackInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBackInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBackInOut* ret = CCEaseBackInOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBackInOut::jsClass, S_CCEaseBackInOut::jsObject, NULL);
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

JSClass* S_CCFadeOutUpTiles::jsClass = NULL;
JSObject* S_CCFadeOutUpTiles::jsObject = NULL;

JSBool S_CCFadeOutUpTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeOutUpTiles::jsClass, S_CCFadeOutUpTiles::jsObject, NULL);
	S_CCFadeOutUpTiles *cobj = new S_CCFadeOutUpTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeOutUpTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeOutUpTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeOutUpTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutUpTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutUpTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeOutUpTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutUpTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutUpTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeOutUpTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("testFunc", S_CCFadeOutUpTiles::jstestFunc, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transformTile", S_CCFadeOutUpTiles::jstransformTile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCFadeOutUpTiles::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFadeOutTRTiles::jsObject,jsClass,S_CCFadeOutUpTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeOutUpTiles::jstestFunc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutUpTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutUpTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		float ret = self->testFunc(*narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutUpTiles::jstransformTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutUpTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutUpTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->transformTile(*narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutUpTiles::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCFadeOutUpTiles* ret = CCFadeOutUpTiles::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeOutUpTiles::jsClass, S_CCFadeOutUpTiles::jsObject, NULL);
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

JSClass* S_CCAnimationCache::jsClass = NULL;
JSObject* S_CCAnimationCache::jsObject = NULL;

JSBool S_CCAnimationCache::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCAnimationCache::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAnimationCache *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAnimationCache::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimationCache *cobj; JSGET_PTRSHELL(S_CCAnimationCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAnimationCache::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimationCache *cobj; JSGET_PTRSHELL(S_CCAnimationCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAnimationCache::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"animations", kAnimations, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimationCache::jsPropertyGet, S_CCAnimationCache::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("addAnimation", S_CCAnimationCache::jsaddAnimation, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAnimationByName", S_CCAnimationCache::jsremoveAnimationByName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("animationByName", S_CCAnimationCache::jsanimationByName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("init", S_CCAnimationCache::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedAnimationCache", S_CCAnimationCache::jssharedAnimationCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeSharedAnimationCache", S_CCAnimationCache::jspurgeSharedAnimationCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCAnimationCache::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAnimationCache::jssharedAnimationCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCAnimationCache* ret = CCAnimationCache::sharedAnimationCache();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimationCache::jsClass, S_CCAnimationCache::jsObject, NULL);
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
JSBool S_CCAnimationCache::jspurgeSharedAnimationCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCAnimationCache::purgeSharedAnimationCache();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimationCache::jsaddAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimationCache* self = NULL; JSGET_PTRSHELL(S_CCAnimationCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oS", &arg0, &arg1);
		CCAnimation* narg0; JSGET_PTRSHELL(CCAnimation, narg0, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		self->addAnimation(narg0, narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimationCache::jsremoveAnimationByName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimationCache* self = NULL; JSGET_PTRSHELL(S_CCAnimationCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->removeAnimationByName(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimationCache::jsanimationByName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimationCache* self = NULL; JSGET_PTRSHELL(S_CCAnimationCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCAnimation* ret = self->animationByName(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimation::jsClass, S_CCAnimation::jsObject, NULL);
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
JSBool S_CCAnimationCache::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimationCache* self = NULL; JSGET_PTRSHELL(S_CCAnimationCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCPlace::jsClass = NULL;
JSObject* S_CCPlace::jsObject = NULL;

JSBool S_CCPlace::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCPlace::jsClass, S_CCPlace::jsObject, NULL);
	S_CCPlace *cobj = new S_CCPlace(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCPlace::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCPlace *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCPlace::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPlace *cobj; JSGET_PTRSHELL(S_CCPlace, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCPlace::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPlace *cobj; JSGET_PTRSHELL(S_CCPlace, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCPlace::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPlace::jsPropertyGet, S_CCPlace::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithPosition", S_CCPlace::jsinitWithPosition, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCPlace::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithPosition", S_CCPlace::jsactionWithPosition, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCPlace::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCPlace::jsactionWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPlace* ret = CCPlace::actionWithPosition(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPlace::jsClass, S_CCPlace::jsObject, NULL);
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
JSBool S_CCPlace::jsinitWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCPlace* self = NULL; JSGET_PTRSHELL(S_CCPlace, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		bool ret = self->initWithPosition(*narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCPlace::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCPlace* self = NULL; JSGET_PTRSHELL(S_CCPlace, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCEaseBackOut::jsClass = NULL;
JSObject* S_CCEaseBackOut::jsObject = NULL;

JSBool S_CCEaseBackOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBackOut::jsClass, S_CCEaseBackOut::jsObject, NULL);
	S_CCEaseBackOut *cobj = new S_CCEaseBackOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBackOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBackOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBackOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackOut *cobj; JSGET_PTRSHELL(S_CCEaseBackOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBackOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackOut *cobj; JSGET_PTRSHELL(S_CCEaseBackOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBackOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseBackOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBackOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseBackOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBackOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBackOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBackOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBackOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBackOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBackOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseBackOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBackOut* ret = CCEaseBackOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBackOut::jsClass, S_CCEaseBackOut::jsObject, NULL);
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

JSClass* S_CCLabelBMFont::jsClass = NULL;
JSObject* S_CCLabelBMFont::jsObject = NULL;

JSBool S_CCLabelBMFont::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLabelBMFont::jsClass, S_CCLabelBMFont::jsObject, NULL);
	S_CCLabelBMFont *cobj = new S_CCLabelBMFont(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLabelBMFont::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLabelBMFont *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLabelBMFont::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelBMFont *cobj; JSGET_PTRSHELL(S_CCLabelBMFont, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
				// don't know what this is (c ~> js)
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	case kString:
				// don't know what this is (c ~> js)
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLabelBMFont::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelBMFont *cobj; JSGET_PTRSHELL(S_CCLabelBMFont, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setColor(color);
		} while (0);
		break;
	case kIsOpacityModifyRGB:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setOpacityModifyRGB(tmp); } while (0);
		break;
	case kString:
				// don't know what this is (js ~> c)
		break;
	case kOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLabelBMFont::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"cOpacity", kCOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{"string", kString, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{"configuration", kConfiguration, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelBMFont::jsPropertyGet, S_CCLabelBMFont::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithString", S_CCLabelBMFont::jsinitWithString, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("createFontChars", S_CCLabelBMFont::jscreateFontChars, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("purgeCachedData", S_CCLabelBMFont::jspurgeCachedData, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("labelWithString", S_CCLabelBMFont::jslabelWithString, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCSpriteBatchNode::jsObject,jsClass,S_CCLabelBMFont::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLabelBMFont::jspurgeCachedData(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCLabelBMFont::purgeCachedData();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLabelBMFont::jslabelWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCLabelBMFont* ret = CCLabelBMFont::labelWithString(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLabelBMFont::jsClass, S_CCLabelBMFont::jsObject, NULL);
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
JSBool S_CCLabelBMFont::jsinitWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelBMFont* self = NULL; JSGET_PTRSHELL(S_CCLabelBMFont, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		bool ret = self->initWithString(narg0, narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLabelBMFont::jscreateFontChars(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelBMFont* self = NULL; JSGET_PTRSHELL(S_CCLabelBMFont, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->createFontChars();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCReverseTime::jsClass = NULL;
JSObject* S_CCReverseTime::jsObject = NULL;

JSBool S_CCReverseTime::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCReverseTime::jsClass, S_CCReverseTime::jsObject, NULL);
	S_CCReverseTime *cobj = new S_CCReverseTime(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCReverseTime::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCReverseTime *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCReverseTime::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCReverseTime *cobj; JSGET_PTRSHELL(S_CCReverseTime, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCReverseTime::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCReverseTime *cobj; JSGET_PTRSHELL(S_CCReverseTime, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCReverseTime::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"other", kOther, JSPROP_PERMANENT | JSPROP_SHARED, S_CCReverseTime::jsPropertyGet, S_CCReverseTime::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCReverseTime::jsinitWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCReverseTime::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCReverseTime::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCReverseTime::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCReverseTime::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCReverseTime::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCReverseTime::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReverseTime* self = NULL; JSGET_PTRSHELL(S_CCReverseTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		bool ret = self->initWithAction(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReverseTime::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReverseTime* self = NULL; JSGET_PTRSHELL(S_CCReverseTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReverseTime::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReverseTime* self = NULL; JSGET_PTRSHELL(S_CCReverseTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReverseTime::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReverseTime* self = NULL; JSGET_PTRSHELL(S_CCReverseTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReverseTime::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReverseTime* self = NULL; JSGET_PTRSHELL(S_CCReverseTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCReverseTime::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		CCReverseTime* ret = CCReverseTime::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCReverseTime::jsClass, S_CCReverseTime::jsObject, NULL);
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

JSClass* S_CCFadeOutTRTiles::jsClass = NULL;
JSObject* S_CCFadeOutTRTiles::jsObject = NULL;

JSBool S_CCFadeOutTRTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeOutTRTiles::jsClass, S_CCFadeOutTRTiles::jsObject, NULL);
	S_CCFadeOutTRTiles *cobj = new S_CCFadeOutTRTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeOutTRTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeOutTRTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeOutTRTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutTRTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutTRTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeOutTRTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutTRTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutTRTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeOutTRTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("testFunc", S_CCFadeOutTRTiles::jstestFunc, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("turnOnTile", S_CCFadeOutTRTiles::jsturnOnTile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("turnOffTile", S_CCFadeOutTRTiles::jsturnOffTile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transformTile", S_CCFadeOutTRTiles::jstransformTile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCFadeOutTRTiles::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCFadeOutTRTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeOutTRTiles::jstestFunc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutTRTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutTRTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		float ret = self->testFunc(*narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutTRTiles::jsturnOnTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutTRTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutTRTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->turnOnTile(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutTRTiles::jsturnOffTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutTRTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutTRTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->turnOffTile(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutTRTiles::jstransformTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutTRTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutTRTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->transformTile(*narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutTRTiles::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutTRTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutTRTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutTRTiles::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCFadeOutTRTiles* ret = CCFadeOutTRTiles::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeOutTRTiles::jsClass, S_CCFadeOutTRTiles::jsObject, NULL);
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

JSClass* S_CCCamera::jsClass = NULL;
JSObject* S_CCCamera::jsObject = NULL;

JSBool S_CCCamera::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCCamera::jsClass, S_CCCamera::jsObject, NULL);
	S_CCCamera *cobj = new S_CCCamera(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCCamera::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCCamera *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCCamera::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCCamera *cobj; JSGET_PTRSHELL(S_CCCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDirty:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isDirty()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCCamera::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCCamera *cobj; JSGET_PTRSHELL(S_CCCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDirty:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDirty(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCCamera::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"eyeX", kEyeX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"eyeY", kEyeY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"eyeZ", kEyeZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"centerX", kCenterX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"centerY", kCenterY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"centerZ", kCenterZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"upX", kUpX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"upY", kUpY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"upZ", kUpZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCCamera::jsPropertyGet, S_CCCamera::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCCamera::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("restore", S_CCCamera::jsrestore, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("locate", S_CCCamera::jslocate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("getZEye", S_CCCamera::jsgetZEye, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCCamera::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCCamera::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCCamera* self = NULL; JSGET_PTRSHELL(S_CCCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->init();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCCamera::jsrestore(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCCamera* self = NULL; JSGET_PTRSHELL(S_CCCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->restore();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCCamera::jslocate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCCamera* self = NULL; JSGET_PTRSHELL(S_CCCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->locate();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCCamera::jsgetZEye(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		float ret = CCCamera::getZEye();
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCMenu::jsClass = NULL;
JSObject* S_CCMenu::jsObject = NULL;

JSBool S_CCMenu::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMenu::jsClass, S_CCMenu::jsObject, NULL);
	S_CCMenu *cobj = new S_CCMenu(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMenu::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenu *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMenu::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenu *cobj; JSGET_PTRSHELL(S_CCMenu, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
				// don't know what this is (c ~> js)
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMenu::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenu *cobj; JSGET_PTRSHELL(S_CCMenu, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setColor(color);
		} while (0);
		break;
	case kOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMenu::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{"cOpacity", kCOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{"eState", kEState, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{"selectedItem", kSelectedItem, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenu::jsPropertyGet, S_CCMenu::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCMenu::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsVertically", S_CCMenu::jsalignItemsVertically, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsVerticallyWithPadding", S_CCMenu::jsalignItemsVerticallyWithPadding, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsHorizontally", S_CCMenu::jsalignItemsHorizontally, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsHorizontallyWithPadding", S_CCMenu::jsalignItemsHorizontallyWithPadding, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsInColumns", S_CCMenu::jsalignItemsInColumns, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("alignItemsInRows", S_CCMenu::jsalignItemsInRows, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("registerWithTouchDispatcher", S_CCMenu::jsregisterWithTouchDispatcher, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("menuWithItems", S_CCMenu::jsmenuWithItems, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("menuWithItem", S_CCMenu::jsmenuWithItem, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCLayer::jsObject,jsClass,S_CCMenu::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenu::jsmenuWithItems(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCMenuItem* narg0; JSGET_PTRSHELL(CCMenuItem, narg0, arg0);
		CCMenu* ret = CCMenu::menuWithItems(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMenu::jsClass, S_CCMenu::jsObject, NULL);
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
JSBool S_CCMenu::jsmenuWithItem(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCMenuItem* narg0; JSGET_PTRSHELL(CCMenuItem, narg0, arg0);
		CCMenu* ret = CCMenu::menuWithItem(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMenu::jsClass, S_CCMenu::jsObject, NULL);
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
JSBool S_CCMenu::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsVertically(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->alignItemsVertically();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsVerticallyWithPadding(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->alignItemsVerticallyWithPadding(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsHorizontally(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->alignItemsHorizontally();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsHorizontallyWithPadding(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->alignItemsHorizontallyWithPadding(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsInColumns(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->alignItemsInColumns(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsInRows(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->alignItemsInRows(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsregisterWithTouchDispatcher(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->registerWithTouchDispatcher();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCAction::jsClass = NULL;
JSObject* S_CCAction::jsObject = NULL;

JSBool S_CCAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAction::jsClass, S_CCAction::jsObject, NULL);
	S_CCAction *cobj = new S_CCAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAction *cobj; JSGET_PTRSHELL(S_CCAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOriginalTarget:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getOriginalTarget();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kTarget:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTarget();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kTag:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTag(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAction *cobj; JSGET_PTRSHELL(S_CCAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOriginalTarget:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setOriginalTarget(tmp); }
		} while (0);
		break;
	case kTarget:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTarget(tmp); }
		} while (0);
		break;
	case kTag:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setTag(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"originalTarget", kOriginalTarget, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAction::jsPropertyGet, S_CCAction::jsPropertySet},
			{"target", kTarget, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAction::jsPropertyGet, S_CCAction::jsPropertySet},
			{"tag", kTag, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAction::jsPropertyGet, S_CCAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("isDone", S_CCAction::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCAction::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCAction::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("action", S_CCAction::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAction::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAction* self = NULL; JSGET_PTRSHELL(S_CCAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAction::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAction* self = NULL; JSGET_PTRSHELL(S_CCAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAction::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAction* self = NULL; JSGET_PTRSHELL(S_CCAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAction::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCAction* ret = CCAction::action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAction::jsClass, S_CCAction::jsObject, NULL);
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

JSClass* S_CCTextureAtlas::jsClass = NULL;
JSObject* S_CCTextureAtlas::jsObject = NULL;

JSBool S_CCTextureAtlas::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTextureAtlas::jsClass, S_CCTextureAtlas::jsObject, NULL);
	S_CCTextureAtlas *cobj = new S_CCTextureAtlas(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTextureAtlas::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTextureAtlas *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTextureAtlas::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTextureAtlas *cobj; JSGET_PTRSHELL(S_CCTextureAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTotalQuads:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTotalQuads(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kCapacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getCapacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kTexture:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTexture();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kQuads:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getQuads();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTextureAtlas::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTextureAtlas *cobj; JSGET_PTRSHELL(S_CCTextureAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTexture:
		do {
			CCTexture2D* tmp; JSGET_PTRSHELL(CCTexture2D, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTexture(tmp); }
		} while (0);
		break;
	case kQuads:
		do {
			ccV3F_C4B_T2F_Quad* tmp; JSGET_PTRSHELL(ccV3F_C4B_T2F_Quad, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setQuads(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTextureAtlas::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"indices", kIndices, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"buffersVBO", kBuffersVBO, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"totalQuads", kTotalQuads, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"capacity", kCapacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{"quads", kQuads, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureAtlas::jsPropertyGet, S_CCTextureAtlas::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFile", S_CCTextureAtlas::jsinitWithFile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTexture", S_CCTextureAtlas::jsinitWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateQuad", S_CCTextureAtlas::jsupdateQuad, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("insertQuad", S_CCTextureAtlas::jsinsertQuad, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("insertQuadFromIndex", S_CCTextureAtlas::jsinsertQuadFromIndex, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeQuadAtIndex", S_CCTextureAtlas::jsremoveQuadAtIndex, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllQuads", S_CCTextureAtlas::jsremoveAllQuads, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resizeCapacity", S_CCTextureAtlas::jsresizeCapacity, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("drawNumberOfQuads", S_CCTextureAtlas::jsdrawNumberOfQuads, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("drawQuads", S_CCTextureAtlas::jsdrawQuads, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("textureAtlasWithFile", S_CCTextureAtlas::jstextureAtlasWithFile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("textureAtlasWithTexture", S_CCTextureAtlas::jstextureAtlasWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCTextureAtlas::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTextureAtlas::jstextureAtlasWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Si", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTextureAtlas* ret = CCTextureAtlas::textureAtlasWithFile(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTextureAtlas::jsClass, S_CCTextureAtlas::jsObject, NULL);
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
JSBool S_CCTextureAtlas::jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Si", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithFile(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jstextureAtlasWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCTextureAtlas* ret = CCTextureAtlas::textureAtlasWithTexture(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTextureAtlas::jsClass, S_CCTextureAtlas::jsObject, NULL);
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
JSBool S_CCTextureAtlas::jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		bool ret = self->initWithTexture(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsupdateQuad(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		ccV3F_C4B_T2F_Quad* narg0; JSGET_PTRSHELL(ccV3F_C4B_T2F_Quad, narg0, arg0);
		self->updateQuad(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsinsertQuad(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		ccV3F_C4B_T2F_Quad* narg0; JSGET_PTRSHELL(ccV3F_C4B_T2F_Quad, narg0, arg0);
		self->insertQuad(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsinsertQuadFromIndex(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		unsigned int arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
		self->insertQuadFromIndex(arg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsremoveQuadAtIndex(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->removeQuadAtIndex(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsremoveAllQuads(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->removeAllQuads();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsresizeCapacity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		bool ret = self->resizeCapacity(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsdrawNumberOfQuads(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->drawNumberOfQuads(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureAtlas::jsdrawQuads(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureAtlas* self = NULL; JSGET_PTRSHELL(S_CCTextureAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->drawQuads();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCMenuItemSprite::jsClass = NULL;
JSObject* S_CCMenuItemSprite::jsObject = NULL;

JSBool S_CCMenuItemSprite::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMenuItemSprite::jsClass, S_CCMenuItemSprite::jsObject, NULL);
	S_CCMenuItemSprite *cobj = new S_CCMenuItemSprite(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMenuItemSprite::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenuItemSprite *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMenuItemSprite::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemSprite *cobj; JSGET_PTRSHELL(S_CCMenuItemSprite, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kNormalImage:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getNormalImage();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kSelectedImage:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getSelectedImage();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kDisabledImage:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getDisabledImage();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kColor:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			ccColor3B* ctmp = new ccColor3B(cobj->getColor());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMenuItemSprite::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemSprite *cobj; JSGET_PTRSHELL(S_CCMenuItemSprite, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kNormalImage:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setNormalImage(tmp); }
		} while (0);
		break;
	case kSelectedImage:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setSelectedImage(tmp); }
		} while (0);
		break;
	case kDisabledImage:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setDisabledImage(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMenuItemSprite::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"normalImage", kNormalImage, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{"selectedImage", kSelectedImage, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{"disabledImage", kDisabledImage, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemSprite::jsPropertyGet, S_CCMenuItemSprite::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithNormalSprite", S_CCMenuItemSprite::jsinitWithNormalSprite, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("selected", S_CCMenuItemSprite::jsselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unselected", S_CCMenuItemSprite::jsunselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("itemWithNormalSprite", S_CCMenuItemSprite::jsitemWithNormalSprite, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMenuItem::jsObject,jsClass,S_CCMenuItemSprite::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemSprite::jsitemWithNormalSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		JSObject *arg0;
		JSObject *arg1;
		JSObject *arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ooo", &arg0, &arg1, &arg2);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCNode* narg1; JSGET_PTRSHELL(CCNode, narg1, arg1);
		CCNode* narg2; JSGET_PTRSHELL(CCNode, narg2, arg2);
		CCMenuItemSprite* ret = CCMenuItemSprite::itemWithNormalSprite(narg0, narg1, narg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMenuItemSprite::jsClass, S_CCMenuItemSprite::jsObject, NULL);
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
JSBool S_CCMenuItemSprite::jsselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemSprite* self = NULL; JSGET_PTRSHELL(S_CCMenuItemSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->selected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItemSprite::jsunselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemSprite* self = NULL; JSGET_PTRSHELL(S_CCMenuItemSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unselected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
MENU_ITEM_ACTION(S_CCMenuItemSprite)

JSClass* S_CCProgressTo::jsClass = NULL;
JSObject* S_CCProgressTo::jsObject = NULL;

JSBool S_CCProgressTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCProgressTo::jsClass, S_CCProgressTo::jsObject, NULL);
	S_CCProgressTo *cobj = new S_CCProgressTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCProgressTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCProgressTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCProgressTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressTo *cobj; JSGET_PTRSHELL(S_CCProgressTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCProgressTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressTo *cobj; JSGET_PTRSHELL(S_CCProgressTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCProgressTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"to", kTo, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTo::jsPropertyGet, S_CCProgressTo::jsPropertySet},
			{"from", kFrom, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTo::jsPropertyGet, S_CCProgressTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCProgressTo::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCProgressTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCProgressTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCProgressTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCProgressTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressTo* self = NULL; JSGET_PTRSHELL(S_CCProgressTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressTo* self = NULL; JSGET_PTRSHELL(S_CCProgressTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressTo* self = NULL; JSGET_PTRSHELL(S_CCProgressTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		CCProgressTo* ret = CCProgressTo::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCProgressTo::jsClass, S_CCProgressTo::jsObject, NULL);
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

JSClass* S_CCDelayTime::jsClass = NULL;
JSObject* S_CCDelayTime::jsObject = NULL;

JSBool S_CCDelayTime::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCDelayTime::jsClass, S_CCDelayTime::jsObject, NULL);
	S_CCDelayTime *cobj = new S_CCDelayTime(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCDelayTime::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCDelayTime *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCDelayTime::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDelayTime *cobj; JSGET_PTRSHELL(S_CCDelayTime, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCDelayTime::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDelayTime *cobj; JSGET_PTRSHELL(S_CCDelayTime, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCDelayTime::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCDelayTime::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCDelayTime::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCDelayTime::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCDelayTime::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDelayTime* self = NULL; JSGET_PTRSHELL(S_CCDelayTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDelayTime::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDelayTime* self = NULL; JSGET_PTRSHELL(S_CCDelayTime, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCDelayTime::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCDelayTime* ret = CCDelayTime::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCDelayTime::jsClass, S_CCDelayTime::jsObject, NULL);
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

JSClass* S_CCSequence::jsClass = NULL;
JSObject* S_CCSequence::jsObject = NULL;

JSBool S_CCSequence::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSequence::jsClass, S_CCSequence::jsObject, NULL);
	S_CCSequence *cobj = new S_CCSequence(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSequence::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSequence *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSequence::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSequence *cobj; JSGET_PTRSHELL(S_CCSequence, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSequence::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSequence *cobj; JSGET_PTRSHELL(S_CCSequence, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSequence::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"actions", kActions, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSequence::jsPropertyGet, S_CCSequence::jsPropertySet},
			{"split", kSplit, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSequence::jsPropertyGet, S_CCSequence::jsPropertySet},
			{"last", kLast, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSequence::jsPropertyGet, S_CCSequence::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initOneTwo", S_CCSequence::jsinitOneTwo, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSequence::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCSequence::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCSequence::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actions", S_CCSequence::jsactions, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("actionsWithArray", S_CCSequence::jsactionsWithArray, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("actionOneTwo", S_CCSequence::jsactionOneTwo, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCSequence::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSequence::jsinitOneTwo(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSequence* self = NULL; JSGET_PTRSHELL(S_CCSequence, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		CCFiniteTimeAction* narg1; JSGET_PTRSHELL(CCFiniteTimeAction, narg1, arg1);
		bool ret = self->initOneTwo(narg0, narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSequence::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSequence* self = NULL; JSGET_PTRSHELL(S_CCSequence, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSequence::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSequence* self = NULL; JSGET_PTRSHELL(S_CCSequence, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSequence::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSequence* self = NULL; JSGET_PTRSHELL(S_CCSequence, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSequence::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSequence* self = NULL; JSGET_PTRSHELL(S_CCSequence, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCSequence::jsactionsWithArray(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCArray* narg0; JSGET_PTRSHELL(CCArray, narg0, arg0);
		CCFiniteTimeAction* ret = CCSequence::actionWithArray(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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
JSBool S_CCSequence::jsactionOneTwo(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		CCFiniteTimeAction* narg1; JSGET_PTRSHELL(CCFiniteTimeAction, narg1, arg1);
		CCSequence* ret = CCSequence::actionOneTwo(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSequence::jsClass, S_CCSequence::jsObject, NULL);
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

JSClass* S_CCWavesTiles3D::jsClass = NULL;
JSObject* S_CCWavesTiles3D::jsObject = NULL;

JSBool S_CCWavesTiles3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCWavesTiles3D::jsClass, S_CCWavesTiles3D::jsObject, NULL);
	S_CCWavesTiles3D *cobj = new S_CCWavesTiles3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCWavesTiles3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCWavesTiles3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCWavesTiles3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWavesTiles3D *cobj; JSGET_PTRSHELL(S_CCWavesTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCWavesTiles3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWavesTiles3D *cobj; JSGET_PTRSHELL(S_CCWavesTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCWavesTiles3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"waves", kWaves, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWavesTiles3D::jsPropertyGet, S_CCWavesTiles3D::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWavesTiles3D::jsPropertyGet, S_CCWavesTiles3D::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWavesTiles3D::jsPropertyGet, S_CCWavesTiles3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithWaves", S_CCWavesTiles3D::jsinitWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithWaves", S_CCWavesTiles3D::jsactionWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCWavesTiles3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCWavesTiles3D::jsinitWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWavesTiles3D* self = NULL; JSGET_PTRSHELL(S_CCWavesTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithWaves(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWavesTiles3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWavesTiles3D* self = NULL; JSGET_PTRSHELL(S_CCWavesTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWavesTiles3D::jsactionWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCWavesTiles3D* ret = CCWavesTiles3D::actionWithWaves(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCWavesTiles3D::jsClass, S_CCWavesTiles3D::jsObject, NULL);
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

JSClass* S_CCParallaxNode::jsClass = NULL;
JSObject* S_CCParallaxNode::jsObject = NULL;

JSBool S_CCParallaxNode::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCParallaxNode::jsClass, S_CCParallaxNode::jsObject, NULL);
	S_CCParallaxNode *cobj = new S_CCParallaxNode(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCParallaxNode::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCParallaxNode *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCParallaxNode::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParallaxNode *cobj; JSGET_PTRSHELL(S_CCParallaxNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCParallaxNode::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParallaxNode *cobj; JSGET_PTRSHELL(S_CCParallaxNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCParallaxNode::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"parallaxArray", kParallaxArray, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParallaxNode::jsPropertyGet, S_CCParallaxNode::jsPropertySet},
			{"lastPosition", kLastPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParallaxNode::jsPropertyGet, S_CCParallaxNode::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("removeChild", S_CCParallaxNode::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCParallaxNode::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("visit", S_CCParallaxNode::jsvisit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCParallaxNode::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCParallaxNode::jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParallaxNode* self = NULL; JSGET_PTRSHELL(S_CCParallaxNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->removeChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParallaxNode::jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParallaxNode* self = NULL; JSGET_PTRSHELL(S_CCParallaxNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->removeAllChildrenWithCleanup(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParallaxNode::jsvisit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParallaxNode* self = NULL; JSGET_PTRSHELL(S_CCParallaxNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->visit();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCParallaxNode::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCTransitionSplitRows::jsClass = NULL;
JSObject* S_CCTransitionSplitRows::jsObject = NULL;

JSBool S_CCTransitionSplitRows::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSplitRows::jsClass, S_CCTransitionSplitRows::jsObject, NULL);
	S_CCTransitionSplitRows *cobj = new S_CCTransitionSplitRows(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSplitRows::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSplitRows *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSplitRows::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSplitRows *cobj; JSGET_PTRSHELL(S_CCTransitionSplitRows, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSplitRows::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSplitRows *cobj; JSGET_PTRSHELL(S_CCTransitionSplitRows, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSplitRows::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("action", S_CCTransitionSplitRows::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSplitRows::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSplitCols::jsObject,jsClass,S_CCTransitionSplitRows::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSplitRows::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSplitRows* self = NULL; JSGET_PTRSHELL(S_CCTransitionSplitRows, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSplitRows::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSplitRows* ret = CCTransitionSplitRows::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSplitRows::jsClass, S_CCTransitionSplitRows::jsObject, NULL);
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

JSClass* S_CCTintBy::jsClass = NULL;
JSObject* S_CCTintBy::jsObject = NULL;

JSBool S_CCTintBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTintBy::jsClass, S_CCTintBy::jsObject, NULL);
	S_CCTintBy *cobj = new S_CCTintBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTintBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTintBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTintBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTintBy *cobj; JSGET_PTRSHELL(S_CCTintBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTintBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTintBy *cobj; JSGET_PTRSHELL(S_CCTintBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTintBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"deltaR", kDeltaR, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{"deltaG", kDeltaG, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{"deltaB", kDeltaB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{"fromR", kFromR, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{"fromG", kFromG, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{"fromB", kFromB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintBy::jsPropertyGet, S_CCTintBy::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCTintBy::jsinitWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCTintBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCTintBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCTintBy::jsactionWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCTintBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTintBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintBy* self = NULL; JSGET_PTRSHELL(S_CCTintBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		double arg0;
		short arg1;
		short arg2;
		short arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "diii", &arg0, &arg1, &arg2, &arg3);
		bool ret = self->initWithDuration(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintBy* self = NULL; JSGET_PTRSHELL(S_CCTintBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintBy::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintBy* self = NULL; JSGET_PTRSHELL(S_CCTintBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintBy* self = NULL; JSGET_PTRSHELL(S_CCTintBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTintBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		double arg0;
		short arg1;
		short arg2;
		short arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "diii", &arg0, &arg1, &arg2, &arg3);
		CCTintBy* ret = CCTintBy::actionWithDuration(arg0, arg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTintBy::jsClass, S_CCTintBy::jsObject, NULL);
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

JSClass* S_CCMotionStreak::jsClass = NULL;
JSObject* S_CCMotionStreak::jsObject = NULL;

JSBool S_CCMotionStreak::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMotionStreak::jsClass, S_CCMotionStreak::jsObject, NULL);
	S_CCMotionStreak *cobj = new S_CCMotionStreak(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMotionStreak::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMotionStreak *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMotionStreak::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMotionStreak *cobj; JSGET_PTRSHELL(S_CCMotionStreak, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTexture:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTexture();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMotionStreak::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMotionStreak *cobj; JSGET_PTRSHELL(S_CCMotionStreak, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTexture:
		do {
			CCTexture2D* tmp; JSGET_PTRSHELL(CCTexture2D, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTexture(tmp); }
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMotionStreak::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"ribbon", kRibbon, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{"segThreshold", kSegThreshold, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{"width", kWidth, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{"lastLocation", kLastLocation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMotionStreak::jsPropertyGet, S_CCMotionStreak::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFade", S_CCMotionStreak::jsinitWithFade, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("streakWithFade", S_CCMotionStreak::jsstreakWithFade, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCMotionStreak::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMotionStreak::jsstreakWithFade(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 6) {
		double arg0;
		double arg1;
        double arg2;
        JSObject *arg3;
		JSString *arg4;
        /*
		double arg3;
		double arg4;
		JSObject *arg5; */
		JS_ConvertArguments(cx, 6, JS_ARGV(cx, vp), "dddoS", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg2 = JS_EncodeString(cx, arg4);
		ccColor3B* narg3; JSGET_PTRSHELL(ccColor3B, narg3, arg3);
		CCMotionStreak* ret = CCMotionStreak::streakWithFade(arg0, arg1, arg2, *narg3, narg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMotionStreak::jsClass, S_CCMotionStreak::jsObject, NULL);
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
JSBool S_CCMotionStreak::jsinitWithFade(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMotionStreak* self = NULL; JSGET_PTRSHELL(S_CCMotionStreak, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 6) {
		double arg0;
		double arg1;
        double arg2;
        JSObject *arg3;
		JSString *arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "dddoS", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg4 = JS_EncodeString(cx, arg4);
		ccColor3B* narg3; JSGET_PTRSHELL(ccColor3B, narg3, arg3);
		bool ret = self->initWithFade(arg0, arg1, arg2, *narg3, narg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMotionStreak::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMotionStreak* self = NULL; JSGET_PTRSHELL(S_CCMotionStreak, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCMotionStreak::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCTransitionProgressRadialCCW::jsClass = NULL;
JSObject* S_CCTransitionProgressRadialCCW::jsObject = NULL;

JSBool S_CCTransitionProgressRadialCCW::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionProgressRadialCCW::jsClass, S_CCTransitionProgressRadialCCW::jsObject, NULL);
	S_CCTransitionProgressRadialCCW *cobj = new S_CCTransitionProgressRadialCCW(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionProgressRadialCCW::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionProgressRadialCCW *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionProgressRadialCCW::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionProgressRadialCCW *cobj; JSGET_PTRSHELL(S_CCTransitionProgressRadialCCW, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionProgressRadialCCW::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionProgressRadialCCW *cobj; JSGET_PTRSHELL(S_CCTransitionProgressRadialCCW, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionProgressRadialCCW::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionProgressRadialCCW::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionProgressRadialCCW::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionProgressRadialCCW::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionProgressRadialCCW::onEnter();
}
void S_CCTransitionProgressRadialCCW::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionProgressRadialCCW::onExit();
}
JSBool S_CCTransitionProgressRadialCCW::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionProgressRadialCCW* ret = CCTransitionProgressRadialCCW::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionProgressRadialCCW::jsClass, S_CCTransitionProgressRadialCCW::jsObject, NULL);
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

JSClass* S_CCLayerColor::jsClass = NULL;
JSObject* S_CCLayerColor::jsObject = NULL;

JSBool S_CCLayerColor::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLayerColor::jsClass, S_CCLayerColor::jsObject, NULL);
	S_CCLayerColor *cobj = new S_CCLayerColor(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLayerColor::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLayerColor *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLayerColor::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayerColor *cobj; JSGET_PTRSHELL(S_CCLayerColor, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
				// don't know what this is (c ~> js)
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLayerColor::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayerColor *cobj; JSGET_PTRSHELL(S_CCLayerColor, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setColor(color);
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	case kOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLayerColor::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"squareVertices", kSquareVertices, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"squareColors", kSquareColors, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"cOpacity", kCOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerColor::jsPropertyGet, S_CCLayerColor::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCLayerColor::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithColor", S_CCLayerColor::jsinitWithColor, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("changeWidth", S_CCLayerColor::jschangeWidth, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("changeHeight", S_CCLayerColor::jschangeHeight, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("changeWidthAndHeight", S_CCLayerColor::jschangeWidthAndHeight, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("layerWithColor", S_CCLayerColor::jslayerWithColor, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCLayer::jsObject,jsClass,S_CCLayerColor::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLayerColor::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerColor* self = NULL; JSGET_PTRSHELL(S_CCLayerColor, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayerColor::jslayerWithColor(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		CCLayerColor* ret = CCLayerColor::layerWithColor(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLayerColor::jsClass, S_CCLayerColor::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)ret;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
		} while (0);
		
		return JS_TRUE;
	}
    else if (argc == 3) {
        JSObject *arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "odd", &arg0, &arg1, &arg2);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		CCLayerColor* ret = CCLayerColor::layerWithColor(*narg0, arg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLayerColor::jsClass, S_CCLayerColor::jsObject, NULL);
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
JSBool S_CCLayerColor::jsinitWithColor(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerColor* self = NULL; JSGET_PTRSHELL(S_CCLayerColor, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		bool ret = self->initWithColor(*narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
    else if (argc == 3) {
        JSObject *arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "odd", &arg0, &arg1, &arg2);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		bool ret = self->initWithColor(*narg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
    }
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayerColor::jschangeWidth(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerColor* self = NULL; JSGET_PTRSHELL(S_CCLayerColor, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->changeWidth(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayerColor::jschangeHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerColor* self = NULL; JSGET_PTRSHELL(S_CCLayerColor, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->changeHeight(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLayerColor::jschangeWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerColor* self = NULL; JSGET_PTRSHELL(S_CCLayerColor, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		self->changeWidthAndHeight(arg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTexture2D::jsClass = NULL;
JSObject* S_CCTexture2D::jsObject = NULL;

JSBool S_CCTexture2D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
	S_CCTexture2D *cobj = new S_CCTexture2D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTexture2D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTexture2D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTexture2D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTexture2D *cobj; JSGET_PTRSHELL(S_CCTexture2D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPixelsWide:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPixelsWide(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kPixelsHigh:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPixelsHigh(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kName:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getName(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kContentSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getContentSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kMaxS:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getMaxS(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kMaxT:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getMaxT(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kHasPremultipliedAlpha:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->hasPremultipliedAlpha()));
		break;
	case kPixelFormat:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTexture2D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTexture2D *cobj; JSGET_PTRSHELL(S_CCTexture2D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kMaxS:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setMaxS(tmp); } while (0);
		break;
	case kMaxT:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setMaxT(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTexture2D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"ePixelFormat", kEPixelFormat, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"pixelsWide", kPixelsWide, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"pixelsHigh", kPixelsHigh, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"name", kName, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"contentSize", kContentSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"maxS", kMaxS, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"maxT", kMaxT, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"hasPremultipliedAlpha", kHasPremultipliedAlpha, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"pVRHaveAlphaPremultiplied", kPVRHaveAlphaPremultiplied, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{"pixelFormat", kPixelFormat, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTexture2D::jsPropertyGet, S_CCTexture2D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("drawAtPoint", S_CCTexture2D::jsdrawAtPoint, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("drawInRect", S_CCTexture2D::jsdrawInRect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithImage", S_CCTexture2D::jsinitWithImage, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithPVRFile", S_CCTexture2D::jsinitWithPVRFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setAntiAliasTexParameters", S_CCTexture2D::jssetAntiAliasTexParameters, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setAliasTexParameters", S_CCTexture2D::jssetAliasTexParameters, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("generateMipmap", S_CCTexture2D::jsgenerateMipmap, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("bitsPerPixelForFormat", S_CCTexture2D::jsbitsPerPixelForFormat, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("defaultAlphaPixelFormat", S_CCTexture2D::jsdefaultAlphaPixelFormat, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("PVRImagesHavePremultipliedAlpha", S_CCTexture2D::jsPVRImagesHavePremultipliedAlpha, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCTexture2D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTexture2D::jsdrawAtPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		self->drawAtPoint(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsdrawInRect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		self->drawInRect(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsinitWithImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCImage* narg0; JSGET_PTRSHELL(CCImage, narg0, arg0);
		bool ret = self->initWithImage(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsinitWithPVRFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithPVRFile(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jssetAntiAliasTexParameters(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->setAntiAliasTexParameters();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jssetAliasTexParameters(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->setAliasTexParameters();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsgenerateMipmap(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->generateMipmap();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsbitsPerPixelForFormat(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTexture2D* self = NULL; JSGET_PTRSHELL(S_CCTexture2D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		unsigned int ret = self->bitsPerPixelForFormat();
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsdefaultAlphaPixelFormat(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		//INVALID RETURN TYPE _1FEE
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTexture2D::jsPVRImagesHavePremultipliedAlpha(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		CCTexture2D::PVRImagesHavePremultipliedAlpha(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCSpriteFrame::jsClass = NULL;
JSObject* S_CCSpriteFrame::jsObject = NULL;

JSBool S_CCSpriteFrame::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSpriteFrame::jsClass, S_CCSpriteFrame::jsObject, NULL);
	S_CCSpriteFrame *cobj = new S_CCSpriteFrame(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSpriteFrame::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSpriteFrame *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSpriteFrame::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteFrame *cobj; JSGET_PTRSHELL(S_CCSpriteFrame, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRectInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCRect* ctmp = new CCRect(cobj->getRectInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kRect:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCRect* ctmp = new CCRect(cobj->getRect());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kOffsetInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getOffsetInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kOriginalSizeInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getOriginalSizeInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kTexture:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTexture();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSpriteFrame::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteFrame *cobj; JSGET_PTRSHELL(S_CCSpriteFrame, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRectInPixels:
		do {
			CCRect* tmp; JSGET_PTRSHELL(CCRect, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setRectInPixels(*tmp); }
		} while (0);
		break;
	case kRotated:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setRotated(tmp); } while (0);
		break;
	case kRect:
		do {
			CCRect* tmp; JSGET_PTRSHELL(CCRect, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setRect(*tmp); }
		} while (0);
		break;
	case kOffsetInPixels:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setOffsetInPixels(*tmp); }
		} while (0);
		break;
	case kOriginalSizeInPixels:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setOriginalSizeInPixels(*tmp); }
		} while (0);
		break;
	case kTexture:
		do {
			CCTexture2D* tmp; JSGET_PTRSHELL(CCTexture2D, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTexture(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSpriteFrame::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rectInPixels", kRectInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{"rotated", kRotated, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{"rect", kRect, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{"offsetInPixels", kOffsetInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{"originalSizeInPixels", kOriginalSizeInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrame::jsPropertyGet, S_CCSpriteFrame::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("isRotated", S_CCSpriteFrame::jsisRotated, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTexture", S_CCSpriteFrame::jsinitWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("frameWithTexture", S_CCSpriteFrame::jsframeWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSpriteFrame::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSpriteFrame::jsisRotated(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrame* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrame, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isRotated();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrame::jsframeWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		CCSpriteFrame* ret = CCSpriteFrame::frameWithTexture(narg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteFrame::jsClass, S_CCSpriteFrame::jsObject, NULL);
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
JSBool S_CCSpriteFrame::jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrame* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrame, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		bool ret = self->initWithTexture(narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCAnimation::jsClass = NULL;
JSObject* S_CCAnimation::jsObject = NULL;

JSBool S_CCAnimation::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAnimation::jsClass, S_CCAnimation::jsObject, NULL);
	S_CCAnimation *cobj = new S_CCAnimation(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAnimation::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAnimation *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAnimation::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimation *cobj; JSGET_PTRSHELL(S_CCAnimation, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDelayPerUnit:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getDelayPerUnit(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAnimation::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimation *cobj; JSGET_PTRSHELL(S_CCAnimation, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDelayPerUnit:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setDelayPerUnit(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAnimation::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"nameStr", kNameStr, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimation::jsPropertyGet, S_CCAnimation::jsPropertySet},
			{"delayPerUnit", kDelayPerUnit, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimation::jsPropertyGet, S_CCAnimation::jsPropertySet},
			{"frames", kFrames, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimation::jsPropertyGet, S_CCAnimation::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithSpriteFrames", S_CCAnimation::jsinitWithSpriteFrames, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addSpriteFrame", S_CCAnimation::jsaddSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addSpriteFrameWithFileName", S_CCAnimation::jsaddSpriteFrameWithFileName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addSpriteFrameWithTexture", S_CCAnimation::jsaddSpriteFrameWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("init", S_CCAnimation::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("animation", S_CCAnimation::jsanimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("animationWithSpriteFrames", S_CCAnimation::jsanimationWithSpriteFrames, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCAnimation::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAnimation::jsinitWithSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCArray* narg0; JSGET_PTRSHELL(CCArray, narg0, arg0);
		bool ret = self->initWithSpriteFrames(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		self->addSpriteFrame(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddSpriteFrameWithFileName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->addSpriteFrameWithFileName(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddSpriteFrameWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		self->addSpriteFrameWithTexture(narg0, *narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsanimation(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCAnimation* ret = CCAnimation::animation();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimation::jsClass, S_CCAnimation::jsObject, NULL);
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
JSBool S_CCAnimation::jsanimationWithSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCArray* narg0; JSGET_PTRSHELL(CCArray, narg0, arg0);
		CCAnimation* ret = CCAnimation::animationWithSpriteFrames(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAnimation::jsClass, S_CCAnimation::jsObject, NULL);
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

JSClass* S_CCTransitionFadeBL::jsClass = NULL;
JSObject* S_CCTransitionFadeBL::jsObject = NULL;

JSBool S_CCTransitionFadeBL::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFadeBL::jsClass, S_CCTransitionFadeBL::jsObject, NULL);
	S_CCTransitionFadeBL *cobj = new S_CCTransitionFadeBL(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFadeBL::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFadeBL *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFadeBL::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeBL *cobj; JSGET_PTRSHELL(S_CCTransitionFadeBL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFadeBL::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeBL *cobj; JSGET_PTRSHELL(S_CCTransitionFadeBL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFadeBL::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("actionWithSize", S_CCTransitionFadeBL::jsactionWithSize, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFadeBL::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionFadeTR::jsObject,jsClass,S_CCTransitionFadeBL::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionFadeBL::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFadeBL* self = NULL; JSGET_PTRSHELL(S_CCTransitionFadeBL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCActionInterval* ret = self->actionWithSize(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionFadeBL::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFadeBL* ret = CCTransitionFadeBL::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFadeBL::jsClass, S_CCTransitionFadeBL::jsObject, NULL);
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

JSClass* S_CCFadeOutDownTiles::jsClass = NULL;
JSObject* S_CCFadeOutDownTiles::jsObject = NULL;

JSBool S_CCFadeOutDownTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeOutDownTiles::jsClass, S_CCFadeOutDownTiles::jsObject, NULL);
	S_CCFadeOutDownTiles *cobj = new S_CCFadeOutDownTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeOutDownTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeOutDownTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeOutDownTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutDownTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutDownTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeOutDownTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOutDownTiles *cobj; JSGET_PTRSHELL(S_CCFadeOutDownTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeOutDownTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("testFunc", S_CCFadeOutDownTiles::jstestFunc, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCFadeOutDownTiles::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFadeOutUpTiles::jsObject,jsClass,S_CCFadeOutDownTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeOutDownTiles::jstestFunc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOutDownTiles* self = NULL; JSGET_PTRSHELL(S_CCFadeOutDownTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		float ret = self->testFunc(*narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOutDownTiles::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCFadeOutDownTiles* ret = CCFadeOutDownTiles::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeOutDownTiles::jsClass, S_CCFadeOutDownTiles::jsObject, NULL);
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

JSClass* S_CCTurnOffTiles::jsClass = NULL;
JSObject* S_CCTurnOffTiles::jsObject = NULL;

JSBool S_CCTurnOffTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTurnOffTiles::jsClass, S_CCTurnOffTiles::jsObject, NULL);
	S_CCTurnOffTiles *cobj = new S_CCTurnOffTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTurnOffTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTurnOffTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTurnOffTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTurnOffTiles *cobj; JSGET_PTRSHELL(S_CCTurnOffTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTurnOffTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTurnOffTiles *cobj; JSGET_PTRSHELL(S_CCTurnOffTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTurnOffTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"seed", kSeed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTurnOffTiles::jsPropertyGet, S_CCTurnOffTiles::jsPropertySet},
			{"tilesCount", kTilesCount, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTurnOffTiles::jsPropertyGet, S_CCTurnOffTiles::jsPropertySet},
			{"tilesOrder", kTilesOrder, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTurnOffTiles::jsPropertyGet, S_CCTurnOffTiles::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithSeed", S_CCTurnOffTiles::jsinitWithSeed, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("turnOnTile", S_CCTurnOffTiles::jsturnOnTile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("turnOffTile", S_CCTurnOffTiles::jsturnOffTile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCTurnOffTiles::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCTurnOffTiles::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("actionWithSeed", S_CCTurnOffTiles::jsactionWithSeed, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCTurnOffTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTurnOffTiles::jsinitWithSeed(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		int arg0;
		JSObject *arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "iod", &arg0, &arg1, &arg2);
		ccGridSize* narg1; JSGET_PTRSHELL(ccGridSize, narg1, arg1);
		bool ret = self->initWithSeed(arg0, *narg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTurnOffTiles::jsturnOnTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->turnOnTile(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTurnOffTiles::jsturnOffTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		self->turnOffTile(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTurnOffTiles::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTurnOffTiles::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTurnOffTiles::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCTurnOffTiles* ret = CCTurnOffTiles::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTurnOffTiles::jsClass, S_CCTurnOffTiles::jsObject, NULL);
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
JSBool S_CCTurnOffTiles::jsactionWithSeed(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		int arg0;
		JSObject *arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "iod", &arg0, &arg1, &arg2);
		ccGridSize* narg1; JSGET_PTRSHELL(ccGridSize, narg1, arg1);
		CCTurnOffTiles* ret = CCTurnOffTiles::actionWithSeed(arg0, *narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTurnOffTiles::jsClass, S_CCTurnOffTiles::jsObject, NULL);
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

JSClass* S_CCTransitionFadeUp::jsClass = NULL;
JSObject* S_CCTransitionFadeUp::jsObject = NULL;

JSBool S_CCTransitionFadeUp::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFadeUp::jsClass, S_CCTransitionFadeUp::jsObject, NULL);
	S_CCTransitionFadeUp *cobj = new S_CCTransitionFadeUp(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFadeUp::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFadeUp *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFadeUp::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeUp *cobj; JSGET_PTRSHELL(S_CCTransitionFadeUp, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFadeUp::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeUp *cobj; JSGET_PTRSHELL(S_CCTransitionFadeUp, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFadeUp::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("actionWithSize", S_CCTransitionFadeUp::jsactionWithSize, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFadeUp::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionFadeTR::jsObject,jsClass,S_CCTransitionFadeUp::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionFadeUp::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFadeUp* self = NULL; JSGET_PTRSHELL(S_CCTransitionFadeUp, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCActionInterval* ret = self->actionWithSize(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionFadeUp::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFadeUp* ret = CCTransitionFadeUp::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFadeUp::jsClass, S_CCTransitionFadeUp::jsObject, NULL);
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

JSClass* S_CCMenuItemImage::jsClass = NULL;
JSObject* S_CCMenuItemImage::jsObject = NULL;

JSBool S_CCMenuItemImage::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMenuItemImage::jsClass, S_CCMenuItemImage::jsObject, NULL);
	S_CCMenuItemImage *cobj = new S_CCMenuItemImage(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMenuItemImage::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenuItemImage *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMenuItemImage::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemImage *cobj; JSGET_PTRSHELL(S_CCMenuItemImage, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMenuItemImage::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemImage *cobj; JSGET_PTRSHELL(S_CCMenuItemImage, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMenuItemImage::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithNormalImage", S_CCMenuItemImage::jsinitWithNormalImage, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("itemWithNormalImage", S_CCMenuItemImage::jsitemWithNormalImage, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMenuItemSprite::jsObject,jsClass,S_CCMenuItemImage::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemImage::jsitemWithNormalImage(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCMenuItemImage* ret = CCMenuItemImage::itemWithNormalImage(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMenuItemImage::jsClass, S_CCMenuItemImage::jsObject, NULL);
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
MENU_ITEM_ACTION(S_CCMenuItemImage)

JSClass* S_CCTintTo::jsClass = NULL;
JSObject* S_CCTintTo::jsObject = NULL;

JSBool S_CCTintTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTintTo::jsClass, S_CCTintTo::jsObject, NULL);
	S_CCTintTo *cobj = new S_CCTintTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTintTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTintTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTintTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTintTo *cobj; JSGET_PTRSHELL(S_CCTintTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTintTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTintTo *cobj; JSGET_PTRSHELL(S_CCTintTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTintTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"to", kTo, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintTo::jsPropertyGet, S_CCTintTo::jsPropertySet},
			{"from", kFrom, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTintTo::jsPropertyGet, S_CCTintTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCTintTo::jsinitWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCTintTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCTintTo::jsactionWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCTintTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTintTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintTo* self = NULL; JSGET_PTRSHELL(S_CCTintTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		double arg0;
		unsigned char arg1;
		unsigned char arg2;
		unsigned char arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dccc", &arg0, &arg1, &arg2, &arg3);
		bool ret = self->initWithDuration(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintTo* self = NULL; JSGET_PTRSHELL(S_CCTintTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTintTo* self = NULL; JSGET_PTRSHELL(S_CCTintTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTintTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		double arg0;
		unsigned char arg1;
		unsigned char arg2;
		unsigned char arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dccc", &arg0, &arg1, &arg2, &arg3);
		CCTintTo* ret = CCTintTo::actionWithDuration(arg0, arg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTintTo::jsClass, S_CCTintTo::jsObject, NULL);
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

JSClass* S_CCParticleSystem::jsClass = NULL;
JSObject* S_CCParticleSystem::jsObject = NULL;

JSBool S_CCParticleSystem::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCParticleSystem::jsClass, S_CCParticleSystem::jsObject, NULL);
	S_CCParticleSystem *cobj = new S_CCParticleSystem(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCParticleSystem::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCParticleSystem *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCParticleSystem::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystem *cobj; JSGET_PTRSHELL(S_CCParticleSystem, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kIsActive:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isActive()));
		break;
	case kParticleCount:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getParticleCount(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kDuration:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getDuration(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kSourcePosition:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getSourcePosition());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kPosVar:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPosVar());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kLife:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getLife(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kLifeVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getLifeVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAngle:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAngle(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAngleVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAngleVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartSize:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartSize(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartSizeVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartSizeVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndSize:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndSize(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndSizeVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndSizeVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartColor:
				// don't know what this is (c ~> js)
		break;
	case kStartColorVar:
				// don't know what this is (c ~> js)
		break;
	case kEndColor:
				// don't know what this is (c ~> js)
		break;
	case kEndColorVar:
				// don't know what this is (c ~> js)
		break;
	case kStartSpin:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartSpin(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartSpinVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartSpinVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndSpin:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndSpin(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndSpinVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndSpinVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEmissionRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEmissionRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kTotalParticles:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTotalParticles(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kTexture:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTexture();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	case kIsBlendAdditive:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isBlendAdditive()));
		break;
	case kIsAutoRemoveOnFinish:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isAutoRemoveOnFinish()));
		break;
	case kEmitterMode:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEmitterMode(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kGravity:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getGravity());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kSpeed:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSpeed(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kSpeedVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSpeedVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kTangentialAccel:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTangentialAccel(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kTangentialAccelVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTangentialAccelVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRadialAccel:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRadialAccel(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRadialAccelVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRadialAccelVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartRadius:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartRadius(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kStartRadiusVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartRadiusVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndRadius:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndRadius(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndRadiusVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndRadiusVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRotatePerSecond:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRotatePerSecond(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRotatePerSecondVar:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRotatePerSecondVar(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kPositionType:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCParticleSystem::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystem *cobj; JSGET_PTRSHELL(S_CCParticleSystem, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDuration:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setDuration(tmp); } while (0);
		break;
	case kSourcePosition:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setSourcePosition(*tmp); }
		} while (0);
		break;
	case kPosVar:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPosVar(*tmp); }
		} while (0);
		break;
	case kLife:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setLife(tmp); } while (0);
		break;
	case kLifeVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setLifeVar(tmp); } while (0);
		break;
	case kAngle:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAngle(tmp); } while (0);
		break;
	case kAngleVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAngleVar(tmp); } while (0);
		break;
	case kStartSize:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartSize(tmp); } while (0);
		break;
	case kStartSizeVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartSizeVar(tmp); } while (0);
		break;
	case kEndSize:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndSize(tmp); } while (0);
		break;
	case kEndSizeVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndSizeVar(tmp); } while (0);
		break;
	case kStartColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb, ja;
			double r, g, b, a;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_GetElement(cx, arr, 3, &ja);
			JS_ValueToNumber(cx, jr, &r); JS_ValueToNumber(cx, jg, &g); JS_ValueToNumber(cx, jb, &b); JS_ValueToNumber(cx, ja, &a);
			ccColor4F color = {r, g, b, a};
			cobj->setStartColor(color);
		} while (0);
		break;
	case kStartColorVar:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb, ja;
			double r, g, b, a;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_GetElement(cx, arr, 3, &ja);
			JS_ValueToNumber(cx, jr, &r); JS_ValueToNumber(cx, jg, &g); JS_ValueToNumber(cx, jb, &b); JS_ValueToNumber(cx, ja, &a);
			ccColor4F color = {r, g, b, a};
			cobj->setStartColorVar(color);
		} while (0);
		break;
	case kEndColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb, ja;
			double r, g, b, a;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_GetElement(cx, arr, 3, &ja);
			JS_ValueToNumber(cx, jr, &r); JS_ValueToNumber(cx, jg, &g); JS_ValueToNumber(cx, jb, &b); JS_ValueToNumber(cx, ja, &a);
			ccColor4F color = {r, g, b, a};
			cobj->setEndColor(color);
		} while (0);
		break;
	case kEndColorVar:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb, ja;
			double r, g, b, a;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_GetElement(cx, arr, 3, &ja);
			JS_ValueToNumber(cx, jr, &r); JS_ValueToNumber(cx, jg, &g); JS_ValueToNumber(cx, jb, &b); JS_ValueToNumber(cx, ja, &a);
			ccColor4F color = {r, g, b, a};
			cobj->setEndColorVar(color);
		} while (0);
		break;
	case kStartSpin:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartSpin(tmp); } while (0);
		break;
	case kStartSpinVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartSpinVar(tmp); } while (0);
		break;
	case kEndSpin:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndSpin(tmp); } while (0);
		break;
	case kEndSpinVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndSpinVar(tmp); } while (0);
		break;
	case kEmissionRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEmissionRate(tmp); } while (0);
		break;
	case kTotalParticles:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setTotalParticles(tmp); } while (0);
		break;
	case kTexture:
		do {
			CCTexture2D* tmp; JSGET_PTRSHELL(CCTexture2D, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTexture(tmp); }
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	case kIsBlendAdditive:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setBlendAdditive(tmp); } while (0);
		break;
	case kIsAutoRemoveOnFinish:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setAutoRemoveOnFinish(tmp); } while (0);
		break;
	case kEmitterMode:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setEmitterMode(tmp); } while (0);
		break;
	case kGravity:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setGravity(*tmp); }
		} while (0);
		break;
	case kSpeed:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSpeed(tmp); } while (0);
		break;
	case kSpeedVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSpeedVar(tmp); } while (0);
		break;
	case kTangentialAccel:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setTangentialAccel(tmp); } while (0);
		break;
	case kTangentialAccelVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setTangentialAccelVar(tmp); } while (0);
		break;
	case kRadialAccel:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRadialAccel(tmp); } while (0);
		break;
	case kRadialAccelVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRadialAccelVar(tmp); } while (0);
		break;
	case kStartRadius:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartRadius(tmp); } while (0);
		break;
	case kStartRadiusVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setStartRadiusVar(tmp); } while (0);
		break;
	case kEndRadius:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndRadius(tmp); } while (0);
		break;
	case kEndRadiusVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setEndRadiusVar(tmp); } while (0);
		break;
	case kRotatePerSecond:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRotatePerSecond(tmp); } while (0);
		break;
	case kRotatePerSecondVar:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRotatePerSecondVar(tmp); } while (0);
		break;
	case kPositionType:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCParticleSystem::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"plistFile", kPlistFile, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"elapsed", kElapsed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"particles", kParticles, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"emitCounter", kEmitCounter, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"particleIdx", kParticleIdx, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"isActive", kIsActive, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"particleCount", kParticleCount, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"duration", kDuration, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"sourcePosition", kSourcePosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"posVar", kPosVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"life", kLife, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"lifeVar", kLifeVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"angle", kAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"angleVar", kAngleVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startSize", kStartSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startSizeVar", kStartSizeVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endSize", kEndSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endSizeVar", kEndSizeVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startColor", kStartColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startColorVar", kStartColorVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endColor", kEndColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endColorVar", kEndColorVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startSpin", kStartSpin, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startSpinVar", kStartSpinVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endSpin", kEndSpin, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endSpinVar", kEndSpinVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"emissionRate", kEmissionRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"totalParticles", kTotalParticles, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"isBlendAdditive", kIsBlendAdditive, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"type", kType, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"isAutoRemoveOnFinish", kIsAutoRemoveOnFinish, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"emitterMode", kEmitterMode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"gravity", kGravity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"speed", kSpeed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"speedVar", kSpeedVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"tangentialAccel", kTangentialAccel, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"tangentialAccelVar", kTangentialAccelVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"radialAccel", kRadialAccel, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"radialAccelVar", kRadialAccelVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startRadius", kStartRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"startRadiusVar", kStartRadiusVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endRadius", kEndRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"endRadiusVar", kEndRadiusVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"rotatePerSecond", kRotatePerSecond, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"rotatePerSecondVar", kRotatePerSecondVar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{"positionType", kPositionType, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystem::jsPropertyGet, S_CCParticleSystem::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFile", S_CCParticleSystem::jsinitWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTotalParticles", S_CCParticleSystem::jsinitWithTotalParticles, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addParticle", S_CCParticleSystem::jsaddParticle, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initParticle", S_CCParticleSystem::jsinitParticle, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopSystem", S_CCParticleSystem::jsstopSystem, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFull", S_CCParticleSystem::jsisFull, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateQuadWithParticle", S_CCParticleSystem::jsupdateQuadWithParticle, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("postStep", S_CCParticleSystem::jspostStep, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("particleWithFile", S_CCParticleSystem::jsparticleWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCParticleSystem::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCParticleSystem::jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithFile(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsinitWithTotalParticles(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		bool ret = self->initWithTotalParticles(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsaddParticle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->addParticle();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsinitParticle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		tCCParticle* narg0; JSGET_PTRSHELL(tCCParticle, narg0, arg0);
		self->initParticle(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsstopSystem(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stopSystem();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsisFull(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isFull();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsupdateQuadWithParticle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		tCCParticle* narg0; JSGET_PTRSHELL(tCCParticle, narg0, arg0);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		self->updateQuadWithParticle(narg0, *narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jspostStep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->postStep();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTransitionFade::jsClass = NULL;
JSObject* S_CCTransitionFade::jsObject = NULL;

JSBool S_CCTransitionFade::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFade::jsClass, S_CCTransitionFade::jsObject, NULL);
	S_CCTransitionFade *cobj = new S_CCTransitionFade(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFade::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFade *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFade::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFade *cobj; JSGET_PTRSHELL(S_CCTransitionFade, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFade::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFade *cobj; JSGET_PTRSHELL(S_CCTransitionFade, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFade::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionFade::jsPropertyGet, S_CCTransitionFade::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCTransitionFade::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFade::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionFade::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionFade::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		JSObject *arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doo", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		ccColor3B* narg2; JSGET_PTRSHELL(ccColor3B, narg2, arg2);
		CCTransitionFade* ret = CCTransitionFade::transitionWithDuration(arg0, narg1, *narg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFade::jsClass, S_CCTransitionFade::jsObject, NULL);
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
JSBool S_CCTransitionFade::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFade* self = NULL; JSGET_PTRSHELL(S_CCTransitionFade, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		JSObject *arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doo", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		ccColor3B* narg2; JSGET_PTRSHELL(ccColor3B, narg2, arg2);
		bool ret = self->initWithDuration(arg0, narg1, *narg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCTransitionFade::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFade::onEnter();
}
void S_CCTransitionFade::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFade::onExit();
}

JSClass* S_CCDeccelAmplitude::jsClass = NULL;
JSObject* S_CCDeccelAmplitude::jsObject = NULL;

JSBool S_CCDeccelAmplitude::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCDeccelAmplitude::jsClass, S_CCDeccelAmplitude::jsObject, NULL);
	S_CCDeccelAmplitude *cobj = new S_CCDeccelAmplitude(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCDeccelAmplitude::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCDeccelAmplitude *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCDeccelAmplitude::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDeccelAmplitude *cobj; JSGET_PTRSHELL(S_CCDeccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCDeccelAmplitude::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDeccelAmplitude *cobj; JSGET_PTRSHELL(S_CCDeccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCDeccelAmplitude::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rate", kRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDeccelAmplitude::jsPropertyGet, S_CCDeccelAmplitude::jsPropertySet},
			{"other", kOther, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDeccelAmplitude::jsPropertyGet, S_CCDeccelAmplitude::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCDeccelAmplitude::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCDeccelAmplitude::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCDeccelAmplitude::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCDeccelAmplitude::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCDeccelAmplitude::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCDeccelAmplitude::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDeccelAmplitude::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDeccelAmplitude::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDeccelAmplitude::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCDeccelAmplitude::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		CCDeccelAmplitude* ret = CCDeccelAmplitude::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCDeccelAmplitude::jsClass, S_CCDeccelAmplitude::jsObject, NULL);
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

JSClass* S_CCEaseElasticIn::jsClass = NULL;
JSObject* S_CCEaseElasticIn::jsObject = NULL;

JSBool S_CCEaseElasticIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseElasticIn::jsClass, S_CCEaseElasticIn::jsObject, NULL);
	S_CCEaseElasticIn *cobj = new S_CCEaseElasticIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseElasticIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseElasticIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseElasticIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticIn *cobj; JSGET_PTRSHELL(S_CCEaseElasticIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseElasticIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticIn *cobj; JSGET_PTRSHELL(S_CCEaseElasticIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseElasticIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseElasticIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseElasticIn::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseElastic::jsObject,jsClass,S_CCEaseElasticIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseElasticIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticIn* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseElasticIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticIn* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseElasticIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseElasticIn* ret = CCEaseElasticIn::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseElasticIn::jsClass, S_CCEaseElasticIn::jsObject, NULL);
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

JSClass* S_CCProgressTimer::jsClass = NULL;
JSObject* S_CCProgressTimer::jsObject = NULL;

JSBool S_CCProgressTimer::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCProgressTimer::jsClass, S_CCProgressTimer::jsObject, NULL);
	S_CCProgressTimer *cobj = new S_CCProgressTimer(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCProgressTimer::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCProgressTimer *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCProgressTimer::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressTimer *cobj; JSGET_PTRSHELL(S_CCProgressTimer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPercentage:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPercentage(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kSprite:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getSprite();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kType:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCProgressTimer::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCProgressTimer *cobj; JSGET_PTRSHELL(S_CCProgressTimer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPercentage:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setPercentage(tmp); } while (0);
		break;
	case kSprite:
		do {
			CCSprite* tmp; JSGET_PTRSHELL(CCSprite, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setSprite(tmp); }
		} while (0);
		break;
	case kType:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCProgressTimer::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"eType", kEType, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{"percentage", kPercentage, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{"sprite", kSprite, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{"vertexDataCount", kVertexDataCount, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{"vertexData", kVertexData, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{"type", kType, JSPROP_PERMANENT | JSPROP_SHARED, S_CCProgressTimer::jsPropertyGet, S_CCProgressTimer::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithSprite", S_CCProgressTimer::jsinitWithSprite, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCProgressTimer::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("progressWithSprite", S_CCProgressTimer::jsprogressWithSprite, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCProgressTimer::jsConstructor,0,properties,funcs,NULL,st_funcs);
}
JSBool S_CCProgressTimer::jsinitWithSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressTimer* self = NULL; JSGET_PTRSHELL(S_CCProgressTimer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		bool ret = self->initWithSprite(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressTimer::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCProgressTimer* self = NULL; JSGET_PTRSHELL(S_CCProgressTimer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCProgressTimer::jsprogressWithSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		CCProgressTimer* ret = CCProgressTimer::progressWithSprite(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCProgressTimer::jsClass, S_CCProgressTimer::jsObject, NULL);
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
void S_CCProgressTimer::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCRotateBy::jsClass = NULL;
JSObject* S_CCRotateBy::jsObject = NULL;

JSBool S_CCRotateBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRotateBy::jsClass, S_CCRotateBy::jsObject, NULL);
	S_CCRotateBy *cobj = new S_CCRotateBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRotateBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRotateBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRotateBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRotateBy *cobj; JSGET_PTRSHELL(S_CCRotateBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRotateBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRotateBy *cobj; JSGET_PTRSHELL(S_CCRotateBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRotateBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"angle", kAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRotateBy::jsPropertyGet, S_CCRotateBy::jsPropertySet},
			{"startAngle", kStartAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRotateBy::jsPropertyGet, S_CCRotateBy::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCRotateBy::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCRotateBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCRotateBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCRotateBy::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCRotateBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRotateBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateBy* self = NULL; JSGET_PTRSHELL(S_CCRotateBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateBy* self = NULL; JSGET_PTRSHELL(S_CCRotateBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateBy::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateBy* self = NULL; JSGET_PTRSHELL(S_CCRotateBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateBy* self = NULL; JSGET_PTRSHELL(S_CCRotateBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCRotateBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		CCRotateBy* ret = CCRotateBy::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRotateBy::jsClass, S_CCRotateBy::jsObject, NULL);
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

JSClass* S_CCPoint::jsClass = NULL;
JSObject* S_CCPoint::jsObject = NULL;

JSBool S_CCPoint::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
	S_CCPoint *cobj = new S_CCPoint(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCPoint::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCPoint *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCPoint::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPoint *cobj; JSGET_PTRSHELL(S_CCPoint, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kX:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->x, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kY:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->y, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCPoint::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPoint *cobj; JSGET_PTRSHELL(S_CCPoint, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kX:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->x = tmp; } while (0);
		break;
	case kY:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->y = tmp; } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCPoint::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"x", kX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet},
			{"y", kY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCPoint::jsPropertyGet, S_CCPoint::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCPointEqualToPoint", S_CCPoint::jsCCPointEqualToPoint, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCPoint::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCPoint::jsCCPointEqualToPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		bool ret = CCPoint::CCPointEqualToPoint(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTransitionTurnOffTiles::jsClass = NULL;
JSObject* S_CCTransitionTurnOffTiles::jsObject = NULL;

JSBool S_CCTransitionTurnOffTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionTurnOffTiles::jsClass, S_CCTransitionTurnOffTiles::jsObject, NULL);
	S_CCTransitionTurnOffTiles *cobj = new S_CCTransitionTurnOffTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionTurnOffTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionTurnOffTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionTurnOffTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionTurnOffTiles *cobj; JSGET_PTRSHELL(S_CCTransitionTurnOffTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionTurnOffTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionTurnOffTiles *cobj; JSGET_PTRSHELL(S_CCTransitionTurnOffTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionTurnOffTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("easeActionWithAction", S_CCTransitionTurnOffTiles::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionTurnOffTiles::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionTurnOffTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionTurnOffTiles::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionTurnOffTiles::onEnter();
}
JSBool S_CCTransitionTurnOffTiles::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionTurnOffTiles* self = NULL; JSGET_PTRSHELL(S_CCTransitionTurnOffTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionTurnOffTiles::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionTurnOffTiles* ret = CCTransitionTurnOffTiles::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionTurnOffTiles::jsClass, S_CCTransitionTurnOffTiles::jsObject, NULL);
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

JSClass* S_CCActionInstant::jsClass = NULL;
JSObject* S_CCActionInstant::jsObject = NULL;

JSBool S_CCActionInstant::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCActionInstant::jsClass, S_CCActionInstant::jsObject, NULL);
	S_CCActionInstant *cobj = new S_CCActionInstant(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCActionInstant::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCActionInstant *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCActionInstant::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionInstant *cobj; JSGET_PTRSHELL(S_CCActionInstant, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCActionInstant::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionInstant *cobj; JSGET_PTRSHELL(S_CCActionInstant, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCActionInstant::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("isDone", S_CCActionInstant::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("step", S_CCActionInstant::jsstep, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCActionInstant::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFiniteTimeAction::jsObject,jsClass,S_CCActionInstant::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCActionInstant::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInstant* self = NULL; JSGET_PTRSHELL(S_CCActionInstant, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInstant::jsstep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInstant* self = NULL; JSGET_PTRSHELL(S_CCActionInstant, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->step(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInstant::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInstant* self = NULL; JSGET_PTRSHELL(S_CCActionInstant, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInstant::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInstant* self = NULL; JSGET_PTRSHELL(S_CCActionInstant, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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

JSClass* S_CCTransitionZoomFlipAngular::jsClass = NULL;
JSObject* S_CCTransitionZoomFlipAngular::jsObject = NULL;

JSBool S_CCTransitionZoomFlipAngular::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionZoomFlipAngular::jsClass, S_CCTransitionZoomFlipAngular::jsObject, NULL);
	S_CCTransitionZoomFlipAngular *cobj = new S_CCTransitionZoomFlipAngular(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionZoomFlipAngular::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionZoomFlipAngular *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionZoomFlipAngular::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipAngular *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipAngular, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionZoomFlipAngular::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipAngular *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipAngular, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionZoomFlipAngular::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionZoomFlipAngular::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionZoomFlipAngular::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionZoomFlipAngular::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionZoomFlipAngular::onEnter();
}
JSBool S_CCTransitionZoomFlipAngular::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionZoomFlipAngular* ret = CCTransitionZoomFlipAngular::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionZoomFlipAngular::jsClass, S_CCTransitionZoomFlipAngular::jsObject, NULL);
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

JSClass* S_CCReuseGrid::jsClass = NULL;
JSObject* S_CCReuseGrid::jsObject = NULL;

JSBool S_CCReuseGrid::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCReuseGrid::jsClass, S_CCReuseGrid::jsObject, NULL);
	S_CCReuseGrid *cobj = new S_CCReuseGrid(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCReuseGrid::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCReuseGrid *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCReuseGrid::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCReuseGrid *cobj; JSGET_PTRSHELL(S_CCReuseGrid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCReuseGrid::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCReuseGrid *cobj; JSGET_PTRSHELL(S_CCReuseGrid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCReuseGrid::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"times", kTimes, JSPROP_PERMANENT | JSPROP_SHARED, S_CCReuseGrid::jsPropertyGet, S_CCReuseGrid::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTimes", S_CCReuseGrid::jsinitWithTimes, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCReuseGrid::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithTimes", S_CCReuseGrid::jsactionWithTimes, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCReuseGrid::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCReuseGrid::jsinitWithTimes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReuseGrid* self = NULL; JSGET_PTRSHELL(S_CCReuseGrid, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		bool ret = self->initWithTimes(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReuseGrid::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCReuseGrid* self = NULL; JSGET_PTRSHELL(S_CCReuseGrid, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCReuseGrid::jsactionWithTimes(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		CCReuseGrid* ret = CCReuseGrid::actionWithTimes(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCReuseGrid::jsClass, S_CCReuseGrid::jsObject, NULL);
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

JSClass* S_CCEaseElastic::jsClass = NULL;
JSObject* S_CCEaseElastic::jsObject = NULL;

JSBool S_CCEaseElastic::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseElastic::jsClass, S_CCEaseElastic::jsObject, NULL);
	S_CCEaseElastic *cobj = new S_CCEaseElastic(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseElastic::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseElastic *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseElastic::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElastic *cobj; JSGET_PTRSHELL(S_CCEaseElastic, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPeriod:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPeriod(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseElastic::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElastic *cobj; JSGET_PTRSHELL(S_CCEaseElastic, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPeriod:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setPeriod(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseElastic::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"period", kPeriod, JSPROP_PERMANENT | JSPROP_SHARED, S_CCEaseElastic::jsPropertyGet, S_CCEaseElastic::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCEaseElastic::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCEaseElastic::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseElastic::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseElastic::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseElastic::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElastic* self = NULL; JSGET_PTRSHELL(S_CCEaseElastic, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseElastic::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElastic* self = NULL; JSGET_PTRSHELL(S_CCEaseElastic, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseElastic::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseElastic* ret = CCEaseElastic::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseElastic::jsClass, S_CCEaseElastic::jsObject, NULL);
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

JSClass* S_CCTransitionFadeDown::jsClass = NULL;
JSObject* S_CCTransitionFadeDown::jsObject = NULL;

JSBool S_CCTransitionFadeDown::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFadeDown::jsClass, S_CCTransitionFadeDown::jsObject, NULL);
	S_CCTransitionFadeDown *cobj = new S_CCTransitionFadeDown(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFadeDown::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFadeDown *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFadeDown::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeDown *cobj; JSGET_PTRSHELL(S_CCTransitionFadeDown, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFadeDown::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeDown *cobj; JSGET_PTRSHELL(S_CCTransitionFadeDown, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFadeDown::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("actionWithSize", S_CCTransitionFadeDown::jsactionWithSize, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFadeDown::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionFadeTR::jsObject,jsClass,S_CCTransitionFadeDown::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionFadeDown::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFadeDown* self = NULL; JSGET_PTRSHELL(S_CCTransitionFadeDown, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCActionInterval* ret = self->actionWithSize(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionFadeDown::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFadeDown* ret = CCTransitionFadeDown::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFadeDown::jsClass, S_CCTransitionFadeDown::jsObject, NULL);
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

JSClass* S_CCTransitionFlipY::jsClass = NULL;
JSObject* S_CCTransitionFlipY::jsObject = NULL;

JSBool S_CCTransitionFlipY::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFlipY::jsClass, S_CCTransitionFlipY::jsObject, NULL);
	S_CCTransitionFlipY *cobj = new S_CCTransitionFlipY(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFlipY::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFlipY *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFlipY::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipY *cobj; JSGET_PTRSHELL(S_CCTransitionFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFlipY::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipY *cobj; JSGET_PTRSHELL(S_CCTransitionFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFlipY::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFlipY::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionFlipY::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionFlipY::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFlipY::onEnter();
}
JSBool S_CCTransitionFlipY::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFlipY* ret = CCTransitionFlipY::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFlipY::jsClass, S_CCTransitionFlipY::jsObject, NULL);
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

JSClass* S_CCStopGrid::jsClass = NULL;
JSObject* S_CCStopGrid::jsObject = NULL;

JSBool S_CCStopGrid::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCStopGrid::jsClass, S_CCStopGrid::jsObject, NULL);
	S_CCStopGrid *cobj = new S_CCStopGrid(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCStopGrid::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCStopGrid *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCStopGrid::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCStopGrid *cobj; JSGET_PTRSHELL(S_CCStopGrid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCStopGrid::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCStopGrid *cobj; JSGET_PTRSHELL(S_CCStopGrid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCStopGrid::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCStopGrid::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("action", S_CCStopGrid::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCStopGrid::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCStopGrid::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCStopGrid* self = NULL; JSGET_PTRSHELL(S_CCStopGrid, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCStopGrid::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCStopGrid* ret = CCStopGrid::action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCStopGrid::jsClass, S_CCStopGrid::jsObject, NULL);
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

JSClass* S_CCSize::jsClass = NULL;
JSObject* S_CCSize::jsObject = NULL;

JSBool S_CCSize::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
	S_CCSize *cobj = new S_CCSize(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSize::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSize *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCSize::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSize *cobj; JSGET_PTRSHELL(S_CCSize, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kWidth:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->width, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kHeight:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->height, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSize::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSize *cobj; JSGET_PTRSHELL(S_CCSize, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kWidth:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->width = tmp; } while (0);
		break;
	case kHeight:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->height = tmp; } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSize::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"width", kWidth, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet},
			{"height", kHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSize::jsPropertyGet, S_CCSize::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCSizeEqualToSize", S_CCSize::jsCCSizeEqualToSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSize::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSize::jsCCSizeEqualToSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCSize* narg0; JSGET_PTRSHELL(CCSize, narg0, arg0);
		CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
		bool ret = CCSize::CCSizeEqualToSize(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTwirl::jsClass = NULL;
JSObject* S_CCTwirl::jsObject = NULL;

JSBool S_CCTwirl::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTwirl::jsClass, S_CCTwirl::jsObject, NULL);
	S_CCTwirl *cobj = new S_CCTwirl(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTwirl::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTwirl *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTwirl::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTwirl *cobj; JSGET_PTRSHELL(S_CCTwirl, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPosition());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTwirl::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTwirl *cobj; JSGET_PTRSHELL(S_CCTwirl, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPosition(*tmp); }
		} while (0);
		break;
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTwirl::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTwirl::jsPropertyGet, S_CCTwirl::jsPropertySet},
			{"twirls", kTwirls, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTwirl::jsPropertyGet, S_CCTwirl::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTwirl::jsPropertyGet, S_CCTwirl::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTwirl::jsPropertyGet, S_CCTwirl::jsPropertySet},
			{"inPixels", kInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTwirl::jsPropertyGet, S_CCTwirl::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithPosition", S_CCTwirl::jsinitWithPosition, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithPosition", S_CCTwirl::jsactionWithPosition, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCTwirl::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTwirl::jsinitWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTwirl* self = NULL; JSGET_PTRSHELL(S_CCTwirl, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSObject *arg0;
		int arg1;
		double arg2;
		JSObject *arg3;
		double arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "oidod", &arg0, &arg1, &arg2, &arg3, &arg4);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg3; JSGET_PTRSHELL(ccGridSize, narg3, arg3);
		bool ret = self->initWithPosition(*narg0, arg1, arg2, *narg3, arg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTwirl::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTwirl* self = NULL; JSGET_PTRSHELL(S_CCTwirl, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTwirl::jsactionWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 5) {
		JSObject *arg0;
		int arg1;
		double arg2;
		JSObject *arg3;
		double arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "oidod", &arg0, &arg1, &arg2, &arg3, &arg4);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg3; JSGET_PTRSHELL(ccGridSize, narg3, arg3);
		CCTwirl* ret = CCTwirl::actionWithPosition(*narg0, arg1, arg2, *narg3, arg4);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTwirl::jsClass, S_CCTwirl::jsObject, NULL);
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

JSClass* S_CCMoveTo::jsClass = NULL;
JSObject* S_CCMoveTo::jsObject = NULL;

JSBool S_CCMoveTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMoveTo::jsClass, S_CCMoveTo::jsObject, NULL);
	S_CCMoveTo *cobj = new S_CCMoveTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMoveTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMoveTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMoveTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMoveTo *cobj; JSGET_PTRSHELL(S_CCMoveTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMoveTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMoveTo *cobj; JSGET_PTRSHELL(S_CCMoveTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMoveTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"endPosition", kEndPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMoveTo::jsPropertyGet, S_CCMoveTo::jsPropertySet},
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMoveTo::jsPropertyGet, S_CCMoveTo::jsPropertySet},
			{"delta", kDelta, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMoveTo::jsPropertyGet, S_CCMoveTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCMoveTo::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCMoveTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCMoveTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCMoveTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMoveTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveTo* self = NULL; JSGET_PTRSHELL(S_CCMoveTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		bool ret = self->initWithDuration(arg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMoveTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveTo* self = NULL; JSGET_PTRSHELL(S_CCMoveTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMoveTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveTo* self = NULL; JSGET_PTRSHELL(S_CCMoveTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMoveTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		CCMoveTo* ret = CCMoveTo::actionWithDuration(arg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMoveTo::jsClass, S_CCMoveTo::jsObject, NULL);
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

JSClass* S_CCTransitionFlipX::jsClass = NULL;
JSObject* S_CCTransitionFlipX::jsObject = NULL;

JSBool S_CCTransitionFlipX::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFlipX::jsClass, S_CCTransitionFlipX::jsObject, NULL);
	S_CCTransitionFlipX *cobj = new S_CCTransitionFlipX(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFlipX::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFlipX *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFlipX::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipX *cobj; JSGET_PTRSHELL(S_CCTransitionFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFlipX::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipX *cobj; JSGET_PTRSHELL(S_CCTransitionFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFlipX::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFlipX::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionFlipX::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionFlipX::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFlipX::onEnter();
}
JSBool S_CCTransitionFlipX::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFlipX* ret = CCTransitionFlipX::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFlipX::jsClass, S_CCTransitionFlipX::jsObject, NULL);
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

JSClass* S_CCRect::jsClass = NULL;
JSObject* S_CCRect::jsObject = NULL;

JSBool S_CCRect::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
	S_CCRect *cobj = new S_CCRect(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRect::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRect *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCRect::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRect *cobj; JSGET_PTRSHELL(S_CCRect, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOrigin:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->origin);
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->size);
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRect::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRect *cobj; JSGET_PTRSHELL(S_CCRect, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOrigin:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->origin = *tmp; }
		} while (0);
		break;
	case kSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->size = *tmp; }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRect::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"origin", kOrigin, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet},
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRect::jsPropertyGet, S_CCRect::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("CCRectGetMinX", S_CCRect::jsCCRectGetMinX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMaxX", S_CCRect::jsCCRectGetMaxX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMidX", S_CCRect::jsCCRectGetMidX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMinY", S_CCRect::jsCCRectGetMinY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMaxY", S_CCRect::jsCCRectGetMaxY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectGetMidY", S_CCRect::jsCCRectGetMidY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectEqualToRect", S_CCRect::jsCCRectEqualToRect, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectContainsPoint", S_CCRect::jsCCRectContainsPoint, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("CCRectIntersectsRect", S_CCRect::jsCCRectIntersectsRect, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCRect::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRect::jsCCRectGetMinX(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMinX(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectGetMaxX(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMaxX(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectGetMidX(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMidX(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectGetMinY(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMinY(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectGetMaxY(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMaxY(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectGetMidY(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		float ret = CCRect::CCRectGetMidY(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectEqualToRect(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		bool ret = CCRect::CCRectEqualToRect(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectContainsPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		bool ret = CCRect::CCRectContainsPoint(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRect::jsCCRectIntersectsRect(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		bool ret = CCRect::CCRectIntersectsRect(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTransitionShrinkGrow::jsClass = NULL;
JSObject* S_CCTransitionShrinkGrow::jsObject = NULL;

JSBool S_CCTransitionShrinkGrow::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionShrinkGrow::jsClass, S_CCTransitionShrinkGrow::jsObject, NULL);
	S_CCTransitionShrinkGrow *cobj = new S_CCTransitionShrinkGrow(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionShrinkGrow::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionShrinkGrow *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionShrinkGrow::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionShrinkGrow *cobj; JSGET_PTRSHELL(S_CCTransitionShrinkGrow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionShrinkGrow::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionShrinkGrow *cobj; JSGET_PTRSHELL(S_CCTransitionShrinkGrow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionShrinkGrow::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("easeActionWithAction", S_CCTransitionShrinkGrow::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionShrinkGrow::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionShrinkGrow::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionShrinkGrow::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionShrinkGrow::onEnter();
}
JSBool S_CCTransitionShrinkGrow::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionShrinkGrow* self = NULL; JSGET_PTRSHELL(S_CCTransitionShrinkGrow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionShrinkGrow::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionShrinkGrow* ret = CCTransitionShrinkGrow::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionShrinkGrow::jsClass, S_CCTransitionShrinkGrow::jsObject, NULL);
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

JSClass* S_CCTransitionSplitCols::jsClass = NULL;
JSObject* S_CCTransitionSplitCols::jsObject = NULL;

JSBool S_CCTransitionSplitCols::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSplitCols::jsClass, S_CCTransitionSplitCols::jsObject, NULL);
	S_CCTransitionSplitCols *cobj = new S_CCTransitionSplitCols(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSplitCols::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSplitCols *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSplitCols::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSplitCols *cobj; JSGET_PTRSHELL(S_CCTransitionSplitCols, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSplitCols::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSplitCols *cobj; JSGET_PTRSHELL(S_CCTransitionSplitCols, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSplitCols::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("action", S_CCTransitionSplitCols::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("easeActionWithAction", S_CCTransitionSplitCols::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSplitCols::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionSplitCols::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSplitCols::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSplitCols* self = NULL; JSGET_PTRSHELL(S_CCTransitionSplitCols, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
void S_CCTransitionSplitCols::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionSplitCols::onEnter();
}
JSBool S_CCTransitionSplitCols::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSplitCols* self = NULL; JSGET_PTRSHELL(S_CCTransitionSplitCols, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSplitCols::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSplitCols* ret = CCTransitionSplitCols::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSplitCols::jsClass, S_CCTransitionSplitCols::jsObject, NULL);
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

JSClass* S_CCShakyTiles3D::jsClass = NULL;
JSObject* S_CCShakyTiles3D::jsObject = NULL;

JSBool S_CCShakyTiles3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCShakyTiles3D::jsClass, S_CCShakyTiles3D::jsObject, NULL);
	S_CCShakyTiles3D *cobj = new S_CCShakyTiles3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCShakyTiles3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCShakyTiles3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCShakyTiles3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShakyTiles3D *cobj; JSGET_PTRSHELL(S_CCShakyTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCShakyTiles3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShakyTiles3D *cobj; JSGET_PTRSHELL(S_CCShakyTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCShakyTiles3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"randrange", kRandrange, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShakyTiles3D::jsPropertyGet, S_CCShakyTiles3D::jsPropertySet},
			{"shakeZ", kShakeZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShakyTiles3D::jsPropertyGet, S_CCShakyTiles3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithRange", S_CCShakyTiles3D::jsinitWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithRange", S_CCShakyTiles3D::jsactionWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCShakyTiles3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCShakyTiles3D::jsinitWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShakyTiles3D* self = NULL; JSGET_PTRSHELL(S_CCShakyTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithRange(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShakyTiles3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShakyTiles3D* self = NULL; JSGET_PTRSHELL(S_CCShakyTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShakyTiles3D::jsactionWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCShakyTiles3D* ret = CCShakyTiles3D::actionWithRange(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCShakyTiles3D::jsClass, S_CCShakyTiles3D::jsObject, NULL);
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

JSClass* S_CCEaseElasticOut::jsClass = NULL;
JSObject* S_CCEaseElasticOut::jsObject = NULL;

JSBool S_CCEaseElasticOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseElasticOut::jsClass, S_CCEaseElasticOut::jsObject, NULL);
	S_CCEaseElasticOut *cobj = new S_CCEaseElasticOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseElasticOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseElasticOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseElasticOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticOut *cobj; JSGET_PTRSHELL(S_CCEaseElasticOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseElasticOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticOut *cobj; JSGET_PTRSHELL(S_CCEaseElasticOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseElasticOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseElasticOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseElasticOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseElastic::jsObject,jsClass,S_CCEaseElasticOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseElasticOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticOut* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseElasticOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticOut* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseElasticOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseElasticOut* ret = CCEaseElasticOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseElasticOut::jsClass, S_CCEaseElasticOut::jsObject, NULL);
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

JSClass* S_CCRotateTo::jsClass = NULL;
JSObject* S_CCRotateTo::jsObject = NULL;

JSBool S_CCRotateTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRotateTo::jsClass, S_CCRotateTo::jsObject, NULL);
	S_CCRotateTo *cobj = new S_CCRotateTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRotateTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRotateTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRotateTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRotateTo *cobj; JSGET_PTRSHELL(S_CCRotateTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRotateTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRotateTo *cobj; JSGET_PTRSHELL(S_CCRotateTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRotateTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"dstAngle", kDstAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRotateTo::jsPropertyGet, S_CCRotateTo::jsPropertySet},
			{"startAngle", kStartAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRotateTo::jsPropertyGet, S_CCRotateTo::jsPropertySet},
			{"diffAngle", kDiffAngle, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRotateTo::jsPropertyGet, S_CCRotateTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCRotateTo::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCRotateTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCRotateTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCRotateTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRotateTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateTo* self = NULL; JSGET_PTRSHELL(S_CCRotateTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateTo* self = NULL; JSGET_PTRSHELL(S_CCRotateTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRotateTo* self = NULL; JSGET_PTRSHELL(S_CCRotateTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRotateTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		CCRotateTo* ret = CCRotateTo::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRotateTo::jsClass, S_CCRotateTo::jsObject, NULL);
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

JSClass* S_CCTransitionProgressRadialCW::jsClass = NULL;
JSObject* S_CCTransitionProgressRadialCW::jsObject = NULL;

JSBool S_CCTransitionProgressRadialCW::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionProgressRadialCW::jsClass, S_CCTransitionProgressRadialCW::jsObject, NULL);
	S_CCTransitionProgressRadialCW *cobj = new S_CCTransitionProgressRadialCW(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionProgressRadialCW::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionProgressRadialCW *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionProgressRadialCW::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionProgressRadialCW *cobj; JSGET_PTRSHELL(S_CCTransitionProgressRadialCW, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionProgressRadialCW::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionProgressRadialCW *cobj; JSGET_PTRSHELL(S_CCTransitionProgressRadialCW, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionProgressRadialCW::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionProgressRadialCW::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionProgressRadialCCW::jsObject,jsClass,S_CCTransitionProgressRadialCW::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionProgressRadialCW::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionProgressRadialCW* ret = CCTransitionProgressRadialCW::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionProgressRadialCW::jsClass, S_CCTransitionProgressRadialCW::jsObject, NULL);
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

JSClass* S_CCAtlasNode::jsClass = NULL;
JSObject* S_CCAtlasNode::jsObject = NULL;

JSBool S_CCAtlasNode::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAtlasNode::jsClass, S_CCAtlasNode::jsObject, NULL);
	S_CCAtlasNode *cobj = new S_CCAtlasNode(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAtlasNode::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAtlasNode *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAtlasNode::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAtlasNode *cobj; JSGET_PTRSHELL(S_CCAtlasNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTextureAtlas:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTextureAtlas::jsClass, S_CCTextureAtlas::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTextureAtlas();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	case kColor:
				// don't know what this is (c ~> js)
		break;
	case kQuadsToDraw:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getQuadsToDraw(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAtlasNode::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAtlasNode *cobj; JSGET_PTRSHELL(S_CCAtlasNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTextureAtlas:
		do {
			CCTextureAtlas* tmp; JSGET_PTRSHELL(CCTextureAtlas, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTextureAtlas(tmp); }
		} while (0);
		break;
	case kIsOpacityModifyRGB:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setOpacityModifyRGB(tmp); } while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	case kColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setColor(color);
		} while (0);
		break;
	case kQuadsToDraw:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setQuadsToDraw(tmp); } while (0);
		break;
	case kOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAtlasNode::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"itemsPerRow", kItemsPerRow, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"itemsPerColumn", kItemsPerColumn, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"itemWidth", kItemWidth, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"itemHeight", kItemHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"colorUnmodified", kColorUnmodified, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"textureAtlas", kTextureAtlas, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"cOpacity", kCOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"quadsToDraw", kQuadsToDraw, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAtlasNode::jsPropertyGet, S_CCAtlasNode::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTileFile", S_CCAtlasNode::jsinitWithTileFile, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateAtlasValues", S_CCAtlasNode::jsupdateAtlasValues, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCAtlasNode::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("atlasWithTileFile", S_CCAtlasNode::jsatlasWithTileFile, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCAtlasNode::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAtlasNode::jsatlasWithTileFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		JSString *arg0;
		unsigned int arg1;
		unsigned int arg2;
		unsigned int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "Siii", &arg0, &arg1, &arg2, &arg3);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCAtlasNode* ret = CCAtlasNode::atlasWithTileFile(narg0, arg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAtlasNode::jsClass, S_CCAtlasNode::jsObject, NULL);
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
JSBool S_CCAtlasNode::jsinitWithTileFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAtlasNode* self = NULL; JSGET_PTRSHELL(S_CCAtlasNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		JSString *arg0;
		unsigned int arg1;
		unsigned int arg2;
		unsigned int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "Siii", &arg0, &arg1, &arg2, &arg3);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithTileFile(narg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAtlasNode::jsupdateAtlasValues(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAtlasNode* self = NULL; JSGET_PTRSHELL(S_CCAtlasNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->updateAtlasValues();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAtlasNode::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAtlasNode* self = NULL; JSGET_PTRSHELL(S_CCAtlasNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCAtlasNode::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCWaves::jsClass = NULL;
JSObject* S_CCWaves::jsObject = NULL;

JSBool S_CCWaves::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCWaves::jsClass, S_CCWaves::jsObject, NULL);
	S_CCWaves *cobj = new S_CCWaves(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCWaves::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCWaves *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCWaves::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWaves *cobj; JSGET_PTRSHELL(S_CCWaves, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCWaves::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWaves *cobj; JSGET_PTRSHELL(S_CCWaves, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCWaves::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"waves", kWaves, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves::jsPropertyGet, S_CCWaves::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves::jsPropertyGet, S_CCWaves::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves::jsPropertyGet, S_CCWaves::jsPropertySet},
			{"vertical", kVertical, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves::jsPropertyGet, S_CCWaves::jsPropertySet},
			{"horizontal", kHorizontal, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves::jsPropertyGet, S_CCWaves::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithWaves", S_CCWaves::jsinitWithWaves, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithWaves", S_CCWaves::jsactionWithWaves, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCWaves::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCWaves::jsinitWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWaves* self = NULL; JSGET_PTRSHELL(S_CCWaves, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 6) {
		int arg0;
		double arg1;
		JSBool arg2;
		JSBool arg3;
		JSObject *arg4;
		double arg5;
		JS_ConvertArguments(cx, 6, JS_ARGV(cx, vp), "idbbod", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5);
		ccGridSize* narg4; JSGET_PTRSHELL(ccGridSize, narg4, arg4);
		bool ret = self->initWithWaves(arg0, arg1, arg2, arg3, *narg4, arg5);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWaves::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWaves* self = NULL; JSGET_PTRSHELL(S_CCWaves, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWaves::jsactionWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 6) {
		int arg0;
		double arg1;
		JSBool arg2;
		JSBool arg3;
		JSObject *arg4;
		double arg5;
		JS_ConvertArguments(cx, 6, JS_ARGV(cx, vp), "idbbod", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5);
		ccGridSize* narg4; JSGET_PTRSHELL(ccGridSize, narg4, arg4);
		CCWaves* ret = CCWaves::actionWithWaves(arg0, arg1, arg2, arg3, *narg4, arg5);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCWaves::jsClass, S_CCWaves::jsObject, NULL);
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

JSClass* S_CCShow::jsClass = NULL;
JSObject* S_CCShow::jsObject = NULL;

JSBool S_CCShow::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCShow::jsClass, S_CCShow::jsObject, NULL);
	S_CCShow *cobj = new S_CCShow(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCShow::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCShow *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCShow::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShow *cobj; JSGET_PTRSHELL(S_CCShow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCShow::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShow *cobj; JSGET_PTRSHELL(S_CCShow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCShow::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCShow::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCShow::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("action", S_CCShow::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCShow::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCShow::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShow* self = NULL; JSGET_PTRSHELL(S_CCShow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShow::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShow* self = NULL; JSGET_PTRSHELL(S_CCShow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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
JSBool S_CCShow::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCShow* ret = CCShow::action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCShow::jsClass, S_CCShow::jsObject, NULL);
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

JSClass* S_CCEaseElasticInOut::jsClass = NULL;
JSObject* S_CCEaseElasticInOut::jsObject = NULL;

JSBool S_CCEaseElasticInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseElasticInOut::jsClass, S_CCEaseElasticInOut::jsObject, NULL);
	S_CCEaseElasticInOut *cobj = new S_CCEaseElasticInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseElasticInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseElasticInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseElasticInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticInOut *cobj; JSGET_PTRSHELL(S_CCEaseElasticInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseElasticInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseElasticInOut *cobj; JSGET_PTRSHELL(S_CCEaseElasticInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseElasticInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseElasticInOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseElasticInOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseElastic::jsObject,jsClass,S_CCEaseElasticInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseElasticInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseElasticInOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseElasticInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseElasticInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseElasticInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseElasticInOut* ret = CCEaseElasticInOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseElasticInOut::jsClass, S_CCEaseElasticInOut::jsObject, NULL);
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

JSClass* S_CCOrbitCamera::jsClass = NULL;
JSObject* S_CCOrbitCamera::jsObject = NULL;

JSBool S_CCOrbitCamera::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCOrbitCamera::jsClass, S_CCOrbitCamera::jsObject, NULL);
	S_CCOrbitCamera *cobj = new S_CCOrbitCamera(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCOrbitCamera::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCOrbitCamera *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCOrbitCamera::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCOrbitCamera *cobj; JSGET_PTRSHELL(S_CCOrbitCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCOrbitCamera::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCOrbitCamera *cobj; JSGET_PTRSHELL(S_CCOrbitCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCOrbitCamera::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"radius", kRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"deltaRadius", kDeltaRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"angleZ", kAngleZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"deltaAngleZ", kDeltaAngleZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"angleX", kAngleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"deltaAngleX", kDeltaAngleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"radZ", kRadZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"radDeltaZ", kRadDeltaZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"radX", kRadX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{"radDeltaX", kRadDeltaX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCOrbitCamera::jsPropertyGet, S_CCOrbitCamera::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCOrbitCamera::jsinitWithDuration, 7, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCOrbitCamera::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCOrbitCamera::jsactionWithDuration, 7, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionCamera::jsObject,jsClass,S_CCOrbitCamera::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCOrbitCamera::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 7) {
		double arg0;
		double arg1;
		double arg2;
		double arg3;
		double arg4;
		double arg5;
		double arg6;
		JS_ConvertArguments(cx, 7, JS_ARGV(cx, vp), "ddddddd", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6);
		CCOrbitCamera* ret = CCOrbitCamera::actionWithDuration(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCOrbitCamera::jsClass, S_CCOrbitCamera::jsObject, NULL);
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
JSBool S_CCOrbitCamera::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCOrbitCamera* self = NULL; JSGET_PTRSHELL(S_CCOrbitCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 7) {
		double arg0;
		double arg1;
		double arg2;
		double arg3;
		double arg4;
		double arg5;
		double arg6;
		JS_ConvertArguments(cx, 7, JS_ARGV(cx, vp), "ddddddd", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6);
		bool ret = self->initWithDuration(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCOrbitCamera::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCOrbitCamera* self = NULL; JSGET_PTRSHELL(S_CCOrbitCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCOrbitCamera::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCOrbitCamera* self = NULL; JSGET_PTRSHELL(S_CCOrbitCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTransitionSlideInL::jsClass = NULL;
JSObject* S_CCTransitionSlideInL::jsObject = NULL;

JSBool S_CCTransitionSlideInL::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSlideInL::jsClass, S_CCTransitionSlideInL::jsObject, NULL);
	S_CCTransitionSlideInL *cobj = new S_CCTransitionSlideInL(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSlideInL::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSlideInL *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSlideInL::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInL *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSlideInL::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInL *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInL, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSlideInL::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionSlideInL::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("action", S_CCTransitionSlideInL::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("easeActionWithAction", S_CCTransitionSlideInL::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSlideInL::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionSlideInL::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSlideInL::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionSlideInL::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
void S_CCTransitionSlideInL::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionSlideInL::onEnter();
}
JSBool S_CCTransitionSlideInL::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInL* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInL, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSlideInL::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSlideInL* ret = CCTransitionSlideInL::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSlideInL::jsClass, S_CCTransitionSlideInL::jsObject, NULL);
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

JSClass* S_CCEaseBounceIn::jsClass = NULL;
JSObject* S_CCEaseBounceIn::jsObject = NULL;

JSBool S_CCEaseBounceIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBounceIn::jsClass, S_CCEaseBounceIn::jsObject, NULL);
	S_CCEaseBounceIn *cobj = new S_CCEaseBounceIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBounceIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBounceIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBounceIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceIn *cobj; JSGET_PTRSHELL(S_CCEaseBounceIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBounceIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceIn *cobj; JSGET_PTRSHELL(S_CCEaseBounceIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBounceIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseBounceIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBounceIn::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseBounce::jsObject,jsClass,S_CCEaseBounceIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBounceIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounceIn* self = NULL; JSGET_PTRSHELL(S_CCEaseBounceIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBounceIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounceIn* self = NULL; JSGET_PTRSHELL(S_CCEaseBounceIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseBounceIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBounceIn* ret = CCEaseBounceIn::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBounceIn::jsClass, S_CCEaseBounceIn::jsObject, NULL);
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

JSClass* S_CCShatteredTiles3D::jsClass = NULL;
JSObject* S_CCShatteredTiles3D::jsObject = NULL;

JSBool S_CCShatteredTiles3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCShatteredTiles3D::jsClass, S_CCShatteredTiles3D::jsObject, NULL);
	S_CCShatteredTiles3D *cobj = new S_CCShatteredTiles3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCShatteredTiles3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCShatteredTiles3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCShatteredTiles3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShatteredTiles3D *cobj; JSGET_PTRSHELL(S_CCShatteredTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCShatteredTiles3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShatteredTiles3D *cobj; JSGET_PTRSHELL(S_CCShatteredTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCShatteredTiles3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"randrange", kRandrange, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShatteredTiles3D::jsPropertyGet, S_CCShatteredTiles3D::jsPropertySet},
			{"once", kOnce, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShatteredTiles3D::jsPropertyGet, S_CCShatteredTiles3D::jsPropertySet},
			{"shatterZ", kShatterZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShatteredTiles3D::jsPropertyGet, S_CCShatteredTiles3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithRange", S_CCShatteredTiles3D::jsinitWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithRange", S_CCShatteredTiles3D::jsactionWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCShatteredTiles3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCShatteredTiles3D::jsinitWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShatteredTiles3D* self = NULL; JSGET_PTRSHELL(S_CCShatteredTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithRange(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShatteredTiles3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShatteredTiles3D* self = NULL; JSGET_PTRSHELL(S_CCShatteredTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShatteredTiles3D::jsactionWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCShatteredTiles3D* ret = CCShatteredTiles3D::actionWithRange(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCShatteredTiles3D::jsClass, S_CCShatteredTiles3D::jsObject, NULL);
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

JSClass* S_CCHide::jsClass = NULL;
JSObject* S_CCHide::jsObject = NULL;

JSBool S_CCHide::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCHide::jsClass, S_CCHide::jsObject, NULL);
	S_CCHide *cobj = new S_CCHide(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCHide::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCHide *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCHide::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCHide *cobj; JSGET_PTRSHELL(S_CCHide, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCHide::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCHide *cobj; JSGET_PTRSHELL(S_CCHide, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCHide::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCHide::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCHide::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("action", S_CCHide::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCHide::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCHide::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCHide* self = NULL; JSGET_PTRSHELL(S_CCHide, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCHide::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCHide* self = NULL; JSGET_PTRSHELL(S_CCHide, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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
JSBool S_CCHide::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCHide* ret = CCHide::action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCHide::jsClass, S_CCHide::jsObject, NULL);
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

JSClass* S_CCTransitionSlideInR::jsClass = NULL;
JSObject* S_CCTransitionSlideInR::jsObject = NULL;

JSBool S_CCTransitionSlideInR::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSlideInR::jsClass, S_CCTransitionSlideInR::jsObject, NULL);
	S_CCTransitionSlideInR *cobj = new S_CCTransitionSlideInR(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSlideInR::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSlideInR *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSlideInR::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInR *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSlideInR::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInR *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSlideInR::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionSlideInR::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("action", S_CCTransitionSlideInR::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSlideInR::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSlideInL::jsObject,jsClass,S_CCTransitionSlideInR::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSlideInR::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInR* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInR, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionSlideInR::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInR* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInR, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSlideInR::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSlideInR* ret = CCTransitionSlideInR::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSlideInR::jsClass, S_CCTransitionSlideInR::jsObject, NULL);
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

JSClass* S_CCToggleVisibility::jsClass = NULL;
JSObject* S_CCToggleVisibility::jsObject = NULL;

JSBool S_CCToggleVisibility::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCToggleVisibility::jsClass, S_CCToggleVisibility::jsObject, NULL);
	S_CCToggleVisibility *cobj = new S_CCToggleVisibility(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCToggleVisibility::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCToggleVisibility *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCToggleVisibility::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCToggleVisibility *cobj; JSGET_PTRSHELL(S_CCToggleVisibility, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCToggleVisibility::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCToggleVisibility *cobj; JSGET_PTRSHELL(S_CCToggleVisibility, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCToggleVisibility::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCToggleVisibility::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("action", S_CCToggleVisibility::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCToggleVisibility::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCToggleVisibility::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCToggleVisibility* self = NULL; JSGET_PTRSHELL(S_CCToggleVisibility, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCToggleVisibility::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCToggleVisibility* ret = CCToggleVisibility::action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCToggleVisibility::jsClass, S_CCToggleVisibility::jsObject, NULL);
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

JSClass* S_CCActionCamera::jsClass = NULL;
JSObject* S_CCActionCamera::jsObject = NULL;

JSBool S_CCActionCamera::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCActionCamera::jsClass, S_CCActionCamera::jsObject, NULL);
	S_CCActionCamera *cobj = new S_CCActionCamera(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCActionCamera::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCActionCamera *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCActionCamera::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionCamera *cobj; JSGET_PTRSHELL(S_CCActionCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCActionCamera::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionCamera *cobj; JSGET_PTRSHELL(S_CCActionCamera, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCActionCamera::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"centerXOrig", kCenterXOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"centerYOrig", kCenterYOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"centerZOrig", kCenterZOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"eyeXOrig", kEyeXOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"eyeYOrig", kEyeYOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"eyeZOrig", kEyeZOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"upXOrig", kUpXOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"upYOrig", kUpYOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{"upZOrig", kUpZOrig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionCamera::jsPropertyGet, S_CCActionCamera::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCActionCamera::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCActionCamera::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCActionCamera::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCActionCamera::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionCamera* self = NULL; JSGET_PTRSHELL(S_CCActionCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionCamera::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionCamera* self = NULL; JSGET_PTRSHELL(S_CCActionCamera, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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

JSClass* S_CCSpriteFrameCache::jsClass = NULL;
JSObject* S_CCSpriteFrameCache::jsObject = NULL;

JSBool S_CCSpriteFrameCache::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCSpriteFrameCache::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSpriteFrameCache *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSpriteFrameCache::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteFrameCache *cobj; JSGET_PTRSHELL(S_CCSpriteFrameCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSpriteFrameCache::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteFrameCache *cobj; JSGET_PTRSHELL(S_CCSpriteFrameCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSpriteFrameCache::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"spriteFrames", kSpriteFrames, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrameCache::jsPropertyGet, S_CCSpriteFrameCache::jsPropertySet},
			{"spriteFramesAliases", kSpriteFramesAliases, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteFrameCache::jsPropertyGet, S_CCSpriteFrameCache::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCSpriteFrameCache::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addSpriteFramesWithFile", S_CCSpriteFrameCache::jsaddSpriteFramesWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addSpriteFrame", S_CCSpriteFrameCache::jsaddSpriteFrame, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeSpriteFrames", S_CCSpriteFrameCache::jsremoveSpriteFrames, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeUnusedSpriteFrames", S_CCSpriteFrameCache::jsremoveUnusedSpriteFrames, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeSpriteFrameByName", S_CCSpriteFrameCache::jsremoveSpriteFrameByName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeSpriteFramesFromFile", S_CCSpriteFrameCache::jsremoveSpriteFramesFromFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeSpriteFramesFromTexture", S_CCSpriteFrameCache::jsremoveSpriteFramesFromTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteFrameByName", S_CCSpriteFrameCache::jsspriteFrameByName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedSpriteFrameCache", S_CCSpriteFrameCache::jssharedSpriteFrameCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeSharedSpriteFrameCache", S_CCSpriteFrameCache::jspurgeSharedSpriteFrameCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSpriteFrameCache::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSpriteFrameCache::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsaddSpriteFramesWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->addSpriteFramesWithFile(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsaddSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oS", &arg0, &arg1);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		self->addSpriteFrame(narg0, narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsremoveSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->removeSpriteFrames();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsremoveUnusedSpriteFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->removeUnusedSpriteFrames();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsremoveSpriteFrameByName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->removeSpriteFrameByName(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsremoveSpriteFramesFromFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->removeSpriteFramesFromFile(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsremoveSpriteFramesFromTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		self->removeSpriteFramesFromTexture(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteFrameCache::jsspriteFrameByName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteFrameCache* self = NULL; JSGET_PTRSHELL(S_CCSpriteFrameCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSpriteFrame* ret = self->spriteFrameByName(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteFrame::jsClass, S_CCSpriteFrame::jsObject, NULL);
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
JSBool S_CCSpriteFrameCache::jssharedSpriteFrameCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCSpriteFrameCache* ret = CCSpriteFrameCache::sharedSpriteFrameCache();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteFrameCache::jsClass, S_CCSpriteFrameCache::jsObject, NULL);
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
JSBool S_CCSpriteFrameCache::jspurgeSharedSpriteFrameCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCSpriteFrameCache::purgeSharedSpriteFrameCache();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCShuffleTiles::jsClass = NULL;
JSObject* S_CCShuffleTiles::jsObject = NULL;

JSBool S_CCShuffleTiles::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCShuffleTiles::jsClass, S_CCShuffleTiles::jsObject, NULL);
	S_CCShuffleTiles *cobj = new S_CCShuffleTiles(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCShuffleTiles::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCShuffleTiles *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCShuffleTiles::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShuffleTiles *cobj; JSGET_PTRSHELL(S_CCShuffleTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCShuffleTiles::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShuffleTiles *cobj; JSGET_PTRSHELL(S_CCShuffleTiles, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCShuffleTiles::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"seed", kSeed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShuffleTiles::jsPropertyGet, S_CCShuffleTiles::jsPropertySet},
			{"tilesCount", kTilesCount, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShuffleTiles::jsPropertyGet, S_CCShuffleTiles::jsPropertySet},
			{"tilesOrder", kTilesOrder, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShuffleTiles::jsPropertyGet, S_CCShuffleTiles::jsPropertySet},
			{"tiles", kTiles, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShuffleTiles::jsPropertyGet, S_CCShuffleTiles::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithSeed", S_CCShuffleTiles::jsinitWithSeed, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCShuffleTiles::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSeed", S_CCShuffleTiles::jsactionWithSeed, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCShuffleTiles::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCShuffleTiles::jsinitWithSeed(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShuffleTiles* self = NULL; JSGET_PTRSHELL(S_CCShuffleTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		int arg0;
		JSObject *arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "iod", &arg0, &arg1, &arg2);
		ccGridSize* narg1; JSGET_PTRSHELL(ccGridSize, narg1, arg1);
		bool ret = self->initWithSeed(arg0, *narg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShuffleTiles::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShuffleTiles* self = NULL; JSGET_PTRSHELL(S_CCShuffleTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShuffleTiles::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShuffleTiles* self = NULL; JSGET_PTRSHELL(S_CCShuffleTiles, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShuffleTiles::jsactionWithSeed(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		int arg0;
		JSObject *arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "iod", &arg0, &arg1, &arg2);
		ccGridSize* narg1; JSGET_PTRSHELL(ccGridSize, narg1, arg1);
		CCShuffleTiles* ret = CCShuffleTiles::actionWithSeed(arg0, *narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCShuffleTiles::jsClass, S_CCShuffleTiles::jsObject, NULL);
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

JSClass* S_CCEaseBounce::jsClass = NULL;
JSObject* S_CCEaseBounce::jsObject = NULL;

JSBool S_CCEaseBounce::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBounce::jsClass, S_CCEaseBounce::jsObject, NULL);
	S_CCEaseBounce *cobj = new S_CCEaseBounce(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBounce::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBounce *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBounce::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounce *cobj; JSGET_PTRSHELL(S_CCEaseBounce, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBounce::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounce *cobj; JSGET_PTRSHELL(S_CCEaseBounce, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBounce::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("bounceTime", S_CCEaseBounce::jsbounceTime, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBounce::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseBounce::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBounce::jsbounceTime(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounce* self = NULL; JSGET_PTRSHELL(S_CCEaseBounce, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		float ret = self->bounceTime(arg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBounce::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBounce* ret = CCEaseBounce::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBounce::jsClass, S_CCEaseBounce::jsObject, NULL);
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

JSClass* S_CCLayerGradient::jsClass = NULL;
JSObject* S_CCLayerGradient::jsObject = NULL;

JSBool S_CCLayerGradient::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLayerGradient::jsClass, S_CCLayerGradient::jsObject, NULL);
	S_CCLayerGradient *cobj = new S_CCLayerGradient(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLayerGradient::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLayerGradient *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLayerGradient::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayerGradient *cobj; JSGET_PTRSHELL(S_CCLayerGradient, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kEndColor:
				// don't know what this is (c ~> js)
		break;
	case kStartColor:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			ccColor3B* ctmp = new ccColor3B(cobj->getStartColor());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kStartOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getStartOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kEndOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getEndOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kVector:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getVector());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsCompressedInterpolation:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isCompressedInterpolation()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLayerGradient::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLayerGradient *cobj; JSGET_PTRSHELL(S_CCLayerGradient, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kEndColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setEndColor(color);
		} while (0);
		break;
	case kStartColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setStartColor(color);
		} while (0);
		break;
	case kStartOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setStartOpacity(tmp); } while (0);
		break;
	case kEndOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setEndOpacity(tmp); } while (0);
		break;
	case kVector:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setVector(*tmp); }
		} while (0);
		break;
	case kIsCompressedInterpolation:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setCompressedInterpolation(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLayerGradient::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"endColor", kEndColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"cEndOpacity", kCEndOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"alongVector", kAlongVector, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"compressedInterpolation", kCompressedInterpolation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"startColor", kStartColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"startOpacity", kStartOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"endOpacity", kEndOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"vector", kVector, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{"isCompressedInterpolation", kIsCompressedInterpolation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLayerGradient::jsPropertyGet, S_CCLayerGradient::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithColor", S_CCLayerGradient::jsinitWithColor, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("layerWithColor", S_CCLayerGradient::jslayerWithColor, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCLayerColor::jsObject,jsClass,S_CCLayerGradient::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLayerGradient::jslayerWithColor(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		ccColor4B* narg1; JSGET_PTRSHELL(ccColor4B, narg1, arg1);
		CCLayerGradient* ret = CCLayerGradient::layerWithColor(*narg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLayerGradient::jsClass, S_CCLayerGradient::jsObject, NULL);
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
JSBool S_CCLayerGradient::jsinitWithColor(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLayerGradient* self = NULL; JSGET_PTRSHELL(S_CCLayerGradient, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		ccColor4B* narg0; JSGET_PTRSHELL(ccColor4B, narg0, arg0);
		ccColor4B* narg1; JSGET_PTRSHELL(ccColor4B, narg1, arg1);
		bool ret = self->initWithColor(*narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCFlipX::jsClass = NULL;
JSObject* S_CCFlipX::jsObject = NULL;

JSBool S_CCFlipX::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFlipX::jsClass, S_CCFlipX::jsObject, NULL);
	S_CCFlipX *cobj = new S_CCFlipX(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFlipX::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFlipX *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFlipX::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipX *cobj; JSGET_PTRSHELL(S_CCFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFlipX::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipX *cobj; JSGET_PTRSHELL(S_CCFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFlipX::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"flipX", kFlipX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFlipX::jsPropertyGet, S_CCFlipX::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFlipX", S_CCFlipX::jsinitWithFlipX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCFlipX::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCFlipX::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithFlipX", S_CCFlipX::jsactionWithFlipX, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCFlipX::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFlipX::jsactionWithFlipX(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		CCFlipX* ret = CCFlipX::actionWithFlipX(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFlipX::jsClass, S_CCFlipX::jsObject, NULL);
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
JSBool S_CCFlipX::jsinitWithFlipX(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX* self = NULL; JSGET_PTRSHELL(S_CCFlipX, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		bool ret = self->initWithFlipX(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipX::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX* self = NULL; JSGET_PTRSHELL(S_CCFlipX, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipX::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX* self = NULL; JSGET_PTRSHELL(S_CCFlipX, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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

JSClass* S_CCEaseBounceInOut::jsClass = NULL;
JSObject* S_CCEaseBounceInOut::jsObject = NULL;

JSBool S_CCEaseBounceInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBounceInOut::jsClass, S_CCEaseBounceInOut::jsObject, NULL);
	S_CCEaseBounceInOut *cobj = new S_CCEaseBounceInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBounceInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBounceInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBounceInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceInOut *cobj; JSGET_PTRSHELL(S_CCEaseBounceInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBounceInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceInOut *cobj; JSGET_PTRSHELL(S_CCEaseBounceInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBounceInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBounceInOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseBounce::jsObject,jsClass,S_CCEaseBounceInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBounceInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounceInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBounceInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBounceInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBounceInOut* ret = CCEaseBounceInOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBounceInOut::jsClass, S_CCEaseBounceInOut::jsObject, NULL);
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

JSClass* S_CCRepeat::jsClass = NULL;
JSObject* S_CCRepeat::jsObject = NULL;

JSBool S_CCRepeat::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRepeat::jsClass, S_CCRepeat::jsObject, NULL);
	S_CCRepeat *cobj = new S_CCRepeat(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRepeat::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRepeat *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRepeat::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRepeat *cobj; JSGET_PTRSHELL(S_CCRepeat, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kInnerAction:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getInnerAction();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRepeat::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRepeat *cobj; JSGET_PTRSHELL(S_CCRepeat, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kInnerAction:
		do {
			CCFiniteTimeAction* tmp; JSGET_PTRSHELL(CCFiniteTimeAction, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setInnerAction(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRepeat::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"times", kTimes, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRepeat::jsPropertyGet, S_CCRepeat::jsPropertySet},
			{"total", kTotal, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRepeat::jsPropertyGet, S_CCRepeat::jsPropertySet},
			{"innerAction", kInnerAction, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRepeat::jsPropertyGet, S_CCRepeat::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCRepeat::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCRepeat::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCRepeat::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDone", S_CCRepeat::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCRepeat::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCRepeat::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCRepeat::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRepeat::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeat::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeat::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeat::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeat::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeat::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeat* self = NULL; JSGET_PTRSHELL(S_CCRepeat, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCRepeat::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCFiniteTimeAction* narg0; JSGET_PTRSHELL(CCFiniteTimeAction, narg0, arg0);
		CCRepeat* ret = CCRepeat::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRepeat::jsClass, S_CCRepeat::jsObject, NULL);
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

JSClass* S_CCFlipY::jsClass = NULL;
JSObject* S_CCFlipY::jsObject = NULL;

JSBool S_CCFlipY::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFlipY::jsClass, S_CCFlipY::jsObject, NULL);
	S_CCFlipY *cobj = new S_CCFlipY(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFlipY::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFlipY *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFlipY::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipY *cobj; JSGET_PTRSHELL(S_CCFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFlipY::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipY *cobj; JSGET_PTRSHELL(S_CCFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFlipY::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"flipY", kFlipY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFlipY::jsPropertyGet, S_CCFlipY::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFlipY", S_CCFlipY::jsinitWithFlipY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCFlipY::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCFlipY::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithFlipY", S_CCFlipY::jsactionWithFlipY, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInstant::jsObject,jsClass,S_CCFlipY::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFlipY::jsactionWithFlipY(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		CCFlipY* ret = CCFlipY::actionWithFlipY(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFlipY::jsClass, S_CCFlipY::jsObject, NULL);
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
JSBool S_CCFlipY::jsinitWithFlipY(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipY* self = NULL; JSGET_PTRSHELL(S_CCFlipY, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		bool ret = self->initWithFlipY(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipY::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipY* self = NULL; JSGET_PTRSHELL(S_CCFlipY, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipY::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipY* self = NULL; JSGET_PTRSHELL(S_CCFlipY, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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

JSClass* S_CCEaseBackIn::jsClass = NULL;
JSObject* S_CCEaseBackIn::jsObject = NULL;

JSBool S_CCEaseBackIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBackIn::jsClass, S_CCEaseBackIn::jsObject, NULL);
	S_CCEaseBackIn *cobj = new S_CCEaseBackIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBackIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBackIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBackIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackIn *cobj; JSGET_PTRSHELL(S_CCEaseBackIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBackIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBackIn *cobj; JSGET_PTRSHELL(S_CCEaseBackIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBackIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseBackIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBackIn::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseBackIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBackIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBackIn* self = NULL; JSGET_PTRSHELL(S_CCEaseBackIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBackIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBackIn* self = NULL; JSGET_PTRSHELL(S_CCEaseBackIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseBackIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBackIn* ret = CCEaseBackIn::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBackIn::jsClass, S_CCEaseBackIn::jsObject, NULL);
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

JSClass* S_CCTransitionMoveInT::jsClass = NULL;
JSObject* S_CCTransitionMoveInT::jsObject = NULL;

JSBool S_CCTransitionMoveInT::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionMoveInT::jsClass, S_CCTransitionMoveInT::jsObject, NULL);
	S_CCTransitionMoveInT *cobj = new S_CCTransitionMoveInT(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionMoveInT::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionMoveInT *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionMoveInT::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInT *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInT, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionMoveInT::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInT *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInT, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionMoveInT::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionMoveInT::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionMoveInT::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionMoveInL::jsObject,jsClass,S_CCTransitionMoveInT::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionMoveInT::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInT* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInT, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionMoveInT::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionMoveInT* ret = CCTransitionMoveInT::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionMoveInT::jsClass, S_CCTransitionMoveInT::jsObject, NULL);
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

JSClass* S_CCEaseBounceOut::jsClass = NULL;
JSObject* S_CCEaseBounceOut::jsObject = NULL;

JSBool S_CCEaseBounceOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseBounceOut::jsClass, S_CCEaseBounceOut::jsObject, NULL);
	S_CCEaseBounceOut *cobj = new S_CCEaseBounceOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseBounceOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseBounceOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseBounceOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceOut *cobj; JSGET_PTRSHELL(S_CCEaseBounceOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseBounceOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseBounceOut *cobj; JSGET_PTRSHELL(S_CCEaseBounceOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseBounceOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseBounceOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseBounceOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseBounce::jsObject,jsClass,S_CCEaseBounceOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseBounceOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounceOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBounceOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseBounceOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseBounceOut* self = NULL; JSGET_PTRSHELL(S_CCEaseBounceOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseBounceOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseBounceOut* ret = CCEaseBounceOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseBounceOut::jsClass, S_CCEaseBounceOut::jsObject, NULL);
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

JSClass* S_CCTransitionMoveInR::jsClass = NULL;
JSObject* S_CCTransitionMoveInR::jsObject = NULL;

JSBool S_CCTransitionMoveInR::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionMoveInR::jsClass, S_CCTransitionMoveInR::jsObject, NULL);
	S_CCTransitionMoveInR *cobj = new S_CCTransitionMoveInR(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionMoveInR::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionMoveInR *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionMoveInR::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInR *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionMoveInR::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInR *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionMoveInR::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionMoveInR::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionMoveInR::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionMoveInL::jsObject,jsClass,S_CCTransitionMoveInR::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionMoveInR::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInR* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInR, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionMoveInR::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionMoveInR* ret = CCTransitionMoveInR::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionMoveInR::jsClass, S_CCTransitionMoveInR::jsObject, NULL);
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

JSClass* S_CCTransitionMoveInB::jsClass = NULL;
JSObject* S_CCTransitionMoveInB::jsObject = NULL;

JSBool S_CCTransitionMoveInB::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionMoveInB::jsClass, S_CCTransitionMoveInB::jsObject, NULL);
	S_CCTransitionMoveInB *cobj = new S_CCTransitionMoveInB(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionMoveInB::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionMoveInB *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionMoveInB::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInB *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInB, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionMoveInB::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionMoveInB *cobj; JSGET_PTRSHELL(S_CCTransitionMoveInB, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionMoveInB::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionMoveInB::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionMoveInB::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionMoveInL::jsObject,jsClass,S_CCTransitionMoveInB::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionMoveInB::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionMoveInB* self = NULL; JSGET_PTRSHELL(S_CCTransitionMoveInB, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionMoveInB::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionMoveInB* ret = CCTransitionMoveInB::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionMoveInB::jsClass, S_CCTransitionMoveInB::jsObject, NULL);
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

JSClass* S_CCBezierBy::jsClass = NULL;
JSObject* S_CCBezierBy::jsObject = NULL;

JSBool S_CCBezierBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCBezierBy::jsClass, S_CCBezierBy::jsObject, NULL);
	S_CCBezierBy *cobj = new S_CCBezierBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCBezierBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCBezierBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCBezierBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBezierBy *cobj; JSGET_PTRSHELL(S_CCBezierBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCBezierBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBezierBy *cobj; JSGET_PTRSHELL(S_CCBezierBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCBezierBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"config", kConfig, JSPROP_PERMANENT | JSPROP_SHARED, S_CCBezierBy::jsPropertyGet, S_CCBezierBy::jsPropertySet},
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCBezierBy::jsPropertyGet, S_CCBezierBy::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCBezierBy::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCBezierBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCBezierBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCBezierBy::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCBezierBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCBezierBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBezierBy* self = NULL; JSGET_PTRSHELL(S_CCBezierBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		ccBezierConfig* narg1; JSGET_PTRSHELL(ccBezierConfig, narg1, arg1);
		bool ret = self->initWithDuration(arg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBezierBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBezierBy* self = NULL; JSGET_PTRSHELL(S_CCBezierBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBezierBy::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBezierBy* self = NULL; JSGET_PTRSHELL(S_CCBezierBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBezierBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBezierBy* self = NULL; JSGET_PTRSHELL(S_CCBezierBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCBezierBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		ccBezierConfig* narg1; JSGET_PTRSHELL(ccBezierConfig, narg1, arg1);
		CCBezierBy* ret = CCBezierBy::actionWithDuration(arg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCBezierBy::jsClass, S_CCBezierBy::jsObject, NULL);
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

JSClass* S_CCEaseIn::jsClass = NULL;
JSObject* S_CCEaseIn::jsObject = NULL;

JSBool S_CCEaseIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseIn::jsClass, S_CCEaseIn::jsObject, NULL);
	S_CCEaseIn *cobj = new S_CCEaseIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseIn *cobj; JSGET_PTRSHELL(S_CCEaseIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseIn *cobj; JSGET_PTRSHELL(S_CCEaseIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseIn::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseRateAction::jsObject,jsClass,S_CCEaseIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseIn* self = NULL; JSGET_PTRSHELL(S_CCEaseIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseIn* ret = CCEaseIn::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseIn::jsClass, S_CCEaseIn::jsObject, NULL);
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

JSClass* S_CCFiniteTimeAction::jsClass = NULL;
JSObject* S_CCFiniteTimeAction::jsObject = NULL;

JSBool S_CCFiniteTimeAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
	S_CCFiniteTimeAction *cobj = new S_CCFiniteTimeAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFiniteTimeAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFiniteTimeAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFiniteTimeAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFiniteTimeAction *cobj; JSGET_PTRSHELL(S_CCFiniteTimeAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDuration:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getDuration(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFiniteTimeAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFiniteTimeAction *cobj; JSGET_PTRSHELL(S_CCFiniteTimeAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDuration:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setDuration(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFiniteTimeAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"duration", kDuration, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFiniteTimeAction::jsPropertyGet, S_CCFiniteTimeAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCFiniteTimeAction::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCAction::jsObject,jsClass,S_CCFiniteTimeAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFiniteTimeAction::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFiniteTimeAction* self = NULL; JSGET_PTRSHELL(S_CCFiniteTimeAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCFiniteTimeAction* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFiniteTimeAction::jsClass, S_CCFiniteTimeAction::jsObject, NULL);
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

JSClass* S_CCPageTurn3D::jsClass = NULL;
JSObject* S_CCPageTurn3D::jsObject = NULL;

JSBool S_CCPageTurn3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCPageTurn3D::jsClass, S_CCPageTurn3D::jsObject, NULL);
	S_CCPageTurn3D *cobj = new S_CCPageTurn3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCPageTurn3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCPageTurn3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCPageTurn3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPageTurn3D *cobj; JSGET_PTRSHELL(S_CCPageTurn3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCPageTurn3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCPageTurn3D *cobj; JSGET_PTRSHELL(S_CCPageTurn3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCPageTurn3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCPageTurn3D::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCPageTurn3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCPageTurn3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCPageTurn3D* self = NULL; JSGET_PTRSHELL(S_CCPageTurn3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCPageTurn3D::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCPageTurn3D* ret = CCPageTurn3D::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPageTurn3D::jsClass, S_CCPageTurn3D::jsObject, NULL);
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

JSClass* S_CCTransitionFadeTR::jsClass = NULL;
JSObject* S_CCTransitionFadeTR::jsObject = NULL;

JSBool S_CCTransitionFadeTR::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFadeTR::jsClass, S_CCTransitionFadeTR::jsObject, NULL);
	S_CCTransitionFadeTR *cobj = new S_CCTransitionFadeTR(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFadeTR::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFadeTR *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFadeTR::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeTR *cobj; JSGET_PTRSHELL(S_CCTransitionFadeTR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFadeTR::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFadeTR *cobj; JSGET_PTRSHELL(S_CCTransitionFadeTR, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFadeTR::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("actionWithSize", S_CCTransitionFadeTR::jsactionWithSize, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("easeActionWithAction", S_CCTransitionFadeTR::jseaseActionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFadeTR::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionFadeTR::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionFadeTR::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFadeTR* self = NULL; JSGET_PTRSHELL(S_CCTransitionFadeTR, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCActionInterval* ret = self->actionWithSize(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
void S_CCTransitionFadeTR::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFadeTR::onEnter();
}
JSBool S_CCTransitionFadeTR::jseaseActionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionFadeTR* self = NULL; JSGET_PTRSHELL(S_CCTransitionFadeTR, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionInterval* ret = self->easeActionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionFadeTR::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFadeTR* ret = CCTransitionFadeTR::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFadeTR::jsClass, S_CCTransitionFadeTR::jsObject, NULL);
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

JSClass* S_CCLens3D::jsClass = NULL;
JSObject* S_CCLens3D::jsObject = NULL;

JSBool S_CCLens3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLens3D::jsClass, S_CCLens3D::jsObject, NULL);
	S_CCLens3D *cobj = new S_CCLens3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLens3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLens3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLens3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLens3D *cobj; JSGET_PTRSHELL(S_CCLens3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPosition());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kLensEffect:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getLensEffect(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLens3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLens3D *cobj; JSGET_PTRSHELL(S_CCLens3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPosition(*tmp); }
		} while (0);
		break;
	case kLensEffect:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setLensEffect(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLens3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLens3D::jsPropertyGet, S_CCLens3D::jsPropertySet},
			{"radius", kRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLens3D::jsPropertyGet, S_CCLens3D::jsPropertySet},
			{"lensEffect", kLensEffect, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLens3D::jsPropertyGet, S_CCLens3D::jsPropertySet},
			{"inPixels", kInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLens3D::jsPropertyGet, S_CCLens3D::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLens3D::jsPropertyGet, S_CCLens3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithPosition", S_CCLens3D::jsinitWithPosition, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithPosition", S_CCLens3D::jsactionWithPosition, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCLens3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLens3D::jsinitWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLens3D* self = NULL; JSGET_PTRSHELL(S_CCLens3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		JSObject *arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "odod", &arg0, &arg1, &arg2, &arg3);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithPosition(*narg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLens3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLens3D* self = NULL; JSGET_PTRSHELL(S_CCLens3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLens3D::jsactionWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		JSObject *arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "odod", &arg0, &arg1, &arg2, &arg3);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCLens3D* ret = CCLens3D::actionWithPosition(*narg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLens3D::jsClass, S_CCLens3D::jsObject, NULL);
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

JSClass* S_CCRipple3D::jsClass = NULL;
JSObject* S_CCRipple3D::jsObject = NULL;

JSBool S_CCRipple3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRipple3D::jsClass, S_CCRipple3D::jsObject, NULL);
	S_CCRipple3D *cobj = new S_CCRipple3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRipple3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRipple3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRipple3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRipple3D *cobj; JSGET_PTRSHELL(S_CCRipple3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPosition());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRipple3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRipple3D *cobj; JSGET_PTRSHELL(S_CCRipple3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kPosition:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPosition(*tmp); }
		} while (0);
		break;
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRipple3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{"radius", kRadius, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{"waves", kWaves, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{"inPixels", kInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRipple3D::jsPropertyGet, S_CCRipple3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithPosition", S_CCRipple3D::jsinitWithPosition, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithPosition", S_CCRipple3D::jsactionWithPosition, 6, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCRipple3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRipple3D::jsinitWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRipple3D* self = NULL; JSGET_PTRSHELL(S_CCRipple3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 6) {
		JSObject *arg0;
		double arg1;
		int arg2;
		double arg3;
		JSObject *arg4;
		double arg5;
		JS_ConvertArguments(cx, 6, JS_ARGV(cx, vp), "odidod", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg4; JSGET_PTRSHELL(ccGridSize, narg4, arg4);
		bool ret = self->initWithPosition(*narg0, arg1, arg2, arg3, *narg4, arg5);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRipple3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRipple3D* self = NULL; JSGET_PTRSHELL(S_CCRipple3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRipple3D::jsactionWithPosition(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 6) {
		JSObject *arg0;
		double arg1;
		int arg2;
		double arg3;
		JSObject *arg4;
		double arg5;
		JS_ConvertArguments(cx, 6, JS_ARGV(cx, vp), "odidod", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		ccGridSize* narg4; JSGET_PTRSHELL(ccGridSize, narg4, arg4);
		CCRipple3D* ret = CCRipple3D::actionWithPosition(*narg0, arg1, arg2, arg3, *narg4, arg5);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRipple3D::jsClass, S_CCRipple3D::jsObject, NULL);
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

JSClass* S_CCApplication::jsClass = NULL;
JSObject* S_CCApplication::jsObject = NULL;

JSBool S_CCApplication::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCApplication::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCApplication *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCApplication::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCApplication *cobj; JSGET_PTRSHELL(S_CCApplication, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCApplication::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCApplication *cobj; JSGET_PTRSHELL(S_CCApplication, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCApplication::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("setAnimationInterval", S_CCApplication::jssetAnimationInterval, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("getCurrentLanguage", S_CCApplication::jsgetCurrentLanguage, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCApplication::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCApplication::jssetAnimationInterval(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCApplication* self = NULL; JSGET_PTRSHELL(S_CCApplication, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->setAnimationInterval(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCEaseOut::jsClass = NULL;
JSObject* S_CCEaseOut::jsObject = NULL;

JSBool S_CCEaseOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseOut::jsClass, S_CCEaseOut::jsObject, NULL);
	S_CCEaseOut *cobj = new S_CCEaseOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseOut *cobj; JSGET_PTRSHELL(S_CCEaseOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseOut *cobj; JSGET_PTRSHELL(S_CCEaseOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseOut::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseRateAction::jsObject,jsClass,S_CCEaseOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseOut* self = NULL; JSGET_PTRSHELL(S_CCEaseOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseOut* ret = CCEaseOut::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseOut::jsClass, S_CCEaseOut::jsObject, NULL);
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

JSClass* S_CCNode::jsClass = NULL;
JSObject* S_CCNode::jsObject = NULL;

JSBool S_CCNode::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
	S_CCNode *cobj = new S_CCNode(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCNode::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCNode *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCNode::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCNode *cobj; JSGET_PTRSHELL(S_CCNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kZOrder:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getZOrder(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kVertexZ:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getVertexZ(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRotation:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRotation(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kScaleX:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getScaleX(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kScaleY:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getScaleY(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kPosition:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPosition());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kSkewX:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSkewX(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kSkewY:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSkewY(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kIsVisible:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isVisible()));
		break;
	case kAnchorPoint:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getAnchorPoint());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kContentSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getContentSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsRunning:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isRunning()));
		break;
	case kParent:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getParent();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsIgnoreAnchorPointForPosition:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isIgnoreAnchorPointForPosition()));
		break;
	case kTag:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTag(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kUserData:
		
		break;
	case kScale:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getScale(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kPositionLua:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPositionLua());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kPositionX:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPositionX(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kPositionY:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getPositionY(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kChildrenCount:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getChildrenCount(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCNode::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCNode *cobj; JSGET_PTRSHELL(S_CCNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kVertexZ:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setVertexZ(tmp); } while (0);
		break;
	case kRotation:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRotation(tmp); } while (0);
		break;
	case kScaleX:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setScaleX(tmp); } while (0);
		break;
	case kScaleY:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setScaleY(tmp); } while (0);
		break;
	case kPosition:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPosition(*tmp); }
		} while (0);
		break;
	case kSkewX:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewX(tmp); } while (0);
		break;
	case kSkewY:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewY(tmp); } while (0);
		break;
	case kIsVisible:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setVisible(tmp); } while (0);
		break;
	case kAnchorPoint:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setAnchorPoint(*tmp); }
		} while (0);
		break;
	case kContentSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setContentSize(*tmp); }
		} while (0);
		break;
	case kParent:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setParent(tmp); }
		} while (0);
		break;
	case kIsIgnoreAnchorPointForPosition:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->ignoreAnchorPointForPosition(tmp); } while (0);
		break;
	case kTag:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setTag(tmp); } while (0);
		break;
	case kUserData:
		do {
			void* tmp; JSGET_PTRSHELL(void, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setUserData(tmp); }
		} while (0);
		break;
	case kScale:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setScale(tmp); } while (0);
		break;
	case kPositionX:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setPositionX(tmp); } while (0);
		break;
	case kPositionY:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setPositionY(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCNode::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"zOrder", kZOrder, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"vertexZ", kVertexZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"rotation", kRotation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scaleX", kScaleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scaleY", kScaleY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewX", kSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewY", kSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"children", kChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isVisible", kIsVisible, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"anchorPoint", kAnchorPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"contentSize", kContentSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isRunning", kIsRunning, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"parent", kParent, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isIgnoreAnchorPointForPosition", kIsIgnoreAnchorPointForPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"tag", kTag, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"userData", kUserData, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"transform", kTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"inverse", kInverse, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"transformGL", kTransformGL, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isTransformDirty", kIsTransformDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isInverseDirty", kIsInverseDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isTransformGLDirty", kIsTransformGLDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scriptHandler", kScriptHandler, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"scale", kScale, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"positionLua", kPositionLua, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"positionX", kPositionX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"positionY", kPositionY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"childrenCount", kChildrenCount, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("registerScriptHandler", S_CCNode::jsregisterScriptHandler, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unregisterScriptHandler", S_CCNode::jsunregisterScriptHandler, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addChild", S_CCNode::jsaddChild, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeFromParentAndCleanup", S_CCNode::jsremoveFromParentAndCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChild", S_CCNode::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChildByTag", S_CCNode::jsremoveChildByTag, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCNode::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reorderChild", S_CCNode::jsreorderChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("cleanup", S_CCNode::jscleanup, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCNode::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("visit", S_CCNode::jsvisit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transform", S_CCNode::jstransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("transformAncestors", S_CCNode::jstransformAncestors, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("boundingBox", S_CCNode::jsboundingBox, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("runAction", S_CCNode::jsrunAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopAllActions", S_CCNode::jsstopAllActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopAction", S_CCNode::jsstopAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopActionByTag", S_CCNode::jsstopActionByTag, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("numberOfRunningActions", S_CCNode::jsnumberOfRunningActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("scheduleUpdate", S_CCNode::jsscheduleUpdate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("scheduleUpdateWithPriority", S_CCNode::jsscheduleUpdateWithPriority, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unscheduleUpdate", S_CCNode::jsunscheduleUpdate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unscheduleAllSelectors", S_CCNode::jsunscheduleAllSelectors, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resumeSchedulerAndActions", S_CCNode::jsresumeSchedulerAndActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pauseSchedulerAndActions", S_CCNode::jspauseSchedulerAndActions, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToNodeSpace", S_CCNode::jsconvertToNodeSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToWorldSpace", S_CCNode::jsconvertToWorldSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToNodeSpaceAR", S_CCNode::jsconvertToNodeSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToWorldSpaceAR", S_CCNode::jsconvertToWorldSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertTouchToNodeSpace", S_CCNode::jsconvertTouchToNodeSpace, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertTouchToNodeSpaceAR", S_CCNode::jsconvertTouchToNodeSpaceAR, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCNode::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCNode::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCNode::onEnter();
}
void S_CCNode::onEnterTransitionDidFinish() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnterTransitionDidFinish", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCNode::onEnterTransitionDidFinish();
}
void S_CCNode::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCNode::onExit();
}
JSBool S_CCNode::jsregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->registerScriptHandler(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsunregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unregisterScriptHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsremoveFromParentAndCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->removeFromParentAndCleanup(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->removeChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsremoveChildByTag(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		int arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ib", &arg0, &arg1);
		self->removeChildByTag(arg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->removeAllChildrenWithCleanup(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->reorderChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jscleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->cleanup();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsvisit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->visit();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jstransform(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->transform();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jstransformAncestors(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->transformAncestors();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsboundingBox(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCRect* ret = new CCRect(self->boundingBox());
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
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
JSBool S_CCNode::jsrunAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		CCAction* ret = self->runAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAction::jsClass, S_CCAction::jsObject, NULL);
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
JSBool S_CCNode::jsstopAllActions(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stopAllActions();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsstopAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		self->stopAction(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsstopActionByTag(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->stopActionByTag(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsnumberOfRunningActions(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		unsigned int ret = self->numberOfRunningActions();
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->scheduleUpdate();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsscheduleUpdateWithPriority(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->scheduleUpdateWithPriority(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsunscheduleUpdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unscheduleUpdate();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsunscheduleAllSelectors(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unscheduleAllSelectors();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsresumeSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->resumeSchedulerAndActions();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jspauseSchedulerAndActions(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->pauseSchedulerAndActions();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsconvertToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToNodeSpace(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCNode::jsconvertToWorldSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToWorldSpace(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCNode::jsconvertToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToNodeSpaceAR(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCNode::jsconvertToWorldSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToWorldSpaceAR(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCNode::jsconvertTouchToNodeSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTouch* narg0; JSGET_PTRSHELL(CCTouch, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertTouchToNodeSpace(narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCNode::jsconvertTouchToNodeSpaceAR(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTouch* narg0; JSGET_PTRSHELL(CCTouch, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertTouchToNodeSpaceAR(narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
void S_CCNode::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCEaseExponentialIn::jsClass = NULL;
JSObject* S_CCEaseExponentialIn::jsObject = NULL;

JSBool S_CCEaseExponentialIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseExponentialIn::jsClass, S_CCEaseExponentialIn::jsObject, NULL);
	S_CCEaseExponentialIn *cobj = new S_CCEaseExponentialIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseExponentialIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseExponentialIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseExponentialIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialIn *cobj; JSGET_PTRSHELL(S_CCEaseExponentialIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseExponentialIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialIn *cobj; JSGET_PTRSHELL(S_CCEaseExponentialIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseExponentialIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseExponentialIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseExponentialIn::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseExponentialIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseExponentialIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseExponentialIn* self = NULL; JSGET_PTRSHELL(S_CCEaseExponentialIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseExponentialIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseExponentialIn* self = NULL; JSGET_PTRSHELL(S_CCEaseExponentialIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseExponentialIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseExponentialIn* ret = CCEaseExponentialIn::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseExponentialIn::jsClass, S_CCEaseExponentialIn::jsObject, NULL);
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

JSClass* S_CCFileUtils::jsClass = NULL;
JSObject* S_CCFileUtils::jsObject = NULL;

JSBool S_CCFileUtils::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFileUtils::jsClass, S_CCFileUtils::jsObject, NULL);
	S_CCFileUtils *cobj = new S_CCFileUtils(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFileUtils::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCFileUtils *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCFileUtils::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFileUtils *cobj; JSGET_PTRSHELL(S_CCFileUtils, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFileUtils::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFileUtils *cobj; JSGET_PTRSHELL(S_CCFileUtils, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFileUtils::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("getFileData", S_CCFileUtils::jsgetFileData, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("fullPathFromRelativePath", S_CCFileUtils::jsfullPathFromRelativePath, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("fullPathFromRelativeFile", S_CCFileUtils::jsfullPathFromRelativeFile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCFileUtils::jsConstructor,0,properties,funcs,NULL,st_funcs);
}


JSClass* S_CCFlipX3D::jsClass = NULL;
JSObject* S_CCFlipX3D::jsObject = NULL;

JSBool S_CCFlipX3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFlipX3D::jsClass, S_CCFlipX3D::jsObject, NULL);
	S_CCFlipX3D *cobj = new S_CCFlipX3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFlipX3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFlipX3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFlipX3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipX3D *cobj; JSGET_PTRSHELL(S_CCFlipX3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFlipX3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipX3D *cobj; JSGET_PTRSHELL(S_CCFlipX3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFlipX3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCFlipX3D::jsinitWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSize", S_CCFlipX3D::jsinitWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCFlipX3D::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCFlipX3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFlipX3D::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX3D* self = NULL; JSGET_PTRSHELL(S_CCFlipX3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		bool ret = self->initWithDuration(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipX3D::jsinitWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX3D* self = NULL; JSGET_PTRSHELL(S_CCFlipX3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		bool ret = self->initWithSize(*narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipX3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipX3D* self = NULL; JSGET_PTRSHELL(S_CCFlipX3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipX3D::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCFlipX3D* ret = CCFlipX3D::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFlipX3D::jsClass, S_CCFlipX3D::jsObject, NULL);
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

JSClass* S_CCEaseInOut::jsClass = NULL;
JSObject* S_CCEaseInOut::jsObject = NULL;

JSBool S_CCEaseInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseInOut::jsClass, S_CCEaseInOut::jsObject, NULL);
	S_CCEaseInOut *cobj = new S_CCEaseInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseInOut *cobj; JSGET_PTRSHELL(S_CCEaseInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseInOut *cobj; JSGET_PTRSHELL(S_CCEaseInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseInOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseInOut::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCEaseRateAction::jsObject,jsClass,S_CCEaseInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseInOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseInOut* ret = CCEaseInOut::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseInOut::jsClass, S_CCEaseInOut::jsObject, NULL);
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

JSClass* S_CCEaseExponentialOut::jsClass = NULL;
JSObject* S_CCEaseExponentialOut::jsObject = NULL;

JSBool S_CCEaseExponentialOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseExponentialOut::jsClass, S_CCEaseExponentialOut::jsObject, NULL);
	S_CCEaseExponentialOut *cobj = new S_CCEaseExponentialOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseExponentialOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseExponentialOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseExponentialOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialOut *cobj; JSGET_PTRSHELL(S_CCEaseExponentialOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseExponentialOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialOut *cobj; JSGET_PTRSHELL(S_CCEaseExponentialOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseExponentialOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseExponentialOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseExponentialOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseExponentialOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseExponentialOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseExponentialOut* self = NULL; JSGET_PTRSHELL(S_CCEaseExponentialOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseExponentialOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseExponentialOut* self = NULL; JSGET_PTRSHELL(S_CCEaseExponentialOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseExponentialOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseExponentialOut* ret = CCEaseExponentialOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseExponentialOut::jsClass, S_CCEaseExponentialOut::jsObject, NULL);
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

JSClass* S_CCJumpTo::jsClass = NULL;
JSObject* S_CCJumpTo::jsObject = NULL;

JSBool S_CCJumpTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCJumpTo::jsClass, S_CCJumpTo::jsObject, NULL);
	S_CCJumpTo *cobj = new S_CCJumpTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCJumpTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCJumpTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCJumpTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpTo *cobj; JSGET_PTRSHELL(S_CCJumpTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCJumpTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpTo *cobj; JSGET_PTRSHELL(S_CCJumpTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCJumpTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCJumpTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCJumpTo::jsactionWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCJumpBy::jsObject,jsClass,S_CCJumpTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCJumpTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpTo* self = NULL; JSGET_PTRSHELL(S_CCJumpTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		double arg0;
		JSObject *arg1;
		double arg2;
		int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dodi", &arg0, &arg1, &arg2, &arg3);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		CCJumpTo* ret = CCJumpTo::actionWithDuration(arg0, *narg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCJumpTo::jsClass, S_CCJumpTo::jsObject, NULL);
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

JSClass* S_CCTransitionPageTurn::jsClass = NULL;
JSObject* S_CCTransitionPageTurn::jsObject = NULL;

JSBool S_CCTransitionPageTurn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionPageTurn::jsClass, S_CCTransitionPageTurn::jsObject, NULL);
	S_CCTransitionPageTurn *cobj = new S_CCTransitionPageTurn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionPageTurn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionPageTurn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionPageTurn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionPageTurn *cobj; JSGET_PTRSHELL(S_CCTransitionPageTurn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionPageTurn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionPageTurn *cobj; JSGET_PTRSHELL(S_CCTransitionPageTurn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionPageTurn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"back", kBack, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionPageTurn::jsPropertyGet, S_CCTransitionPageTurn::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCTransitionPageTurn::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("actionWithSize", S_CCTransitionPageTurn::jsactionWithSize, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionPageTurn::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionPageTurn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionPageTurn::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		JSBool arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "dob", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionPageTurn* ret = CCTransitionPageTurn::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionPageTurn::jsClass, S_CCTransitionPageTurn::jsObject, NULL);
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
JSBool S_CCTransitionPageTurn::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionPageTurn* self = NULL; JSGET_PTRSHELL(S_CCTransitionPageTurn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		JSBool arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "dob", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		bool ret = self->initWithDuration(arg0, narg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionPageTurn::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionPageTurn* self = NULL; JSGET_PTRSHELL(S_CCTransitionPageTurn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCActionInterval* ret = self->actionWithSize(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
void S_CCTransitionPageTurn::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionPageTurn::onEnter();
}

JSClass* S_CCParticleSystemQuad::jsClass = NULL;
JSObject* S_CCParticleSystemQuad::jsObject = NULL;

JSBool S_CCParticleSystemQuad::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCParticleSystemQuad::jsClass, S_CCParticleSystemQuad::jsObject, NULL);
	S_CCParticleSystemQuad *cobj = new S_CCParticleSystemQuad(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCParticleSystemQuad::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCParticleSystemQuad *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCParticleSystemQuad::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystemQuad *cobj; JSGET_PTRSHELL(S_CCParticleSystemQuad, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCParticleSystemQuad::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystemQuad *cobj; JSGET_PTRSHELL(S_CCParticleSystemQuad, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCParticleSystemQuad::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"quads", kQuads, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystemQuad::jsPropertyGet, S_CCParticleSystemQuad::jsPropertySet},
			{"indices", kIndices, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystemQuad::jsPropertyGet, S_CCParticleSystemQuad::jsPropertySet},
			{"quadsID", kQuadsID, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystemQuad::jsPropertyGet, S_CCParticleSystemQuad::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("setupIndices", S_CCParticleSystemQuad::jssetupIndices, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initTexCoordsWithRect", S_CCParticleSystemQuad::jsinitTexCoordsWithRect, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTotalParticles", S_CCParticleSystemQuad::jsinitWithTotalParticles, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateQuadWithParticle", S_CCParticleSystemQuad::jsupdateQuadWithParticle, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("postStep", S_CCParticleSystemQuad::jspostStep, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCParticleSystemQuad::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("particleWithFile", S_CCParticleSystemQuad::jsparticleWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCParticleSystem::jsObject,jsClass,S_CCParticleSystemQuad::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCParticleSystemQuad::jsparticleWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCParticleSystemQuad* ret = CCParticleSystemQuad::particleWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCParticleSystemQuad::jsClass, S_CCParticleSystemQuad::jsObject, NULL);
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
JSBool S_CCParticleSystemQuad::jssetupIndices(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->setupIndices();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemQuad::jsinitTexCoordsWithRect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCRect* narg0; JSGET_PTRSHELL(CCRect, narg0, arg0);
		self->initTexCoordsWithRect(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemQuad::jsinitWithTotalParticles(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		bool ret = self->initWithTotalParticles(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemQuad::jsupdateQuadWithParticle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		tCCParticle* narg0; JSGET_PTRSHELL(tCCParticle, narg0, arg0);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		self->updateQuadWithParticle(narg0, *narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemQuad::jspostStep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->postStep();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemQuad::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCLabelTTF::jsClass = NULL;
JSObject* S_CCLabelTTF::jsObject = NULL;

JSBool S_CCLabelTTF::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLabelTTF::jsClass, S_CCLabelTTF::jsObject, NULL);
	S_CCLabelTTF *cobj = new S_CCLabelTTF(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLabelTTF::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLabelTTF *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLabelTTF::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelTTF *cobj; JSGET_PTRSHELL(S_CCLabelTTF, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLabelTTF::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelTTF *cobj; JSGET_PTRSHELL(S_CCLabelTTF, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLabelTTF::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"dimensions", kDimensions, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelTTF::jsPropertyGet, S_CCLabelTTF::jsPropertySet},
			{"eAlignment", kEAlignment, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelTTF::jsPropertyGet, S_CCLabelTTF::jsPropertySet},
			{"fontName", kFontName, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelTTF::jsPropertyGet, S_CCLabelTTF::jsPropertySet},
			{"fontSize", kFontSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelTTF::jsPropertyGet, S_CCLabelTTF::jsPropertySet},
			{"string", kString, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelTTF::jsPropertyGet, S_CCLabelTTF::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithString", S_CCLabelTTF::jsinitWithString, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("labelWithString", S_CCLabelTTF::jslabelWithString, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCSprite::jsObject,jsClass,S_CCLabelTTF::jsConstructor,0,properties,funcs,NULL,st_funcs);
}


JSClass* S_CCScene::jsClass = NULL;
JSObject* S_CCScene::jsObject = NULL;

JSBool S_CCScene::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCScene::jsClass, S_CCScene::jsObject, NULL);
	S_CCScene *cobj = new S_CCScene(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCScene::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCScene *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCScene::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScene *cobj; JSGET_PTRSHELL(S_CCScene, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCScene::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScene *cobj; JSGET_PTRSHELL(S_CCScene, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCScene::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCScene::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCScene::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCScene::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScene* self = NULL; JSGET_PTRSHELL(S_CCScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCScene::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCDirector::jsClass = NULL;
JSObject* S_CCDirector::jsObject = NULL;

JSBool S_CCDirector::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCDirector::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCDirector *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCDirector::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDirector *cobj; JSGET_PTRSHELL(S_CCDirector, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTotalFrames:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getTotalFrames(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kRunningScene:
		do {
			CCScene *scene = cobj->getRunningScene();
			if (scene) {
				JSObject *tmp = JS_NewObject(cx, S_CCScene::jsClass, S_CCScene::jsObject, NULL);
				pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
				pt->flags = kPointerTemporary;
				pt->data = (void *)scene;
				JS_SetPrivate(tmp, pt);
				JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
			} else {
				JS_SET_RVAL(cx, val, JSVAL_NULL);
			}
		} while (0);
		break;
	case kWinSizeInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getWinSizeInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kContentScaleFactor:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getContentScaleFactor(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kNotificationNode:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getNotificationNode();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kAnimationInterval:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAnimationInterval(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kProjection:
				// don't know what this is (c ~> js)
		break;
	case kWinSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getWinSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kZEye:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getZEye(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kDeviceOrientation:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCDirector::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDirector *cobj; JSGET_PTRSHELL(S_CCDirector, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDisplayStats:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDisplayStats(tmp); } while (0);
		break;
	case kNextDeltaTimeZero:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setNextDeltaTimeZero(tmp); } while (0);
		break;
	case kContentScaleFactor:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setContentScaleFactor(tmp); } while (0);
		break;
	case kNotificationNode:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setNotificationNode(tmp); }
		} while (0);
		break;
	case kAnimationInterval:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAnimationInterval(tmp); } while (0);
		break;
	case kProjection:
				// don't know what this is (js ~> c)
		break;
	case kDeviceOrientation:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCDirector::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"purgeDirecotorInNextLoop", kPurgeDirecotorInNextLoop, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"openGLView", kOpenGLView, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"interval", kInterval, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"landscape", kLandscape, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"displayStats", kDisplayStats, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"accumDt", kAccumDt, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"frameRate", kFrameRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"fPSLabel", kFPSLabel, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"paused", kPaused, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"totalFrames", kTotalFrames, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"frames", kFrames, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"runningScene", kRunningScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"nextScene", kNextScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"sendCleanupToScene", kSendCleanupToScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"scenesStack", kScenesStack, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"lastUpdate", kLastUpdate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"deltaTime", kDeltaTime, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"nextDeltaTimeZero", kNextDeltaTimeZero, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"eProjection", kEProjection, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"winSizeInPoints", kWinSizeInPoints, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"winSizeInPixels", kWinSizeInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"contentScaleFactor", kContentScaleFactor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"pszFPS", kPszFPS, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"notificationNode", kNotificationNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"projectionDelegate", kProjectionDelegate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"eDeviceOrientation", kEDeviceOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"isContentScaleSupported", kIsContentScaleSupported, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"retinaDisplay", kRetinaDisplay, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"animationInterval", kAnimationInterval, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"projection", kProjection, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"winSize", kWinSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"zEye", kZEye, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"deviceOrientation", kDeviceOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCDirector::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDisplayStats", S_CCDirector::jsisDisplayStats, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isNextDeltaTimeZero", S_CCDirector::jsisNextDeltaTimeZero, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isPaused", S_CCDirector::jsisPaused, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isSendCleanupToScene", S_CCDirector::jsisSendCleanupToScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reshapeProjection", S_CCDirector::jsreshapeProjection, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToGL", S_CCDirector::jsconvertToGL, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("convertToUI", S_CCDirector::jsconvertToUI, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("runWithScene", S_CCDirector::jsrunWithScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pushScene", S_CCDirector::jspushScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("popScene", S_CCDirector::jspopScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("replaceScene", S_CCDirector::jsreplaceScene, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("endToLua", S_CCDirector::jsendToLua, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("end", S_CCDirector::jsend, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("pause", S_CCDirector::jspause, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("resume", S_CCDirector::jsresume, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stopAnimation", S_CCDirector::jsstopAnimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startAnimation", S_CCDirector::jsstartAnimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("drawScene", S_CCDirector::jsdrawScene, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeCachedData", S_CCDirector::jspurgeCachedData, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("mainLoop", S_CCDirector::jsmainLoop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("enableRetinaDisplay", S_CCDirector::jsenableRetinaDisplay, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedDirector", S_CCDirector::jssharedDirector, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCDirector::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCDirector::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisDisplayStats(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDisplayStats();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisNextDeltaTimeZero(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isNextDeltaTimeZero();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisPaused(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isPaused();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisSendCleanupToScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isSendCleanupToScene();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsreshapeProjection(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSize* narg0; JSGET_PTRSHELL(CCSize, narg0, arg0);
		self->reshapeProjection(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsconvertToGL(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToGL(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCDirector::jsconvertToUI(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->convertToUI(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCDirector::jsrunWithScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
		self->runWithScene(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jspushScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
		self->pushScene(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jspopScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->popScene();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsreplaceScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCScene* narg0; JSGET_PTRSHELL(CCScene, narg0, arg0);
		self->replaceScene(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsendToLua(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->endToLua();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsend(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->end();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jspause(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->pause();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsresume(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->resume();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsstopAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stopAnimation();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsstartAnimation(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->startAnimation();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsdrawScene(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->drawScene();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jspurgeCachedData(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->purgeCachedData();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsmainLoop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->mainLoop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsenableRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		bool ret = self->enableRetinaDisplay(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jssharedDirector(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCDirector* ret = CCDirector::sharedDirector();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCDirector::jsClass, S_CCDirector::jsObject, NULL);
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

JSClass* S_CCFlipY3D::jsClass = NULL;
JSObject* S_CCFlipY3D::jsObject = NULL;

JSBool S_CCFlipY3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFlipY3D::jsClass, S_CCFlipY3D::jsObject, NULL);
	S_CCFlipY3D *cobj = new S_CCFlipY3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFlipY3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFlipY3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFlipY3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipY3D *cobj; JSGET_PTRSHELL(S_CCFlipY3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFlipY3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFlipY3D *cobj; JSGET_PTRSHELL(S_CCFlipY3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFlipY3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCFlipY3D::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFlipX3D::jsObject,jsClass,S_CCFlipY3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFlipY3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFlipY3D* self = NULL; JSGET_PTRSHELL(S_CCFlipY3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFlipY3D::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCFlipY3D* ret = CCFlipY3D::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFlipY3D::jsClass, S_CCFlipY3D::jsObject, NULL);
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

JSClass* S_CCLiquid::jsClass = NULL;
JSObject* S_CCLiquid::jsObject = NULL;

JSBool S_CCLiquid::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLiquid::jsClass, S_CCLiquid::jsObject, NULL);
	S_CCLiquid *cobj = new S_CCLiquid(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLiquid::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLiquid *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLiquid::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLiquid *cobj; JSGET_PTRSHELL(S_CCLiquid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLiquid::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLiquid *cobj; JSGET_PTRSHELL(S_CCLiquid, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLiquid::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"waves", kWaves, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLiquid::jsPropertyGet, S_CCLiquid::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLiquid::jsPropertyGet, S_CCLiquid::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLiquid::jsPropertyGet, S_CCLiquid::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithWaves", S_CCLiquid::jsinitWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithWaves", S_CCLiquid::jsactionWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCLiquid::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLiquid::jsinitWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLiquid* self = NULL; JSGET_PTRSHELL(S_CCLiquid, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithWaves(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLiquid::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLiquid* self = NULL; JSGET_PTRSHELL(S_CCLiquid, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLiquid::jsactionWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCLiquid* ret = CCLiquid::actionWithWaves(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLiquid::jsClass, S_CCLiquid::jsObject, NULL);
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

JSClass* S_CCEaseExponentialInOut::jsClass = NULL;
JSObject* S_CCEaseExponentialInOut::jsObject = NULL;

JSBool S_CCEaseExponentialInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseExponentialInOut::jsClass, S_CCEaseExponentialInOut::jsObject, NULL);
	S_CCEaseExponentialInOut *cobj = new S_CCEaseExponentialInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseExponentialInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseExponentialInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseExponentialInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialInOut *cobj; JSGET_PTRSHELL(S_CCEaseExponentialInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseExponentialInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseExponentialInOut *cobj; JSGET_PTRSHELL(S_CCEaseExponentialInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseExponentialInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseExponentialInOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseExponentialInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseExponentialInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseExponentialInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseExponentialInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseExponentialInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseExponentialInOut* ret = CCEaseExponentialInOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseExponentialInOut::jsClass, S_CCEaseExponentialInOut::jsObject, NULL);
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

JSClass* S_CCTiledGrid3DAction::jsClass = NULL;
JSObject* S_CCTiledGrid3DAction::jsObject = NULL;

JSBool S_CCTiledGrid3DAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTiledGrid3DAction::jsClass, S_CCTiledGrid3DAction::jsObject, NULL);
	S_CCTiledGrid3DAction *cobj = new S_CCTiledGrid3DAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTiledGrid3DAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTiledGrid3DAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTiledGrid3DAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTiledGrid3DAction *cobj; JSGET_PTRSHELL(S_CCTiledGrid3DAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTiledGrid3DAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTiledGrid3DAction *cobj; JSGET_PTRSHELL(S_CCTiledGrid3DAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTiledGrid3DAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTiledGrid3DAction::jsPropertyGet, S_CCTiledGrid3DAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("tile", S_CCTiledGrid3DAction::jstile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("originalTile", S_CCTiledGrid3DAction::jsoriginalTile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGridAction::jsObject,jsClass,S_CCTiledGrid3DAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTiledGrid3DAction::jstile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTiledGrid3DAction* self = NULL; JSGET_PTRSHELL(S_CCTiledGrid3DAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		//INVALID RETURN TYPE _51F
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTiledGrid3DAction::jsoriginalTile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTiledGrid3DAction* self = NULL; JSGET_PTRSHELL(S_CCTiledGrid3DAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		//INVALID RETURN TYPE _51F
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

/*
JSClass* S_CCParticleSystemPoint::jsClass = NULL;
JSObject* S_CCParticleSystemPoint::jsObject = NULL;

JSBool S_CCParticleSystemPoint::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCParticleSystemPoint::jsClass, S_CCParticleSystemPoint::jsObject, NULL);
	S_CCParticleSystemPoint *cobj = new S_CCParticleSystemPoint(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCParticleSystemPoint::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCParticleSystemPoint *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCParticleSystemPoint::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystemPoint *cobj; JSGET_PTRSHELL(S_CCParticleSystemPoint, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCParticleSystemPoint::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCParticleSystemPoint *cobj; JSGET_PTRSHELL(S_CCParticleSystemPoint, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCParticleSystemPoint::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"vertices", kVertices, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystemPoint::jsPropertyGet, S_CCParticleSystemPoint::jsPropertySet},
			{"verticesID", kVerticesID, JSPROP_PERMANENT | JSPROP_SHARED, S_CCParticleSystemPoint::jsPropertyGet, S_CCParticleSystemPoint::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTotalParticles", S_CCParticleSystemPoint::jsinitWithTotalParticles, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateQuadWithParticle", S_CCParticleSystemPoint::jsupdateQuadWithParticle, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("postStep", S_CCParticleSystemPoint::jspostStep, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCParticleSystemPoint::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("particleWithFile", S_CCParticleSystemPoint::jsparticleWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCParticleSystem::jsObject,jsClass,S_CCParticleSystemPoint::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCParticleSystemPoint::jsparticleWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCParticleSystemPoint* ret = CCParticleSystemPoint::particleWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCParticleSystemPoint::jsClass, S_CCParticleSystemPoint::jsObject, NULL);
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
JSBool S_CCParticleSystemPoint::jsinitWithTotalParticles(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemPoint* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemPoint, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		unsigned int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		bool ret = self->initWithTotalParticles(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemPoint::jsupdateQuadWithParticle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemPoint* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemPoint, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		tCCParticle* narg0; JSGET_PTRSHELL(tCCParticle, narg0, arg0);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		self->updateQuadWithParticle(narg0, *narg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemPoint::jspostStep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemPoint* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemPoint, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->postStep();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystemPoint::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemPoint* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemPoint, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
*/

JSClass* S_CCJumpBy::jsClass = NULL;
JSObject* S_CCJumpBy::jsObject = NULL;

JSBool S_CCJumpBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCJumpBy::jsClass, S_CCJumpBy::jsObject, NULL);
	S_CCJumpBy *cobj = new S_CCJumpBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCJumpBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCJumpBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCJumpBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpBy *cobj; JSGET_PTRSHELL(S_CCJumpBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCJumpBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpBy *cobj; JSGET_PTRSHELL(S_CCJumpBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCJumpBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"position", kPosition, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpBy::jsPropertyGet, S_CCJumpBy::jsPropertySet},
			{"delta", kDelta, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpBy::jsPropertyGet, S_CCJumpBy::jsPropertySet},
			{"height", kHeight, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpBy::jsPropertyGet, S_CCJumpBy::jsPropertySet},
			{"jumps", kJumps, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpBy::jsPropertyGet, S_CCJumpBy::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCJumpBy::jsinitWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCJumpBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCJumpBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCJumpBy::jsactionWithDuration, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCJumpBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCJumpBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpBy* self = NULL; JSGET_PTRSHELL(S_CCJumpBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		double arg0;
		JSObject *arg1;
		double arg2;
		unsigned int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dodi", &arg0, &arg1, &arg2, &arg3);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		bool ret = self->initWithDuration(arg0, *narg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpBy* self = NULL; JSGET_PTRSHELL(S_CCJumpBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpBy::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpBy* self = NULL; JSGET_PTRSHELL(S_CCJumpBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpBy* self = NULL; JSGET_PTRSHELL(S_CCJumpBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCJumpBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		double arg0;
		JSObject *arg1;
		double arg2;
		unsigned int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dodi", &arg0, &arg1, &arg2, &arg3);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		CCJumpBy* ret = CCJumpBy::actionWithDuration(arg0, *narg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCJumpBy::jsClass, S_CCJumpBy::jsObject, NULL);
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

JSClass* S_CCFollow::jsClass = NULL;
JSObject* S_CCFollow::jsObject = NULL;

JSBool S_CCFollow::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFollow::jsClass, S_CCFollow::jsObject, NULL);
	S_CCFollow *cobj = new S_CCFollow(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFollow::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFollow *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFollow::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFollow *cobj; JSGET_PTRSHELL(S_CCFollow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFollow::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFollow *cobj; JSGET_PTRSHELL(S_CCFollow, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFollow::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"followedNode", kFollowedNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"boundarySet", kBoundarySet, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"boundaryFullyCovered", kBoundaryFullyCovered, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"halfScreenSize", kHalfScreenSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"fullScreenSize", kFullScreenSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"leftBoundary", kLeftBoundary, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"rightBoundary", kRightBoundary, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"topBoundary", kTopBoundary, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{"bottomBoundary", kBottomBoundary, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFollow::jsPropertyGet, S_CCFollow::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("isBoundarySet", S_CCFollow::jsisBoundarySet, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTarget", S_CCFollow::jsinitWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDone", S_CCFollow::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCFollow::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithTarget", S_CCFollow::jsactionWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCAction::jsObject,jsClass,S_CCFollow::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFollow::jsisBoundarySet(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFollow* self = NULL; JSGET_PTRSHELL(S_CCFollow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isBoundarySet();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFollow::jsinitWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFollow* self = NULL; JSGET_PTRSHELL(S_CCFollow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		bool ret = self->initWithTarget(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFollow::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFollow* self = NULL; JSGET_PTRSHELL(S_CCFollow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFollow::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFollow* self = NULL; JSGET_PTRSHELL(S_CCFollow, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFollow::jsactionWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCFollow* ret = CCFollow::actionWithTarget(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFollow::jsClass, S_CCFollow::jsObject, NULL);
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

JSClass* S_CCSkewBy::jsClass = NULL;
JSObject* S_CCSkewBy::jsObject = NULL;

JSBool S_CCSkewBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSkewBy::jsClass, S_CCSkewBy::jsObject, NULL);
	S_CCSkewBy *cobj = new S_CCSkewBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSkewBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSkewBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSkewBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSkewBy *cobj; JSGET_PTRSHELL(S_CCSkewBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSkewBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSkewBy *cobj; JSGET_PTRSHELL(S_CCSkewBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSkewBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCSkewBy::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSkewBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCSkewBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCSkewBy::jsactionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCSkewTo::jsObject,jsClass,S_CCSkewBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSkewBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewBy* self = NULL; JSGET_PTRSHELL(S_CCSkewBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		bool ret = self->initWithDuration(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSkewBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewBy* self = NULL; JSGET_PTRSHELL(S_CCSkewBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSkewBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewBy* self = NULL; JSGET_PTRSHELL(S_CCSkewBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCSkewBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		CCSkewBy* ret = CCSkewBy::actionWithDuration(arg0, arg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSkewBy::jsClass, S_CCSkewBy::jsObject, NULL);
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

JSClass* S_CCAccelDeccelAmplitude::jsClass = NULL;
JSObject* S_CCAccelDeccelAmplitude::jsObject = NULL;

JSBool S_CCAccelDeccelAmplitude::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAccelDeccelAmplitude::jsClass, S_CCAccelDeccelAmplitude::jsObject, NULL);
	S_CCAccelDeccelAmplitude *cobj = new S_CCAccelDeccelAmplitude(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAccelDeccelAmplitude::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAccelDeccelAmplitude *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAccelDeccelAmplitude::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAccelDeccelAmplitude *cobj; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAccelDeccelAmplitude::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAccelDeccelAmplitude *cobj; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAccelDeccelAmplitude::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rate", kRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAccelDeccelAmplitude::jsPropertyGet, S_CCAccelDeccelAmplitude::jsPropertySet},
			{"other", kOther, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAccelDeccelAmplitude::jsPropertyGet, S_CCAccelDeccelAmplitude::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCAccelDeccelAmplitude::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCAccelDeccelAmplitude::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCAccelDeccelAmplitude::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCAccelDeccelAmplitude::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCAccelDeccelAmplitude::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAccelDeccelAmplitude::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelDeccelAmplitude::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelDeccelAmplitude::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelDeccelAmplitude::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelDeccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelDeccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCAccelDeccelAmplitude::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		CCAccelDeccelAmplitude* ret = CCAccelDeccelAmplitude::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAccelDeccelAmplitude::jsClass, S_CCAccelDeccelAmplitude::jsObject, NULL);
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

JSClass* S_CCEaseSineIn::jsClass = NULL;
JSObject* S_CCEaseSineIn::jsObject = NULL;

JSBool S_CCEaseSineIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseSineIn::jsClass, S_CCEaseSineIn::jsObject, NULL);
	S_CCEaseSineIn *cobj = new S_CCEaseSineIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseSineIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseSineIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseSineIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineIn *cobj; JSGET_PTRSHELL(S_CCEaseSineIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseSineIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineIn *cobj; JSGET_PTRSHELL(S_CCEaseSineIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseSineIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseSineIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseSineIn::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseSineIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseSineIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseSineIn* self = NULL; JSGET_PTRSHELL(S_CCEaseSineIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseSineIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseSineIn* self = NULL; JSGET_PTRSHELL(S_CCEaseSineIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseSineIn::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseSineIn* ret = CCEaseSineIn::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseSineIn::jsClass, S_CCEaseSineIn::jsObject, NULL);
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

JSClass* S_CCLabelAtlas::jsClass = NULL;
JSObject* S_CCLabelAtlas::jsObject = NULL;

JSBool S_CCLabelAtlas::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCLabelAtlas::jsClass, S_CCLabelAtlas::jsObject, NULL);
	S_CCLabelAtlas *cobj = new S_CCLabelAtlas(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCLabelAtlas::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCLabelAtlas *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCLabelAtlas::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelAtlas *cobj; JSGET_PTRSHELL(S_CCLabelAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kString:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCLabelAtlas::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCLabelAtlas *cobj; JSGET_PTRSHELL(S_CCLabelAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kString:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCLabelAtlas::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"string", kString, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelAtlas::jsPropertyGet, S_CCLabelAtlas::jsPropertySet},
			{"startChar", kStartChar, JSPROP_PERMANENT | JSPROP_SHARED, S_CCLabelAtlas::jsPropertyGet, S_CCLabelAtlas::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithString", S_CCLabelAtlas::jsinitWithString, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateAtlasValues", S_CCLabelAtlas::jsupdateAtlasValues, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("labelWithString", S_CCLabelAtlas::jslabelWithString, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCAtlasNode::jsObject,jsClass,S_CCLabelAtlas::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCLabelAtlas::jslabelWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 5) {
		JSString *arg0;
		JSString *arg1;
		unsigned int arg2;
		unsigned int arg3;
		unsigned char arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SSiic", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCLabelAtlas* ret = CCLabelAtlas::labelWithString(narg0, narg1, arg2, arg3, arg4);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCLabelAtlas::jsClass, S_CCLabelAtlas::jsObject, NULL);
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
JSBool S_CCLabelAtlas::jsinitWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelAtlas* self = NULL; JSGET_PTRSHELL(S_CCLabelAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSString *arg0;
		JSString *arg1;
		unsigned int arg2;
		unsigned int arg3;
		unsigned char arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SSiic", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		bool ret = self->initWithString(narg0, narg1, arg2, arg3, arg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLabelAtlas::jsupdateAtlasValues(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelAtlas* self = NULL; JSGET_PTRSHELL(S_CCLabelAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->updateAtlasValues();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCMenuItem::jsClass = NULL;
JSObject* S_CCMenuItem::jsObject = NULL;

JSBool S_CCMenuItem::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMenuItem::jsClass, S_CCMenuItem::jsObject, NULL);
	S_CCMenuItem *cobj = new S_CCMenuItem(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMenuItem::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenuItem *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMenuItem::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItem *cobj; JSGET_PTRSHELL(S_CCMenuItem, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kIsSelected:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isSelected()));
		break;
	case kIsEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isEnabled()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMenuItem::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItem *cobj; JSGET_PTRSHELL(S_CCMenuItem, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kIsEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setEnabled(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMenuItem::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"isSelected", kIsSelected, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItem::jsPropertyGet, S_CCMenuItem::jsPropertySet},
			{"isEnabled", kIsEnabled, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItem::jsPropertyGet, S_CCMenuItem::jsPropertySet},
			{"listener", kListener, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItem::jsPropertyGet, S_CCMenuItem::jsPropertySet},
			{"selector", kSelector, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItem::jsPropertyGet, S_CCMenuItem::jsPropertySet},
			{"scriptHandler", kScriptHandler, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItem::jsPropertyGet, S_CCMenuItem::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCMenuItem::jsinit, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("rect", S_CCMenuItem::jsrect, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("activate", S_CCMenuItem::jsactivate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("selected", S_CCMenuItem::jsselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unselected", S_CCMenuItem::jsunselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("registerScriptHandler", S_CCMenuItem::jsregisterScriptHandler, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unregisterScriptHandler", S_CCMenuItem::jsunregisterScriptHandler, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCMenuItem::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItem::jsrect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCRect* ret = new CCRect(self->rect());
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRect::jsClass, S_CCRect::jsObject, NULL);
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
JSBool S_CCMenuItem::jsactivate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->activate();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->selected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsunselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unselected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		int arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "i", &arg0);
		self->registerScriptHandler(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsunregisterScriptHandler(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unregisterScriptHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCMenuItem::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}
MENU_ITEM_ACTION(S_CCMenuItem)

JSClass* S_CCMoveBy::jsClass = NULL;
JSObject* S_CCMoveBy::jsObject = NULL;

JSBool S_CCMoveBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMoveBy::jsClass, S_CCMoveBy::jsObject, NULL);
	S_CCMoveBy *cobj = new S_CCMoveBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMoveBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMoveBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMoveBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMoveBy *cobj; JSGET_PTRSHELL(S_CCMoveBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMoveBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMoveBy *cobj; JSGET_PTRSHELL(S_CCMoveBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMoveBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCMoveBy::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCMoveBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCMoveBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCMoveBy::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMoveTo::jsObject,jsClass,S_CCMoveBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMoveBy::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveBy* self = NULL; JSGET_PTRSHELL(S_CCMoveBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		bool ret = self->initWithDuration(arg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMoveBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveBy* self = NULL; JSGET_PTRSHELL(S_CCMoveBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMoveBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMoveBy* self = NULL; JSGET_PTRSHELL(S_CCMoveBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCMoveBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCPoint* narg1; JSGET_PTRSHELL(CCPoint, narg1, arg1);
		CCMoveBy* ret = CCMoveBy::actionWithDuration(arg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCMoveBy::jsClass, S_CCMoveBy::jsObject, NULL);
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

JSClass* S_CCEaseSineOut::jsClass = NULL;
JSObject* S_CCEaseSineOut::jsObject = NULL;

JSBool S_CCEaseSineOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseSineOut::jsClass, S_CCEaseSineOut::jsObject, NULL);
	S_CCEaseSineOut *cobj = new S_CCEaseSineOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseSineOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseSineOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseSineOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineOut *cobj; JSGET_PTRSHELL(S_CCEaseSineOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseSineOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineOut *cobj; JSGET_PTRSHELL(S_CCEaseSineOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseSineOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCEaseSineOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseSineOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseSineOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseSineOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseSineOut* self = NULL; JSGET_PTRSHELL(S_CCEaseSineOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseSineOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseSineOut* self = NULL; JSGET_PTRSHELL(S_CCEaseSineOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseSineOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseSineOut* ret = CCEaseSineOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseSineOut::jsClass, S_CCEaseSineOut::jsObject, NULL);
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

JSClass* S_CCTMXTiledMap::jsClass = NULL;
JSObject* S_CCTMXTiledMap::jsObject = NULL;

JSBool S_CCTMXTiledMap::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTMXTiledMap::jsClass, S_CCTMXTiledMap::jsObject, NULL);
	S_CCTMXTiledMap *cobj = new S_CCTMXTiledMap(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTMXTiledMap::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTMXTiledMap *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTMXTiledMap::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTMXTiledMap *cobj; JSGET_PTRSHELL(S_CCTMXTiledMap, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kMapSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getMapSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kTileSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getTileSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kMapOrientation:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getMapOrientation(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kProperties:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getProperties();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTMXTiledMap::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTMXTiledMap *cobj; JSGET_PTRSHELL(S_CCTMXTiledMap, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kMapSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setMapSize(*tmp); }
		} while (0);
		break;
	case kTileSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTileSize(*tmp); }
		} while (0);
		break;
	case kMapOrientation:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setMapOrientation(tmp); } while (0);
		break;
	case kProperties:
		do {
			CCDictionary* tmp; JSGET_PTRSHELL(CCDictionary, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setProperties(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTMXTiledMap::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"mapSize", kMapSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"tileSize", kTileSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"mapOrientation", kMapOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"objectGroups", kObjectGroups, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"properties", kProperties, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"tileProperties", kTileProperties, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{"tMXLayers", kTMXLayers, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXTiledMap::jsPropertyGet, S_CCTMXTiledMap::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTMXFile", S_CCTMXTiledMap::jsinitWithTMXFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("layerNamed", S_CCTMXTiledMap::jslayerNamed, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("tiledMapWithTMXFile", S_CCTMXTiledMap::jstiledMapWithTMXFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCTMXTiledMap::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTMXTiledMap::jstiledMapWithTMXFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTMXTiledMap* ret = CCTMXTiledMap::tiledMapWithTMXFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTMXTiledMap::jsClass, S_CCTMXTiledMap::jsObject, NULL);
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
JSBool S_CCTMXTiledMap::jsinitWithTMXFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXTiledMap* self = NULL; JSGET_PTRSHELL(S_CCTMXTiledMap, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithTMXFile(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTMXTiledMap::jslayerNamed(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXTiledMap* self = NULL; JSGET_PTRSHELL(S_CCTMXTiledMap, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTMXLayer* ret = self->layerNamed(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTMXLayer::jsClass, S_CCTMXLayer::jsObject, NULL);
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
void S_CCTMXTiledMap::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCAccelAmplitude::jsClass = NULL;
JSObject* S_CCAccelAmplitude::jsObject = NULL;

JSBool S_CCAccelAmplitude::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCAccelAmplitude::jsClass, S_CCAccelAmplitude::jsObject, NULL);
	S_CCAccelAmplitude *cobj = new S_CCAccelAmplitude(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCAccelAmplitude::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCAccelAmplitude *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCAccelAmplitude::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAccelAmplitude *cobj; JSGET_PTRSHELL(S_CCAccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCAccelAmplitude::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAccelAmplitude *cobj; JSGET_PTRSHELL(S_CCAccelAmplitude, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCAccelAmplitude::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rate", kRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAccelAmplitude::jsPropertyGet, S_CCAccelAmplitude::jsPropertySet},
			{"other", kOther, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAccelAmplitude::jsPropertyGet, S_CCAccelAmplitude::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCAccelAmplitude::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCAccelAmplitude::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCAccelAmplitude::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCAccelAmplitude::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCAccelAmplitude::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAccelAmplitude::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelAmplitude::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelAmplitude::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAccelAmplitude::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAccelAmplitude* self = NULL; JSGET_PTRSHELL(S_CCAccelAmplitude, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCAccelAmplitude::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCAction* narg0; JSGET_PTRSHELL(CCAction, narg0, arg0);
		CCAccelAmplitude* ret = CCAccelAmplitude::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCAccelAmplitude::jsClass, S_CCAccelAmplitude::jsObject, NULL);
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

JSClass* S_CCTMXLayer::jsClass = NULL;
JSObject* S_CCTMXLayer::jsObject = NULL;

JSBool S_CCTMXLayer::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTMXLayer::jsClass, S_CCTMXLayer::jsObject, NULL);
	S_CCTMXLayer *cobj = new S_CCTMXLayer(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTMXLayer::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTMXLayer *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTMXLayer::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTMXLayer *cobj; JSGET_PTRSHELL(S_CCTMXLayer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kLayerSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getLayerSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kMapTileSize:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getMapTileSize());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kLayerOrientation:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getLayerOrientation(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kLayerName:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTMXLayer::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTMXLayer *cobj; JSGET_PTRSHELL(S_CCTMXLayer, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kLayerSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setLayerSize(*tmp); }
		} while (0);
		break;
	case kMapTileSize:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setMapTileSize(*tmp); }
		} while (0);
		break;
	case kTiles:
		do {
			unsigned int* tmp; JSGET_PTRSHELL(unsigned int, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTiles(tmp); }
		} while (0);
		break;
	case kTileSet:
		do {
			CCTMXTilesetInfo* tmp; JSGET_PTRSHELL(CCTMXTilesetInfo, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTileSet(tmp); }
		} while (0);
		break;
	case kLayerOrientation:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setLayerOrientation(tmp); } while (0);
		break;
	case kProperties:
		do {
			CCDictionary* tmp; JSGET_PTRSHELL(CCDictionary, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setProperties(tmp); }
		} while (0);
		break;
	case kLayerName:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTMXLayer::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"layerSize", kLayerSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"mapTileSize", kMapTileSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"tiles", kTiles, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"tileSet", kTileSet, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"layerOrientation", kLayerOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"properties", kProperties, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"layerName", kLayerName, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"cOpacity", kCOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"minGID", kMinGID, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"maxGID", kMaxGID, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"vertexZvalue", kVertexZvalue, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"useAutomaticVertexZ", kUseAutomaticVertexZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"alphaFuncValue", kAlphaFuncValue, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"reusedTile", kReusedTile, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"atlasIndexArray", kAtlasIndexArray, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{"contentScaleFactor", kContentScaleFactor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTMXLayer::jsPropertyGet, S_CCTMXLayer::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("tileAt", S_CCTMXLayer::jstileAt, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("tileGIDAt", S_CCTMXLayer::jstileGIDAt, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeTileAt", S_CCTMXLayer::jsremoveTileAt, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("positionAt", S_CCTMXLayer::jspositionAt, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCSpriteBatchNode::jsObject,jsClass,S_CCTMXLayer::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTMXLayer::jstileAt(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXLayer* self = NULL; JSGET_PTRSHELL(S_CCTMXLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCSprite* ret = self->tileAt(*narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
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
JSBool S_CCTMXLayer::jstileGIDAt(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXLayer* self = NULL; JSGET_PTRSHELL(S_CCTMXLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		unsigned int ret = self->tileGIDAt(*narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTMXLayer::jsremoveTileAt(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXLayer* self = NULL; JSGET_PTRSHELL(S_CCTMXLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		self->removeTileAt(*narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTMXLayer::jspositionAt(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTMXLayer* self = NULL; JSGET_PTRSHELL(S_CCTMXLayer, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCPoint* narg0; JSGET_PTRSHELL(CCPoint, narg0, arg0);
		CCPoint* ret = new CCPoint(self->positionAt(*narg0));
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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

JSClass* S_CCSkewTo::jsClass = NULL;
JSObject* S_CCSkewTo::jsObject = NULL;

JSBool S_CCSkewTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSkewTo::jsClass, S_CCSkewTo::jsObject, NULL);
	S_CCSkewTo *cobj = new S_CCSkewTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSkewTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSkewTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSkewTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSkewTo *cobj; JSGET_PTRSHELL(S_CCSkewTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSkewTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSkewTo *cobj; JSGET_PTRSHELL(S_CCSkewTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSkewTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"skewX", kSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"skewY", kSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"startSkewX", kStartSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"startSkewY", kStartSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"endSkewX", kEndSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"endSkewY", kEndSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"deltaX", kDeltaX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{"deltaY", kDeltaY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSkewTo::jsPropertyGet, S_CCSkewTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCSkewTo::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSkewTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCSkewTo::jsactionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCSkewTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSkewTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewTo* self = NULL; JSGET_PTRSHELL(S_CCSkewTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		bool ret = self->initWithDuration(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSkewTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewTo* self = NULL; JSGET_PTRSHELL(S_CCSkewTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSkewTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSkewTo* self = NULL; JSGET_PTRSHELL(S_CCSkewTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSkewTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		double arg1;
		double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ddd", &arg0, &arg1, &arg2);
		CCSkewTo* ret = CCSkewTo::actionWithDuration(arg0, arg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSkewTo::jsClass, S_CCSkewTo::jsObject, NULL);
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

JSClass* S_CCShaky3D::jsClass = NULL;
JSObject* S_CCShaky3D::jsObject = NULL;

JSBool S_CCShaky3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCShaky3D::jsClass, S_CCShaky3D::jsObject, NULL);
	S_CCShaky3D *cobj = new S_CCShaky3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCShaky3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCShaky3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCShaky3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShaky3D *cobj; JSGET_PTRSHELL(S_CCShaky3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCShaky3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCShaky3D *cobj; JSGET_PTRSHELL(S_CCShaky3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCShaky3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"randrange", kRandrange, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShaky3D::jsPropertyGet, S_CCShaky3D::jsPropertySet},
			{"shakeZ", kShakeZ, JSPROP_PERMANENT | JSPROP_SHARED, S_CCShaky3D::jsPropertyGet, S_CCShaky3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithRange", S_CCShaky3D::jsinitWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithRange", S_CCShaky3D::jsactionWithRange, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCShaky3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCShaky3D::jsinitWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShaky3D* self = NULL; JSGET_PTRSHELL(S_CCShaky3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithRange(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShaky3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCShaky3D* self = NULL; JSGET_PTRSHELL(S_CCShaky3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCShaky3D::jsactionWithRange(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		JSBool arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "ibod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCShaky3D* ret = CCShaky3D::actionWithRange(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCShaky3D::jsClass, S_CCShaky3D::jsObject, NULL);
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

JSClass* S_CCActionInterval::jsClass = NULL;
JSObject* S_CCActionInterval::jsObject = NULL;

JSBool S_CCActionInterval::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
	S_CCActionInterval *cobj = new S_CCActionInterval(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCActionInterval::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCActionInterval *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCActionInterval::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionInterval *cobj; JSGET_PTRSHELL(S_CCActionInterval, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kElapsed:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getElapsed(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCActionInterval::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionInterval *cobj; JSGET_PTRSHELL(S_CCActionInterval, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCActionInterval::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"elapsed", kElapsed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionInterval::jsPropertyGet, S_CCActionInterval::jsPropertySet},
			{"firstTick", kFirstTick, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionInterval::jsPropertyGet, S_CCActionInterval::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionInterval::jsPropertyGet, S_CCActionInterval::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCActionInterval::jsinitWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDone", S_CCActionInterval::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("step", S_CCActionInterval::jsstep, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCActionInterval::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCActionInterval::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCActionInterval::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCFiniteTimeAction::jsObject,jsClass,S_CCActionInterval::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCActionInterval::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInterval* self = NULL; JSGET_PTRSHELL(S_CCActionInterval, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		bool ret = self->initWithDuration(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInterval::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInterval* self = NULL; JSGET_PTRSHELL(S_CCActionInterval, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInterval::jsstep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInterval* self = NULL; JSGET_PTRSHELL(S_CCActionInterval, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->step(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInterval::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInterval* self = NULL; JSGET_PTRSHELL(S_CCActionInterval, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionInterval::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionInterval* self = NULL; JSGET_PTRSHELL(S_CCActionInterval, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCActionInterval::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCActionInterval* ret = CCActionInterval::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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

JSClass* S_CCTransitionZoomFlipY::jsClass = NULL;
JSObject* S_CCTransitionZoomFlipY::jsObject = NULL;

JSBool S_CCTransitionZoomFlipY::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionZoomFlipY::jsClass, S_CCTransitionZoomFlipY::jsObject, NULL);
	S_CCTransitionZoomFlipY *cobj = new S_CCTransitionZoomFlipY(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionZoomFlipY::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionZoomFlipY *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionZoomFlipY::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipY *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionZoomFlipY::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipY *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipY, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionZoomFlipY::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionZoomFlipY::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionZoomFlipY::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionZoomFlipY::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionZoomFlipY::onEnter();
}
JSBool S_CCTransitionZoomFlipY::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionZoomFlipY* ret = CCTransitionZoomFlipY::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionZoomFlipY::jsClass, S_CCTransitionZoomFlipY::jsObject, NULL);
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

JSClass* S_CCTextureCache::jsClass = NULL;
JSObject* S_CCTextureCache::jsObject = NULL;

JSBool S_CCTextureCache::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCTextureCache::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTextureCache *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTextureCache::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTextureCache *cobj; JSGET_PTRSHELL(S_CCTextureCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTextureCache::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTextureCache *cobj; JSGET_PTRSHELL(S_CCTextureCache, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTextureCache::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"textures", kTextures, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTextureCache::jsPropertyGet, S_CCTextureCache::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("addImage", S_CCTextureCache::jsaddImage, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addUIImage", S_CCTextureCache::jsaddUIImage, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("textureForKey", S_CCTextureCache::jstextureForKey, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllTextures", S_CCTextureCache::jsremoveAllTextures, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeUnusedTextures", S_CCTextureCache::jsremoveUnusedTextures, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeTexture", S_CCTextureCache::jsremoveTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeTextureForKey", S_CCTextureCache::jsremoveTextureForKey, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("dumpCachedTextureInfo", S_CCTextureCache::jsdumpCachedTextureInfo, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addPVRTCImage", S_CCTextureCache::jsaddPVRTCImage, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addPVRImage", S_CCTextureCache::jsaddPVRImage, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedTextureCache", S_CCTextureCache::jssharedTextureCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeSharedTextureCache", S_CCTextureCache::jspurgeSharedTextureCache, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reloadAllTextures", S_CCTextureCache::jsreloadAllTextures, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCTextureCache::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTextureCache::jssharedTextureCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCTextureCache* ret = CCTextureCache::sharedTextureCache();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTextureCache::jsClass, S_CCTextureCache::jsObject, NULL);
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
JSBool S_CCTextureCache::jspurgeSharedTextureCache(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCTextureCache::purgeSharedTextureCache();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsaddImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTexture2D* ret = self->addImage(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
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
JSBool S_CCTextureCache::jsaddUIImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oS", &arg0, &arg1);
		CCImage* narg0; JSGET_PTRSHELL(CCImage, narg0, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCTexture2D* ret = self->addUIImage(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
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
JSBool S_CCTextureCache::jstextureForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTexture2D* ret = self->textureForKey(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
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
JSBool S_CCTextureCache::jsremoveAllTextures(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->removeAllTextures();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsremoveUnusedTextures(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->removeUnusedTextures();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsremoveTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		self->removeTexture(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsremoveTextureForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->removeTextureForKey(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsdumpCachedTextureInfo(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->dumpCachedTextureInfo();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}


JSBool S_CCTextureCache::jsaddPVRTCImage(JSContext *cx, uint32_t argc, jsval *vp) {
#ifdef CC_SUPPORT_PVRTC
 	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		JSString *arg0;
		int arg1;
		JSBool arg2;
		int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "Sibi", &arg0, &arg1, &arg2, &arg3);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTexture2D* ret = self->addPVRTCImage(narg0, arg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)ret;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
		} while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
#endif
	return JS_TRUE;
}
JSBool S_CCTextureCache::jsaddPVRImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTextureCache* self = NULL; JSGET_PTRSHELL(S_CCTextureCache, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCTexture2D* ret = self->addPVRImage(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
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
JSBool S_CCTextureCache::jsreloadAllTextures(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCTextureCache::reloadAllTextures();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCRepeatForever::jsClass = NULL;
JSObject* S_CCRepeatForever::jsObject = NULL;

JSBool S_CCRepeatForever::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRepeatForever::jsClass, S_CCRepeatForever::jsObject, NULL);
	S_CCRepeatForever *cobj = new S_CCRepeatForever(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRepeatForever::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRepeatForever *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRepeatForever::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRepeatForever *cobj; JSGET_PTRSHELL(S_CCRepeatForever, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kInnerAction:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getInnerAction();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRepeatForever::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRepeatForever *cobj; JSGET_PTRSHELL(S_CCRepeatForever, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kInnerAction:
		do {
			CCActionInterval* tmp; JSGET_PTRSHELL(CCActionInterval, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setInnerAction(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRepeatForever::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"innerAction", kInnerAction, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRepeatForever::jsPropertyGet, S_CCRepeatForever::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCRepeatForever::jsinitWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCRepeatForever::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("step", S_CCRepeatForever::jsstep, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDone", S_CCRepeatForever::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCRepeatForever::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCRepeatForever::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCRepeatForever::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRepeatForever::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeatForever* self = NULL; JSGET_PTRSHELL(S_CCRepeatForever, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		bool ret = self->initWithAction(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeatForever::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeatForever* self = NULL; JSGET_PTRSHELL(S_CCRepeatForever, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeatForever::jsstep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeatForever* self = NULL; JSGET_PTRSHELL(S_CCRepeatForever, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->step(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeatForever::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeatForever* self = NULL; JSGET_PTRSHELL(S_CCRepeatForever, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRepeatForever::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRepeatForever* self = NULL; JSGET_PTRSHELL(S_CCRepeatForever, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCRepeatForever::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCRepeatForever* ret = CCRepeatForever::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRepeatForever::jsClass, S_CCRepeatForever::jsObject, NULL);
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

JSClass* S_CCSpeed::jsClass = NULL;
JSObject* S_CCSpeed::jsObject = NULL;

JSBool S_CCSpeed::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSpeed::jsClass, S_CCSpeed::jsObject, NULL);
	S_CCSpeed *cobj = new S_CCSpeed(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSpeed::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSpeed *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSpeed::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpeed *cobj; JSGET_PTRSHELL(S_CCSpeed, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSpeed:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getSpeed(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kInnerAction:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getInnerAction();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSpeed::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpeed *cobj; JSGET_PTRSHELL(S_CCSpeed, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSpeed:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSpeed(tmp); } while (0);
		break;
	case kInnerAction:
		do {
			CCActionInterval* tmp; JSGET_PTRSHELL(CCActionInterval, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setInnerAction(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSpeed::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"speed", kSpeed, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpeed::jsPropertyGet, S_CCSpeed::jsPropertySet},
			{"innerAction", kInnerAction, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpeed::jsPropertyGet, S_CCSpeed::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCSpeed::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSpeed::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCSpeed::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDone", S_CCSpeed::jsisDone, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCSpeed::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCSpeed::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCAction::jsObject,jsClass,S_CCSpeed::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSpeed::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpeed* self = NULL; JSGET_PTRSHELL(S_CCSpeed, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpeed::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpeed* self = NULL; JSGET_PTRSHELL(S_CCSpeed, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpeed::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpeed* self = NULL; JSGET_PTRSHELL(S_CCSpeed, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpeed::jsisDone(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpeed* self = NULL; JSGET_PTRSHELL(S_CCSpeed, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDone();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpeed::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpeed* self = NULL; JSGET_PTRSHELL(S_CCSpeed, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCSpeed::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCSpeed* ret = CCSpeed::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpeed::jsClass, S_CCSpeed::jsObject, NULL);
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

JSClass* S_CCTransitionZoomFlipX::jsClass = NULL;
JSObject* S_CCTransitionZoomFlipX::jsObject = NULL;

JSBool S_CCTransitionZoomFlipX::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionZoomFlipX::jsClass, S_CCTransitionZoomFlipX::jsObject, NULL);
	S_CCTransitionZoomFlipX *cobj = new S_CCTransitionZoomFlipX(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionZoomFlipX::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionZoomFlipX *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionZoomFlipX::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipX *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionZoomFlipX::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionZoomFlipX *cobj; JSGET_PTRSHELL(S_CCTransitionZoomFlipX, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionZoomFlipX::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionZoomFlipX::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionZoomFlipX::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionZoomFlipX::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionZoomFlipX::onEnter();
}
JSBool S_CCTransitionZoomFlipX::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionZoomFlipX* ret = CCTransitionZoomFlipX::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionZoomFlipX::jsClass, S_CCTransitionZoomFlipX::jsObject, NULL);
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

JSClass* S_CCEaseSineInOut::jsClass = NULL;
JSObject* S_CCEaseSineInOut::jsObject = NULL;

JSBool S_CCEaseSineInOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseSineInOut::jsClass, S_CCEaseSineInOut::jsObject, NULL);
	S_CCEaseSineInOut *cobj = new S_CCEaseSineInOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseSineInOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseSineInOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseSineInOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineInOut *cobj; JSGET_PTRSHELL(S_CCEaseSineInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseSineInOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseSineInOut *cobj; JSGET_PTRSHELL(S_CCEaseSineInOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseSineInOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseSineInOut::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseSineInOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseSineInOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseSineInOut* self = NULL; JSGET_PTRSHELL(S_CCEaseSineInOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseSineInOut::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseSineInOut* ret = CCEaseSineInOut::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseSineInOut::jsClass, S_CCEaseSineInOut::jsObject, NULL);
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

JSClass* S_CCSplitCols::jsClass = NULL;
JSObject* S_CCSplitCols::jsObject = NULL;

JSBool S_CCSplitCols::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSplitCols::jsClass, S_CCSplitCols::jsObject, NULL);
	S_CCSplitCols *cobj = new S_CCSplitCols(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSplitCols::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSplitCols *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSplitCols::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSplitCols *cobj; JSGET_PTRSHELL(S_CCSplitCols, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSplitCols::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSplitCols *cobj; JSGET_PTRSHELL(S_CCSplitCols, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSplitCols::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"cols", kCols, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSplitCols::jsPropertyGet, S_CCSplitCols::jsPropertySet},
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSplitCols::jsPropertyGet, S_CCSplitCols::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithCols", S_CCSplitCols::jsinitWithCols, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSplitCols::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithCols", S_CCSplitCols::jsactionWithCols, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCSplitCols::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSplitCols::jsinitWithCols(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitCols* self = NULL; JSGET_PTRSHELL(S_CCSplitCols, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		int arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "id", &arg0, &arg1);
		bool ret = self->initWithCols(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitCols::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitCols* self = NULL; JSGET_PTRSHELL(S_CCSplitCols, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitCols::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitCols* self = NULL; JSGET_PTRSHELL(S_CCSplitCols, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitCols::jsactionWithCols(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		int arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "id", &arg0, &arg1);
		CCSplitCols* ret = CCSplitCols::actionWithCols(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSplitCols::jsClass, S_CCSplitCols::jsObject, NULL);
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

JSClass* S_CCFadeOut::jsClass = NULL;
JSObject* S_CCFadeOut::jsObject = NULL;

JSBool S_CCFadeOut::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeOut::jsClass, S_CCFadeOut::jsObject, NULL);
	S_CCFadeOut *cobj = new S_CCFadeOut(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeOut::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeOut *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeOut::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOut *cobj; JSGET_PTRSHELL(S_CCFadeOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeOut::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeOut *cobj; JSGET_PTRSHELL(S_CCFadeOut, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeOut::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCFadeOut::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCFadeOut::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCFadeOut::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeOut::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOut* self = NULL; JSGET_PTRSHELL(S_CCFadeOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeOut::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeOut* self = NULL; JSGET_PTRSHELL(S_CCFadeOut, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCFadeOut::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCFadeOut* ret = CCFadeOut::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeOut::jsClass, S_CCFadeOut::jsObject, NULL);
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

JSClass* S_CCTileMapAtlas::jsClass = NULL;
JSObject* S_CCTileMapAtlas::jsObject = NULL;

JSBool S_CCTileMapAtlas::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTileMapAtlas::jsClass, S_CCTileMapAtlas::jsObject, NULL);
	S_CCTileMapAtlas *cobj = new S_CCTileMapAtlas(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTileMapAtlas::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTileMapAtlas *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTileMapAtlas::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTileMapAtlas *cobj; JSGET_PTRSHELL(S_CCTileMapAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTileMapAtlas::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTileMapAtlas *cobj; JSGET_PTRSHELL(S_CCTileMapAtlas, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTileMapAtlas::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"tGAInfo", kTGAInfo, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTileMapAtlas::jsPropertyGet, S_CCTileMapAtlas::jsPropertySet},
			{"posToAtlasIndex", kPosToAtlasIndex, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTileMapAtlas::jsPropertyGet, S_CCTileMapAtlas::jsPropertySet},
			{"itemsToRender", kItemsToRender, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTileMapAtlas::jsPropertyGet, S_CCTileMapAtlas::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTileFile", S_CCTileMapAtlas::jsinitWithTileFile, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("tileAt", S_CCTileMapAtlas::jstileAt, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("releaseMap", S_CCTileMapAtlas::jsreleaseMap, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("tileMapAtlasWithTileFile", S_CCTileMapAtlas::jstileMapAtlasWithTileFile, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCAtlasNode::jsObject,jsClass,S_CCTileMapAtlas::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTileMapAtlas::jstileMapAtlasWithTileFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		JSString *arg0;
		JSString *arg1;
		int arg2;
		int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "SSii", &arg0, &arg1, &arg2, &arg3);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCTileMapAtlas* ret = CCTileMapAtlas::tileMapAtlasWithTileFile(narg0, narg1, arg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTileMapAtlas::jsClass, S_CCTileMapAtlas::jsObject, NULL);
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
JSBool S_CCTileMapAtlas::jsinitWithTileFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTileMapAtlas* self = NULL; JSGET_PTRSHELL(S_CCTileMapAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		JSString *arg0;
		JSString *arg1;
		int arg2;
		int arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "SSii", &arg0, &arg1, &arg2, &arg3);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		bool ret = self->initWithTileFile(narg0, narg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTileMapAtlas::jstileAt(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTileMapAtlas* self = NULL; JSGET_PTRSHELL(S_CCTileMapAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		//INVALID RETURN TYPE _45B
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTileMapAtlas::jsreleaseMap(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTileMapAtlas* self = NULL; JSGET_PTRSHELL(S_CCTileMapAtlas, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->releaseMap();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCRenderTexture::jsClass = NULL;
JSObject* S_CCRenderTexture::jsObject = NULL;

JSBool S_CCRenderTexture::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCRenderTexture::jsClass, S_CCRenderTexture::jsObject, NULL);
	S_CCRenderTexture *cobj = new S_CCRenderTexture(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCRenderTexture::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCRenderTexture *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCRenderTexture::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRenderTexture *cobj; JSGET_PTRSHELL(S_CCRenderTexture, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSprite:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getSprite();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCRenderTexture::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCRenderTexture *cobj; JSGET_PTRSHELL(S_CCRenderTexture, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kSprite:
		do {
			CCSprite* tmp; JSGET_PTRSHELL(CCSprite, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setSprite(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCRenderTexture::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"sprite", kSprite, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{"fBO", kFBO, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{"oldFBO", kOldFBO, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{"uITextureImage", kUITextureImage, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{"ePixelFormat", kEPixelFormat, JSPROP_PERMANENT | JSPROP_SHARED, S_CCRenderTexture::jsPropertyGet, S_CCRenderTexture::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithWidthAndHeight", S_CCRenderTexture::jsinitWithWidthAndHeight, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("begin", S_CCRenderTexture::jsbegin, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("beginWithClear", S_CCRenderTexture::jsbeginWithClear, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("endToLua", S_CCRenderTexture::jsendToLua, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("end", S_CCRenderTexture::jsend, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("clear", S_CCRenderTexture::jsclear, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("saveToFile", S_CCRenderTexture::jssaveToFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("renderTextureWithWidthAndHeight", S_CCRenderTexture::jsrenderTextureWithWidthAndHeight, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCRenderTexture::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRenderTexture::jsbegin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->begin();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jsbeginWithClear(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		double arg0;
		double arg1;
		double arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dddd", &arg0, &arg1, &arg2, &arg3);
		self->beginWithClear(arg0, arg1, arg2, arg3);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jsendToLua(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->endToLua();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jsend(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->end();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jsclear(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		double arg0;
		double arg1;
		double arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "dddd", &arg0, &arg1, &arg2, &arg3);
		self->clear(arg0, arg1, arg2, arg3);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jssaveToFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->saveToFile(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCRenderTexture::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCTransitionCrossFade::jsClass = NULL;
JSObject* S_CCTransitionCrossFade::jsObject = NULL;

JSBool S_CCTransitionCrossFade::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionCrossFade::jsClass, S_CCTransitionCrossFade::jsObject, NULL);
	S_CCTransitionCrossFade *cobj = new S_CCTransitionCrossFade(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionCrossFade::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionCrossFade *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionCrossFade::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionCrossFade *cobj; JSGET_PTRSHELL(S_CCTransitionCrossFade, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionCrossFade::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionCrossFade *cobj; JSGET_PTRSHELL(S_CCTransitionCrossFade, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionCrossFade::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCTransitionCrossFade::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionCrossFade::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionCrossFade::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionCrossFade::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionCrossFade* self = NULL; JSGET_PTRSHELL(S_CCTransitionCrossFade, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCTransitionCrossFade::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionCrossFade::onEnter();
}
void S_CCTransitionCrossFade::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionCrossFade::onExit();
}
JSBool S_CCTransitionCrossFade::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionCrossFade* ret = CCTransitionCrossFade::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionCrossFade::jsClass, S_CCTransitionCrossFade::jsObject, NULL);
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

JSClass* S_CCWaves3D::jsClass = NULL;
JSObject* S_CCWaves3D::jsObject = NULL;

JSBool S_CCWaves3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCWaves3D::jsClass, S_CCWaves3D::jsObject, NULL);
	S_CCWaves3D *cobj = new S_CCWaves3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCWaves3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCWaves3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCWaves3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWaves3D *cobj; JSGET_PTRSHELL(S_CCWaves3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCWaves3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCWaves3D *cobj; JSGET_PTRSHELL(S_CCWaves3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCWaves3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"waves", kWaves, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves3D::jsPropertyGet, S_CCWaves3D::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves3D::jsPropertyGet, S_CCWaves3D::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCWaves3D::jsPropertyGet, S_CCWaves3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithWaves", S_CCWaves3D::jsinitWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithWaves", S_CCWaves3D::jsactionWithWaves, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGrid3DAction::jsObject,jsClass,S_CCWaves3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCWaves3D::jsinitWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWaves3D* self = NULL; JSGET_PTRSHELL(S_CCWaves3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithWaves(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWaves3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCWaves3D* self = NULL; JSGET_PTRSHELL(S_CCWaves3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCWaves3D::jsactionWithWaves(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCWaves3D* ret = CCWaves3D::actionWithWaves(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCWaves3D::jsClass, S_CCWaves3D::jsObject, NULL);
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

JSClass* S_CCActionEase::jsClass = NULL;
JSObject* S_CCActionEase::jsObject = NULL;

JSBool S_CCActionEase::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCActionEase::jsClass, S_CCActionEase::jsObject, NULL);
	S_CCActionEase *cobj = new S_CCActionEase(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCActionEase::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCActionEase *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCActionEase::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionEase *cobj; JSGET_PTRSHELL(S_CCActionEase, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCActionEase::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCActionEase *cobj; JSGET_PTRSHELL(S_CCActionEase, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCActionEase::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"other", kOther, JSPROP_PERMANENT | JSPROP_SHARED, S_CCActionEase::jsPropertyGet, S_CCActionEase::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCActionEase::jsinitWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCActionEase::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCActionEase::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCActionEase::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCActionEase::jsactionWithAction, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCActionEase::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCActionEase::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionEase* self = NULL; JSGET_PTRSHELL(S_CCActionEase, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		bool ret = self->initWithAction(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionEase::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionEase* self = NULL; JSGET_PTRSHELL(S_CCActionEase, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionEase::jsstop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionEase* self = NULL; JSGET_PTRSHELL(S_CCActionEase, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionEase::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionEase* self = NULL; JSGET_PTRSHELL(S_CCActionEase, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCActionEase::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCActionEase* self = NULL; JSGET_PTRSHELL(S_CCActionEase, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCActionEase::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCActionEase* ret = CCActionEase::actionWithAction(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionEase::jsClass, S_CCActionEase::jsObject, NULL);
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

JSClass* S_CCFadeTo::jsClass = NULL;
JSObject* S_CCFadeTo::jsObject = NULL;

JSBool S_CCFadeTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeTo::jsClass, S_CCFadeTo::jsObject, NULL);
	S_CCFadeTo *cobj = new S_CCFadeTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeTo *cobj; JSGET_PTRSHELL(S_CCFadeTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeTo *cobj; JSGET_PTRSHELL(S_CCFadeTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"toOpacity", kToOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFadeTo::jsPropertyGet, S_CCFadeTo::jsPropertySet},
			{"fromOpacity", kFromOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCFadeTo::jsPropertyGet, S_CCFadeTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCFadeTo::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCFadeTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCFadeTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCFadeTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeTo* self = NULL; JSGET_PTRSHELL(S_CCFadeTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		unsigned char arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dc", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeTo* self = NULL; JSGET_PTRSHELL(S_CCFadeTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeTo* self = NULL; JSGET_PTRSHELL(S_CCFadeTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		unsigned char arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dc", &arg0, &arg1);
		CCFadeTo* ret = CCFadeTo::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeTo::jsClass, S_CCFadeTo::jsObject, NULL);
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

JSClass* S_CCMenuItemLabel::jsClass = NULL;
JSObject* S_CCMenuItemLabel::jsObject = NULL;

JSBool S_CCMenuItemLabel::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCMenuItemLabel::jsClass, S_CCMenuItemLabel::jsObject, NULL);
	S_CCMenuItemLabel *cobj = new S_CCMenuItemLabel(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCMenuItemLabel::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCMenuItemLabel *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCMenuItemLabel::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemLabel *cobj; JSGET_PTRSHELL(S_CCMenuItemLabel, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDisabledColor:
				// don't know what this is (c ~> js)
		break;
	case kLabel:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCNode::jsClass, S_CCNode::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getLabel();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kColor:
		do {
			JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			ccColor3B* ctmp = new ccColor3B(cobj->getColor());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCMenuItemLabel::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCMenuItemLabel *cobj; JSGET_PTRSHELL(S_CCMenuItemLabel, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDisabledColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setDisabledColor(color);
		} while (0);
		break;
	case kLabel:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setLabel(tmp); }
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCMenuItemLabel::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"disabledColor", kDisabledColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"label", kLabel, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"colorBackup", kColorBackup, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"originalScale", kOriginalScale, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCMenuItemLabel::jsPropertyGet, S_CCMenuItemLabel::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithLabel", S_CCMenuItemLabel::jsinitWithLabel, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("activate", S_CCMenuItemLabel::jsactivate, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("selected", S_CCMenuItemLabel::jsselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unselected", S_CCMenuItemLabel::jsunselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("itemWithLabel", S_CCMenuItemLabel::jsitemWithLabel, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMenuItem::jsObject,jsClass,S_CCMenuItemLabel::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemLabel::jsactivate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->activate();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItemLabel::jsselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->selected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItemLabel::jsunselected(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->unselected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
MENU_ITEM_ACTION(S_CCMenuItemLabel)

JSClass* S_CCTransitionJumpZoom::jsClass = NULL;
JSObject* S_CCTransitionJumpZoom::jsObject = NULL;

JSBool S_CCTransitionJumpZoom::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionJumpZoom::jsClass, S_CCTransitionJumpZoom::jsObject, NULL);
	S_CCTransitionJumpZoom *cobj = new S_CCTransitionJumpZoom(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionJumpZoom::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionJumpZoom *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionJumpZoom::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionJumpZoom *cobj; JSGET_PTRSHELL(S_CCTransitionJumpZoom, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionJumpZoom::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionJumpZoom *cobj; JSGET_PTRSHELL(S_CCTransitionJumpZoom, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionJumpZoom::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionJumpZoom::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionJumpZoom::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionJumpZoom::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionJumpZoom::onEnter();
}
JSBool S_CCTransitionJumpZoom::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionJumpZoom* ret = CCTransitionJumpZoom::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionJumpZoom::jsClass, S_CCTransitionJumpZoom::jsObject, NULL);
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

JSClass* S_CCBlink::jsClass = NULL;
JSObject* S_CCBlink::jsObject = NULL;

JSBool S_CCBlink::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCBlink::jsClass, S_CCBlink::jsObject, NULL);
	S_CCBlink *cobj = new S_CCBlink(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCBlink::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCBlink *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCBlink::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBlink *cobj; JSGET_PTRSHELL(S_CCBlink, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCBlink::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBlink *cobj; JSGET_PTRSHELL(S_CCBlink, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCBlink::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"times", kTimes, JSPROP_PERMANENT | JSPROP_SHARED, S_CCBlink::jsPropertyGet, S_CCBlink::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCBlink::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCBlink::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCBlink::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCBlink::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCBlink::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBlink* self = NULL; JSGET_PTRSHELL(S_CCBlink, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "di", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBlink::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBlink* self = NULL; JSGET_PTRSHELL(S_CCBlink, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBlink::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBlink* self = NULL; JSGET_PTRSHELL(S_CCBlink, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCBlink::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "di", &arg0, &arg1);
		CCBlink* ret = CCBlink::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCBlink::jsClass, S_CCBlink::jsObject, NULL);
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

JSClass* S_CCTransitionFlipAngular::jsClass = NULL;
JSObject* S_CCTransitionFlipAngular::jsObject = NULL;

JSBool S_CCTransitionFlipAngular::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionFlipAngular::jsClass, S_CCTransitionFlipAngular::jsObject, NULL);
	S_CCTransitionFlipAngular *cobj = new S_CCTransitionFlipAngular(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionFlipAngular::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionFlipAngular *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionFlipAngular::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipAngular *cobj; JSGET_PTRSHELL(S_CCTransitionFlipAngular, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionFlipAngular::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionFlipAngular *cobj; JSGET_PTRSHELL(S_CCTransitionFlipAngular, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionFlipAngular::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionFlipAngular::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSceneOriented::jsObject,jsClass,S_CCTransitionFlipAngular::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionFlipAngular::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionFlipAngular::onEnter();
}
JSBool S_CCTransitionFlipAngular::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionFlipAngular* ret = CCTransitionFlipAngular::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionFlipAngular::jsClass, S_CCTransitionFlipAngular::jsObject, NULL);
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

JSClass* S_CCTransitionRotoZoom::jsClass = NULL;
JSObject* S_CCTransitionRotoZoom::jsObject = NULL;

JSBool S_CCTransitionRotoZoom::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionRotoZoom::jsClass, S_CCTransitionRotoZoom::jsObject, NULL);
	S_CCTransitionRotoZoom *cobj = new S_CCTransitionRotoZoom(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionRotoZoom::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionRotoZoom *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionRotoZoom::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionRotoZoom *cobj; JSGET_PTRSHELL(S_CCTransitionRotoZoom, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionRotoZoom::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionRotoZoom *cobj; JSGET_PTRSHELL(S_CCTransitionRotoZoom, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionRotoZoom::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionRotoZoom::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionRotoZoom::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

void S_CCTransitionRotoZoom::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionRotoZoom::onEnter();
}
JSBool S_CCTransitionRotoZoom::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionRotoZoom* ret = CCTransitionRotoZoom::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionRotoZoom::jsClass, S_CCTransitionRotoZoom::jsObject, NULL);
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

JSClass* S_CCJumpTiles3D::jsClass = NULL;
JSObject* S_CCJumpTiles3D::jsObject = NULL;

JSBool S_CCJumpTiles3D::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCJumpTiles3D::jsClass, S_CCJumpTiles3D::jsObject, NULL);
	S_CCJumpTiles3D *cobj = new S_CCJumpTiles3D(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCJumpTiles3D::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCJumpTiles3D *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCJumpTiles3D::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpTiles3D *cobj; JSGET_PTRSHELL(S_CCJumpTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitude(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAmplitudeRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCJumpTiles3D::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCJumpTiles3D *cobj; JSGET_PTRSHELL(S_CCJumpTiles3D, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kAmplitude:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitude(tmp); } while (0);
		break;
	case kAmplitudeRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setAmplitudeRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCJumpTiles3D::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"jumps", kJumps, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpTiles3D::jsPropertyGet, S_CCJumpTiles3D::jsPropertySet},
			{"amplitude", kAmplitude, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpTiles3D::jsPropertyGet, S_CCJumpTiles3D::jsPropertySet},
			{"amplitudeRate", kAmplitudeRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCJumpTiles3D::jsPropertyGet, S_CCJumpTiles3D::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithJumps", S_CCJumpTiles3D::jsinitWithJumps, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithJumps", S_CCJumpTiles3D::jsactionWithJumps, 4, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCJumpTiles3D::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCJumpTiles3D::jsinitWithJumps(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpTiles3D* self = NULL; JSGET_PTRSHELL(S_CCJumpTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		bool ret = self->initWithJumps(arg0, arg1, *narg2, arg3);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpTiles3D::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCJumpTiles3D* self = NULL; JSGET_PTRSHELL(S_CCJumpTiles3D, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCJumpTiles3D::jsactionWithJumps(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 4) {
		int arg0;
		double arg1;
		JSObject *arg2;
		double arg3;
		JS_ConvertArguments(cx, 4, JS_ARGV(cx, vp), "idod", &arg0, &arg1, &arg2, &arg3);
		ccGridSize* narg2; JSGET_PTRSHELL(ccGridSize, narg2, arg2);
		CCJumpTiles3D* ret = CCJumpTiles3D::actionWithJumps(arg0, arg1, *narg2, arg3);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCJumpTiles3D::jsClass, S_CCJumpTiles3D::jsObject, NULL);
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

JSClass* S_CCFadeIn::jsClass = NULL;
JSObject* S_CCFadeIn::jsObject = NULL;

JSBool S_CCFadeIn::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCFadeIn::jsClass, S_CCFadeIn::jsObject, NULL);
	S_CCFadeIn *cobj = new S_CCFadeIn(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCFadeIn::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCFadeIn *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCFadeIn::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeIn *cobj; JSGET_PTRSHELL(S_CCFadeIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCFadeIn::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCFadeIn *cobj; JSGET_PTRSHELL(S_CCFadeIn, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCFadeIn::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("reverse", S_CCFadeIn::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCFadeIn::jsactionWithDuration, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCFadeIn::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCFadeIn::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeIn* self = NULL; JSGET_PTRSHELL(S_CCFadeIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFadeIn::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCFadeIn* self = NULL; JSGET_PTRSHELL(S_CCFadeIn, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCFadeIn::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		CCFadeIn* ret = CCFadeIn::actionWithDuration(arg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCFadeIn::jsClass, S_CCFadeIn::jsObject, NULL);
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

JSClass* S_CCUserDefault::jsClass = NULL;
JSObject* S_CCUserDefault::jsObject = NULL;

JSBool S_CCUserDefault::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	return JS_FALSE;
};

void S_CCUserDefault::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCUserDefault *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCUserDefault::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCUserDefault *cobj; JSGET_PTRSHELL(S_CCUserDefault, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCUserDefault::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCUserDefault *cobj; JSGET_PTRSHELL(S_CCUserDefault, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCUserDefault::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("getBoolForKey", S_CCUserDefault::jsgetBoolForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("getIntegerForKey", S_CCUserDefault::jsgetIntegerForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("getFloatForKey", S_CCUserDefault::jsgetFloatForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("getDoubleForKey", S_CCUserDefault::jsgetDoubleForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("getStringForKey", S_CCUserDefault::jsgetStringForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setBoolForKey", S_CCUserDefault::jssetBoolForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setIntegerForKey", S_CCUserDefault::jssetIntegerForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setFloatForKey", S_CCUserDefault::jssetFloatForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setDoubleForKey", S_CCUserDefault::jssetDoubleForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setStringForKey", S_CCUserDefault::jssetStringForKey, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("flush", S_CCUserDefault::jsflush, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("sharedUserDefault", S_CCUserDefault::jssharedUserDefault, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("purgeSharedUserDefault", S_CCUserDefault::jspurgeSharedUserDefault, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCUserDefault::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCUserDefault::jsgetBoolForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sb", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->getBoolForKey(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jsgetIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Si", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		int ret = self->getIntegerForKey(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jsgetFloatForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sd", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		float ret = self->getFloatForKey(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jsgetDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sd", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		double ret = self->getDoubleForKey(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jssetBoolForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sb", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->setBoolForKey(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jssetIntegerForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Si", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->setIntegerForKey(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jssetFloatForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sd", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->setFloatForKey(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jssetDoubleForKey(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Sd", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->setDoubleForKey(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jsflush(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCUserDefault* self = NULL; JSGET_PTRSHELL(S_CCUserDefault, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->flush();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCUserDefault::jssharedUserDefault(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCUserDefault* ret = CCUserDefault::sharedUserDefault();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCUserDefault::jsClass, S_CCUserDefault::jsObject, NULL);
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
JSBool S_CCUserDefault::jspurgeSharedUserDefault(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		CCUserDefault::purgeSharedUserDefault();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCSplitRows::jsClass = NULL;
JSObject* S_CCSplitRows::jsObject = NULL;

JSBool S_CCSplitRows::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSplitRows::jsClass, S_CCSplitRows::jsObject, NULL);
	S_CCSplitRows *cobj = new S_CCSplitRows(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSplitRows::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSplitRows *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSplitRows::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSplitRows *cobj; JSGET_PTRSHELL(S_CCSplitRows, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSplitRows::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSplitRows *cobj; JSGET_PTRSHELL(S_CCSplitRows, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSplitRows::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rows", kRows, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSplitRows::jsPropertyGet, S_CCSplitRows::jsPropertySet},
			{"size", kSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSplitRows::jsPropertyGet, S_CCSplitRows::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithRows", S_CCSplitRows::jsinitWithRows, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCSplitRows::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithRows", S_CCSplitRows::jsactionWithRows, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTiledGrid3DAction::jsObject,jsClass,S_CCSplitRows::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSplitRows::jsinitWithRows(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitRows* self = NULL; JSGET_PTRSHELL(S_CCSplitRows, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		int arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "id", &arg0, &arg1);
		bool ret = self->initWithRows(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitRows::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitRows* self = NULL; JSGET_PTRSHELL(S_CCSplitRows, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitRows::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSplitRows* self = NULL; JSGET_PTRSHELL(S_CCSplitRows, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSplitRows::jsactionWithRows(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		int arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "id", &arg0, &arg1);
		CCSplitRows* ret = CCSplitRows::actionWithRows(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSplitRows::jsClass, S_CCSplitRows::jsObject, NULL);
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

JSClass* S_CCTransitionSlideInB::jsClass = NULL;
JSObject* S_CCTransitionSlideInB::jsObject = NULL;

JSBool S_CCTransitionSlideInB::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSlideInB::jsClass, S_CCTransitionSlideInB::jsObject, NULL);
	S_CCTransitionSlideInB *cobj = new S_CCTransitionSlideInB(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSlideInB::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSlideInB *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSlideInB::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInB *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInB, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSlideInB::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInB *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInB, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSlideInB::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionSlideInB::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("action", S_CCTransitionSlideInB::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSlideInB::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSlideInL::jsObject,jsClass,S_CCTransitionSlideInB::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSlideInB::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInB* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInB, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionSlideInB::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInB* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInB, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSlideInB::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSlideInB* ret = CCTransitionSlideInB::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSlideInB::jsClass, S_CCTransitionSlideInB::jsObject, NULL);
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

JSClass* S_CCTransitionSceneOriented::jsClass = NULL;
JSObject* S_CCTransitionSceneOriented::jsObject = NULL;

JSBool S_CCTransitionSceneOriented::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSceneOriented::jsClass, S_CCTransitionSceneOriented::jsObject, NULL);
	S_CCTransitionSceneOriented *cobj = new S_CCTransitionSceneOriented(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSceneOriented::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSceneOriented *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSceneOriented::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSceneOriented *cobj; JSGET_PTRSHELL(S_CCTransitionSceneOriented, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSceneOriented::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSceneOriented *cobj; JSGET_PTRSHELL(S_CCTransitionSceneOriented, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSceneOriented::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"eOrientation", kEOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionSceneOriented::jsPropertyGet, S_CCTransitionSceneOriented::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCTransitionSceneOriented::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSceneOriented::jstransitionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionScene::jsObject,jsClass,S_CCTransitionSceneOriented::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSceneOriented::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSceneOriented* ret = CCTransitionSceneOriented::transitionWithDuration(arg0, narg1, arg2);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSceneOriented::jsClass, S_CCTransitionSceneOriented::jsObject, NULL);
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
JSBool S_CCTransitionSceneOriented::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSceneOriented* self = NULL; JSGET_PTRSHELL(S_CCTransitionSceneOriented, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		tOrientation arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "doi", &arg0, &arg1, &arg2);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		bool ret = self->initWithDuration(arg0, narg1, arg2);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCSet::jsClass = NULL;
JSObject* S_CCSet::jsObject = NULL;

JSBool S_CCSet::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSet::jsClass, S_CCSet::jsObject, NULL);
	S_CCSet *cobj = new S_CCSet(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSet::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSet *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSet::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSet *cobj; JSGET_PTRSHELL(S_CCSet, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSet::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSet *cobj; JSGET_PTRSHELL(S_CCSet, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSet::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"set", kSet, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSet::jsPropertyGet, S_CCSet::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("copy", S_CCSet::jscopy, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("count", S_CCSet::jscount, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addObject", S_CCSet::jsaddObject, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeObject", S_CCSet::jsremoveObject, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("containsObject", S_CCSet::jscontainsObject, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("begin", S_CCSet::jsbegin, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("end", S_CCSet::jsend, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCSet::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSet::jscopy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCSet* ret = self->copy();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSet::jsClass, S_CCSet::jsObject, NULL);
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
JSBool S_CCSet::jscount(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		int ret = self->count();
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jsaddObject(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCObject* narg0; JSGET_PTRSHELL(CCObject, narg0, arg0);
		self->addObject(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jsremoveObject(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCObject* narg0; JSGET_PTRSHELL(CCObject, narg0, arg0);
		self->removeObject(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jscontainsObject(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCObject* narg0; JSGET_PTRSHELL(CCObject, narg0, arg0);
		bool ret = self->containsObject(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jsbegin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		//INVALID RETURN TYPE _3EF6
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jsend(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		//INVALID RETURN TYPE _3EF6
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTouch::jsClass = NULL;
JSObject* S_CCTouch::jsObject = NULL;

JSBool S_CCTouch::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTouch::jsClass, S_CCTouch::jsObject, NULL);
	S_CCTouch *cobj = new S_CCTouch(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTouch::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTouch *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTouch::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTouch *cobj; JSGET_PTRSHELL(S_CCTouch, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTouch::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTouch *cobj; JSGET_PTRSHELL(S_CCTouch, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTouch::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"point", kPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTouch::jsPropertyGet, S_CCTouch::jsPropertySet},
			{"prevPoint", kPrevPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTouch::jsPropertyGet, S_CCTouch::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("locationInView", S_CCTouch::jslocationInView, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("previousLocationInView", S_CCTouch::jspreviousLocationInView, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("setTouchInfo", S_CCTouch::jsSetTouchInfo, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCTouch::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTouch::jslocationInView(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTouch* self = NULL; JSGET_PTRSHELL(S_CCTouch, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCPoint* ret = new CCPoint(self->locationInView());
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCTouch::jspreviousLocationInView(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTouch* self = NULL; JSGET_PTRSHELL(S_CCTouch, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCPoint* ret = new CCPoint(self->previousLocationInView());
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
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
JSBool S_CCTouch::jsSetTouchInfo(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTouch* self = NULL; JSGET_PTRSHELL(S_CCTouch, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		double arg1;
        double arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "dd", &arg0, &arg1, &arg2);
		self->setTouchInfo(arg0, arg1, arg2);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCTransitionSlideInT::jsClass = NULL;
JSObject* S_CCTransitionSlideInT::jsObject = NULL;

JSBool S_CCTransitionSlideInT::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionSlideInT::jsClass, S_CCTransitionSlideInT::jsObject, NULL);
	S_CCTransitionSlideInT *cobj = new S_CCTransitionSlideInT(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionSlideInT::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionSlideInT *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionSlideInT::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInT *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInT, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionSlideInT::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionSlideInT *cobj; JSGET_PTRSHELL(S_CCTransitionSlideInT, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionSlideInT::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initScenes", S_CCTransitionSlideInT::jsinitScenes, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("action", S_CCTransitionSlideInT::jsaction, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionSlideInT::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCTransitionSlideInL::jsObject,jsClass,S_CCTransitionSlideInT::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionSlideInT::jsinitScenes(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInT* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInT, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->initScenes();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionSlideInT::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionSlideInT* self = NULL; JSGET_PTRSHELL(S_CCTransitionSlideInT, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->action();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCTransitionSlideInT::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionSlideInT* ret = CCTransitionSlideInT::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionSlideInT::jsClass, S_CCTransitionSlideInT::jsObject, NULL);
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

JSClass* S_CCSprite::jsClass = NULL;
JSObject* S_CCSprite::jsObject = NULL;

JSBool S_CCSprite::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
	S_CCSprite *cobj = new S_CCSprite(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSprite::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSprite *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSprite::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSprite *cobj; JSGET_PTRSHELL(S_CCSprite, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kColor:
				// don't know what this is (c ~> js)
		break;
	case kAtlasIndex:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAtlasIndex(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	case kTexture:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTexture2D::jsClass, S_CCTexture2D::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTexture();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kQuad:
				// don't know what this is (c ~> js)
		break;
	case kHonorParentTransform:
				// don't know what this is (c ~> js)
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->isOpacityModifyRGB()));
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSprite::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSprite *cobj; JSGET_PTRSHELL(S_CCSprite, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kOpacity:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setOpacity(tmp); } while (0);
		break;
	case kColor:
		do {
			JSObject *arr = JSVAL_TO_OBJECT(*val);
			jsval jr, jg, jb;
			int32_t r, g, b;
			JS_GetElement(cx, arr, 0, &jr);
			JS_GetElement(cx, arr, 1, &jg);
			JS_GetElement(cx, arr, 2, &jb);
			JS_ValueToInt32(cx, jr, &r); JS_ValueToInt32(cx, jg, &g); JS_ValueToInt32(cx, jb, &b);
			ccColor3B color = ccc3(r, g, b);
			cobj->setColor(color);
		} while (0);
		break;
	case kAtlasIndex:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setAtlasIndex(tmp); } while (0);
		break;
	case kDirty:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDirty(tmp); } while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	case kTexture:
		do {
			CCTexture2D* tmp; JSGET_PTRSHELL(CCTexture2D, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTexture(tmp); }
		} while (0);
		break;
	case kFlipX:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipX(tmp); } while (0);
		break;
	case kFlipY:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipY(tmp); } while (0);
		break;
	case kHonorParentTransform:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSprite::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"opacity", kOpacity, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"color", kColor, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"textureAtlas", kTextureAtlas, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"atlasIndex", kAtlasIndex, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"batchNode", kBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"transform", kTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"recursiveDirty", kRecursiveDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"hasChildren", kHasChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"texture", kTexture, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"usesBatchNode", kUsesBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rect", kRect, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rectInPixels", kRectInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rectRotated", kRectRotated, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"unflippedOffsetPositionFromCenter", kUnflippedOffsetPositionFromCenter, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"quad", kQuad, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"colorUnmodified", kColorUnmodified, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"opacityModifyRGB", kOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipX", kFlipX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipY", kFlipY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"honorParentTransform", kHonorParentTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCSprite::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDirty", S_CCSprite::jsisDirty, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isTextureRectRotated", S_CCSprite::jsisTextureRectRotated, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("init", S_CCSprite::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChild", S_CCSprite::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCSprite::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reorderChild", S_CCSprite::jsreorderChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFlipX", S_CCSprite::jsisFlipX, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFlipY", S_CCSprite::jsisFlipY, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateColor", S_CCSprite::jsupdateColor, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithTexture", S_CCSprite::jsinitWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSpriteFrame", S_CCSprite::jsinitWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSpriteFrameName", S_CCSprite::jsinitWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithFile", S_CCSprite::jsinitWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateTransform", S_CCSprite::jsupdateTransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFrameDisplayed", S_CCSprite::jsisFrameDisplayed, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("displayFrame", S_CCSprite::jsdisplayFrame, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("spriteWithTexture", S_CCSprite::jsspriteWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrame", S_CCSprite::jsspriteWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrameName", S_CCSprite::jsspriteWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithFile", S_CCSprite::jsspriteWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCSprite::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSprite::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisDirty(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isDirty();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisTextureRectRotated(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isTextureRectRotated();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsspriteWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCSprite* ret = CCSprite::spriteWithTexture(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
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
JSBool S_CCSprite::jsspriteWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		CCSprite* ret = CCSprite::spriteWithSpriteFrame(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
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
JSBool S_CCSprite::jsspriteWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSprite* ret = CCSprite::spriteWithSpriteFrameName(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
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
JSBool S_CCSprite::jsspriteWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSprite* ret = CCSprite::spriteWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSprite::jsClass, S_CCSprite::jsObject, NULL);
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
JSBool S_CCSprite::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->removeChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->removeAllChildrenWithCleanup(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->reorderChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisFlipX(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isFlipX();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisFlipY(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->isFlipY();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsupdateColor(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->updateColor();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		bool ret = self->initWithTexture(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsinitWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		bool ret = self->initWithSpriteFrame(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsinitWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithSpriteFrameName(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithFile(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsupdateTransform(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->updateTransform();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisFrameDisplayed(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		bool ret = self->isFrameDisplayed(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsdisplayFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCSpriteFrame* ret = self->displayFrame();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteFrame::jsClass, S_CCSpriteFrame::jsObject, NULL);
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
void S_CCSprite::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCTransitionScene::jsClass = NULL;
JSObject* S_CCTransitionScene::jsObject = NULL;

JSBool S_CCTransitionScene::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCTransitionScene::jsClass, S_CCTransitionScene::jsObject, NULL);
	S_CCTransitionScene *cobj = new S_CCTransitionScene(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCTransitionScene::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCTransitionScene *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCTransitionScene::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionScene *cobj; JSGET_PTRSHELL(S_CCTransitionScene, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCTransitionScene::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCTransitionScene *cobj; JSGET_PTRSHELL(S_CCTransitionScene, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCTransitionScene::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"inScene", kInScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionScene::jsPropertyGet, S_CCTransitionScene::jsPropertySet},
			{"outScene", kOutScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionScene::jsPropertyGet, S_CCTransitionScene::jsPropertySet},
			{"duration", kDuration, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionScene::jsPropertyGet, S_CCTransitionScene::jsPropertySet},
			{"isInSceneOnTop", kIsInSceneOnTop, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionScene::jsPropertyGet, S_CCTransitionScene::jsPropertySet},
			{"isSendCleanupToScene", kIsSendCleanupToScene, JSPROP_PERMANENT | JSPROP_SHARED, S_CCTransitionScene::jsPropertyGet, S_CCTransitionScene::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCTransitionScene::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("cleanup", S_CCTransitionScene::jscleanup, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithDuration", S_CCTransitionScene::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("finish", S_CCTransitionScene::jsfinish, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("hideOutShowIn", S_CCTransitionScene::jshideOutShowIn, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("transitionWithDuration", S_CCTransitionScene::jstransitionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCScene::jsObject,jsClass,S_CCTransitionScene::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCTransitionScene::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionScene* self = NULL; JSGET_PTRSHELL(S_CCTransitionScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCTransitionScene::onEnter() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onEnter", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onEnter", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionScene::onEnter();
}
void S_CCTransitionScene::onExit() {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "onExit", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "onExit", &fval);
			JS_CallFunctionValue(cx, m_jsobj, fval, 0, 0, &rval);
		}
	}
			CCTransitionScene::onExit();
}
JSBool S_CCTransitionScene::jscleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionScene* self = NULL; JSGET_PTRSHELL(S_CCTransitionScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->cleanup();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionScene::jstransitionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		CCTransitionScene* ret = CCTransitionScene::transitionWithDuration(arg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTransitionScene::jsClass, S_CCTransitionScene::jsObject, NULL);
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
JSBool S_CCTransitionScene::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionScene* self = NULL; JSGET_PTRSHELL(S_CCTransitionScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		CCScene* narg1; JSGET_PTRSHELL(CCScene, narg1, arg1);
		bool ret = self->initWithDuration(arg0, narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionScene::jsfinish(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionScene* self = NULL; JSGET_PTRSHELL(S_CCTransitionScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->finish();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCTransitionScene::jshideOutShowIn(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCTransitionScene* self = NULL; JSGET_PTRSHELL(S_CCTransitionScene, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->hideOutShowIn();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCScaleBy::jsClass = NULL;
JSObject* S_CCScaleBy::jsObject = NULL;

JSBool S_CCScaleBy::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCScaleBy::jsClass, S_CCScaleBy::jsObject, NULL);
	S_CCScaleBy *cobj = new S_CCScaleBy(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCScaleBy::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCScaleBy *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCScaleBy::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScaleBy *cobj; JSGET_PTRSHELL(S_CCScaleBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCScaleBy::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScaleBy *cobj; JSGET_PTRSHELL(S_CCScaleBy, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCScaleBy::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCScaleBy::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCScaleBy::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCScaleBy::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCScaleTo::jsObject,jsClass,S_CCScaleBy::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCScaleBy::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScaleBy* self = NULL; JSGET_PTRSHELL(S_CCScaleBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCScaleBy::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScaleBy* self = NULL; JSGET_PTRSHELL(S_CCScaleBy, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCScaleBy::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		CCScaleBy* ret = CCScaleBy::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCScaleBy::jsClass, S_CCScaleBy::jsObject, NULL);
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

JSClass* S_CCSpriteBatchNode::jsClass = NULL;
JSObject* S_CCSpriteBatchNode::jsObject = NULL;

JSBool S_CCSpriteBatchNode::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCSpriteBatchNode::jsClass, S_CCSpriteBatchNode::jsObject, NULL);
	S_CCSpriteBatchNode *cobj = new S_CCSpriteBatchNode(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCSpriteBatchNode::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCSpriteBatchNode *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCSpriteBatchNode::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteBatchNode *cobj; JSGET_PTRSHELL(S_CCSpriteBatchNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTextureAtlas:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCTextureAtlas::jsClass, S_CCTextureAtlas::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			pt->flags = kPointerTemporary;
			pt->data = (void *)cobj->getTextureAtlas();
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCSpriteBatchNode::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCSpriteBatchNode *cobj; JSGET_PTRSHELL(S_CCSpriteBatchNode, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kTextureAtlas:
		do {
			CCTextureAtlas* tmp; JSGET_PTRSHELL(CCTextureAtlas, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setTextureAtlas(tmp); }
		} while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c)
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCSpriteBatchNode::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"textureAtlas", kTextureAtlas, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteBatchNode::jsPropertyGet, S_CCSpriteBatchNode::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteBatchNode::jsPropertyGet, S_CCSpriteBatchNode::jsPropertySet},
			{"descendants", kDescendants, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSpriteBatchNode::jsPropertyGet, S_CCSpriteBatchNode::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithTexture", S_CCSpriteBatchNode::jsinitWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithFile", S_CCSpriteBatchNode::jsinitWithFile, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("increaseAtlasCapacity", S_CCSpriteBatchNode::jsincreaseAtlasCapacity, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChildAtIndex", S_CCSpriteBatchNode::jsremoveChildAtIndex, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("insertChild", S_CCSpriteBatchNode::jsinsertChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeSpriteFromAtlas", S_CCSpriteBatchNode::jsremoveSpriteFromAtlas, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("rebuildIndexInOrder", S_CCSpriteBatchNode::jsrebuildIndexInOrder, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("highestAtlasIndexInChild", S_CCSpriteBatchNode::jshighestAtlasIndexInChild, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("lowestAtlasIndexInChild", S_CCSpriteBatchNode::jslowestAtlasIndexInChild, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("atlasIndexForChild", S_CCSpriteBatchNode::jsatlasIndexForChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("visit", S_CCSpriteBatchNode::jsvisit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reorderChild", S_CCSpriteBatchNode::jsreorderChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeChild", S_CCSpriteBatchNode::jsremoveChild, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("removeAllChildrenWithCleanup", S_CCSpriteBatchNode::jsremoveAllChildrenWithCleanup, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("draw", S_CCSpriteBatchNode::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("batchNodeWithTexture", S_CCSpriteBatchNode::jsbatchNodeWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("batchNodeWithFile", S_CCSpriteBatchNode::jsbatchNodeWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCSpriteBatchNode::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSpriteBatchNode::jsbatchNodeWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCSpriteBatchNode* ret = CCSpriteBatchNode::batchNodeWithTexture(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteBatchNode::jsClass, S_CCSpriteBatchNode::jsObject, NULL);
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
JSBool S_CCSpriteBatchNode::jsbatchNodeWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSpriteBatchNode* ret = CCSpriteBatchNode::batchNodeWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSpriteBatchNode::jsClass, S_CCSpriteBatchNode::jsObject, NULL);
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
JSBool S_CCSpriteBatchNode::jsinitWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		bool ret = self->initWithTexture(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsinitWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSString *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "Si", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->initWithFile(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsincreaseAtlasCapacity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->increaseAtlasCapacity();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsremoveChildAtIndex(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		unsigned int arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ib", &arg0, &arg1);
		self->removeChildAtIndex(arg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsinsertChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		self->insertChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsremoveSpriteFromAtlas(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		self->removeSpriteFromAtlas(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsrebuildIndexInOrder(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		unsigned int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		unsigned int ret = self->rebuildIndexInOrder(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jshighestAtlasIndexInChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		unsigned int ret = self->highestAtlasIndexInChild(narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jslowestAtlasIndexInChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		unsigned int ret = self->lowestAtlasIndexInChild(narg0);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsatlasIndexForChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCSprite* narg0; JSGET_PTRSHELL(CCSprite, narg0, arg0);
		unsigned int ret = self->atlasIndexForChild(narg0, arg1);
		do { jsval tmp; JS_NewNumberValue(cx, ret, &tmp); JS_SET_RVAL(cx, vp, tmp); } while (0);
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsvisit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->visit();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsreorderChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oi", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->reorderChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsremoveChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSBool arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ob", &arg0, &arg1);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->removeChild(narg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsremoveAllChildrenWithCleanup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSBool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->removeAllChildrenWithCleanup(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSpriteBatchNode::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSpriteBatchNode* self = NULL; JSGET_PTRSHELL(S_CCSpriteBatchNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCSpriteBatchNode::update(float delta) {
	if (m_jsobj) {
		JSContext* cx = ScriptingCore::getInstance().getGlobalContext();
		JSBool found; JS_HasProperty(cx, m_jsobj, "update", &found);
		if (found == JS_TRUE) {
			jsval rval, fval;
			JS_GetProperty(cx, m_jsobj, "update", &fval);
			jsval jsdelta; JS_NewNumberValue(cx, delta, &jsdelta);
			JS_CallFunctionValue(cx, m_jsobj, fval, 1, &jsdelta, &rval);
		}
	}
}

JSClass* S_CCGridAction::jsClass = NULL;
JSObject* S_CCGridAction::jsObject = NULL;

JSBool S_CCGridAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCGridAction::jsClass, S_CCGridAction::jsObject, NULL);
	S_CCGridAction *cobj = new S_CCGridAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCGridAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCGridAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCGridAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCGridAction *cobj; JSGET_PTRSHELL(S_CCGridAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCGridAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCGridAction *cobj; JSGET_PTRSHELL(S_CCGridAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCGridAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"gridSize", kGridSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCGridAction::jsPropertyGet, S_CCGridAction::jsPropertySet},
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCGridAction::jsPropertyGet, S_CCGridAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCGridAction::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCGridAction::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithSize", S_CCGridAction::jsinitWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithSize", S_CCGridAction::jsactionWithSize, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCGridAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCGridAction::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCGridAction* self = NULL; JSGET_PTRSHELL(S_CCGridAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCGridAction::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCGridAction* self = NULL; JSGET_PTRSHELL(S_CCGridAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCGridAction::jsinitWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCGridAction* self = NULL; JSGET_PTRSHELL(S_CCGridAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		bool ret = self->initWithSize(*narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCGridAction::jsactionWithSize(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		CCGridAction* ret = CCGridAction::actionWithSize(*narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCGridAction::jsClass, S_CCGridAction::jsObject, NULL);
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

JSClass* S_CCScaleTo::jsClass = NULL;
JSObject* S_CCScaleTo::jsObject = NULL;

JSBool S_CCScaleTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCScaleTo::jsClass, S_CCScaleTo::jsObject, NULL);
	S_CCScaleTo *cobj = new S_CCScaleTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCScaleTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCScaleTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCScaleTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScaleTo *cobj; JSGET_PTRSHELL(S_CCScaleTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCScaleTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCScaleTo *cobj; JSGET_PTRSHELL(S_CCScaleTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCScaleTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"scaleX", kScaleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"scaleY", kScaleY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"startScaleX", kStartScaleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"startScaleY", kStartScaleY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"endScaleX", kEndScaleX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"endScaleY", kEndScaleY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"deltaX", kDeltaX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{"deltaY", kDeltaY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCScaleTo::jsPropertyGet, S_CCScaleTo::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithDuration", S_CCScaleTo::jsinitWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCScaleTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCScaleTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionInterval::jsObject,jsClass,S_CCScaleTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCScaleTo::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScaleTo* self = NULL; JSGET_PTRSHELL(S_CCScaleTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		bool ret = self->initWithDuration(arg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCScaleTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScaleTo* self = NULL; JSGET_PTRSHELL(S_CCScaleTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCScaleTo::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCScaleTo* self = NULL; JSGET_PTRSHELL(S_CCScaleTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		double arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "d", &arg0);
		self->update(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCScaleTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		CCScaleTo* ret = CCScaleTo::actionWithDuration(arg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCScaleTo::jsClass, S_CCScaleTo::jsObject, NULL);
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

JSClass* S_CCEaseRateAction::jsClass = NULL;
JSObject* S_CCEaseRateAction::jsObject = NULL;

JSBool S_CCEaseRateAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCEaseRateAction::jsClass, S_CCEaseRateAction::jsObject, NULL);
	S_CCEaseRateAction *cobj = new S_CCEaseRateAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCEaseRateAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCEaseRateAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCEaseRateAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseRateAction *cobj; JSGET_PTRSHELL(S_CCEaseRateAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getRate(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCEaseRateAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCEaseRateAction *cobj; JSGET_PTRSHELL(S_CCEaseRateAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kRate:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setRate(tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCEaseRateAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"rate", kRate, JSPROP_PERMANENT | JSPROP_SHARED, S_CCEaseRateAction::jsPropertyGet, S_CCEaseRateAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithAction", S_CCEaseRateAction::jsinitWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCEaseRateAction::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAction", S_CCEaseRateAction::jsactionWithAction, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCActionEase::jsObject,jsClass,S_CCEaseRateAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCEaseRateAction::jsinitWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseRateAction* self = NULL; JSGET_PTRSHELL(S_CCEaseRateAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		bool ret = self->initWithAction(narg0, arg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCEaseRateAction::jsreverse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCEaseRateAction* self = NULL; JSGET_PTRSHELL(S_CCEaseRateAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		CCActionInterval* ret = self->reverse();
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCActionInterval::jsClass, S_CCActionInterval::jsObject, NULL);
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
JSBool S_CCEaseRateAction::jsactionWithAction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "od", &arg0, &arg1);
		CCActionInterval* narg0; JSGET_PTRSHELL(CCActionInterval, narg0, arg0);
		CCEaseRateAction* ret = CCEaseRateAction::actionWithAction(narg0, arg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCEaseRateAction::jsClass, S_CCEaseRateAction::jsObject, NULL);
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

JSClass* S_CCGrid3DAction::jsClass = NULL;
JSObject* S_CCGrid3DAction::jsObject = NULL;

JSBool S_CCGrid3DAction::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCGrid3DAction::jsClass, S_CCGrid3DAction::jsObject, NULL);
	S_CCGrid3DAction *cobj = new S_CCGrid3DAction(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCGrid3DAction::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCGrid3DAction *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCGrid3DAction::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCGrid3DAction *cobj; JSGET_PTRSHELL(S_CCGrid3DAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCGrid3DAction::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCGrid3DAction *cobj; JSGET_PTRSHELL(S_CCGrid3DAction, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCGrid3DAction::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCGrid3DAction::jsPropertyGet, S_CCGrid3DAction::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("vertex", S_CCGrid3DAction::jsvertex, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("originalVertex", S_CCGrid3DAction::jsoriginalVertex, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCGridAction::jsObject,jsClass,S_CCGrid3DAction::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCGrid3DAction::jsvertex(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCGrid3DAction* self = NULL; JSGET_PTRSHELL(S_CCGrid3DAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		//INVALID RETURN TYPE _4E0
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCGrid3DAction::jsoriginalVertex(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCGrid3DAction* self = NULL; JSGET_PTRSHELL(S_CCGrid3DAction, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		ccGridSize* narg0; JSGET_PTRSHELL(ccGridSize, narg0, arg0);
		//INVALID RETURN TYPE _4E0
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSClass* S_CCBezierTo::jsClass = NULL;
JSObject* S_CCBezierTo::jsObject = NULL;

JSBool S_CCBezierTo::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S_CCBezierTo::jsClass, S_CCBezierTo::jsObject, NULL);
	S_CCBezierTo *cobj = new S_CCBezierTo(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S_CCBezierTo::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) ((S_CCBezierTo *)pt->data)->release();
		JS_free(cx, pt);
	}
}

JSBool S_CCBezierTo::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBezierTo *cobj; JSGET_PTRSHELL(S_CCBezierTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S_CCBezierTo::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCBezierTo *cobj; JSGET_PTRSHELL(S_CCBezierTo, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	default:
		break;
	}
	return JS_TRUE;
}

void S_CCBezierTo::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("startWithTarget", S_CCBezierTo::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithDuration", S_CCBezierTo::jsactionWithDuration, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCBezierBy::jsObject,jsClass,S_CCBezierTo::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCBezierTo::jsstartWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCBezierTo* self = NULL; JSGET_PTRSHELL(S_CCBezierTo, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->startWithTarget(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCBezierTo::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		double arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "do", &arg0, &arg1);
		ccBezierConfig* narg1; JSGET_PTRSHELL(ccBezierConfig, narg1, arg1);
		CCBezierTo* ret = CCBezierTo::actionWithDuration(arg0, *narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCBezierTo::jsClass, S_CCBezierTo::jsObject, NULL);
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

JSClass* S__ccGridSize::jsClass = NULL;
JSObject* S__ccGridSize::jsObject = NULL;

JSBool S__ccGridSize::jsConstructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_NewObject(cx, S__ccGridSize::jsClass, S__ccGridSize::jsObject, NULL);
	S__ccGridSize *cobj = new S__ccGridSize(obj);
	pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
	pt->flags = 0; pt->data = cobj;
	JS_SetPrivate(obj, pt);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	return JS_TRUE;
}

void S__ccGridSize::jsFinalize(JSContext *cx, JSObject *obj)
{
	pointerShell_t *pt = (pointerShell_t *)JS_GetPrivate(obj);
	if (pt) {
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S__ccGridSize *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S__ccGridSize::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S__ccGridSize *cobj; JSGET_PTRSHELL(S__ccGridSize, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kX:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->x, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kY:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->y, &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool S__ccGridSize::jsPropertySet(JSContext *cx, JSObject *obj, jsid _id, JSBool strict, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S__ccGridSize *cobj; JSGET_PTRSHELL(S__ccGridSize, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kX:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->x = tmp; } while (0);
		break;
	case kY:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->y = tmp; } while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

void S__ccGridSize::jsCreateClass(JSContext *cx, JSObject *globalObj, const char *name)
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
			{"x", kX, JSPROP_PERMANENT | JSPROP_SHARED, S__ccGridSize::jsPropertyGet, S__ccGridSize::jsPropertySet},
			{"y", kY, JSPROP_PERMANENT | JSPROP_SHARED, S__ccGridSize::jsPropertyGet, S__ccGridSize::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S__ccGridSize::jsConstructor,0,properties,funcs,NULL,st_funcs);
}


void register_enums_cocos2d_generated(JSObject *global) {
	JSContext *cx = ScriptingCore::getInstance().getGlobalContext();
}
