#include "jsb_pluginx_spidermonkey_specifics.h"

namespace pluginx {

js_proxy_t *_native_js_global_ht = NULL;
js_proxy_t *_js_native_global_ht = NULL;
std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;

unsigned int getHashCodeByString(const char *key)
{
    unsigned int len = strlen(key);
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++)
    {
        hash *= 16777619;
        hash ^= (unsigned int) (unsigned char) toupper(*key);
    }
    return (hash);
}

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj)
{
    js_proxy_t* p;
    JS_NEW_PROXY(p, nativeObj, jsObj);
    return p;
}

js_proxy_t* jsb_get_native_proxy(void* nativeObj)
{
    js_proxy_t* p;
    JS_GET_PROXY(p, nativeObj);
    return p;
}

js_proxy_t* jsb_get_js_proxy(JSObject* jsObj)
{
    js_proxy_t* p;
    JS_GET_NATIVE_PROXY(p, jsObj);
    return p;
}

void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy)
{
    JS_REMOVE_PROXY(nativeProxy, jsProxy);
}

void get_or_create_js_obj(JSContext* cx, JS::HandleObject obj, const std::string &name, JS::MutableHandleObject jsObj)
{
    JS::RootedValue nsval(cx);
    JS_GetProperty(cx, obj, name.c_str(), &nsval);
    if (nsval == JSVAL_VOID) {
        jsObj.set(JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        nsval = OBJECT_TO_JSVAL(jsObj);
        JS_SetProperty(cx, obj, name.c_str(), nsval);
    } else {
        jsObj.set(nsval.toObjectOrNull());
    }
}

} // namespace pluginx {

