/*
 * JS Bindings: https://github.com/zynga/jsbindings
 *
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "js_bindings_config.h"
#ifdef JSB_INCLUDE_CHIPMUNK

#include "jsapi.h"
#include "jsfriendapi.h"

#include "js_bindings_chipmunk_manual.h"
#include "js_manual_conversions.h"
#include "uthash.h"
#include "CCPhysicsSprite.h"

// Function declarations
void static freeSpaceChildren(cpSpace *space);


#pragma mark - convertions

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


JSBool jsval_to_cpBB( JSContext *cx, jsval vp, cpBB *ret )
{
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION( ok, "Error converting value to object");
	JSB_PRECONDITION( jsobj, "Not a valid JS object");
	
	jsval vall, valb, valr, valt;
	ok = JS_TRUE;
	ok &= JS_GetProperty(cx, jsobj, "l", &vall);
	ok &= JS_GetProperty(cx, jsobj, "b", &valb);
	ok &= JS_GetProperty(cx, jsobj, "r", &valr);
	ok &= JS_GetProperty(cx, jsobj, "t", &valt);
	JSB_PRECONDITION( ok, "Error obtaining point properties");
	
	double l, b, r, t;
	ok &= JS_ValueToNumber(cx, vall, &l);
	ok &= JS_ValueToNumber(cx, valb, &b);
	ok &= JS_ValueToNumber(cx, valr, &r);
	ok &= JS_ValueToNumber(cx, valt, &t);
	JSB_PRECONDITION( ok, "Error converting value to numbers");
	
	ret->l = l;
	ret->b = b;
	ret->r = r;
	ret->t = t;
	
	return JS_TRUE;
}

jsval cpBB_to_jsval(JSContext *cx, cpBB bb )
{
	JSObject *object = JS_NewObject(cx, NULL, NULL, NULL );
	if (!object)
		return JSVAL_VOID;
	
	if (!JS_DefineProperty(cx, object, "l", DOUBLE_TO_JSVAL(bb.l), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "b", DOUBLE_TO_JSVAL(bb.b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "r", DOUBLE_TO_JSVAL(bb.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) ||
		!JS_DefineProperty(cx, object, "t", DOUBLE_TO_JSVAL(bb.t), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) )
		return JSVAL_VOID;
	
	return OBJECT_TO_JSVAL(object);
}

// In order to be compatible with Chipmunk-JS API,
// this function expect to receive an array of numbers, and not an array of vects
// OK:  [1,2,  3,4,  5,6]   <- expected
// BAD: [{x:1, y:2}, {x:3,y:4}, {x:5, y:6}]  <- not expected
JSBool jsval_to_array_of_cpvect( JSContext *cx, jsval vp, cpVect**verts, int *numVerts)
{
	// Parsing sequence
	JSObject *jsobj;
	JSBool ok = JS_ValueToObject( cx, vp, &jsobj );
	JSB_PRECONDITION( ok, "Error converting value to object");
	
	JSB_PRECONDITION( jsobj && JS_IsArrayObject( cx, jsobj),  "Object must be an array");

	uint32_t len;
	JS_GetArrayLength(cx, jsobj, &len);
	
	JSB_PRECONDITION( len%2==0, "Array lenght should be even");
	
	cpVect *array = (cpVect*)malloc( sizeof(cpVect) * len/2);
	
	for( uint32_t i=0; i< len;i++ ) {
		jsval valarg;
		JS_GetElement(cx, jsobj, i, &valarg);

		double value;
		ok = JS_ValueToNumber(cx, valarg, &value);
		JSB_PRECONDITION( ok, "Error converting value to nsobject");
		
		if(i%2==0)
			array[i/2].x = value;
		else
			array[i/2].y = value;
	}
	
	*numVerts = len/2;
	*verts = array;
	
	return JS_TRUE;
}

#pragma mark - Collision Handler

struct collision_handler {
	cpCollisionType		typeA;
	cpCollisionType		typeB;
	jsval				begin;
	jsval				pre;
	jsval				post;
	jsval				separate;
	JSObject			*jsthis;
	JSContext			*cx;

	unsigned long		hash_key;

	unsigned int		is_oo; // Objected oriented API ?
	UT_hash_handle  hh;
};

// hash
struct collision_handler* collision_handler_hash = NULL;

// helper pair
static unsigned long pair_ints( unsigned long A, unsigned long B )
{
	// order is not important
	unsigned long k1 = MIN(A, B );
	unsigned long k2 = MAX(A, B );
	
	return (k1 + k2) * (k1 + k2 + 1) /2 + k2;
}

static cpBool myCollisionBegin(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
	
	jsval rval;
	JSBool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, handler->begin, 2, args, &rval);
	JSB_PRECONDITION2(ok, handler->cx, cpFalse, "Error calling collision callback: begin");

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
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
	
	jsval rval;
	JSBool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, handler->pre, 2, args, &rval);
	JSB_PRECONDITION2(ok, handler->cx, JS_FALSE, "Error calling collision callback: pre");
	
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
	
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
	
	jsval ignore;
	JSBool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, handler->post, 2, args, &ignore);
	JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Post");
}

static void myCollisionSeparate(cpArbiter *arb, cpSpace *space, void *data)
{
	struct collision_handler *handler = (struct collision_handler*) data;
	
	jsval args[2];
	if( handler->is_oo ) {
		args[0] = c_class_to_jsval(handler->cx, arb, JSB_cpArbiter_object, JSB_cpArbiter_class, "cpArbiter");
		args[1] = c_class_to_jsval(handler->cx, space, JSB_cpSpace_object, JSB_cpSpace_class, "cpArbiter");
	} else {
		args[0] = opaque_to_jsval( handler->cx, arb);
		args[1] = opaque_to_jsval( handler->cx, space );
	}
	
	jsval ignore;
	JSBool ok = JS_CallFunctionValue( handler->cx, handler->jsthis, handler->separate, 2, args, &ignore);
	JSB_PRECONDITION2(ok, handler->cx, , "Error calling collision callback: Separate");}

#pragma mark - cpSpace

#pragma mark constructor / destructor

void JSB_cpSpace_finalize(JSFreeOp *fop, JSObject *jsthis)
{
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	if( proxy ) {
		CCLOGINFO("jsbindings: finalizing JS object %p (cpSpace), handle: %p", jsthis, proxy->handle);
		
		// Free Space Children
		freeSpaceChildren((cpSpace*)proxy->handle);
		
		jsb_del_jsobject_for_proxy(proxy->handle);
		if(proxy->flags == JSB_C_FLAG_CALL_FREE)
			cpSpaceFree( (cpSpace*)proxy->handle);
		jsb_del_c_proxy_for_jsobject(jsthis);
	}
}


#pragma mark addCollisionHandler

static
JSBool __jsb_cpSpace_addCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, cpSpace *space, unsigned int is_oo)
{
	struct collision_handler *handler = (struct collision_handler*) malloc( sizeof(*handler) );

	JSB_PRECONDITION(handler, "Error allocating memory");
	
	JSBool ok = JS_TRUE;
	
	// args
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &handler->typeB );
	
	// this is no longer passed, so "this" is going to be "this".
//	ok &= JS_ValueToObject(cx, *argvp++, &handler->jsthis );
	handler->jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	
	handler->begin = *argvp++;
	handler->pre = *argvp++;
	handler->post = *argvp++;
	handler->separate = *argvp++;
	
	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	// Object Oriented API ?
	handler->is_oo = is_oo;
	
//	if( ! JSVAL_IS_NULL(handler->begin) )
//		JS_AddNamedValueRoot(cx, &handler->begin, "begin collision_handler");
//	if( ! JSVAL_IS_NULL(handler->pre) )
//		JS_AddNamedValueRoot(cx, &handler->pre, "pre collision_handler");
//	if( ! JSVAL_IS_NULL(handler->post) )
//		JS_AddNamedValueRoot(cx, &handler->post, "post collision_handler");
//	if( ! JSVAL_IS_NULL(handler->separate) )
//		JS_AddNamedValueRoot(cx, &handler->separate, "separate collision_handler");
	
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

JSBool JSB_cpSpaceAddCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==7, cx, JS_FALSE, "Invalid number of arguments");


	jsval *argvp = JS_ARGV(cx,vp);

	// args
	cpSpace *space;
	JSBool ok = jsval_to_opaque( cx, *argvp++, (void**)&space);
	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	return __jsb_cpSpace_addCollisionHandler(cx, vp, argvp, space, 0);
}

// method
JSBool JSB_cpSpace_addCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==6, cx, JS_FALSE, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpSpace_addCollisionHandler(cx, vp, JS_ARGV(cx,vp), (cpSpace*)handle, 1);
}

#pragma mark removeCollisionHandler

static
JSBool __jsb_cpSpace_removeCollisionHandler(JSContext *cx, jsval *vp, jsval *argvp, cpSpace *space)
{
	JSBool ok = JS_TRUE;
	
	cpCollisionType typeA;
	cpCollisionType typeB;
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeA );
	ok &= jsval_to_int(cx, *argvp++, (int32_t*) &typeB );

	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	cpSpaceRemoveCollisionHandler(space, typeA, typeB );
	
	// Remove it
	struct collision_handler *hashElement = NULL;
	unsigned long key = pair_ints(typeA, typeB );
	HASH_FIND_INT(collision_handler_hash, &key, hashElement);
    if( hashElement ) {
		
		// unroot it
//		if( ! JSVAL_IS_NULL(hashElement->begin) )
//			JS_RemoveValueRoot(cx, &hashElement->begin);
//		if( ! JSVAL_IS_NULL(hashElement->pre) )
//			JS_RemoveValueRoot(cx, &hashElement->pre);
//		if( ! JSVAL_IS_NULL(hashElement->post) )
//			JS_RemoveValueRoot(cx, &hashElement->post);
//		if( ! JSVAL_IS_NULL(hashElement->separate) )
//			JS_RemoveValueRoot(cx, &hashElement->separate);
		
		HASH_DEL( collision_handler_hash, hashElement );
		free( hashElement );
	}
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Free function
JSBool JSB_cpSpaceRemoveCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==3, cx, JS_FALSE, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	
	cpSpace* space;
	JSBool ok = jsval_to_opaque( cx, *argvp++, (void**)&space);
	
	JSB_PRECONDITION(ok, "Error parsing arguments");

	return __jsb_cpSpace_removeCollisionHandler(cx, vp, argvp, space);
}

// method
JSBool JSB_cpSpace_removeCollisionHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==2, cx, JS_FALSE, "Invalid number of arguments");

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpSpace_removeCollisionHandler(cx, vp, JS_ARGV(cx,vp), (cpSpace*)handle);
}

#pragma mark Add functios. Root JSObjects

// Arguments: cpBody*
// Ret value: cpBody*
JSBool JSB_cpSpace_addBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddBody((cpSpace*)arg0 , (cpBody*)arg1  );
	
	// Root it:
	JS_AddNamedObjectRoot(cx, &retproxy->jsobj, "cpBody");
	
	// addBody returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: cpConstraint*
JSBool JSB_cpSpace_addConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	
	// Root it:
	JS_AddNamedObjectRoot(cx, &retproxy->jsobj, "cpConstraint");
	
	// addConstraint returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpShape*
JSBool JSB_cpSpace_addShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg1;

	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddShape((cpSpace*)arg0 , (cpShape*)arg1  );
	
	// Root it:
	JS_AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape");
	
	// addShape returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: cpShape*
JSBool JSB_cpSpace_addStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg1;
	
	jsval retval = *argvp; struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceAddStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
	
	// Root it:
	JS_AddNamedObjectRoot(cx, &retproxy->jsobj, "cpShape (static)");

	// addStaticShape returns the same object that was added, so return it without conversions
	JS_SET_RVAL(cx, vp, retval);
    
	return JS_TRUE;
}

#pragma mark Remove functios. Untoot JSObjects

// Arguments: cpBody*
// Ret value: void
JSBool JSB_cpSpace_removeBody(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveBody((cpSpace*)arg0 , (cpBody*)arg1  );
	JS_RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpConstraint*
// Ret value: void
JSBool JSB_cpSpace_removeConstraint(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpConstraint* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveConstraint((cpSpace*)arg0 , (cpConstraint*)arg1  );
	JS_RemoveObjectRoot(cx, &retproxy->jsobj);

	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: void
JSBool JSB_cpSpace_removeShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}

// Arguments: cpShape*
// Ret value: void
JSBool JSB_cpSpace_removeStaticShape(JSContext *cx, uint32_t argc, jsval *vp) {
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	cpSpace* arg0 = (cpSpace*) proxy->handle;
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpShape* arg1;
	
	struct jsb_c_proxy_s *retproxy;
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&arg1, &retproxy );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpSpaceRemoveStaticShape((cpSpace*)arg0 , (cpShape*)arg1  );
	JS_RemoveObjectRoot(cx, &retproxy->jsobj);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}
#pragma mark - Arbiter

#pragma mark getBodies
static
JSBool __jsb_cpArbiter_getBodies(JSContext *cx, jsval *vp, jsval *argvp, cpArbiter *arbiter, unsigned int is_oo)
{
	cpBody *bodyA;
	cpBody *bodyB;
	cpArbiterGetBodies(arbiter, &bodyA, &bodyB);
	
	jsval valA, valB;
	if( is_oo ) {
		valA = c_class_to_jsval(cx, bodyA, JSB_cpBody_object, JSB_cpBody_class, "cpArbiter");
		valB = c_class_to_jsval(cx, bodyB, JSB_cpBody_object, JSB_cpBody_class, "cpArbiter");
	} else {
		valA = opaque_to_jsval(cx, bodyA);
		valB = opaque_to_jsval(cx, bodyB);		
	}
	
	JSObject *jsobj = JS_NewArrayObject(cx, 2, NULL);
	JS_SetElement(cx, jsobj, 0, &valA);
	JS_SetElement(cx, jsobj, 1, &valB);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return JS_TRUE;	
}

// Free function
JSBool JSB_cpArbiterGetBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if( ! jsval_to_opaque( cx, *argvp++, (void**)&arbiter ) )
		return JS_FALSE;

	return __jsb_cpArbiter_getBodies(cx, vp, argvp, arbiter, 0);
}

// Method
JSBool JSB_cpArbiter_getBodies(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==0, cx, JS_FALSE, "Invalid number of arguments");

	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	JSB_PRECONDITION( proxy, "Invalid private object");
	void *handle = proxy->handle;
	
	return __jsb_cpArbiter_getBodies(cx, vp, JS_ARGV(cx,vp), (cpArbiter*)handle, 1);
}

#pragma mark getShapes
static
JSBool __jsb_cpArbiter_getShapes(JSContext *cx, jsval *vp, jsval *argvp, cpArbiter *arbiter, unsigned int is_oo)
{
	cpShape *shapeA;
	cpShape *shapeB;
	cpArbiterGetShapes(arbiter, &shapeA, &shapeB);

	jsval valA, valB;
	if( is_oo ) {
		valA = c_class_to_jsval(cx, shapeA, JSB_cpShape_object, JSB_cpShape_class, "cpShape");
		valB = c_class_to_jsval(cx, shapeB, JSB_cpShape_object, JSB_cpShape_class, "cpShape");
	} else {
		valA = opaque_to_jsval(cx, shapeA);
		valB = opaque_to_jsval(cx, shapeB);
	}
	
	JSObject *jsobj = JS_NewArrayObject(cx, 2, NULL);
	JS_SetElement(cx, jsobj, 0, &valA);
	JS_SetElement(cx, jsobj, 1, &valB);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	return JS_TRUE;
}

// function
JSBool JSB_cpArbiterGetShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	cpArbiter* arbiter;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &arbiter ) )
	   return JS_FALSE;

	return __jsb_cpArbiter_getShapes(cx, vp, argvp, arbiter, 0);
}

// method
JSBool JSB_cpArbiter_getShapes(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==0, cx, JS_FALSE, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpArbiter_getShapes(cx, vp, JS_ARGV(cx,vp), (cpArbiter*)handle, 1);
}

#pragma mark - Body

#pragma mark constructor

// Manually added to identify static vs dynamic bodies
JSBool JSB_cpBody_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==2, cx, JS_FALSE, "Invalid number of arguments");
	JSObject *jsobj = JS_NewObject(cx, JSB_cpBody_class, JSB_cpBody_object, NULL);
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	double m; double i;
	
	ok &= JS_ValueToNumber( cx, *argvp++, &m );
	ok &= JS_ValueToNumber( cx, *argvp++, &i );
	JSB_PRECONDITION(ok, "Error processing arguments");
	
	cpBody *ret_body = NULL;
	if( m == INFINITY && i == INFINITY) {
		ret_body = cpBodyNewStatic();
		
		// XXX: Hack. IT WILL LEAK "rogue" objects., But at least it prevents a crash.
		// The thing is that "rogue" bodies needs to be freed after the its shape, and I am not sure
		// how to do it in a "js" way.
		jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_DO_NOT_CALL_FREE);
	} else {
		ret_body = cpBodyNew((cpFloat)m , (cpFloat)i  );
		jsb_set_c_proxy_for_jsobject(jsobj, ret_body, JSB_C_FLAG_CALL_FREE);
	}
	
	jsb_set_jsobject_for_proxy(jsobj, ret_body);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return JS_TRUE;
}

#pragma mark getUserData

static
JSBool __jsb_cpBody_getUserData(JSContext *cx, jsval *vp, jsval *argvp, cpBody *body)
{
	JSObject *data = (JSObject*) cpBodyGetUserData(body);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(data));
	
	return JS_TRUE;
}

// free function
JSBool JSB_cpBodyGetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	cpBody *body;
	if( ! jsval_to_opaque( cx, *argvp++, (void**) &body ) )
		return JS_FALSE;

	return __jsb_cpBody_getUserData(cx, vp, argvp, body);
}

// method
JSBool JSB_cpBody_getUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==0, cx, JS_FALSE, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpBody_getUserData(cx, vp, JS_ARGV(cx,vp), (cpBody*)handle);
}


#pragma mark setUserData

static
JSBool __jsb_cpBody_setUserData(JSContext *cx, jsval *vp, jsval *argvp, cpBody *body)
{
	JSObject *jsobj;

	JSBool ok = JS_ValueToObject(cx, *argvp++, &jsobj);

	JSB_PRECONDITION(ok, "Error parsing arguments");
	
	cpBodySetUserData(body, jsobj);
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	
	return JS_TRUE;
}

// free function
JSBool JSB_cpBodySetUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==2, cx, JS_FALSE, "Invalid number of arguments");

	jsval *argvp = JS_ARGV(cx,vp);
	cpBody *body;
	JSBool ok = jsval_to_opaque( cx, *argvp++, (void**) &body );
	JSB_PRECONDITION(ok, "Error parsing arguments");
	return __jsb_cpBody_setUserData(cx, vp, argvp, body);
}

// method
JSBool JSB_cpBody_setUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	
	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	return __jsb_cpBody_setUserData(cx, vp, JS_ARGV(cx,vp), (cpBody*)handle);
}

#pragma mark - Poly related

// cpFloat cpAreaForPoly(const int numVerts, const cpVect *verts);
JSBool JSB_cpAreaForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{	
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect *verts;
	int numVerts;
	
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error parsing array");
	
	cpFloat area = cpAreaForPoly(numVerts, verts);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(area));
	return JS_TRUE;
}

// cpFloat cpMomentForPoly(cpFloat m, int numVerts, const cpVect *verts, cpVect offset);
JSBool JSB_cpMomentForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==3, cx, JS_FALSE, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect *verts; cpVect offset;
	int numVerts;
	double m;
	
	ok &= JS_ValueToNumber(cx, *argvp++, &m);
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &offset );

	JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error parsing args");
	
	cpFloat moment = cpMomentForPoly((cpFloat)m, numVerts, verts, offset);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(moment));
	return JS_TRUE;
}

// cpVect cpCentroidForPoly(const int numVerts, const cpVect *verts);
JSBool JSB_cpCentroidForPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpVect *verts;
	int numVerts;
	
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error parsing args");
	
	cpVect centroid = cpCentroidForPoly(numVerts, verts);
	
	free(verts);
	
	JS_SET_RVAL(cx, vp, cpVect_to_jsval(cx, (cpVect)centroid));
	return JS_TRUE;
}

// void cpRecenterPoly(const int numVerts, cpVect *verts);
JSBool JSB_cpRecenterPoly(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCAssert(false, "NOT IMPLEMENTED");
	return JS_FALSE;
}

#pragma mark - Object Oriented Chipmunk

/*
 * Chipmunk Base Object
 */

