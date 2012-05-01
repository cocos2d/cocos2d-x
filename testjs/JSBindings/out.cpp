#include "out.hpp"

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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCAnimate *)pt->data;
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
			JS_FN("initWithDuration", S_CCAnimate::jsinitWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("startWithTarget", S_CCAnimate::jsstartWithTarget, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("stop", S_CCAnimate::jsstop, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("reverse", S_CCAnimate::jsreverse, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("actionWithAnimation", S_CCAnimate::jsactionWithAnimation, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("actionWithDuration", S_CCAnimate::jsactionWithDuration, 3, JSPROP_PERMANENT | JSPROP_SHARED),
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
JSBool S_CCAnimate::jsinitWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimate* self = NULL; JSGET_PTRSHELL(S_CCAnimate, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		bool arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "dob", &arg0, &arg1, &arg2);
		CCAnimation* narg1; JSGET_PTRSHELL(CCAnimation, narg1, arg1);
		bool ret = self->initWithDuration(arg0, narg1, arg2);
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
JSBool S_CCAnimate::jsactionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		double arg0;
		JSObject *arg1;
		bool arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "dob", &arg0, &arg1, &arg2);
		CCAnimation* narg1; JSGET_PTRSHELL(CCAnimation, narg1, arg1);
		CCAnimate* ret = CCAnimate::actionWithDuration(arg0, narg1, arg2);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCLayer *)pt->data;
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
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsTouchEnabled()));
		break;
	case kIsAccelerometerEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsAccelerometerEnabled()));
		break;
	case kIsKeypadEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsKeypadEnabled()));
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
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsTouchEnabled(tmp); } while (0);
		break;
	case kIsAccelerometerEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsAccelerometerEnabled(tmp); } while (0);
		break;
	case kIsKeypadEnabled:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsKeypadEnabled(tmp); } while (0);
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
				CCTouch *touch = new CCTouch(pt.x, pt.y);
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
			delete touches;
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
				CCTouch *touch = new CCTouch(pt.x, pt.y);
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
			delete touches;
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
				CCTouch *touch = new CCTouch(pt.x, pt.y);
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
			delete touches;
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
				CCTouch *touch = new CCTouch(pt.x, pt.y);
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
			delete touches;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		bool arg1;
		int arg2;
		bool arg3;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->unregisterScriptTouchHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCLayer::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBackInOut *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBackOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMenu *)pt->data;
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
				// don't know what this is (c ~> js, {:type=>"_45E", :getter=>#<CppMethod:0x00000101aeed48 @name="getColor", @static=false, @num_arguments=0, @arguments=[], @type="_2070", @klass=Class: CCMenu>, :setter=>#<CppMethod:0x00000101aedc40 @name="setColor", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2070"}], @type="_12", @klass=Class: CCMenu>, :requires_accessor=>true})
		break;
	case kOpacity:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getOpacity(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsOpacityModifyRGB()));
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
				// don't know what this is (js ~> c, _45B)
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
			JS_FN("initWithItems", S_CCMenu::jsinitWithItems, 2, JSPROP_PERMANENT | JSPROP_SHARED),
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsinitWithItems(JSContext *cx, uint32_t argc, jsval *vp) {
//	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
//	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
//	if (self == NULL) return JS_FALSE;
//	if (argc > 0) {
//		char *buff = (char *)malloc(sizeof(void *) * argc);
//		void *m = buff;
//		CCMenuItem *first = NULL;
//		jsval* argv = JS_ARGV(cx, vp);
//		int i=0;
//		while (argc--) {
//			JSObject *arg0 = JSVAL_TO_OBJECT(argv[i++]);
//			CCMenuItem* narg0; JSGET_PTRSHELL(CCMenuItem, narg0, arg0);
//			if (first == NULL) {
//				first = narg0;
//			} else {
//				(*(void **)) = (void *)narg0;
//				m += (int)sizeof(void *);
//			}
//		}
//		bool ret = self->initWithItems(first, buff);
//		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
//		
//		return JS_TRUE;
//	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenu::jsalignItemsVertically(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenu* self = NULL; JSGET_PTRSHELL(S_CCMenu, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCAction *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->stop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAction::jsaction(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMenuItemSprite *)pt->data;
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
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsOpacityModifyRGB()));
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
			JS_FN("initFromNormalSprite", S_CCMenuItemSprite::jsinitFromNormalSprite, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("selected", S_CCMenuItemSprite::jsselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("unselected", S_CCMenuItemSprite::jsunselected, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("itemFromNormalSprite", S_CCMenuItemSprite::jsitemFromNormalSprite, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMenuItem::jsObject,jsClass,S_CCMenuItemSprite::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemSprite::jsitemFromNormalSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 3) {
		JSObject *arg0;
		JSObject *arg1;
		JSObject *arg2;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "ooo", &arg0, &arg1, &arg2);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCNode* narg1; JSGET_PTRSHELL(CCNode, narg1, arg1);
		CCNode* narg2; JSGET_PTRSHELL(CCNode, narg2, arg2);
		CCMenuItemSprite* ret = CCMenuItemSprite::itemFromNormalSprite(narg0, narg1, narg2);
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
JSBool S_CCMenuItemSprite::jsinitFromNormalSprite(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemSprite* self = NULL; JSGET_PTRSHELL(S_CCMenuItemSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 2) {
		JSObject *arg0;
		JSObject *arg1;
		JSObject *arg2 = NULL;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "oo/o", &arg0, &arg1, &arg2);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		CCNode* narg1; JSGET_PTRSHELL(CCNode, narg1, arg1);
		CCNode* narg2 = NULL; if (argc == 3) JSGET_PTRSHELL(CCNode, narg2, arg2);
		bool ret = self->initFromNormalSprite(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemSprite::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->unselected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
MENU_ITEM_ACTION(S_CCMenuItemSprite)

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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSequence *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
JSBool S_CCSequence::jsactions(JSContext *cx, uint32_t argc, jsval *vp) {
	// just like CCSequence::actions
	if (argc > 0) {
		jsval* argv = JS_ARGV(cx, vp);
		// get first element
		S_CCSequence* prev;
		JSGET_PTRSHELL(S_CCSequence, prev, JSVAL_TO_OBJECT(argv[0]));
		for (int i=1; i < argc; i++) {
			CCFiniteTimeAction *next; JSGET_PTRSHELL(CCFiniteTimeAction, next, JSVAL_TO_OBJECT(argv[i]));
			prev = (S_CCSequence *)CCSequence::actionOneTwo(prev, next);
		}
		// wrap prev in an action
		// temporary because it's just a wrapper for an autoreleased object
		// or worst case, it's an already binded object (if it's just one item in the array)
		pointerShell_t* pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
		pt->flags = kPointerTemporary;
		pt->data = prev;
		JSObject* out = JS_NewObject(cx, S_CCSequence::jsClass, S_CCSequence::jsObject, NULL);
		prev->jsObject = out;
		JS_SetPrivate(out, pt);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(out));
		return JS_TRUE;
	}
	JS_ReportError(cx, "must call with at least one element");
	return JS_FALSE;
}
JSBool S_CCSequence::jsactionsWithArray(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCArray* narg0; JSGET_PTRSHELL(CCArray, narg0, arg0);
		CCFiniteTimeAction* ret = CCSequence::actionsWithArray(narg0);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSpriteFrame *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCAnimation *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCAnimation::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCAnimation *cobj; JSGET_PTRSHELL(S_CCAnimation, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kDelay:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getDelay(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
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
	case kDelay:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setDelay(tmp); } while (0);
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
			{"delay", kDelay, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimation::jsPropertyGet, S_CCAnimation::jsPropertySet},
			{"frames", kFrames, JSPROP_PERMANENT | JSPROP_SHARED, S_CCAnimation::jsPropertyGet, S_CCAnimation::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("initWithFrames", S_CCAnimation::jsinitWithFrames, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addFrame", S_CCAnimation::jsaddFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addFrameWithFileName", S_CCAnimation::jsaddFrameWithFileName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("addFrameWithTexture", S_CCAnimation::jsaddFrameWithTexture, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("init", S_CCAnimation::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("animation", S_CCAnimation::jsanimation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("animationWithFrames", S_CCAnimation::jsanimationWithFrames, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,NULL,jsClass,S_CCAnimation::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCAnimation::jsinitWithFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCMutableArray<CCSpriteFrame*>* narg0; JSGET_PTRSHELL(CCMutableArray<CCSpriteFrame*>, narg0, arg0);
		bool ret = self->initWithFrames(narg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteFrame* narg0; JSGET_PTRSHELL(CCSpriteFrame, narg0, arg0);
		self->addFrame(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddFrameWithFileName(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		self->addFrameWithFileName(narg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsaddFrameWithTexture(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCAnimation* self = NULL; JSGET_PTRSHELL(S_CCAnimation, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCTexture2D* narg0; JSGET_PTRSHELL(CCTexture2D, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		self->addFrameWithTexture(narg0, *narg1);
		
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCAnimation::jsanimation(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
JSBool S_CCAnimation::jsanimationWithFrames(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCMutableArray<CCSpriteFrame*>* narg0; JSGET_PTRSHELL(CCMutableArray<CCSpriteFrame*>, narg0, arg0);
		CCAnimation* ret = CCAnimation::animationWithFrames(narg0);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMenuItemImage *)pt->data;
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
			JS_FN("initFromNormalImage", S_CCMenuItemImage::jsinitFromNormalImage, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("itemFromNormalImage", S_CCMenuItemImage::jsitemFromNormalImage, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCMenuItemSprite::jsObject,jsClass,S_CCMenuItemImage::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItemImage::jsitemFromNormalImage(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		CCMenuItemImage* ret = CCMenuItemImage::itemFromNormalImage(narg0, narg1);
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
JSBool S_CCMenuItemImage::jsinitFromNormalImage(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemImage* self = NULL; JSGET_PTRSHELL(S_CCMenuItemImage, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 2) {
		JSString *arg0;
		JSString *arg1;
		JSString *arg2 = NULL;
		JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "SS/S", &arg0, &arg1, &arg2);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		char *narg2 = (arg2) ? JS_EncodeString(cx, arg2) : NULL;
		bool ret = self->initFromNormalImage(narg0, narg1, narg2, self, menu_selector(S_CCMenuItemImage::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
MENU_ITEM_ACTION(S_CCMenuItemImage)

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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCParticleSystem *)pt->data;
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
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsActive()));
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
				// don't know what this is (c ~> js, {:type=>"_4A5", :getter=>#<CppMethod:0x007fd552c02fe0 @name="getStartColor", @static=false, @num_arguments=0, @arguments=[], @type="_2F6F", @klass=Class: CCParticleSystem>, :setter=>#<CppMethod:0x007fd552c193a8 @name="setStartColor", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2F6F"}], @type="_12", @klass=Class: CCParticleSystem>, :requires_accessor=>true})
		break;
	case kStartColorVar:
				// don't know what this is (c ~> js, {:type=>"_4A5", :getter=>#<CppMethod:0x007fd552c186d8 @name="getStartColorVar", @static=false, @num_arguments=0, @arguments=[], @type="_2F6F", @klass=Class: CCParticleSystem>, :setter=>#<CppMethod:0x007fd552c17aa8 @name="setStartColorVar", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2F6F"}], @type="_12", @klass=Class: CCParticleSystem>, :requires_accessor=>true})
		break;
	case kEndColor:
				// don't know what this is (c ~> js, {:type=>"_4A5", :getter=>#<CppMethod:0x007fd552c16dd8 @name="getEndColor", @static=false, @num_arguments=0, @arguments=[], @type="_2F6F", @klass=Class: CCParticleSystem>, :setter=>#<CppMethod:0x007fd552c161a8 @name="setEndColor", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2F6F"}], @type="_12", @klass=Class: CCParticleSystem>, :requires_accessor=>true})
		break;
	case kEndColorVar:
				// don't know what this is (c ~> js, {:type=>"_4A5", :getter=>#<CppMethod:0x007fd552c154d8 @name="getEndColorVar", @static=false, @num_arguments=0, @arguments=[], @type="_2F6F", @klass=Class: CCParticleSystem>, :setter=>#<CppMethod:0x007fd552c2b878 @name="setEndColorVar", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2F6F"}], @type="_12", @klass=Class: CCParticleSystem>, :requires_accessor=>true})
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
	case kBlendFunc:
				// don't know what this is (c ~> js, {:type=>"_208F", :getter=>#<CppMethod:0x007fd552c6d840 @name="getBlendFunc", @static=false, @num_arguments=0, @arguments=[], @type="_5AC", @klass=Class: CCParticleSystem>, :setter=>#<CppMethod:0x007fd552c6cc10 @name="setBlendFunc", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_208F"}], @type="_12", @klass=Class: CCParticleSystem>, :requires_accessor=>true})
		break;
	case kIsBlendAdditive:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsBlendAdditive()));
		break;
	case kIsAutoRemoveOnFinish:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsAutoRemoveOnFinish()));
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
				// don't know what this is (c ~> js, {:type=>"_2F20", :getter=>#<CppMethod:0x007f8cf1e31a18 @name="getPositionType", @static=false, @num_arguments=0, @arguments=[], @type="_2ECF", @klass=Class: CCParticleSystem>, :requires_accessor=>true, :setter=>#<CppMethod:0x007f8cf1e309d8 @name="setPositionType", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2F20"}], @type="_12", @klass=Class: CCParticleSystem>})
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
				// don't know what this is (js ~> c, _4A2)
		break;
	case kStartColorVar:
				// don't know what this is (js ~> c, _4A2)
		break;
	case kEndColor:
				// don't know what this is (js ~> c, _4A2)
		break;
	case kEndColorVar:
				// don't know what this is (js ~> c, _4A2)
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
	case kBlendFunc:
				// don't know what this is (js ~> c, _5AC)
		break;
	case kIsBlendAdditive:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsBlendAdditive(tmp); } while (0);
		break;
	case kIsAutoRemoveOnFinish:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsAutoRemoveOnFinish(tmp); } while (0);
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
				// don't know what this is (js ~> c, _2ECF)
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

JSBool S_CCParticleSystem::jsparticleWithFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCParticleSystem* ret = CCParticleSystem::particleWithFile(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCParticleSystem::jsClass, S_CCParticleSystem::jsObject, NULL);
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->postStep();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCParticleSystem::jsupdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystem* self = NULL; JSGET_PTRSHELL(S_CCParticleSystem, self, obj);
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
void S_CCParticleSystem::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseElasticIn *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRotateBy *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseElastic *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMoveTo *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseElasticOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRotateTo *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseElasticInOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBounceIn *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSpriteFrameCache *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		CCSpriteFrameCache::purgeSharedSpriteFrameCache();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBounce *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBounceInOut *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBackIn *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseBounceOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseIn *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCFiniteTimeAction *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseOut *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCNode *)pt->data;
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
	case kPositionInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getPositionInPixels());
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
//	case kChildren:
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCArray::jsClass, S_CCArray::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)cobj->getChildren();
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		break;
	case kIsVisible:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsVisible()));
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
	case kAnchorPointInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getAnchorPointInPixels());
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
	case kContentSizeInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getContentSizeInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kIsRunning:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsRunning()));
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
	case kIsRelativeAnchorPoint:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsRelativeAnchorPoint()));
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
	case kPositionInPixels:
		do {
			CCPoint* tmp; JSGET_PTRSHELL(CCPoint, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setPositionInPixels(*tmp); }
		} while (0);
		break;
	case kSkewX:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewX(tmp); } while (0);
		break;
	case kSkewY:
		do { double tmp; JS_ValueToNumber(cx, *val, &tmp); cobj->setSkewY(tmp); } while (0);
		break;
	case kIsVisible:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsVisible(tmp); } while (0);
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
	case kContentSizeInPixels:
		do {
			CCSize* tmp; JSGET_PTRSHELL(CCSize, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setContentSizeInPixels(*tmp); }
		} while (0);
		break;
	case kParent:
		do {
			CCNode* tmp; JSGET_PTRSHELL(CCNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setParent(tmp); }
		} while (0);
		break;
	case kIsRelativeAnchorPoint:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsRelativeAnchorPoint(tmp); } while (0);
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
			{"positionInPixels", kPositionInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewX", kSkewX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"skewY", kSkewY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"children", kChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"grid", kGrid, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isVisible", kIsVisible, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"anchorPoint", kAnchorPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"anchorPointInPixels", kAnchorPointInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"contentSize", kContentSize, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"contentSizeInPixels", kContentSizeInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isRunning", kIsRunning, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"parent", kParent, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
			{"isRelativeAnchorPoint", kIsRelativeAnchorPoint, JSPROP_PERMANENT | JSPROP_SHARED, S_CCNode::jsPropertyGet, S_CCNode::jsPropertySet},
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
			JS_FN("boundingBoxInPixels", S_CCNode::jsboundingBoxInPixels, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->unregisterScriptHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCNode::jsaddChild(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc >= 1) {
		JSObject *arg0;
		int zorder = 0;
		int tag = 0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o/ii", &arg0, &zorder, &tag);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		self->addChild(narg0, zorder, tag);
		
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
		bool arg0;
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
		bool arg1;
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
		bool arg1;
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
		bool arg0;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
JSBool S_CCNode::jsboundingBoxInPixels(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCNode* self = NULL; JSGET_PTRSHELL(S_CCNode, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		CCRect* ret = new CCRect(self->boundingBoxInPixels());
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
void S_CCNode::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseExponentialIn *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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

JSBool S_CCFileUtils::jsgetFileData(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		unsigned long len;
		unsigned char *ret = CCFileUtils::getFileData(narg0, narg1, &len);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, (const char *)ret, len);
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));	
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFileUtils::jsfullPathFromRelativePath(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 1) {
		JSString *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "S", &arg0);
		char *narg0 = JS_EncodeString(cx, arg0);
		const char *ret = CCFileUtils::fullPathFromRelativePath(narg0);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCFileUtils::jsfullPathFromRelativeFile(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSString *arg0;
		JSString *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "SS", &arg0, &arg1);
		char *narg0 = JS_EncodeString(cx, arg0);
		char *narg1 = JS_EncodeString(cx, arg1);
		const char *ret = CCFileUtils::fullPathFromRelativeFile(narg0, narg1);
		if (ret == NULL) {
			JS_SET_RVAL(cx, vp, JSVAL_NULL);
			return JS_TRUE;
		}
		JSString *str = JS_NewStringCopyN(cx, ret, strlen(ret));
		JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));		
		return JS_TRUE;
		
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseInOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseExponentialOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCParticleSystemQuad *)pt->data;
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
			JS_FN("initIndices", S_CCParticleSystemQuad::jsinitIndices, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
JSBool S_CCParticleSystemQuad::jsinitIndices(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCParticleSystemQuad* self = NULL; JSGET_PTRSHELL(S_CCParticleSystemQuad, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->initIndices();
		
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCLabelTTF *)pt->data;
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

JSBool S_CCLabelTTF::jslabelWithString(JSContext *cx, uint32_t argc, jsval *vp) {
//	if (argc == 5) {
//		JSString *arg0;
//		JSObject *arg1;
//		JSObject *arg2;
//		JSString *arg3;
//		float arg4;
//		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "So*Sd", &arg0, &arg1, &arg2, &arg3, &arg4);
//		char *narg0 = JS_EncodeString(cx, arg0);
//		CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
//		char *narg3 = JS_EncodeString(cx, arg3);
//		CCLabelTTF* ret = CCLabelTTF::labelWithString(narg0, *narg1, *narg2, narg3, arg4);
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCLabelTTF::jsClass, S_CCLabelTTF::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)ret;
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		
//		return JS_TRUE;
//	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCLabelTTF::jsinitWithString(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCLabelTTF* self = NULL; JSGET_PTRSHELL(S_CCLabelTTF, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSString *arg0;
		JSObject *arg1;
		int arg2;
		JSString *arg3;
		double arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "SoiSd", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		CCSize* narg1; JSGET_PTRSHELL(CCSize, narg1, arg1);
		char *narg3 = JS_EncodeString(cx, arg3);
		bool ret = self->initWithString(narg0, *narg1, (CCTextAlignment)arg2, narg3, arg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCScene *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCScene::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCDirector *)pt->data;
		JS_free(cx, pt);
	}
}

JSBool S_CCDirector::jsPropertyGet(JSContext *cx, JSObject *obj, jsid _id, jsval *val)
{
	int32_t propId = JSID_TO_INT(_id);
	S_CCDirector *cobj; JSGET_PTRSHELL(S_CCDirector, cobj, obj);
	if (!cobj) return JS_FALSE;
	switch(propId) {
	case kFrames:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getFrames(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
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
				// don't know what this is (c ~> js, {:type=>"_2526", :getter=>#<CppMethod:0x007f8cf1bfe480 @name="getProjection", @static=false, @num_arguments=0, @arguments=[], @type="_24D5", @klass=Class: CCDirector>, :requires_accessor=>true, :setter=>#<CppMethod:0x007f8cf1bfd2b0 @name="setProjection", @static=false, @num_arguments=1, @arguments=[{:name=>"kProjection", :type=>"_2526"}], @type="_12", @klass=Class: CCDirector>})
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
	case kDisplaySizeInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCSize::jsClass, S_CCSize::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCSize* ctmp = new CCSize(cobj->getDisplaySizeInPixels());
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
				// don't know what this is (c ~> js, {:type=>"_2531", :getter=>#<CppMethod:0x007f8cf213fbd8 @name="getDeviceOrientation", @static=false, @num_arguments=0, @arguments=[], @type="_24F3", @klass=Class: CCDirector>, :requires_accessor=>true, :setter=>#<CppMethod:0x007f8cf213e418 @name="setDeviceOrientation", @static=false, @num_arguments=1, @arguments=[{:name=>"kDeviceOrientation", :type=>"_2531"}], @type="_12", @klass=Class: CCDirector>})
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
	case kDisplayFPS:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDisplayFPS(tmp); } while (0);
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
				// don't know what this is (js ~> c, _24D5)
		break;
	case kDeviceOrientation:
				// don't know what this is (js ~> c, _24F3)
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
			{"displayFPS", kDisplayFPS, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
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
			{"displaySizeInPixels", kDisplaySizeInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"zEye", kZEye, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{"deviceOrientation", kDeviceOrientation, JSPROP_PERMANENT | JSPROP_SHARED, S_CCDirector::jsPropertyGet, S_CCDirector::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("init", S_CCDirector::jsinit, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDisplayFPS", S_CCDirector::jsisDisplayFPS, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
			JS_FN("showProfilers", S_CCDirector::jsshowProfilers, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("applyOrientation", S_CCDirector::jsapplyOrientation, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("enableRetinaDisplay", S_CCDirector::jsenableRetinaDisplay, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isRetinaDisplay", S_CCDirector::jsisRetinaDisplay, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->init();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisDisplayFPS(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->isDisplayFPS();
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->mainLoop();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsshowProfilers(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->showProfilers();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsapplyOrientation(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->applyOrientation();
		
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
		bool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		bool ret = self->enableRetinaDisplay(arg0);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jsisRetinaDisplay(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCDirector* self = NULL; JSGET_PTRSHELL(S_CCDirector, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->isRetinaDisplay();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCDirector::jssharedDirector(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseExponentialInOut *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCParticleSystemPoint *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->draw();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseSineIn *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMenuItem *)pt->data;
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
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsSelected()));
		break;
	case kIsEnabled:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsEnabled()));
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
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setIsEnabled(tmp); } while (0);
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
			JS_FN("itemWithTarget", S_CCMenuItem::jsitemWithTarget, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCMenuItem::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCMenuItem::jsitemWithTarget(JSContext *cx, uint32_t argc, jsval *vp) {
//	if (argc == 1) {
//		JSObject *arg0;
//		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
//		CCObject* narg0; JSGET_PTRSHELL(CCObject, narg0, arg0);
//		CCMenuItem* ret = CCMenuItem::itemWithTarget(narg0, NULL);
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCMenuItem::jsClass, S_CCMenuItem::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)ret;
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		
//		return JS_TRUE;
//	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsinit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		bool ret = self->initWithTarget(self, menu_selector(S_CCMenuItem::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItem::jsrect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItem* self = NULL; JSGET_PTRSHELL(S_CCMenuItem, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->unregisterScriptHandler();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCMenuItem::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMoveBy *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseSineOut *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCActionInterval *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRepeatForever *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseSineInOut *)pt->data;
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCRenderTexture *)pt->data;
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
			JS_FN("saveBuffer", S_CCRenderTexture::jssaveBuffer, 5, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("renderTextureWithWidthAndHeight", S_CCRenderTexture::jsrenderTextureWithWidthAndHeight, 3, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCRenderTexture::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCRenderTexture::jsrenderTextureWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		int arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
		CCRenderTexture* ret = CCRenderTexture::renderTextureWithWidthAndHeight(arg0, arg1);
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCRenderTexture::jsClass, S_CCRenderTexture::jsObject, NULL);
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
JSBool S_CCRenderTexture::jsinitWithWidthAndHeight(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		int arg0;
		int arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "ii", &arg0, &arg1);
		bool ret = self->initWithWidthAndHeight(arg0, arg1, kCCTexture2DPixelFormat_RGBA8888);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCRenderTexture::jsbegin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
	if (argc == 1) {
		bool arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "b", &arg0);
		self->end(arg0);
		
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
JSBool S_CCRenderTexture::jssaveBuffer(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCRenderTexture* self = NULL; JSGET_PTRSHELL(S_CCRenderTexture, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 5) {
		JSString *arg0;
		int arg1;
		int arg2;
		int arg3;
		int arg4;
		JS_ConvertArguments(cx, 5, JS_ARGV(cx, vp), "Siiii", &arg0, &arg1, &arg2, &arg3, &arg4);
		char *narg0 = JS_EncodeString(cx, arg0);
		bool ret = self->saveBuffer(narg0, arg1, arg2, arg3, arg4);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
void S_CCRenderTexture::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCActionEase *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCMenuItemLabel *)pt->data;
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
				// don't know what this is (c ~> js, {:type=>"_45E", :getter=>#<CppMethod:0x0000010182b0e8 @name="getDisabledColor", @static=false, @num_arguments=0, @arguments=[], @type="_2070", @klass=Class: CCMenuItemLabel>, :setter=>#<CppMethod:0x00000101829540 @name="setDisabledColor", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2070"}], @type="_12", @klass=Class: CCMenuItemLabel>, :requires_accessor=>true})
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
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsOpacityModifyRGB()));
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
				// don't know what this is (js ~> c, _45B)
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

JSBool S_CCMenuItemLabel::jsitemWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
//	if (argc == 3) {
//		JSObject *arg0;
//		JSObject *arg1;
//		JSObject *arg2;
//		JS_ConvertArguments(cx, 3, JS_ARGV(cx, vp), "oo*", &arg0, &arg1, &arg2);
//		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
//		CCObject* narg1; JSGET_PTRSHELL(CCObject, narg1, arg1);
//		CCMenuItemLabel* ret = CCMenuItemLabel::itemWithLabel(narg0, narg1, *narg2);
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCMenuItemLabel::jsClass, S_CCMenuItemLabel::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)ret;
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		
//		return JS_TRUE;
//	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItemLabel::jsinitWithLabel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCNode* narg0; JSGET_PTRSHELL(CCNode, narg0, arg0);
		bool ret = self->initWithLabel(narg0, self, menu_selector(S_CCMenuItemLabel::menuAction));
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCMenuItemLabel::jsactivate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCMenuItemLabel* self = NULL; JSGET_PTRSHELL(S_CCMenuItemLabel, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->unselected();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
MENU_ITEM_ACTION(S_CCMenuItemLabel)

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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSet *)pt->data;
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
			JS_FN("anyObject", S_CCSet::jsanyObject, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		//INVALID RETURN TYPE _3EF6
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSet::jsanyObject(JSContext *cx, uint32_t argc, jsval *vp) {
//	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
//	S_CCSet* self = NULL; JSGET_PTRSHELL(S_CCSet, self, obj);
//	if (self == NULL) return JS_FALSE;
//	if (argc == 0) {
//		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
//		CCObject* ret = self->anyObject();
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCObject::jsClass, S_CCObject::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)ret;
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		
//		return JS_TRUE;
//	}
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCTouch *)pt->data;
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
			JS_FN("SetTouchInfo", S_CCTouch::jsSetTouchInfo, 2, JSPROP_PERMANENT | JSPROP_SHARED),
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
	if (argc == 2) {
		double arg0;
		double arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "dd", &arg0, &arg1);
		self->SetTouchInfo(arg0, arg1);
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCSprite *)pt->data;
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
				// don't know what this is (c ~> js, {:type=>"_45E", :getter=>#<CppMethod:0x000001020557a0 @name="getColor", @static=false, @num_arguments=0, @arguments=[], @type="_2070", @klass=Class: CCSprite>, :setter=>#<CppMethod:0x0000010203d088 @name="setColor", @static=false, @num_arguments=1, @arguments=[{:name=>"var", :type=>"_2070"}], @type="_12", @klass=Class: CCSprite>, :requires_accessor=>true})
		break;
	case kAtlasIndex:
		do { jsval tmp; JS_NewNumberValue(cx, cobj->getAtlasIndex(), &tmp); JS_SET_RVAL(cx, val, tmp); } while (0);
		break;
	case kBlendFunc:
				// don't know what this is (c ~> js, {:type=>"_208F", :getter=>#<CppMethod:0x00000101bd4b68 @name="getBlendFunc", @static=false, @num_arguments=0, @arguments=[], @type="_5AC", @klass=Class: CCSprite>, :setter=>#<CppMethod:0x00000101bd2110 @name="setBlendFunc", @static=false, @num_arguments=1, @arguments=[{:name=>"blendFunc", :type=>"_208F"}], @type="_12", @klass=Class: CCSprite>, :requires_accessor=>true})
		break;
	case kOffsetPositionInPixels:
		do {
			JSObject *tmp = JS_NewObject(cx, S_CCPoint::jsClass, S_CCPoint::jsObject, NULL);
			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
			CCPoint* ctmp = new CCPoint(cobj->getOffsetPositionInPixels());
			pt->flags = 0;
			pt->data = (void *)ctmp;
			JS_SetPrivate(tmp, pt);
			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
		} while (0);
		break;
	case kQuad:
				// don't know what this is (c ~> js, {:type=>"_2930", :getter=>#<CppMethod:0x00000101c3c948 @name="getQuad", @static=false, @num_arguments=0, @arguments=[], @type="_587", @klass=Class: CCSprite>, :setter=>nil, :requires_accessor=>true})
		break;
//	case kSpriteBatchNode:
//		do {
//			JSObject *tmp = JS_NewObject(cx, S_CCSpriteBatchNode::jsClass, S_CCSpriteBatchNode::jsObject, NULL);
//			pointerShell_t *pt = (pointerShell_t *)JS_malloc(cx, sizeof(pointerShell_t));
//			pt->flags = kPointerTemporary;
//			pt->data = (void *)cobj->getSpriteBatchNode();
//			JS_SetPrivate(tmp, pt);
//			JS_SET_RVAL(cx, val, OBJECT_TO_JSVAL(tmp));
//		} while (0);
//		break;
	case kHonorParentTransform:
				// don't know what this is (c ~> js, {:type=>"_2991", :getter=>#<CppMethod:0x007f8cf1c64af0 @name="getHonorParentTransform", @static=false, @num_arguments=0, @arguments=[], @type="_2984", @klass=Class: CCSprite>, :requires_accessor=>true, :setter=>#<CppMethod:0x007f8cf1c634c0 @name="setHonorParentTransform", @static=false, @num_arguments=1, @arguments=[{:name=>"eHonorParentTransform", :type=>"_2991"}], @type="_12", @klass=Class: CCSprite>})
		break;
	case kIsOpacityModifyRGB:
		JS_SET_RVAL(cx, val, BOOLEAN_TO_JSVAL(cobj->getIsOpacityModifyRGB()));
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
				// don't know what this is (js ~> c, _45B)
		break;
	case kAtlasIndex:
		do { uint32_t tmp; JS_ValueToECMAUint32(cx, *val, &tmp); cobj->setAtlasIndex(tmp); } while (0);
		break;
	case kDirty:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setDirty(tmp); } while (0);
		break;
	case kBlendFunc:
				// don't know what this is (js ~> c, _5AC)
		break;
	case kFlipX:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipX(tmp); } while (0);
		break;
	case kFlipY:
		do { JSBool tmp; JS_ValueToBoolean(cx, *val, &tmp); cobj->setFlipY(tmp); } while (0);
		break;
	case kSpriteBatchNode:
		do {
			CCSpriteBatchNode* tmp; JSGET_PTRSHELL(CCSpriteBatchNode, tmp, JSVAL_TO_OBJECT(*val));
			if (tmp) { cobj->setSpriteBatchNode(tmp); }
		} while (0);
		break;
	case kHonorParentTransform:
				// don't know what this is (js ~> c, _2984)
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
			{"atlasIndex", kAtlasIndex, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"batchNode", kBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"transform", kTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"dirty", kDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"recursiveDirty", kRecursiveDirty, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"hasChildren", kHasChildren, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"blendFunc", kBlendFunc, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"usesBatchNode", kUsesBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rect", kRect, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rectInPixels", kRectInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"rectRotated", kRectRotated, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"offsetPositionInPixels", kOffsetPositionInPixels, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"unflippedOffsetPositionFromCenter", kUnflippedOffsetPositionFromCenter, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"quad", kQuad, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"colorUnmodified", kColorUnmodified, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"opacityModifyRGB", kOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipX", kFlipX, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"flipY", kFlipY, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"spriteBatchNode", kSpriteBatchNode, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"honorParentTransform", kHonorParentTransform, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{"isOpacityModifyRGB", kIsOpacityModifyRGB, JSPROP_PERMANENT | JSPROP_SHARED, S_CCSprite::jsPropertyGet, S_CCSprite::jsPropertySet},
			{0, 0, 0, 0, 0}
		};

		static JSFunctionSpec funcs[] = {
			JS_FN("draw", S_CCSprite::jsdraw, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isDirty", S_CCSprite::jsisDirty, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isTextureRectRotated", S_CCSprite::jsisTextureRectRotated, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isUsesBatchNode", S_CCSprite::jsisUsesBatchNode, 0, JSPROP_PERMANENT | JSPROP_SHARED),
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
			JS_FN("initWithBatchNode", S_CCSprite::jsinitWithBatchNode, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("initWithBatchNodeRectInPixels", S_CCSprite::jsinitWithBatchNodeRectInPixels, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("updateTransform", S_CCSprite::jsupdateTransform, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("useSelfRender", S_CCSprite::jsuseSelfRender, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("useBatchNode", S_CCSprite::jsuseBatchNode, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("isFrameDisplayed", S_CCSprite::jsisFrameDisplayed, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("displayedFrame", S_CCSprite::jsdisplayedFrame, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

		static JSFunctionSpec st_funcs[] = {
			JS_FN("spriteWithTexture", S_CCSprite::jsspriteWithTexture, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrame", S_CCSprite::jsspriteWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithSpriteFrameName", S_CCSprite::jsspriteWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithFile", S_CCSprite::jsspriteWithFile, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("spriteWithBatchNode", S_CCSprite::jsspriteWithBatchNode, 2, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FS_END
		};

	jsObject = JS_InitClass(cx,globalObj,S_CCNode::jsObject,jsClass,S_CCSprite::jsConstructor,0,properties,funcs,NULL,st_funcs);
}

JSBool S_CCSprite::jsdraw(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->isTextureRectRotated();
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsisUsesBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		bool ret = self->isUsesBatchNode();
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
JSBool S_CCSprite::jsspriteWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		CCSprite* ret = CCSprite::spriteWithBatchNode(narg0, *narg1);
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		bool arg1;
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
		bool arg0;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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
JSBool S_CCSprite::jsinitWithBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		bool ret = self->initWithBatchNode(narg0, *narg1);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsinitWithBatchNodeRectInPixels(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 2) {
		JSObject *arg0;
		JSObject *arg1;
		JS_ConvertArguments(cx, 2, JS_ARGV(cx, vp), "oo", &arg0, &arg1);
		CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
		CCRect* narg1; JSGET_PTRSHELL(CCRect, narg1, arg1);
		bool ret = self->initWithBatchNodeRectInPixels(narg0, *narg1);
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->updateTransform();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsuseSelfRender(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		self->useSelfRender();
		
		JS_SET_RVAL(cx, vp, JSVAL_TRUE);
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}
JSBool S_CCSprite::jsuseBatchNode(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 1) {
		JSObject *arg0;
		JS_ConvertArguments(cx, 1, JS_ARGV(cx, vp), "o", &arg0);
		CCSpriteBatchNode* narg0; JSGET_PTRSHELL(CCSpriteBatchNode, narg0, arg0);
		self->useBatchNode(narg0);
		
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
JSBool S_CCSprite::jsdisplayedFrame(JSContext *cx, uint32_t argc, jsval *vp) {
	JSObject* obj = (JSObject *)JS_THIS_OBJECT(cx, vp);
	S_CCSprite* self = NULL; JSGET_PTRSHELL(S_CCSprite, self, obj);
	if (self == NULL) return JS_FALSE;
	if (argc == 0) {
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
		CCSpriteFrame* ret = self->displayedFrame();
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
void S_CCSprite::update(ccTime delta) {
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
		if (!(pt->flags & kPointerTemporary) && pt->data) delete (S_CCEaseRateAction *)pt->data;
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
		JS_ConvertArguments(cx, 0, JS_ARGV(cx, vp), "");
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

