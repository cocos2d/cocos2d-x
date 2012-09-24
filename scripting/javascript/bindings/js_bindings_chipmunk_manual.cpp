//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//


#include "js_bindings_chipmunk_manual.hpp"
#include "jsapi.h"
#include "cocosjs_manual_conversions.h"
#include "uthash.h"
#include "ccConfig.h"
#include "ScriptingCore.h"
#include "CCPhysicsSprite.h"

using namespace cocos2d;

#pragma mark - Collision Handler


struct collision_handler {
	cpCollisionType		typeA;
	cpCollisionType		typeB;
	jsval				begin;
	jsval				pre;
	jsval				post;
	jsval				separate;
	JSObject			*self;
	JSContext			*cx;
	unsigned long		hash_key;
	UT_hash_handle  hh;
};

// hash
struct collision_handler* collision_handler_hash = NULL;

// helper pair
static unsigned long pair_ints( unsigned long A, unsigned long B )
{
	// order is not important
  unsigned long k1 = (A < B) ? A : B;
  unsigned long k2 = (A > B) ? A : B;
	
	return (k1 + k2) * (k1 + k2 + 1) /2 + k2;
}

static cpBool myCollisionBegin(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	jsval args[2];
    
    handler->cx = ScriptingCore::getInstance()->getGlobalContext();
    
	args[0] = opaque_to_jsval( handler->cx, arb);
	args[1] = opaque_to_jsval( handler->cx, space );
	
	jsval rval;
	JS_CallFunctionValue(handler->cx , handler->self, handler->begin, 2, args, &rval);
	
	if( JSVAL_IS_BOOLEAN(rval) ) {
		JSBool ret = JSVAL_TO_BOOLEAN(rval);
		return (cpBool)ret;
	}
	return cpTrue;	
}

static cpBool myCollisionPre(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	args[0] = opaque_to_jsval( handler->cx, arb);
	args[1] = opaque_to_jsval( handler->cx, space );
	
	jsval rval;
	JS_CallFunctionValue( handler->cx, handler->self, handler->pre, 2, args, &rval);
	
	if( JSVAL_IS_BOOLEAN(rval) ) {
		JSBool ret = JSVAL_TO_BOOLEAN(rval);
		return (cpBool)ret;
	}
	return cpTrue;	
}

static void myCollisionPost(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	args[0] = opaque_to_jsval( handler->cx, arb);
	args[1] = opaque_to_jsval( handler->cx, space );
	
	jsval ignore;
	JS_CallFunctionValue( handler->cx, handler->self, handler->post, 2, args, &ignore);
}

static void myCollisionSeparate(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	args[0] = opaque_to_jsval( handler->cx, arb);
	args[1] = opaque_to_jsval( handler->cx, space );
	
	jsval ignore;
	JS_CallFunctionValue( handler->cx, handler->self, handler->separate, 2, args, &ignore);
}

JSBool JSPROXY_cpSpaceAddCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	if( argc != 8 )
		return JS_FALSE;

	jsval *argvp = JS_ARGV(cx,vp);

	struct collision_handler *handler;
	handler = (struct collision_handler *) malloc(sizeof (struct collision_handler));
	if( ! handler )
		return JS_FALSE;
	
	JSBool ok = JS_TRUE;

	// args
	cpSpace *space;
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&space);
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeB );
	

	ok &= JS_ValueToObject(cx, *argvp++, &handler->self );

	handler->begin =  *argvp++;
	handler->pre = *argvp++;
	handler->post = *argvp++;
	handler->separate = *argvp++;

	if( ! ok )
		return JS_FALSE;
		
	handler->cx = cx;
	
	cpSpaceAddCollisionHandler(space, handler->typeA, handler->typeB,
							   JSVAL_IS_NULL(handler->begin) ? NULL : &myCollisionBegin,
							   JSVAL_IS_NULL(handler->pre) ? NULL : &myCollisionPre,
							   JSVAL_IS_NULL(handler->post) ? NULL : &myCollisionPost,
							   JSVAL_IS_NULL(handler->separate) ? NULL : &myCollisionSeparate,
							   handler );
	

	//
	// Already added ? If so, remove it.
	// Then add new entry
	//
	struct collision_handler *hashElement = NULL;
	unsigned long paired_key = pair_ints(handler->typeA, handler->typeB );
	HASH_FIND_INT(collision_handler_hash, &paired_key, hashElement);
    if( hashElement ) {
		HASH_DEL( collision_handler_hash, hashElement );
		free( hashElement );
	}

	handler->hash_key = paired_key;
	HASH_ADD_INT( collision_handler_hash, hash_key, handler );

		
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

