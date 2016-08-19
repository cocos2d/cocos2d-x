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

#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "scripting/js-bindings/manual/js_bindings_core.h"
#include "scripting/js-bindings/manual/js_bindings_config.h"

#include "3d/CCBundle3DData.h"
#include "3d/CCOBB.h"
#include "3d/CCRay.h"
#include "base/CCEventMouse.h"
#include "base/CCMap.h"
#include "base/CCValue.h"
#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "deprecated/CCArray.h"
#include "math/CCAffineTransform.h"
#include "platform/CCPlatformMacros.h"
#include "renderer/CCGLProgram.h"
#include "scripting/js-bindings/manual/spidermonkey_specifics.h"
#include "scripting/js-bindings/manual/js-BindingsExport.h"

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES

NS_CC_BEGIN
struct CC_DLL ResourceData;
NS_CC_END

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
    JSFunctionWrapper(JSContext* cx, JS::HandleObject jsthis, JS::HandleValue fval);
    JSFunctionWrapper(JSContext* cx, JS::HandleObject jsthis, JS::HandleValue fval, JS::HandleValue owner);
    ~JSFunctionWrapper();

    bool invoke(unsigned int argc, jsval *argv, JS::MutableHandleValue rval);
private:
    JSContext *_cx;
    JS::Heap<JSObject*> _jsthis;
    JS::Heap<JS::Value> _fval;
    JS::Heap<JS::Value> _owner;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JSFunctionWrapper);
};

bool jsval_to_opaque( JSContext *cx, JS::HandleValue vp, void **out );
bool jsval_to_int( JSContext *cx, JS::HandleValue vp, int *out);
bool jsval_to_uint( JSContext *cx, JS::HandleValue vp, unsigned int *out);
bool jsval_to_c_class( JSContext *cx, JS::HandleValue vp, void **out_native, struct jsb_c_proxy_s **out_proxy);
/** converts a jsval (JS string) into a char */
bool jsval_to_charptr( JSContext *cx, JS::HandleValue vp, const char **out);

jsval opaque_to_jsval( JSContext *cx, void* opaque);
jsval c_class_to_jsval( JSContext *cx, void* handle, JS::HandleObject object, JSClass *klass, const char* class_name);

/* Converts a char ptr into a jsval (using JS string) */
jsval charptr_to_jsval( JSContext *cx, const char *str);
bool JSB_jsval_typedarray_to_dataptr( JSContext *cx, JS::HandleValue vp, GLsizei *count, void **data, js::Scalar::Type t);
bool JSB_get_arraybufferview_dataptr( JSContext *cx, JS::HandleValue vp, GLsizei *count, GLvoid **data );

// some utility functions
// to native
bool jsval_to_ushort( JSContext *cx, JS::HandleValue vp, unsigned short *ret );
bool jsval_to_int32( JSContext *cx, JS::HandleValue vp, int32_t *ret );
bool jsval_to_uint32( JSContext *cx, JS::HandleValue vp, uint32_t *ret );
bool jsval_to_uint16( JSContext *cx, JS::HandleValue vp, uint16_t *ret );
bool jsval_to_long( JSContext *cx, JS::HandleValue vp, long *out);
bool jsval_to_ulong( JSContext *cx, JS::HandleValue vp, unsigned long *out);
bool jsval_to_long_long(JSContext *cx, JS::HandleValue v, long long* ret);
CC_JS_DLL bool jsval_to_std_string(JSContext *cx, JS::HandleValue v, std::string* ret);
bool jsval_to_ccpoint(JSContext *cx, JS::HandleValue v, cocos2d::Point* ret);
bool jsval_to_ccrect(JSContext *cx, JS::HandleValue v, cocos2d::Rect* ret);
bool jsval_to_ccsize(JSContext *cx, JS::HandleValue v, cocos2d::Size* ret);
bool jsval_to_cccolor4b(JSContext *cx, JS::HandleValue v, cocos2d::Color4B* ret);
bool jsval_to_cccolor4f(JSContext *cx, JS::HandleValue v, cocos2d::Color4F* ret);
bool jsval_to_cccolor3b(JSContext *cx, JS::HandleValue v, cocos2d::Color3B* ret);
bool jsval_cccolor_to_opacity(JSContext *cx, JS::HandleValue v, int32_t* ret);
bool jsval_to_ccarray_of_CCPoint(JSContext* cx, JS::HandleValue v, cocos2d::Point **points, int *numPoints);
bool jsval_to_ccarray(JSContext* cx, JS::HandleValue v, cocos2d::__Array** ret);
bool jsval_to_ccdictionary(JSContext* cx, JS::HandleValue v, cocos2d::__Dictionary** ret);
bool jsval_to_ccacceleration(JSContext* cx, JS::HandleValue v, cocos2d::Acceleration* ret);
bool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, cocos2d::__Array** ret);
bool jsval_to_quaternion(JSContext *cx, JS::HandleValue vp, cocos2d::Quaternion* ret);
bool jsval_to_obb(JSContext *cx, JS::HandleValue vp, cocos2d::OBB* ret);
bool jsval_to_ray(JSContext *cx, JS::HandleValue vp, cocos2d::Ray* ret);
bool jsval_to_resourcedata(JSContext *cx, JS::HandleValue v, cocos2d::ResourceData* ret);

