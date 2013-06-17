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
/** converts a jsval (JS string) into a char */
extern JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **out);
/* Converts a char ptr into a jsval (using JS string) */
extern jsval charptr_to_jsval( JSContext *cx, const char *str);

extern JSBool JSB_jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval );
extern JSBool JSB_jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval);
extern JSBool JSB_jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t);
extern JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data );
extern JSBool JSB_jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval );

//#ifdef __cplusplus
//}
//#endif

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

