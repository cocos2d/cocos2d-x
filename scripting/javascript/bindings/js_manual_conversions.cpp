//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "jsapi.h"
#include "jsfriendapi.h"
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "js_manual_conversions.h"

JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **r)
{
#ifdef __LP64__
	JSObject *tmp_arg;
	if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
		return JS_FALSE;

	JSB_PRECONDITION( JS_IsTypedArrayObject( tmp_arg ), "jsb: Not a TypedArray object");

	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(void*), "jsb: Invalid Typed Array lenght");
	
    uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	uint64_t ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
#else
	assert( sizeof(int)==4);
	int32_t ret;
	if( ! jsval_to_int32(cx, vp, &ret ) )
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
	return jsval_to_int32(cx, vp, (int32_t*)ret);
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

	JSB_PRECONDITION( JS_IsTypedArrayObject( tmp_arg ), "jsb: Not a TypedArray object");

	JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long), "jsb: Invalid Typed Array lenght");
	
    uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
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
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
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
    JSObject *typedArray = JS_NewUint32Array( cx, 2 );
    uint32_t *buffer = (uint32_t*)JS_GetArrayBufferViewData(typedArray);
    buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);		
#else
	assert(sizeof(int)==4);
	int32_t number = (int32_t) opaque;
	return INT_TO_JSVAL(number);
#endif
}

jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name)
{
	JSObject *jsobj;
    
	jsobj = jsb_get_jsobject_for_proxy(handle);
	if( !jsobj ) {
		jsobj = JS_NewObject(cx, klass, object, NULL);
		CCAssert(jsobj, "Invalid object");
		jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
		jsb_set_jsobject_for_proxy(jsobj, handle);
	}
    
	return OBJECT_TO_JSVAL(jsobj);
}

JSBool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy)
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject(cx, vp, &jsobj);
	JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error converting jsval to object");
	
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);
	*out_native = proxy->handle;
	if( out_proxy )
		*out_proxy = proxy;
	return JS_TRUE;
}

JSBool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *ret )
{
	// Since this is called to cast uint64 to uint32,
	// it is needed to initialize the value to 0 first
#ifdef __LP64__
	long *tmp = (long*)ret;
	*tmp = 0;
#endif
	return jsval_to_int32(cx, vp, (int32_t*)ret);
}


JSBool JSB_jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
	JSBool ret = JS_FALSE;
	double dp;
	if( (ret=JS_ValueToNumber(cx, vp, &dp)) ) {
		if( isnan(dp))
			return JS_FALSE;
		*outval = (int32_t)dp;
	}
	return ret;
}

JSBool JSB_jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
	JSBool ret = JS_FALSE;
	double dp;
	if( (ret=JS_ValueToNumber(cx, vp, &dp)) ) {
		if( isnan(dp))
			return JS_FALSE;
		*outval = (uint32_t)dp;
	}
	return ret;
}

JSBool JSB_jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
	JSBool ret = JS_FALSE;
	double dp;
	if( (ret=JS_ValueToNumber(cx, vp, &dp)) ) {
		if( isnan(dp))
			return JS_FALSE;
		*outval = (uint16_t)dp;
	}
	return ret;
}

jsval int_to_jsval( JSContext *cx, int number )
{
	return INT_TO_JSVAL(number);
}

jsval uint_to_jsval( JSContext *cx, unsigned int number )
{
	return UINT_TO_JSVAL(number);
}

jsval long_to_jsval( JSContext *cx, long number )
{
#ifdef __LP64__
	assert( sizeof(long)==8);
    
	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%ld", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
#else
	CCAssert( sizeof(int)==4, "Error!");
	return INT_TO_JSVAL(number);
#endif
}

jsval longlong_to_jsval( JSContext *cx, long long number )
{
#if JSB_REPRESENT_LONGLONG_AS_STR
	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%lld", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
    
#else
	CCAssert( sizeof(long long)==8, "Error!");
	JSObject *typedArray = JS_NewUint32Array( cx, 2 );
	uint32_t *buffer = (uint32_t*)JS_GetArrayBufferViewData(typedArray, cx);
	buffer[0] = number >> 32;
	buffer[1] = number & 0xffffffff;
	return OBJECT_TO_JSVAL(typedArray);
#endif
}

JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **ret )
{
    JSString *jsstr = JS_ValueToString( cx, vp );
    JSB_PRECONDITION2( jsstr, cx, JS_FALSE, "invalid string" );

    // root it
    vp = STRING_TO_JSVAL(jsstr);

    JSStringWrapper strWrapper(jsstr);
    
    // XXX: It is converted to CCString and then back to char* to autorelease the created object.
    CCString *tmp = CCString::create(strWrapper.get());

    JSB_PRECONDITION2( tmp, cx, JS_FALSE, "Error creating string from UTF8");

    *ret = tmp->getCString();

    return JS_TRUE;
}

jsval charptr_to_jsval( JSContext *cx, const char *str)
{
    JSString *ret_obj = JS_NewStringCopyZ(cx, str);
    return STRING_TO_JSVAL(ret_obj);
}



JSBool JSB_jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t)
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, JS_FALSE, "Error converting value to object");
    
	// WebGL supports TypedArray and sequences for some of its APIs. So when converting a TypedArray, we should
	// also check for a possible non-Typed Array JS object, like a JS Array.
    
	if( JS_IsTypedArrayObject( jsobj ) ) {
        
		*count = JS_GetTypedArrayLength(jsobj);
		JSArrayBufferViewType type = JS_GetArrayBufferViewType(jsobj);
		JSB_PRECONDITION2(t==type, cx, JS_FALSE, "TypedArray type different than expected type");
        
		switch (t) {
			case js::ArrayBufferView::TYPE_INT8:
			case js::ArrayBufferView::TYPE_UINT8:
				*data = JS_GetUint8ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_INT16:
			case js::ArrayBufferView::TYPE_UINT16:
				*data = JS_GetUint16ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_INT32:
			case js::ArrayBufferView::TYPE_UINT32:
				*data = JS_GetUint32ArrayData(jsobj);
				break;
                
			case js::ArrayBufferView::TYPE_FLOAT32:
				*data = JS_GetFloat32ArrayData(jsobj);
				break;
                
			default:
				JSB_PRECONDITION2(false, cx, JS_FALSE, "Unsupported typedarray type");
				break;
		}
	} else if( JS_IsArrayObject(cx, jsobj)) {
		// Slow... avoid it. Use TypedArray instead, but the spec says that it can receive
		// Sequence<> as well.
		uint32_t length;
		JS_GetArrayLength(cx, jsobj, &length);
        
		for( uint32_t i=0; i<length;i++ ) {
            
			jsval valarg;
			JS_GetElement(cx, jsobj, i, &valarg);
            
			switch(t) {
				case js::ArrayBufferView::TYPE_INT32:
				case js::ArrayBufferView::TYPE_UINT32:
				{
					uint32_t e = JSVAL_TO_INT(valarg);
					((uint32_t*)data)[i] = e;
					break;
				}
				case js::ArrayBufferView::TYPE_FLOAT32:
				{
					double e = JSVAL_TO_DOUBLE(valarg);
					((GLfloat*)data)[i] = (GLfloat)e;
					break;
				}
				default:
					JSB_PRECONDITION2(false, cx, JS_FALSE, "Unsupported typedarray type");
					break;
			}
		}
        
	} else
		JSB_PRECONDITION2(false, cx, JS_FALSE, "Object shall be a TypedArray or Sequence");
    
	return JS_TRUE;
}

JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data )
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION2( ok && jsobj, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( JS_IsArrayBufferViewObject(jsobj), cx, JS_FALSE, "Not an ArrayBufferView object");
    
	*data = JS_GetArrayBufferViewData(jsobj);
	*count = JS_GetArrayBufferViewByteLength(jsobj);
    
	return JS_TRUE;
}



