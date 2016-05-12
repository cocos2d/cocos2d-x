/*
 * Created by Rohan Kuruvilla
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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

#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "math/TransformUtils.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;

// JSStringWrapper
JSStringWrapper::JSStringWrapper()
: _buffer(nullptr)
{
}

JSStringWrapper::JSStringWrapper(JSString* str, JSContext* cx/* = NULL*/)
: _buffer(nullptr)
{
    set(str, cx);
}

JSStringWrapper::JSStringWrapper(jsval val, JSContext* cx/* = NULL*/)
: _buffer(nullptr)
{
    set(val, cx);
}

JSStringWrapper::~JSStringWrapper()
{
    JS_free(ScriptingCore::getInstance()->getGlobalContext(), (void*)_buffer);
}

void JSStringWrapper::set(jsval val, JSContext* cx)
{
    if (val.isString())
    {
        this->set(val.toString(), cx);
    }
    else
    {
        CC_SAFE_DELETE_ARRAY(_buffer);
    }
}

void JSStringWrapper::set(JSString* str, JSContext* cx)
{
    CC_SAFE_DELETE_ARRAY(_buffer);
    
    if (!cx)
    {
        cx = ScriptingCore::getInstance()->getGlobalContext();
    }
    JS::RootedString jsstr(cx, str);
    _buffer = JS_EncodeStringToUTF8(cx, jsstr);
}

const char* JSStringWrapper::get()
{
    return _buffer ? _buffer : "";
}

// JSFunctionWrapper
JSFunctionWrapper::JSFunctionWrapper(JSContext* cx, JS::HandleObject jsthis, JS::HandleValue fval)
: _cx(cx)
{
    _jsthis = jsthis;
    _fval = fval;
    
    JS::RootedObject root(cx);
    get_or_create_js_obj("jsb._root", &root);
    JS::RootedValue valRoot(cx, OBJECT_TO_JSVAL(root));
    _owner = valRoot;
    
    if (!valRoot.isNullOrUndefined())
    {
        JS::RootedValue thisVal(cx, OBJECT_TO_JSVAL(_jsthis));
        if (!thisVal.isNullOrUndefined())
        {
            js_add_object_reference(valRoot, thisVal);
        }
        JS::RootedValue funcVal(cx, _fval);
        if (!funcVal.isNullOrUndefined())
        {
            js_add_object_reference(valRoot, funcVal);
        }
    }
}
JSFunctionWrapper::JSFunctionWrapper(JSContext* cx, JS::HandleObject jsthis, JS::HandleValue fval, JS::HandleValue owner)
: _cx(cx)
{
    _jsthis = jsthis;
    _fval = fval;
    _owner = owner;
    JS::RootedValue ownerVal(cx, owner);
    
    JS::RootedValue thisVal(cx, OBJECT_TO_JSVAL(jsthis));
    if (!thisVal.isNullOrUndefined())
    {
        js_add_object_reference(ownerVal, thisVal);
    }
    JS::RootedValue funcVal(cx, _fval);
    if (!funcVal.isNullOrUndefined())
    {
        js_add_object_reference(ownerVal, funcVal);
    }
}

JSFunctionWrapper::~JSFunctionWrapper()
{
    JS::RootedValue ownerVal(_cx, _owner);
    
    if (!ownerVal.isNullOrUndefined())
    {
        JS::RootedValue thisVal(_cx, OBJECT_TO_JSVAL(_jsthis));
        if (!thisVal.isNullOrUndefined())
        {
            js_remove_object_reference(ownerVal, thisVal);
        }
        JS::RootedValue funcVal(_cx, _fval);
        if (!funcVal.isNullOrUndefined())
        {
            js_remove_object_reference(ownerVal, funcVal);
        }
    }
}

bool JSFunctionWrapper::invoke(unsigned int argc, jsval *argv, JS::MutableHandleValue rval)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JS::RootedObject thisObj(_cx, _jsthis);
    JS::RootedValue fval(_cx, _fval);
    return JS_CallFunctionValue(_cx, thisObj, fval, JS::HandleValueArray::fromMarkedLocation(argc, argv), rval);
}

static Color3B getColorFromJSObject(JSContext *cx, JS::HandleObject colorObject)
{
    JS::RootedValue jsr(cx);
    Color3B out;
    JS_GetProperty(cx, colorObject, "r", &jsr);
    double fontR = 0.0;
    JS::ToNumber(cx, jsr, &fontR);
    
    JS_GetProperty(cx, colorObject, "g", &jsr);
    double fontG = 0.0;
    JS::ToNumber(cx, jsr, &fontG);
    
    JS_GetProperty(cx, colorObject, "b", &jsr);
    double fontB = 0.0;
    JS::ToNumber(cx, jsr, &fontB);
    
    // the out
    out.r = (unsigned char)fontR;
    out.g = (unsigned char)fontG;
    out.b = (unsigned char)fontB;
    
    return out;
}

static Size getSizeFromJSObject(JSContext *cx, JS::HandleObject sizeObject)
{
    JS::RootedValue jsr(cx);
    Size out;
    JS_GetProperty(cx, sizeObject, "width", &jsr);
    double width = 0.0;
    JS::ToNumber(cx, jsr, &width);
    
    JS_GetProperty(cx, sizeObject, "height", &jsr);
    double height = 0.0;
    JS::ToNumber(cx, jsr, &height);
    
    
    // the out
    out.width  = width;
    out.height = height;
    
    return out;
}

bool jsval_to_opaque( JSContext *cx, JS::HandleValue vp, void **r)
{
#ifdef __LP64__

    // begin
    JS::RootedObject tmp_arg(cx);
    bool ok = JS_ValueToObject( cx, vp, &tmp_arg );
    JSB_PRECONDITION2( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, false, "Not a TypedArray object");
    JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(void*), cx, false, "Invalid Typed Array length");

    uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
    uint64_t ret =  arg_array[0];
    ret = ret << 32;
    ret |= arg_array[1];

#else
    assert( sizeof(int)==4);
    int32_t ret;
    if( ! jsval_to_int32(cx, vp, &ret ) )
      return false;
#endif
    *r = (void*)ret;
    return true;
}

bool jsval_to_int( JSContext *cx, JS::HandleValue vp, int *ret )
{
    // Since this is called to cast uint64 to uint32,
    // it is needed to initialize the value to 0 first
#ifdef __LP64__
    // When int size is 8 Bit (same as long), the following operation is needed
    if (sizeof(int) == 8)
    {
        long *tmp = (long*)ret;
        *tmp = 0;
    }
#endif
    return jsval_to_int32(cx, vp, (int32_t*)ret);
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

jsval c_class_to_jsval( JSContext *cx, void* handle, JS::HandleObject object, JSClass *klass, const char* class_name)
{
    JS::RootedObject jsobj(cx);
    
    jsobj = jsb_get_jsobject_for_proxy(handle);
    if( !jsobj ) {
        JS::RootedObject parent(cx);
        jsobj = JS_NewObject(cx, klass, object, parent);
        CCASSERT(jsobj, "Invalid object");
        jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
        jsb_set_jsobject_for_proxy(jsobj, handle);
    }
    
    return OBJECT_TO_JSVAL(jsobj);
}

bool jsval_to_c_class( JSContext *cx, JS::HandleValue vp, void **out_native, struct jsb_c_proxy_s **out_proxy)
{
    JS::RootedObject jsobj(cx);
    bool ok = JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION2(ok, cx, false, "Error converting jsval to object");
    
    struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);
    *out_native = proxy->handle;
    if( out_proxy )
        *out_proxy = proxy;
    return true;
}

