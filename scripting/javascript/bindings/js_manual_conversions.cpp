//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "jsapi.h"
#include "jsfriendapi.h"
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "js_manual_conversions.h"

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

//#include "js_bindings_NS_manual.h"


JSBool jsval_to_CCPoint( JSContext *cx, jsval vp, CCPoint *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *jsobj;
	if( ! JS_ValueToObject( cx, vp, &jsobj ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
	jsval valx, valy;
	JSBool ok = JS_TRUE;
	ok &= JS_GetProperty(cx, jsobj, "x", &valx);
	ok &= JS_GetProperty(cx, jsobj, "y", &valy);
    
	if( ! ok )
		return JS_FALSE;
	
	double x, y;
	ok &= JS_ValueToNumber(cx, valx, &x);
	ok &= JS_ValueToNumber(cx, valy, &y);
	
	if( ! ok )
		return JS_FALSE;
	
	ret->x = x;
	ret->y = y;
    
	return JS_TRUE;
    
#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
	
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");
	
	*ret = *(CCPoint*)JS_GetArrayBufferViewData( tmp_arg, cx );
	
	return JS_TRUE;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


JSBool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *jsobj;
	if( ! JS_ValueToObject( cx, vp, &jsobj ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
	jsval valx, valy;
	JSBool ok = JS_TRUE;
	ok &= JS_GetProperty(cx, jsobj, "x", &valx);
	ok &= JS_GetProperty(cx, jsobj, "y", &valy);
    
	if( ! ok )
		return JS_FALSE;
	
	double x, y;
	ok &= JS_ValueToNumber(cx, valx, &x);
	ok &= JS_ValueToNumber(cx, valy, &y);
	
	if( ! ok )
		return JS_FALSE;
	
	ret->x = x;
	ret->y = y;
    
	return JS_TRUE;
    
#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
	
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");
	
	*ret = *(cpVect*)JS_GetArrayBufferViewData( tmp_arg, cx );
	
	return JS_TRUE;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


jsval CGPoint_to_jsval( JSContext *cx, cpVect p)
{
	
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
	if (!object)
		return JSVAL_VOID;
    
	if (!JS_DefineProperty(cx, object, "x", DOUBLE_TO_JSVAL(p.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "y", DOUBLE_TO_JSVAL(p.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JSVAL_VOID;
	
	return OBJECT_TO_JSVAL(object);
    
#else // JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
	
#ifdef __LP64__
	JSObject *typedArray = JS_NewFloat64Array( cx, 2 );
#else
	JSObject *typedArray = JS_NewFloat32Array( cx, 2 );
#endif
    
	cpVect *buffer = (cpVect*)JS_GetArrayBufferViewData(typedArray, cx );
	*buffer = p;
	return OBJECT_TO_JSVAL(typedArray);
#endif // ! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}


JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **r)
{
#ifdef __LP64__
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;

	JSB_PRECONDITION( js_IsTypedArray( tmp_arg ), "jsb: Not a TypedArray object");

	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(void*), "jsb: Invalid Typed Array lenght");
	
	int32_t* arg_array = (int32_t*)JS_GetTypedArrayData( tmp_arg );
	uint64 ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
#else
	assert( sizeof(int)==4);
	int32_t ret;
	if( ! JS_ValueToInt32(cx, vp, &ret ) )
	  return JS_FALSE;
#endif
	*r = (void*)ret;
	return JS_TRUE;
}

JSBool jsval_to_int( JSContext *cx, jsval vp, int *ret )
{
	// Since this is called to cast uint64 to uint32,
	// it is needed to initialize the value to 0 first
#ifdef __LP64__
	long *tmp = (long*)ret;
	*tmp = 0;
#endif
	return JS_ValueToInt32(cx, vp, (int32_t*)ret);
}

// XXX: sizeof(long) == 8 in 64 bits on OS X... apparently on Windows it is 32 bits (???)
JSBool jsval_to_long( JSContext *cx, jsval vp, long *r )
{
#ifdef __LP64__
	// compatibility check
	assert( sizeof(long)==8);
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;

	JSB_PRECONDITION( js_IsTypedArray( tmp_arg ), "jsb: Not a TypedArray object");

	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long), "jsb: Invalid Typed Array lenght");
	
	int32_t* arg_array = (int32_t*)JS_GetTypedArrayData( tmp_arg );
	long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
#else
	// compatibility check
	assert( sizeof(int)==4);
	long ret = JSVAL_TO_INT(vp);
#endif
	
	*r = ret;
	return JS_TRUE;
}

JSBool jsval_to_longlong( JSContext *cx, jsval vp, long long *r )
{
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
    
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(long long), "Invalid Typed Array lenght");
	
	int32_t* arg_array = (int32_t*)JS_GetArrayBufferViewData( tmp_arg, cx );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return JS_TRUE;
}


jsval opaque_to_jsval( JSContext *cx, void *opaque )
{
#ifdef __LP64__
	uint64_t number = (uint64_t)opaque;
	JSObject *typedArray = js_CreateTypedArray(cx, js::TypedArray::TYPE_UINT32, 2);
	int32_t *buffer = (int32_t*)JS_GetTypedArrayData(typedArray);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);		
#else
	assert(sizeof(int)==4);
	int32_t number = (int32_t) opaque;
	return INT_TO_JSVAL(number);
#endif
}

jsval int_to_jsval( JSContext *cx, int number )
{
	return INT_TO_JSVAL(number);
}

jsval long_to_jsval( JSContext *cx, long number )
{
#ifdef __LP64__
	assert( sizeof(long)==8);

	JSObject *typedArray = js_CreateTypedArray(cx, js::TypedArray::TYPE_UINT32, 2);
	int32_t *buffer = (int32_t*)JS_GetTypedArrayData(typedArray);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);		
#else
	assert( sizeof(int)==4);
	return INT_TO_JSVAL(number);
#endif
}

JSBool jsval_to_cpBB( JSContext *cx, jsval vp, cpBB *ret )
{
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
	
	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpFloat)*4, "Invalid length");
	
	*ret = *(cpBB*)JS_GetArrayBufferViewData( tmp_arg, cx);
    
	return JS_TRUE;
}

jsval cpBB_to_jsval(JSContext *cx, cpBB bb )
{
#ifdef __LP64__
	JSObject *typedArray = JS_NewFloat64Array( cx, 4 );
#else
	JSObject *typedArray = JS_NewFloat32Array( cx, 4 );
#endif
	cpBB *buffer = (cpBB*)JS_GetArrayBufferViewData(typedArray, cx);
	
	*buffer = bb;
	return OBJECT_TO_JSVAL(typedArray);
}

jsval longlong_to_jsval( JSContext *cx, long long number )
{
	//NSCAssert( sizeof(long long)==8, @"Error!");
	JSObject *typedArray = JS_NewUint32Array( cx, 2 );
	int32_t *buffer = (int32_t*)JS_GetArrayBufferViewData(typedArray, cx);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);
}
