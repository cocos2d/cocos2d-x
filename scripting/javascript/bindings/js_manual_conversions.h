//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//
#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"

//#ifdef __cplusplus
//extern "C" {
//#endif
  
extern JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
extern JSBool jsval_to_int( JSContext *cx, jsval vp, int *out);
extern JSBool jsval_to_long( JSContext *cx, jsval vp, long *out);
extern JSBool jsval_to_longlong( JSContext *cx, jsval vp, long long *out);	
extern jsval int_to_jsval( JSContext *cx, int l);
extern jsval long_to_jsval( JSContext *cx, long l);
extern jsval longlong_to_jsval( JSContext *cx, long long l);
extern jsval opaque_to_jsval( JSContext *cx, void* opaque);

//#ifdef __cplusplus
//}
//#endif

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

