//
//  S_CCActions.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/19/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include "S_CCActions.h"
#include "ScriptingCore.h"

#define JSTOF(n) JSValueToNumber(ctx, arguments[n], NULL)

// set and protect (avoid GC) for the actions
#define SET_PROTECT_JS(result, obj) do { \
	if (result) { \
		jsObject = obj; \
		JSValueProtect(ctx, jsObject); \
	} \
} while (0)

#pragma mark - CCAction

JSClassRef js_S_CCAction_class;

using namespace cocos2d;

SCRIPTABLE_BOILERPLATE_IMP(S_CCAction)

JSStaticFunction* S_CCAction::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"isDone", S_CCAction::jsIsDone, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"startWithTarget", S_CCAction::jsStartWithTarget, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"stop", S_CCAction::jsStop, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	
	return funcs;
}

bool S_CCAction::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	jsObject = obj;
	return true;
}

JS_STATIC_FUNC_IMP(S_CCAction, jsIsDone)
{
	CCAction *act = (CCAction *)JSObjectGetPrivate(thisObject);
	if (act) {
		return JSValueMakeBoolean(ctx, act->isDone());
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAction, jsStartWithTarget)
{
	CCAction *act = (CCAction *)JSObjectGetPrivate(thisObject);
	if (act && argumentCount == 1) {
		JSObjectRef jsTarget = JSValueToObject(ctx, arguments[0], NULL);
		CCNode *target = (CCNode *)JSObjectGetPrivate(jsTarget);
		if (target) {
			act->startWithTarget(target);
		}
	}
	return thisObject;
}

JS_STATIC_FUNC_IMP(S_CCAction, jsStop)
{
	CCAction *act = (CCAction *)JSObjectGetPrivate(thisObject);
	if (act) {
		act->stop();
	}
	return thisObject;
}

#pragma mark - CCSequence

JSClassRef js_S_CCSequence_class;

JSObjectRef S_CCSequence::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	return NULL;
}

bool S_CCSequence::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	return false;
}

JSValueRef S_CCSequence::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	return JSValueMakeUndefined(ctx);
}


JSStaticFunction* S_CCSequence::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"actions", S_CCSequence::jsActions, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCSequence::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	return false;
}

/**
 * var seq = CCSequence.actions(action1, action2, action3, ...);
 * node.runAction(seq);
 */
JS_STATIC_FUNC_IMP(S_CCSequence, jsActions)
{
	if (argumentCount > 0) {
		int idx = 0;
		JSObjectRef prev = JSValueToObject(ctx, arguments[0], NULL);
		JSObjectRef pnow = NULL;
		while (idx < argumentCount - 1) {
			pnow = JSValueToObject(ctx, arguments[++idx], NULL);
			// need to create an action here, with prev & pnow
			CCFiniteTimeAction *cc1 = (CCFiniteTimeAction *)JSObjectGetPrivate(prev);
			CCFiniteTimeAction *cc2 = (CCFiniteTimeAction *)JSObjectGetPrivate(pnow);
			CCSequence *seq = CCSequence::actionOneTwo(cc1, cc2);

			JSObjectRef obj = JSObjectMake(ctx, js_S_CCSequence_class, NULL);
			JSObjectSetPrivate(obj, seq);
			prev = obj;
		}
		return prev;
	}
	return JSValueMakeUndefined(ctx);
}

#pragma mark - CCRepeat

JSClassRef js_S_CCRepeat_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCRepeat)

JSStaticFunction* S_CCRepeat::jsStaticFunctions()
{
	return NULL;
}

bool S_CCRepeat::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		CCAction *action = (CCAction *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		CCFiniteTimeAction *fAction = dynamic_cast<CCFiniteTimeAction *>(action);
		if (action) {
			int times = JSValueToNumber(ctx, arguments[1], NULL);
			result = CCRepeat::initWithAction(fAction, times);
		} else {
			result = false;
		}
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

S_CCRepeat::~S_CCRepeat()
{
	S_CCAction *action = (S_CCAction *)m_pInnerAction;
	JSValueRef val = action->jsObject;
	JSGlobalContextRef ctx = GLOBAL_CTX;
	if (val) {
		JSValueUnprotect(ctx, val);
	}
	// unprotect our js-object
	if (jsObject) {
		JSValueUnprotect(ctx, jsObject);
	}
}

#pragma mark - CCRepeatForever

JSClassRef js_S_CCRepeatForever_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCRepeatForever)

