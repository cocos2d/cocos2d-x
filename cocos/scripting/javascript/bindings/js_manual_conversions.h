//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//
#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"
#include "js_bindings_core.h"
#include "js_bindings_config.h"
#include "cocos2d.h"
#include "spidermonkey_specifics.h"

// just a simple utility to avoid mem leaking when using JSString
class JSStringWrapper
{
public:
    JSStringWrapper();
    JSStringWrapper(JSString* str, JSContext* cx = NULL);
    JSStringWrapper(jsval val, JSContext* cx = NULL);
    ~JSStringWrapper();
    
    void set(jsval val, JSContext* cx);
    void set(JSString* str, JSContext* cx);
    const char* get();
    
private:
    const char* _buffer;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JSStringWrapper);
};

// wraps a function and "this" object
class JSFunctionWrapper
{
public:
    JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval);
    ~JSFunctionWrapper();

    JSBool invoke(unsigned int argc, jsval *argv, jsval &rval);
private:
    JSContext *_cx;
    JSObject *_jsthis;
    jsval _fval;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JSFunctionWrapper);
};

JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
JSBool jsval_to_int( JSContext *cx, jsval vp, int *out);
JSBool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *out);
JSBool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy);
/** converts a jsval (JS string) into a char */
JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **out);

jsval opaque_to_jsval( JSContext *cx, void* opaque);
jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name);

/* Converts a char ptr into a jsval (using JS string) */
jsval charptr_to_jsval( JSContext *cx, const char *str);
JSBool JSB_jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t);
JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data );

// some utility functions
// to native
JSBool jsval_to_ushort( JSContext *cx, jsval vp, unsigned short *ret );
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
JSBool jsval_to_long( JSContext *cx, jsval vp, long *out);
JSBool jsval_to_ulong( JSContext *cx, jsval vp, unsigned long *out);
JSBool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);
JSBool jsval_to_ccpoint(JSContext *cx, jsval v, cocos2d::Point* ret);
JSBool jsval_to_ccrect(JSContext *cx, jsval v, cocos2d::Rect* ret);
JSBool jsval_to_ccsize(JSContext *cx, jsval v, cocos2d::Size* ret);
JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, cocos2d::Color4B* ret);
JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, cocos2d::Color4F* ret);
JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, cocos2d::Color3B* ret);
JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, cocos2d::Point **points, int *numPoints);
JSBool jsval_to_ccarray(JSContext* cx, jsval v, cocos2d::__Array** ret);
JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, cocos2d::__Dictionary** ret);
JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, cocos2d::Acceleration* ret);
JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, cocos2d::__Array** ret);

// forward declaration
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);

template <class T>
JSBool jsvals_variadic_to_ccvector( JSContext *cx, jsval *vp, int argc, cocos2d::Vector<T>* ret)
{
    JSBool ok = JS_TRUE;

    for (int i = 0; i < argc; i++)
    {
        js_proxy_t* p;
        JSObject* obj = JSVAL_TO_OBJECT(*vp);
        p = jsb_get_js_proxy(obj);
        CCASSERT(p, "Native object not found!");
        if (p) {
            ret->pushBack((T)p->ptr);
        }
        
        // next
        vp++;
    }

    JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");
    return ok;
}

JSBool jsvals_variadic_to_ccvaluevector( JSContext *cx, jsval *vp, int argc, cocos2d::ValueVector* ret);

JSBool jsval_to_ccaffinetransform(JSContext* cx, jsval v, cocos2d::AffineTransform* ret);
JSBool jsval_to_FontDefinition( JSContext *cx, jsval vp, cocos2d::FontDefinition* ret );

template <class T>
JSBool jsval_to_ccvector(JSContext* cx, jsval v, cocos2d::Vector<T>* ret)
{
    JSObject *jsobj;
    JSBool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");
    
    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);

    for (uint32_t i=0; i < len; i++)
    {
        jsval value;
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            CCASSERT(value.isObject(), "the element in Vector isn't a native object.");

            js_proxy_t *proxy;
            JSObject *tmp = JSVAL_TO_OBJECT(value);
            proxy = jsb_get_js_proxy(tmp);
            T cobj = (T)(proxy ? proxy->ptr : nullptr);
            if (cobj)
            {
                ret->pushBack(cobj);
            }
        }
    }

    return JS_TRUE;
}