JSClass* JSB_cpBase_class = NULL;
JSObject* JSB_cpBase_object = NULL;
// Constructor
JSBool JSB_cpBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3( argc==1, cx, JS_FALSE, "Invalid arguments. Expecting 1");
	
	JSObject *jsobj = JS_NewObject(cx, JSB_cpBase_class, JSB_cpBase_object, NULL);
	
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	
	void *handle = NULL;
	
	ok = jsval_to_opaque(cx, *argvp++, &handle);
	
	JSB_PRECONDITION(ok, "Error converting arguments for JSB_cpBase_constructor");

	jsb_set_c_proxy_for_jsobject(jsobj, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsobj, handle);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	return JS_TRUE;
}

// Destructor
void JSB_cpBase_finalize(JSFreeOp *fop, JSObject *obj)
{
	CCLOGINFO("jsbindings: finalizing JS object %p (cpBase)", obj);
	
	// should not delete the handle since it was manually added
}

JSBool JSB_cpBase_getHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	JSB_PRECONDITION3(argc==0, cx, JS_FALSE, "Invalid number of arguments");

	struct jsb_c_proxy_s* proxy = jsb_get_c_proxy_for_jsobject(jsthis);
	void *handle = proxy->handle;
	
	jsval ret_val = opaque_to_jsval(cx, handle);
	JS_SET_RVAL(cx, vp, ret_val);
	return JS_TRUE;
}