bool jsval_to_uint( JSContext *cx, JS::HandleValue vp, unsigned int *ret )
{
    // Since this is called to cast uint64 to uint32,
    // it is needed to initialize the value to 0 first
#ifdef __LP64__
    // When unsigned int size is 8 Bit (same as long), the following operation is needed
    if (sizeof(unsigned int)==8)
    {
        long *tmp = (long*)ret;
        *tmp = 0;
    }
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

jsval ulong_to_jsval( JSContext *cx, unsigned long number )
{
#ifdef __LP64__
    assert( sizeof(unsigned long)==8);
    
    char chr[128];
    snprintf(chr, sizeof(chr)-1, "%lu", number);
    JSString *ret_obj = JS_NewStringCopyZ(cx, chr);
    return STRING_TO_JSVAL(ret_obj);
#else
    CCASSERT( sizeof(int)==4, "Error!");
    return UINT_TO_JSVAL(number);
#endif
}

jsval long_long_to_jsval( JSContext *cx, long long number )
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

bool jsval_to_charptr( JSContext *cx, JS::HandleValue vp, const char **ret )
{
    JSString *jsstr = JS::ToString( cx, vp );
    JSB_PRECONDITION2( jsstr, cx, false, "invalid string" );

    //XXX: what's this?
    // root it
//    vp = STRING_TO_JSVAL(jsstr);

    JSStringWrapper strWrapper(jsstr);
    
    // XXX: It is converted to String and then back to char* to autorelease the created object.
    __String *tmp = __String::create(strWrapper.get());

    JSB_PRECONDITION2( tmp, cx, false, "Error creating string from UTF8");

    *ret = tmp->getCString();

    return true;
}

jsval charptr_to_jsval( JSContext *cx, const char *str)
{
    return c_string_to_jsval(cx, str);
}

bool JSB_jsval_typedarray_to_dataptr( JSContext *cx, JS::HandleValue vp, GLsizei *count, void **data, js::Scalar::Type t)
{
    JS::RootedObject jsobj(cx);
    bool ok = JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION2( ok && jsobj, cx, false, "Error converting value to object");
    
    // WebGL supports TypedArray and sequences for some of its APIs. So when converting a TypedArray, we should
    // also check for a possible non-Typed Array JS object, like a JS Array.
    
    if( JS_IsTypedArrayObject( jsobj ) ) {
        
        *count = JS_GetTypedArrayLength(jsobj);
        js::Scalar::Type type = JS_GetArrayBufferViewType(jsobj);
        JSB_PRECONDITION2(t==type, cx, false, "TypedArray type different than expected type");
        
        switch (t) {
            case js::Scalar::Int8:
            case js::Scalar::Uint8:
                *data = JS_GetUint8ArrayData(jsobj);
                break;
                
            case js::Scalar::Int16:
            case js::Scalar::Uint16:
                *data = JS_GetUint16ArrayData(jsobj);
                break;
                
            case js::Scalar::Int32:
            case js::Scalar::Uint32:
                *data = JS_GetUint32ArrayData(jsobj);
                break;
                
            case js::Scalar::Float32:
                *data = JS_GetFloat32ArrayData(jsobj);
                break;
                
            default:
                JSB_PRECONDITION2(false, cx, false, "Unsupported typedarray type");
                break;
        }
    } else if( JS_IsArrayObject(cx, jsobj)) {
        // Slow... avoid it. Use TypedArray instead, but the spec says that it can receive
        // Sequence<> as well.
        uint32_t length;
        JS_GetArrayLength(cx, jsobj, &length);
        
        for( uint32_t i=0; i<length;i++ ) {
            
            JS::RootedValue valarg(cx);
            JS_GetElement(cx, jsobj, i, &valarg);
            
            switch(t) {
                case js::Scalar::Int32:
                case js::Scalar::Uint32:
                {
                    uint32_t e = valarg.toInt32();
                    ((uint32_t*)data)[i] = e;
                    break;
                }
                case js::Scalar::Float32:
                {
                    double e = valarg.toNumber();
                    ((GLfloat*)data)[i] = (GLfloat)e;
                    break;
                }
                default:
                    JSB_PRECONDITION2(false, cx, false, "Unsupported typedarray type");
                    break;
            }
        }
        
    } else
        JSB_PRECONDITION2(false, cx, false, "Object shall be a TypedArray or Sequence");
    
    return true;
}

bool JSB_get_arraybufferview_dataptr( JSContext *cx, JS::HandleValue vp, GLsizei *count, GLvoid **data )
{
    JS::RootedObject jsobj(cx);
    bool ok = JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION2( ok && jsobj, cx, false, "Error converting value to object");
    JSB_PRECONDITION2( JS_IsArrayBufferViewObject(jsobj), cx, false, "Not an ArrayBufferView object");
    
    *data = JS_GetArrayBufferViewData(jsobj);
    *count = JS_GetArrayBufferViewByteLength(jsobj);
    
    return true;
}


#pragma mark - Conversion Routines
bool jsval_to_ushort( JSContext *cx, JS::HandleValue vp, unsigned short *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    *outval = (unsigned short)dp;

    return ok;
}

bool jsval_to_int32( JSContext *cx, JS::HandleValue vp, int32_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (int32_t)dp;
    
    return ok;
}

bool jsval_to_uint32( JSContext *cx, JS::HandleValue vp, uint32_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (uint32_t)dp;
    
    return ok;
}

bool jsval_to_uint16( JSContext *cx, JS::HandleValue vp, uint16_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *outval = (uint16_t)dp;
    
    return ok;
}

// XXX: sizeof(long) == 8 in 64 bits on OS X... apparently on Windows it is 32 bits (???)
bool jsval_to_long( JSContext *cx, JS::HandleValue vp, long *r )
{
#ifdef __LP64__
    // compatibility check
    assert( sizeof(long)==8);
    JSString *jsstr = JS::ToString(cx, vp);
    JSB_PRECONDITION2(jsstr, cx, false, "Error converting value to string");
    
    char *str = JS_EncodeString(cx, jsstr);
    JSB_PRECONDITION2(str, cx, false, "Error encoding string");
    
    char *endptr;
    long ret = strtol(str, &endptr, 10);
    
    *r = ret;
    return true;
    
#else
    // compatibility check
    assert( sizeof(int)==4);
    long ret = vp.toInt32();
#endif
    
    *r = ret;
    return true;
}


bool jsval_to_ulong( JSContext *cx, JS::HandleValue vp, unsigned long *out)
{
    if (out == nullptr)
        return false;
    
    long rval = 0;
    bool ret = false;
    ret = jsval_to_long(cx, vp, &rval);
    if (ret)
    {
        *out = (unsigned long)rval;
    }
    return ret;
}

bool jsval_to_long_long(JSContext *cx, JS::HandleValue vp, long long* r)
{
    JSString *jsstr = JS::ToString(cx, vp);
    JSB_PRECONDITION2(jsstr, cx, false, "Error converting value to string");
    
    char *str = JS_EncodeString(cx, jsstr);
    JSB_PRECONDITION2(str, cx, false, "Error encoding string");
    
    char *endptr;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    __int64 ret = _strtoi64(str, &endptr, 10);
#else
    long long ret = strtoll(str, &endptr, 10);
#endif
    
    *r = ret;
    return true;
}

bool jsval_to_std_string(JSContext *cx, JS::HandleValue v, std::string* ret) {
    if(v.isString() || v.isNumber())
    {
        JSString *tmp = JS::ToString(cx, v);
        JSB_PRECONDITION3(tmp, cx, false, "Error processing arguments");

        JSStringWrapper str(tmp);
        *ret = str.get();
        return true;
    }

    return false;
}

bool jsval_to_ccpoint(JSContext *cx, JS::HandleValue v, Point* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    double x, y;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return true;
}

bool jsval_to_ccacceleration(JSContext* cx, JS::HandleValue v, Acceleration* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    JS::RootedValue jstimestamp(cx);
    
    double x, y, timestamp, z;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "timestamp", &jstimestamp) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jsz, &z) &&
    JS::ToNumber(cx, jstimestamp, &timestamp);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = x;
    ret->y = y;
    ret->z = z;
    ret->timestamp = timestamp;
    return true;
}

