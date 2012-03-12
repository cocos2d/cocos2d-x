//
//  S_CCSpriteFrameCache.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/12/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include <iostream>
#import "S_CCSpriteFrameCache.h"

using namespace cocos2d;

JSClassRef js_S_CCSpriteFrameCache_class;

JSObjectRef S_CCSpriteFrameCache::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	return NULL;
}

bool S_CCSpriteFrameCache::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	return false;
}

JSValueRef S_CCSpriteFrameCache::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	return JSValueMakeUndefined(ctx);
}

JSStaticFunction* S_CCSpriteFrameCache::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"addSpriteFramesWithFile", S_CCSpriteFrameCache::jsAddSpriteFramesWithFile, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

JS_STATIC_FUNC_IMP(S_CCSpriteFrameCache, jsAddSpriteFramesWithFile)
{
	if (argumentCount == 1)
	{
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		size_t len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(buff);
		JSStringRelease(str);
		free(buff);
	}
	return JSValueMakeNull(ctx);
}