JSBool JSB_cpBase_setHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject* jsthis = (JSObject *)JS_THIS_OBJECT(cx, vp);
	JSB_PRECONDITION( jsthis, "Invalid jsthis object");
	JSB_PRECONDITION3(argc==1, cx, JS_FALSE, "Invalid number of arguments");
	
	jsval *argvp = JS_ARGV(cx,vp);
	
	void *handle;
	JSBool ok = jsval_to_opaque(cx, *argvp++, &handle);
	JSB_PRECONDITION( ok, "Invalid parsing arguments");

	jsb_set_c_proxy_for_jsobject(jsthis, handle, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsthis, handle);
	
	JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return JS_TRUE;
}


void JSB_cpBase_createClass(JSContext *cx, JSObject* globalObj, const char* name )
{
	JSB_cpBase_class = (JSClass *)calloc(1, sizeof(JSClass));
	JSB_cpBase_class->name = name;
	JSB_cpBase_class->addProperty = JS_PropertyStub;
	JSB_cpBase_class->delProperty = JS_PropertyStub;
	JSB_cpBase_class->getProperty = JS_PropertyStub;
	JSB_cpBase_class->setProperty = JS_StrictPropertyStub;
	JSB_cpBase_class->enumerate = JS_EnumerateStub;
	JSB_cpBase_class->resolve = JS_ResolveStub;
	JSB_cpBase_class->convert = JS_ConvertStub;
	JSB_cpBase_class->finalize = JSB_cpBase_finalize;
	JSB_cpBase_class->flags = JSCLASS_HAS_PRIVATE;
	
	static JSPropertySpec properties[] = {
		{0, 0, 0, 0, 0}
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("getHandle", JSB_cpBase_getHandle, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FN("setHandle", JSB_cpBase_setHandle, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};
	
	JSB_cpBase_object = JS_InitClass(cx, globalObj, NULL, JSB_cpBase_class, JSB_cpBase_constructor,0,properties,funcs,NULL,st_funcs);
	JSBool found;
	JS_SetPropertyAttributes(cx, globalObj, name, JSPROP_ENUMERATE | JSPROP_READONLY, &found);
}

// Manual "methods"
// Constructor
JSBool JSB_cpPolyShape_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION3(argc==3, cx, JS_FALSE, "Invalid number of arguments");
	JSObject *jsobj = JS_NewObject(cx, JSB_cpPolyShape_class, JSB_cpPolyShape_object, NULL);
	jsval *argvp = JS_ARGV(cx,vp);
	JSBool ok = JS_TRUE;
	cpBody* body; cpVect *verts; cpVect offset;
	int numVerts;
	
	ok &= jsval_to_c_class( cx, *argvp++, (void**)&body, NULL );
	ok &= jsval_to_array_of_cpvect( cx, *argvp++, &verts, &numVerts);
	ok &= jsval_to_cpVect( cx, *argvp++, (cpVect*) &offset );
	JSB_PRECONDITION(ok, "Error processing arguments");
	cpShape *shape = cpPolyShapeNew(body, numVerts, verts, offset);

	jsb_set_c_proxy_for_jsobject(jsobj, shape, JSB_C_FLAG_DO_NOT_CALL_FREE);
	jsb_set_jsobject_for_proxy(jsobj, shape);
	
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsobj));
	
	free(verts);
	
	return JS_TRUE;
}


