//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//


#ifndef __JS_BINDINGS_CONFIG_H
#define __JS_BINDINGS_CONFIG_H


/** @def JSB_ASSERT_ON_FAIL
 */
#ifndef JSB_ASSERT_ON_FAIL
#define JSB_ASSERT_ON_FAIL 0
#endif


#if JSB_ASSERT_ON_FAIL
#define JSB_PRECONDITION( condition, error_msg) do { assert( condition, error_msg ) } while(0)
#else
#define JSB_PRECONDITION(condition, error_msg) do {							\
	if( ! (condition) ) {														\
		CCLOG("jsb: ERROR in %s: %s", __FUNCTION__, error_msg);				\
		return JS_FALSE;														\
	}																			\
} while(0)
#endif

#endif // __JS_BINDINGS_CONFIG_H