JSBool JSPROXY_cpSpaceRemoveCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	if( argc != 3 )
		return  JS_FALSE;
	
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	
	cpSpace* space;
	cpCollisionType typeA;
	cpCollisionType typeB;
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&space);
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeB );
	
	if( ! ok )
		return JS_FALSE;

	cpSpaceRemoveCollisionHandler(space, typeA, typeB );
	
	// Remove it
	struct collision_handler *hashElement = NULL;
	unsigned long key = pair_ints(typeA, typeB );
	HASH_FIND_INT(collision_handler_hash, &key, hashElement);
    if( hashElement ) {
		HASH_DEL( collision_handler_hash, hashElement );
		free( hashElement );
	}
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

#pragma mark - Arbiter

JSBool JSPROXY_cpArbiterGetBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
	if( argc != 1 )
		return  JS_FALSE;
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if(!jsval_to_opaque( cx, *argvp++, (void**) &arbiter ) )
		return JS_FALSE;

	cpBody *bodyA;
	cpBody *bodyB;
	cpArbiterGetBodies(arbiter, &bodyA, &bodyB);
	jsval valA = opaque_to_jsval(cx, bodyA);
	jsval valB = opaque_to_jsval(cx, bodyB);
	
	JSObject *jsobj = JS_NewArrayObject(cx, 2, NULL);
	JS_SetElement(cx, jsobj, 0, &valA);
	JS_SetElement(cx, jsobj, 1, &valB);

	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return JS_TRUE;
	
}

JSBool JSPROXY_cpArbiterGetShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
	if( argc != 1 )
		return  JS_FALSE;
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &arbiter ) )
	   return JS_FALSE;
	
	cpShape *shapeA;
	cpShape *shapeB;
	cpArbiterGetShapes(arbiter, &shapeA, &shapeB);
	jsval valA = opaque_to_jsval(cx, shapeA);
	jsval valB = opaque_to_jsval(cx, shapeB);
	
	JSObject *jsobj = JS_NewArrayObject(cx, 2, NULL);
	JS_SetElement(cx, jsobj, 0, &valA);
	JS_SetElement(cx, jsobj, 1, &valB);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return JS_TRUE;
}


JSBool JSPROXY_cpBodyGetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc!=1) {
        js_log("Invalid number of arguments");
        return JS_FALSE;
    }
    
	jsval *argvp = JS_ARGV(cx,vp);
	cpBody *body;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &body ) )
		return JS_FALSE;
    
	JSObject *data = (JSObject*) cpBodyGetUserData(body);
	
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(data));
	
	return JS_TRUE;
}

JSBool JSPROXY_cpBodySetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	if(argc!=2) {
        js_log("Invalid number of arguments");
        return JS_FALSE;
    }
    
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	
	cpBody *body;
	JSObject *jsobj;
	
	ok &=jsval_to_opaque( cx, *argvp++, (void**) &body );
	ok &=JS_ValueToObject(cx, *argvp++, &jsobj);
	
	if( ! ok )
		return JS_FALSE;
	
	cpBodySetUserData(body, jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	
	return JS_TRUE;
}




/*
 * CCPhysicsSprite
 */
#pragma mark - CCPhysicsSprite

JSClass* JSPROXY_CCPhysicsSprite_class = NULL;
JSObject* JSPROXY_CCPhysicsSprite_object = NULL;
// Constructor

// Destructor
void JSPROXY_CCPhysicsSprite_finalize(JSFreeOp *fop, JSObject *obj)
{
    
}

// Arguments:
// Ret value: cpBody* (N/A)
JSBool JSPROXY_CCPhysicsSprite_body(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    CCPhysicsSprite* real = (CCPhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
	cpBody* ret_val;
    
	ret_val = real->_body;
    jsval ret_jsval = opaque_to_jsval(cx, ret_val);
	JS_SET_RVAL(cx, vp, ret_jsval);
	
	return JS_TRUE;
}

// Arguments:
// Ret value: BOOL (b)
JSBool JSPROXY_CCPhysicsSprite_ignoreBodyRotation(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CCPhysicsSprite* real = (CCPhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	bool ret_val;
    
	ret_val = real->_ignoreBodyRotation;
	JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret_val));
	return JS_TRUE;
}

