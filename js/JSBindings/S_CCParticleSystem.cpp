//
//  S_CCParticleSystem.cpp
//  cocos2d-x
//
//  Created By XXX on 02/15/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#include <JavaScriptCore/JavaScriptCore.h>
#include "S_CCParticleSystem.h"

using namespace cocos2d;


#pragma mark - CCParticleSystem

JSClassRef js_S_CCParticleSystem_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCParticleSystem)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCParticleSystem, CCParticleSystem)

JSStaticFunction* S_CCParticleSystem::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setGravity", S_CCParticleSystem::jsSetGravity, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getSpeed", S_CCParticleSystem::jsGetSpeed, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setSpeed", S_CCParticleSystem::jsSetSpeed, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getSpeedVar", S_CCParticleSystem::jsGetSpeedVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setSpeedVar", S_CCParticleSystem::jsSetSpeedVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getTangentialAccel", S_CCParticleSystem::jsGetTangentialAccel, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setTangentialAccel", S_CCParticleSystem::jsSetTangentialAccel, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getTangentialAccelVar", S_CCParticleSystem::jsGetTangentialAccelVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setTangentialAccelVar", S_CCParticleSystem::jsSetTangentialAccelVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getRadialAccel", S_CCParticleSystem::jsGetRadialAccel, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRadialAccel", S_CCParticleSystem::jsSetRadialAccel, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getRadialAccelVar", S_CCParticleSystem::jsGetRadialAccelVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRadialAccelVar", S_CCParticleSystem::jsSetRadialAccelVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getStartRadius", S_CCParticleSystem::jsGetStartRadius, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setStartRadius", S_CCParticleSystem::jsSetStartRadius, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getStartRadiusVar", S_CCParticleSystem::jsGetStartRadiusVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setStartRadiusVar", S_CCParticleSystem::jsSetStartRadiusVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getEndRadius", S_CCParticleSystem::jsGetEndRadius, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setEndRadius", S_CCParticleSystem::jsSetEndRadius, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getEndRadiusVar", S_CCParticleSystem::jsGetEndRadiusVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setEndRadiusVar", S_CCParticleSystem::jsSetEndRadiusVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getRotatePerSecond", S_CCParticleSystem::jsGetRotatePerSecond, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRotatePerSecond", S_CCParticleSystem::jsSetRotatePerSecond, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getRotatePerSecondVar", S_CCParticleSystem::jsGetRotatePerSecondVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setRotatePerSecondVar", S_CCParticleSystem::jsSetRotatePerSecondVar, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"addParticle", S_CCParticleSystem::jsAddParticle, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"stopSystem", S_CCParticleSystem::jsStopSystem, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"resetSystem", S_CCParticleSystem::jsResetSystem, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"isFull", S_CCParticleSystem::jsIsFull, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCParticleSystem::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 1) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		result = CCParticleSystem::initWithFile(buff);
		
		JSStringRelease(str);
		free(buff);
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetGravity)
{
	//	virtual void setGravity(const CCPoint& g);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		CCPoint *_arg0 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		self->setGravity(*_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetSpeed)
{
	//	virtual float getSpeed();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getSpeed());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetSpeed)
{
	//	virtual void setSpeed(float speed);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setSpeed(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetSpeedVar)
{
	//	virtual float getSpeedVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getSpeedVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetSpeedVar)
{
	//	virtual void setSpeedVar(float speed);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setSpeedVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetTangentialAccel)
{
	//	virtual float getTangentialAccel();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getTangentialAccel());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetTangentialAccel)
{
	//	virtual void setTangentialAccel(float t);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setTangentialAccel(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetTangentialAccelVar)
{
	//	virtual float getTangentialAccelVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getTangentialAccelVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetTangentialAccelVar)
{
	//	virtual void setTangentialAccelVar(float t);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setTangentialAccelVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetRadialAccel)
{
	//	virtual float getRadialAccel();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getRadialAccel());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetRadialAccel)
{
	//	virtual void setRadialAccel(float t);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setRadialAccel(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetRadialAccelVar)
{
	//	virtual float getRadialAccelVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getRadialAccelVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetRadialAccelVar)
{
	//	virtual void setRadialAccelVar(float t);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setRadialAccelVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetStartRadius)
{
	//	virtual float getStartRadius();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getStartRadius());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetStartRadius)
{
	//	virtual void setStartRadius(float startRadius);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setStartRadius(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetStartRadiusVar)
{
	//	virtual float getStartRadiusVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getStartRadiusVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetStartRadiusVar)
{
	//	virtual void setStartRadiusVar(float startRadiusVar);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setStartRadiusVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetEndRadius)
{
	//	virtual float getEndRadius();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getEndRadius());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetEndRadius)
{
	//	virtual void setEndRadius(float endRadius);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setEndRadius(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetEndRadiusVar)
{
	//	virtual float getEndRadiusVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getEndRadiusVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetEndRadiusVar)
{
	//	virtual void setEndRadiusVar(float endRadiusVar);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setEndRadiusVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetRotatePerSecond)
{
	//	virtual float getRotatePerSecond();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getRotatePerSecond());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetRotatePerSecond)
{
	//	virtual void setRotatePerSecond(float degrees);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setRotatePerSecond(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsGetRotatePerSecondVar)
{
	//	virtual float getRotatePerSecondVar();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeNumber(ctx, self->getRotatePerSecondVar());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsSetRotatePerSecondVar)
{
	//	virtual void setRotatePerSecondVar(float degrees);

	if (argumentCount == 1) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		float _arg0 = JSValueToNumber(ctx, arguments[0], NULL);
		self->setRotatePerSecondVar(_arg0);
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsAddParticle)
{
	//	bool addParticle();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeBoolean(ctx, self->addParticle());
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsStopSystem)
{
	//	void stopSystem();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		self->stopSystem();
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsResetSystem)
{
	//	void resetSystem();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		self->resetSystem();
	}
	return JSValueMakeUndefined(ctx);
}


JS_STATIC_FUNC_IMP(S_CCParticleSystem, jsIsFull)
{
	//	bool isFull();

	if (argumentCount == 0) {
		CCParticleSystem* self = (CCParticleSystem *)JSObjectGetPrivate(thisObject);
		// CHECK FOR THIS CONVERTIONS - MIGHT BE WRONG!
		
		return JSValueMakeBoolean(ctx, self->isFull());
	}
	return JSValueMakeUndefined(ctx);
}