#pragma mark Space Free functions
//
// When the space is removed, it should all remove its children. But not "free" them.
// "free" will be performed by the JS Garbage Collector
//
// Functions copied & pasted from ChipmunkDemo.c
// https://github.com/slembcke/Chipmunk-Physics/blob/master/Demo/ChipmunkDemo.c#L89
//

static void unroot_jsobject_from_handle(void *handle)
{
	JSObject *jsobj = jsb_get_jsobject_for_proxy(handle);
	struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(jsobj);
	
	// HACK context from global
	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	JS_RemoveObjectRoot(cx, &proxy->jsobj);
	
}
static void shapeFreeWrap(cpSpace *space, cpShape *shape, void *unused){
	cpSpaceRemoveShape(space, shape);
	unroot_jsobject_from_handle(shape);
//	cpShapeFree(shape);
}

static void postShapeFree(cpShape *shape, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)shapeFreeWrap, shape, NULL);
}

static void constraintFreeWrap(cpSpace *space, cpConstraint *constraint, void *unused){
	cpSpaceRemoveConstraint(space, constraint);
	unroot_jsobject_from_handle(constraint);
//	cpConstraintFree(constraint);
}

static void postConstraintFree(cpConstraint *constraint, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)constraintFreeWrap, constraint, NULL);
}

static void bodyFreeWrap(cpSpace *space, cpBody *body, void *unused){
	cpSpaceRemoveBody(space, body);
	unroot_jsobject_from_handle(body);
//	cpBodyFree(body);
}

static void postBodyFree(cpBody *body, cpSpace *space){
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)bodyFreeWrap, body, NULL);
}

// Safe and future proof way to remove and free all objects that have been added to the space.
void static freeSpaceChildren(cpSpace *space)
{
	// Must remove these BEFORE freeing the body or you will access dangling pointers.
	cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)postShapeFree, space);
	cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)postConstraintFree, space);
	
	cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)postBodyFree, space);
}

#endif // JSB_INCLUDE_CHIPMUNK