bool jsval_to_quaternion( JSContext *cx, JS::HandleValue v, cocos2d::Quaternion* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue x(cx);
    JS::RootedValue y(cx);
    JS::RootedValue z(cx);
    JS::RootedValue w(cx);
    
    double xx, yy, zz, ww;
    bool ok = v.isObject() &&
        JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "x", &x) &&
        JS_GetProperty(cx, tmp, "y", &y) &&
        JS_GetProperty(cx, tmp, "z", &z) &&
        JS_GetProperty(cx, tmp, "w", &w) &&
        JS::ToNumber(cx, x, &xx) &&
        JS::ToNumber(cx, y, &yy) &&
        JS::ToNumber(cx, z, &zz) &&
        JS::ToNumber(cx, w, &ww) &&
        !isnan(xx) && !isnan(yy) && !isnan(zz) && !isnan(ww);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    ret->set(xx, yy, zz, ww);

    return true;
}

bool jsval_to_obb(JSContext *cx, JS::HandleValue v, cocos2d::OBB* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jscenter(cx);
    JS::RootedValue jsxAxis(cx);
    JS::RootedValue jsyAxis(cx);
    JS::RootedValue jszAxis(cx);
    JS::RootedValue jsextents(cx);
    JS::RootedValue jsextentx(cx);
    JS::RootedValue jsextenty(cx);
    JS::RootedValue jsextentz(cx);
    
    cocos2d::Vec3 center, xAxis, yAxis, zAxis, extents, extentx, extenty, extentz;
    bool ok = v.isObject() &&
        JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "center", &jscenter) &&
        JS_GetProperty(cx, tmp, "xAxis", &jsxAxis) &&
        JS_GetProperty(cx, tmp, "yAxis", &jsyAxis) &&
        JS_GetProperty(cx, tmp, "zAxis", &jszAxis) &&
        JS_GetProperty(cx, tmp, "extents", &jsextents) &&
        JS_GetProperty(cx, tmp, "extentX", &jsextentx) &&
        JS_GetProperty(cx, tmp, "extentY", &jsextenty) &&
        JS_GetProperty(cx, tmp, "extentZ", &jsextentz) &&
        jsval_to_vector3(cx, jscenter, &center) &&
        jsval_to_vector3(cx, jsxAxis, &xAxis) &&
        jsval_to_vector3(cx, jsyAxis, &yAxis) &&
        jsval_to_vector3(cx, jszAxis, &zAxis) &&
        jsval_to_vector3(cx, jsextents, &extents) &&
        jsval_to_vector3(cx, jsextentx, &extentx) &&
        jsval_to_vector3(cx, jsextenty, &extenty) &&
        jsval_to_vector3(cx, jsextentz, &extentz);

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    ret->_center.set(center);
    ret->_xAxis.set(xAxis);
    ret->_yAxis.set(yAxis);
    ret->_zAxis.set(zAxis);
    ret->_extents.set(extents);
    ret->_extentX.set(extentx);
    ret->_extentY.set(extenty);
    ret->_extentZ.set(extentz);
    return true;
}

bool jsval_to_ray(JSContext *cx, JS::HandleValue v, cocos2d::Ray* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsorigin(cx);
    JS::RootedValue jsdirection(cx);

    cocos2d::Vec3 origin, direction;
    bool ok = v.isObject() &&
        JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "origin", &jsorigin) &&
        JS_GetProperty(cx, tmp, "direction", &jsdirection) &&
        jsval_to_vector3(cx, jsorigin, &origin) && 
        jsval_to_vector3(cx, jsdirection, &direction);

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->set(origin, direction);
    return true;
}

bool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, __Array** ret)
{
    bool ok = true;
    __Array* pArray = __Array::create();
    for( int i=0; i < argc; i++ )
    {
        double num = 0.0;
        // optimization: JS::ToNumber is expensive. And can convert an string like "12" to a number
        JS::RootedValue jsv(cx, *vp);
        if (jsv.isNumber()) {
            ok &= JS::ToNumber(cx, jsv, &num );
            if (!ok) {
                break;
            }
            pArray->addObject(__Integer::create((int)num));
        }
        else if (jsv.isString())
        {
            JSStringWrapper str(jsv, cx);
            pArray->addObject(__String::create(str.get()));
        }
        else
        {
            js_proxy_t* p;
            JS::RootedObject obj(cx, jsv.toObjectOrNull());
            p = jsb_get_js_proxy(obj);
            if (p) {
                pArray->addObject((Ref*)p->ptr);
            }
        }
        // next
        vp++;
    }
    *ret = pArray;
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    return ok;
}

bool jsvals_variadic_to_ccvaluevector( JSContext *cx, jsval *vp, int argc, cocos2d::ValueVector* ret)
{
    JS::RootedValue value(cx);
    for (int i = 0; i < argc; i++)
    {
        value = *vp;
        if (value.isObject())
        {
            JS::RootedObject jsobj(cx, value.toObjectOrNull());
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            
            if (!JS_IsArrayObject(cx, jsobj))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    ret->push_back(Value(dictVal));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    ret->push_back(Value(arrVal));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            ret->push_back(Value(valueWapper.get()));
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok)
            {
                ret->push_back(Value(number));
            }
        }
        else if (value.isBoolean())
        {
            bool boolVal = JS::ToBoolean(value);
            ret->push_back(Value(boolVal));
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
        // next
        vp++;
    }
    
    return true;
}

bool jsval_to_ccrect(JSContext *cx, JS::HandleValue v, Rect* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jswidth(cx);
    JS::RootedValue jsheight(cx);
    
    double x, y, width, height;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "width", &jswidth) &&
    JS_GetProperty(cx, tmp, "height", &jsheight) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jswidth, &width) &&
    JS::ToNumber(cx, jsheight, &height);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->origin.x = x;
    ret->origin.y = y;
    ret->size.width = width;
    ret->size.height = height;
    return true;
}

bool jsval_to_ccsize(JSContext *cx, JS::HandleValue v, Size* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsw(cx);
    JS::RootedValue jsh(cx);
    double w, h;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "width", &jsw) &&
    JS_GetProperty(cx, tmp, "height", &jsh) &&
    JS::ToNumber(cx, jsw, &w) &&
    JS::ToNumber(cx, jsh, &h);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ret->width = w;
    ret->height = h;
    return true;
}

bool jsval_to_cccolor4b(JSContext *cx, JS::HandleValue v, Color4B* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    
    double r, g, b, a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx,  v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->r = (GLubyte)r;
    ret->g = (GLubyte)g;
    ret->b = (GLubyte)b;
    ret->a = (GLubyte)a;
    return true;
}

bool jsval_to_cccolor4f(JSContext *cx, JS::HandleValue v, Color4F* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsa(cx);
    double r, g, b, a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsa, &a);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    ret->r = (float)r / 255;
    ret->g = (float)g / 255;
    ret->b = (float)b / 255;
    ret->a = (float)a / 255;
    return true;
}

bool jsval_to_cccolor3b(JSContext *cx, JS::HandleValue v, Color3B* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsg(cx);
    JS::RootedValue jsb(cx);
    double r, g, b;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "r", &jsr) &&
    JS_GetProperty(cx, tmp, "g", &jsg) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS::ToNumber(cx, jsr, &r) &&
    JS::ToNumber(cx, jsg, &g) &&
    JS::ToNumber(cx, jsb, &b);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->r = (GLubyte)r;
    ret->g = (GLubyte)g;
    ret->b = (GLubyte)b;
    return true;
}

bool jsval_cccolor_to_opacity(JSContext *cx, JS::HandleValue v, int32_t* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jsa(cx);
    
    double a;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_LookupProperty(cx, tmp, "a", &jsa) &&
    !jsa.isUndefined() &&
    JS::ToNumber(cx, jsa, &a);
    
    if (ok) {
        *ret = (int32_t)a;
        return true;
    }
    else return false;
}

bool jsval_to_ccarray_of_CCPoint(JSContext* cx, JS::HandleValue v, Point **points, int *numPoints) {
    // Parsing sequence
    JS::RootedObject jsobj(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");
    
    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);
    
    Point *array = new (std::nothrow) Point[len];

    for( uint32_t i=0; i< len;i++ ) {
        JS::RootedValue valarg(cx);
        JS_GetElement(cx, jsobj, i, &valarg);
        
        ok = jsval_to_ccpoint(cx, valarg, &array[i]);
        JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    }
    
    *numPoints = len;
    *points = array;
    
    return true;
}