JSStaticFunction* S_CCRepeatForever::jsStaticFunctions()
{
	return NULL;
}

bool S_CCRepeatForever::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		CCActionInterval *action = (CCActionInterval *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		if (action && (result = CCRepeatForever::initWithAction(action))) {
			JSValueProtect(ctx, arguments[0]);
		}
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

S_CCRepeatForever::~S_CCRepeatForever()
{
	S_CCAction *action = (S_CCAction *)m_pInnerAction;
	JSValueRef val = action->jsObject;
	JSGlobalContextRef ctx = GLOBAL_CTX;
	if (val) {
		JSValueUnprotect(ctx, val);
	}
	// unprotect our js-object
	if (jsObject) {
		JSValueUnprotect(ctx, jsObject);
	}
}


#pragma mark - CCSpawn

JSClassRef js_S_CCSpawn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSpawn)

JSStaticFunction* S_CCSpawn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSpawn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	return false;
}

/**
 * var actions = CCSpawn.actions(action1, action2, action3, ...);
 * node.runAction(actions);
 */
JS_STATIC_FUNC_IMP(S_CCSpawn, jsActions)
{
	if (argumentCount > 0) {
		int idx = 0;
		JSObjectRef prev = JSValueToObject(ctx, arguments[0], NULL);
		JSObjectRef pnow = NULL;
		while (idx < argumentCount - 1) {
			pnow = JSValueToObject(ctx, arguments[++idx], NULL);
			// need to create an action here, with prev & pnow
			CCFiniteTimeAction *cc1 = (CCFiniteTimeAction *)JSObjectGetPrivate(prev);
			CCFiniteTimeAction *cc2 = (CCFiniteTimeAction *)JSObjectGetPrivate(pnow);
			CCSpawn *seq = CCSpawn::actionOneTwo(cc1, cc2);
			
			JSObjectRef obj = JSObjectMake(ctx, js_S_CCSpawn_class, NULL);
			JSObjectSetPrivate(obj, seq);
			prev = obj;
		}
		return prev;
	}
	return JSValueMakeUndefined(ctx);
}

#pragma mark - CCRotateTo

JSClassRef js_S_CCRotateTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCRotateTo)

JSStaticFunction* S_CCRotateTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCRotateTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		float deltaAngle = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCRotateTo::initWithDuration(duration, deltaAngle);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCRotateBy

JSClassRef js_S_CCRotateBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCRotateBy)

JSStaticFunction* S_CCRotateBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCRotateBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		float deltaAngle = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCRotateBy::initWithDuration(duration, deltaAngle);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCMoveTo

JSClassRef js_S_CCMoveTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMoveTo)

JSStaticFunction* S_CCMoveTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCMoveTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		result = CCMoveTo::initWithDuration(duration, *pt);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCMoveBy

JSClassRef js_S_CCMoveBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCMoveBy)

JSStaticFunction* S_CCMoveBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCMoveBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		result = CCMoveBy::initWithDuration(duration, *pt);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCSkewTo

JSClassRef js_S_CCSkewTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSkewTo)

JSStaticFunction* S_CCSkewTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSkewTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		float sx = JSValueToNumber(ctx, arguments[1], NULL);
		float sy = JSValueToNumber(ctx, arguments[2], NULL);
		result = CCSkewTo::initWithDuration(t, sx, sy);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCSkewBy

JSClassRef js_S_CCSkewBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSkewBy)

JSStaticFunction* S_CCSkewBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSkewBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		float sx = JSValueToNumber(ctx, arguments[1], NULL);
		float sy = JSValueToNumber(ctx, arguments[2], NULL);
		result = CCSkewBy::initWithDuration(t, sx, sy);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCJumpBy

JSClassRef js_S_CCJumpBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCJumpBy)

JSStaticFunction* S_CCJumpBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCJumpBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		ccTime height = JSValueToNumber(ctx, arguments[2], NULL);
		int jumps = JSValueToNumber(ctx, arguments[3], NULL);
		result = CCJumpBy::initWithDuration(duration, *pt, height, jumps);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCJumpTo

JSClassRef js_S_CCJumpTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCJumpTo)

JSStaticFunction* S_CCJumpTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCJumpTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		ccTime height = JSValueToNumber(ctx, arguments[2], NULL);
		int jumps = JSValueToNumber(ctx, arguments[3], NULL);
		result = CCJumpTo::initWithDuration(duration, *pt, height, jumps);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCBezierBy

JSClassRef js_S_CCBezierBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCBezierBy)

JSStaticFunction* S_CCBezierBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCBezierBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccBezierConfig config;
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt1 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		CCPoint *pt2 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		CCPoint *ptEnd = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[3]);
		config.controlPoint_1 = *pt1;
		config.controlPoint_2 = *pt2;
		config.endPosition = *ptEnd;
		result = CCBezierBy::initWithDuration(t, config);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCBezierTo

JSClassRef js_S_CCBezierTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCBezierTo)

JSStaticFunction* S_CCBezierTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCBezierTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccBezierConfig config;
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCPoint *pt1 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		CCPoint *pt2 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		CCPoint *ptEnd = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[3]);
		config.controlPoint_1 = *pt1;
		config.controlPoint_2 = *pt2;
		config.endPosition = *ptEnd;
		result = CCBezierTo::initWithDuration(t, config);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCScaleTo

JSClassRef js_S_CCScaleTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCScaleTo)

JSStaticFunction* S_CCScaleTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCScaleTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		float s = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCScaleTo::initWithDuration(t, s);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCScaleBy

JSClassRef js_S_CCScaleBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCScaleBy)

JSStaticFunction* S_CCScaleBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCScaleBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		float s = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCScaleBy::initWithDuration(t, s);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCBlink

JSClassRef js_S_CCBlink_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCBlink)

JSStaticFunction* S_CCBlink::jsStaticFunctions()
{
	return NULL;
}

bool S_CCBlink::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		int blinks = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCBlink::initWithDuration(duration, blinks);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeIn

JSClassRef js_S_CCFadeIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeIn)

JSStaticFunction* S_CCFadeIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		result = CCFadeIn::initWithDuration(duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeOut

JSClassRef js_S_CCFadeOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeOut)

JSStaticFunction* S_CCFadeOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		result = CCFadeOut::initWithDuration(duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeTo

JSClassRef js_S_CCFadeTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeTo)

JSStaticFunction* S_CCFadeTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		int opacity = JSValueToNumber(ctx, arguments[1], NULL);
		result = CCFadeTo::initWithDuration(duration, opacity & 0xff);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCTintTo

JSClassRef js_S_CCTintTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTintTo)

JSStaticFunction* S_CCTintTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTintTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		int r = JSValueToNumber(ctx, arguments[1], NULL);
		int g = JSValueToNumber(ctx, arguments[2], NULL);
		int b = JSValueToNumber(ctx, arguments[3], NULL);
		result = CCTintTo::initWithDuration(duration, r, g, b);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCTintBy

JSClassRef js_S_CCTintBy_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTintBy)

JSStaticFunction* S_CCTintBy::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTintBy::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 4) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		int r = JSValueToNumber(ctx, arguments[1], NULL);
		int g = JSValueToNumber(ctx, arguments[2], NULL);
		int b = JSValueToNumber(ctx, arguments[3], NULL);
		result = CCTintBy::initWithDuration(duration, r, g, b);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCDelayTime

JSClassRef js_S_CCDelayTime_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCDelayTime)

JSStaticFunction* S_CCDelayTime::jsStaticFunctions()
{
	return NULL;
}

bool S_CCDelayTime::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		ccTime duration = JSValueToNumber(ctx, arguments[0], NULL);
		result = CCDelayTime::initWithDuration(duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCReverseTime

JSClassRef js_S_CCReverseTime_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCReverseTime)

JSStaticFunction* S_CCReverseTime::jsStaticFunctions()
{
	return NULL;
}

bool S_CCReverseTime::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		CCFiniteTimeAction *action = (CCFiniteTimeAction *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		result = CCReverseTime::initWithAction(action);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCAnimate

JSClassRef js_S_CCAnimate_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCAnimate)

JSStaticFunction* S_CCAnimate::jsStaticFunctions()
{
	return NULL;
}

