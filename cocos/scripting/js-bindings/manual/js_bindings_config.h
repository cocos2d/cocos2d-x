/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
 It is recommended to turn it off in Release mode.
 */
#ifndef JSB_ASSERT_ON_FAIL
#define JSB_ASSERT_ON_FAIL 0
#endif


#if JSB_ASSERT_ON_FAIL
#define JSB_PRECONDITION( condition, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)
#define JSB_PRECONDITION2( condition, context, ret_value, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)
#define ASSERT( condition, error_msg) do { NSCAssert( condition, [NSString stringWithUTF8String:error_msg] ); } while(0)

#else
#define JSB_PRECONDITION( condition, ...) do {                          \
    if( ! (condition) ) {                                                       \
        cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );         \
        cocos2d::log(__VA_ARGS__);                                        \
        JSContext* globalContext = ScriptingCore::getInstance()->getGlobalContext();    \
        if( ! JS_IsExceptionPending( globalContext ) ) {                        \
            JS_ReportError( globalContext, __VA_ARGS__ );                           \
        }                                                                       \
        return false;                                                       \
    }                                                                           \
} while(0)
#define JSB_PRECONDITION2( condition, context, ret_value, ...) do {             \
    if( ! (condition) ) {                                                       \
        cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );         \
        cocos2d::log(__VA_ARGS__);                                        \
        if( ! JS_IsExceptionPending( context ) ) {                          \
            JS_ReportError( context, __VA_ARGS__ );                             \
        }                                                                       \
        return ret_value;                                                       \
    }                                                                           \
} while(0)
#define ASSERT( condition, error_msg) do {                                      \
    if( ! (condition) ) {                                                       \
        CCLOG("jsb: ERROR in %s: %s\n", __FUNCTION__, error_msg);               \
        return false;                                                           \
    }                                                                           \
    } while(0)
#endif

#define JSB_PRECONDITION3( condition, context, ret_value, ...) do { \
        if( ! (condition) ) return (ret_value); \
    } while(0)


/** @def JSB_REPRESENT_LONGLONG_AS_STR
 When JSB_REPRESENT_LONGLONG_AS_STR is defined, the long long will be represented as JS strings.
 Otherwise they will be represented as an array of two integers.
 It is needed to use an special representation since there are no 64-bit integers in JS.
 Representing the long long as string could be a bit slower, but it is easier to debug from JS.
 Enabled by default.
 */
#ifndef JSB_REPRESENT_LONGLONG_AS_STR
#define JSB_REPRESENT_LONGLONG_AS_STR 1
#endif // JSB_REPRESENT_LONGLONG_AS_STR


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

#define JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

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
