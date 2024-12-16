#ifndef _WEB_VIEW_NAPI_H
#define _WEB_VIEW_NAPI_H

#include <string>
#include <napi/native_api.h>

class WebViewNapi {
public:
    static napi_value shouldStartLoading(napi_env env, napi_callback_info info);
    static napi_value finishLoading(napi_env env, napi_callback_info info);
    static napi_value failLoading(napi_env env, napi_callback_info info);
    static napi_value jsCallback(napi_env env, napi_callback_info info);
};

#endif //_WEB_VIEW_NAPI_H