bool S_CCAnimate::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount > 0) {
		CCAnimation *animation = (CCAnimation *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		bool restoreOriginalFrame = false;
		if (argumentCount == 2) {
			restoreOriginalFrame = JSValueToBoolean(ctx, arguments[1]);
		}
		result = CCAnimate::initWithAnimation(animation, restoreOriginalFrame);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCCallFunc

JSClassRef js_S_CCCallFunc_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCCallFunc)

JSStaticFunction* S_CCCallFunc::jsStaticFunctions()
{
	return NULL;
}

/**
 * target MUST be a CCNode
 * 
 * var callFunc = new CCCallFunc(function () {});  // <~ `this' in the function is the callFunc object
 */
bool S_CCCallFunc::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	if (argumentCount == 1) {
		JSObjectRef func = JSValueToObject(ctx, arguments[0], NULL);
		if (!JSObjectIsFunction(ctx, func) || !CCCallFunc::initWithTarget(this)) {
			return false;
		}
		m_pCallFunc = callfunc_selector(S_CCCallFunc::callfunc);
		// store the callback on the object
		JSValueProtect(ctx, func);
		callback = func;
		
		jsObject = obj;
		return true;
	}
	return false;
}

S_CCCallFunc::~S_CCCallFunc()
{
	if (jsObject) {
		JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
		JSValueUnprotect(ctx, callback);
	}
}

void S_CCCallFunc::callfunc()
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	JSObjectCallAsFunction(ctx, callback, NULL, 0, NULL, NULL);
}

#pragma mark - CCActionCamera

JSClassRef js_S_CCActionCamera_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCActionCamera)

JSStaticFunction* S_CCActionCamera::jsStaticFunctions()
{
	return NULL;
}

bool S_CCActionCamera::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCActionCamera::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	jsObject = obj;
	return result;
}

#pragma mark - CCOrbitCamera

JSClassRef js_S_CCOrbitCamera_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCOrbitCamera)


JSStaticFunction* S_CCOrbitCamera::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"sphericalRadius", S_CCOrbitCamera::jsSphericalRadius, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCOrbitCamera::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 7 &&
		CCOrbitCamera::initWithDuration(JSTOF(0), JSTOF(1), JSTOF(1), JSTOF(2), JSTOF(3), JSTOF(4), JSTOF(5))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

JS_STATIC_FUNC_IMP(S_CCOrbitCamera, jsSphericalRadius)
{
	//		void sphericalRadius(float *r, float *zenith, float *azimuth);
	
	if (argumentCount == 3) {
		CCOrbitCamera* self = (CCOrbitCamera *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		float r, zenith, azimuth;
		self->sphericalRadius(&r, &zenith, &azimuth);
		JSValueRef args[3] = {
			JSValueMakeNumber(ctx, r),
			JSValueMakeNumber(ctx, zenith),
			JSValueMakeNumber(ctx, azimuth)
		};
		return JSObjectMakeArray(ctx, 3, args, NULL);
	}
	return JSValueMakeUndefined(ctx);
}

#pragma mark - CCActionEase

JSClassRef js_S_CCActionEase_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCActionEase)


JSStaticFunction* S_CCActionEase::jsStaticFunctions()
{
	return NULL;
}

bool S_CCActionEase::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCActionEase::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	jsObject = obj;
	return result;
}

#pragma mark - CCEaseRateAction

JSClassRef js_S_CCEaseRateAction_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseRateAction)

JSStaticFunction* S_CCEaseRateAction::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseRateAction::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseRateAction::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseIn

JSClassRef js_S_CCEaseIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseIn)

JSStaticFunction* S_CCEaseIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseOut

JSClassRef js_S_CCEaseOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseOut)

JSStaticFunction* S_CCEaseOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseInOut

JSClassRef js_S_CCEaseInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseInOut)

JSStaticFunction* S_CCEaseInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseExponentialIn

JSClassRef js_S_CCEaseExponentialIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseExponentialIn)

JSStaticFunction* S_CCEaseExponentialIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseExponentialIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseExponentialIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseExponentialOut

JSClassRef js_S_CCEaseExponentialOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseExponentialOut)

JSStaticFunction* S_CCEaseExponentialOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseExponentialOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseExponentialOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseExponentialInOut

JSClassRef js_S_CCEaseExponentialInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseExponentialInOut)

JSStaticFunction* S_CCEaseExponentialInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseExponentialInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseExponentialInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseSineIn

JSClassRef js_S_CCEaseSineIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseSineIn)

JSStaticFunction* S_CCEaseSineIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseSineIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseSineIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseSineOut

JSClassRef js_S_CCEaseSineOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseSineOut)

JSStaticFunction* S_CCEaseSineOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseSineOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseSineOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseSineInOut

JSClassRef js_S_CCEaseSineInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseSineInOut)

