//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//
#ifndef __JS_MANUAL_CONVERSIONS_H__
#define __JS_MANUAL_CONVERSIONS_H__

#include "jsapi.h"
#include "js_bindings_core.h"
#include "cocos2d.h"
  
extern JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
extern JSBool jsval_to_int( JSContext *cx, jsval vp, int *out);
extern JSBool jsval_to_uint( JSContext *cx, jsval vp, unsigned int *out);
extern JSBool jsval_to_long( JSContext *cx, jsval vp, long *out);
extern JSBool jsval_to_c_class( JSContext *cx, jsval vp, void **out_native, struct jsb_c_proxy_s **out_proxy);
/** converts a jsval (JS string) into a char */
extern JSBool jsval_to_charptr( JSContext *cx, jsval vp, const char **out);

extern jsval opaque_to_jsval( JSContext *cx, void* opaque);
extern jsval c_class_to_jsval( JSContext *cx, void* handle, JSObject* object, JSClass *klass, const char* class_name);
extern jsval long_to_jsval( JSContext *cx, long number );
extern jsval longlong_to_jsval( JSContext *cx, long long number );

/* Converts a char ptr into a jsval (using JS string) */
extern jsval charptr_to_jsval( JSContext *cx, const char *str);
extern JSBool JSB_jsval_typedarray_to_dataptr( JSContext *cx, jsval vp, GLsizei *count, void **data, JSArrayBufferViewType t);
extern JSBool JSB_get_arraybufferview_dataptr( JSContext *cx, jsval vp, GLsizei *count, GLvoid **data );

// some utility functions
// to native
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
JSBool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);
JSBool jsval_to_ccpoint(JSContext *cx, jsval v, cocos2d::Point* ret);
JSBool jsval_to_ccrect(JSContext *cx, jsval v, cocos2d::Rect* ret);
JSBool jsval_to_ccsize(JSContext *cx, jsval v, cocos2d::Size* ret);
JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, cocos2d::Color4B* ret);
JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, cocos2d::Color4F* ret);
JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, cocos2d::Color3B* ret);
JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, cocos2d::Point **points, int *numPoints);
JSBool jsval_to_ccarray(JSContext* cx, jsval v, cocos2d::Array** ret);
JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, cocos2d::Dictionary** ret);
JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, cocos2d::Acceleration* ret);
JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, cocos2d::Array** ret);
JSBool jsval_to_ccaffinetransform(JSContext* cx, jsval v, cocos2d::AffineTransform* ret);
JSBool jsval_to_FontDefinition( JSContext *cx, jsval vp, cocos2d::FontDefinition* ret );

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, const std::string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);
jsval ccpoint_to_jsval(JSContext* cx, const cocos2d::Point& v);
jsval ccrect_to_jsval(JSContext* cx, const cocos2d::Rect& v);
jsval ccsize_to_jsval(JSContext* cx, const cocos2d::Size& v);
jsval cccolor4b_to_jsval(JSContext* cx, const cocos2d::Color4B& v);
jsval cccolor4f_to_jsval(JSContext* cx, const cocos2d::Color4F& v);
jsval cccolor3b_to_jsval(JSContext* cx, const cocos2d::Color3B& v);
jsval ccdictionary_to_jsval(JSContext* cx, cocos2d::Dictionary *dict);
jsval ccarray_to_jsval(JSContext* cx, cocos2d::Array *arr);
jsval ccacceleration_to_jsval(JSContext* cx, const cocos2d::Acceleration& v);
jsval ccaffinetransform_to_jsval(JSContext* cx, const cocos2d::AffineTransform& t);
jsval FontDefinition_to_jsval(JSContext* cx, const cocos2d::FontDefinition& t);

JSBool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *out );
jsval CGPoint_to_jsval( JSContext *cx, cpVect p );

#define cpVect_to_jsval CGPoint_to_jsval
#define jsval_to_cpVect jsval_to_CGPoint

#endif /* __JS_MANUAL_CONVERSIONS_H__ */

