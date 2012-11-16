//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//
#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"
#include "js_bindings_core.h"

//#ifdef __cplusplus
//extern "C" {
//#endif
  
extern JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
extern JSBool jsval_to_int( JSContext *cx, jsval vp, int *out);
extern JSBool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *out);
extern JSBool jsval_to_long( JSContext *cx, jsval vp, long *out);
extern JSBool jsval_to_longlong( JSContext *cx, jsval vp, long long *out);	
extern jsval opaque_to_jsval( JSContext *cx, void* opaque);
extern jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name);
extern JSBool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy);
extern jsval int_to_jsval( JSContext *cx, int number );
extern jsval uint_to_jsval( JSContext *cx, unsigned int number );
extern jsval long_to_jsval( JSContext *cx, long number );
extern jsval longlong_to_jsval( JSContext *cx, long long number );


//#ifdef __cplusplus
//}
//#endif

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

