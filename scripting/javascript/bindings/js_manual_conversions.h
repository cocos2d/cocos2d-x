//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "chipmunk.h"
#include "cocos2d.h"

using namespace cocos2d;
#ifdef __cplusplus
extern "C" {
#endif
  
JSBool jsval_to_opaque( JSContext *cx, jsval vp, void **out );
JSBool jsval_to_int( JSContext *cx, jsval vp, int *out);
JSBool jsval_to_long( JSContext *cx, jsval vp, long *out);
JSBool jsval_to_longlong( JSContext *cx, jsval vp, long long *out);	
	
JSBool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *out );

jsval CGPoint_to_jsval( JSContext *cx, cpVect p );

jsval int_to_jsval( JSContext *cx, int l);
jsval long_to_jsval( JSContext *cx, long l);
jsval longlong_to_jsval( JSContext *cx, long long l);
jsval opaque_to_jsval( JSContext *cx, void* opaque);
	
	
    JSBool jsval_to_cpBB( JSContext *cx, jsval vp, cpBB *ret );
    jsval cpBB_to_jsval(JSContext *cx, cpBB bb );
    
#ifdef __cplusplus
}
#endif

#define cpVect_to_jsval CGPoint_to_jsval
#define jsval_to_cpVect jsval_to_CGPoint