JSBool jsval_to_ccvalue(JSContext* cx, jsval v, cocos2d::Value* ret);
JSBool jsval_to_ccvaluemap(JSContext* cx, jsval v, cocos2d::ValueMap* ret);
JSBool jsval_to_ccvaluemapintkey(JSContext* cx, jsval v, cocos2d::ValueMapIntKey* ret);
JSBool jsval_to_ccvaluevector(JSContext* cx, jsval v, cocos2d::ValueVector* ret);
JSBool jsval_to_ssize( JSContext *cx, jsval vp, ssize_t* ret);
JSBool jsval_to_std_vector_string( JSContext *cx, jsval vp, std::vector<std::string>* ret);
JSBool jsval_to_std_vector_int( JSContext *cx, jsval vp, std::vector<int>* ret);

template <class T>
JSBool jsval_to_ccmap_string_key(JSContext *cx, jsval v, cocos2d::Map<std::string, T>* ret)
{
    if (JSVAL_IS_NULL(v) || JSVAL_IS_VOID(v))
    {
        return JS_TRUE;
    }
    
    JSObject* tmp = JSVAL_TO_OBJECT(v);
    if (!tmp) {
        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
        return JS_FALSE;
    }
    
    JSObject* it = JS_NewPropertyIterator(cx, tmp);
    
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
        
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (value.isObject())
        {
            js_proxy_t *proxy = nullptr;
            JSObject* jsobj = JSVAL_TO_OBJECT(value);
            proxy = jsb_get_js_proxy(jsobj);
            CCASSERT(proxy, "Native object should be added!");
            T cobj = (T)(proxy ? proxy->ptr : nullptr);
            ret->insert(keyWrapper.get(), cobj);
        }
        else
        {
            CCASSERT(false, "not supported type");
        }
    }
    
    return JS_TRUE;
}

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval ushort_to_jsval( JSContext *cx, unsigned short number );
jsval long_to_jsval( JSContext *cx, long number );
jsval ulong_to_jsval(JSContext* cx, unsigned long v);
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, const std::string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);
jsval ccpoint_to_jsval(JSContext* cx, const cocos2d::Point& v);
jsval ccrect_to_jsval(JSContext* cx, const cocos2d::Rect& v);
jsval ccsize_to_jsval(JSContext* cx, const cocos2d::Size& v);
jsval cccolor4b_to_jsval(JSContext* cx, const cocos2d::Color4B& v);
jsval cccolor4f_to_jsval(JSContext* cx, const cocos2d::Color4F& v);
jsval cccolor3b_to_jsval(JSContext* cx, const cocos2d::Color3B& v);
jsval ccdictionary_to_jsval(JSContext* cx, cocos2d::__Dictionary *dict);
jsval ccarray_to_jsval(JSContext* cx, cocos2d::__Array *arr);
jsval ccacceleration_to_jsval(JSContext* cx, const cocos2d::Acceleration& v);
jsval ccaffinetransform_to_jsval(JSContext* cx, const cocos2d::AffineTransform& t);
jsval FontDefinition_to_jsval(JSContext* cx, const cocos2d::FontDefinition& t);

JSBool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *out );
jsval CGPoint_to_jsval( JSContext *cx, cpVect p );

#define cpVect_to_jsval CGPoint_to_jsval
#define jsval_to_cpVect jsval_to_CGPoint


template<class T>
js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj);

template <class T>
jsval ccvector_to_jsval(JSContext* cx, const cocos2d::Vector<T>& v)
{
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);
    
    int i = 0;
    for (const auto& obj : v)
    {
        jsval arrElement;
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Object>(cx, obj);
        if (jsproxy) {
            arrElement = OBJECT_TO_JSVAL(jsproxy->obj);
        }

        if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

template <class T>
jsval ccmap_string_key_to_jsval(JSContext* cx, const cocos2d::Map<std::string, T>& v)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue element(cx);
        
        std::string key = iter->first;
        T obj = iter->second;
        
        //First, check whether object is associated with js object.
        js_proxy_t* jsproxy = js_get_or_create_proxy<cocos2d::Object>(cx, obj);
        if (jsproxy) {
            element = OBJECT_TO_JSVAL(jsproxy->obj);
        }
        
        if (!key.empty())
        {
            JS_SetProperty(cx, jsRet, key.c_str(), element);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

jsval ccvalue_to_jsval(JSContext* cx, const cocos2d::Value& v);
jsval ccvaluemap_to_jsval(JSContext* cx, const cocos2d::ValueMap& v);
jsval ccvaluemapintkey_to_jsval(JSContext* cx, const cocos2d::ValueMapIntKey& v);
jsval ccvaluevector_to_jsval(JSContext* cx, const cocos2d::ValueVector& v);
jsval ssize_to_jsval(JSContext *cx, ssize_t v);

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

