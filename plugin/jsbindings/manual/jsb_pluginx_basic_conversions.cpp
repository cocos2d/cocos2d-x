#include "jsb_pluginx_basic_conversions.h"
#include <math.h>

#include "jsb_pluginx_spidermonkey_specifics.h"
#include "pluginxUTF8.h"
#include <sstream>

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
        //buffer = JS_EncodeString(cx, string);
        
        buffer = JS_EncodeString(cx, str);
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

// JSFunctionWrapper
JSFunctionWrapper::JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval)
: _cx(cx)
, _jsthis(jsthis)
, _fval(fval)
{
    JS::AddNamedValueRoot(cx, &this->_fval, "JSFunctionWrapper");
    JS::AddNamedObjectRoot(cx, &this->_jsthis, "JSFunctionWrapper");
}

JSFunctionWrapper::~JSFunctionWrapper()
{
    JS::RemoveValueRoot(this->_cx, &this->_fval);
    JS::RemoveObjectRoot(this->_cx, &this->_jsthis);
}

bool JSFunctionWrapper::invoke(unsigned int argc, jsval *argv, JS::MutableHandleValue rval)
{
    //JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    return JS_CallFunctionValue(this->_cx, JS::RootedObject(_cx, this->_jsthis), JS::RootedValue(_cx, this->_fval), JS::HandleValueArray::fromMarkedLocation(argc, argv), rval);
}

bool jsval_to_int32( JSContext *cx, JS::HandleValue vp, int32_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_int32: the argument is not a number");
        return false;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    *outval = (int32_t)dp;

    return ok;
}

bool jsval_to_uint32( JSContext *cx, JS::HandleValue vp, uint32_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_uint32: the argument is not a number");
        return false;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    *outval = (uint32_t)dp;

    return ok;
}

bool jsval_to_uint16( JSContext *cx, JS::HandleValue vp, uint16_t *outval )
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_uint16: the argument is not a number");
        return false;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    *outval = (uint16_t)dp;

    return ok;
}

bool jsval_to_long_long(JSContext *cx, JS::HandleValue vp, long long* r) {
    JS::RootedObject tmp_arg(cx);
    bool ok = JS_ValueToObject( cx, vp, &tmp_arg );
    if (!ok) {
        LOGD("jsval_to_long_long: Error converting value to object");
        return false;
    }

    JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, false, "Not a TypedArray object");
    JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, false, "Invalid Typed Array length");
    
    uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
    long long ret =  arg_array[0];
    ret = ret << 32;
    ret |= arg_array[1];
    
    *r = ret;
    return true;
}

bool jsval_to_long(JSContext *cx, JS::HandleValue vp, long* ret)
{
    bool ok = true;
    double dp;
    ok &= JS::ToNumber(cx, vp, &dp);
    if (!ok) {
        LOGD("jsval_to_long: the argument is not a number");
        return false;
    }
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    *ret = (long)dp;

    return ok;
}

bool jsval_to_std_string(JSContext *cx, JS::HandleValue v, std::string* ret) {
    JSString *tmp = JS::ToString(cx, v);
    if (!tmp) {
        LOGD("jsval_to_std_string: the jsval is not a string.");
        return false;
    }

    JSStringWrapper str(tmp, cx);
    *ret = str.get();
    return true;
}

bool jsval_to_TProductInfo(JSContext *cx, JS::HandleValue v, TProductInfo* ret)
{
    JS::RootedObject tmp(cx, v.toObjectOrNull());
    if (!tmp) {
        LOGD("jsval_to_TProductInfo: the jsval is not an object.");
        return false;
    }

    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));

    while (true)
    {
        jsid idp;
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key))
            return false; // error
        if (key.isNullOrUndefined())
            break; // end of iteration
        if (! key.isString())
            continue; // ignore integer properties
        JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, JS::RootedId(cx, idp), &value);
        if (! value.isString())
            continue; // ignore integer properties

        JSStringWrapper strWrapper(key.toString(), cx);
        JSStringWrapper strWrapper2(value.toString(), cx);

        (*ret)[strWrapper.get()] = strWrapper2.get();
        LOGD("iterate object: key = %s, value = %s", strWrapper.get().c_str(), strWrapper2.get().c_str());
    }

    return true;
}

bool jsval_to_FBInfo(JSContext *cx, JS::HandleValue v, StringMap* ret)
{
    JS::RootedObject tmp(cx, v.toObjectOrNull());
	if (!tmp) {
		LOGD("jsval_to_TProductInfo: the jsval is not an object.");
		return false;
	}

    JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));

	while (true)
	{
		jsid idp;
        JS::RootedValue key(cx);
		if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key))
			return false; // error
		if (key.isNullOrUndefined())
			break; // end of iteration
		if (! key.isString())
			continue; // ignore integer properties
		JS::RootedValue value(cx);
        JS_GetPropertyById(cx, tmp, JS::RootedId(cx, idp), &value);