bool jsval_to_ccarray(JSContext* cx, JS::HandleValue v, __Array** ret)
{
    JS::RootedObject jsobj(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    __Array* arr = __Array::createWithCapacity(len);
    for (uint32_t i=0; i < len; i++) {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value)) {
            if (value.isObject())
            {
                js_proxy_t *proxy;
                JS::RootedObject tmp(cx, value.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmp);
                cocos2d::Ref* cobj = (cocos2d::Ref *)(proxy ? proxy->ptr : NULL);
                // Don't test it.
                //TEST_NATIVE_OBJECT(cx, cobj)
                if (cobj) {
                    // It's a native js object.
                    arr->addObject(cobj);
                }
                else if (!JS_IsArrayObject(cx, tmp)){
                    // It's a normal js object.
                    __Dictionary* dictVal = NULL;
                    ok = jsval_to_ccdictionary(cx, value, &dictVal);
                    if (ok) {
                        arr->addObject(dictVal);
                    }
                }
                else {
                    // It's a js array object.
                    __Array* arrVal = NULL;
                    ok = jsval_to_ccarray(cx, value, &arrVal);
                    if (ok) {
                        arr->addObject(arrVal);
                    }
                }
            }
            else if (value.isString()) {
                JSStringWrapper valueWapper(value.toString(), cx);
                arr->addObject(__String::create(valueWapper.get()));
            }
            else if (value.isNumber()) {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok) {
                    arr->addObject(__Double::create(number));
                }
            }
            else if (value.isBoolean()) {
                bool boolVal = JS::ToBoolean(value);
                arr->addObject(__Bool::create(boolVal));
            }
            else {
                CCASSERT(false, "not supported type");
            }
        }
    }
    *ret = arr;
    return true;
}

bool jsval_to_ccvalue(JSContext* cx, JS::HandleValue v, cocos2d::Value* ret)
{
    if (v.isObject())
    {
        JS::RootedObject jsobj(cx, v.toObjectOrNull());
        CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
        if (!JS_IsArrayObject(cx, jsobj))
        {
            // It's a normal js object.
            ValueMap dictVal;
            bool ok = jsval_to_ccvaluemap(cx, v, &dictVal);
            if (ok)
            {
                *ret = Value(dictVal);
            }
        }
        else {
            // It's a js array object.
            ValueVector arrVal;
            bool ok = jsval_to_ccvaluevector(cx, v, &arrVal);
            if (ok)
            {
                *ret = Value(arrVal);
            }
        }
    }
    else if (v.isString())
    {
        JSStringWrapper valueWapper(v.toString(), cx);
        *ret = Value(valueWapper.get());
    }
    else if (v.isNumber())
    {
        double number = 0.0;
        bool ok = JS::ToNumber(cx, v, &number);
        if (ok) {
            *ret = Value(number);
        }
    }
    else if (v.isBoolean())
    {
        bool boolVal = JS::ToBoolean(v);
        *ret = Value(boolVal);
    }
    else {
        CCASSERT(false, "not supported type");
    }

    return true;
}

bool jsval_to_ccvaluemap(JSContext* cx, JS::HandleValue v, cocos2d::ValueMap* ret)
{
    if (v.isNullOrUndefined())
    {
        return true;
    }
    
    JS::RootedObject tmp(cx, v.toObjectOrNull());
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return false;
    }
    
    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
    
    ValueMap& dict = *ret;
    
    while (true)
    {
        JS::RootedId idp(cx);
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
            return false; // error
        }
        
        if (key.isNullOrUndefined()) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            JS::RootedObject jsobj(cx, value.toObjectOrNull());
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            if (!JS_IsArrayObject(cx, jsobj))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    dict.insert(ValueMap::value_type(keyWrapper.get(), Value(dictVal)));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    dict.insert(ValueMap::value_type(keyWrapper.get(), Value(arrVal)));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict.insert(ValueMap::value_type(keyWrapper.get(), Value(valueWapper.get())));
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict.insert(ValueMap::value_type(keyWrapper.get(), Value(number)));
            }
        }
        else if (value.isBoolean())
        {
            bool boolVal = JS::ToBoolean(value);
            dict.insert(ValueMap::value_type(keyWrapper.get(), Value(boolVal)));
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
}

bool jsval_to_ccvaluemapintkey(JSContext* cx, JS::HandleValue v, cocos2d::ValueMapIntKey* ret)
{
    if (v.isNullOrUndefined())
    {
        return true;
    }
    
    JS::RootedObject tmp(cx, v.toObjectOrNull());
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return false;
    }
    
    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
    
    ValueMapIntKey& dict = *ret;
    
    while (true)
    {
        JS::RootedId idp(cx);
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
            return false; // error
        }
        
        if (key.isNullOrUndefined()) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        int keyVal = key.toInt32();
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            JS::RootedObject jsobj(cx, value.toObjectOrNull());
            CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
            if (!JS_IsArrayObject(cx, jsobj))
            {
                // It's a normal js object.
                ValueMap dictVal;
                bool ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                if (ok)
                {
                    dict.insert(ValueMapIntKey::value_type(keyVal, Value(dictVal)));
                }
            }
            else {
                // It's a js array object.
                ValueVector arrVal;
                bool ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                if (ok)
                {
                    dict.insert(ValueMapIntKey::value_type(keyVal, Value(arrVal)));
                }
            }
        }
        else if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict.insert(ValueMapIntKey::value_type(keyVal, Value(valueWapper.get())));
        }
        else if (value.isNumber())
        {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict.insert(ValueMapIntKey::value_type(keyVal, Value(number)));
            }
        }
        else if (value.isBoolean())
        {
            bool boolVal = JS::ToBoolean(value);
            dict.insert(ValueMapIntKey::value_type(keyVal, Value(boolVal)));
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    return true;
}

bool jsval_to_ccvaluevector(JSContext* cx, JS::HandleValue v, cocos2d::ValueVector* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);

    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            if (value.isObject())
            {
                JS::RootedObject jsobj(cx, value.toObjectOrNull());
                CCASSERT(jsb_get_js_proxy(jsobj) == nullptr, "Native object should be added!");
                
                if (!JS_IsArrayObject(cx, jsobj))
                {
                    // It's a normal js object.
                    ValueMap dictVal;
                    ok = jsval_to_ccvaluemap(cx, value, &dictVal);
                    if (ok)
                    {
                        ret->push_back(Value(dictVal));
                    }
                }
                else {
                    // It's a js array object.
                    ValueVector arrVal;
                    ok = jsval_to_ccvaluevector(cx, value, &arrVal);
                    if (ok)
                    {
                        ret->push_back(Value(arrVal));
                    }
                }
            }
            else if (value.isString())
            {
                JSStringWrapper valueWapper(value.toString(), cx);
                ret->push_back(Value(valueWapper.get()));
            }
            else if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->push_back(Value(number));
                }
            }
            else if (value.isBoolean())
            {
                bool boolVal = JS::ToBoolean(value);
                ret->push_back(Value(boolVal));
            }
            else
            {
                CCASSERT(false, "not supported type");
            }
        }
    }

    return true;
}

bool jsval_to_ssize( JSContext *cx, JS::HandleValue vp, ssize_t* size)
{
    bool ret = false;
    int32_t sizeInt32 = 0;
    ret = jsval_to_int32(cx, vp, &sizeInt32);
    *size = sizeInt32;
    return ret;
}

