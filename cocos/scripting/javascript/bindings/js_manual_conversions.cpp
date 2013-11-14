//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "jsapi.h"
#include "jsfriendapi.h"
#include "ScriptingCore.h"
#include "js_bindings_config.h"
#include "js_manual_conversions.h"
#include "cocos2d_specifics.hpp"

USING_NS_CC;

static Color3B getColorFromJSObject(JSContext *cx, JSObject *colorObject)
{
    JS::RootedValue jsr(cx);
    Color3B out;
    JS_GetProperty(cx, colorObject, "r", &jsr);
    double fontR = 0.0;
    JS_ValueToNumber(cx, jsr, &fontR);
    
    JS_GetProperty(cx, colorObject, "g", &jsr);
    double fontG = 0.0;
    JS_ValueToNumber(cx, jsr, &fontG);
    
    JS_GetProperty(cx, colorObject, "b", &jsr);
    double fontB = 0.0;
    JS_ValueToNumber(cx, jsr, &fontB);
    
    // the out
    out.r = (unsigned char)fontR;
    out.g = (unsigned char)fontG;
    out.b = (unsigned char)fontB;
    
    return out;
}

static Size getSizeFromJSObject(JSContext *cx, JSObject *sizeObject)
{
    JS::RootedValue jsr(cx);
    Size out;
    JS_GetProperty(cx, sizeObject, "width", &jsr);
    double width = 0.0;
    JS_ValueToNumber(cx, jsr, &width);
    
    JS_GetProperty(cx, sizeObject, "height", &jsr);
    double height = 0.0;
    JS_ValueToNumber(cx, jsr, &height);
    
    
    // the out
    out.width  = width;
    out.height = height;
    
    return out;
}

JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **r)
{
#ifdef __LP64__

    // begin
	JSObject *tmp_arg;
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(void*), cx, JS_FALSE, "Invalid Typed Array length");

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
	JSString *jsstr = JS_ValueToString(cx, vp);
	JSB_PRECONDITION2(jsstr, cx, JS_FALSE, "Error converting value to string");

	char *str = JS_EncodeString(cx, jsstr);
	JSB_PRECONDITION2(str, cx, JS_FALSE, "Error encoding string");

	char *endptr;
	long ret = strtol(str, &endptr, 10);

	*r = ret;
	return JS_TRUE;

#else
	// compatibility check
	assert( sizeof(int)==4);
	long ret = JSVAL_TO_INT(vp);
#endif
	
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
		CCASSERT(jsobj, "Invalid object");
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

jsval long_to_jsval( JSContext *cx, long number )
{
#ifdef __LP64__
	assert( sizeof(long)==8);

	char chr[128];
	snprintf(chr, sizeof(chr)-1, "%ld", number);
	JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
	return STRING_TO_JSVAL(ret_obj);
#else
	CCASSERT( sizeof(int)==4, "Error!");
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
	CCASSERT( sizeof(long long)==8, "Error!");
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
    
    // XXX: It is converted to String and then back to char* to autorelease the created object.
    String *tmp = String::create(strWrapper.get());

    JSB_PRECONDITION2( tmp, cx, JS_FALSE, "Error creating string from UTF8");

    *ret = tmp->getCString();

    return JS_TRUE;
}

jsval charptr_to_jsval( JSContext *cx, const char *str)
{
    return c_string_to_jsval(cx, str);
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


#pragma mark - Conversion Routines
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (int32_t)dp;
    
    return ok;
}

JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (uint32_t)dp;
    
    return ok;
}

JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    *outval = (uint16_t)dp;
    
    return ok;
}

JSBool jsval_to_long_long(JSContext *cx, jsval vp, long long* r) {
	JSObject *tmp_arg;
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION3( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	JSB_PRECONDITION3( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return JS_TRUE;
}

JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JSString *tmp = JS_ValueToString(cx, v);
    JSB_PRECONDITION3(tmp, cx, JS_FALSE, "Error processing arguments");
    
    JSStringWrapper str(tmp);
    *ret = str.get();
    return JS_TRUE;
}

JSBool jsval_to_ccpoint(JSContext *cx, jsval v, Point* ret) {
    JSObject *tmp;
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    double x, y;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return JS_TRUE;
}

JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, Acceleration* ret) {
    JSObject *tmp;
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    JS::RootedValue jstimestamp(cx);
    
    double x, y, timestamp, z;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "timestamp", &jstimestamp) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y) &&
    JS_ValueToNumber(cx, jsz, &z) &&
    JS_ValueToNumber(cx, jstimestamp, &timestamp);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->x = x;
    ret->y = y;
    ret->z = z;
    ret->timestamp = timestamp;
    return JS_TRUE;
}

JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, Array** ret)
{
    JSBool ok = JS_TRUE;
    Array* pArray = Array::create();
    for( int i=0; i < argc; i++ )
    {
        double num = 0.0;
        // optimization: JS_ValueToNumber is expensive. And can convert an string like "12" to a number
        if ( JSVAL_IS_NUMBER(*vp)) {
            ok &= JS_ValueToNumber(cx, *vp, &num );
            if (!ok) {
                break;
            }
            pArray->addObject(Integer::create((int)num));
        }
        else if (JSVAL_IS_STRING(*vp))
        {
            JSStringWrapper str(JSVAL_TO_STRING(*vp), cx);
            pArray->addObject(String::create(str.get()));
        }
        else
        {
            js_proxy_t* p;
            JSObject* obj = JSVAL_TO_OBJECT(*vp);
            p = jsb_get_js_proxy(obj);
            if (p) {
                pArray->addObject((Object*)p->ptr);
            }
        }
        // next
        vp++;
    }
    *ret = pArray;
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    return ok;
}

JSBool jsval_to_ccrect(JSContext *cx, jsval v, Rect* ret) {
    JSObject *tmp;
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jswidth(cx);
    JS::RootedValue jsheight(cx);
    
    double x, y, width, height;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "width", &jswidth) &&
    JS_GetProperty(cx, tmp, "height", &jsheight) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y) &&
    JS_ValueToNumber(cx, jswidth, &width) &&
    JS_ValueToNumber(cx, jsheight, &height);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->origin.x = x;
    ret->origin.y = y;
    ret->size.width = width;
    ret->size.height = height;
    return JS_TRUE;
}

JSBool jsval_to_ccsize(JSContext *cx, jsval v, Size* ret) {
    JSObject *tmp;
    JS::RootedValue jsw(cx);
    JS::RootedValue jsh(cx);
    double w, h;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "width", &jsw) &&
    JS_GetProperty(cx, tmp, "height", &jsh) &&
    JS_ValueToNumber(cx, jsw, &w) &&
    JS_ValueToNumber(cx, jsh, &h);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    ret->width = w;
    ret->height = h;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, Color4B* ret) {
    JSObject *tmp;
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    
    double r, g, b, a;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b) &&
    JS_ValueToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, Color4F* ret) {
    JSObject *tmp;
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    double r, g, b, a;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b) &&
    JS_ValueToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, Color3B* ret) {
    JSObject *tmp;
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    double r, g, b;
    JSBool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_ValueToNumber(cx, jsr, &r) &&
    JS_ValueToNumber(cx, jsg, &g) &&
    JS_ValueToNumber(cx, jsb, &b);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    ret->r = r;
    ret->g = g;
    ret->b = b;
    return JS_TRUE;
}

JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, Point **points, int *numPoints) {
    // Parsing sequence
    JSObject *jsobj;
    JSBool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, JS_FALSE, "Object must be an array");
    
    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);
    
    Point *array = (Point*)malloc( sizeof(Point) * len);
    
    for( uint32_t i=0; i< len;i++ ) {
        jsval valarg;
        JS_GetElement(cx, jsobj, i, &valarg);
        
        ok = jsval_to_ccpoint(cx, valarg, &array[i]);
        JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    }
    
    *numPoints = len;
    *points = array;
    
    return JS_TRUE;
}


