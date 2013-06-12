#include "jsb_pluginx_basic_conversions.h"
#include <math.h>

#include "jsb_pluginx_spidermonkey_specifics.h"
#include "pluginxUTF8.h"

namespace pluginx {

// just a simple utility to avoid mem leaking when using JSString
class JSStringWrapper
{
    JSString*   string;
    const char* buffer;
    JSContext* cx;
public:
    JSStringWrapper() {
        buffer = NULL;
    }
    JSStringWrapper(JSString* str, JSContext* cx) {
        set(str, cx);
    }
    JSStringWrapper(jsval val, JSContext* cx) {
        set(val, cx);
    }
    ~JSStringWrapper() {
        if (buffer) {
            // delete[] buffer;
            // buffer = NULL;
            JS_free(cx, (void*)buffer);
        }
    }
    void set(jsval val, JSContext* cx) {
        if (val.isString()) {
            this->set(val.toString(), cx);
        } else {
            buffer = NULL;
        }
    }
    void set(JSString* str, JSContext* cx) {
        this->cx = cx;
        string = str;
        // Not suppored in SpiderMonkey v19
        buffer = JS_EncodeString(cx, string);
        
        // const jschar *chars = JS_GetStringCharsZ(cx, string);
        // size_t l = JS_GetStringLength(string);
        // char* pUTF8Str = cc_utf16_to_utf8((const unsigned short*)chars, l, NULL, NULL);
        // buffer = pUTF8Str;
    }

    std::string get() {
        return buffer;
    }

    operator std::string() {
        return std::string(buffer);
    }
    operator char*() {
        return (char*)buffer;
    }
};


JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_int32: the argument is not a number");
        return JS_FALSE;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (int32_t)dp;

    return ok;
}

JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_uint32: the argument is not a number");
        return JS_FALSE;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint32_t)dp;

    return ok;
}

JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_uint16: the argument is not a number");
        return JS_FALSE;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint16_t)dp;

    return ok;
}

JSBool jsval_to_long_long(JSContext *cx, jsval vp, long long* r) {
    JSObject *tmp_arg;
    JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
    if (!ok) {
        LOGD("jsval_to_long_long: Error converting value to object");
        return JS_FALSE;
    }

    JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
    JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
    
    uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
    long long ret =  arg_array[0];
    ret = ret << 32;
    ret |= arg_array[1];
    
    *r = ret;
    return JS_TRUE;
}

JSBool jsval_to_long(JSContext *cx, jsval vp, long* ret)
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_long: the argument is not a number");
        return JS_FALSE;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *ret = (long)dp;

    return ok;
}

JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JSString *tmp = JS_ValueToString(cx, v);
    if (!tmp) {
        LOGD("jsval_to_std_string: the jsval is not a string.");
        return JS_FALSE;
    }

    JSStringWrapper str(tmp, cx);
    *ret = str.get();
    return JS_TRUE;
}

JSBool jsval_to_TProductInfo(JSContext *cx, jsval v, TProductInfo* ret)
{
    JSObject* tmp = JSVAL_TO_OBJECT(v);
    if (!tmp) {
        LOGD("jsval_to_TProductInfo: the jsval is not an object.");
        return JS_FALSE;
    }

    JSObject* it = JS_NewPropertyIterator(cx, tmp);

    while (true)
    {
        jsid idp;
        jsval key;
        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key))
            return JS_FALSE; // error
        if (key == JSVAL_VOID)
            break; // end of iteration
        if (! JSVAL_IS_STRING(key))
            continue; // ignore integer properties
        jsval value;
        JS_GetPropertyById(cx, tmp, idp, &value);
        if (! JSVAL_IS_STRING(value))
            continue; // ignore integer properties

        JSStringWrapper strWrapper(JSVAL_TO_STRING(key), cx);
        JSStringWrapper strWrapper2(JSVAL_TO_STRING(value), cx);

        (*ret)[strWrapper.get()] = strWrapper2.get();
        LOGD("iterate object: key = %s, value = %s", strWrapper.get().c_str(), strWrapper2.get().c_str());
    }

    return JS_TRUE;
}

JSBool jsval_to_TIAPDeveloperInfo(JSContext *cx, jsval v, TIAPDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

JSBool jsval_to_TAdsDeveloperInfo(JSContext *cx, jsval v, TAdsDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

JSBool jsval_to_TSocialDeveloperInfo(JSContext *cx, jsval v, TSocialDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

JSBool jsval_to_TShareInfo(JSContext *cx, jsval v, TShareInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

JSBool jsval_to_TPaymentInfo(JSContext *cx, jsval v, std::map<std::string, std::string>* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

JSBool jsval_to_LogEventParamMap(JSContext *cx, jsval v, LogEventParamMap** ret)
{
    JSBool jsret = JS_FALSE;
    if (v.isObject())
    {
        LogEventParamMap* tmp = new LogEventParamMap();
        jsret = jsval_to_TProductInfo(cx, v, tmp);
        if (jsret) {
            *ret = tmp;
        }
    }

    return jsret;
}

JSBool jsval_to_StringMap(JSContext *cx, jsval v, StringMap* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
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

jsval long_long_to_jsval(JSContext* cx, long long v) {
    JSObject *tmp = JS_NewUint32Array(cx, 2);
    uint32_t *data = (uint32_t *)JS_GetArrayBufferViewData(tmp);
    data[0] = ((uint32_t *)(&v))[0];
    data[1] = ((uint32_t *)(&v))[1];
    return OBJECT_TO_JSVAL(tmp);
}

jsval long_to_jsval(JSContext* cx, long v)
{
    return INT_TO_JSVAL(v);
}

jsval std_string_to_jsval(JSContext* cx, std::string& v) {
    JSString *str = JS_NewStringCopyZ(cx, v.c_str());
    jsval rval;
    // unsigned short* pUTF16 = cc_utf8_to_utf16(v.c_str());
    // JSString *str = JS_NewUCStringCopyZ(cx, pUTF16);
    rval = STRING_TO_JSVAL(str);
    // delete[] pUTF16;
    return rval;
}

jsval c_string_to_jsval(JSContext* cx, const char* v) {
    std::string str(v);
    return std_string_to_jsval(cx, str);
}

jsval TProductInfo_to_jsval(JSContext *cx, TProductInfo& ret)
{
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;

    for (TProductInfo::iterator it = ret.begin(); it != ret.end(); ++it)
    {
        JS_DefineProperty(cx, tmp, it->first.c_str(), std_string_to_jsval(cx, it->second), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    }

    return OBJECT_TO_JSVAL(tmp);
}

jsval LogEventParamMap_to_jsval(JSContext *cx, LogEventParamMap*& ret)
{// TODO:
    return JSVAL_NULL;
}

}// namespace pluginx {

