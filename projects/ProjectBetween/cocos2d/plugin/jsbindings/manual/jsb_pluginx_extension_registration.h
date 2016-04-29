#ifndef __JS_EXTENSION_REGISTRATION_H__
#define __JS_EXTENSION_REGISTRATION_H__

#include "jsapi.h"
#include "jsfriendapi.h"

void register_pluginx_js_extensions(JSContext* cx, JS::HandleObject global);

#endif /* __JS_EXTENSION_REGISTRATION_H__ */