JSBool jsval_to_ccarray(JSContext* cx, jsval v, Array** ret) {
    JSObject *jsobj;
    JSBool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    Array* arr = Array::createWithCapacity(len);
    for (uint32_t i=0; i < len; i++) {
        jsval value;
        if (JS_GetElement(cx, jsobj, i, &value)) {
            if (value.isObject())
            {
                js_proxy_t *proxy;
                JSObject *tmp = JSVAL_TO_OBJECT(value);
                proxy = jsb_get_js_proxy(tmp);
                cocos2d::Object* cobj = (cocos2d::Object *)(proxy ? proxy->ptr : NULL);
                // Don't test it.
                //TEST_NATIVE_OBJECT(cx, cobj)
                if (cobj) {
                    // It's a native js object.
                    arr->addObject(cobj);
                }
                else if (!JS_IsArrayObject(cx, tmp)){
                    // It's a normal js object.
                    Dictionary* dictVal = NULL;
                    JSBool ok = jsval_to_ccdictionary(cx, value, &dictVal);
                    if (ok) {
                        arr->addObject(dictVal);
                    }
                }
                else {
                    // It's a js array object.
                    Array* arrVal = NULL;
                    JSBool ok = jsval_to_ccarray(cx, value, &arrVal);
                    if (ok) {
                        arr->addObject(arrVal);
                    }
                }
            }
            else if (JSVAL_IS_STRING(value)) {
                JSStringWrapper valueWapper(JSVAL_TO_STRING(value), cx);
                arr->addObject(String::create(valueWapper.get()));
                //                CCLOG("iterate array: value = %s", valueWapper.get().c_str());
            }
            else if (JSVAL_IS_NUMBER(value)) {
                double number = 0.0;
                JSBool ok = JS_ValueToNumber(cx, value, &number);
                if (ok) {
                    arr->addObject(Double::create(number));
                    //                    CCLOG("iterate array: value = %lf", number);
                }
            }
            else if (JSVAL_IS_BOOLEAN(value)) {
                JSBool boolVal = JS_FALSE;
                JSBool ok = JS_ValueToBoolean(cx, value, &boolVal);
                if (ok) {
                    arr->addObject(Bool::create(boolVal));
                    //                    CCLOG("iterate object: value = %d", boolVal);
                }
            }
            else {
                CCASSERT(false, "not supported type");
            }
        }
    }
    *ret = arr;
    return JS_TRUE;
}


jsval ccarray_to_jsval(JSContext* cx, Array *arr)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);
    
    Object* obj;
    int i = 0;
    CCARRAY_FOREACH(arr, obj)
    {
        jsval arrElement;
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Object>(cx, obj);
        if (jsproxy) {
            arrElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        else {
            String* strVal = NULL;
            Dictionary* dictVal = NULL;
            Array* arrVal = NULL;
            Double* doubleVal = NULL;
            Bool* boolVal = NULL;
            Float* floatVal = NULL;
            Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::String *>(obj))) {
                arrElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<cocos2d::Dictionary*>(obj))) {
                arrElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<cocos2d::Array*>(obj))) {
                arrElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<Double*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<Float*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<Integer*>(obj))) {
                arrElement = INT_TO_JSVAL(intVal->getValue());
            }  else if ((boolVal = dynamic_cast<Bool*>(obj))) {
                arrElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? JS_TRUE : JS_FALSE);
            } else {
                CCASSERT(false, "the type isn't suppored.");
            }
        }
        if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ccdictionary_to_jsval(JSContext* cx, Dictionary* dict)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
    DictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        JS::RootedValue dictElement(cx);
        Object* obj = pElement->getObject();
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Object>(cx, obj);
        if (jsproxy) {
            dictElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        else {
            String* strVal = NULL;
            Dictionary* dictVal = NULL;
            Array* arrVal = NULL;
            Double* doubleVal = NULL;
            Bool* boolVal = NULL;
            Float* floatVal = NULL;
            Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::String *>(obj))) {
                dictElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<Dictionary*>(obj))) {
                dictElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<Array*>(obj))) {
                dictElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<Double*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<Float*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<Integer*>(obj))) {
                dictElement = INT_TO_JSVAL(intVal->getValue());
            } else if ((boolVal = dynamic_cast<Bool*>(obj))) {
                dictElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? JS_TRUE : JS_FALSE);
            } else {
                CCASSERT(false, "the type isn't suppored.");
            }
        }
        const char* key = pElement->getStrKey();
        if (key && strlen(key) > 0)
        {
            JS_SetProperty(cx, jsRet, key, dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, Dictionary** ret)
{
    if (JSVAL_IS_NULL(v) || JSVAL_IS_VOID(v))
    {
        *ret = NULL;
        return JS_TRUE;
    }
    
    JSObject* tmp = JSVAL_TO_OBJECT(v);
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccdictionary: the jsval is not an object.");
        return JS_FALSE;
    }
    
    JSObject* it = JS_NewPropertyIterator(cx, tmp);
    Dictionary* dict = NULL;
    
    while (true)
    {
        jsid idp;
        jsval key;
        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
            return JS_FALSE; // error
        }
        
        if (key == JSVAL_VOID) {
            break; // end of iteration
        }
        
        if (!JSVAL_IS_STRING(key)) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);
        if (!dict) {
            dict = Dictionary::create();
        }
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            js_proxy_t *proxy;
            JSObject *tmp = JSVAL_TO_OBJECT(value);
            proxy = jsb_get_js_proxy(tmp);
            cocos2d::Object* cobj = (cocos2d::Object *)(proxy ? proxy->ptr : NULL);
            // Don't test it.
            //TEST_NATIVE_OBJECT(cx, cobj)
            if (cobj) {
                // It's a native <-> js glue object.
                dict->setObject(cobj, keyWrapper.get());
            }
            else if (!JS_IsArrayObject(cx, tmp)){
                // It's a normal js object.
                Dictionary* dictVal = NULL;
                JSBool ok = jsval_to_ccdictionary(cx, value, &dictVal);
                if (ok) {
                    dict->setObject(dictVal, keyWrapper.get());
                }
            }
            else {
                // It's a js array object.
                Array* arrVal = NULL;
                JSBool ok = jsval_to_ccarray(cx, value, &arrVal);
                if (ok) {
                    dict->setObject(arrVal, keyWrapper.get());
                }
            }
        }
        else if (JSVAL_IS_STRING(value)) {
            JSStringWrapper valueWapper(JSVAL_TO_STRING(value), cx);
            dict->setObject(String::create(valueWapper.get()), keyWrapper.get());
            //            CCLOG("iterate object: key = %s, value = %s", keyWrapper.get().c_str(), valueWapper.get().c_str());
        }
        else if (JSVAL_IS_NUMBER(value)) {
            double number = 0.0;
            JSBool ok = JS_ValueToNumber(cx, value, &number);
            if (ok) {
                dict->setObject(Double::create(number), keyWrapper.get());
                //                CCLOG("iterate object: key = %s, value = %lf", keyWrapper.get().c_str(), number);
            }
        }
        else if (JSVAL_IS_BOOLEAN(value)) {
            JSBool boolVal = JS_FALSE;
            JSBool ok = JS_ValueToBoolean(cx, value, &boolVal);
            if (ok) {
                dict->setObject(Bool::create(boolVal), keyWrapper.get());
                //                CCLOG("iterate object: key = %s, value = %d", keyWrapper.get().c_str(), boolVal);
            }
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    *ret = dict;
    return JS_TRUE;
}