bool jsval_to_std_vector_string( JSContext *cx, JS::HandleValue vp, std::vector<std::string>* ret)
{
    JS::RootedObject jsobj(cx);
    bool ok = vp.isObject() && JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    ret->reserve(len);
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isString())
            {
                JSStringWrapper valueWapper(value.toString(), cx);
                ret->push_back(valueWapper.get());
            }
            else
            {
                JS_ReportError(cx, "not supported type in array");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_std_vector_int( JSContext *cx, JS::HandleValue vp, std::vector<int>* ret)
{
    JS::RootedObject jsobj(cx);
    bool ok = vp.isObject() && JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    ret->reserve(len);
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->push_back(static_cast<int>(number));
                }
            }
            else
            {
                JS_ReportError(cx, "not supported type in array");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_std_vector_float( JSContext *cx, JS::HandleValue vp, std::vector<float>* ret)
{
    JS::RootedObject jsobj(cx);
    bool ok = vp.isObject() && JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");

    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    ret->reserve(len);
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->push_back(number);
                }
            }
            else
            {
                JS_ReportError(cx, "not supported type in array");
                return false;
            }
        }
    }

    return true;
}

bool jsval_to_matrix(JSContext *cx, JS::HandleValue vp, cocos2d::Mat4* ret)
{
    JS::RootedObject jsobj(cx);
    bool ok = vp.isObject() && JS_ValueToObject( cx, vp, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an matrix");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    
    if (len != 16)
    {
        JS_ReportError(cx, "array length error: %d, was expecting 16", len);
    }
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            if (value.isNumber())
            {
                double number = 0.0;
                ok = JS::ToNumber(cx, value, &number);
                if (ok)
                {
                    ret->m[i] = static_cast<float>(number);
                }
            }
            else
            {
                JS_ReportError(cx, "not supported type in matrix");
                return false;
            }
        }
    }
    
    return true;
}

bool jsval_to_vector2(JSContext *cx, JS::HandleValue vp, cocos2d::Vec2* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    double x, y;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    !isnan(x) && !isnan(y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    return true;
}

bool jsval_to_vector3(JSContext *cx, JS::HandleValue vp, cocos2d::Vec3* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    double x, y, z;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jsz, &z) &&
    !isnan(x) && !isnan(y) && !isnan(z);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    ret->z = (float)z;
    return true;
}

bool jsval_to_vector4(JSContext *cx, JS::HandleValue vp, cocos2d::Vec4* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    JS::RootedValue jsz(cx);
    JS::RootedValue jsw(cx);
    double x, y, z, w;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "w", &jsw) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    JS::ToNumber(cx, jsz, &z) &&
    JS::ToNumber(cx, jsw, &w) &&
    !isnan(x) && !isnan(y) && !isnan(z) && !isnan(w);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->x = (float)x;
    ret->y = (float)y;
    ret->z = (float)z;
    ret->w = (float)w;
    return true;
}

bool jsval_to_blendfunc(JSContext *cx, JS::HandleValue vp, cocos2d::BlendFunc* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jssrc(cx);
    JS::RootedValue jsdst(cx);
    double src, dst;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "src", &jssrc) &&
    JS_GetProperty(cx, tmp, "dst", &jsdst) &&
    JS::ToNumber(cx, jssrc, &src) &&
    JS::ToNumber(cx, jsdst, &dst);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->src = (unsigned int)src;
    ret->dst = (unsigned int)dst;
    return true;
}

bool jsval_to_vector_vec2(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::Vec2>* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);
    ret->reserve(len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            cocos2d::Vec2 vec2;
            ok &= jsval_to_vector2(cx, value, &vec2);
            ret->push_back(vec2);
        }
    }
    return ok;
}

bool jsval_to_cctex2f(JSContext* cx, JS::HandleValue vp, cocos2d::Tex2F* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsx(cx);
    JS::RootedValue jsy(cx);
    double x, y;
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, vp, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS::ToNumber(cx, jsx, &x) &&
    JS::ToNumber(cx, jsy, &y) &&
    !isnan(x) && !isnan(y);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->u = (GLfloat)x;
    ret->v = (GLfloat)y;
    return true;
}

bool jsval_to_v3fc4bt2f(JSContext* cx, JS::HandleValue v, cocos2d::V3F_C4B_T2F* ret)
{
    JS::RootedObject object(cx, v.toObjectOrNull());
    
    cocos2d::Vec3 v3;
    cocos2d::Color4B color;
    cocos2d::Tex2F t2;
    
    JS::RootedValue jsv3(cx);
    JS::RootedValue jscolor(cx);
    JS::RootedValue jst2(cx);
    
    bool ok = JS_GetProperty(cx, object, "v3f", &jsv3) &&
    JS_GetProperty(cx, object, "c4b", &jscolor) &&
    JS_GetProperty(cx, object, "t2f", &jst2) &&
    jsval_to_vector3(cx, jsv3, &v3) &&
    jsval_to_cccolor4b(cx, jscolor, &color) &&
    jsval_to_cctex2f(cx, jst2, &t2);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->vertices = v3;
    ret->colors = color;
    ret->texCoords = t2;
    return true;
}

bool jsval_to_v3fc4bt2f_quad(JSContext* cx, JS::HandleValue v, cocos2d::V3F_C4B_T2F_Quad* ret)
{
    JS::RootedObject object(cx, v.toObjectOrNull());
    
    cocos2d::V3F_C4B_T2F tl;
    cocos2d::V3F_C4B_T2F bl;
    cocos2d::V3F_C4B_T2F tr;
    cocos2d::V3F_C4B_T2F br;
    
    JS::RootedValue jstl(cx);
    JS::RootedValue jsbl(cx);
    JS::RootedValue jstr(cx);
    JS::RootedValue jsbr(cx);
    
    bool ok = JS_GetProperty(cx, object, "tl", &jstl) &&
              JS_GetProperty(cx, object, "bl", &jsbl) &&
              JS_GetProperty(cx, object, "tr", &jstr) &&
              JS_GetProperty(cx, object, "br", &jsbr) &&
              jsval_to_v3fc4bt2f(cx, jstl, &tl) &&
              jsval_to_v3fc4bt2f(cx, jsbl, &bl) &&
              jsval_to_v3fc4bt2f(cx, jstr, &tr) &&
              jsval_to_v3fc4bt2f(cx, jsbr, &br);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->tl = tl;
    ret->bl = bl;
    ret->tr = tr;
    ret->br = br;
    return true;
}

bool jsval_to_vector_v3fc4bt2f(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::V3F_C4B_T2F>* ret)
{
    JS::RootedObject jsArr(cx);
    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsArr );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsArr && JS_IsArrayObject( cx, jsArr),  cx, false, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsArr, &len);
    ret->reserve(len);
    
    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsArr, i, &value))
        {
            cocos2d::V3F_C4B_T2F vert;
            ok &= jsval_to_v3fc4bt2f(cx, value, &vert);
            ret->push_back(vert);
        }
    }
    return ok;
}

bool jsval_to_std_map_string_string(JSContext* cx, JS::HandleValue v, std::map<std::string, std::string>* ret)
{
    if (v.isNullOrUndefined())
    {
        return true;
    }
    
    JS::RootedObject tmp(cx, v.toObjectOrNull());
    if (!tmp) 
    {
        CCLOG("%s", "jsval_to_std_map_string_string: the jsval is not an object.");
        return false;
    }
    
    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
    
    std::map<std::string, std::string>& dict = *ret;
    
    while (true)
    {
        JS::RootedId idp(cx);
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) 
        {
            return false; // error
        }
        
        if (key.isNullOrUndefined()) 
        {
            break; // end of iteration
        }
        
        if (!key.isString()) 
        {
            continue; // only take account of string key
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict[keyWrapper.get()] = valueWapper.get();
        }
        else 
        {
            CCASSERT(false, "jsval_to_std_map_string_string: not supported map type");
        }
    }
    
    return true;
}

// native --> jsval