// forward declaration
CC_JS_DLL js_proxy_t* jsb_get_js_proxy(JS::HandleObject jsObj);

template <class T>
bool jsvals_variadic_to_ccvector( JSContext *cx, /*jsval *vp, int argc,*/const JS::CallArgs& args, cocos2d::Vector<T>* ret)
{
    bool ok = true;

    for (unsigned i = 0; i < args.length(); i++)
    {
        js_proxy_t* p;
        JS::RootedObject obj(cx, args.get(i).toObjectOrNull());

        p = jsb_get_js_proxy(obj);
        CCASSERT(p, "Native object not found!");
        if (p) {
            ret->pushBack((T)p->ptr);
        }
    }

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    return ok;
}

bool jsvals_variadic_to_ccvaluevector( JSContext *cx, jsval *vp, int argc, cocos2d::ValueVector* ret);

bool jsval_to_ccaffinetransform(JSContext* cx, JS::HandleValue v, cocos2d::AffineTransform* ret);
bool jsval_to_FontDefinition( JSContext *cx, JS::HandleValue vp, cocos2d::FontDefinition* ret );

template <class T>
bool jsval_to_ccvector(JSContext* cx, JS::HandleValue v, cocos2d::Vector<T>* ret)
{
    JS::RootedObject jsobj(cx);

    bool ok = v.isObject() && JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");

    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);

    for (uint32_t i=0; i < len; i++)
    {
        JS::RootedValue value(cx);
        if (JS_GetElement(cx, jsobj, i, &value))
        {
            CCASSERT(value.isObject(), "the element in Vector isn't a native object.");

            js_proxy_t *proxy;
            JS::RootedObject tmp(cx, value.toObjectOrNull());
            proxy = jsb_get_js_proxy(tmp);
            T cobj = (T)(proxy ? proxy->ptr : nullptr);
            if (cobj)
            {
                ret->pushBack(cobj);
            }
        }
    }

    return true;
}

bool jsval_to_ccvalue(JSContext* cx, JS::HandleValue v, cocos2d::Value* ret);
bool jsval_to_ccvaluemap(JSContext* cx, JS::HandleValue v, cocos2d::ValueMap* ret);
bool jsval_to_ccvaluemapintkey(JSContext* cx, JS::HandleValue v, cocos2d::ValueMapIntKey* ret);
bool jsval_to_ccvaluevector(JSContext* cx, JS::HandleValue v, cocos2d::ValueVector* ret);
bool jsval_to_ssize( JSContext *cx, JS::HandleValue vp, ssize_t* ret);
CC_JS_DLL bool jsval_to_std_vector_string( JSContext *cx, JS::HandleValue vp, std::vector<std::string>* ret);
bool jsval_to_std_vector_int( JSContext *cx, JS::HandleValue vp, std::vector<int>* ret);
bool jsval_to_std_vector_float( JSContext *cx, JS::HandleValue vp, std::vector<float>* ret);
bool jsval_to_matrix(JSContext *cx, JS::HandleValue vp, cocos2d::Mat4* ret);
bool jsval_to_vector2(JSContext *cx, JS::HandleValue vp, cocos2d::Vec2* ret);
bool jsval_to_vector3(JSContext *cx, JS::HandleValue vp, cocos2d::Vec3* ret);
bool jsval_to_vector4(JSContext *cx, JS::HandleValue vp, cocos2d::Vec4* ret);
bool jsval_to_blendfunc(JSContext *cx, JS::HandleValue vp, cocos2d::BlendFunc* ret);
bool jsval_to_vector_vec2(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::Vec2>* ret);
bool jsval_to_cctex2f(JSContext* cx, JS::HandleValue vp, cocos2d::Tex2F* ret);
bool jsval_to_v3fc4bt2f(JSContext* cx, JS::HandleValue v, cocos2d::V3F_C4B_T2F* ret);
bool jsval_to_v3fc4bt2f_quad(JSContext* cx, JS::HandleValue v, cocos2d::V3F_C4B_T2F_Quad* ret);
bool jsval_to_vector_v3fc4bt2f(JSContext* cx, JS::HandleValue v, std::vector<cocos2d::V3F_C4B_T2F>* ret);
bool jsval_to_std_map_string_string(JSContext* cx, JS::HandleValue v, std::map<std::string, std::string>* ret);