JSBool jsval_to_ccaffinetransform(JSContext* cx, jsval v, AffineTransform* ret)
{
    JSObject *tmp;
    JS::RootedValue jsa(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsc(cx);
    JS::RootedValue jsd(cx);
    JS::RootedValue jstx(cx);
    JS::RootedValue jsty(cx);
    double a, b, c, d, tx, ty;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "c", &jsc) &&
    JS_GetProperty(cx, tmp, "d", &jsd) &&
    JS_GetProperty(cx, tmp, "tx", &jstx) &&
    JS_GetProperty(cx, tmp, "ty", &jsty) &&
    JS_ValueToNumber(cx, jsa, &a) &&
    JS_ValueToNumber(cx, jsb, &b) &&
    JS_ValueToNumber(cx, jsc, &c) &&
    JS_ValueToNumber(cx, jsd, &d) &&
    JS_ValueToNumber(cx, jstx, &tx) &&
    JS_ValueToNumber(cx, jsty, &ty);
    
    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    
    *ret = AffineTransformMake(a, b, c, d, tx, ty);
    return JS_TRUE;
}

// From native type to jsval
jsval int32_to_jsval( JSContext *cx, int32_t number )
{
    return INT_TO_JSVAL(number);
}

jsval uint32_to_jsval( JSContext *cx, uint32_t number )
{
    return UINT_TO_JSVAL(number);
}

jsval std_string_to_jsval(JSContext* cx, const std::string& v)
{
    return c_string_to_jsval(cx, v.c_str(), v.size());
}

jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length /* = -1 */)
{
    if (v == NULL)
    {
        return JSVAL_NULL;
    }
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    if (0 == length)
    {
        auto emptyStr = JS_NewStringCopyZ(cx, "");
        return STRING_TO_JSVAL(emptyStr);
    }
    
    jsval ret = JSVAL_NULL;
    int utf16_size = 0;
    jschar* strUTF16 = (jschar*)cc_utf8_to_utf16(v, length, &utf16_size);
    
    if (strUTF16 && utf16_size > 0) {
        JSString* str = JS_NewUCStringCopyN(cx, strUTF16, utf16_size);
        if (str) {
            ret = STRING_TO_JSVAL(str);
        }
        delete[] strUTF16;
    }
    return ret;
}

