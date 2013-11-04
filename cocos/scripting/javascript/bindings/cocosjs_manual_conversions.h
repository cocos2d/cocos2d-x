#ifndef __COCOSJS_MANUAL_CONVERSIONS_H__
#define __COCOSJS_MANUAL_CONVERSIONS_H__

#include "chipmunk.h"
#include "cocos2d.h"
#include "js_manual_conversions.h"

//#ifdef __cplusplus
//extern "C" {
//#endif
  
JSBool jsval_to_CGPoint( JSContext *cx, jsval vp, cpVect *out );
jsval CGPoint_to_jsval( JSContext *cx, cpVect p );

    
//#ifdef __cplusplus
//}
//#endif

#define cpVect_to_jsval CGPoint_to_jsval
#define jsval_to_cpVect jsval_to_CGPoint

#endif /* __COCOSJS_MANUAL_CONVERSIONS_H__ */

