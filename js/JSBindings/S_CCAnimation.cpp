//
//  S_CCAnimation.cpp
//  cocos2d-x
//
//  Created By XXX on 02/22/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#include <JavaScriptCore/JavaScriptCore.h>
#include "S_CCAnimation.h"

using namespace cocos2d;


#pragma mark - CCAnimation

JSClassRef js_S_CCAnimation_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCAnimation)

JSStaticFunction* S_CCAnimation::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"addFrame", S_CCAnimation::jsAddFrame, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCAnimation::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount > 0) {
		CCMutableArray<CCSpriteFrame*> frames;
		// get the array
		if (JSValueIsObject(ctx, arguments[0])) {
			JSObjectRef obj = (JSObjectRef)arguments[0];
			JSStringRef propName = JSStringCreateWithUTF8CString("length");
			if (JSObjectHasProperty(ctx, obj, propName)) {
				// might be an array
				int totalElements = JSValueToNumber(ctx, JSObjectGetProperty(ctx, obj, propName, NULL), NULL);
				for (int i=0; i < totalElements; i++) {
					// we could definitively improve this!!
					JSValueRef val = JSObjectGetPropertyAtIndex(ctx, obj, i, NULL);
					JSStringRef str = JSValueToStringCopy(ctx, val, NULL);
					int len = JSStringGetLength(str);
					char *buff = (char *)malloc(len+1);
					JSStringGetUTF8CString(str, buff, len+1);
					
					CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buff);
					if (frame)
						frames.addObject(frame);
					
					JSStringRelease(str);
					free(buff);
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
		if (argumentCount == 2) {
			float delay = JSValueToNumber(ctx, arguments[1], NULL);
			result = CCAnimation::initWithFrames(&frames, delay);
		} else {
			result = CCAnimation::initWithFrames(&frames);
		}
	} else {
		result = CCAnimation::init();
	}
	if (result) {
		
		jsObject = obj;
	}
	return result;
}

JS_STATIC_FUNC_IMP(S_CCAnimation, jsAddFrame)
{
	//		void addFrame(CCSpriteFrame *pFrame);

	if (argumentCount == 1) {
		CCAnimation* self = (CCAnimation *)JSObjectGetPrivate(thisObject);
		JSStringRef str = JSValueToStringCopy(ctx, arguments[0], NULL);
		int len = JSStringGetLength(str);
		char *buff = (char *)malloc(len+1);
		JSStringGetUTF8CString(str, buff, len+1);
		
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buff);
		if (frame) {
			self->addFrame(frame);
		}

		JSStringRelease(str);
		free(buff);
	}
	return JSValueMakeUndefined(ctx);
}