// Arguments: cpBody*
// Ret value: void (None)
JSBool JSPROXY_CCPhysicsSprite_setBody_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CCPhysicsSprite* real = (CCPhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	
    cpBody* arg0;
    
	ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
	if( ! ok ) return JS_FALSE;
    
	real->setBody((cpBody*)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: BOOL
// Ret value: void (None)
JSBool JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_(JSContext *cx, uint32_t argc, jsval *vp) {
    
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	CCPhysicsSprite* real = (CCPhysicsSprite *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, real)
    
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	JSBool arg0;
    
	ok &= JS_ValueToBoolean( cx, *argvp++, &arg0 );
	if( ! ok ) return JS_FALSE;
    
	real->setIgnoreBodyRotation((bool)arg0);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}


template <class T>
js_type_class_t *js_get_type_from_native(T* native_obj) {
	js_type_class_t *typeProxy;
	uint32_t typeId = reinterpret_cast<int>(typeid(*native_obj).name());
    //const char *nam = typeid(*native_obj).name();
	HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
	if (!typeProxy) {
		TypeInfo *typeInfo = dynamic_cast<TypeInfo *>(native_obj);
		if (typeInfo) {
			typeId = typeInfo->getClassTypeInfo();
		} else {
			typeId = reinterpret_cast<int>(typeid(T).name());
		}
		HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
	}
	return typeProxy;
}

/**
 * you don't need to manage the returned pointer. The returned pointer should be deleted
 * using JS_REMOVE_PROXY. Most of the time you do that in the C++ destructor.
 */
template<class T>
js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj) {
	js_proxy_t *proxy;
	HASH_FIND_PTR(_native_js_global_ht, &native_obj, proxy);
	if (!proxy) {
		js_type_class_t *typeProxy = js_get_type_from_native<T>(native_obj);
		assert(typeProxy);
		JSObject* js_obj = JS_NewObject(cx, typeProxy->jsclass, typeProxy->proto, typeProxy->parentProto);
		JS_NEW_PROXY(proxy, native_obj, js_obj);
        
		JS_AddNamedObjectRoot(cx, &proxy->obj, typeid(native_obj).name());
		return proxy;
	} else {
		return proxy;
	}
	return NULL;
}


template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
    
	return JS_TRUE;
}

