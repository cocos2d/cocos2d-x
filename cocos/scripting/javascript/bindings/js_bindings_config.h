/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef __JS_BINDINGS_CONFIG_H
#define __JS_BINDINGS_CONFIG_H


/** @def JSB_ASSERT_ON_FAIL
 Whether or not to assert when the arguments or conversions are incorrect.
 It is recommened to turn it off in Release mode.
 */
#ifndef JSB_ASSERT_ON_FAIL
#define JSB_ASSERT_ON_FAIL 0
#endif


#if JSB_ASSERT_ON_FAIL
#define JSB_PRECONDITION( condition, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)
#define JSB_PRECONDITION2( condition, context, ret_value, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)
#define ASSERT( condition, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)

#else
#define JSB_PRECONDITION( condition, ...) do {							\
	if( ! (condition) ) {														\
        cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );			\
        cocos2d::log(__VA_ARGS__);                                        \
		JSContext* globalContext = ScriptingCore::getInstance()->getGlobalContext();	\
		if( ! JS_IsExceptionPending( globalContext ) ) {						\
			JS_ReportError( globalContext, __VA_ARGS__ );							\
		}																		\
		return JS_FALSE;														\
	}																			\
} while(0)
#define JSB_PRECONDITION2( condition, context, ret_value, ...) do {             \
    if( ! (condition) ) {														\
        cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );			\
        cocos2d::log(__VA_ARGS__);                                        \
        if( ! JS_IsExceptionPending( context ) ) {							\
            JS_ReportError( context, __VA_ARGS__ );								\
        }																		\
        return ret_value;														\
    }                                                                           \
} while(0)
#define ASSERT( condition, error_msg) do {										\
	if( ! (condition) ) {														\
		CCLOG("jsb: ERROR in %s: %s\n", __FUNCTION__, error_msg);				\
		return false;															\
	}																			\
	} while(0)
#endif

#define JSB_PRECONDITION3( condition, context, ret_value, ...) do { \
        if( ! (condition) ) return (ret_value); \
    } while(0)


/** @def JSB_REPRESENT_LONGLONG_AS_STR
 When JSB_REPRESENT_LONGLONG_AS_STR is defined, the long long will be represented as JS strings.
 Otherwise they will be represented as an array of two intengers.
 It is needed to to use an special representation since there are no 64-bit integers in JS.
 Representing the long long as string could be a bit slower, but it is easier to debug from JS.
 Enabled by default.
 */
#ifndef JSB_REPRESENT_LONGLONG_AS_STR
#define JSB_REPRESENT_LONGLONG_AS_STR 1
#endif // JSB_REPRESENT_LONGLONG_AS_STR


/** @def JSB_INCLUDE_NS
 Whether or not it should include JS bindings for basic NS* / Cocoa / CocoaTouch objects.
 It should be enabled in order to support bindings for any objective-c projects.
 Not needed for pure C projects.
 Enabled by default.
 */
#ifndef JSB_INCLUDE_NS
#define JSB_INCLUDE_NS 1
#endif // JSB_INCLUDE_NS


/** @def JSB_INCLUDE_COCOS2D
 Whether or not it should include JS bindings for cocos2d.
 */
#ifndef JSB_INCLUDE_COCOS2D
#define JSB_INCLUDE_COCOS2D 1

#include "cocos2d.h"
#if defined(__CC_PLATFORM_IOS)
#define JSB_INCLUDE_COCOS2D_IOS 1
#elif defined(__CC_PLATFORM_MAC)
#define JSB_INCLUDE_COCOS2D_MAC 1
#endif

#endif // JSB_INCLUDE_COCOS2D


/** @def JSB_INCLUDE_CHIPMUNK
 Whether or not it should include JS bindings for Chipmunk
 */
#ifndef JSB_INCLUDE_CHIPMUNK
#define JSB_INCLUDE_CHIPMUNK 1
#endif // JSB_INCLUDE_CHIPMUNK


/** @def JSB_INCLUDE_COCOSBUILDERREADER
 Whether or not it should include JS bindings for CocosBuilder Reader
 */
#ifndef JSB_INCLUDE_COCOSBUILDERREADER
#define JSB_INCLUDE_COCOSBUILDERREADER 1
#endif // JSB_INCLUDE_COCOSBUILDERREADER

/** @def JSB_INCLUDE_COCOSDENSHION
 Whether or not it should include bindings for CocosDenshion (sound engine)
 */
#ifndef JSB_INCLUDE_COCOSDENSHION
#define JSB_INCLUDE_COCOSDENSHION 1
#endif // JSB_INCLUDE_COCOSDENSHION

#if JSB_ENABLE_DEBUGGER
#define JSB_ENSURE_AUTOCOMPARTMENT(cx, obj) \
JSAutoCompartment ac(cx, obj)
#else
#define JSB_ENSURE_AUTOCOMPARTMENT(cx, obj)
#endif

#define JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET \
JSAutoCompartment __jsb_ac(ScriptingCore::getInstance()->getGlobalContext(), ScriptingCore::getInstance()->getGlobalObject());

/**
 * @def JSB_DEBUGGER_PORT
 * The port number, where the client will be listening on
 */
#define JSB_DEBUGGER_PORT 5086

/** @def JSB_INCLUDE_SYSTEM
 Whether or not it should include bindings for system components like LocalStorage
 */
#ifndef JSB_INCLUDE_SYSTEM
#define JSB_INCLUDE_SYSTEM 1
#endif // JSB_INCLUDE_SYSTEM

/** @def JSB_INCLUDE_OPENGL
 Whether or not it should include bindings for WebGL / OpenGL ES 2.0
 */
#ifndef JSB_INCLUDE_OPENGL
#define JSB_INCLUDE_OPENGL 1
#endif // JSB_INCLUDE_OPENGL

/** @def JSB_INCLUDE_XMLHTTP
 Whether or not it should include bindings for XmlHttpRequest
 */
#ifndef JSB_INCLUDE_XMLHTTP
#define JSB_INCLUDE_XMLHTTP 1
#endif // JSB_INCLUDE_XMLHTTP

#ifndef JSB_MAX_STACK_QUOTA
#define JSB_MAX_STACK_QUOTA 500000
#endif // JSB_MAX_STACK_QUOTA

#endif // __JS_BINDINGS_CONFIG_H