jsval ccpoint_to_jsval(JSContext* cx, const Point& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccacceleration_to_jsval(JSContext* cx, const Acceleration& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", DOUBLE_TO_JSVAL(v.z), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timestamp", DOUBLE_TO_JSVAL(v.timestamp), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccrect_to_jsval(JSContext* cx, const Rect& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.origin.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.origin.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.size.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.size.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccsize_to_jsval(JSContext* cx, const Size& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4b_to_jsval(JSContext* cx, const Color4B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", INT_TO_JSVAL(v.a), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4f_to_jsval(JSContext* cx, const Color4F& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(v.a), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor3b_to_jsval(JSContext* cx, const Color3B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccaffinetransform_to_jsval(JSContext* cx, const AffineTransform& t)
{
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(t.a), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(t.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "c", DOUBLE_TO_JSVAL(t.c), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "d", DOUBLE_TO_JSVAL(t.d), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "tx", DOUBLE_TO_JSVAL(t.tx), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "ty", DOUBLE_TO_JSVAL(t.ty), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval FontDefinition_to_jsval(JSContext* cx, const FontDefinition& t)
{
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_TRUE;
    
    ok &= JS_DefineProperty(cx, tmp, "fontName", std_string_to_jsval(cx, t._fontName), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "fontSize", int32_to_jsval(cx, t._fontSize), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "fontAlignmentH", int32_to_jsval(cx, (int32_t)t._alignment), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "fontAlignmentV", int32_to_jsval(cx, (int32_t)t._vertAlignment), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "fontFillColor", cccolor3b_to_jsval(cx, t._fontFillColor), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "fontDimensions", ccsize_to_jsval(cx, t._dimensions), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Shadow
    ok &= JS_DefineProperty(cx, tmp, "shadowEnabled", BOOLEAN_TO_JSVAL(t._shadow._shadowEnabled), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "shadowOffset", ccsize_to_jsval(cx, t._shadow._shadowOffset), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "shadowBlur", DOUBLE_TO_JSVAL(t._shadow._shadowBlur), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "shadowOpacity", DOUBLE_TO_JSVAL(t._shadow._shadowOpacity), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Stroke
    ok &= JS_DefineProperty(cx, tmp, "strokeEnabled", BOOLEAN_TO_JSVAL(t._stroke._strokeEnabled), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "strokeColor", cccolor3b_to_jsval(cx, t._stroke._strokeColor), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    ok &= JS_DefineProperty(cx, tmp, "strokeSize", DOUBLE_TO_JSVAL(t._stroke._strokeSize), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

JSBool jsval_to_FontDefinition( JSContext *cx, jsval vp, FontDefinition *out )
{
    JSObject *jsobj;
    
	if (!JS_ValueToObject( cx, vp, &jsobj ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
    // defaul values
    const char *            defautlFontName         = "Arial";
    const int               defaultFontSize         = 32;
    TextHAlignment         defaultTextAlignment    = TextHAlignment::LEFT;
    TextVAlignment defaultTextVAlignment   = TextVAlignment::TOP;
    
    // by default shadow and stroke are off
    out->_shadow._shadowEnabled = false;
    out->_stroke._strokeEnabled = false;
    
    // white text by default
    out->_fontFillColor = Color3B::WHITE;
    
    // font name
    JS::RootedValue jsr(cx);
    JS_GetProperty(cx, jsobj, "fontName", &jsr);
    JS_ValueToString(cx, jsr);
    JSStringWrapper wrapper(jsr);
    const char* fontName = wrapper.get();
    
    if (fontName && strlen(fontName) > 0)
    {
        out->_fontName  = fontName;
    }
    else
    {
        out->_fontName  = defautlFontName;
    }
    
    // font size
    JSBool hasProperty;
    JS_HasProperty(cx, jsobj, "fontSize", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontSize", &jsr);
        double fontSize = 0.0;
        JS_ValueToNumber(cx, jsr, &fontSize);
        out->_fontSize  = fontSize;
    }
    else
    {
        out->_fontSize  = defaultFontSize;
    }
    
    // font alignment horizontal
    JS_HasProperty(cx, jsobj, "fontAlignmentH", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontAlignmentH", &jsr);
        double fontAlign = 0.0;
        JS_ValueToNumber(cx, jsr, &fontAlign);
        out->_alignment = (TextHAlignment)(int)fontAlign;
    }
    else
    {
        out->_alignment  = defaultTextAlignment;
    }
    
    // font alignment vertical
    JS_HasProperty(cx, jsobj, "fontAlignmentV", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontAlignmentV", &jsr);
        double fontAlign = 0.0;
        JS_ValueToNumber(cx, jsr, &fontAlign);
        out->_vertAlignment = (TextVAlignment)(int)fontAlign;
    }
    else
    {
        out->_vertAlignment  = defaultTextVAlignment;
    }
    
    // font fill color
    JS_HasProperty(cx, jsobj, "fontFillColor", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontFillColor", &jsr);
        
        JSObject *jsobjColor;
        if (!JS_ValueToObject( cx, jsr, &jsobjColor ) )
            return JS_FALSE;
        
        out->_fontFillColor = getColorFromJSObject(cx, jsobjColor);
    }
    
    // font rendering box dimensions
    JS_HasProperty(cx, jsobj, "fontDimensions", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontDimensions", &jsr);
        
        JSObject *jsobjSize;
        if (!JS_ValueToObject( cx, jsr, &jsobjSize ) )
            return JS_FALSE;
        
        out->_dimensions = getSizeFromJSObject(cx, jsobjSize);
    }
    
    // shadow
    JS_HasProperty(cx, jsobj, "shadowEnabled", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "shadowEnabled", &jsr);
        out->_shadow._shadowEnabled  = ToBoolean(jsr);
        
        if ( out->_shadow._shadowEnabled )
        {
            // default shadow values
            out->_shadow._shadowOffset  = Size(5, 5);
            out->_shadow._shadowBlur    = 1;
            out->_shadow._shadowOpacity = 1;
            
            // shado offset
            JS_HasProperty(cx, jsobj, "shadowOffset", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowOffset", &jsr);
                
                JSObject *jsobjShadowOffset;
                if (!JS_ValueToObject( cx, jsr, &jsobjShadowOffset ) )
                    return JS_FALSE;
                out->_shadow._shadowOffset = getSizeFromJSObject(cx, jsobjShadowOffset);
            }
            
            // shadow blur
            JS_HasProperty(cx, jsobj, "shadowBlur", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowBlur", &jsr);
                double shadowBlur = 0.0;
                JS_ValueToNumber(cx, jsr, &shadowBlur);
                out->_shadow._shadowBlur = shadowBlur;
            }
            
            // shadow intensity
            JS_HasProperty(cx, jsobj, "shadowOpacity", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowOpacity", &jsr);
                double shadowOpacity = 0.0;
                JS_ValueToNumber(cx, jsr, &shadowOpacity);
                out->_shadow._shadowOpacity = shadowOpacity;
            }
        }
    }
    
    // stroke
    JS_HasProperty(cx, jsobj, "strokeEnabled", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "strokeEnabled", &jsr);
        out->_stroke._strokeEnabled  = ToBoolean(jsr);
        
        if ( out->_stroke._strokeEnabled )
        {
            // default stroke values
            out->_stroke._strokeSize  = 1;
            out->_stroke._strokeColor = Color3B::BLUE;
            
            // stroke color
            JS_HasProperty(cx, jsobj, "strokeColor", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "strokeColor", &jsr);
                
                JSObject *jsobjStrokeColor;
                if (!JS_ValueToObject( cx, jsr, &jsobjStrokeColor ) )
                    return JS_FALSE;
                out->_stroke._strokeColor = getColorFromJSObject(cx, jsobjStrokeColor);
            }
            
            // stroke size
            JS_HasProperty(cx, jsobj, "strokeSize", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "strokeSize", &jsr);
                double strokeSize = 0.0;
                JS_ValueToNumber(cx, jsr, &strokeSize);
                out->_stroke._strokeSize = strokeSize;
            }
        }
    }
    
    // we are done here
	return JS_TRUE;
}

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

JSBool jsval_to_CCPoint( JSContext *cx, jsval vp, Point *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
	JSObject *jsobj;
	if( ! JS_ValueToObject( cx, vp, &jsobj ) )
		return JS_FALSE;
	
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
    JS::RootedValue valx(cx);
    JS::RootedValue valy(cx);
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
	
	*ret = *(Point*)JS_GetArrayBufferViewData( tmp_arg, cx );
	
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
    
    JS::RootedValue valx(cx);
    JS::RootedValue valy(cx);
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