template <class T>
bool jsval_to_ccmap_string_key(JSContext *cx, JS::HandleValue v, cocos2d::Map<std::string, T>* ret)
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

    while (true)
    {
        JS::RootedId idp(cx);
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
            return false; // error
        }

        if (key.isUndefined()) {
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
            js_proxy_t *proxy = nullptr;
            JS::RootedObject jsobj(cx, value.toObjectOrNull());
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

    return true;
}

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval ushort_to_jsval( JSContext *cx, unsigned short number );
jsval long_to_jsval( JSContext *cx, long number );
jsval ulong_to_jsval(JSContext* cx, unsigned long v);
jsval long_long_to_jsval(JSContext* cx, long long v);
CC_JS_DLL jsval std_string_to_jsval(JSContext* cx, const std::string& v);
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
jsval quaternion_to_jsval(JSContext* cx, const cocos2d::Quaternion& q);
jsval meshVertexAttrib_to_jsval(JSContext* cx, const cocos2d::MeshVertexAttrib& q);
jsval uniform_to_jsval(JSContext* cx, const cocos2d::Uniform* uniform);
jsval resourcedata_to_jsval(JSContext* cx, const cocos2d::ResourceData& v);


// forward declaration
template <class T>
js_type_class_t *js_get_type_from_native(T* native_obj);

// Ref version of ccvector_to_jsval
template <class T>
jsval ccvector_to_jsval(JSContext* cx, const cocos2d::Vector<T>& v)
{
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));

    int i = 0;
    for (const auto& obj : v)
    {
        JS::RootedValue arrElement(cx);

        //First, check whether object is associated with js object.
        js_type_class_t *typeClass = js_get_type_from_native(obj);
        JS::RootedObject jsobject(cx, jsb_ref_get_or_create_jsobject(cx, obj, typeClass, typeid(*obj).name()));
        if (jsobject.get()) {
            arrElement = OBJECT_TO_JSVAL(jsobject);
        }

        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

template <class T>
jsval ccmap_string_key_to_jsval(JSContext* cx, const cocos2d::Map<std::string, T>& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, proto, parent));

    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        JS::RootedValue element(cx);

        std::string key = iter->first;
        T obj = iter->second;

        //First, check whether object is associated with js object.
        js_type_class_t *typeClass = js_get_type_from_native(obj);
        JS::RootedObject jsobject(cx, jsb_ref_get_or_create_jsobject(cx, obj, typeClass, typeid(*obj).name()));

        if (jsobject.get()) {
            element = OBJECT_TO_JSVAL(jsobject);
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
jsval std_vector_string_to_jsval( JSContext *cx, const std::vector<std::string>& v);
jsval std_vector_int_to_jsval( JSContext *cx, const std::vector<int>& v);
jsval std_vector_float_to_jsval( JSContext *cx, const std::vector<float>& v);
jsval matrix_to_jsval(JSContext *cx, const cocos2d::Mat4& v);
jsval vector2_to_jsval(JSContext *cx, const cocos2d::Vec2& v);
jsval vector3_to_jsval(JSContext *cx, const cocos2d::Vec3& v);
jsval vector4_to_jsval(JSContext *cx, const cocos2d::Vec4& v);
jsval blendfunc_to_jsval(JSContext *cx, const cocos2d::BlendFunc& v);
jsval vector_vec2_to_jsval(JSContext *cx, const std::vector<cocos2d::Vec2>& v);
jsval std_map_string_string_to_jsval(JSContext* cx, const std::map<std::string, std::string>& v);

#endif /* __JS_MANUAL_CONVERSIONS_H__ */
