#ifndef __JS_BASIC_CONVERSIONS_H__
#define __JS_BASIC_CONVERSIONS_H__

#include "jsapi.h"
#include "jsfriendapi.h"

#include "ProtocolIAP.h"
#include "ProtocolAnalytics.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"

#ifndef CCLOGINFO
#define CCLOGINFO(...)      
#endif

using namespace cocos2d::plugin;

namespace pluginx {

// to native
bool jsval_to_int32( JSContext *cx, JS::HandleValue vp, int32_t *ret );
bool jsval_to_uint32( JSContext *cx, JS::HandleValue vp, uint32_t *ret );
bool jsval_to_uint16( JSContext *cx, JS::HandleValue vp, uint16_t *ret );
bool jsval_to_long(JSContext *cx, JS::HandleValue v, long* ret);
bool jsval_to_long_long(JSContext *cx, JS::HandleValue v, long long* ret);
bool jsval_to_std_string(JSContext *cx, JS::HandleValue v, std::string* ret);
bool jsval_to_TProductInfo(JSContext *cx, JS::HandleValue v, TProductInfo* ret);
bool jsval_to_TIAPDeveloperInfo(JSContext *cx, JS::HandleValue v, TIAPDeveloperInfo* ret);
bool jsval_to_TAdsDeveloperInfo(JSContext *cx, JS::HandleValue v, TAdsDeveloperInfo* ret);
bool jsval_to_TAdsInfo(JSContext *cx, JS::HandleValue v, TAdsInfo* ret);
bool jsval_to_TShareDeveloperInfo(JSContext *cx, JS::HandleValue v, TShareDeveloperInfo* ret);
bool jsval_to_TShareInfo(JSContext *cx, JS::HandleValue v, TShareInfo* ret);
bool jsval_to_TSocialDeveloperInfo(JSContext *cx, JS::HandleValue v, TSocialDeveloperInfo* ret);
bool jsval_to_TAchievementInfo(JSContext *cx, JS::HandleValue v, TAchievementInfo* ret);
bool jsval_to_TPaymentInfo(JSContext *cx, JS::HandleValue v, std::map<std::string, std::string>* ret);
bool jsval_to_TUserDeveloperInfo(JSContext *cx, JS::HandleValue v, TUserDeveloperInfo* ret);
bool jsval_to_LogEventParamMap(JSContext *cx, JS::HandleValue v, LogEventParamMap** ret);
bool jsval_to_StringMap(JSContext *cx, JS::HandleValue v, StringMap* ret);
bool jsval_to_FBInfo(JSContext *cx, JS::HandleValue v, StringMap* ret);
bool jsval_array_to_string(JSContext *cx, JS::HandleValue v, std::string* ret);
bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string, std::string>* ret);
// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval long_to_jsval(JSContext* cx, long v);
jsval std_string_to_jsval(JSContext* cx, const std::string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);
jsval TProductInfo_to_jsval(JSContext *cx, TProductInfo& ret);
jsval TProductList_to_jsval(JSContext *cx, TProductList ret);
jsval LogEventParamMap_to_jsval(JSContext *cx, LogEventParamMap*& ret);


// wraps a function and "this" object
class JSFunctionWrapper
{
public:
    JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval);
    ~JSFunctionWrapper();

    bool invoke(unsigned int argc, jsval *argv, JS::MutableHandleValue rval);
private:
    JSContext *_cx;
    JS::Heap<JSObject*> _jsthis;
    JS::Heap<jsval> _fval;
private:
    JSFunctionWrapper(const JSFunctionWrapper &);
    JSFunctionWrapper& operator=(const JSFunctionWrapper &);
};

} // namespace pluginx {

#endif /* __JS_BASIC_CONVERSIONS_H__ */
