//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "jsfriendapi.h"
#include "ScriptingCore.h"
#include "cocosjs_manual_conversions.h"
#include "js_bindings_config.h"
#include "js_bindings_chipmunk_functions.hpp"

// Arguments: cpArbiter*
// Ret value: int
JSBool JSPROXY_cpArbiterGetCount(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	int ret_val;

	ret_val = cpArbiterGetCount((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpArbiter*, int
// Ret value: cpFloat
JSBool JSPROXY_cpArbiterGetDepth(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpArbiterGetDepth((cpArbiter*)arg0 , (int)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpFloat
JSBool JSPROXY_cpArbiterGetElasticity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpArbiterGetElasticity((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpFloat
JSBool JSPROXY_cpArbiterGetFriction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpArbiterGetFriction((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpArbiter*, int
// Ret value: cpVect
JSBool JSPROXY_cpArbiterGetNormal(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpArbiterGetNormal((cpArbiter*)arg0 , (int)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpArbiter*, int
// Ret value: cpVect
JSBool JSPROXY_cpArbiterGetPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpArbiterGetPoint((cpArbiter*)arg0 , (int)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpVect
JSBool JSPROXY_cpArbiterGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpArbiterGetSurfaceVelocity((cpArbiter*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: void
JSBool JSPROXY_cpArbiterIgnore(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpArbiterIgnore((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpBool
JSBool JSPROXY_cpArbiterIsFirstContact(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpArbiterIsFirstContact((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpArbiter*, cpFloat
// Ret value: void
JSBool JSPROXY_cpArbiterSetElasticity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpArbiterSetElasticity((cpArbiter*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpArbiter*, cpFloat
// Ret value: void
JSBool JSPROXY_cpArbiterSetFriction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpArbiterSetFriction((cpArbiter*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpArbiter*, cpVect
// Ret value: void
JSBool JSPROXY_cpArbiterSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpArbiterSetSurfaceVelocity((cpArbiter*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpVect
JSBool JSPROXY_cpArbiterTotalImpulse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpArbiterTotalImpulse((cpArbiter*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpVect
JSBool JSPROXY_cpArbiterTotalImpulseWithFriction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpArbiterTotalImpulseWithFriction((cpArbiter*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpArbiter*
// Ret value: cpFloat
JSBool JSPROXY_cpArbiterTotalKE(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpArbiter* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpArbiterTotalKE((cpArbiter*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpAreaForCircle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpAreaForCircle((cpFloat)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpAreaForSegment(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpAreaForSegment((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB
// Ret value: cpFloat
JSBool JSPROXY_cpBBArea(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBBArea((cpBB)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBBClampVect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBBClampVect((cpBB)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBB, cpBB
// Ret value: cpBool
JSBool JSPROXY_cpBBContainsBB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpBB arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBBContainsBB((cpBB)arg0 , (cpBB)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpVect
// Ret value: cpBool
JSBool JSPROXY_cpBBContainsVect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBBContainsVect((cpBB)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpVect
// Ret value: cpBB
JSBool JSPROXY_cpBBExpand(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpBBExpand((cpBB)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBB, cpBB
// Ret value: cpBool
JSBool JSPROXY_cpBBIntersects(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpBB arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBBIntersects((cpBB)arg0 , (cpBB)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpVect, cpVect
// Ret value: cpBool
JSBool JSPROXY_cpBBIntersectsSegment(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBBIntersectsSegment((cpBB)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpBB
// Ret value: cpBB
JSBool JSPROXY_cpBBMerge(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpBB arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpBBMerge((cpBB)arg0 , (cpBB)arg1  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBB, cpBB
// Ret value: cpFloat
JSBool JSPROXY_cpBBMergedArea(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpBB arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBBMergedArea((cpBB)arg0 , (cpBB)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat, cpFloat
// Ret value: cpBB
JSBool JSPROXY_cpBBNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; double arg3; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpBBNew((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2 , (cpFloat)arg3  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpFloat
// Ret value: cpBB
JSBool JSPROXY_cpBBNewForCircle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; double arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpBBNewForCircle((cpVect)arg0 , (cpFloat)arg1  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBB, cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpBBSegmentQuery(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBBSegmentQuery((cpBB)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBB, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBBWrapVect(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBB arg0; cpVect arg1; 

	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBBWrapVect((cpBB)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void
JSBool JSPROXY_cpBodyActivate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpBodyActivate((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpShape*
// Ret value: void
JSBool JSPROXY_cpBodyActivateStatic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodyActivateStatic((cpBody*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: 
// Ret value: cpBody*
JSBool JSPROXY_cpBodyAlloc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
	cpBody* ret_val;

	ret_val = cpBodyAlloc( );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect, cpVect
// Ret value: void
JSBool JSPROXY_cpBodyApplyForce(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;

	cpBodyApplyForce((cpBody*)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect, cpVect
// Ret value: void
JSBool JSPROXY_cpBodyApplyImpulse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;

	cpBodyApplyImpulse((cpBody*)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void
JSBool JSPROXY_cpBodyDestroy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpBodyDestroy((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void
JSBool JSPROXY_cpBodyFree(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpBodyFree((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetAngVel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetAngVel((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetAngVelLimit((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetAngle((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetForce(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetForce((cpBody*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetMass(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetMass((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetMoment(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetMoment((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetPos(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetPos((cpBody*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetRot(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetRot((cpBody*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpSpace*
JSBool JSPROXY_cpBodyGetSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpSpace* ret_val;

	ret_val = cpBodyGetSpace((cpBody*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetTorque(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetTorque((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetVel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetVel((cpBody*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetVelAtLocalPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetVelAtLocalPoint((cpBody*)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBodyGetVelAtWorldPoint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyGetVelAtWorldPoint((cpBody*)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyGetVelLimit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyGetVelLimit((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat, cpFloat
// Ret value: cpBody*
JSBool JSPROXY_cpBodyInit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; double arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpBodyInit((cpBody*)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpBody*
JSBool JSPROXY_cpBodyInitStatic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpBodyInitStatic((cpBody*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpBool
JSBool JSPROXY_cpBodyIsRogue(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBodyIsRogue((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpBool
JSBool JSPROXY_cpBodyIsSleeping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBodyIsSleeping((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpBool
JSBool JSPROXY_cpBodyIsStatic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpBodyIsStatic((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: cpFloat
JSBool JSPROXY_cpBodyKineticEnergy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpBodyKineticEnergy((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBodyLocal2World(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyLocal2World((cpBody*)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat
// Ret value: cpBody*
JSBool JSPROXY_cpBodyNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpBodyNew((cpFloat)arg0 , (cpFloat)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: 
// Ret value: cpBody*
JSBool JSPROXY_cpBodyNewStatic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
	cpBody* ret_val;

	ret_val = cpBodyNewStatic( );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void
JSBool JSPROXY_cpBodyResetForces(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpBodyResetForces((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetAngVel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetAngVel((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetAngVelLimit((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetAngle((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: void
JSBool JSPROXY_cpBodySetForce(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetForce((cpBody*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetMass(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetMass((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetMoment(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetMoment((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: void
JSBool JSPROXY_cpBodySetPos(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetPos((cpBody*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetTorque(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetTorque((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: void
JSBool JSPROXY_cpBodySetVel(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetVel((cpBody*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodySetVelLimit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySetVelLimit((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void
JSBool JSPROXY_cpBodySleep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpBodySleep((cpBody*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*
// Ret value: void
JSBool JSPROXY_cpBodySleepWithGroup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodySleepWithGroup((cpBody*)arg0 , (cpBody*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodyUpdatePosition(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpBodyUpdatePosition((cpBody*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect, cpFloat, cpFloat
// Ret value: void
JSBool JSPROXY_cpBodyUpdateVelocity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; double arg2; double arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;

	cpBodyUpdateVelocity((cpBody*)arg0 , (cpVect)arg1 , (cpFloat)arg2 , (cpFloat)arg3  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpBodyWorld2Local(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpBodyWorld2Local((cpBody*)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat, cpFloat
// Ret value: cpShape*
JSBool JSPROXY_cpBoxShapeNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; double arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpBoxShapeNew((cpBody*)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*, cpBB
// Ret value: cpShape*
JSBool JSPROXY_cpBoxShapeNew2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBB arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpBoxShapeNew2((cpBody*)arg0 , (cpBB)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpVect
JSBool JSPROXY_cpCircleShapeGetOffset(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpCircleShapeGetOffset((cpShape*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpFloat
JSBool JSPROXY_cpCircleShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpCircleShapeGetRadius((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpFloat, cpVect
// Ret value: cpShape*
JSBool JSPROXY_cpCircleShapeNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; double arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpCircleShapeNew((cpBody*)arg0 , (cpFloat)arg1 , (cpVect)arg2  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: void
JSBool JSPROXY_cpConstraintActivateBodies(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpConstraintActivateBodies((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: void
JSBool JSPROXY_cpConstraintDestroy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpConstraintDestroy((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: void
JSBool JSPROXY_cpConstraintFree(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpConstraintFree((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpBody*
JSBool JSPROXY_cpConstraintGetA(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpConstraintGetA((cpConstraint*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpBody*
JSBool JSPROXY_cpConstraintGetB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpConstraintGetB((cpConstraint*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpConstraintGetErrorBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpConstraintGetErrorBias((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpConstraintGetImpulse(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpConstraintGetImpulse((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpConstraintGetMaxBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpConstraintGetMaxBias((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpConstraintGetMaxForce(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpConstraintGetMaxForce((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpSpace*
JSBool JSPROXY_cpConstraintGetSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpSpace* ret_val;

	ret_val = cpConstraintGetSpace((cpConstraint*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpConstraintSetErrorBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpConstraintSetErrorBias((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpConstraintSetMaxBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpConstraintSetMaxBias((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpConstraintSetMaxForce(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpConstraintSetMaxForce((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedRotarySpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedRotarySpringGetDamping((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedRotarySpringGetRestAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedRotarySpringGetRestAngle((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedRotarySpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedRotarySpringGetStiffness((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpFloat, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpDampedRotarySpringNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 5, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; double arg2; double arg3; double arg4; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg4 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpDampedRotarySpringNew((cpBody*)arg0 , (cpBody*)arg1 , (cpFloat)arg2 , (cpFloat)arg3 , (cpFloat)arg4  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedRotarySpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedRotarySpringSetDamping((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedRotarySpringSetRestAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedRotarySpringSetRestAngle((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedRotarySpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedRotarySpringSetStiffness((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpDampedSpringGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpDampedSpringGetAnchr1((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpDampedSpringGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpDampedSpringGetAnchr2((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedSpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedSpringGetDamping((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedSpringGetRestLength(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedSpringGetRestLength((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpDampedSpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpDampedSpringGetStiffness((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect, cpVect, cpFloat, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpDampedSpringNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 7, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; cpVect arg3; double arg4; double arg5; double arg6; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg4 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg5 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg6 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpDampedSpringNew((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2 , (cpVect)arg3 , (cpFloat)arg4 , (cpFloat)arg5 , (cpFloat)arg6  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpDampedSpringSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedSpringSetAnchr1((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpDampedSpringSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedSpringSetAnchr2((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedSpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedSpringSetDamping((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedSpringSetRestLength(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedSpringSetRestLength((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpDampedSpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpDampedSpringSetStiffness((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpGearJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpGearJointGetPhase((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpGearJointGetRatio(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpGearJointGetRatio((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpGearJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; double arg2; double arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpGearJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpFloat)arg2 , (cpFloat)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpGearJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpGearJointSetPhase((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpGearJointSetRatio(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpGearJointSetRatio((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpGrooveJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpGrooveJointGetAnchr2((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpGrooveJointGetGrooveA(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpGrooveJointGetGrooveA((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpGrooveJointGetGrooveB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpGrooveJointGetGrooveB((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect, cpVect, cpVect
// Ret value: cpConstraint*
JSBool JSPROXY_cpGrooveJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 5, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; cpVect arg3; cpVect arg4; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg4 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpGrooveJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2 , (cpVect)arg3 , (cpVect)arg4  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpGrooveJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpGrooveJointSetAnchr2((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpGrooveJointSetGrooveA(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpGrooveJointSetGrooveA((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpGrooveJointSetGrooveB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpGrooveJointSetGrooveB((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: 
// Ret value: void
JSBool JSPROXY_cpInitChipmunk(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );

	cpInitChipmunk( );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpMomentForBox(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpMomentForBox((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpBB
// Ret value: cpFloat
JSBool JSPROXY_cpMomentForBox2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; cpBB arg1; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= jsval_to_cpBB( cx, *argvp++, (cpBB*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpMomentForBox2((cpFloat)arg0 , (cpBB)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpMomentForCircle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; cpVect arg3; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpMomentForCircle((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2 , (cpVect)arg3  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpMomentForSegment(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; cpVect arg1; cpVect arg2; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpMomentForSegment((cpFloat)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpPinJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpPinJointGetAnchr1((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpPinJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpPinJointGetAnchr2((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpPinJointGetDist(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpPinJointGetDist((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect, cpVect
// Ret value: cpConstraint*
JSBool JSPROXY_cpPinJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; cpVect arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpPinJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2 , (cpVect)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpPinJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpPinJointSetAnchr1((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpPinJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpPinJointSetAnchr2((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpPinJointSetDist(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpPinJointSetDist((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpPivotJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpPivotJointGetAnchr1((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpPivotJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpPivotJointGetAnchr2((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect
// Ret value: cpConstraint*
JSBool JSPROXY_cpPivotJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpPivotJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect, cpVect
// Ret value: cpConstraint*
JSBool JSPROXY_cpPivotJointNew2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; cpVect arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpPivotJointNew2((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2 , (cpVect)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpPivotJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpPivotJointSetAnchr1((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpPivotJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpPivotJointSetAnchr2((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: int
JSBool JSPROXY_cpPolyShapeGetNumVerts(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	int ret_val;

	ret_val = cpPolyShapeGetNumVerts((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*, int
// Ret value: cpVect
JSBool JSPROXY_cpPolyShapeGetVert(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpPolyShapeGetVert((cpShape*)arg0 , (int)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpRatchetJointGetAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpRatchetJointGetAngle((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpRatchetJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpRatchetJointGetPhase((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpRatchetJointGetRatchet(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpRatchetJointGetRatchet((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpRatchetJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; double arg2; double arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpRatchetJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpFloat)arg2 , (cpFloat)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpRatchetJointSetAngle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpRatchetJointSetAngle((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpRatchetJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpRatchetJointSetPhase((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpRatchetJointSetRatchet(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpRatchetJointSetRatchet((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: 
// Ret value: void
JSBool JSPROXY_cpResetShapeIdCounter(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );

	cpResetShapeIdCounter( );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpRotaryLimitJointGetMax(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpRotaryLimitJointGetMax((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpRotaryLimitJointGetMin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpRotaryLimitJointGetMin((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpRotaryLimitJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; double arg2; double arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpRotaryLimitJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpFloat)arg2 , (cpFloat)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpRotaryLimitJointSetMax(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpRotaryLimitJointSetMax((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpRotaryLimitJointSetMin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpRotaryLimitJointSetMin((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpVect
JSBool JSPROXY_cpSegmentShapeGetA(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSegmentShapeGetA((cpShape*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpVect
JSBool JSPROXY_cpSegmentShapeGetB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSegmentShapeGetB((cpShape*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpVect
JSBool JSPROXY_cpSegmentShapeGetNormal(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSegmentShapeGetNormal((cpShape*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpFloat
JSBool JSPROXY_cpSegmentShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSegmentShapeGetRadius((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpVect, cpVect, cpFloat
// Ret value: cpShape*
JSBool JSPROXY_cpSegmentShapeNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpVect arg1; cpVect arg2; double arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg3 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpSegmentShapeNew((cpBody*)arg0 , (cpVect)arg1 , (cpVect)arg2 , (cpFloat)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpShape*, cpVect, cpVect
// Ret value: void
JSBool JSPROXY_cpSegmentShapeSetNeighbors(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;

	cpSegmentShapeSetNeighbors((cpShape*)arg0 , (cpVect)arg1 , (cpVect)arg2  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpBB
JSBool JSPROXY_cpShapeCacheBB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpShapeCacheBB((cpShape*)arg0  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: void
JSBool JSPROXY_cpShapeDestroy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpShapeDestroy((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: void
JSBool JSPROXY_cpShapeFree(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpShapeFree((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpBB
JSBool JSPROXY_cpShapeGetBB(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpShapeGetBB((cpShape*)arg0  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpBody*
JSBool JSPROXY_cpShapeGetBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpShapeGetBody((cpShape*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpCollisionType
JSBool JSPROXY_cpShapeGetCollisionType(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpCollisionType ret_val;

	ret_val = cpShapeGetCollisionType((cpShape*)arg0  );

	jsval ret_jsval = int_to_jsval( cx, (cpCollisionType)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpFloat
JSBool JSPROXY_cpShapeGetElasticity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpShapeGetElasticity((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpFloat
JSBool JSPROXY_cpShapeGetFriction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpShapeGetFriction((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpGroup
JSBool JSPROXY_cpShapeGetGroup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpGroup ret_val;

	ret_val = cpShapeGetGroup((cpShape*)arg0  );

	jsval ret_jsval = int_to_jsval( cx, (cpGroup)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpLayers
JSBool JSPROXY_cpShapeGetLayers(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpLayers ret_val;

	ret_val = cpShapeGetLayers((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpBool
JSBool JSPROXY_cpShapeGetSensor(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpShapeGetSensor((cpShape*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpSpace*
JSBool JSPROXY_cpShapeGetSpace(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpSpace* ret_val;

	ret_val = cpShapeGetSpace((cpShape*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpVect
JSBool JSPROXY_cpShapeGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpShapeGetSurfaceVelocity((cpShape*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpShape*, cpVect
// Ret value: cpBool
JSBool JSPROXY_cpShapePointQuery(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpShapePointQuery((cpShape*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpShape*, cpBody*
// Ret value: void
JSBool JSPROXY_cpShapeSetBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetBody((cpShape*)arg0 , (cpBody*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpCollisionType
// Ret value: void
JSBool JSPROXY_cpShapeSetCollisionType(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpCollisionType arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_int( cx, *argvp++, (int*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetCollisionType((cpShape*)arg0 , (cpCollisionType)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpFloat
// Ret value: void
JSBool JSPROXY_cpShapeSetElasticity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetElasticity((cpShape*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpFloat
// Ret value: void
JSBool JSPROXY_cpShapeSetFriction(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetFriction((cpShape*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpGroup
// Ret value: void
JSBool JSPROXY_cpShapeSetGroup(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpGroup arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_int( cx, *argvp++, (int*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetGroup((cpShape*)arg0 , (cpGroup)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpLayers
// Ret value: void
JSBool JSPROXY_cpShapeSetLayers(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; uint32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAUint32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetLayers((cpShape*)arg0 , (cpLayers)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpBool
// Ret value: void
JSBool JSPROXY_cpShapeSetSensor(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetSensor((cpShape*)arg0 , (cpBool)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpVect
// Ret value: void
JSBool JSPROXY_cpShapeSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpShapeSetSurfaceVelocity((cpShape*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*, cpVect, cpVect
// Ret value: cpBB
JSBool JSPROXY_cpShapeUpdate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg0; cpVect arg1; cpVect arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	if( ! ok ) return JS_FALSE;
	cpBB ret_val;

	ret_val = cpShapeUpdate((cpShape*)arg0 , (cpVect)arg1 , (cpVect)arg2  );

	jsval ret_jsval = cpBB_to_jsval( cx, (cpBB)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpSimpleMotorGetRate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSimpleMotorGetRate((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpSimpleMotorNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; double arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpSimpleMotorNew((cpBody*)arg0 , (cpBody*)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSimpleMotorSetRate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSimpleMotorSetRate((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpSlideJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSlideJointGetAnchr1((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpVect
JSBool JSPROXY_cpSlideJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSlideJointGetAnchr2((cpConstraint*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpSlideJointGetMax(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSlideJointGetMax((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpFloat
JSBool JSPROXY_cpSlideJointGetMin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSlideJointGetMin((cpConstraint*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*, cpBody*, cpVect, cpVect, cpFloat, cpFloat
// Ret value: cpConstraint*
JSBool JSPROXY_cpSlideJointNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 6, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg0; cpBody* arg1; cpVect arg2; cpVect arg3; double arg4; double arg5; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg2 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg3 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg4 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg5 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpSlideJointNew((cpBody*)arg0 , (cpBody*)arg1 , (cpVect)arg2 , (cpVect)arg3 , (cpFloat)arg4 , (cpFloat)arg5  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpSlideJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSlideJointSetAnchr1((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpVect
// Ret value: void
JSBool JSPROXY_cpSlideJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSlideJointSetAnchr2((cpConstraint*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSlideJointSetMax(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSlideJointSetMax((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSlideJointSetMin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSlideJointSetMin((cpConstraint*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: void
JSBool JSPROXY_cpSpaceActivateShapesTouchingShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceActivateShapesTouchingShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpBody*
// Ret value: cpBody*
JSBool JSPROXY_cpSpaceAddBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpSpaceAddBody((cpSpace*)arg0 , (cpBody*)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpConstraint*
// Ret value: cpConstraint*
JSBool JSPROXY_cpSpaceAddConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpConstraint* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpConstraint* ret_val;

	ret_val = cpSpaceAddConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: cpShape*
JSBool JSPROXY_cpSpaceAddShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpSpaceAddShape((cpSpace*)arg0 , (cpShape*)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: cpShape*
JSBool JSPROXY_cpSpaceAddStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpSpaceAddStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: 
// Ret value: cpSpace*
JSBool JSPROXY_cpSpaceAlloc(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
	cpSpace* ret_val;

	ret_val = cpSpaceAlloc( );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpBody*
// Ret value: cpBool
JSBool JSPROXY_cpSpaceContainsBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpSpaceContainsBody((cpSpace*)arg0 , (cpBody*)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*, cpConstraint*
// Ret value: cpBool
JSBool JSPROXY_cpSpaceContainsConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpConstraint* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpSpaceContainsConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: cpBool
JSBool JSPROXY_cpSpaceContainsShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpSpaceContainsShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: void
JSBool JSPROXY_cpSpaceDestroy(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpSpaceDestroy((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: void
JSBool JSPROXY_cpSpaceFree(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpSpaceFree((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetCollisionBias((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpTimestamp
JSBool JSPROXY_cpSpaceGetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpTimestamp ret_val;

	ret_val = cpSpaceGetCollisionPersistence((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetCollisionSlop((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetCurrentTimeStep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetCurrentTimeStep((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetDamping((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpBool
JSBool JSPROXY_cpSpaceGetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpSpaceGetEnableContactGraph((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpVect
JSBool JSPROXY_cpSpaceGetGravity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpSpaceGetGravity((cpSpace*)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetIdleSpeedThreshold((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: int
JSBool JSPROXY_cpSpaceGetIterations(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	int ret_val;

	ret_val = cpSpaceGetIterations((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpFloat
JSBool JSPROXY_cpSpaceGetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpSpaceGetSleepTimeThreshold((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpBody*
JSBool JSPROXY_cpSpaceGetStaticBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBody* ret_val;

	ret_val = cpSpaceGetStaticBody((cpSpace*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpSpace*
JSBool JSPROXY_cpSpaceInit(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpSpace* ret_val;

	ret_val = cpSpaceInit((cpSpace*)arg0  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: cpBool
JSBool JSPROXY_cpSpaceIsLocked(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpSpaceIsLocked((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: 
// Ret value: cpSpace*
JSBool JSPROXY_cpSpaceNew(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 0, "Invalid number of arguments" );
	cpSpace* ret_val;

	ret_val = cpSpaceNew( );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpVect, cpLayers, cpGroup
// Ret value: cpShape*
JSBool JSPROXY_cpSpacePointQueryFirst(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 4, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpVect arg1; uint32_t arg2; cpGroup arg3; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToECMAUint32( cx, *argvp++, &arg2 );
	ok &= jsval_to_int( cx, *argvp++, (int*) &arg3 );
	if( ! ok ) return JS_FALSE;
	cpShape* ret_val;

	ret_val = cpSpacePointQueryFirst((cpSpace*)arg0 , (cpVect)arg1 , (cpLayers)arg2 , (cpGroup)arg3  );

	jsval ret_jsval = opaque_to_jsval( cx, ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: void
JSBool JSPROXY_cpSpaceReindexShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceReindexShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpBody*
// Ret value: void
JSBool JSPROXY_cpSpaceReindexShapesForBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceReindexShapesForBody((cpSpace*)arg0 , (cpBody*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*
// Ret value: void
JSBool JSPROXY_cpSpaceReindexStatic(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;

	cpSpaceReindexStatic((cpSpace*)arg0  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpBody*
// Ret value: void
JSBool JSPROXY_cpSpaceRemoveBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpBody* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceRemoveBody((cpSpace*)arg0 , (cpBody*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpConstraint*
// Ret value: void
JSBool JSPROXY_cpSpaceRemoveConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpConstraint* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceRemoveConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: void
JSBool JSPROXY_cpSpaceRemoveShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceRemoveShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpShape*
// Ret value: void
JSBool JSPROXY_cpSpaceRemoveStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
//	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpShape* arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceRemoveStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceSetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetCollisionBias((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpTimestamp
// Ret value: void
JSBool JSPROXY_cpSpaceSetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; uint32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAUint32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetCollisionPersistence((cpSpace*)arg0 , (cpTimestamp)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceSetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetCollisionSlop((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceSetDamping(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetDamping((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpBool
// Ret value: void
JSBool JSPROXY_cpSpaceSetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetEnableContactGraph((cpSpace*)arg0 , (cpBool)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpVect
// Ret value: void
JSBool JSPROXY_cpSpaceSetGravity(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; cpVect arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetGravity((cpSpace*)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceSetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetIdleSpeedThreshold((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, int
// Ret value: void
JSBool JSPROXY_cpSpaceSetIterations(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; int32_t arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetIterations((cpSpace*)arg0 , (int)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceSetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceSetSleepTimeThreshold((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat
// Ret value: void
JSBool JSPROXY_cpSpaceStep(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;

	cpSpaceStep((cpSpace*)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpSpace*, cpFloat, int
// Ret value: void
JSBool JSPROXY_cpSpaceUseSpatialHash(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpSpace* arg0; double arg1; int32_t arg2; 

	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToECMAInt32( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;

	cpSpaceUseSpatialHash((cpSpace*)arg0 , (cpFloat)arg1 , (int)arg2  );
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpfabs(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpfabs((cpFloat)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpfclamp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpfclamp((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpfclamp01(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpfclamp01((cpFloat)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpflerp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpflerp((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpflerpconst(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; double arg2; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpflerpconst((cpFloat)arg0 , (cpFloat)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpfmax(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpfmax((cpFloat)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat, cpFloat
// Ret value: cpFloat
JSBool JSPROXY_cpfmin(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpfmin((cpFloat)arg0 , (cpFloat)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvadd(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvadd((cpVect)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}


// Arguments: cpFloat, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpv(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; double arg1;
    
	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;
    
	ret_val = cpv((cpFloat)arg0 , (cpFloat)arg1  );
    
	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);
    
	return JS_TRUE;
}

// Arguments: cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvclamp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; double arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvclamp((cpVect)arg0 , (cpFloat)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvcross(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvcross((cpVect)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvdist(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvdist((cpVect)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvdistsq(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvdistsq((cpVect)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvdot(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvdot((cpVect)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpBool
JSBool JSPROXY_cpveql(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpveql((cpVect)arg0 , (cpVect)arg1  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvforangle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double arg0; 

	ok &= JS_ValueToNumber( cx, *argvp++, &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvforangle((cpFloat)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvlength(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvlength((cpVect)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvlengthsq(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvlengthsq((cpVect)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvlerp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvlerp((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvlerpconst(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvlerpconst((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvmult(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; double arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvmult((cpVect)arg0 , (cpFloat)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpBool
JSBool JSPROXY_cpvnear(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpBool ret_val;

	ret_val = cpvnear((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );
	JS_SET_RVAL(cx, vp, INT_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvneg(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvneg((cpVect)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvnormalize(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvnormalize((cpVect)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvnormalize_safe(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvnormalize_safe((cpVect)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvperp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvperp((cpVect)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvproject(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvproject((cpVect)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvrotate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvrotate((cpVect)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvrperp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvrperp((cpVect)arg0  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvslerp(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvslerp((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect, cpFloat
// Ret value: cpVect
JSBool JSPROXY_cpvslerpconst(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 3, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; double arg2; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	ok &= JS_ValueToNumber( cx, *argvp++, &arg2 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvslerpconst((cpVect)arg0 , (cpVect)arg1 , (cpFloat)arg2  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvsub(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvsub((cpVect)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}

// Arguments: cpVect
// Ret value: cpFloat
JSBool JSPROXY_cpvtoangle(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 1, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	if( ! ok ) return JS_FALSE;
	cpFloat ret_val;

	ret_val = cpvtoangle((cpVect)arg0  );
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpVect, cpVect
// Ret value: cpVect
JSBool JSPROXY_cpvunrotate(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION( argc == 2, "Invalid number of arguments" );
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect arg0; cpVect arg1; 

	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg0 );
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &arg1 );
	if( ! ok ) return JS_FALSE;
	cpVect ret_val;

	ret_val = cpvunrotate((cpVect)arg0 , (cpVect)arg1  );

	jsval ret_jsval = cpVect_to_jsval( cx, (cpVect)ret_val );
	JS_SET_RVAL(cx, vp, ret_jsval);

	return JS_TRUE;
}




