#include <napi/native_api.h>
#include <string>

class NapiValueConverter {
public:
    template<typename ReturnType>
    static bool ToCppValue(napi_env env, napi_value value, ReturnType& result);

    static napi_value ToNapiValue(napi_env env, int32_t value);
    static napi_value ToNapiValue(napi_env env, int64_t value);
    static napi_value ToNapiValue(napi_env env, double value);
    static napi_value ToNapiValue(napi_env env, bool value);
    static napi_value ToNapiValue(napi_env env, const char* value);
    static napi_value ToNapiValue(napi_env env, std::string value);

};
