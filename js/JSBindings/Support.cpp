//
//  Support.c
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/8/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include <stdio.h>
#include "ScriptingCore.h"

//
// Eval an anonymous function with a custom 'this'.
//	Used to easily inspect and manipulate a JSValue
//		Given a javascript date :
//			[jsc anonEval:@"return this.getMilliseconds()" withThis:myObject]
//		Getting an object's keys :
//			[jsc anonEval:@"return Object.keys(this)" withThis:myObject]
//		Getting the length of an array :
//			[jsc anonEval:@"return this.length" withThis:myObject]
//
JSValueRef anonEval(const char* script, JSContextRef ctx, JSValueRef thisObject, size_t argumentCount, const JSValueRef *arguments)
{
	JSStringRef scriptJS= JSStringCreateWithUTF8CString(script);
	JSObjectRef fn		= JSObjectMakeFunction(ctx, NULL, 0, NULL, scriptJS, NULL, 1, NULL);
	JSValueRef result	= JSObjectCallAsFunction(ctx, fn, thisObject ? JSValueToObject(ctx, thisObject, NULL) : NULL, argumentCount, arguments, NULL);
	JSStringRelease(scriptJS);
	return result;
}

JSValueRef js_log(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	static char *buff = NULL;
	if (!buff) {
		buff = (char *)malloc(1024);
	}
	for (int i = 0; i < argumentCount; i++) {
		JSStringRef resultStringJS = JSValueToStringCopy(ctx, arguments[i], NULL);
		JSStringGetUTF8CString(resultStringJS, buff, 1024);
		fprintf(stdout, "%s\n", buff);
		fflush(stdout);
		JSStringRelease(resultStringJS);
	}
	return JSValueMakeUndefined(ctx);
}

JSValueRef js_require(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	char *buff = (char *)malloc(512);
	for (int i=0; buff && i < argumentCount; i++) {
		JSStringRef str = JSValueToStringCopy(ctx, arguments[i], NULL);
		size_t len = JSStringGetLength(str);
		if (len < 512) {
			JSStringGetUTF8CString(str, buff, 511);
		}
		ScriptingCore::getInstance().runScript(buff);
	}
	free(buff);
	return JSValueMakeUndefined(ctx);
}

JSValueRef js_exit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	int returnValue = 0;
	if (argumentCount == 1) {
		returnValue = JSValueToNumber(ctx, arguments[0], NULL);
	}
	exit(returnValue);
}
