//
//  S_CCLabel.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 1/13/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "S_CCLabel.h"

#pragma mark - CCLabelTTF

JSClassRef js_S_CCLabelTTF_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCLabelTTF)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCLabelTTF, CCLabelTTF)

JSStaticFunction* S_CCLabelTTF::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"setString", S_CCLabelTTF::jsSetString, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"getString", S_CCLabelTTF::jsGetString, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCLabelTTF::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = true;
	if (argumentCount == 3) {
		char *buffText = (char *)malloc(128);
		char *buffFont = (char *)malloc(128);
		
		JSStringRef jsLabelText = JSValueToStringCopy(ctx, arguments[0], NULL);
		JSStringRef jsFontName  = JSValueToStringCopy(ctx, arguments[1], NULL);
		float fontSize = JSValueToNumber(ctx, arguments[2], NULL);
		
		JSStringGetUTF8CString(jsLabelText, buffText, 128);
		JSStringGetUTF8CString(jsFontName, buffFont, 128);
		
		if (!CCLabelTTF::initWithString(buffText, buffFont, fontSize)) {
			return false;
		}
		free(buffText);
		free(buffFont);
	} else {
		if (!CCLabelTTF::init()) {
			result = false;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

JS_STATIC_FUNC_IMP(S_CCLabelTTF, jsSetString)
{
	if (argumentCount == 1) {
		CCLabelTTF *label = (CCLabelTTF *)JSObjectGetPrivate(thisObject);
		if (label) {
			char *buffText = (char *)malloc(128);
			JSStringRef jsLabelText = JSValueToStringCopy(ctx, arguments[0], NULL);
			JSStringGetUTF8CString(jsLabelText, buffText, 128);
			label->setString(buffText);
			free(buffText);
		}
	}
	return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCLabelTTF, jsGetString)
{
	CCLabelTTF *label = (CCLabelTTF *)JSObjectGetPrivate(thisObject);
	if (label) {
		JSStringRef jsStr = JSStringCreateWithUTF8CString(label->getString());
		JSValueRef ret = JSValueMakeString(ctx, jsStr);
		JSStringRelease(jsStr);
		return ret;
	}
	return JSValueMakeUndefined(ctx);
}