JSStaticFunction* S_CCEaseSineInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseSineInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseSineInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseElastic

JSClassRef js_S_CCEaseElastic_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseElastic)

JSStaticFunction* S_CCEaseElastic::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCEaseElastic::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseElastic::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseElasticIn

JSClassRef js_S_CCEaseElasticIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseElasticIn)

JSStaticFunction* S_CCEaseElasticIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseElasticIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseElasticIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseElasticOut

JSClassRef js_S_CCEaseElasticOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseElasticOut)

JSStaticFunction* S_CCEaseElasticOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseElasticOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseElasticOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseElasticInOut

JSClassRef js_S_CCEaseElasticInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseElasticInOut)

JSStaticFunction* S_CCEaseElasticInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseElasticInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseElasticInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBounce

JSClassRef js_S_CCEaseBounce_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBounce)

JSStaticFunction* S_CCEaseBounce::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBounce::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBounce::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBounceIn

JSClassRef js_S_CCEaseBounceIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBounceIn)


JSStaticFunction* S_CCEaseBounceIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBounceIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBounceIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBounceOut

JSClassRef js_S_CCEaseBounceOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBounceOut)

JSStaticFunction* S_CCEaseBounceOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBounceOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBounceOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBounceInOut

JSClassRef js_S_CCEaseBounceInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBounceInOut)

JSStaticFunction* S_CCEaseBounceInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBounceInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBounceInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBackIn

JSClassRef js_S_CCEaseBackIn_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBackIn)

JSStaticFunction* S_CCEaseBackIn::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBackIn::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBackIn::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBackOut

JSClassRef js_S_CCEaseBackOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBackOut)

JSStaticFunction* S_CCEaseBackOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBackOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBackOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCEaseBackInOut

JSClassRef js_S_CCEaseBackInOut_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCEaseBackInOut)

JSStaticFunction* S_CCEaseBackInOut::jsStaticFunctions()
{
	return NULL;
}

bool S_CCEaseBackInOut::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1 && CCEaseBackInOut::initWithDuration(JSValueToNumber(ctx, arguments[0], NULL))) {
		result = true;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCGridAction

JSClassRef js_S_CCGridAction_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCGridAction)

JSStaticFunction* S_CCGridAction::jsStaticFunctions()
{
	return NULL;
}

bool S_CCGridAction::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {pt->x, pt->y};
		result = CCGridAction::initWithSize(size, JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCGrid3DAction

JSClassRef js_S_CCGrid3DAction_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCGrid3DAction)

JSStaticFunction* S_CCGrid3DAction::jsStaticFunctions()
{
	return NULL;
}

bool S_CCGrid3DAction::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {pt->x, pt->y};
		result = CCGrid3DAction::initWithSize(size, JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCTiledGrid3DAction

JSClassRef js_S_CCTiledGrid3DAction_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTiledGrid3DAction)

JSStaticFunction* S_CCTiledGrid3DAction::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTiledGrid3DAction::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {pt->x, pt->y};
		result = CCTiledGrid3DAction::initWithSize(size, JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}


#pragma mark - CCAccelDeccelAmplitude

JSClassRef js_S_CCAccelDeccelAmplitude_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCAccelDeccelAmplitude)

JSStaticFunction* S_CCAccelDeccelAmplitude::jsStaticFunctions()
{
	return NULL;
}

bool S_CCAccelDeccelAmplitude::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1) {
		result = CCAccelDeccelAmplitude::initWithDuration(JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCAccelAmplitude

JSClassRef js_S_CCAccelAmplitude_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCAccelAmplitude)

JSStaticFunction* S_CCAccelAmplitude::jsStaticFunctions()
{
	return NULL;
}

bool S_CCAccelAmplitude::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1) {
		result = CCAccelAmplitude::initWithDuration(JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCDeccelAmplitude

JSClassRef js_S_CCDeccelAmplitude_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCDeccelAmplitude)

JSStaticFunction* S_CCDeccelAmplitude::jsStaticFunctions()
{
	return NULL;
}

bool S_CCDeccelAmplitude::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 1) {
		result = CCDeccelAmplitude::initWithDuration(JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCWaves3D

JSClassRef js_S_CCWaves3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCWaves3D)

JSStaticFunction* S_CCWaves3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCWaves3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int wav = JSTOF(0);
		float amp = JSTOF(1);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		float duration = JSTOF(3);
		ccGridSize size = {ptSize->x, ptSize->y};
		result = CCWaves3D::initWithWaves(wav, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFlipX3D

JSClassRef js_S_CCFlipX3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFlipX3D)

JSStaticFunction* S_CCFlipX3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFlipX3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {pt->x, pt->y};
		result = CCFlipX3D::initWithSize(size, JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFlipY3D

JSClassRef js_S_CCFlipY3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFlipY3D)

JSStaticFunction* S_CCFlipY3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFlipY3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *pt = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {pt->x, pt->y};
		result = CCFlipY3D::initWithSize(size, JSValueToNumber(ctx, arguments[1], NULL));
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCLens3D

JSClassRef js_S_CCLens3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCLens3D)

