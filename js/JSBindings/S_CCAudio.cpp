//
//  S_CCAudio.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 1/31/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "S_CCAudio.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#pragma mark - CCAudio

JSClassRef js_S_CCAudioManager_class;

JSObjectRef S_CCAudioManager::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	return NULL;
}

bool S_CCAudioManager::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	return false;
}

JSValueRef S_CCAudioManager::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	return JSValueMakeUndefined(ctx);
}

JSStaticFunction *S_CCAudioManager::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"preloadBackgroundMusic", S_CCAudioManager::jsPreloadBackgroundMusic, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"playBackgroundMusic", S_CCAudioManager::jsPlayBackgroundMusic, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"stopBackgroundMusic", S_CCAudioManager::jsStopBackgroundMusic, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"pauseBackgroundMusic", S_CCAudioManager::jsPauseBackgroundMusic, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"setBackgroundMusicVolume", S_CCAudioManager::jsSetBackgroundMusicVolume, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getBackgroundMusicVolume", S_CCAudioManager::jsGetBackgroundMusicVolume, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"playEffect", S_CCAudioManager::jsPlayEffect, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"stopEffect", S_CCAudioManager::jsStopEffect, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"stopAllEffects", S_CCAudioManager::jsStopAllEffects, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCAudioManager::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	return false;
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsPreloadBackgroundMusic)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (argumentCount > 0) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		
		engine->preloadBackgroundMusic(buff);
		
		JSStringRelease(str);
		free(buff);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsPlayBackgroundMusic)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (argumentCount > 0) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		
		bool loop = false;
		if (argumentCount == 2) {
			loop = JSValueToBoolean(ctx, arguments[1]);
		}

		engine->playBackgroundMusic(buff, loop);

		JSStringRelease(str);
		free(buff);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsStopBackgroundMusic)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	engine->stopBackgroundMusic();
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsPauseBackgroundMusic)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	engine->pauseBackgroundMusic();
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsSetBackgroundMusicVolume)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (argumentCount == 1) {
		engine->setBackgroundMusicVolume(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsGetBackgroundMusicVolume)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	return JSValueMakeNumber(ctx, engine->getBackgroundMusicVolume());
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsPlayEffect)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (argumentCount == 1) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);

		int soundId = engine->playEffect(buff);

		JSStringRelease(str);
		free(buff);
		return JSValueMakeNumber(ctx, soundId);
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsStopEffect)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	if (argumentCount == 1) {
		engine->stopEffect(JSValueToNumber(ctx, arguments[0], NULL));
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCAudioManager, jsStopAllEffects)
{
	SimpleAudioEngine *engine = SimpleAudioEngine::sharedEngine();
	engine->stopAllEffects();
	return JSValueMakeUndefined(ctx);
}