jsval ccarray_to_jsval(JSContext* cx, __Array *arr)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
    
    Ref* obj;
    int i = 0;
    CCARRAY_FOREACH(arr, obj)
    {
        JS::RootedValue arrElement(cx);
        
        //First, check whether object is associated with js object.
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Ref>(obj);
        auto jsobj = jsb_ref_get_or_create_jsobject(cx, obj, typeClass, "cocos2d::Ref");
        if (jsobj) {
            arrElement = OBJECT_TO_JSVAL(jsobj);
        }
        else {
            __String* strVal = NULL;
            __Dictionary* dictVal = NULL;
            __Array* arrVal = NULL;
            __Double* doubleVal = NULL;
            __Bool* boolVal = NULL;
            __Float* floatVal = NULL;
            __Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::__String *>(obj))) {
                arrElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<cocos2d::__Dictionary*>(obj))) {
                arrElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<cocos2d::__Array*>(obj))) {
                arrElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
                arrElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
                arrElement = INT_TO_JSVAL(intVal->getValue());
            }  else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
                arrElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? true : false);
            } else {
                CCASSERT(false, "the type isn't suppored.");
            }
        }
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ccdictionary_to_jsval(JSContext* cx, __Dictionary* dict)
{

    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, proto, parent));
    DictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        JS::RootedValue dictElement(cx);
        Ref* obj = pElement->getObject();
        //First, check whether object is associated with js object.
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Ref>(obj);
        auto jsobj = jsb_ref_get_or_create_jsobject(cx, obj, typeClass, "cocos2d::Ref");
        if (jsobj) {
            dictElement = OBJECT_TO_JSVAL(jsobj);
        }
        else {
            __String* strVal = NULL;
            __Dictionary* dictVal = NULL;
            __Array* arrVal = NULL;
            __Double* doubleVal = NULL;
            __Bool* boolVal = NULL;
            __Float* floatVal = NULL;
            __Integer* intVal = NULL;
            
            if ((strVal = dynamic_cast<cocos2d::__String *>(obj))) {
                dictElement = c_string_to_jsval(cx, strVal->getCString());
            } else if ((dictVal = dynamic_cast<__Dictionary*>(obj))) {
                dictElement = ccdictionary_to_jsval(cx, dictVal);
            } else if ((arrVal = dynamic_cast<__Array*>(obj))) {
                dictElement = ccarray_to_jsval(cx, arrVal);
            } else if ((doubleVal = dynamic_cast<__Double*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(doubleVal->getValue());
            } else if ((floatVal = dynamic_cast<__Float*>(obj))) {
                dictElement = DOUBLE_TO_JSVAL(floatVal->getValue());
            } else if ((intVal = dynamic_cast<__Integer*>(obj))) {
                dictElement = INT_TO_JSVAL(intVal->getValue());
            } else if ((boolVal = dynamic_cast<__Bool*>(obj))) {
                dictElement = BOOLEAN_TO_JSVAL(boolVal->getValue() ? true : false);
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

bool jsval_to_ccdictionary(JSContext* cx, JS::HandleValue v, __Dictionary** ret)
{
    if (v.isNullOrUndefined())
    {
        *ret = NULL;
        return true;
    }
    
    JS::RootedObject tmp(cx, v.toObjectOrNull());
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccdictionary: the jsval is not an object.");
        return false;
    }
    
    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
    __Dictionary* dict = NULL;
    
    while (true)
    {
        JS::RootedId idp(cx);
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
            return false; // error
        }
        
        if (key.isNullOrUndefined()) {
            break; // end of iteration
        }
        
        if (!key.isString()) {
            continue; // ignore integer properties
        }
        
        JSStringWrapper keyWrapper(key.toString(), cx);
        if (!dict) {
            dict = __Dictionary::create();
        }
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            js_proxy_t *proxy;
            tmp = value.toObjectOrNull();
            proxy = jsb_get_js_proxy(tmp);
            cocos2d::Ref* cobj = (cocos2d::Ref *)(proxy ? proxy->ptr : NULL);
            // Don't test it.
            //TEST_NATIVE_OBJECT(cx, cobj)
            if (cobj) {
                // It's a native <-> js glue object.
                dict->setObject(cobj, keyWrapper.get());
            }
            else if (!JS_IsArrayObject(cx, tmp)){
                // It's a normal js object.
                __Dictionary* dictVal = NULL;
                bool ok = jsval_to_ccdictionary(cx, value, &dictVal);
                if (ok) {
                    dict->setObject(dictVal, keyWrapper.get());
                }
            }
            else {
                // It's a js array object.
                __Array* arrVal = NULL;
                bool ok = jsval_to_ccarray(cx, value, &arrVal);
                if (ok) {
                    dict->setObject(arrVal, keyWrapper.get());
                }
            }
        }
        else if (value.isString()) {
            JSStringWrapper valueWapper(value.toString(), cx);
            dict->setObject(__String::create(valueWapper.get()), keyWrapper.get());
        }
        else if (value.isNumber()) {
            double number = 0.0;
            bool ok = JS::ToNumber(cx, value, &number);
            if (ok) {
                dict->setObject(__Double::create(number), keyWrapper.get());
            }
        }
        else if (value.isBoolean()) {
            bool boolVal = JS::ToBoolean(value);
            dict->setObject(__Bool::create(boolVal), keyWrapper.get());
        }
        else {
            CCASSERT(false, "not supported type");
        }
    }
    
    *ret = dict;
    return true;
}

bool jsval_to_ccaffinetransform(JSContext* cx, JS::HandleValue v, AffineTransform* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsa(cx);
    JS::RootedValue jsb(cx);
    JS::RootedValue jsc(cx);
    JS::RootedValue jsd(cx);
    JS::RootedValue jstx(cx);
    JS::RootedValue jsty(cx);
    double a, b, c, d, tx, ty;
    bool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "a", &jsa) &&
    JS_GetProperty(cx, tmp, "b", &jsb) &&
    JS_GetProperty(cx, tmp, "c", &jsc) &&
    JS_GetProperty(cx, tmp, "d", &jsd) &&
    JS_GetProperty(cx, tmp, "tx", &jstx) &&
    JS_GetProperty(cx, tmp, "ty", &jsty) &&
    JS::ToNumber(cx, jsa, &a) &&
    JS::ToNumber(cx, jsb, &b) &&
    JS::ToNumber(cx, jsc, &c) &&
    JS::ToNumber(cx, jsd, &d) &&
    JS::ToNumber(cx, jstx, &tx) &&
    JS::ToNumber(cx, jsty, &ty);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    *ret = AffineTransformMake(a, b, c, d, tx, ty);
    return true;
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

jsval ushort_to_jsval( JSContext *cx, unsigned short number )
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
    if (length == -1)
    {
        length = strlen(v);
    }
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    if (0 == length)
    {
        auto emptyStr = JS_NewStringCopyZ(cx, "");
        return STRING_TO_JSVAL(emptyStr);
    }
    
    jsval ret = JSVAL_NULL;

    int utf16_size = 0;
    const jschar* strUTF16 = (jschar*)cc_utf8_to_utf16(v, (int)length, &utf16_size);
    
    if (strUTF16 && utf16_size > 0) {
        JSString* str = JS_NewUCStringCopyN(cx, strUTF16, (size_t)utf16_size);
        if (str) {
            ret = STRING_TO_JSVAL(str);
        }
        delete[] strUTF16;
    }

    return ret;
}