JSStaticFunction* S_CCLens3D::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setPosition", S_CCLens3D::jsSetPosition, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCLens3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = true;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		CCPoint *pos = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		float r = JSTOF(1);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);
		CCLens3D::initWithPosition(*pos, r, size, duration);
		result = false;
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

JS_STATIC_FUNC_IMP(S_CCLens3D, jsSetPosition)
{
	//		void setPosition(const CCPoint& position);
	
	if (argumentCount == 1) {
		CCLens3D* self = (CCLens3D *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		CCPoint *_arg0 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		self->setPosition(*_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


#pragma mark - CCRipple3D

JSClassRef js_S_CCRipple3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCRipple3D)

JSStaticFunction* S_CCRipple3D::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setPosition", S_CCRipple3D::jsSetPosition, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCRipple3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 6) {
		CCPoint *pos = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		float r = JSTOF(1);
		int wav = JSTOF(2);
		float amp = JSTOF(3);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[4]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(5);
		result = CCRipple3D::initWithPosition(*pos, r, wav, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

JS_STATIC_FUNC_IMP(S_CCRipple3D, jsSetPosition)
{
	//		void setPosition(const CCPoint& position);
	
	if (argumentCount == 1) {
		CCRipple3D* self = (CCRipple3D *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		CCPoint *_arg0 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		self->setPosition(*_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


#pragma mark - CCShaky3D

JSClassRef js_S_CCShaky3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCShaky3D)

JSStaticFunction* S_CCShaky3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCShaky3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int range = JSTOF(0);
		bool shakeZ = JSValueToBoolean(ctx, arguments[1]);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);

		result = CCShaky3D::initWithRange(range, shakeZ, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCLiquid

JSClassRef js_S_CCLiquid_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCLiquid)

JSStaticFunction* S_CCLiquid::jsStaticFunctions()
{
	return NULL;
}

bool S_CCLiquid::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int wav = JSTOF(0);
		float amp = JSTOF(1);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);
		
		result = CCLiquid::initWithWaves(wav, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCWaves

JSClassRef js_S_CCWaves_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCWaves)

JSStaticFunction* S_CCWaves::jsStaticFunctions()
{
	return NULL;
}

bool S_CCWaves::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 6) {
		int wav = JSTOF(0);
		float amp = JSTOF(1);
		bool h = JSValueToBoolean(ctx, arguments[2]);
		bool v = JSValueToBoolean(ctx, arguments[3]);

		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[4]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(5);
		
		result = CCWaves::initWithWaves(wav, amp, h, v, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCTwirl

JSClassRef js_S_CCTwirl_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTwirl)

JSStaticFunction* S_CCTwirl::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setPosition", S_CCTwirl::jsSetPosition, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCTwirl::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 5) {
		CCPoint *pos = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		int t = JSTOF(1);
		float amp = JSTOF(2);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[3]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(4);
		result = CCTwirl::initWithPosition(*pos, t, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

JS_STATIC_FUNC_IMP(S_CCTwirl, jsSetPosition)
{
	//		void setPosition(const CCPoint& position);
	
	if (argumentCount == 1) {
		CCTwirl* self = (CCTwirl *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		CCPoint *_arg0 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		self->setPosition(*_arg0);
	}
	return JSValueMakeUndefined(ctx);
}

#pragma mark - CCPageTurn3D

JSClassRef js_S_CCPageTurn3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCPageTurn3D)

JSStaticFunction* S_CCPageTurn3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCPageTurn3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);

		result = CCPageTurn3D::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCProgressTo

JSClassRef js_S_CCProgressTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCProgressTo)

JSStaticFunction* S_CCProgressTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCProgressTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		ccTime duration = JSTOF(0);
		float fPercent = JSTOF(1);
		result = CCProgressTo::initWithDuration(duration, fPercent);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCProgressFromTo

JSClassRef js_S_CCProgressFromTo_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCProgressFromTo)

JSStaticFunction* S_CCProgressFromTo::jsStaticFunctions()
{
	return NULL;
}

bool S_CCProgressFromTo::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 3) {
		ccTime duration = JSTOF(0);
		float fFromPercent = JSTOF(1);
		float fToPercent = JSTOF(2);
		result = CCProgressFromTo::initWithDuration(duration, fFromPercent, fToPercent);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCShakyTiles3D

JSClassRef js_S_CCShakyTiles3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCShakyTiles3D)

JSStaticFunction* S_CCShakyTiles3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCShakyTiles3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int nRange = JSTOF(0);
		bool bShakeZ = JSValueToBoolean(ctx, arguments[1]);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);

		result = CCShakyTiles3D::initWithRange(nRange, bShakeZ, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCShatteredTiles3D

JSClassRef js_S_CCShatteredTiles3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCShatteredTiles3D)

JSStaticFunction* S_CCShatteredTiles3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCShatteredTiles3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int nRange = JSTOF(0);
		bool bShakeZ = JSValueToBoolean(ctx, arguments[1]);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);
		result = CCShatteredTiles3D::initWithRange(nRange, bShakeZ, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCShuffleTiles

JSClassRef js_S_CCShuffleTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCShuffleTiles)