//		if (! JSVAL_IS_STRING(value))
//			continue; // ignore integer properties
		if(value.isString())
		{

			JSStringWrapper strWrapper(key.toString(), cx);
			JSStringWrapper strWrapper2(value.toString(), cx);

			ret->insert(std::map<std::string, std::string>::value_type(strWrapper.get(), strWrapper2.get()));
		}
		else if(value.isNumber())
		{
			double number = 0.0;
			JS::ToNumber(cx, value, &number);

			std::stringstream ss;
			ss << number;

			JSStringWrapper strWrapper(key.toString(), cx);
			//JSStringWrapper strWrapper2(JSVAL_TO_STRING(value), cx);

			ret->insert(std::map<std::string, std::string>::value_type(strWrapper.get(), ss.str()));
		}
		else if(value.isBoolean())
		{
			bool boolVal = JS::ToBoolean(value);
			JSStringWrapper strWrapper(key.toString(), cx);
			//JSStringWrapper strWrapper2(JSVAL_TO_STRING(value), cx);
			std::string boolstring = boolVal ? "true" : "false";
			ret->insert(std::map<std::string, std::string>::value_type(strWrapper.get(), boolstring));
		}
	}

	return true;
}

bool jsval_array_to_string(JSContext *cx, JS::HandleValue v, std::string* ret)
{
	JS::RootedObject jsobj(cx);
	bool ok = v.isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, v), &jsobj );
	JSB_PRECONDITION2( ok, cx, false, "Error converting value to object");
	JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");

	uint32_t len;
	JS_GetArrayLength(cx, jsobj, &len);

	for( uint32_t i=0; i< len;i++ ) {
		JS::RootedValue valarg(cx);
		JS_GetElement(cx, jsobj, i, &valarg);

		std::string temp;
		ok = jsval_to_std_string(cx, valarg, &temp);
		JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
		if(i != len -1)
			ret->append(temp + ",");
		else
			ret->append(temp);
	}

	return true;
}

bool jsval_to_TIAPDeveloperInfo(JSContext *cx, JS::HandleValue v, TIAPDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TAdsDeveloperInfo(JSContext *cx, JS::HandleValue v, TAdsDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TAdsInfo(JSContext *cx, JS::HandleValue v, TAdsInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TShareDeveloperInfo(JSContext *cx, JS::HandleValue v, TShareDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TShareInfo(JSContext *cx, JS::HandleValue v, TShareInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TPaymentInfo(JSContext *cx, JS::HandleValue v, std::map<std::string, std::string>* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TSocialDeveloperInfo(JSContext *cx, JS::HandleValue v, TSocialDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TAchievementInfo(JSContext *cx, JS::HandleValue v, TAchievementInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_TUserDeveloperInfo(JSContext *cx, JS::HandleValue v, TUserDeveloperInfo* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}

bool jsval_to_LogEventParamMap(JSContext *cx, JS::HandleValue v, LogEventParamMap** ret)
{
    bool jsret = false;
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

bool jsval_to_StringMap(JSContext *cx, JS::HandleValue v, StringMap* ret)
{
    return jsval_to_TProductInfo(cx, v, ret);
}
    
bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string, std::string>* ret)
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
        jsid idp;
        JS::RootedValue key(cx);
        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
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
        JS_GetPropertyById(cx, tmp, JS::RootedId(cx, idp), &value);
        if (value.isString())
        {
            JSStringWrapper valueWapper(value.toString(), cx);
            ret->insert(std::make_pair(keyWrapper.get(), valueWapper.get()));
        }
        else
        {
            CCASSERT(false, "not a string");
        }
    }
        
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

jsval std_string_to_jsval(JSContext* cx, const std::string& v) {
    return c_string_to_jsval(cx, v.data());
}

jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length /* = -1 */) {
    if (v == NULL) {
        return JSVAL_NULL;
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

jsval TProductInfo_to_jsval(JSContext *cx, TProductInfo& ret)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
    if (!tmp) return JSVAL_NULL;

    for (TProductInfo::iterator it = ret.begin(); it != ret.end(); ++it)
    {
        JS_DefineProperty(cx, tmp, it->first.c_str(), JS::RootedValue(cx, std_string_to_jsval(cx, it->second)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    }

    return OBJECT_TO_JSVAL(tmp);
}

jsval TProductList_to_jsval(JSContext *cx,TProductList list){
    JS::RootedObject tmp(cx, JS_NewArrayObject(cx, 0));
	int i = 0;
	for(TProductList::iterator it = list.begin();it!=list.end();++it){
		JS::RootedValue arrElement(cx);

		arrElement = TProductInfo_to_jsval(cx, *it);
		JS_SetElement(cx, tmp, i, arrElement);
		++i;
	}
	return OBJECT_TO_JSVAL(tmp);
}
    
jsval LogEventParamMap_to_jsval(JSContext *cx, LogEventParamMap*& ret)
{// TODO:
    return JSVAL_NULL;
}

}// namespace pluginx {

