//
//  S_CCDirector.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include "S_CCDirector.h"

JSClassRef js_S_CCDirector_class;

JSObjectRef S_CCDirector::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	return NULL;
}

bool S_CCDirector::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	return false;
}

JSValueRef S_CCDirector::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	return JSValueMakeUndefined(ctx);
}

JSStaticFunction* S_CCDirector::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"runWithScene", S_CCDirector::jsRunWithScene, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"replaceScene", S_CCDirector::jsReplaceScene, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"pushScene", S_CCDirector::jsPushScene, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"popScene", S_CCDirector::jsPopScene, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCDirector::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	return false;
}

JS_STATIC_FUNC_IMP(S_CCDirector, jsRunWithScene)
{
	if (argumentCount == 1)
	{
		// this should be a CCNode
		JSObjectRef scene = JSValueToObject(ctx, arguments[0], NULL);
		CCScene *obj = (CCScene *)JSObjectGetPrivate(scene);
		if (obj)
		{
			CCDirector::sharedDirector()->runWithScene(obj);
			JSValueProtect(ctx, arguments[0]);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCDirector, jsReplaceScene)
{
	if (argumentCount == 1)
	{
		// this should be a CCNode
		JSObjectRef scene = JSValueToObject(ctx, arguments[0], NULL);
		CCScene *obj = (CCScene *)JSObjectGetPrivate(scene);
		if (obj)
		{
			// get old scene
			CCScene *old = CCDirector::sharedDirector()->getRunningScene();
			if (old) {
				JSObjectRef oldObj = (JSObjectRef)old->getUserData();
				if (oldObj) {
					JSValueUnprotect(ctx, oldObj);
				}
			}
			CCDirector::sharedDirector()->replaceScene(obj);
			JSValueProtect(ctx, arguments[0]);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCDirector, jsPushScene)
{
	if (argumentCount == 1) {
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		if (scene) {
			JSValueProtect(ctx, arguments[0]);
			CCDirector::sharedDirector()->pushScene(scene);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCDirector, jsPopScene)
{
	if (argumentCount == 0) {
		CCScene *scene = CCDirector::sharedDirector()->getRunningScene();
		JSObjectRef jsScene = (JSObjectRef)scene->getUserData();
		if (jsScene) {
			JSValueUnprotect(ctx, jsScene);
			CCDirector::sharedDirector()->popScene();
		}
	}
	return JSValueMakeUndefined(ctx);
}