jsval ccpoint_to_jsval(JSContext* cx, const Point& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccacceleration_to_jsval(JSContext* cx, const Acceleration& v)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timestamp", v.timestamp, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccrect_to_jsval(JSContext* cx, const Rect& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.origin.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.origin.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "width", v.size.width, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", v.size.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccsize_to_jsval(JSContext* cx, const Size& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "width", v.width, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "height", v.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4b_to_jsval(JSContext* cx, const Color4B& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "r", (int32_t)v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", (int32_t)v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", (int32_t)v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", (int32_t)v.a, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4f_to_jsval(JSContext* cx, const Color4F& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "r", (int32_t)(v.r * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", (int32_t)(v.g * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", (int32_t)(v.b * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "a", (int32_t)(v.a * 255), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor3b_to_jsval(JSContext* cx, const Color3B& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "r", (int32_t)v.r, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "g", (int32_t)v.g, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", (int32_t)v.b, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccaffinetransform_to_jsval(JSContext* cx, const AffineTransform& t)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "a", t.a, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "b", t.b, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "c", t.c, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "d", t.d, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "tx", t.tx, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "ty", t.ty, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval quaternion_to_jsval(JSContext* cx, const cocos2d::Quaternion& q)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if(!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", q.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "y", q.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "z", q.z, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "w", q.w, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if(ok)
        return OBJECT_TO_JSVAL(tmp);

    return JSVAL_NULL;
}

jsval uniform_to_jsval(JSContext* cx, const cocos2d::Uniform* uniform)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if(!tmp) return JSVAL_NULL;
    JS::RootedValue jsname(cx, std_string_to_jsval(cx, uniform->name));
    bool ok = JS_DefineProperty(cx, tmp, "location", uniform->location, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "size", uniform->size, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "type", uniform->type, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "name", jsname, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if(ok)
        return OBJECT_TO_JSVAL(tmp);
    
    return JSVAL_NULL;
}


jsval meshVertexAttrib_to_jsval(JSContext* cx, const cocos2d::MeshVertexAttrib& q)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if(!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "size", q.size, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "type", q.type, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "vertexAttrib", q.vertexAttrib, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "attribSizeBytes", q.attribSizeBytes, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if(ok)
        return OBJECT_TO_JSVAL(tmp);

    return JSVAL_NULL;
}

jsval FontDefinition_to_jsval(JSContext* cx, const FontDefinition& t)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    JS::RootedValue prop(cx);
    
    bool ok = true;
    
    prop.set(std_string_to_jsval(cx, t._fontName));
    ok &= JS_DefineProperty(cx, tmp, "fontName", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "fontSize", t._fontSize, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "textAlign", (int32_t)t._alignment, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "verticalAlign", (int32_t)t._vertAlignment, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(cccolor3b_to_jsval(cx, t._fontFillColor));
    ok &= JS_DefineProperty(cx, tmp, "fillStyle", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "boundingWidth", t._dimensions.width, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "boundingHeight", t._dimensions.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Shadow
    prop.set(BOOLEAN_TO_JSVAL(t._shadow._shadowEnabled));
    ok &= JS_DefineProperty(cx, tmp, "shadowEnabled", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "shadowOffsetX", t._shadow._shadowOffset.width, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "shadowOffsetY", t._shadow._shadowOffset.height, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "shadowBlur", t._shadow._shadowBlur, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "shadowOpacity", t._shadow._shadowOpacity, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // Stroke
    prop.set(BOOLEAN_TO_JSVAL(t._stroke._strokeEnabled));
    ok &= JS_DefineProperty(cx, tmp, "strokeEnabled", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(cccolor3b_to_jsval(cx, t._stroke._strokeColor));
    ok &= JS_DefineProperty(cx, tmp, "strokeStyle", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    ok &= JS_DefineProperty(cx, tmp, "lineWidth", t._stroke._strokeSize, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

bool jsval_to_FontDefinition( JSContext *cx, JS::HandleValue vp, FontDefinition *out )
{
    JS::RootedObject jsobj(cx);
    
    if (!JS_ValueToObject( cx, vp, &jsobj ) )
        return false;
    
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
    JS::ToString(cx, jsr);
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
    bool hasProperty, hasSecondProp;
    JS_HasProperty(cx, jsobj, "fontSize", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fontSize", &jsr);
        double fontSize = 0.0;
        JS::ToNumber(cx, jsr, &fontSize);
        out->_fontSize  = fontSize;
    }
    else
    {
        out->_fontSize  = defaultFontSize;
    }
    
    // font alignment horizontal
    JS_HasProperty(cx, jsobj, "textAlign", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "textAlign", &jsr);
        double fontAlign = 0.0;
        JS::ToNumber(cx, jsr, &fontAlign);
        out->_alignment = (TextHAlignment)(int)fontAlign;
    }
    else
    {
        out->_alignment  = defaultTextAlignment;
    }
    
    // font alignment vertical
    JS_HasProperty(cx, jsobj, "verticalAlign", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "verticalAlign", &jsr);
        double fontAlign = 0.0;
        JS::ToNumber(cx, jsr, &fontAlign);
        out->_vertAlignment = (TextVAlignment)(int)fontAlign;
    }
    else
    {
        out->_vertAlignment  = defaultTextVAlignment;
    }
    
    // font fill color
    JS_HasProperty(cx, jsobj, "fillStyle", &hasProperty);
    if ( hasProperty )
    {
        JS_GetProperty(cx, jsobj, "fillStyle", &jsr);
        
        JS::RootedObject jsobjColor(cx);
        JS::RootedValue jsvalColor(cx, jsr);
        if (!JS_ValueToObject( cx, jsvalColor, &jsobjColor ) )
            return false;
        
        out->_fontFillColor = getColorFromJSObject(cx, jsobjColor);
    }
    
    // font rendering box dimensions
    JS_HasProperty(cx, jsobj, "boundingWidth", &hasProperty);
    JS_HasProperty(cx, jsobj, "boundingHeight", &hasSecondProp);
    if ( hasProperty && hasSecondProp )
    {
        JS_GetProperty(cx, jsobj, "boundingWidth", &jsr);
        double boundingW = 0.0;
        JS::ToNumber(cx, jsr, &boundingW);
        
        JS_GetProperty(cx, jsobj, "boundingHeight", &jsr);
        double boundingH = 0.0;
        JS::ToNumber(cx, jsr, &boundingH);
        
        Size dimension;
        dimension.width = boundingW;
        dimension.height = boundingH;
        out->_dimensions = dimension;
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
            JS_HasProperty(cx, jsobj, "shadowOffsetX", &hasProperty);
            JS_HasProperty(cx, jsobj, "shadowOffsetY", &hasSecondProp);
            if ( hasProperty && hasSecondProp )
            {
                JS_GetProperty(cx, jsobj, "shadowOffsetX", &jsr);
                double offx = 0.0;
                JS::ToNumber(cx, jsr, &offx);
                
                JS_GetProperty(cx, jsobj, "shadowOffsetY", &jsr);
                double offy = 0.0;
                JS::ToNumber(cx, jsr, &offy);
                
                Size offset;
                offset.width = offx;
                offset.height = offy;
                out->_shadow._shadowOffset = offset;
            }
            
            // shadow blur
            JS_HasProperty(cx, jsobj, "shadowBlur", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowBlur", &jsr);
                double shadowBlur = 0.0;
                JS::ToNumber(cx, jsr, &shadowBlur);
                out->_shadow._shadowBlur = shadowBlur;
            }
            
            // shadow intensity
            JS_HasProperty(cx, jsobj, "shadowOpacity", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "shadowOpacity", &jsr);
                double shadowOpacity = 0.0;
                JS::ToNumber(cx, jsr, &shadowOpacity);
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
            JS_HasProperty(cx, jsobj, "strokeStyle", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "strokeStyle", &jsr);
                
                JS::RootedObject jsobjStrokeColor(cx);
                if (!JS_ValueToObject( cx, jsr, &jsobjStrokeColor ) )
                    return false;
                out->_stroke._strokeColor = getColorFromJSObject(cx, jsobjStrokeColor);
            }
            
            // stroke size
            JS_HasProperty(cx, jsobj, "lineWidth", &hasProperty);
            if ( hasProperty )
            {
                JS_GetProperty(cx, jsobj, "lineWidth", &jsr);
                double strokeSize = 0.0;
                JS::ToNumber(cx, jsr, &strokeSize);
                out->_stroke._strokeSize = strokeSize;
            }
        }
    }
    
    // we are done here
    return true;
}

bool jsval_to_CCPoint( JSContext *cx, JS::HandleValue vp, Point *ret )
{
#ifdef JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
    JS::RootedObject jsobj(cx);
    if( ! JS_ValueToObject( cx, vp, &jsobj ) )
        return false;
    
    JSB_PRECONDITION( jsobj, "Not a valid JS object");
    
    JS::RootedValue valx(cx);
    JS::RootedValue valy(cx);
    bool ok = true;
    ok &= JS_GetProperty(cx, jsobj, "x", &valx);
    ok &= JS_GetProperty(cx, jsobj, "y", &valy);
    
    if( ! ok )
        return false;
    
    double x, y;
    ok &= JS::ToNumber(cx, valx, &x);
    ok &= JS::ToNumber(cx, valy, &y);
    
    if( ! ok )
        return false;
    
    ret->x = x;
    ret->y = y;
    
    return true;
    
#else // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    
    JSObject *tmp_arg;
    if( ! JS_ValueToObject( cx, vp, &tmp_arg ) )
        return false;
    
    JSB_PRECONDITION( tmp_arg && JS_IsTypedArrayObject( tmp_arg, cx ), "Not a TypedArray object");
    
    JSB_PRECONDITION( JS_GetTypedArrayByteLength( tmp_arg, cx ) == sizeof(cpVect), "Invalid length");
    
    *ret = *(Point*)JS_GetArrayBufferViewData( tmp_arg, cx );
    
    return true;
#endif // #! JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
}

jsval ccvalue_to_jsval(JSContext* cx, const cocos2d::Value& v)
{
    jsval ret = JSVAL_NULL;
    const Value& obj = v;
    
    switch (obj.getType())
    {
        case Value::Type::BOOLEAN:
            ret = BOOLEAN_TO_JSVAL(obj.asBool());
            break;
        case Value::Type::FLOAT:
        case Value::Type::DOUBLE:
            ret = DOUBLE_TO_JSVAL(obj.asDouble());
            break;
        case Value::Type::INTEGER:
            ret = INT_TO_JSVAL(obj.asInt());
            break;
        case Value::Type::STRING:
            ret = std_string_to_jsval(cx, obj.asString());
            break;
        case Value::Type::VECTOR:
            ret = ccvaluevector_to_jsval(cx, obj.asValueVector());
            break;
        case Value::Type::MAP:
            ret = ccvaluemap_to_jsval(cx, obj.asValueMap());
            break;
        case Value::Type::INT_KEY_MAP:
            ret = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
            break;
        default:
            break;
    }
    
    return ret;
}

jsval ccvaluemap_to_jsval(JSContext* cx, const cocos2d::ValueMap& v)
{
    JS::RootedObject jsRet(cx, JS_NewArrayObject(cx, 0));
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue dictElement(cx);

        std::string key = iter->first;
        const Value& obj = iter->second;
        
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                dictElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                dictElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case Value::Type::INTEGER:
                dictElement = INT_TO_JSVAL(obj.asInt());
                break;
            case Value::Type::STRING:
                dictElement = std_string_to_jsval(cx, obj.asString());
                break;
            case Value::Type::VECTOR:
                dictElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case Value::Type::MAP:
                dictElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case Value::Type::INT_KEY_MAP:
                dictElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRet, key.c_str(), dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

jsval ccvaluemapintkey_to_jsval(JSContext* cx, const cocos2d::ValueMapIntKey& v)
{
    JS::RootedObject jsRet(cx, JS_NewArrayObject(cx, 0));
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue dictElement(cx);
        std::stringstream keyss;
        keyss << iter->first;
        std::string key = keyss.str();
        
        const Value& obj = iter->second;
        
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                dictElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                dictElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case Value::Type::INTEGER:
                dictElement = INT_TO_JSVAL(obj.asInt());
                break;
            case Value::Type::STRING:
                dictElement = std_string_to_jsval(cx, obj.asString());
                break;
            case Value::Type::VECTOR:
                dictElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case Value::Type::MAP:
                dictElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case Value::Type::INT_KEY_MAP:
                dictElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRet, key.c_str(), dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

jsval ccvaluevector_to_jsval(JSContext* cx, const cocos2d::ValueVector& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
    
    int i = 0;
    for (const auto& obj : v)
    {
        JS::RootedValue arrElement(cx);
        
        switch (obj.getType())
        {
            case Value::Type::BOOLEAN:
                arrElement = BOOLEAN_TO_JSVAL(obj.asBool());
                break;
            case Value::Type::FLOAT:
            case Value::Type::DOUBLE:
                arrElement = DOUBLE_TO_JSVAL(obj.asDouble());
                break;
            case Value::Type::INTEGER:
                arrElement = INT_TO_JSVAL(obj.asInt());
                break;
            case Value::Type::STRING:
                arrElement = std_string_to_jsval(cx, obj.asString());
                break;
            case Value::Type::VECTOR:
                arrElement = ccvaluevector_to_jsval(cx, obj.asValueVector());
                break;
            case Value::Type::MAP:
                arrElement = ccvaluemap_to_jsval(cx, obj.asValueMap());
                break;
            case Value::Type::INT_KEY_MAP:
                arrElement = ccvaluemapintkey_to_jsval(cx, obj.asIntKeyMap());
                break;
            default:
                break;
        }

        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ssize_to_jsval(JSContext *cx, ssize_t v)
{
    CCASSERT(v < INT_MAX, "The size should not bigger than 32 bit (int32_t).");
    return int32_to_jsval(cx, static_cast<int>(v));
}

jsval std_vector_string_to_jsval( JSContext *cx, const std::vector<std::string>& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, v.size()));
    
    int i = 0;
    for (const std::string obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = std_string_to_jsval(cx, obj);
        
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval std_vector_int_to_jsval( JSContext *cx, const std::vector<int>& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, v.size()));
    
    int i = 0;
    for (const int obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = int32_to_jsval(cx, obj);
        
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval std_vector_float_to_jsval( JSContext *cx, const std::vector<float>& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, v.size()));

    int i = 0;
    for (const float obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = DOUBLE_TO_JSVAL(obj);

        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval matrix_to_jsval(JSContext *cx, const cocos2d::Mat4& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 16));
    
    for (int i = 0; i < 16; i++) {
        JS::RootedValue arrElement(cx);
        arrElement = DOUBLE_TO_JSVAL(v.m[i]);
        
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
    }
    
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval vector2_to_jsval(JSContext *cx, const cocos2d::Vec2& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval vector3_to_jsval(JSContext *cx, const cocos2d::Vec3& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval vector4_to_jsval(JSContext *cx, const cocos2d::Vec4& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "x", v.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", v.y, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "w", v.z, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval blendfunc_to_jsval(JSContext *cx, const cocos2d::BlendFunc& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "src", (uint32_t)v.src, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "dst", (uint32_t)v.dst, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval vector_vec2_to_jsval(JSContext *cx, const std::vector<cocos2d::Vec2>& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, v.size()));
    
    int i = 0;
    for (const cocos2d::Vec2 obj : v)
    {
        JS::RootedValue arrElement(cx);
        arrElement = vector2_to_jsval(cx, obj);
        
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval std_map_string_string_to_jsval(JSContext* cx, const std::map<std::string, std::string>& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, proto, parent));
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue element(cx);
        
        std::string key = iter->first;
        std::string obj = iter->second;
        
        element = std_string_to_jsval(cx, obj);
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRet, key.c_str(), element);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

bool jsval_to_resourcedata(JSContext *cx, JS::HandleValue v, ResourceData* ret) {
    JS::RootedObject tmp(cx);
    JS::RootedValue jstype(cx);
    JS::RootedValue jsfile(cx);
    JS::RootedValue jsplist(cx);

    double t = 0;
    std::string file, plist;
    bool ok = v.isObject() &&
        JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "type", &jstype) &&
        JS_GetProperty(cx, tmp, "name", &jsfile) &&
        JS_GetProperty(cx, tmp, "plist", &jsplist) &&
        JS::ToNumber(cx, jstype, &t) &&
        jsval_to_std_string(cx, jsfile, &file) &&
        jsval_to_std_string(cx, jsplist, &plist);

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    ret->type = (int)t;
    ret->file = file;
    ret->plist = plist;
    return true;
}

jsval resourcedata_to_jsval(JSContext* cx, const ResourceData& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "type", v.type, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "file", JS::RootedValue(cx, std_string_to_jsval(cx, v.file)), JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
        JS_DefineProperty(cx, tmp, "plist", JS::RootedValue(cx, std_string_to_jsval(cx, v.plist)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}