JSStaticFunction* S_CCShuffleTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCShuffleTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int s = JSTOF(0);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(2);

		result = CCShuffleTiles::initWithSeed(s, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeOutTRTiles

JSClassRef js_S_CCFadeOutTRTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeOutTRTiles)

JSStaticFunction* S_CCFadeOutTRTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeOutTRTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = true;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCFadeOutTRTiles::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeOutBLTiles

JSClassRef js_S_CCFadeOutBLTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeOutBLTiles)

JSStaticFunction* S_CCFadeOutBLTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeOutBLTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCFadeOutBLTiles::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeOutUpTiles

JSClassRef js_S_CCFadeOutUpTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeOutUpTiles)

JSStaticFunction* S_CCFadeOutUpTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeOutUpTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCFadeOutUpTiles::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCFadeOutDownTiles

JSClassRef js_S_CCFadeOutDownTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCFadeOutDownTiles)

JSStaticFunction* S_CCFadeOutDownTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCFadeOutDownTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCFadeOutDownTiles::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCTurnOffTiles

JSClassRef js_S_CCTurnOffTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTurnOffTiles)

JSStaticFunction* S_CCTurnOffTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTurnOffTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = true;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCTurnOffTiles::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCWavesTiles3D

JSClassRef js_S_CCWavesTiles3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCWavesTiles3D)

JSStaticFunction* S_CCWavesTiles3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCWavesTiles3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int wav = JSTOF(0);
		float amp = JSTOF(1);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);
		result = CCWavesTiles3D::initWithWaves(wav, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCJumpTiles3D

JSClassRef js_S_CCJumpTiles3D_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCJumpTiles3D)

JSStaticFunction* S_CCJumpTiles3D::jsStaticFunctions()
{
	return NULL;
}

bool S_CCJumpTiles3D::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 4) {
		int j = JSTOF(0);
		float amp = JSTOF(1);
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[2]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(3);
		result = CCJumpTiles3D::initWithJumps(j, amp, size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCSplitRows

JSClassRef js_S_CCSplitRows_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSplitRows)

JSStaticFunction* S_CCSplitRows::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSplitRows::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCSplitRows::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}

#pragma mark - CCSplitCols

JSClassRef js_S_CCSplitCols_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCSplitCols)

JSStaticFunction* S_CCSplitCols::jsStaticFunctions()
{
	return NULL;
}

bool S_CCSplitCols::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	// IMPLEMENT THE CONSTRUCTOR HERE AND INITIALIZE THE CCNODE SUBCLASS
	// basically do something like this:
	if (argumentCount == 2) {
		CCPoint *ptSize = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		ccGridSize size = {ptSize->x, ptSize->y};
		ccTime duration = JSTOF(1);
		result = CCSplitCols::initWithSize(size, duration);
	}
	SET_PROTECT_JS(result, obj);
	return result;
}