// Arguments: NSString*, CGRect
// Ret value: CCPhysicsSprite* (o)
JSBool JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static(JSContext *cx, uint32_t argc, jsval *vp) {
    
    jsval *argv = JS_ARGV(cx, vp);
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		cocos2d::CCRect arg1;
		arg1 = jsval_to_ccrect(cx, argv[1]);
        CCPhysicsSprite* ret = new CCPhysicsSprite();
        ret->initWithFile(arg0, arg1);
		jsval jsret;
		do {
			if (ret) {
                TypeTest<CCPhysicsSprite> t;
                js_type_class_t *typeClass;
                uint32_t typeId = t.s_id();
                HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
                assert(typeClass);
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
				jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p;
                JS_NEW_PROXY(p, ret, obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
		CCPhysicsSprite* ret = new CCPhysicsSprite();
        ret->initWithFile(arg0);
        
		jsval jsret;
		do {
			if (ret) {
				TypeTest<CCPhysicsSprite> t;
                js_type_class_t *typeClass;
                uint32_t typeId = t.s_id();
                HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
                assert(typeClass);
                JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
				jsret = OBJECT_TO_JSVAL(obj);
                js_proxy_t *p;
                JS_NEW_PROXY(p, ret, obj);
                
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	return JS_FALSE;
    
}

// Arguments: CCSpriteFrame*
// Ret value: CCPhysicsSprite* (o)
JSBool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	cocos2d::CCSpriteFrame* arg0;
	if (argc >= 1) {
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCSpriteFrame*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, arg0)
		} while (0);
	}
    CCPhysicsSprite* ret = new CCPhysicsSprite();
    ret->initWithSpriteFrame(arg0);
	jsval jsret;
	do {
		if (ret) {
            TypeTest<CCPhysicsSprite> t;
            js_type_class_t *typeClass;
            uint32_t typeId = t.s_id();
            HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
            assert(typeClass);
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p;
            JS_NEW_PROXY(p, ret, obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

// Arguments: NSString*
// Ret value: CCPhysicsSprite* (o)
JSBool JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static(JSContext *cx, uint32_t argc, jsval *vp) {
	jsval *argv = JS_ARGV(cx, vp);
	const char* arg0;
	if (argc >= 1) {
		std::string arg0_tmp = jsval_to_std_string(cx, argv[0]); arg0 = arg0_tmp.c_str();
	}
    CCPhysicsSprite* ret = new CCPhysicsSprite();
    ret->initWithSpriteFrameName(arg0);
	jsval jsret;
	do {
		if (ret) {
            TypeTest<CCPhysicsSprite> t;
            js_type_class_t *typeClass;
            uint32_t typeId = t.s_id();
            HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
            assert(typeClass);
            JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            jsret = OBJECT_TO_JSVAL(obj);
            js_proxy_t *p;
            JS_NEW_PROXY(p, ret, obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

void JSPROXY_CCPhysicsSprite_createClass(JSContext *cx, JSObject* globalObj)
{
	JSPROXY_CCPhysicsSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSPROXY_CCPhysicsSprite_class->name = "PhysicsSprite";
	JSPROXY_CCPhysicsSprite_class->addProperty = JS_PropertyStub;
	JSPROXY_CCPhysicsSprite_class->delProperty = JS_PropertyStub;
	JSPROXY_CCPhysicsSprite_class->getProperty = JS_PropertyStub;
	JSPROXY_CCPhysicsSprite_class->setProperty = JS_StrictPropertyStub;
	JSPROXY_CCPhysicsSprite_class->enumerate = JS_EnumerateStub;
	JSPROXY_CCPhysicsSprite_class->resolve = JS_ResolveStub;
	JSPROXY_CCPhysicsSprite_class->convert = JS_ConvertStub;
	JSPROXY_CCPhysicsSprite_class->finalize = JSPROXY_CCPhysicsSprite_finalize;
	JSPROXY_CCPhysicsSprite_class->flags = 0;
    
	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("getBody", JSPROXY_CCPhysicsSprite_body, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("getIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_ignoreBodyRotation, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("setBody", JSPROXY_CCPhysicsSprite_setBody_, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("setIgnoreBodyRotation", JSPROXY_CCPhysicsSprite_setIgnoreBodyRotation_, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", JSPROXY_CCPhysicsSprite_spriteWithFile_rect__static, 2, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrame", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrame__static, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("createWithSpriteFrameName", JSPROXY_CCPhysicsSprite_spriteWithSpriteFrameName__static, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FS_END
	};
    
    TypeTest<cocos2d::CCSprite> t1;
    js_type_class_t *typeClass;
    uint32_t typeId = t1.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
    assert(typeClass);
    
	JSPROXY_CCPhysicsSprite_object = JS_InitClass(cx, globalObj, typeClass->proto, JSPROXY_CCPhysicsSprite_class, dummy_constructor<CCPhysicsSprite>, 0,properties,funcs,NULL,st_funcs);
    
    TypeTest<CCPhysicsSprite> t;
	js_type_class_t *p;
	typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = JSPROXY_CCPhysicsSprite_class;
		p->proto = JSPROXY_CCPhysicsSprite_object;
		p->parentProto = typeClass->proto;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


void register_CCPhysicsSprite(JSContext *cx, JSObject *obj) {
    jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;
    JSPROXY_CCPhysicsSprite_createClass(cx, obj);
}

void register_chipmunk_manual(JSContext* cx, JSObject* global)
{
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, global, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, global, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
    
    
    // register chipmunk functions
    JSObject *chipmunk = JS_NewObject(cx, NULL, NULL, NULL);
    jsval chipmunkVal = OBJECT_TO_JSVAL(chipmunk);
    JS_SetProperty(cx, global, "cp", &chipmunkVal);
    JS_DefineFunction(cx, chipmunk, "arbiterGetCount", JSPROXY_cpArbiterGetCount, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetDepth", JSPROXY_cpArbiterGetDepth, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetElasticity", JSPROXY_cpArbiterGetElasticity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetFriction", JSPROXY_cpArbiterGetFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetNormal", JSPROXY_cpArbiterGetNormal, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetPoint", JSPROXY_cpArbiterGetPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetSurfaceVelocity", JSPROXY_cpArbiterGetSurfaceVelocity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterIgnore", JSPROXY_cpArbiterIgnore, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterIsFirstContact", JSPROXY_cpArbiterIsFirstContact, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterSetElasticity", JSPROXY_cpArbiterSetElasticity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterSetFriction", JSPROXY_cpArbiterSetFriction, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterSetSurfaceVelocity", JSPROXY_cpArbiterSetSurfaceVelocity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterTotalImpulse", JSPROXY_cpArbiterTotalImpulse, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterTotalImpulseWithFriction", JSPROXY_cpArbiterTotalImpulseWithFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterTotalKE", JSPROXY_cpArbiterTotalKE, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "areaForCircle", JSPROXY_cpAreaForCircle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "areaForSegment", JSPROXY_cpAreaForSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBArea", JSPROXY_cpBBArea, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBClampVect", JSPROXY_cpBBClampVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBContainsBB", JSPROXY_cpBBContainsBB, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBContainsVect", JSPROXY_cpBBContainsVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBExpand", JSPROXY_cpBBExpand, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBIntersects", JSPROXY_cpBBIntersects, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBIntersectsSegment", JSPROXY_cpBBIntersectsSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBMerge", JSPROXY_cpBBMerge, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBMergedArea", JSPROXY_cpBBMergedArea, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBNew", JSPROXY_cpBBNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBNewForCircle", JSPROXY_cpBBNewForCircle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBSegmentQuery", JSPROXY_cpBBSegmentQuery, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bBWrapVect", JSPROXY_cpBBWrapVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyActivate", JSPROXY_cpBodyActivate, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyActivateStatic", JSPROXY_cpBodyActivateStatic, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyAlloc", JSPROXY_cpBodyAlloc, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyApplyForce", JSPROXY_cpBodyApplyForce, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyApplyImpulse", JSPROXY_cpBodyApplyImpulse, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyDestroy", JSPROXY_cpBodyDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyFree", JSPROXY_cpBodyFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetAngVel", JSPROXY_cpBodyGetAngVel, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetAngVelLimit", JSPROXY_cpBodyGetAngVelLimit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetAngle", JSPROXY_cpBodyGetAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetForce", JSPROXY_cpBodyGetForce, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetMass", JSPROXY_cpBodyGetMass, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetMoment", JSPROXY_cpBodyGetMoment, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetPos", JSPROXY_cpBodyGetPos, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetRot", JSPROXY_cpBodyGetRot, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetSpace", JSPROXY_cpBodyGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetTorque", JSPROXY_cpBodyGetTorque, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetVel", JSPROXY_cpBodyGetVel, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetVelAtLocalPoint", JSPROXY_cpBodyGetVelAtLocalPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetVelAtWorldPoint", JSPROXY_cpBodyGetVelAtWorldPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetVelLimit", JSPROXY_cpBodyGetVelLimit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyInit", JSPROXY_cpBodyInit, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyInitStatic", JSPROXY_cpBodyInitStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyIsRogue", JSPROXY_cpBodyIsRogue, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyIsSleeping", JSPROXY_cpBodyIsSleeping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyIsStatic", JSPROXY_cpBodyIsStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyKineticEnergy", JSPROXY_cpBodyKineticEnergy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyLocal2World", JSPROXY_cpBodyLocal2World, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyNew", JSPROXY_cpBodyNew, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyNewStatic", JSPROXY_cpBodyNewStatic, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyResetForces", JSPROXY_cpBodyResetForces, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetAngVel", JSPROXY_cpBodySetAngVel, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetAngVelLimit", JSPROXY_cpBodySetAngVelLimit, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetAngle", JSPROXY_cpBodySetAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetForce", JSPROXY_cpBodySetForce, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetMass", JSPROXY_cpBodySetMass, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetMoment", JSPROXY_cpBodySetMoment, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetPos", JSPROXY_cpBodySetPos, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetTorque", JSPROXY_cpBodySetTorque, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetVel", JSPROXY_cpBodySetVel, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetVelLimit", JSPROXY_cpBodySetVelLimit, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySleep", JSPROXY_cpBodySleep, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySleepWithGroup", JSPROXY_cpBodySleepWithGroup, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyUpdatePosition", JSPROXY_cpBodyUpdatePosition, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyUpdateVelocity", JSPROXY_cpBodyUpdateVelocity, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyWorld2Local", JSPROXY_cpBodyWorld2Local, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "boxShapeNew", JSPROXY_cpBoxShapeNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "boxShapeNew2", JSPROXY_cpBoxShapeNew2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "circleShapeGetOffset", JSPROXY_cpCircleShapeGetOffset, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "circleShapeGetRadius", JSPROXY_cpCircleShapeGetRadius, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "circleShapeNew", JSPROXY_cpCircleShapeNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintActivateBodies", JSPROXY_cpConstraintActivateBodies, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintDestroy", JSPROXY_cpConstraintDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintFree", JSPROXY_cpConstraintFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetA", JSPROXY_cpConstraintGetA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetB", JSPROXY_cpConstraintGetB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetErrorBias", JSPROXY_cpConstraintGetErrorBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetImpulse", JSPROXY_cpConstraintGetImpulse, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetMaxBias", JSPROXY_cpConstraintGetMaxBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetMaxForce", JSPROXY_cpConstraintGetMaxForce, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintGetSpace", JSPROXY_cpConstraintGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintSetErrorBias", JSPROXY_cpConstraintSetErrorBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintSetMaxBias", JSPROXY_cpConstraintSetMaxBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "constraintSetMaxForce", JSPROXY_cpConstraintSetMaxForce, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringGetDamping", JSPROXY_cpDampedRotarySpringGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringGetRestAngle", JSPROXY_cpDampedRotarySpringGetRestAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringGetStiffness", JSPROXY_cpDampedRotarySpringGetStiffness, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringNew", JSPROXY_cpDampedRotarySpringNew, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringSetDamping", JSPROXY_cpDampedRotarySpringSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringSetRestAngle", JSPROXY_cpDampedRotarySpringSetRestAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedRotarySpringSetStiffness", JSPROXY_cpDampedRotarySpringSetStiffness, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringGetAnchr1", JSPROXY_cpDampedSpringGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringGetAnchr2", JSPROXY_cpDampedSpringGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringGetDamping", JSPROXY_cpDampedSpringGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringGetRestLength", JSPROXY_cpDampedSpringGetRestLength, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringGetStiffness", JSPROXY_cpDampedSpringGetStiffness, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringNew", JSPROXY_cpDampedSpringNew, 7, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringSetAnchr1", JSPROXY_cpDampedSpringSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringSetAnchr2", JSPROXY_cpDampedSpringSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringSetDamping", JSPROXY_cpDampedSpringSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringSetRestLength", JSPROXY_cpDampedSpringSetRestLength, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "dampedSpringSetStiffness", JSPROXY_cpDampedSpringSetStiffness, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "gearJointGetPhase", JSPROXY_cpGearJointGetPhase, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "gearJointGetRatio", JSPROXY_cpGearJointGetRatio, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "gearJointNew", JSPROXY_cpGearJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "gearJointSetPhase", JSPROXY_cpGearJointSetPhase, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "gearJointSetRatio", JSPROXY_cpGearJointSetRatio, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointGetAnchr2", JSPROXY_cpGrooveJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointGetGrooveA", JSPROXY_cpGrooveJointGetGrooveA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointGetGrooveB", JSPROXY_cpGrooveJointGetGrooveB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointNew", JSPROXY_cpGrooveJointNew, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointSetAnchr2", JSPROXY_cpGrooveJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointSetGrooveA", JSPROXY_cpGrooveJointSetGrooveA, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "grooveJointSetGrooveB", JSPROXY_cpGrooveJointSetGrooveB, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "initChipmunk", JSPROXY_cpInitChipmunk, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "momentForBox", JSPROXY_cpMomentForBox, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "momentForBox2", JSPROXY_cpMomentForBox2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "momentForCircle", JSPROXY_cpMomentForCircle, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "momentForSegment", JSPROXY_cpMomentForSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointGetAnchr1", JSPROXY_cpPinJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointGetAnchr2", JSPROXY_cpPinJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointGetDist", JSPROXY_cpPinJointGetDist, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointNew", JSPROXY_cpPinJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointSetAnchr1", JSPROXY_cpPinJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointSetAnchr2", JSPROXY_cpPinJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pinJointSetDist", JSPROXY_cpPinJointSetDist, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointGetAnchr1", JSPROXY_cpPivotJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointGetAnchr2", JSPROXY_cpPivotJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointNew", JSPROXY_cpPivotJointNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointNew2", JSPROXY_cpPivotJointNew2, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointSetAnchr1", JSPROXY_cpPivotJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "pivotJointSetAnchr2", JSPROXY_cpPivotJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "polyShapeGetNumVerts", JSPROXY_cpPolyShapeGetNumVerts, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "polyShapeGetVert", JSPROXY_cpPolyShapeGetVert, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointGetAngle", JSPROXY_cpRatchetJointGetAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointGetPhase", JSPROXY_cpRatchetJointGetPhase, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointGetRatchet", JSPROXY_cpRatchetJointGetRatchet, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointNew", JSPROXY_cpRatchetJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointSetAngle", JSPROXY_cpRatchetJointSetAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointSetPhase", JSPROXY_cpRatchetJointSetPhase, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "ratchetJointSetRatchet", JSPROXY_cpRatchetJointSetRatchet, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "resetShapeIdCounter", JSPROXY_cpResetShapeIdCounter, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "rotaryLimitJointGetMax", JSPROXY_cpRotaryLimitJointGetMax, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "rotaryLimitJointGetMin", JSPROXY_cpRotaryLimitJointGetMin, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "rotaryLimitJointNew", JSPROXY_cpRotaryLimitJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "rotaryLimitJointSetMax", JSPROXY_cpRotaryLimitJointSetMax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "rotaryLimitJointSetMin", JSPROXY_cpRotaryLimitJointSetMin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeGetA", JSPROXY_cpSegmentShapeGetA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeGetB", JSPROXY_cpSegmentShapeGetB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeGetNormal", JSPROXY_cpSegmentShapeGetNormal, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeGetRadius", JSPROXY_cpSegmentShapeGetRadius, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeNew", JSPROXY_cpSegmentShapeNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "segmentShapeSetNeighbors", JSPROXY_cpSegmentShapeSetNeighbors, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeCacheBB", JSPROXY_cpShapeCacheBB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeDestroy", JSPROXY_cpShapeDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeFree", JSPROXY_cpShapeFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetBB", JSPROXY_cpShapeGetBB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetBody", JSPROXY_cpShapeGetBody, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetCollisionType", JSPROXY_cpShapeGetCollisionType, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetElasticity", JSPROXY_cpShapeGetElasticity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetFriction", JSPROXY_cpShapeGetFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetGroup", JSPROXY_cpShapeGetGroup, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetLayers", JSPROXY_cpShapeGetLayers, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetSensor", JSPROXY_cpShapeGetSensor, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetSpace", JSPROXY_cpShapeGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeGetSurfaceVelocity", JSPROXY_cpShapeGetSurfaceVelocity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapePointQuery", JSPROXY_cpShapePointQuery, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetBody", JSPROXY_cpShapeSetBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetCollisionType", JSPROXY_cpShapeSetCollisionType, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetElasticity", JSPROXY_cpShapeSetElasticity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetFriction", JSPROXY_cpShapeSetFriction, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetGroup", JSPROXY_cpShapeSetGroup, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetLayers", JSPROXY_cpShapeSetLayers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetSensor", JSPROXY_cpShapeSetSensor, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeSetSurfaceVelocity", JSPROXY_cpShapeSetSurfaceVelocity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "shapeUpdate", JSPROXY_cpShapeUpdate, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "simpleMotorGetRate", JSPROXY_cpSimpleMotorGetRate, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "simpleMotorNew", JSPROXY_cpSimpleMotorNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "simpleMotorSetRate", JSPROXY_cpSimpleMotorSetRate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointGetAnchr1", JSPROXY_cpSlideJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointGetAnchr2", JSPROXY_cpSlideJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointGetMax", JSPROXY_cpSlideJointGetMax, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointGetMin", JSPROXY_cpSlideJointGetMin, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointNew", JSPROXY_cpSlideJointNew, 6, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointSetAnchr1", JSPROXY_cpSlideJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointSetAnchr2", JSPROXY_cpSlideJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointSetMax", JSPROXY_cpSlideJointSetMax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "slideJointSetMin", JSPROXY_cpSlideJointSetMin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceActivateShapesTouchingShape", JSPROXY_cpSpaceActivateShapesTouchingShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceAddBody", JSPROXY_cpSpaceAddBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceAddConstraint", JSPROXY_cpSpaceAddConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceAddShape", JSPROXY_cpSpaceAddShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceAddStaticShape", JSPROXY_cpSpaceAddStaticShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceAlloc", JSPROXY_cpSpaceAlloc, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceContainsBody", JSPROXY_cpSpaceContainsBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceContainsConstraint", JSPROXY_cpSpaceContainsConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceContainsShape", JSPROXY_cpSpaceContainsShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceDestroy", JSPROXY_cpSpaceDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceFree", JSPROXY_cpSpaceFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetCollisionBias", JSPROXY_cpSpaceGetCollisionBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetCollisionPersistence", JSPROXY_cpSpaceGetCollisionPersistence, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetCollisionSlop", JSPROXY_cpSpaceGetCollisionSlop, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetCurrentTimeStep", JSPROXY_cpSpaceGetCurrentTimeStep, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetDamping", JSPROXY_cpSpaceGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetEnableContactGraph", JSPROXY_cpSpaceGetEnableContactGraph, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetGravity", JSPROXY_cpSpaceGetGravity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetIdleSpeedThreshold", JSPROXY_cpSpaceGetIdleSpeedThreshold, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetIterations", JSPROXY_cpSpaceGetIterations, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetSleepTimeThreshold", JSPROXY_cpSpaceGetSleepTimeThreshold, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceGetStaticBody", JSPROXY_cpSpaceGetStaticBody, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceInit", JSPROXY_cpSpaceInit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceIsLocked", JSPROXY_cpSpaceIsLocked, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceNew", JSPROXY_cpSpaceNew, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spacePointQueryFirst", JSPROXY_cpSpacePointQueryFirst, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceReindexShape", JSPROXY_cpSpaceReindexShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceReindexShapesForBody", JSPROXY_cpSpaceReindexShapesForBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceReindexStatic", JSPROXY_cpSpaceReindexStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveBody", JSPROXY_cpSpaceRemoveBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveConstraint", JSPROXY_cpSpaceRemoveConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveShape", JSPROXY_cpSpaceRemoveShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveStaticShape", JSPROXY_cpSpaceRemoveStaticShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetCollisionBias", JSPROXY_cpSpaceSetCollisionBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetCollisionPersistence", JSPROXY_cpSpaceSetCollisionPersistence, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetCollisionSlop", JSPROXY_cpSpaceSetCollisionSlop, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetDamping", JSPROXY_cpSpaceSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetEnableContactGraph", JSPROXY_cpSpaceSetEnableContactGraph, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetGravity", JSPROXY_cpSpaceSetGravity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetIdleSpeedThreshold", JSPROXY_cpSpaceSetIdleSpeedThreshold, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetIterations", JSPROXY_cpSpaceSetIterations, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceSetSleepTimeThreshold", JSPROXY_cpSpaceSetSleepTimeThreshold, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceStep", JSPROXY_cpSpaceStep, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceUseSpatialHash", JSPROXY_cpSpaceUseSpatialHash, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "fabs", JSPROXY_cpfabs, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "fclamp", JSPROXY_cpfclamp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "fclamp01", JSPROXY_cpfclamp01, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "flerp", JSPROXY_cpflerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "flerpconst", JSPROXY_cpflerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "fmax", JSPROXY_cpfmax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "fmin", JSPROXY_cpfmin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "v", JSPROXY_cpv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vadd", JSPROXY_cpvadd, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vclamp", JSPROXY_cpvclamp, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vcross", JSPROXY_cpvcross, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vdist", JSPROXY_cpvdist, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vdistsq", JSPROXY_cpvdistsq, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vdot", JSPROXY_cpvdot, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "veql", JSPROXY_cpveql, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vforangle", JSPROXY_cpvforangle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vlength", JSPROXY_cpvlength, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vlengthsq", JSPROXY_cpvlengthsq, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vlerp", JSPROXY_cpvlerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vlerpconst", JSPROXY_cpvlerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vmult", JSPROXY_cpvmult, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vnear", JSPROXY_cpvnear, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vneg", JSPROXY_cpvneg, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vnormalize", JSPROXY_cpvnormalize, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vnormalize_safe", JSPROXY_cpvnormalize_safe, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vperp", JSPROXY_cpvperp, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vproject", JSPROXY_cpvproject, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vrotate", JSPROXY_cpvrotate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vrperp", JSPROXY_cpvrperp, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vslerp", JSPROXY_cpvslerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vslerpconst", JSPROXY_cpvslerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vsub", JSPROXY_cpvsub, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vtoangle", JSPROXY_cpvtoangle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "vunrotate", JSPROXY_cpvunrotate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    

    // manual
    JS_DefineFunction(cx, chipmunk, "spaceAddCollisionHandler", JSPROXY_cpSpaceAddCollisionHandler, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "spaceRemoveCollisionHandler", JSPROXY_cpSpaceRemoveCollisionHandler, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetBodies", JSPROXY_cpArbiterGetBodies, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "arbiterGetShapes", JSPROXY_cpArbiterGetShapes, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodyGetUserData", JSPROXY_cpBodyGetUserData, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, chipmunk, "bodySetUserData", JSPROXY_cpBodySetUserData, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    
}




