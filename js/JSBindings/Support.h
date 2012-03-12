//
//  Support.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/8/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_Support_h
#define TestCocos2dX_Support_h

#include <JavaScriptCore/JavaScriptCore.h>

#pragma mark - Macros

/**
 * implementation of a js binding function
 */
#define JS_STATIC_FUNC_IMP(klass, name) \
JSValueRef klass::name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)

/**
 * definition of a js binding function
 */
#define JS_STATIC_FUNC_DEF(name) \
static JSValueRef name(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)

#pragma mark - Functions

JSValueRef anonEval(const char* script, JSContextRef ctx, JSValueRef thisObject, size_t argumentCount, const JSValueRef *arguments);
JSValueRef js_log(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);
JSValueRef js_require(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);
JSValueRef js_exit(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);

#endif
